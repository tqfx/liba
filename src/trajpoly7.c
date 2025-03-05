#include "a/trajpoly7.h"
#include "a/poly.h"

void a_trajpoly7_gen(a_trajpoly7 *ctx, a_real ts,
                     a_real p0, a_real p1,
                     a_real v0, a_real v1,
                     a_real a0, a_real a1,
                     a_real j0, a_real j1)
{
    a_real const p = p1 - p0;
    a_real const _t1 = 1 / ts;
    a_real const _t2 = _t1 * _t1;
    a_real const _t3 = _t1 * _t2;
    a_real const _t4 = _t2 * _t2;
    a_real const _t5 = _t2 * _t3;
    a_real const _t6 = _t3 * _t3;
    a_real const _t7 = _t3 * _t4;
    ctx->c[0] = p0;
    ctx->c[1] = v0;
    ctx->c[2] = a0 * (a_real)(1.0 / 2);
    ctx->c[3] = j0 * (a_real)(1.0 / 6);
    ctx->c[4] = (a_real)(1.0 / 6) *
                (_t1 * (-4 * j0 - j1) +
                 _t2 * (15 * a1 - 30 * a0) -
                 _t3 * (120 * v0 + 90 * v1) +
                 _t4 * p * 210);
    ctx->c[5] = (a_real)(1.0 / 2) *
                (_t2 * (2 * j0 + j1) +
                 _t3 * (20 * a0 - 14 * a1) +
                 _t4 * (90 * v0 + 78 * v1) -
                 _t5 * p * 168);
    ctx->c[6] = (a_real)(1.0 / 6) *
                (_t3 * (-4 * j0 - 3 * j1) +
                 _t4 * (39 * a1 - 45 * a0) -
                 _t5 * (216 * v0 + 204 * v1) +
                 _t6 * p * 420);
    ctx->c[7] = (a_real)(1.0 / 6) *
                (_t4 * (j0 + j1) +
                 _t5 * (a0 - a1) * 12 +
                 _t6 * (v0 + v1) * 60 -
                 _t7 * p * 120);
}

void a_trajpoly7_c0(a_trajpoly7 const *ctx, a_real c[8])
{
    a_copy(c, ctx->c, sizeof(ctx->c));
}

void a_trajpoly7_c1(a_trajpoly7 const *ctx, a_real c[7])
{
    c[0] = ctx->c[1];
    c[1] = ctx->c[2] * 2;
    c[2] = ctx->c[3] * 3;
    c[3] = ctx->c[4] * 4;
    c[4] = ctx->c[5] * 5;
    c[5] = ctx->c[6] * 6;
    c[6] = ctx->c[7] * 7;
}

void a_trajpoly7_c2(a_trajpoly7 const *ctx, a_real c[6])
{
    c[0] = ctx->c[2] * 2;
    c[1] = ctx->c[3] * 3 * 2;
    c[2] = ctx->c[4] * 4 * 3;
    c[3] = ctx->c[5] * 5 * 4;
    c[4] = ctx->c[6] * 6 * 5;
    c[5] = ctx->c[7] * 7 * 6;
}

void a_trajpoly7_c3(a_trajpoly7 const *ctx, a_real c[5])
{
    c[0] = ctx->c[3] * 3 * 2;
    c[1] = ctx->c[4] * 4 * 3 * 2;
    c[2] = ctx->c[5] * 5 * 4 * 3;
    c[3] = ctx->c[6] * 6 * 5 * 4;
    c[4] = ctx->c[7] * 7 * 6 * 5;
}

a_real a_trajpoly7_pos(a_trajpoly7 const *ctx, a_real x)
{
    return a_poly_eval_(ctx->c, ctx->c + A_LEN(ctx->c), x);
}

a_real a_trajpoly7_vel(a_trajpoly7 const *ctx, a_real x)
{
    a_real c[A_LEN(ctx->c) - 1];
    a_trajpoly7_c1(ctx, c);
    return a_poly_eval_(c, c + A_LEN(c), x);
}

a_real a_trajpoly7_acc(a_trajpoly7 const *ctx, a_real x)
{
    a_real c[A_LEN(ctx->c) - 2];
    a_trajpoly7_c2(ctx, c);
    return a_poly_eval_(c, c + A_LEN(c), x);
}

a_real a_trajpoly7_jer(a_trajpoly7 const *ctx, a_real x)
{
    a_real c[A_LEN(ctx->c) - 3];
    a_trajpoly7_c3(ctx, c);
    return a_poly_eval_(c, c + A_LEN(c), x);
}
