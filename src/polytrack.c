#include "a/polytrack.h"
#include "a/poly.h"

/* function for cubic polynomial trajectory */

void a_polytrack3_gen(a_polytrack3_s *const ctx,
                      a_float_t const t0, a_float_t const t1,
                      a_float_t const q0, a_float_t const q1,
                      a_float_t const v0, a_float_t const v1)
{
    a_float_t const q = q1 - q0;
    a_float_t const t = t1 - t0;
    a_float_t const inv_t1 = 1 / t;
    a_float_t const inv_t2 = inv_t1 * inv_t1;
    a_float_t const inv_t3 = inv_t1 * inv_t2;
    ctx->k[0] = q0;
    ctx->k[1] = v0;
    ctx->k[2] = inv_t1 * (-2 * v0 - v1) +
                inv_t2 * q * 3;
    ctx->k[3] = inv_t2 * (v0 + v1) -
                inv_t3 * q * 2;
}

void a_polytrack3_out(a_polytrack3_s const *const ctx, a_float_t dt, a_float_t out[3])
{
    a_float_t a[4];
    a[0] = ctx->k[3];
    a[1] = ctx->k[2];
    a[2] = ctx->k[1];
    a[3] = ctx->k[0];
    out[0] = a_poly_evar(a, 4, dt);
    a[0] *= 3;
    a[1] *= 2;
    out[1] = a_poly_evar(a, 3, dt);
    a[0] *= 2;
    out[2] = a_poly_evar(a, 2, dt);
}

a_float_t a_polytrack3_pos(a_polytrack3_s const *const ctx, a_float_t const dt)
{
    a_float_t a[4];
    a[0] = ctx->k[3];
    a[1] = ctx->k[2];
    a[2] = ctx->k[1];
    a[3] = ctx->k[0];
    return a_poly_evar(a, 4, dt);
}

a_float_t a_polytrack3_vel(a_polytrack3_s const *const ctx, a_float_t const dt)
{
    a_float_t a[3];
    a[0] = ctx->k[3] * 3;
    a[1] = ctx->k[2] * 2;
    a[2] = ctx->k[1];
    return a_poly_evar(a, 3, dt);
}

a_float_t a_polytrack3_acc(a_polytrack3_s const *const ctx, a_float_t const dt)
{
    a_float_t a[2];
    a[0] = ctx->k[3] * 3 * 2;
    a[1] = ctx->k[2] * 2;
    return a_poly_evar(a, 2, dt);
}

/* function for quintic polynomial trajectory */

void a_polytrack5_gen(a_polytrack5_s *const ctx,
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
    ctx->k[0] = q0;
    ctx->k[1] = v0;
    ctx->k[2] = a0 * (a_float_t)(1 / 2.0);
    ctx->k[3] = (a_float_t)(1 / 2.0) *
                (inv_t1 * (a1 - 3 * a0) -
                 inv_t2 * (12 * v0 + 8 * v1) +
                 inv_t3 * q * 20);
    ctx->k[4] = (a_float_t)(1 / 2.0) *
                (inv_t2 * (3 * a0 - 2 * a1) +
                 inv_t3 * (16 * v0 + 14 * v1) -
                 inv_t4 * q * 30);
    ctx->k[5] = (a_float_t)(1 / 2.0) *
                (inv_t3 * (a1 - a0) -
                 inv_t4 * (v0 + v1) * 6 +
                 inv_t5 * q * 12);
}

void a_polytrack5_out(a_polytrack5_s const *const ctx, a_float_t dt, a_float_t out[3])
{
    a_float_t a[6];
    a[0] = ctx->k[5];
    a[1] = ctx->k[4];
    a[2] = ctx->k[3];
    a[3] = ctx->k[2];
    a[4] = ctx->k[1];
    a[5] = ctx->k[0];
    out[0] = a_poly_evar(a, 6, dt);
    a[0] *= 5;
    a[1] *= 4;
    a[2] *= 3;
    a[3] *= 2;
    out[1] = a_poly_evar(a, 5, dt);
    a[0] *= 4;
    a[1] *= 3;
    a[2] *= 2;
    out[2] = a_poly_evar(a, 4, dt);
}

a_float_t a_polytrack5_pos(a_polytrack5_s const *const ctx, a_float_t const dt)
{
    a_float_t a[6];
    a[0] = ctx->k[5];
    a[1] = ctx->k[4];
    a[2] = ctx->k[3];
    a[3] = ctx->k[2];
    a[4] = ctx->k[1];
    a[5] = ctx->k[0];
    return a_poly_evar(a, 6, dt);
}

a_float_t a_polytrack5_vel(a_polytrack5_s const *const ctx, a_float_t const dt)
{
    a_float_t a[5];
    a[0] = ctx->k[5] * 5;
    a[1] = ctx->k[4] * 4;
    a[2] = ctx->k[3] * 3;
    a[3] = ctx->k[2] * 2;
    a[4] = ctx->k[1];
    return a_poly_evar(a, 5, dt);
}

a_float_t a_polytrack5_acc(a_polytrack5_s const *const ctx, a_float_t const dt)
{
    a_float_t a[4];
    a[0] = ctx->k[5] * 5 * 4;
    a[1] = ctx->k[4] * 4 * 3;
    a[2] = ctx->k[3] * 3 * 2;
    a[3] = ctx->k[2] * 2;
    return a_poly_evar(a, 4, dt);
}

/* function for hepta polynomial trajectory */

void a_polytrack7_gen(a_polytrack7_s *const ctx,
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
    ctx->k[0] = q0;
    ctx->k[1] = v0;
    ctx->k[2] = a0 * (a_float_t)(1 / 2.0);
    ctx->k[3] = j0 * (a_float_t)(1 / 6.0);
    ctx->k[4] = (a_float_t)(1 / 6.0) *
                (inv_t1 * (-4 * j0 - j1) +
                 inv_t2 * (15 * a1 - 30 * a0) -
                 inv_t3 * (120 * v0 + 90 * v1) +
                 inv_t4 * q * 210);
    ctx->k[5] = (a_float_t)(1 / 2.0) *
                (inv_t2 * (2 * j0 + j1) +
                 inv_t3 * (20 * a0 - 14 * a1) +
                 inv_t4 * (90 * v0 + 78 * v1) -
                 inv_t5 * q * 168);
    ctx->k[6] = (a_float_t)(1 / 6.0) *
                (inv_t3 * (-4 * j0 - 3 * j1) +
                 inv_t4 * (39 * a1 - 45 * a0) -
                 inv_t5 * (216 * v0 + 204 * v1) +
                 inv_t6 * q * 420);
    ctx->k[7] = (a_float_t)(1 / 6.0) *
                (inv_t4 * (j0 + j1) +
                 inv_t5 * (a0 - a1) * 12 +
                 inv_t6 * (v0 + v1) * 60 -
                 inv_t7 * q * 120);
}

void a_polytrack7_out(a_polytrack7_s const *const ctx, a_float_t dt, a_float_t out[4])
{
    a_float_t a[8];
    a[0] = ctx->k[7];
    a[1] = ctx->k[6];
    a[2] = ctx->k[5];
    a[3] = ctx->k[4];
    a[4] = ctx->k[3];
    a[5] = ctx->k[2];
    a[6] = ctx->k[1];
    a[7] = ctx->k[0];
    out[0] = a_poly_evar(a, 8, dt);
    a[0] *= 7;
    a[1] *= 6;
    a[2] *= 5;
    a[3] *= 4;
    a[4] *= 3;
    a[5] *= 2;
    out[1] = a_poly_evar(a, 7, dt);
    a[0] *= 6;
    a[1] *= 5;
    a[2] *= 4;
    a[3] *= 3;
    a[4] *= 2;
    out[2] = a_poly_evar(a, 6, dt);
    a[0] *= 5;
    a[1] *= 4;
    a[2] *= 3;
    a[3] *= 2;
    out[3] = a_poly_evar(a, 5, dt);
}

a_float_t a_polytrack7_pos(a_polytrack7_s const *const ctx, a_float_t const dt)
{
    a_float_t a[8];
    a[0] = ctx->k[7];
    a[1] = ctx->k[6];
    a[2] = ctx->k[5];
    a[3] = ctx->k[4];
    a[4] = ctx->k[3];
    a[5] = ctx->k[2];
    a[6] = ctx->k[1];
    a[7] = ctx->k[0];
    return a_poly_evar(a, 8, dt);
}

a_float_t a_polytrack7_vel(a_polytrack7_s const *const ctx, a_float_t const dt)
{
    a_float_t a[7];
    a[0] = ctx->k[7] * 7;
    a[1] = ctx->k[6] * 6;
    a[2] = ctx->k[5] * 5;
    a[3] = ctx->k[4] * 4;
    a[4] = ctx->k[3] * 3;
    a[5] = ctx->k[2] * 2;
    a[6] = ctx->k[1];
    return a_poly_evar(a, 7, dt);
}

a_float_t a_polytrack7_acc(a_polytrack7_s const *const ctx, a_float_t const dt)
{
    a_float_t a[6];
    a[0] = ctx->k[7] * 7 * 6;
    a[1] = ctx->k[6] * 6 * 5;
    a[2] = ctx->k[5] * 5 * 4;
    a[3] = ctx->k[4] * 4 * 3;
    a[4] = ctx->k[3] * 3 * 2;
    a[5] = ctx->k[2] * 2;
    return a_poly_evar(a, 6, dt);
}

a_float_t a_polytrack7_jer(a_polytrack7_s const *const ctx, a_float_t const dt)
{
    a_float_t a[5];
    a[0] = ctx->k[7] * 7 * 6 * 5;
    a[1] = ctx->k[6] * 6 * 5 * 4;
    a[2] = ctx->k[5] * 5 * 4 * 3;
    a[3] = ctx->k[4] * 4 * 3 * 2;
    a[4] = ctx->k[3] * 3 * 2;
    return a_poly_evar(a, 5, dt);
}
