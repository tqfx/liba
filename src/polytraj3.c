#include "a/polytraj3.h"
#include "a/poly.h"

void a_polytraj3_gen(a_polytraj3 *ctx,
                     a_float t0, a_float t1,
                     a_float q0, a_float q1,
                     a_float v0, a_float v1)
{
    a_polytraj3_gen0(ctx, t0, t1, q0, q1, v0, v1);
#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 1)
    a_polytraj3_gen1(ctx);
#endif /* A_POLYTRAJ3 */
#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 2)
    a_polytraj3_gen2(ctx);
#endif /* A_POLYTRAJ3 */
}

void a_polytraj3_gen0(a_polytraj3 *ctx,
                      a_float t0, a_float t1,
                      a_float q0, a_float q1,
                      a_float v0, a_float v1)
{
    a_float const q = q1 - q0;
    a_float const t = t1 - t0;
    a_float const inv_t1 = 1 / t;
    a_float const inv_t2 = inv_t1 * inv_t1;
    a_float const inv_t3 = inv_t1 * inv_t2;

    ctx->q[0] = q0;
    ctx->q[1] = v0;
    ctx->q[2] = inv_t1 * (-2 * v0 - v1) +
                inv_t2 * q * 3;
    ctx->q[3] = inv_t2 * (v0 + v1) -
                inv_t3 * q * 2;
}

#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 1)
void a_polytraj3_gen1(a_polytraj3 *ctx)
{
    ctx->v[0] = ctx->q[1];
    ctx->v[1] = ctx->q[2] * 2;
    ctx->v[2] = ctx->q[3] * 3;
}
#endif /* A_POLYTRAJ3 */

#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 2)
void a_polytraj3_gen2(a_polytraj3 *ctx)
{
    ctx->a[0] = ctx->v[1];
    ctx->a[1] = ctx->v[2] * 2;
}
#endif /* A_POLYTRAJ3 */

a_float a_polytraj3_pos(a_polytraj3 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->q, ctx->q + A_LEN(ctx->q), dt);
}

#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 1)
a_float a_polytraj3_vel(a_polytraj3 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->v, ctx->v + A_LEN(ctx->v), dt);
}
#endif /* A_POLYTRAJ3 */

#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 2)
a_float a_polytraj3_acc(a_polytraj3 const *ctx, a_float dt)
{
    return a_poly_eval_(ctx->a, ctx->a + A_LEN(ctx->a), dt);
}
#endif /* A_POLYTRAJ3 */
