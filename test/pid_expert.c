#include "pid_expert.h"
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

void a_pid_expert_kpid(a_pid_expert *ctx, a_float kp, a_float ki, a_float kd)
{
    a_pid_kpid(&ctx->pid, kp, ki, kd);
}

a_float a_pid_expert_iter(a_pid_expert *ctx, a_float set, a_float fdb)
{
    a_float out = 0;
    a_float const err = set - fdb;
    a_float const abs = A_ABS(err);
    a_float const var = ctx->pid.fdb - fdb;
    a_float const ec = err - ctx->pid.err;

    if (-ctx->max1 > err)
    {
        out = -ctx->outmax;
        goto out;
    }
    else if (err > ctx->max1)
    {
        out = ctx->outmax;
        goto out;
    }

    if (err * ec > 0 || ec == 0)
    {
        out = ctx->pid.kp * ec + ctx->pid.ki * err + ctx->pid.kd * (var - ctx->pid.var);
        if (abs > ctx->max2) { out *= ctx->gain; }
    }
    else if (ec * ctx->ec < 0 && err != 0)
    {
        out = ctx->pid.kp * ctx->pid.err;
        if (abs > ctx->max2) { out *= ctx->gain; }
        else { out *= ctx->loss; }
    }

    if (abs < ctx->epsilon) { out = ctx->pid.kp * ec + ctx->pid.ki * err; }

out:
    ctx->pid.out = A_SAT(out, ctx->pid.outmin, ctx->pid.outmax);
    ctx->pid.fdb = fdb;
    ctx->pid.var = var;
    ctx->pid.err = err;
    ctx->ec = ec;
    return ctx->pid.out;
}

void a_pid_expert_zero(a_pid_expert *ctx)
{
    a_pid_zero(&ctx->pid);
    ctx->ec = 0;
}
