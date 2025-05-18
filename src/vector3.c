#define LIBA_VECTOR3_C
#include "a/vector3.h"

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

a_real a_vector3_unit(a_vector3 *ctx)
{
    a_real r = ctx->x * ctx->x + ctx->y * ctx->y + ctx->z * ctx->z, s;
    if (r != 1 && r > 0)
    {
        r = a_real_sqrt(r);
        s = 1 / r;
        ctx->x *= s;
        ctx->y *= s;
        ctx->z *= s;
    }
    return r;
}

a_real a_vector3_norm(a_vector3 const *ctx)
{
    return a_real_sqrt(ctx->x * ctx->x + ctx->y * ctx->y + ctx->z * ctx->z);
}

a_real a_vector3_norm1(a_vector3 const *ctx)
{
    return A_ABS(ctx->x) + A_ABS(ctx->y) + A_ABS(ctx->z);
}

a_real a_vector3_norm2(a_vector3 const *ctx)
{
    return ctx->x * ctx->x + ctx->y * ctx->y + ctx->z * ctx->z;
}

a_real a_vector3_dot(a_vector3 const *lhs, a_vector3 const *rhs)
{
    return lhs->x * rhs->x + lhs->y * rhs->y + lhs->z * rhs->z;
}

a_real a_vector3_dist(a_vector3 const *lhs, a_vector3 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    a_real const z = rhs->z - lhs->z;
    return a_real_sqrt(x * x + y * y + z * z);
}

a_real a_vector3_dist1(a_vector3 const *lhs, a_vector3 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    a_real const z = rhs->z - lhs->z;
    return A_ABS(x) + A_ABS(y) + A_ABS(z);
}

a_real a_vector3_dist2(a_vector3 const *lhs, a_vector3 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    a_real const z = rhs->z - lhs->z;
    return x * x + y * y + z * z;
}

a_real a_vector3_angle(a_vector3 const *lhs, a_vector3 const *rhs)
{
    a_real const n1 = a_vector3_norm(lhs), n2 = a_vector3_norm(rhs);
    a_real r = a_vector3_dot(lhs, rhs) / (n1 * n2);
    if (r > +1) { r = +1; }
    if (r < -1) { r = -1; }
    return a_real_acos(r);
}

a_bool a_vector3_isver(a_vector3 const *lhs, a_vector3 const *rhs)
{
    return a_vector3_dot(lhs, rhs) < A_REAL_EPS;
}

a_bool a_vector3_ispar(a_vector3 const *lhs, a_vector3 const *rhs)
{
    a_real x, y, z;
    x = lhs->y * rhs->z - lhs->z * rhs->y;
    if (!(A_ABS(x) < A_REAL_EPS)) { return 0; }
    y = lhs->z * rhs->x - lhs->x * rhs->z;
    if (!(A_ABS(y) < A_REAL_EPS)) { return 0; }
    z = lhs->x * rhs->y - lhs->y * rhs->x;
    if (!(A_ABS(z) < A_REAL_EPS)) { return 0; }
    return 1;
}

void a_vector3_cross(a_vector3 const *lhs, a_vector3 const *rhs, a_vector3 *res)
{
    a_real const x = lhs->y * rhs->z - lhs->z * rhs->y;
    a_real const y = lhs->z * rhs->x - lhs->x * rhs->z;
    a_real const z = lhs->x * rhs->y - lhs->y * rhs->x;
    res->x = x;
    res->y = y;
    res->z = z;
}

int a_vector3_ortho(a_vector3 const *ctx, a_vector3 *a, a_vector3 *b)
{
    if (A_ABS(ctx->x) >= A_ABS(ctx->y))
    {
        a_real const n = ctx->x * ctx->x + ctx->z * ctx->z;
        if (n == 1)
        {
            a->x = 0 + ctx->z;
            a->y = 0;
            a->z = 0 - ctx->x;
        }
        else if (n > 0)
        {
            a_real const s = 1 / a_real_sqrt(n);
            a->x = 0 + ctx->z * s;
            a->y = 0;
            a->z = 0 - ctx->x * s;
        }
        else { return A_FAILURE; }
        b->x = 0 + ctx->y * a->z;
        b->y = ctx->z * a->x - ctx->x * a->z;
        b->z = 0 - ctx->y * a->x;
        a_vector3_unit(b);
    }
    else
    {
        a_real const n = ctx->y * ctx->y + ctx->z * ctx->z;
        if (n == 1)
        {
            b->x = 0;
            b->y = 0 + ctx->z;
            b->z = 0 - ctx->y;
        }
        else if (n > 0)
        {
            a_real const s = 1 / a_real_sqrt(n);
            b->x = 0;
            b->y = 0 + ctx->z * s;
            b->z = 0 - ctx->y * s;
        }
        else { return A_FAILURE; }
        a->x = b->y * ctx->z - b->z * ctx->y;
        a->y = 0 + b->z * ctx->x;
        a->z = 0 - b->y * ctx->x;
        a_vector3_unit(a);
    }
    return A_SUCCESS;
}
