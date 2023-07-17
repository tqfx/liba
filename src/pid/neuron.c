#include "neuron.h"

void a_pid_neuron_init(a_pid_neuron_s *const ctx, unsigned int const num)
{
    ctx->pid.chan = num;
    a_pid_neuron_zero(ctx);
}

void a_pid_neuron_chan(a_pid_neuron_s *const ctx, unsigned int const num,
                       a_float_t *const out, a_float_t *const fdb, a_float_t *const tmp, a_float_t *const err,
                       a_float_t *const ec, a_float_t *const wp, a_float_t *const wi, a_float_t *const wd)
{
    ctx->pid.chan = num;
    if (ctx->pid.chan)
    {
        A_PID_CHAN(&ctx->pid);
        A_PID_NEURON_CHAN(ctx);
    }
    a_pid_neuron_zero(ctx);
}

void a_pid_neuron_kpid(a_pid_neuron_s *const ctx, a_float_t const k, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    a_pid_kpid(&ctx->pid, kp, ki, kd);
    ctx->k = k;
}

void a_pid_neuron_wpid(a_pid_neuron_s *const ctx, a_float_t const wp, a_float_t const wi, a_float_t const wd)
{
    if (ctx->pid.chan)
    {
        for (unsigned int i = 0; i != ctx->pid.chan; ++i)
        {
            ctx->wp.p[i] = wp;
            ctx->wi.p[i] = wi;
            ctx->wd.p[i] = wd;
        }
    }
    else
    {
        ctx->wp.f = wp;
        ctx->wi.f = wi;
        ctx->wd.f = wd;
    }
}

void a_pid_neuron_zero(a_pid_neuron_s *const ctx)
{
    if (ctx->pid.chan)
    {
        for (unsigned int i = 0; i != ctx->pid.chan; ++i)
        {
            A_PID_ZERO(&ctx->pid, .p[i]);
            A_PID_NEURON_ZERO(ctx, .p[i]);
        }
    }
    else
    {
        A_PID_ZERO(&ctx->pid, .f);
        A_PID_NEURON_ZERO(ctx, .f);
    }
}

void a_pid_neuron_outf_(a_pid_neuron_s *const ctx, a_float_t const fdb, a_float_t const ec, a_float_t const e)
{
#define A_PID_NEURON_OUT_(_)                                                      \
    a_float_t out = e * ctx->pid.out _;                                           \
    a_float_t const tmp = ec - ctx->ec _;                                         \
    ctx->wp _ += ctx->pid.kp * out * ctx->ec _;                                   \
    ctx->wi _ += ctx->pid.ki * out * ctx->pid.err _;                              \
    ctx->wd _ += ctx->pid.kd * out * ctx->pid.tmp _;                              \
    a_float_t const abs = A_ABS(ctx->wp _) + A_ABS(ctx->wi _) + A_ABS(ctx->wd _); \
    out = ctx->k * (ctx->wp _ * ec + ctx->wi _ * e + ctx->wd _ * tmp) / abs;      \
    ctx->pid.out _ = A_SAT(out, ctx->pid.outmin, ctx->pid.outmax);                \
    ctx->pid.fdb _ = fdb;                                                         \
    ctx->pid.tmp _ = tmp;                                                         \
    ctx->pid.err _ = e;                                                           \
    ctx->ec _ = ec
    A_PID_NEURON_OUT_(.f);
}

void a_pid_neuron_outp_(a_pid_neuron_s const *const ctx, a_float_t const fdb, a_float_t const ec, a_float_t const e, unsigned int const i)
{
    A_PID_NEURON_OUT_(.p[i]);
}

a_float_t a_pid_neuron_outf(a_pid_neuron_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t const e = set - fdb;
    a_pid_neuron_outf_(ctx, fdb, e - ctx->pid.err.f, e);
    return ctx->pid.out.f;
}

a_float_t const *a_pid_neuron_outp(a_pid_neuron_s const *const ctx, a_float_t const *const set, a_float_t const *const fdb)
{
    for (unsigned int i = 0; i != ctx->pid.chan; ++i)
    {
        a_float_t const e = set[i] - fdb[i];
        a_pid_neuron_outp_(ctx, fdb[i], e - ctx->pid.err.p[i], e, i);
    }
    return ctx->pid.out.p;
}

a_float_t const *a_pid_neuron_iter(a_pid_neuron_s *const ctx, a_float_t const *const set, a_float_t const *const fdb)
{
    if (ctx->pid.chan)
    {
        return a_pid_neuron_outp(ctx, set, fdb);
    }
    a_pid_neuron_outf(ctx, *set, *fdb);
    return &ctx->pid.out.f;
}
