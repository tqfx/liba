#include "a/pid.h"

void a_pid_zero(a_pid_s *const ctx)
{
    ctx->sum = 0;
    ctx->out = 0;
    ctx->fdb = 0;
    ctx->var = 0;
    ctx->err = 0;
}

void a_pid_init(a_pid_s *const ctx)
{
    a_pid_zero(ctx);
}

void a_pid_kpid(a_pid_s *const ctx, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
}

A_HIDDEN a_float_t a_pid_off_(a_pid_s *ctx, a_float_t set, a_float_t fdb, a_float_t err);
a_float_t a_pid_off(a_pid_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    return a_pid_off_(ctx, set, fdb, set - fdb);
}
a_float_t a_pid_off_(a_pid_s *const ctx, a_float_t const set, a_float_t const fdb, a_float_t const err)
{
    a_float_t const var = ctx->fdb - fdb;
    ctx->out = A_SAT(set, ctx->outmin, ctx->outmax);
    ctx->fdb = fdb;
    ctx->var = var;
    ctx->err = err;
    return ctx->out;
}

A_HIDDEN a_float_t a_pid_pos_(a_pid_s *ctx, a_float_t fdb, a_float_t err);
a_float_t a_pid_pos(a_pid_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    return a_pid_pos_(ctx, fdb, set - fdb);
}
a_float_t a_pid_pos_(a_pid_s *const ctx, a_float_t const fdb, a_float_t const err)
{
    a_float_t const var = ctx->fdb - fdb;
    // When the limit of integration is exceeded or the direction of integration is the same, the integration stops.
    if ((ctx->sum > ctx->summin && ctx->sum < ctx->summax) || ctx->sum * err < 0)
    {
        ctx->sum += ctx->ki * err; // sum = K_i[\sum^k_{i=0}err(i)]
    }
    // Avoid derivative kick, fdb[k-1]-fdb[k]. out = K_p[err(k)]+sum+K_d[fdb(k-1)-fdb(k)].
    ctx->out = ctx->kp * err + ctx->sum + ctx->kd * var;
    ctx->out = A_SAT(ctx->out, ctx->outmin, ctx->outmax);
    ctx->fdb = fdb;
    ctx->var = var;
    ctx->err = err;
    return ctx->out;
}

A_HIDDEN a_float_t a_pid_inc_(a_pid_s *ctx, a_float_t fdb, a_float_t err);
a_float_t a_pid_inc(a_pid_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    return a_pid_inc_(ctx, fdb, set - fdb);
}
a_float_t a_pid_inc_(a_pid_s *const ctx, a_float_t const fdb, a_float_t const err)
{
    a_float_t const var = ctx->fdb - fdb;
    ctx->out += ctx->kp * (err - ctx->err) + ctx->ki * err + ctx->kd * (var - ctx->var);
    ctx->out = A_SAT(ctx->out, ctx->outmin, ctx->outmax);
    ctx->fdb = fdb;
    ctx->var = var;
    ctx->err = err;
    return ctx->out;
}
