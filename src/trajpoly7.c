#include "a/trajpoly7.h"
#include "a/poly.h"

void a_trajpoly7_gen(a_trajpoly7 *ctx, a_float ts,
                     a_float p0, a_float p1,
                     a_float v0, a_float v1,
                     a_float a0, a_float a1,
                     a_float j0, a_float j1)
{
    a_trajpoly7_gen0(ctx, ts, p0, p1, v0, v1, a0, a1, j0, j1);
#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 1)
    a_trajpoly7_gen1(ctx);
#endif /* A_TRAJPOLY7 */
#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 2)
    a_trajpoly7_gen2(ctx);
#endif /* A_TRAJPOLY7 */
#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 3)
    a_trajpoly7_gen3(ctx);
#endif /* A_TRAJPOLY7 */
}

void a_trajpoly7_gen0(a_trajpoly7 *ctx, a_float ts,
                      a_float p0, a_float p1,
                      a_float v0, a_float v1,
                      a_float a0, a_float a1,
                      a_float j0, a_float j1)
{
    a_float const p = p1 - p0;
    a_float const _t1 = 1 / ts;
    a_float const _t2 = _t1 * _t1;
    a_float const _t3 = _t1 * _t2;
    a_float const _t4 = _t2 * _t2;
    a_float const _t5 = _t2 * _t3;
    a_float const _t6 = _t3 * _t3;
    a_float const _t7 = _t3 * _t4;

    ctx->p[0] = p0;
    ctx->p[1] = v0;
    ctx->p[2] = a0 * (a_float)(1 / 2.0);
    ctx->p[3] = j0 * (a_float)(1 / 6.0);
    ctx->p[4] = (a_float)(1 / 6.0) *
                (_t1 * (-4 * j0 - j1) +
                 _t2 * (15 * a1 - 30 * a0) -
                 _t3 * (120 * v0 + 90 * v1) +
                 _t4 * p * 210);
    ctx->p[5] = (a_float)(1 / 2.0) *
                (_t2 * (2 * j0 + j1) +
                 _t3 * (20 * a0 - 14 * a1) +
                 _t4 * (90 * v0 + 78 * v1) -
                 _t5 * p * 168);
    ctx->p[6] = (a_float)(1 / 6.0) *
                (_t3 * (-4 * j0 - 3 * j1) +
                 _t4 * (39 * a1 - 45 * a0) -
                 _t5 * (216 * v0 + 204 * v1) +
                 _t6 * p * 420);
    ctx->p[7] = (a_float)(1 / 6.0) *
                (_t4 * (j0 + j1) +
                 _t5 * (a0 - a1) * 12 +
                 _t6 * (v0 + v1) * 60 -
                 _t7 * p * 120);
}

#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 1)
void a_trajpoly7_gen1(a_trajpoly7 *ctx)
{
    ctx->v[0] = ctx->p[1];
    ctx->v[1] = ctx->p[2] * 2;
    ctx->v[2] = ctx->p[3] * 3;
    ctx->v[3] = ctx->p[4] * 4;
    ctx->v[4] = ctx->p[5] * 5;
    ctx->v[5] = ctx->p[6] * 6;
    ctx->v[6] = ctx->p[7] * 7;
}
#endif /* A_TRAJPOLY7 */

#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 2)
void a_trajpoly7_gen2(a_trajpoly7 *ctx)
{
    ctx->a[0] = ctx->v[1];
    ctx->a[1] = ctx->v[2] * 2;
    ctx->a[2] = ctx->v[3] * 3;
    ctx->a[3] = ctx->v[4] * 4;
    ctx->a[4] = ctx->v[5] * 5;
    ctx->a[5] = ctx->v[6] * 6;
}
#endif /* A_TRAJPOLY7 */

#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 3)
void a_trajpoly7_gen3(a_trajpoly7 *ctx)
{
    ctx->j[0] = ctx->a[1];
    ctx->j[1] = ctx->a[2] * 2;
    ctx->j[2] = ctx->a[3] * 3;
    ctx->j[3] = ctx->a[4] * 4;
    ctx->j[4] = ctx->a[5] * 5;
}
#endif /* A_TRAJPOLY7 */

a_float a_trajpoly7_pos(a_trajpoly7 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->p, ctx->p + A_LEN(ctx->p), dt);
}

#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 1)
a_float a_trajpoly7_vel(a_trajpoly7 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->v, ctx->v + A_LEN(ctx->v), dt);
}
#endif /* A_TRAJPOLY7 */

#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 2)
a_float a_trajpoly7_acc(a_trajpoly7 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->a, ctx->a + A_LEN(ctx->a), dt);
}
#endif /* A_TRAJPOLY7 */

#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 3)
a_float a_trajpoly7_jer(a_trajpoly7 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->j, ctx->j + A_LEN(ctx->j), dt);
}
#endif /* A_TRAJPOLY7 */
