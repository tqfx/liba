#include "a/pid_neuro.h"

void a_pid_neuro_set_kpid(a_pid_neuro *ctx, a_real k, a_real kp, a_real ki, a_real kd)
{
    a_pid_set_kpid(&ctx->pid, kp, ki, kd);
    ctx->k = k;
}

void a_pid_neuro_set_wpid(a_pid_neuro *ctx, a_real wp, a_real wi, a_real wd)
{
    ctx->wp = wp;
    ctx->wi = wi;
    ctx->wd = wd;
}

A_HIDDEN a_real a_pid_neuro_run_(a_pid_neuro *ctx, a_real set, a_real fdb, a_real err, a_real ec);
a_real a_pid_neuro_run(a_pid_neuro *ctx, a_real set, a_real fdb)
{
    a_real const err = set - fdb;
    return a_pid_neuro_run_(ctx, set, fdb, err, err - ctx->pid.err);
}
A_HIDDEN a_real a_pid_run_(a_pid *ctx, a_real set, a_real fdb, a_real err);
a_real a_pid_neuro_run_(a_pid_neuro *ctx, a_real set, a_real fdb, a_real err, a_real ec)
{
    a_pid_run_(&ctx->pid, set, fdb, err);
    ctx->ec = ec;
    return ctx->pid.out;
}

A_HIDDEN a_real a_pid_neuro_inc_(a_pid_neuro *ctx, a_real fdb, a_real err, a_real ec);
a_real a_pid_neuro_inc(a_pid_neuro *ctx, a_real set, a_real fdb)
{
    a_real const err = set - fdb;
    return a_pid_neuro_inc_(ctx, fdb, err, err - ctx->pid.err);
}
a_real a_pid_neuro_inc_(a_pid_neuro *ctx, a_real fdb, a_real err, a_real ec)
{
    a_real const var = ec - ctx->ec;
    a_real out = err * ctx->pid.out;
    ctx->wp += ctx->pid.kp * out * ctx->ec;
    ctx->wi += ctx->pid.ki * out * ctx->pid.err;
    ctx->wd += ctx->pid.kd * out * ctx->pid.var;
    out = A_ABS(ctx->wp) + A_ABS(ctx->wi) + A_ABS(ctx->wd);
    out = ctx->k * (ctx->wp * ec + ctx->wi * err + ctx->wd * var) / out;
    ctx->pid.out = A_SAT(out, ctx->pid.outmin, ctx->pid.outmax);
    ctx->pid.var = var;
    ctx->pid.fdb = fdb;
    ctx->pid.err = err;
    ctx->ec = ec;
    return ctx->pid.out;
}

void a_pid_neuro_zero(a_pid_neuro *ctx)
{
    a_pid_zero(&ctx->pid);
    ctx->ec = 0;
}
