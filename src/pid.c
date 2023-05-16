#define LIBA_PID_C
#include "pid.h"

a_void_t a_pid_set_dt(a_pid_s *const ctx, a_real_t const dt)
{
    a_real_t const t = dt / ctx->dt;
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

a_pid_s *a_pid_pos(a_pid_s *const ctx, a_real_t const max)
{
    ctx->summax = (max > 0) ? max : -max;
    if (ctx->outmax < ctx->summax)
    {
        ctx->summax = ctx->outmax;
    }
    a_pid_set_mode(ctx, A_PID_POS);
    return ctx;
}

a_pid_s *a_pid_kpid(a_pid_s *const ctx, a_real_t const kp, a_real_t const ki, a_real_t const kd)
{
    ctx->kp = kp;
    ctx->ki = ki * ctx->dt;
    ctx->kd = kd / ctx->dt;
    return ctx;
}

a_pid_s *a_pid_chan(a_pid_s *const ctx, a_uint_t const num, a_real_t *const out, a_real_t *const fdb, a_real_t *const sum, a_real_t *const ec, a_real_t *const e)
{
    if (num > 1)
    {
        a_pid_set_num(ctx, num);
        ctx->out.p = out;
        ctx->fdb.p = fdb;
        ctx->sum.p = sum;
        ctx->ec.p = ec;
        ctx->e.p = e;
    }
    else
    {
        a_pid_set_num(ctx, 0);
    }
    return a_pid_zero(ctx);
}

a_pid_s *a_pid_init(a_pid_s *const ctx, a_real_t const dt, a_real_t const min, a_real_t const max)
{
    ctx->reg = A_PID_OFF;
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
    a_uint_t const num = a_pid_num(ctx);
    if (num > 1)
    {
        for (a_uint_t i = 0; i != num; ++i)
        {
            ctx->sum.p[i] = 0;
            ctx->out.p[i] = 0;
            ctx->fdb.p[i] = 0;
            ctx->ec.p[i] = 0;
            ctx->e.p[i] = 0;
        }
    }
    else
    {
        ctx->out.f = 0;
        ctx->sum.f = 0;
        ctx->fdb.f = 0;
        ctx->ec.f = 0;
        ctx->e.f = 0;
    }
    return ctx;
}

a_real_t a_pid_outf_(a_pid_s *const ctx, a_uint_t const mode, a_real_t const set, a_real_t const fdb, a_real_t const ec, a_real_t const e)
{
    /* calculation */
    switch (mode)
    {
    case A_PID_INC:
    {
        /* K_p[e(k)-e(k-1)]+K_i[e(k)]+K_d[ec(k)-ec(k-1)] */
        ctx->sum.f += ctx->kp * ec + ctx->ki * e + ctx->kd * (ec - ctx->ec.f);
        ctx->out.f = ctx->sum.f;
        break;
    }
    case A_PID_POS:
    {
        a_real_t const sum = ctx->ki * e;
        /* when the limit of integration is exceeded or */
        /* the direction of integration is the same, the integration stops. */
        if ((-ctx->summax < ctx->sum.f && ctx->sum.f < ctx->summax) || ctx->sum.f * sum < 0)
        {
            /* sum = K_i[\sum^k_{i=0}e(i)] */
            ctx->sum.f += sum;
        }
        /* avoid derivative kick, fdb[k-1]-fdb[k] */
        /* out = K_p[e(k)]+sum+K_d[fdb(k-1)-fdb(k)] */
        ctx->out.f = ctx->kp * e + ctx->sum.f + ctx->kd * (ctx->fdb.f - fdb);
        break;
    }
    case A_PID_OFF:
    default:
        ctx->out.f = ctx->sum.f = set;
    }
    ctx->out.f = A_SAT(ctx->out.f, ctx->outmin, ctx->outmax);
    /* cache data */
    ctx->fdb.f = fdb;
    ctx->ec.f = ec;
    ctx->e.f = e;
    return ctx->out.f;
}

a_real_t a_pid_outp_(a_pid_s *const ctx, a_uint_t const mode, a_real_t const set, a_real_t const fdb, a_real_t const ec, a_real_t const e, a_uint_t const i)
{
    /* calculation */
    switch (mode)
    {
    case A_PID_INC:
    {
        /* K_p[e(k)-e(k-1)]+K_i[e(k)]+K_d[ec(k)-ec(k-1)] */
        ctx->sum.p[i] += ctx->kp * ec + ctx->ki * e + ctx->kd * (ec - ctx->ec.p[i]);
        ctx->out.p[i] = ctx->sum.p[i];
        break;
    }
    case A_PID_POS:
    {
        a_real_t const sum = ctx->ki * e;
        /* when the limit of integration is exceeded or */
        /* the direction of integration is the same, the integration stops. */
        if ((-ctx->summax < ctx->sum.p[i] && ctx->sum.p[i] < ctx->summax) || ctx->sum.p[i] * sum < 0)
        {
            /* sum = K_i[\sum^k_{i=0}e(i)] */
            ctx->sum.p[i] += sum;
        }
        /* avoid derivative kick, fdb[k-1]-fdb[k] */
        /* out = K_p[e(k)]+sum+K_d[fdb(k-1)-fdb(k)] */
        ctx->out.p[i] = ctx->kp * e + ctx->sum.p[i] + ctx->kd * (ctx->fdb.p[i] - fdb);
        break;
    }
    case A_PID_OFF:
    default:
        ctx->out.p[i] = ctx->sum.p[i] = set;
    }
    ctx->out.p[i] = A_SAT(ctx->out.p[i], ctx->outmin, ctx->outmax);
    /* cache data */
    ctx->fdb.p[i] = fdb;
    ctx->ec.p[i] = ec;
    ctx->e.p[i] = e;
    return ctx->out.p[i];
}

a_real_t a_pid_outf(a_pid_s *const ctx, a_real_t const set, a_real_t const fdb)
{
    a_real_t const e = set - fdb;
    a_real_t const ec = e - ctx->e.f;
    return a_pid_outf_(ctx, a_pid_mode(ctx), set, fdb, ec, e);
}

a_real_t const *a_pid_outp(a_pid_s *const ctx, a_real_t const *const set, a_real_t const *const fdb)
{
    a_uint_t const num = a_pid_num(ctx);
    a_uint_t const mode = a_pid_mode(ctx);
    for (a_uint_t i = 0; i != num; ++i)
    {
        a_real_t const e = set[i] - fdb[i];
        a_real_t const ec = e - ctx->e.p[i];
        a_pid_outp_(ctx, mode, set[i], fdb[i], ec, e, i);
    }
    return ctx->out.p;
}
