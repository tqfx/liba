#include "a/trajtrap.h"
#include "a/math.h"

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

a_real a_trajtrap_gen(a_trajtrap *ctx, a_real vm, a_real ac, a_real de,
                      a_real p0, a_real p1, a_real v0, a_real v1)
{
    a_real v02, v12, vc2;
    a_real const p = p1 - p0;
    a_real const _2p = 2 * p;
    int const reversed = p < 0;
    if (ac == de) { return 0; }
    if (vm < 0) { vm = -vm; }
    v0 = A_SAT(v0, -vm, +vm);
    v1 = A_SAT(v1, -vm, +vm);
    ctx->p0 = p0;
    ctx->p1 = p1;
    ctx->v0 = v0;
    ctx->v1 = v1;
    v02 = v0 * v0;
    v12 = v1 * v1;
    vc2 = (v12 * ac - v02 * de - _2p * ac * de) / (ac - de);
    if (vc2 <= 0) { return 0; }
    if (vc2 > vm * vm) /* acceleration, constant velocity, deceleration */
    {
        ctx->vc = reversed ? -vm : vm;
        ctx->ta = (ctx->vc - v0) / ac;
        ctx->t = (v1 - ctx->vc) / de;
        ctx->pa = p0 + ctx->v0 * ctx->ta + A_REAL_C(0.5) * ac * ctx->ta * ctx->ta;
        ctx->pd = p1 - ctx->vc * ctx->t - A_REAL_C(0.5) * de * ctx->t * ctx->t;
        ctx->td = ctx->ta + (ctx->pd - ctx->pa) / ctx->vc;
        ctx->t += ctx->td;
    }
    else if (vc2 > v02 && vc2 <= v12) /* acceleration */
    {
        v12 = v02 + _2p * ac;
        if (v12 < 0) { return 0; }
        ctx->v1 = a_real_sqrt(v12);
        if (reversed) { ctx->v1 = -ctx->v1; }
        ctx->vc = ctx->v1;
        ctx->t = (ctx->v1 - v0) / ac;
        ctx->ta = ctx->t;
        ctx->td = ctx->t;
        ctx->pa = p0 + ctx->v0 * ctx->t + A_REAL_C(0.5) * ac * ctx->t * ctx->t;
        ctx->pd = p1;
    }
    else if (vc2 <= v02 && vc2 > v12) /* deceleration */
    {
        v12 = v02 + _2p * de;
        if (v12 < 0) { return 0; }
        ctx->v1 = a_real_sqrt(v12);
        if (reversed) { ctx->v1 = -ctx->v1; }
        ctx->vc = ctx->v0;
        ctx->t = (ctx->v1 - v0) / de;
        ctx->ta = 0;
        ctx->td = 0;
        ctx->pa = p0;
        ctx->pd = p0;
    }
    else /* acceleration, deceleration */
    {
        ctx->vc = a_real_sqrt(vc2);
        if (reversed) { ctx->vc = -ctx->vc; }
        ctx->t = (ctx->vc - v0) / ac;
        ctx->ta = ctx->t;
        ctx->td = ctx->t;
        ctx->pa = p0 + ctx->v0 * ctx->t + A_REAL_C(0.5) * ac * ctx->t * ctx->t;
        ctx->t += (v1 - ctx->vc) / de;
        ctx->pd = ctx->pa;
    }
    ctx->ac = ac;
    ctx->de = de;
    return ctx->t;
}

a_real a_trajtrap_pos(a_trajtrap const *ctx, a_real x)
{
    if (x >= ctx->ta)
    {
        if (x < ctx->td) /* linear motion */
        {
            return ctx->pa + ctx->vc * (x - ctx->ta);
        }
        if (x < ctx->t) /* final blend */
        {
            x -= ctx->td;
            return ctx->pd + ctx->vc * x + A_REAL_C(0.5) * ctx->de * x * x;
        }
        return ctx->p1;
    }
    if (x > 0) /* initial blend */
    {
        return ctx->p0 + ctx->v0 * x + A_REAL_C(0.5) * ctx->ac * x * x;
    }
    return ctx->p0;
}

a_real a_trajtrap_vel(a_trajtrap const *ctx, a_real x)
{
    if (x >= ctx->ta)
    {
        if (x < ctx->td) /* linear motion */
        {
            return ctx->vc;
        }
        if (x < ctx->t) /* final blend */
        {
            return ctx->vc + ctx->de * (x - ctx->td);
        }
        return ctx->v1;
    }
    if (x > 0) /* initial blend */
    {
        return ctx->v0 + ctx->ac * x;
    }
    return ctx->v0;
}

a_real a_trajtrap_acc(a_trajtrap const *ctx, a_real x)
{
    if (x < ctx->ta)
    {
        if (x >= 0) /* initial blend */
        {
            return ctx->ac;
        }
    }
    else if (x >= ctx->td)
    {
        if (x <= ctx->t) /* final blend */
        {
            return ctx->de;
        }
    }
    return 0; /* linear motion */
}
