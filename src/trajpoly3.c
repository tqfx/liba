#include "a/trajpoly3.h"
#include "a/poly.h"

void a_trajpoly3_gen(a_trajpoly3 *ctx, a_float ts,
                     a_float p0, a_float p1,
                     a_float v0, a_float v1)
{
    a_trajpoly3_gen0(ctx, ts, p0, p1, v0, v1);
#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 1)
    a_trajpoly3_gen1(ctx);
#endif /* A_TRAJPOLY3 */
#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 2)
    a_trajpoly3_gen2(ctx);
#endif /* A_TRAJPOLY3 */
}

void a_trajpoly3_gen0(a_trajpoly3 *ctx, a_float ts,
                      a_float p0, a_float p1,
                      a_float v0, a_float v1)
{
    a_float const p = p1 - p0;
    a_float const _t1 = 1 / ts;
    a_float const _t2 = _t1 * _t1;
    a_float const _t3 = _t1 * _t2;

    ctx->p[0] = p0;
    ctx->p[1] = v0;
    ctx->p[2] = _t1 * (-2 * v0 - v1) +
                _t2 * p * 3;
    ctx->p[3] = _t2 * (v0 + v1) -
                _t3 * p * 2;
}

#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 1)
void a_trajpoly3_gen1(a_trajpoly3 *ctx)
{
    ctx->v[0] = ctx->p[1];
    ctx->v[1] = ctx->p[2] * 2;
    ctx->v[2] = ctx->p[3] * 3;
}
#endif /* A_TRAJPOLY3 */

#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 2)
void a_trajpoly3_gen2(a_trajpoly3 *ctx)
{
    ctx->a[0] = ctx->v[1];
    ctx->a[1] = ctx->v[2] * 2;
}
#endif /* A_TRAJPOLY3 */

a_float a_trajpoly3_pos(a_trajpoly3 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->p, ctx->p + A_LEN(ctx->p), dt);
}

#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 1)
a_float a_trajpoly3_vel(a_trajpoly3 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->v, ctx->v + A_LEN(ctx->v), dt);
}
#endif /* A_TRAJPOLY3 */

#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 2)
a_float a_trajpoly3_acc(a_trajpoly3 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->a, ctx->a + A_LEN(ctx->a), dt);
}
#endif /* A_TRAJPOLY3 */
