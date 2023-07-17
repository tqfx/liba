#include "pid.h"

void a_pid_init(a_pid_s *const ctx, unsigned int const num)
{
    ctx->chan = num;
    a_pid_zero(ctx);
}

void a_pid_chan(a_pid_s *const ctx, unsigned int const num, a_float_t *const out, a_float_t *const fdb, a_float_t *const tmp, a_float_t *const err)
{
    ctx->chan = num;
    if (ctx->chan)
    {
        A_PID_CHAN(ctx);
    }
    a_pid_zero(ctx);
}

void a_pid_kpid(a_pid_s *const ctx, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
}

void a_pid_zero(a_pid_s *const ctx)
{
    if (ctx->chan)
    {
        for (unsigned int i = 0; i != ctx->chan; ++i)
        {
            A_PID_ZERO(ctx, .p[i]);
        }
    }
    else
    {
        A_PID_ZERO(ctx, .f);
    }
}

void a_pid_outf_(a_pid_s *const ctx, a_float_t const set, a_float_t const fdb, a_float_t const ec, a_float_t const e)
{
#define A_PID_OUT_(_)                                                                        \
    /* calculation */                                                                        \
    switch (ctx->mode)                                                                       \
    {                                                                                        \
    case A_PID_INC:                                                                          \
    {                                                                                        \
        a_float_t tmp = ctx->fdb _ - fdb;                                                    \
        ctx->out _ += ctx->kp * ec + ctx->ki * e + ctx->kd * (tmp - ctx->tmp _);             \
        ctx->tmp _ = tmp;                                                                    \
        break;                                                                               \
    }                                                                                        \
    case A_PID_POS:                                                                          \
    {                                                                                        \
        a_float_t const sum = ctx->ki * e;                                                   \
        /* when the limit of integration is exceeded or */                                   \
        /* the direction of integration is the same, the integration stops. */               \
        if ((-ctx->summax < ctx->tmp _ && ctx->tmp _ < ctx->summax) || ctx->tmp _ * sum < 0) \
        {                                                                                    \
            ctx->tmp _ += sum; /* sum = K_i[\sum^k_{i=0}e(i)] */                             \
        }                                                                                    \
        /* avoid derivative kick, fdb[k-1]-fdb[k] */                                         \
        /* out = K_p[e(k)]+sum+K_d[fdb(k-1)-fdb(k)] */                                       \
        ctx->out _ = ctx->kp * e + ctx->tmp _ + ctx->kd * (ctx->fdb _ - fdb);                \
        break;                                                                               \
    }                                                                                        \
    case A_PID_OFF:                                                                          \
    default:                                                                                 \
        ctx->out _ = set;                                                                    \
        ctx->tmp _ = 0;                                                                      \
    }                                                                                        \
    ctx->out _ = A_SAT(ctx->out _, ctx->outmin, ctx->outmax);                                \
    ctx->fdb _ = fdb;                                                                        \
    ctx->err _ = e
    A_PID_OUT_(.f);
}

void a_pid_outp_(a_pid_s const *const ctx, a_float_t const set, a_float_t const fdb, a_float_t const ec, a_float_t const e, unsigned int const i)
{
    A_PID_OUT_(.p[i]);
}

a_float_t a_pid_outf(a_pid_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t const e = set - fdb;
    a_pid_outf_(ctx, set, fdb, e - ctx->err.f, e);
    return ctx->out.f;
}

a_float_t const *a_pid_outp(a_pid_s const *const ctx, a_float_t const *const set, a_float_t const *const fdb)
{
    for (unsigned int i = 0; i != ctx->chan; ++i)
    {
        a_float_t const e = set[i] - fdb[i];
        a_pid_outp_(ctx, set[i], fdb[i], e - ctx->err.p[i], e, i);
    }
    return ctx->out.p;
}

a_float_t const *a_pid_iter(a_pid_s *const ctx, a_float_t const *const set, a_float_t const *const fdb)
{
    if (ctx->chan)
    {
        return a_pid_outp(ctx, set, fdb);
    }
    a_pid_outf(ctx, *set, *fdb);
    return &ctx->out.f;
}
