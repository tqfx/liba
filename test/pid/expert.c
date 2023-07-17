#include "expert.h"
#include "../src/pid.h"
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

void a_pid_expert_init(a_pid_expert_s *const ctx, unsigned int const num)
{
    ctx->pid.chan = num;
    a_pid_expert_zero(ctx);
}

void a_pid_expert_chan(a_pid_expert_s *const ctx, unsigned int const num, a_float_t *const out, a_float_t *const fdb,
                       a_float_t *const tmp, a_float_t *const err, a_float_t *const ec)
{
#define A_PID_EXPERT_CHAN(ctx) \
    do                         \
    {                          \
        (ctx)->ec.p = ec;      \
    } while (0)
    ctx->pid.chan = num;
    if (ctx->pid.chan)
    {
        A_PID_CHAN(&ctx->pid);
        A_PID_EXPERT_CHAN(ctx);
    }
    a_pid_expert_zero(ctx);
}

void a_pid_expert_kpid(a_pid_expert_s *const ctx, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    a_pid_kpid(&ctx->pid, kp, ki, kd);
}

void a_pid_expert_zero(a_pid_expert_s *const ctx)
{
#define A_PID_EXPERT_ZERO(ctx, _) \
    do                            \
    {                             \
        (ctx)->ec _ = 0;          \
    } while (0)
    if (ctx->pid.chan)
    {
        for (unsigned int i = 0; i != ctx->pid.chan; ++i)
        {
            A_PID_ZERO(&ctx->pid, .p[i]);
            A_PID_EXPERT_ZERO(ctx, .p[i]);
        }
    }
    else
    {
        A_PID_ZERO(&ctx->pid, .f);
        A_PID_EXPERT_ZERO(ctx, .f);
    }
}

A_HIDDEN void a_pid_expert_outf_(a_pid_expert_s *ctx, a_float_t fdb, a_float_t ec, a_float_t e);
void a_pid_expert_outf_(a_pid_expert_s *const ctx, a_float_t const fdb, a_float_t const ec, a_float_t const e)
{
#define A_PID_EXPERT_OUT_(_)                                                             \
    a_float_t out = 0;                                                                   \
    a_float_t const abs = A_ABS(e);                                                      \
    a_float_t const tmp = ctx->pid.fdb _ - fdb;                                          \
                                                                                         \
    if (-ctx->max1 > e)                                                                  \
    {                                                                                    \
        out = -ctx->outmax;                                                              \
        goto out;                                                                        \
    }                                                                                    \
    else if (e > ctx->max1)                                                              \
    {                                                                                    \
        out = ctx->outmax;                                                               \
        goto out;                                                                        \
    }                                                                                    \
                                                                                         \
    if (e * ec > 0 || ec == 0)                                                           \
    {                                                                                    \
        out = ctx->pid.kp * ec + ctx->pid.ki * e + ctx->pid.kd * (tmp - ctx->pid.tmp _); \
        if (abs > ctx->max2)                                                             \
        {                                                                                \
            out *= ctx->gain;                                                            \
        }                                                                                \
    }                                                                                    \
    else if (ec * ctx->ec _ < 0 && e != 0)                                               \
    {                                                                                    \
        out = ctx->pid.kp * ctx->pid.err _;                                              \
        if (abs > ctx->max2)                                                             \
        {                                                                                \
            out *= ctx->gain;                                                            \
        }                                                                                \
        else                                                                             \
        {                                                                                \
            out *= ctx->loss;                                                            \
        }                                                                                \
    }                                                                                    \
                                                                                         \
    if (abs < ctx->epsilon)                                                              \
    {                                                                                    \
        out = ctx->pid.kp * ec + ctx->pid.ki * e;                                        \
    }                                                                                    \
    out:                                                                                 \
                                                                                         \
    ctx->pid.out _ = A_SAT(out, ctx->pid.outmin, ctx->pid.outmax);                       \
    ctx->pid.fdb _ = fdb;                                                                \
    ctx->pid.tmp _ = tmp;                                                                \
    ctx->pid.err _ = e;                                                                  \
    ctx->ec _ = ec
    A_PID_EXPERT_OUT_(.f);
}

A_HIDDEN void a_pid_expert_outp_(a_pid_expert_s *ctx, a_float_t fdb, a_float_t ec, a_float_t e, unsigned int i);
void a_pid_expert_outp_(a_pid_expert_s *const ctx, a_float_t const fdb, a_float_t const ec, a_float_t const e, unsigned int const i)
{
    A_PID_EXPERT_OUT_(.p[i]);
}

a_float_t a_pid_expert_outf(a_pid_expert_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t const e = set - fdb;
    a_pid_expert_outf_(ctx, fdb, e - ctx->pid.err.f, e);
    return ctx->pid.out.f;
}

a_float_t const *a_pid_expert_outp(a_pid_expert_s *const ctx, a_float_t const *const set, a_float_t const *const fdb)
{
    for (unsigned int i = 0; i != ctx->pid.chan; ++i)
    {
        a_float_t const e = set[i] - fdb[i];
        a_pid_expert_outp_(ctx, fdb[i], e - ctx->pid.err.p[i], e, i);
    }
    return ctx->pid.out.p;
}

a_float_t const *a_pid_expert_iter(a_pid_expert_s *const ctx, a_float_t const *const set, a_float_t const *const fdb)
{
    if (ctx->pid.chan)
    {
        return a_pid_expert_outp(ctx, set, fdb);
    }
    a_pid_expert_outf(ctx, *set, *fdb);
    return &ctx->pid.out.f;
}
