#include "pid_neuron.h"

a_pid_neuron_s *a_pid_neuron_init(a_pid_neuron_s *const ctx, unsigned int const num)
{
    ctx->pid.chan = num;
    return a_pid_neuron_zero(ctx);
}

a_pid_neuron_s *a_pid_neuron_chan(a_pid_neuron_s *const ctx,
                                  unsigned int const num, a_float_t *const out, a_float_t *const fdb,
                                  a_float_t *const tmp, a_float_t *const err, a_float_t *const ec,
                                  a_float_t *const wp, a_float_t *const wi, a_float_t *const wd)
{
    if (num > 1)
    {
        ctx->pid.chan = num;
        ctx->pid.out.p = out;
        ctx->pid.fdb.p = fdb;
        ctx->pid.tmp.p = tmp;
        ctx->pid.err.p = err;
        ctx->ec.p = ec;
        ctx->wp.p = wp;
        ctx->wi.p = wi;
        ctx->wd.p = wd;
    }
    else
    {
        ctx->pid.chan = 0;
    }
    return a_pid_neuron_zero(ctx);
}

a_pid_neuron_s *a_pid_neuron_kpid(a_pid_neuron_s *const ctx, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    ctx->pid.kp = kp;
    ctx->pid.ki = ki;
    ctx->pid.kd = kd;
    return ctx;
}

a_pid_neuron_s *a_pid_neuron_zero(a_pid_neuron_s *const ctx)
{
    if (ctx->pid.chan > 1)
    {
        for (unsigned int i = 0; i != ctx->pid.chan; ++i)
        {
            a_pid_zerop(&ctx->pid, i);
            ctx->ec.p[i] = 0;
        }
    }
    else
    {
        a_pid_zerof(&ctx->pid);
        ctx->ec.f = 0;
    }
    return ctx;
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
    out = ctx->ko * (ctx->wp _ * ec + ctx->wi _ * e + ctx->wd _ * tmp) / abs;     \
    ctx->pid.out _ = A_SAT(out, ctx->pid.outmin, ctx->pid.outmax);                \
    ctx->pid.fdb _ = fdb;                                                         \
    ctx->pid.tmp _ = tmp;                                                         \
    ctx->pid.err _ = e;                                                           \
    ctx->ec _ = ec
    A_PID_NEURON_OUT_(.f);
}

void a_pid_neuron_outp_(a_pid_neuron_s *const ctx, a_float_t const fdb, a_float_t const ec, a_float_t const e, unsigned int const i)
{
    A_PID_NEURON_OUT_(.p[i]);
}

a_float_t a_pid_neuron_outf(a_pid_neuron_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t const e = set - fdb;
    a_pid_neuron_outf_(ctx, fdb, e - ctx->pid.err.f, e);
    return ctx->pid.out.f;
}

a_float_t const *a_pid_neuron_outp(a_pid_neuron_s *const ctx, a_float_t const *const set, a_float_t const *const fdb)
{
    for (unsigned int i = 0; i != ctx->pid.chan; ++i)
    {
        a_float_t const e = set[i] - fdb[i];
        a_pid_neuron_outp_(ctx, fdb[i], e - ctx->pid.err.p[i], e, i);
    }
    return ctx->pid.out.p;
}
