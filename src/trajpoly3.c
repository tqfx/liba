#include "a/trajpoly3.h"
#include "a/poly.h"

void a_trajpoly3_gen(a_trajpoly3 *ctx, a_real ts,
                     a_real p0, a_real p1,
                     a_real v0, a_real v1)
{
    a_real const p = p1 - p0;
    a_real const _t1 = 1 / ts;
    a_real const _t2 = _t1 * _t1;
    a_real const _t3 = _t1 * _t2;
    ctx->c[0] = p0;
    ctx->c[1] = v0;
    ctx->c[2] = _t1 * (-2 * v0 - v1) +
                _t2 * p * 3;
    ctx->c[3] = _t2 * (v0 + v1) -
                _t3 * p * 2;
}

void a_trajpoly3_c0(a_trajpoly3 const *ctx, a_real c[4])
{
    a_copy(c, ctx->c, sizeof(ctx->c));
}

void a_trajpoly3_c1(a_trajpoly3 const *ctx, a_real c[3])
{
    c[0] = ctx->c[1];
    c[1] = ctx->c[2] * 2;
    c[2] = ctx->c[3] * 3;
}

void a_trajpoly3_c2(a_trajpoly3 const *ctx, a_real c[2])
{
    c[0] = ctx->c[2] * 2;
    c[1] = ctx->c[3] * 3 * 2;
}

a_real a_trajpoly3_pos(a_trajpoly3 const *ctx, a_real x)
{
    return a_poly_eval_(ctx->c, ctx->c + A_LEN(ctx->c), x);
}

a_real a_trajpoly3_vel(a_trajpoly3 const *ctx, a_real x)
{
    a_real c[A_LEN(ctx->c) - 1];
    a_trajpoly3_c1(ctx, c);
    return a_poly_eval_(c, c + A_LEN(c), x);
}

a_real a_trajpoly3_acc(a_trajpoly3 const *ctx, a_real x)
{
    a_real c[A_LEN(ctx->c) - 2];
    a_trajpoly3_c2(ctx, c);
    return a_poly_eval_(c, c + A_LEN(c), x);
}
