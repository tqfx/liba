#define LIBA_VECTOR2_C
#include "a/vector2.h"

a_real a_vector2_unit(a_vector2 *ctx)
{
    a_real const n = a_real_hypot(ctx->x, ctx->y);
    if (n > 0)
    {
        ctx->x /= n;
        ctx->y /= n;
    }
    return n;
}

a_real a_vector2_norm(a_vector2 const *ctx)
{
    return a_real_hypot(ctx->x, ctx->y);
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
    return a_real_hypot(x, y);
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
    a_real const n1 = a_real_hypot(lhs->x, lhs->y);
    a_real const n2 = a_real_hypot(rhs->x, rhs->y);
    a_real r = a_vector2_dot(lhs, rhs) / (n1 * n2);
    if (r > +1) { r = +1; }
    if (r < -1) { r = -1; }
    return a_real_acos(r);
}

a_bool a_vector2_isver(a_vector2 const *lhs, a_vector2 const *rhs)
{
    return a_vector2_dot(lhs, rhs) < A_REAL_EPS;
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
