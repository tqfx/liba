#include "a/traptraj.h"
#include "a/math.h"

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

a_float a_traptraj_gen(a_traptraj *ctx, a_float qm, a_float vm, a_float ac, a_float de, a_float vs, a_float ve)
{
    a_bool const reversed = qm < 0;
    a_float const _2q = 2 * qm;
    a_float vs2, ve2, vc2, vm2;
    if (vm < 0) { vm = -vm; }
    if (vs > vm) { vs = vm; }
    else if (vs < -vm) { vs = -vm; }
    if (ve > vm) { ve = vm; }
    else if (ve < -vm) { ve = -vm; }
    vm2 = vm * vm;
    vs2 = vs * vs;
    ve2 = ve * ve;
    ctx->vs = vs;
    ctx->ve = ve;
    ctx->ac = ac;
    ctx->de = de;
    if (ac != de)
    {
        vc2 = (ve2 * ac - vs2 * de - _2q * ac * de) / (ac - de);
        if (vc2 <= 0) { return 0; }
    }
    else if (ac == 0) { return 0; }
    else { vc2 = vm2; }
    if (vc2 > vm2) /* acceleration, constant velocity, deceleration */
    {
        ctx->vc = reversed ? -vm : vm;
        ctx->ta = (ctx->vc - vs) / ac;
        ctx->td = (ve - ctx->vc) / de;
        ctx->qa = ctx->vs * ctx->ta + A_FLOAT_C(0.5) * ac * ctx->ta * ctx->ta;
        ctx->qd = ctx->vc * ctx->td + A_FLOAT_C(0.5) * de * ctx->td * ctx->td;
        ctx->qc = qm - ctx->qa - ctx->qd;
        ctx->tc = ctx->qc / ctx->vc;
    }
    else if (vc2 > vs2 && vc2 <= ve2) /* acceleration */
    {
        ve2 = vs2 + _2q * ac;
        if (ve2 < 0) { return 0; }
        ctx->ve = a_float_sqrt(ve2);
        if (reversed) { ctx->ve = -ctx->ve; }
        ctx->vc = ctx->ve;
        ctx->ta = (ctx->ve - vs) / ac;
        ctx->tc = 0;
        ctx->td = 0;
        ctx->qa = ctx->vs * ctx->ta + A_FLOAT_C(0.5) * ac * ctx->ta * ctx->ta;
        ctx->qc = 0;
        ctx->qd = 0;
    }
    else if (vc2 <= vs2 && vc2 > ve2) /* deceleration */
    {
        ve2 = vs2 + _2q * de;
        if (ve2 < 0) { return 0; }
        ctx->ve = a_float_sqrt(ve2);
        if (reversed) { ctx->ve = -ctx->ve; }
        ctx->vc = ctx->vs;
        ctx->ta = 0;
        ctx->tc = 0;
        ctx->td = (ctx->ve - vs) / de;
        ctx->qa = 0;
        ctx->qc = 0;
        ctx->qd = ctx->vc * ctx->td + A_FLOAT_C(0.5) * de * ctx->td * ctx->td;
    }
    else /* acceleration, deceleration */
    {
        ctx->vc = a_float_sqrt(vc2);
        if (reversed) { ctx->vc = -ctx->vc; }
        ctx->ta = (ctx->vc - vs) / ac;
        ctx->tc = 0;
        ctx->td = (ve - ctx->vc) / de;
        ctx->qa = ctx->vs * ctx->ta + A_FLOAT_C(0.5) * ac * ctx->ta * ctx->ta;
        ctx->qc = 0;
        ctx->qd = ctx->vc * ctx->td + A_FLOAT_C(0.5) * de * ctx->td * ctx->td;
    }
    return ctx->ta + ctx->tc + ctx->td;
}

a_float a_traptraj_pos(a_traptraj const *ctx, a_float dt)
{
    a_float tc;
    if (dt < 0)
    {
        return 0;
    }
    else if (dt < ctx->ta) /* initial blend */
    {
        return ctx->vs * dt + A_FLOAT_C(0.5) * ctx->ac * dt * dt;
    }
    tc = ctx->ta + ctx->tc;
    if (dt < tc) /* linear motion */
    {
        return ctx->qa + ctx->vc * (dt - ctx->ta);
    }
    else if (dt < tc + ctx->td) /* final blend */
    {
        dt -= tc;
        return ctx->qa + ctx->qc + ctx->vc * dt + A_FLOAT_C(0.5) * ctx->de * dt * dt;
    }
    else
    {
        return ctx->qa + ctx->qc + ctx->qd;
    }
}

a_float a_traptraj_vel(a_traptraj const *ctx, a_float dt)
{
    a_float tc;
    if (dt < 0)
    {
        return ctx->vs;
    }
    else if (dt < ctx->ta) /* initial blend */
    {
        return ctx->vs + ctx->ac * dt;
    }
    tc = ctx->ta + ctx->tc;
    if (dt < tc) /* linear motion */
    {
        return ctx->vc;
    }
    else if (dt < tc + ctx->td) /* final blend */
    {
        return ctx->vc + ctx->de * (dt - tc);
    }
    else
    {
        return ctx->ve;
    }
}

a_float a_traptraj_acc(a_traptraj const *ctx, a_float dt)
{
    a_float tc;
    if (dt >= 0 && dt < ctx->ta) /* initial blend */
    {
        return ctx->ac;
    }
    tc = ctx->ta + ctx->tc;
    if (dt >= tc && dt < tc + ctx->td) /* final blend */
    {
        return ctx->de;
    }
    else /* linear motion */
    {
        return 0;
    }
}
