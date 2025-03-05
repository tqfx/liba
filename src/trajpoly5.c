#include "a/trajpoly5.h"
#include "a/poly.h"

void a_trajpoly5_gen(a_trajpoly5 *ctx, a_real ts,
                     a_real p0, a_real p1,
                     a_real v0, a_real v1,
                     a_real a0, a_real a1)
{
    a_real const p = p1 - p0;
    a_real const _t1 = 1 / ts;
    a_real const _t2 = _t1 * _t1;
    a_real const _t3 = _t1 * _t2;
    a_real const _t4 = _t2 * _t2;
    a_real const _t5 = _t2 * _t3;
    ctx->c[0] = p0;
    ctx->c[1] = v0;
    ctx->c[2] = a0 * (a_real)(1.0 / 2);
    ctx->c[3] = (a_real)(1.0 / 2) *
                (_t1 * (a1 - 3 * a0) -
                 _t2 * (12 * v0 + 8 * v1) +
                 _t3 * p * 20);
    ctx->c[4] = (a_real)(1.0 / 2) *
                (_t2 * (3 * a0 - 2 * a1) +
                 _t3 * (16 * v0 + 14 * v1) -
                 _t4 * p * 30);
    ctx->c[5] = (a_real)(1.0 / 2) *
                (_t3 * (a1 - a0) -
                 _t4 * (v0 + v1) * 6 +
                 _t5 * p * 12);
}

void a_trajpoly5_c0(a_trajpoly5 const *ctx, a_real c[6])
{
    a_copy(c, ctx->c, sizeof(ctx->c));
}

void a_trajpoly5_c1(a_trajpoly5 const *ctx, a_real c[5])
{
    c[0] = ctx->c[1];
    c[1] = ctx->c[2] * 2;
    c[2] = ctx->c[3] * 3;
    c[3] = ctx->c[4] * 4;
    c[4] = ctx->c[5] * 5;
}

void a_trajpoly5_c2(a_trajpoly5 const *ctx, a_real c[4])
{
    c[0] = ctx->c[2] * 2;
    c[1] = ctx->c[3] * 3 * 2;
    c[2] = ctx->c[4] * 4 * 3;
    c[3] = ctx->c[5] * 5 * 4;
}

a_real a_trajpoly5_pos(a_trajpoly5 const *ctx, a_real x)
{
    return a_poly_eval_(ctx->c, ctx->c + A_LEN(ctx->c), x);
}

a_real a_trajpoly5_vel(a_trajpoly5 const *ctx, a_real x)
{
    a_real c[A_LEN(ctx->c) - 1];
    a_trajpoly5_c1(ctx, c);
    return a_poly_eval_(c, c + A_LEN(c), x);
}

a_real a_trajpoly5_acc(a_trajpoly5 const *ctx, a_real x)
{
    a_real c[A_LEN(ctx->c) - 2];
    a_trajpoly5_c2(ctx, c);
    return a_poly_eval_(c, c + A_LEN(c), x);
}
