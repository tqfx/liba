#include "a/pid.h"

void a_pid_set_kpid(a_pid *ctx, a_real kp, a_real ki, a_real kd)
{
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
}

A_HIDDEN a_real a_pid_run_(a_pid *ctx, a_real set, a_real fdb, a_real err);
a_real a_pid_run(a_pid *ctx, a_real set, a_real fdb)
{
    return a_pid_run_(ctx, set, fdb, set - fdb);
}
a_real a_pid_run_(a_pid *ctx, a_real set, a_real fdb, a_real err)
{
    a_real const var = ctx->fdb - fdb;
    ctx->out = A_SAT(set, ctx->outmin, ctx->outmax);
    ctx->var = var;
    ctx->fdb = fdb;
    ctx->err = err;
    return ctx->out;
}

A_HIDDEN a_real a_pid_pos_(a_pid *ctx, a_real fdb, a_real err);
a_real a_pid_pos(a_pid *ctx, a_real set, a_real fdb)
{
    return a_pid_pos_(ctx, fdb, set - fdb);
}
a_real a_pid_pos_(a_pid *ctx, a_real fdb, a_real err)
{
    a_real const var = ctx->fdb - fdb;
    /* When the limit of integration is exceeded or the direction of integration is the same, the integration stops. */
    if ((ctx->sum > ctx->summin && ctx->sum < ctx->summax) || ctx->sum * err < 0)
    {
#if 1
        ctx->sum += ctx->ki * err; /* sum = K_i[\sum^k_{i=0}err(i)] */
#else
        ctx->sum += ctx->ki * (err + ctx->err) * A_REAL_C(0.5);
#endif
    }
    /* Avoid derivative kick, fdb[k-1]-fdb[k]. out = K_p[err(k)]+sum+K_d[fdb(k-1)-fdb(k)]. */
    ctx->out = ctx->kp * err + ctx->sum + ctx->kd * var;
    ctx->out = A_SAT(ctx->out, ctx->outmin, ctx->outmax);
    ctx->var = var;
    ctx->fdb = fdb;
    ctx->err = err;
    return ctx->out;
}

A_HIDDEN a_real a_pid_inc_(a_pid *ctx, a_real fdb, a_real err);
a_real a_pid_inc(a_pid *ctx, a_real set, a_real fdb)
{
    return a_pid_inc_(ctx, fdb, set - fdb);
}
a_real a_pid_inc_(a_pid *ctx, a_real fdb, a_real err)
{
    a_real const var = ctx->fdb - fdb;
    ctx->out += ctx->kp * (err - ctx->err) + ctx->ki * err + ctx->kd * (var - ctx->var);
    ctx->out = A_SAT(ctx->out, ctx->outmin, ctx->outmax);
    ctx->var = var;
    ctx->fdb = fdb;
    ctx->err = err;
    return ctx->out;
}

void a_pid_zero(a_pid *ctx)
{
    ctx->sum = 0;
    ctx->out = 0;
    ctx->var = 0;
    ctx->fdb = 0;
    ctx->err = 0;
}
