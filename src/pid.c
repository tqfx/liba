#define LIBA_PID_C
#include "pid.h"

void a_pid_set_dt(a_pid_s *const ctx, a_float_t const dt)
{
    a_float_t const t = dt / ctx->dt;
    ctx->ki *= t;
    ctx->kd /= t;
    ctx->dt = dt;
}

a_pid_s *a_pid_off(a_pid_s *const ctx)
{
    a_pid_set_mode(ctx, A_PID_OFF);
    return ctx;
}

a_pid_s *a_pid_inc(a_pid_s *const ctx)
{
    a_pid_set_mode(ctx, A_PID_INC);
    return ctx;
}

a_pid_s *a_pid_pos(a_pid_s *const ctx, a_float_t const max)
{
    ctx->summax = (max > 0) ? max : -max;
    if (ctx->outmax < ctx->summax)
    {
        ctx->summax = ctx->outmax;
    }
    a_pid_set_mode(ctx, A_PID_POS);
    return ctx;
}

a_pid_s *a_pid_kpid(a_pid_s *const ctx, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    ctx->kp = kp;
    ctx->ki = ki * ctx->dt;
    ctx->kd = kd / ctx->dt;
    return ctx;
}

a_pid_s *a_pid_chan(a_pid_s *const ctx, unsigned int const num, a_float_t *const out, a_float_t *const fdb, a_float_t *const tmp, a_float_t *const err)
{
    if (num > 1)
    {
        a_pid_set_num(ctx, num);
        ctx->out.p = out;
        ctx->fdb.p = fdb;
        ctx->tmp.p = tmp;
        ctx->err.p = err;
    }
    else
    {
        a_pid_set_num(ctx, 0);
    }
    return a_pid_zero(ctx);
}

a_pid_s *a_pid_init(a_pid_s *const ctx, a_float_t const dt, a_float_t const min, a_float_t const max)
{
    ctx->reg = A_PID_INC;
    ctx->outmin = min;
    ctx->outmax = max;
    ctx->summax = 0;
    ctx->num = 0;
    ctx->dt = dt;
    ctx->kp = 0;
    ctx->ki = 0;
    ctx->kd = 0;
    return a_pid_zero(ctx);
}

a_pid_s *a_pid_exit(a_pid_s *const ctx) { return a_pid_zero(ctx); }

a_pid_s *a_pid_zero(a_pid_s *const ctx)
{
    unsigned int const num = a_pid_num(ctx);
    if (num > 1)
    {
        for (unsigned int i = 0; i != num; ++i)
        {
            ctx->out.p[i] = 0;
            ctx->fdb.p[i] = 0;
            ctx->tmp.p[i] = 0;
            ctx->err.p[i] = 0;
        }
    }
    else
    {
        ctx->out.f = 0;
        ctx->fdb.f = 0;
        ctx->tmp.f = 0;
        ctx->err.f = 0;
    }
    return ctx;
}

a_float_t a_pid_outf_(a_pid_s *const ctx, unsigned int const mode, a_float_t const set, a_float_t const fdb, a_float_t const ec, a_float_t const e)
{
    /* calculation */
    switch (mode)
    {
    case A_PID_INC:
    {
        a_float_t tmp = ctx->fdb.f - fdb;
        ctx->out.f += ctx->kp * ec + ctx->ki * e + ctx->kd * (tmp - ctx->tmp.f);
        ctx->tmp.f = tmp;
        break;
    }
    case A_PID_POS:
    {
        a_float_t const sum = ctx->ki * e;
        /* when the limit of integration is exceeded or */
        /* the direction of integration is the same, the integration stops. */
        if ((-ctx->summax < ctx->tmp.f && ctx->tmp.f < ctx->summax) || ctx->tmp.f * sum < 0)
        {
            ctx->tmp.f += sum; /* sum = K_i[\sum^k_{i=0}e(i)] */
        }
        /* avoid derivative kick, fdb[k-1]-fdb[k] */
        /* out = K_p[e(k)]+sum+K_d[fdb(k-1)-fdb(k)] */
        ctx->out.f = ctx->kp * e + ctx->tmp.f + ctx->kd * (ctx->fdb.f - fdb);
        break;
    }
    case A_PID_OFF:
    default:
        ctx->out.f = set;
        ctx->tmp.f = 0;
    }
    ctx->out.f = A_SAT(ctx->out.f, ctx->outmin, ctx->outmax);
    ctx->fdb.f = fdb;
    ctx->err.f = e;
    return ctx->out.f;
}

a_float_t a_pid_outp_(a_pid_s *const ctx, unsigned int const mode, a_float_t const set, a_float_t const fdb, a_float_t const ec, a_float_t const e, unsigned int const i)
{
    /* calculation */
    switch (mode)
    {
    case A_PID_INC:
    {
        a_float_t tmp = ctx->fdb.p[i] - fdb;
        ctx->out.p[i] += ctx->kp * ec + ctx->ki * e + ctx->kd * (tmp - ctx->tmp.p[i]);
        ctx->tmp.p[i] = tmp;
        break;
    }
    case A_PID_POS:
    {
        a_float_t const sum = ctx->ki * e;
        /* when the limit of integration is exceeded or */
        /* the direction of integration is the same, the integration stops. */
        if ((-ctx->summax < ctx->tmp.p[i] && ctx->tmp.p[i] < ctx->summax) || ctx->tmp.p[i] * sum < 0)
        {
            ctx->tmp.p[i] += sum; /* sum = K_i[\sum^k_{i=0}e(i)] */
        }
        /* avoid derivative kick, fdb[k-1]-fdb[k] */
        /* out = K_p[e(k)]+sum+K_d[fdb(k-1)-fdb(k)] */
        ctx->out.p[i] = ctx->kp * e + ctx->tmp.p[i] + ctx->kd * (ctx->fdb.p[i] - fdb);
        break;
    }
    case A_PID_OFF:
    default:
        ctx->out.p[i] = set;
        ctx->tmp.p[i] = 0;
    }
    ctx->out.p[i] = A_SAT(ctx->out.p[i], ctx->outmin, ctx->outmax);
    ctx->fdb.p[i] = fdb;
    ctx->err.p[i] = e;
    return ctx->out.p[i];
}

a_float_t a_pid_outf(a_pid_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t const e = set - fdb;
    a_float_t const ec = e - ctx->err.f;
    return a_pid_outf_(ctx, a_pid_mode(ctx), set, fdb, ec, e);
}

a_float_t const *a_pid_outp(a_pid_s *const ctx, a_float_t const *const set, a_float_t const *const fdb)
{
    unsigned int const num = a_pid_num(ctx);
    unsigned int const mode = a_pid_mode(ctx);
    for (unsigned int i = 0; i != num; ++i)
    {
        a_float_t const e = set[i] - fdb[i];
        a_float_t const ec = e - ctx->err.p[i];
        a_pid_outp_(ctx, mode, set[i], fdb[i], ec, e, i);
    }
    return ctx->out.p;
}
