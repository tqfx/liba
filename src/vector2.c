#define LIBA_VECTOR2_C
#include "a/vector2.h"

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

a_real a_vector2_unit(a_vector2 *ctx)
{
    a_real r = ctx->x * ctx->x + ctx->y * ctx->y, s;
    if (r != 1 && r > 0)
    {
        r = a_real_sqrt(r);
        s = 1 / r;
        ctx->x *= s;
        ctx->y *= s;
    }
    return r;
}

a_real a_vector2_norm(a_vector2 const *ctx)
{
    return a_real_sqrt(ctx->x * ctx->x + ctx->y * ctx->y);
}

a_real a_vector2_norm1(a_vector2 const *ctx)
{
    return A_ABS(ctx->x) + A_ABS(ctx->y);
}

a_real a_vector2_norm2(a_vector2 const *ctx)
{
    return ctx->x * ctx->x + ctx->y * ctx->y;
}

a_real a_vector2_dot(a_vector2 const *lhs, a_vector2 const *rhs)
{
    return lhs->x * rhs->x + lhs->y * rhs->y;
}

a_real a_vector2_dist(a_vector2 const *lhs, a_vector2 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    return a_real_sqrt(x * x + y * y);
}

a_real a_vector2_dist1(a_vector2 const *lhs, a_vector2 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    return A_ABS(x) + A_ABS(y);
}

a_real a_vector2_dist2(a_vector2 const *lhs, a_vector2 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    return x * x + y * y;
}

a_real a_vector2_angle(a_vector2 const *lhs, a_vector2 const *rhs)
{
    a_real const n1 = a_vector2_norm(lhs), n2 = a_vector2_norm(rhs);
    a_real r = a_vector2_dot(lhs, rhs) / (n1 * n2);
    if (r > +1) { r = +1; }
    if (r < -1) { r = -1; }
    return a_real_acos(r);
}

a_bool a_vector2_isver(a_vector2 const *lhs, a_vector2 const *rhs)
{
    a_real const r = a_vector2_dot(lhs, rhs);
    return A_ABS(r) < A_REAL_EPS;
}

a_bool a_vector2_ispar(a_vector2 const *lhs, a_vector2 const *rhs)
{
    a_real const r = lhs->x * rhs->y - lhs->y * rhs->x;
    return A_ABS(r) < A_REAL_EPS;
}

a_real a_vector2_cross(a_vector2 const *lhs, a_vector2 const *rhs)
{
    return lhs->x * rhs->y - lhs->y * rhs->x;
}

void a_vector2_rot_(a_vector2 const *ctx, a_real sin, a_real cos, a_vector2 *res)
{
    a_real const x = cos * ctx->x - sin * ctx->y;
    a_real const y = sin * ctx->x + cos * ctx->y;
    res->x = x;
    res->y = y;
}

void a_vector2_rot(a_vector2 const *ctx, a_real angle, a_vector2 *res)
{
    a_real const s = a_real_sin(angle);
    a_real const c = a_real_cos(angle);
    a_vector2_rot_(ctx, s, c, res);
}
