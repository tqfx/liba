#define LIBA_PID_EXPERT_C
#include "pid_expert.h"
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

a_pid_expert_s *a_pid_expert_kpid(a_pid_expert_s *const ctx, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    a_pid_kpid(&ctx->pid, kp, ki, kd);
    return ctx;
}

a_pid_expert_s *a_pid_expert_chan(a_pid_expert_s *const ctx, unsigned int const num, a_float_t *const out, a_float_t *const fdb,
                                  a_float_t *const tmp, a_float_t *const err, a_float_t *const ec)
{
    if (num > 1)
    {
        a_pid_set_num(&ctx->pid, num);
        a_pid_chan_(&ctx->pid, out, fdb, tmp, err);
        ctx->ec.p = ec;
    }
    else
    {
        a_pid_set_num(&ctx->pid, 0);
    }
    a_pid_expert_zero_(ctx, num);
    return ctx;
}

a_pid_expert_s *a_pid_expert_init(a_pid_expert_s *const ctx, a_float_t const dt, a_float_t const min, a_float_t const max,
                                  a_float_t const max1, a_float_t const gain, a_float_t const max2, a_float_t const loss,
                                  a_float_t const epsilon)
{
    a_pid_init(&ctx->pid, dt, min, max);
    ctx->epsilon = epsilon;
    ctx->max1 = max1;
    ctx->gain = gain;
    ctx->max2 = max2;
    ctx->loss = loss;
    ctx->ec.f = 0;
    return ctx;
}

void a_pid_expert_zero_(a_pid_expert_s *const ctx, unsigned int const num)
{
    if (num > 1)
    {
        for (unsigned int i = 0; i != num; ++i)
        {
            a_pid_zerop(&ctx->pid, i);
            ctx->ec.p[i] = 0;
        }
    }
    else
    {
        a_pid_zerof(&ctx->pid);
        ctx->ec.f = 0;
    }
}

a_pid_expert_s *a_pid_expert_zero(a_pid_expert_s *const ctx)
{
    a_pid_expert_zero_(ctx, a_pid_num(&ctx->pid));
    return ctx;
}

#define A_PID_EXPERT_OUT_(_)                                                             \
    a_float_t out = 0;                                                                   \
    a_float_t abs = A_ABS(e);                                                            \
    a_float_t tmp = ctx->pid.fdb _ - fdb;                                                \
                                                                                         \
    if (-ctx->max1 > e)                                                                  \
    {                                                                                    \
        out = ctx->pid.outmin;                                                           \
    }                                                                                    \
    else if (e > ctx->max1)                                                              \
    {                                                                                    \
        out = ctx->pid.outmax;                                                           \
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
                                                                                         \
    ctx->pid.out _ += out;                                                               \
    ctx->pid.out _ = A_SAT(ctx->pid.out _, ctx->pid.outmin, ctx->pid.outmax);            \
    ctx->pid.fdb _ = fdb;                                                                \
    ctx->pid.tmp _ = tmp;                                                                \
    ctx->pid.err _ = e;                                                                  \
    ctx->ec _ = ec

void a_pid_expert_outf_(a_pid_expert_s *const ctx, a_float_t const fdb, a_float_t const ec, a_float_t const e)
{
    A_PID_EXPERT_OUT_(.f);
}

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
    unsigned int const num = a_pid_num(&ctx->pid);
    for (unsigned int i = 0; i != num; ++i)
    {
        a_float_t const e = set[i] - fdb[i];
        a_pid_expert_outp_(ctx, fdb[i], e - ctx->pid.err.p[i], e, i);
    }
    return ctx->pid.out.p;
}
