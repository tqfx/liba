#include "a/traptraj.h"
#include "a/math.h"

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

a_float a_traptraj_gen(a_traptraj *ctx, a_float qm, a_float vm, a_float ac, a_float de, a_float vs, a_float ve)
{
    a_float vs2, ve2, vc2;
    a_float const _2q = 2 * qm;
    a_bool const reversed = qm < 0;
    if (vm < 0) { vm = -vm; }
    if (vs > vm) { vs = vm; }
    else if (vs < -vm) { vs = -vm; }
    if (ve > vm) { ve = vm; }
    else if (ve < -vm) { ve = -vm; }
    if (ac == de) { return 0; }
    ctx->ac = ac;
    ctx->de = de;
    ctx->vs = vs;
    ctx->ve = ve;
    vs2 = vs * vs;
    ve2 = ve * ve;
    vc2 = (ve2 * ac - vs2 * de - _2q * ac * de) / (ac - de);
    if (vc2 <= 0) { return 0; }
    if (vc2 > vm * vm) /* acceleration, constant velocity, deceleration */
    {
        ctx->vc = reversed ? -vm : vm;
        ctx->t1 = (ctx->vc - vs) / ac;
        ctx->t = (ve - ctx->vc) / de;
        ctx->q1 = ctx->vs * ctx->t1 + A_FLOAT_C(0.5) * ac * ctx->t1 * ctx->t1;
        ctx->q = ctx->vc * ctx->t + A_FLOAT_C(0.5) * de * ctx->t * ctx->t;
        ctx->q2 = qm - ctx->q;
        ctx->t2 = (ctx->q2 - ctx->q1) / ctx->vc;
        ctx->t2 += ctx->t1;
        ctx->t += ctx->t2;
        ctx->q = qm;
    }
    else if (vc2 > vs2 && vc2 <= ve2) /* acceleration */
    {
        ve2 = vs2 + _2q * ac;
        if (ve2 < 0) { return 0; }
        ctx->ve = a_float_sqrt(ve2);
        if (reversed) { ctx->ve = -ctx->ve; }
        ctx->vc = ctx->ve;
        ctx->t1 = (ctx->ve - vs) / ac;
        ctx->t2 = ctx->t1;
        ctx->t = ctx->t1;
        ctx->q1 = ctx->vs * ctx->t1 + A_FLOAT_C(0.5) * ac * ctx->t1 * ctx->t1;
        ctx->q2 = qm;
        ctx->q = qm;
    }
    else if (vc2 <= vs2 && vc2 > ve2) /* deceleration */
    {
        ve2 = vs2 + _2q * de;
        if (ve2 < 0) { return 0; }
        ctx->ve = a_float_sqrt(ve2);
        if (reversed) { ctx->ve = -ctx->ve; }
        ctx->vc = ctx->vs;
        ctx->t1 = 0;
        ctx->t2 = 0;
        ctx->t = (ctx->ve - vs) / de;
        ctx->q1 = 0;
        ctx->q2 = 0;
        ctx->q = ctx->vc * ctx->t + A_FLOAT_C(0.5) * de * ctx->t * ctx->t;
    }
    else /* acceleration, deceleration */
    {
        ctx->vc = a_float_sqrt(vc2);
        if (reversed) { ctx->vc = -ctx->vc; }
        ctx->t1 = (ctx->vc - vs) / ac;
        ctx->t2 = ctx->t1;
        ctx->t = (ve - ctx->vc) / de;
        ctx->q1 = ctx->vs * ctx->t1 + A_FLOAT_C(0.5) * ac * ctx->t1 * ctx->t1;
        ctx->q2 = ctx->q1;
        ctx->q = ctx->vc * ctx->t + A_FLOAT_C(0.5) * de * ctx->t * ctx->t;
        ctx->t += ctx->t1;
        ctx->q += ctx->q1;
    }
    return ctx->t;
}

a_float a_traptraj_pos(a_traptraj const *ctx, a_float dt)
{
    if (dt >= ctx->t1)
    {
        if (dt < ctx->t2) /* linear motion */
        {
            return ctx->q1 + ctx->vc * (dt - ctx->t1);
        }
        if (dt < ctx->t) /* final blend */
        {
            dt -= ctx->t2;
            return ctx->q2 + ctx->vc * dt + A_FLOAT_C(0.5) * ctx->de * dt * dt;
        }
        return ctx->q;
    }
    if (dt > 0) /* initial blend */
    {
        return ctx->vs * dt + A_FLOAT_C(0.5) * ctx->ac * dt * dt;
    }
    return 0;
}

a_float a_traptraj_vel(a_traptraj const *ctx, a_float dt)
{
    if (dt >= ctx->t1)
    {
        if (dt < ctx->t2) /* linear motion */
        {
            return ctx->vc;
        }
        if (dt < ctx->t) /* final blend */
        {
            return ctx->vc + ctx->de * (dt - ctx->t2);
        }
        return ctx->ve;
    }
    if (dt > 0) /* initial blend */
    {
        return ctx->vs + ctx->ac * dt;
    }
    return ctx->vs;
}

a_float a_traptraj_acc(a_traptraj const *ctx, a_float dt)
{
    if (dt < ctx->t1)
    {
        if (dt >= 0) /* initial blend */
        {
            return ctx->ac;
        }
    }
    else if (dt >= ctx->t2)
    {
        if (dt < ctx->t) /* final blend */
        {
            return ctx->de;
        }
    }
    return 0; /* linear motion */
}
