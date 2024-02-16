#include "a/trajpoly5.h"
#include "a/poly.h"

void a_trajpoly5_gen(a_trajpoly5 *ctx, a_float ts,
                     a_float p0, a_float p1,
                     a_float v0, a_float v1,
                     a_float a0, a_float a1)
{
    a_trajpoly5_gen0(ctx, ts, p0, p1, v0, v1, a0, a1);
#if defined(A_TRAJPOLY5) && (A_TRAJPOLY5 + 0 > 1)
    a_trajpoly5_gen1(ctx);
#endif /* A_TRAJPOLY5 */
#if defined(A_TRAJPOLY5) && (A_TRAJPOLY5 + 0 > 2)
    a_trajpoly5_gen2(ctx);
#endif /* A_TRAJPOLY5 */
}

void a_trajpoly5_gen0(a_trajpoly5 *ctx, a_float ts,
                      a_float p0, a_float p1,
                      a_float v0, a_float v1,
                      a_float a0, a_float a1)
{
    a_float const p = p1 - p0;
    a_float const _t1 = 1 / ts;
    a_float const _t2 = _t1 * _t1;
    a_float const _t3 = _t1 * _t2;
    a_float const _t4 = _t2 * _t2;
    a_float const _t5 = _t2 * _t3;

    ctx->p[0] = p0;
    ctx->p[1] = v0;
    ctx->p[2] = a0 * (a_float)(1 / 2.0);
    ctx->p[3] = (a_float)(1 / 2.0) *
                (_t1 * (a1 - 3 * a0) -
                 _t2 * (12 * v0 + 8 * v1) +
                 _t3 * p * 20);
    ctx->p[4] = (a_float)(1 / 2.0) *
                (_t2 * (3 * a0 - 2 * a1) +
                 _t3 * (16 * v0 + 14 * v1) -
                 _t4 * p * 30);
    ctx->p[5] = (a_float)(1 / 2.0) *
                (_t3 * (a1 - a0) -
                 _t4 * (v0 + v1) * 6 +
                 _t5 * p * 12);
}

#if defined(A_TRAJPOLY5) && (A_TRAJPOLY5 + 0 > 1)
void a_trajpoly5_gen1(a_trajpoly5 *ctx)
{
    ctx->v[0] = ctx->p[1];
    ctx->v[1] = ctx->p[2] * 2;
    ctx->v[2] = ctx->p[3] * 3;
    ctx->v[3] = ctx->p[4] * 4;
    ctx->v[4] = ctx->p[5] * 5;
}
#endif /* A_TRAJPOLY5 */

#if defined(A_TRAJPOLY5) && (A_TRAJPOLY5 + 0 > 2)
void a_trajpoly5_gen2(a_trajpoly5 *ctx)
{
    ctx->a[0] = ctx->v[1];
    ctx->a[1] = ctx->v[2] * 2;
    ctx->a[2] = ctx->v[3] * 3;
    ctx->a[3] = ctx->v[4] * 4;
}
#endif /* A_TRAJPOLY5 */

a_float a_trajpoly5_pos(a_trajpoly5 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->p, ctx->p + A_LEN(ctx->p), dt);
}

#if defined(A_TRAJPOLY5) && (A_TRAJPOLY5 + 0 > 1)
a_float a_trajpoly5_vel(a_trajpoly5 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->v, ctx->v + A_LEN(ctx->v), dt);
}
#endif /* A_TRAJPOLY5 */

#if defined(A_TRAJPOLY5) && (A_TRAJPOLY5 + 0 > 2)
a_float a_trajpoly5_acc(a_trajpoly5 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->a, ctx->a + A_LEN(ctx->a), dt);
}
#endif /* A_TRAJPOLY5 */
