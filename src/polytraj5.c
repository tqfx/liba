#include "a/polytraj5.h"
#include "a/poly.h"

void a_polytraj5_gen(a_polytraj5 *ctx,
                     a_float t0, a_float t1,
                     a_float q0, a_float q1,
                     a_float v0, a_float v1,
                     a_float a0, a_float a1)
{
    a_polytraj5_gen0(ctx, t0, t1, q0, q1, v0, v1, a0, a1);
#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 1)
    a_polytraj5_gen1(ctx);
#endif /* A_POLYTRAJ5 */
#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 2)
    a_polytraj5_gen2(ctx);
#endif /* A_POLYTRAJ5 */
}

void a_polytraj5_gen0(a_polytraj5 *ctx,
                      a_float t0, a_float t1,
                      a_float q0, a_float q1,
                      a_float v0, a_float v1,
                      a_float a0, a_float a1)
{
    a_float const q = q1 - q0;
    a_float const t = t1 - t0;
    a_float const inv_t1 = 1 / t;
    a_float const inv_t2 = inv_t1 * inv_t1;
    a_float const inv_t3 = inv_t1 * inv_t2;
    a_float const inv_t4 = inv_t2 * inv_t2;
    a_float const inv_t5 = inv_t2 * inv_t3;

    ctx->q[0] = q0;
    ctx->q[1] = v0;
    ctx->q[2] = a0 * (a_float)(1 / 2.0);
    ctx->q[3] = (a_float)(1 / 2.0) *
                (inv_t1 * (a1 - 3 * a0) -
                 inv_t2 * (12 * v0 + 8 * v1) +
                 inv_t3 * q * 20);
    ctx->q[4] = (a_float)(1 / 2.0) *
                (inv_t2 * (3 * a0 - 2 * a1) +
                 inv_t3 * (16 * v0 + 14 * v1) -
                 inv_t4 * q * 30);
    ctx->q[5] = (a_float)(1 / 2.0) *
                (inv_t3 * (a1 - a0) -
                 inv_t4 * (v0 + v1) * 6 +
                 inv_t5 * q * 12);
}

#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 1)
void a_polytraj5_gen1(a_polytraj5 *ctx)
{
    ctx->v[0] = ctx->q[1];
    ctx->v[1] = ctx->q[2] * 2;
    ctx->v[2] = ctx->q[3] * 3;
    ctx->v[3] = ctx->q[4] * 4;
    ctx->v[4] = ctx->q[5] * 5;
}
#endif /* A_POLYTRAJ5 */

#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 2)
void a_polytraj5_gen2(a_polytraj5 *ctx)
{
    ctx->a[0] = ctx->v[1];
    ctx->a[1] = ctx->v[2] * 2;
    ctx->a[2] = ctx->v[3] * 3;
    ctx->a[3] = ctx->v[4] * 4;
}
#endif /* A_POLYTRAJ5 */

a_float a_polytraj5_pos(a_polytraj5 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->q, ctx->q + A_LEN(ctx->q), dt);
}

#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 1)
a_float a_polytraj5_vel(a_polytraj5 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->v, ctx->v + A_LEN(ctx->v), dt);
}
#endif /* A_POLYTRAJ5 */

#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 2)
a_float a_polytraj5_acc(a_polytraj5 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->a, ctx->a + A_LEN(ctx->a), dt);
}
#endif /* A_POLYTRAJ5 */
