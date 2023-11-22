#include "expert.h"
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

void a_pid_expert_zero(a_pid_expert_s *const ctx)
{
    a_pid_zero(&ctx->pid);
    ctx->ec = 0;
}

void a_pid_expert_init(a_pid_expert_s *const ctx)
{
    a_pid_expert_zero(ctx);
}

void a_pid_expert_kpid(a_pid_expert_s *const ctx, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    a_pid_kpid(&ctx->pid, kp, ki, kd);
}

a_float_t a_pid_expert_iter(a_pid_expert_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t out = 0;
    a_float_t const err = set - fdb;
    a_float_t const abs = A_ABS(err);
    a_float_t const var = ctx->pid.fdb - fdb;
    a_float_t const ec = err - ctx->pid.err;

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
        if (abs > ctx->max2)
        {
            out *= ctx->gain;
        }
    }
    else if (ec * ctx->ec < 0 && err != 0)
    {
        out = ctx->pid.kp * ctx->pid.err;
        if (abs > ctx->max2)
        {
            out *= ctx->gain;
        }
        else
        {
            out *= ctx->loss;
        }
    }

    if (abs < ctx->epsilon)
    {
        out = ctx->pid.kp * ec + ctx->pid.ki * err;
    }

out:
    ctx->pid.out = A_SAT(out, ctx->pid.outmin, ctx->pid.outmax);
    ctx->pid.fdb = fdb;
    ctx->pid.var = var;
    ctx->pid.err = err;
    ctx->ec = ec;
    return ctx->pid.out;
}
