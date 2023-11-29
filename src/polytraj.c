#include "a/polytraj.h"
#include "a/poly.h"

/* function for cubic polynomial trajectory */

void a_polytraj3_gen(a_polytraj3_s *const ctx,
                     a_float_t const t0, a_float_t const t1,
                     a_float_t const q0, a_float_t const q1,
                     a_float_t const v0, a_float_t const v1)
{
    a_float_t const q = q1 - q0;
    a_float_t const t = t1 - t0;
    a_float_t const inv_t1 = 1 / t;
    a_float_t const inv_t2 = inv_t1 * inv_t1;
    a_float_t const inv_t3 = inv_t1 * inv_t2;

    ctx->q[0] = q0;
    ctx->q[1] = v0;
    ctx->q[2] = inv_t1 * (-2 * v0 - v1) +
                inv_t2 * q * 3;
    ctx->q[3] = inv_t2 * (v0 + v1) -
                inv_t3 * q * 2;

    ctx->v[0] = ctx->q[1];
    ctx->v[1] = ctx->q[2] * 2;
    ctx->v[2] = ctx->q[3] * 3;

    ctx->a[0] = ctx->v[1];
    ctx->a[1] = ctx->v[2] * 2;
}

a_float_t a_polytraj3_pos(a_polytraj3_s const *const ctx, a_float_t const dt)
{
    return a_poly_eval(ctx->q, A_LEN(ctx->q), dt);
}

a_float_t a_polytraj3_vel(a_polytraj3_s const *const ctx, a_float_t const dt)
{
    return a_poly_eval(ctx->v, A_LEN(ctx->v), dt);
}

a_float_t a_polytraj3_acc(a_polytraj3_s const *const ctx, a_float_t const dt)
{
    return a_poly_eval(ctx->a, A_LEN(ctx->a), dt);
}

/* function for quintic polynomial trajectory */

void a_polytraj5_gen(a_polytraj5_s *const ctx,
                     a_float_t const t0, a_float_t const t1,
                     a_float_t const q0, a_float_t const q1,
                     a_float_t const v0, a_float_t const v1,
                     a_float_t const a0, a_float_t const a1)
{
    a_float_t const q = q1 - q0;
    a_float_t const t = t1 - t0;
    a_float_t const inv_t1 = 1 / t;
    a_float_t const inv_t2 = inv_t1 * inv_t1;
    a_float_t const inv_t3 = inv_t1 * inv_t2;
    a_float_t const inv_t4 = inv_t2 * inv_t2;
    a_float_t const inv_t5 = inv_t2 * inv_t3;

    ctx->q[0] = q0;
    ctx->q[1] = v0;
    ctx->q[2] = a0 * (a_float_t)(1 / 2.0);
    ctx->q[3] = (a_float_t)(1 / 2.0) *
                (inv_t1 * (a1 - 3 * a0) -
                 inv_t2 * (12 * v0 + 8 * v1) +
                 inv_t3 * q * 20);
    ctx->q[4] = (a_float_t)(1 / 2.0) *
                (inv_t2 * (3 * a0 - 2 * a1) +
                 inv_t3 * (16 * v0 + 14 * v1) -
                 inv_t4 * q * 30);
    ctx->q[5] = (a_float_t)(1 / 2.0) *
                (inv_t3 * (a1 - a0) -
                 inv_t4 * (v0 + v1) * 6 +
                 inv_t5 * q * 12);

    ctx->v[0] = ctx->q[1];
    ctx->v[1] = ctx->q[2] * 2;
    ctx->v[2] = ctx->q[3] * 3;
    ctx->v[3] = ctx->q[4] * 4;
    ctx->v[4] = ctx->q[5] * 5;

    ctx->a[0] = ctx->v[1];
    ctx->a[1] = ctx->v[2] * 2;
    ctx->a[2] = ctx->v[3] * 3;
    ctx->a[3] = ctx->v[4] * 4;
}

a_float_t a_polytraj5_pos(a_polytraj5_s const *const ctx, a_float_t const dt)
{
    return a_poly_eval(ctx->q, A_LEN(ctx->q), dt);
}

a_float_t a_polytraj5_vel(a_polytraj5_s const *const ctx, a_float_t const dt)
{
    return a_poly_eval(ctx->v, A_LEN(ctx->v), dt);
}

a_float_t a_polytraj5_acc(a_polytraj5_s const *const ctx, a_float_t const dt)
{
    return a_poly_eval(ctx->a, A_LEN(ctx->a), dt);
}

/* function for hepta polynomial trajectory */

void a_polytraj7_gen(a_polytraj7_s *const ctx,
                     a_float_t const t0, a_float_t const t1,
                     a_float_t const q0, a_float_t const q1,
                     a_float_t const v0, a_float_t const v1,
                     a_float_t const a0, a_float_t const a1,
                     a_float_t const j0, a_float_t const j1)
{
    a_float_t const q = q1 - q0;
    a_float_t const t = t1 - t0;
    a_float_t const inv_t1 = 1 / t;
    a_float_t const inv_t2 = inv_t1 * inv_t1;
    a_float_t const inv_t3 = inv_t1 * inv_t2;
    a_float_t const inv_t4 = inv_t2 * inv_t2;
    a_float_t const inv_t5 = inv_t2 * inv_t3;
    a_float_t const inv_t6 = inv_t3 * inv_t3;
    a_float_t const inv_t7 = inv_t3 * inv_t4;

    ctx->q[0] = q0;
    ctx->q[1] = v0;
    ctx->q[2] = a0 * (a_float_t)(1 / 2.0);
    ctx->q[3] = j0 * (a_float_t)(1 / 6.0);
    ctx->q[4] = (a_float_t)(1 / 6.0) *
                (inv_t1 * (-4 * j0 - j1) +
                 inv_t2 * (15 * a1 - 30 * a0) -
                 inv_t3 * (120 * v0 + 90 * v1) +
                 inv_t4 * q * 210);
    ctx->q[5] = (a_float_t)(1 / 2.0) *
                (inv_t2 * (2 * j0 + j1) +
                 inv_t3 * (20 * a0 - 14 * a1) +
                 inv_t4 * (90 * v0 + 78 * v1) -
                 inv_t5 * q * 168);
    ctx->q[6] = (a_float_t)(1 / 6.0) *
                (inv_t3 * (-4 * j0 - 3 * j1) +
                 inv_t4 * (39 * a1 - 45 * a0) -
                 inv_t5 * (216 * v0 + 204 * v1) +
                 inv_t6 * q * 420);
    ctx->q[7] = (a_float_t)(1 / 6.0) *
                (inv_t4 * (j0 + j1) +
                 inv_t5 * (a0 - a1) * 12 +
                 inv_t6 * (v0 + v1) * 60 -
                 inv_t7 * q * 120);

    ctx->v[0] = ctx->q[1];
    ctx->v[1] = ctx->q[2] * 2;
    ctx->v[2] = ctx->q[3] * 3;
    ctx->v[3] = ctx->q[4] * 4;
    ctx->v[4] = ctx->q[5] * 5;
    ctx->v[5] = ctx->q[6] * 6;
    ctx->v[6] = ctx->q[7] * 7;

    ctx->a[0] = ctx->v[1];
    ctx->a[1] = ctx->v[2] * 2;
    ctx->a[2] = ctx->v[3] * 3;
    ctx->a[3] = ctx->v[4] * 4;
    ctx->a[4] = ctx->v[5] * 5;
    ctx->a[5] = ctx->v[6] * 6;

    ctx->j[0] = ctx->a[1];
    ctx->j[1] = ctx->a[2] * 2;
    ctx->j[2] = ctx->a[3] * 3;
    ctx->j[3] = ctx->a[4] * 4;
    ctx->j[4] = ctx->a[5] * 5;
}

a_float_t a_polytraj7_pos(a_polytraj7_s const *const ctx, a_float_t const dt)
{
    return a_poly_eval(ctx->q, A_LEN(ctx->q), dt);
}

a_float_t a_polytraj7_vel(a_polytraj7_s const *const ctx, a_float_t const dt)
{
    return a_poly_eval(ctx->v, A_LEN(ctx->v), dt);
}

a_float_t a_polytraj7_acc(a_polytraj7_s const *const ctx, a_float_t const dt)
{
    return a_poly_eval(ctx->a, A_LEN(ctx->a), dt);
}

a_float_t a_polytraj7_jer(a_polytraj7_s const *const ctx, a_float_t const dt)
{
    return a_poly_eval(ctx->j, A_LEN(ctx->j), dt);
}
