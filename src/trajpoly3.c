#include "a/trajpoly3.h"
#include "a/poly.h"

void a_trajpoly3_gen(a_trajpoly3 *ctx, a_float ts,
                     a_float q0, a_float q1,
                     a_float v0, a_float v1)
{
    a_trajpoly3_gen0(ctx, ts, q0, q1, v0, v1);
#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 1)
    a_trajpoly3_gen1(ctx);
#endif /* A_TRAJPOLY3 */
#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 2)
    a_trajpoly3_gen2(ctx);
#endif /* A_TRAJPOLY3 */
}

void a_trajpoly3_gen0(a_trajpoly3 *ctx, a_float ts,
                      a_float q0, a_float q1,
                      a_float v0, a_float v1)
{
    a_float const q = q1 - q0;
    a_float const inv_t1 = 1 / ts;
    a_float const inv_t2 = inv_t1 * inv_t1;
    a_float const inv_t3 = inv_t1 * inv_t2;

    ctx->q[0] = q0;
    ctx->q[1] = v0;
    ctx->q[2] = inv_t1 * (-2 * v0 - v1) +
                inv_t2 * q * 3;
    ctx->q[3] = inv_t2 * (v0 + v1) -
                inv_t3 * q * 2;
}

#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 1)
void a_trajpoly3_gen1(a_trajpoly3 *ctx)
{
    ctx->v[0] = ctx->q[1];
    ctx->v[1] = ctx->q[2] * 2;
    ctx->v[2] = ctx->q[3] * 3;
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
    return a_poly_eval_(ctx->q, ctx->q + A_LEN(ctx->q), dt);
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
