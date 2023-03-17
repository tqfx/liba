#include "a/polytrack.h"
#include "a/poly.h"

/* function for cubic polynomial trajectory */

a_void_t a_polytrack3_init1(a_polytrack3_s *const ctx, a_real_t const t[2], a_real_t const q[2], a_real_t const v[2])
{
    ctx->t[0] = t[0];
    ctx->t[1] = t[1];
    ctx->q[0] = q[0];
    ctx->q[1] = q[1];
    ctx->v[0] = v[0];
    ctx->v[1] = v[1];
    a_polytrack3_gen(ctx);
}

a_void_t a_polytrack3_init2(a_polytrack3_s *const ctx, a_real_t const source[3], a_real_t const target[3])
{
    ctx->t[0] = source[0];
    ctx->t[1] = target[0];
    ctx->q[0] = source[1];
    ctx->q[1] = target[1];
    ctx->v[0] = source[2];
    ctx->v[1] = target[2];
    a_polytrack3_gen(ctx);
}

a_void_t a_polytrack3_init(a_polytrack3_s *const ctx,
                           a_real_t const t0, a_real_t const t1,
                           a_real_t const q0, a_real_t const q1,
                           a_real_t const v0, a_real_t const v1)
{
    ctx->t[0] = t0;
    ctx->t[1] = t1;
    ctx->q[0] = q0;
    ctx->q[1] = q1;
    ctx->v[0] = v0;
    ctx->v[1] = v1;
    a_polytrack3_gen(ctx);
}

a_void_t a_polytrack3_gen(a_polytrack3_s *const ctx)
{
    a_real_t const q = ctx->q[1] - ctx->q[0];
    a_real_t const t = ctx->t[1] - ctx->t[0];
    a_real_t const inv_t1 = 1 / t;
    a_real_t const inv_t2 = inv_t1 * inv_t1;
    a_real_t const inv_t3 = inv_t1 * inv_t2;

    ctx->k[0] = ctx->q[0];
    ctx->k[1] = ctx->v[0];
    ctx->k[2] = inv_t1 * (-2 * ctx->v[0] - ctx->v[1]) +
                inv_t2 * q * 3;
    ctx->k[3] = inv_t2 * (ctx->v[0] + ctx->v[1]) -
                inv_t3 * q * 2;
}

a_void_t a_polytrack3_out(a_polytrack3_s const *const ctx, a_real_t ts, a_real_t out[3])
{
    a_real_t a[4];
    a[0] = ctx->k[3];
    a[1] = ctx->k[2];
    a[2] = ctx->k[1];
    a[3] = ctx->k[0];
    ts -= ctx->t[0];
    out[0] = a_poly_evar(a, 4, ts);
    a[0] *= 3;
    a[1] *= 2;
    out[1] = a_poly_evar(a, 3, ts);
    a[0] *= 2;
    out[2] = a_poly_evar(a, 2, ts);
}

a_real_t a_polytrack3_pos(a_polytrack3_s const *const ctx, a_real_t const ts)
{
    a_real_t a[4];
    a[0] = ctx->k[3];
    a[1] = ctx->k[2];
    a[2] = ctx->k[1];
    a[3] = ctx->k[0];
    return a_poly_evar(a, 4, ts - ctx->t[0]);
}

a_real_t a_polytrack3_vec(a_polytrack3_s const *const ctx, a_real_t const ts)
{
    a_real_t a[3];
    a[0] = ctx->k[3] * 3;
    a[1] = ctx->k[2] * 2;
    a[2] = ctx->k[1];
    return a_poly_evar(a, 3, ts - ctx->t[0]);
}

a_real_t a_polytrack3_acc(a_polytrack3_s const *const ctx, a_real_t const ts)
{
    a_real_t a[2];
    a[0] = ctx->k[3] * 3 * 2;
    a[1] = ctx->k[2] * 2;
    return a_poly_evar(a, 2, ts - ctx->t[0]);
}

/* function for quintic polynomial trajectory */

a_void_t a_polytrack5_init1(a_polytrack5_s *const ctx, a_real_t const t[2], a_real_t const q[2], a_real_t const v[2], a_real_t const a[2])
{
    ctx->t[0] = t[0];
    ctx->t[1] = t[1];
    ctx->q[0] = q[0];
    ctx->q[1] = q[1];
    ctx->v[0] = v[0];
    ctx->v[1] = v[1];
    ctx->a[0] = a[0];
    ctx->a[1] = a[1];
    a_polytrack5_gen(ctx);
}

a_void_t a_polytrack5_init2(a_polytrack5_s *const ctx, a_real_t const source[4], a_real_t const target[4])
{
    ctx->t[0] = source[0];
    ctx->t[1] = target[0];
    ctx->q[0] = source[1];
    ctx->q[1] = target[1];
    ctx->v[0] = source[2];
    ctx->v[1] = target[2];
    ctx->a[0] = source[3];
    ctx->a[1] = target[3];
    a_polytrack5_gen(ctx);
}

a_void_t a_polytrack5_init(a_polytrack5_s *const ctx,
                           a_real_t const t0, a_real_t const t1,
                           a_real_t const q0, a_real_t const q1,
                           a_real_t const v0, a_real_t const v1,
                           a_real_t const a0, a_real_t const a1)
{
    ctx->t[0] = t0;
    ctx->t[1] = t1;
    ctx->v[0] = v0;
    ctx->v[1] = v1;
    ctx->q[0] = q0;
    ctx->q[1] = q1;
    ctx->a[0] = a0;
    ctx->a[1] = a1;
    a_polytrack5_gen(ctx);
}

a_void_t a_polytrack5_gen(a_polytrack5_s *const ctx)
{
    a_real_t const q = ctx->q[1] - ctx->q[0];
    a_real_t const t = ctx->t[1] - ctx->t[0];
    a_real_t const inv_t1 = 1 / t;
    a_real_t const inv_t2 = inv_t1 * inv_t1;
    a_real_t const inv_t3 = inv_t1 * inv_t2;
    a_real_t const inv_t4 = inv_t2 * inv_t2;
    a_real_t const inv_t5 = inv_t2 * inv_t3;
    ctx->k[0] = ctx->q[0];
    ctx->k[1] = ctx->v[0];
    ctx->k[2] = ctx->a[0] * a_real_c(1 / 2.0);
    ctx->k[3] = a_real_c(1 / 2.0) *
                (inv_t1 * (ctx->a[1] - 3 * ctx->a[0]) -
                 inv_t2 * (12 * ctx->v[0] + 8 * ctx->v[1]) +
                 inv_t3 * q * 20);
    ctx->k[4] = a_real_c(1 / 2.0) *
                (inv_t2 * (3 * ctx->a[0] - 2 * ctx->a[1]) +
                 inv_t3 * (16 * ctx->v[0] + 14 * ctx->v[1]) -
                 inv_t4 * q * 30);
    ctx->k[5] = a_real_c(1 / 2.0) *
                (inv_t3 * (ctx->a[1] - ctx->a[0]) -
                 inv_t4 * (ctx->v[0] + ctx->v[1]) * 6 +
                 inv_t5 * q * 12);
}

a_void_t a_polytrack5_out(a_polytrack5_s const *const ctx, a_real_t ts, a_real_t out[3])
{
    a_real_t a[6];
    a[0] = ctx->k[5];
    a[1] = ctx->k[4];
    a[2] = ctx->k[3];
    a[3] = ctx->k[2];
    a[4] = ctx->k[1];
    a[5] = ctx->k[0];
    ts -= ctx->t[0];
    out[0] = a_poly_evar(a, 6, ts);
    a[0] *= 5;
    a[1] *= 4;
    a[2] *= 3;
    a[3] *= 2;
    out[1] = a_poly_evar(a, 5, ts);
    a[0] *= 4;
    a[1] *= 3;
    a[2] *= 2;
    out[2] = a_poly_evar(a, 4, ts);
}

a_real_t a_polytrack5_pos(a_polytrack5_s const *const ctx, a_real_t const ts)
{
    a_real_t a[6];
    a[0] = ctx->k[5];
    a[1] = ctx->k[4];
    a[2] = ctx->k[3];
    a[3] = ctx->k[2];
    a[4] = ctx->k[1];
    a[5] = ctx->k[0];
    return a_poly_evar(a, 6, ts - ctx->t[0]);
}

a_real_t a_polytrack5_vec(a_polytrack5_s const *const ctx, a_real_t const ts)
{
    a_real_t a[5];
    a[0] = ctx->k[5] * 5;
    a[1] = ctx->k[4] * 4;
    a[2] = ctx->k[3] * 3;
    a[3] = ctx->k[2] * 2;
    a[4] = ctx->k[1];
    return a_poly_evar(a, 5, ts - ctx->t[0]);
}

a_real_t a_polytrack5_acc(a_polytrack5_s const *const ctx, a_real_t const ts)
{
    a_real_t a[4];
    a[0] = ctx->k[5] * 5 * 4;
    a[1] = ctx->k[4] * 4 * 3;
    a[2] = ctx->k[3] * 3 * 2;
    a[3] = ctx->k[2] * 2;
    return a_poly_evar(a, 4, ts - ctx->t[0]);
}

/* function for hepta polynomial trajectory */

a_void_t a_polytrack7_init1(a_polytrack7_s *const ctx, a_real_t const t[2], a_real_t const q[2], a_real_t const v[2], a_real_t const a[2], a_real_t const j[2])
{
    ctx->t[0] = t[0];
    ctx->t[1] = t[1];
    ctx->q[0] = q[0];
    ctx->q[1] = q[1];
    ctx->v[0] = v[0];
    ctx->v[1] = v[1];
    ctx->a[0] = a[0];
    ctx->a[1] = a[1];
    ctx->j[0] = j[0];
    ctx->j[1] = j[1];
    a_polytrack7_gen(ctx);
}

a_void_t a_polytrack7_init2(a_polytrack7_s *const ctx, a_real_t const source[5], a_real_t const target[5])
{
    ctx->t[0] = source[0];
    ctx->t[1] = target[0];
    ctx->q[0] = source[1];
    ctx->q[1] = target[1];
    ctx->v[0] = source[2];
    ctx->v[1] = target[2];
    ctx->a[0] = source[3];
    ctx->a[1] = target[3];
    ctx->j[0] = source[4];
    ctx->j[1] = target[4];
    a_polytrack7_gen(ctx);
}

a_void_t a_polytrack7_init(a_polytrack7_s *const ctx,
                           a_real_t const t0, a_real_t const t1,
                           a_real_t const q0, a_real_t const q1,
                           a_real_t const v0, a_real_t const v1,
                           a_real_t const a0, a_real_t const a1,
                           a_real_t const j0, a_real_t const j1)
{
    ctx->t[0] = t0;
    ctx->t[1] = t1;
    ctx->q[0] = q0;
    ctx->q[1] = q1;
    ctx->v[0] = v0;
    ctx->v[1] = v1;
    ctx->a[0] = a0;
    ctx->a[1] = a1;
    ctx->j[0] = j0;
    ctx->j[1] = j1;
    a_polytrack7_gen(ctx);
}

a_void_t a_polytrack7_gen(a_polytrack7_s *const ctx)
{
    a_real_t const q = ctx->q[1] - ctx->q[0];
    a_real_t const t = ctx->t[1] - ctx->t[0];
    a_real_t const inv_t1 = 1 / t;
    a_real_t const inv_t2 = inv_t1 * inv_t1;
    a_real_t const inv_t3 = inv_t1 * inv_t2;
    a_real_t const inv_t4 = inv_t2 * inv_t2;
    a_real_t const inv_t5 = inv_t2 * inv_t3;
    a_real_t const inv_t6 = inv_t3 * inv_t3;
    a_real_t const inv_t7 = inv_t3 * inv_t4;
    ctx->k[0] = ctx->q[0];
    ctx->k[1] = ctx->v[0];
    ctx->k[2] = ctx->a[0] * a_real_c(1 / 2.0);
    ctx->k[3] = ctx->j[0] * a_real_c(1 / 6.0);
    ctx->k[4] = a_real_c(1 / 6.0) *
                (inv_t1 * (-4 * ctx->j[0] - ctx->j[1]) +
                 inv_t2 * (15 * ctx->a[1] - 30 * ctx->a[0]) -
                 inv_t3 * (120 * ctx->v[0] + 90 * ctx->v[1]) +
                 inv_t4 * q * 210);
    ctx->k[5] = a_real_c(1 / 2.0) *
                (inv_t2 * (2 * ctx->j[0] + ctx->j[1]) +
                 inv_t3 * (20 * ctx->a[0] - 14 * ctx->a[1]) +
                 inv_t4 * (90 * ctx->v[0] + 78 * ctx->v[1]) -
                 inv_t5 * q * 168);
    ctx->k[6] = a_real_c(1 / 6.0) *
                (inv_t3 * (-4 * ctx->j[0] - 3 * ctx->j[1]) +
                 inv_t4 * (39 * ctx->a[1] - 45 * ctx->a[0]) -
                 inv_t5 * (216 * ctx->v[0] + 204 * ctx->v[1]) +
                 inv_t6 * q * 420);
    ctx->k[7] = a_real_c(1 / 6.0) *
                (inv_t4 * (ctx->j[0] + ctx->j[1]) +
                 inv_t5 * (ctx->a[0] - ctx->a[1]) * 12 +
                 inv_t6 * (ctx->v[0] + ctx->v[1]) * 60 -
                 inv_t7 * q * 120);
}

a_void_t a_polytrack7_out(a_polytrack7_s const *const ctx, a_real_t ts, a_real_t out[4])
{
    a_real_t a[8];
    a[0] = ctx->k[7];
    a[1] = ctx->k[6];
    a[2] = ctx->k[5];
    a[3] = ctx->k[4];
    a[4] = ctx->k[3];
    a[5] = ctx->k[2];
    a[6] = ctx->k[1];
    a[7] = ctx->k[0];
    ts -= ctx->t[0];
    out[0] = a_poly_evar(a, 8, ts);
    a[0] *= 7;
    a[1] *= 6;
    a[2] *= 5;
    a[3] *= 4;
    a[4] *= 3;
    a[5] *= 2;
    out[1] = a_poly_evar(a, 7, ts);
    a[0] *= 6;
    a[1] *= 5;
    a[2] *= 4;
    a[3] *= 3;
    a[4] *= 2;
    out[2] = a_poly_evar(a, 6, ts);
    a[0] *= 5;
    a[1] *= 4;
    a[2] *= 3;
    a[3] *= 2;
    out[3] = a_poly_evar(a, 5, ts);
}

a_real_t a_polytrack7_pos(a_polytrack7_s const *const ctx, a_real_t const ts)
{
    a_real_t a[8];
    a[0] = ctx->k[7];
    a[1] = ctx->k[6];
    a[2] = ctx->k[5];
    a[3] = ctx->k[4];
    a[4] = ctx->k[3];
    a[5] = ctx->k[2];
    a[6] = ctx->k[1];
    a[7] = ctx->k[0];
    return a_poly_evar(a, 8, ts - ctx->t[0]);
}

a_real_t a_polytrack7_vec(a_polytrack7_s const *const ctx, a_real_t const ts)
{
    a_real_t a[7];
    a[0] = ctx->k[7] * 7;
    a[1] = ctx->k[6] * 6;
    a[2] = ctx->k[5] * 5;
    a[3] = ctx->k[4] * 4;
    a[4] = ctx->k[3] * 3;
    a[5] = ctx->k[2] * 2;
    a[6] = ctx->k[1];
    return a_poly_evar(a, 7, ts - ctx->t[0]);
}

a_real_t a_polytrack7_acc(a_polytrack7_s const *const ctx, a_real_t const ts)
{
    a_real_t a[6];
    a[0] = ctx->k[7] * 7 * 6;
    a[1] = ctx->k[6] * 6 * 5;
    a[2] = ctx->k[5] * 5 * 4;
    a[3] = ctx->k[4] * 4 * 3;
    a[4] = ctx->k[3] * 3 * 2;
    a[5] = ctx->k[2] * 2;
    return a_poly_evar(a, 6, ts - ctx->t[0]);
}

a_real_t a_polytrack7_jer(a_polytrack7_s const *const ctx, a_real_t const ts)
{
    a_real_t a[5];
    a[0] = ctx->k[7] * 7 * 6 * 5;
    a[1] = ctx->k[6] * 6 * 5 * 4;
    a[2] = ctx->k[5] * 5 * 4 * 3;
    a[3] = ctx->k[4] * 4 * 3 * 2;
    a[4] = ctx->k[3] * 3 * 2;
    return a_poly_evar(a, 5, ts - ctx->t[0]);
}
