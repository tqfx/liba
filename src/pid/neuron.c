#include "a/pid/neuron.h"

void a_pid_neuron_zero(a_pid_neuron_s *const ctx)
{
    a_pid_zero(&ctx->pid);
    ctx->ec = 0;
}

void a_pid_neuron_init(a_pid_neuron_s *const ctx)
{
    a_pid_neuron_zero(ctx);
}

void a_pid_neuron_kpid(a_pid_neuron_s *const ctx, a_float_t const k, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    a_pid_kpid(&ctx->pid, kp, ki, kd);
    ctx->k = k;
}

void a_pid_neuron_wpid(a_pid_neuron_s *const ctx, a_float_t const wp, a_float_t const wi, a_float_t const wd)
{
    ctx->wp = wp;
    ctx->wi = wi;
    ctx->wd = wd;
}

A_HIDDEN a_float_t a_pid_off_(a_pid_s *ctx, a_float_t set, a_float_t fdb, a_float_t err);
A_HIDDEN a_float_t a_pid_neuron_off_(a_pid_neuron_s *ctx, a_float_t set, a_float_t fdb, a_float_t err, a_float_t ec);
a_float_t a_pid_neuron_off(a_pid_neuron_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t const err = set - fdb;
    return a_pid_neuron_off_(ctx, set, fdb, err, err - ctx->pid.err);
}
a_float_t a_pid_neuron_off_(a_pid_neuron_s *const ctx, a_float_t const set, a_float_t const fdb, a_float_t const err, a_float_t const ec)
{
    a_pid_off_(&ctx->pid, set, fdb, err);
    ctx->ec = ec;
    return ctx->pid.out;
}

A_HIDDEN a_float_t a_pid_neuron_inc_(a_pid_neuron_s *ctx, a_float_t fdb, a_float_t err, a_float_t ec);
a_float_t a_pid_neuron_inc(a_pid_neuron_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t const err = set - fdb;
    return a_pid_neuron_inc_(ctx, fdb, err, err - ctx->pid.err);
}
a_float_t a_pid_neuron_inc_(a_pid_neuron_s *const ctx, a_float_t const fdb, a_float_t const err, a_float_t const ec)
{
    a_float_t const var = ec - ctx->ec;
    a_float_t out = err * ctx->pid.out;
    ctx->wp += ctx->pid.kp * out * ctx->ec;
    ctx->wi += ctx->pid.ki * out * ctx->pid.err;
    ctx->wd += ctx->pid.kd * out * ctx->pid.var;
    a_float_t const abs = A_ABS(ctx->wp) + A_ABS(ctx->wi) + A_ABS(ctx->wd);
    out = ctx->k * (ctx->wp * ec + ctx->wi * err + ctx->wd * var) / abs;
    ctx->pid.out = A_SAT(out, ctx->pid.outmin, ctx->pid.outmax);
    ctx->pid.fdb = fdb;
    ctx->pid.var = var;
    ctx->pid.err = err;
    ctx->ec = ec;
    return ctx->pid.out;
}
