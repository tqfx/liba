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
    a_real const r = a_vector3_dot(lhs, rhs);
    return A_ABS(r) < A_REAL_TOL;
}

a_bool a_vector3_ispar(a_vector3 const *lhs, a_vector3 const *rhs)
{
    a_real x, y, z;
    x = lhs->y * rhs->z - lhs->z * rhs->y;
    if (!(A_ABS(x) < A_REAL_TOL)) { return 0; }
    y = lhs->z * rhs->x - lhs->x * rhs->z;
    if (!(A_ABS(y) < A_REAL_TOL)) { return 0; }
    z = lhs->x * rhs->y - lhs->y * rhs->x;
    if (!(A_ABS(z) < A_REAL_TOL)) { return 0; }
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

void a_vector3_outer(a_vector3 const *lhs, a_vector3 const *rhs, a_real res[9])
{
    res[0] = lhs->x * rhs->x;
    res[1] = lhs->x * rhs->y;
    res[2] = lhs->x * rhs->z;
    res[3] = lhs->y * rhs->x;
    res[4] = lhs->y * rhs->y;
    res[5] = lhs->y * rhs->z;
    res[6] = lhs->z * rhs->x;
    res[7] = lhs->z * rhs->y;
    res[8] = lhs->z * rhs->z;
}

int a_vector3_ortho(a_vector3 const *ctx, a_vector3 *u, a_vector3 *v)
{
    if (A_ABS(ctx->x) >= A_ABS(ctx->y))
    {
        a_real const n = ctx->x * ctx->x + ctx->z * ctx->z;
        if (n == 1)
        {
            u->x = 0 + ctx->z;
            u->y = 0;
            u->z = 0 - ctx->x;
        }
        else if (n > 0)
        {
            a_real const s = 1 / a_real_sqrt(n);
            u->x = 0 + ctx->z * s;
            u->y = 0;
            u->z = 0 - ctx->x * s;
        }
        else { return A_FAILURE; }
        v->x = 0 + ctx->y * u->z;
        v->y = ctx->z * u->x - ctx->x * u->z;
        v->z = 0 - ctx->y * u->x;
        a_vector3_unit(v);
    }
    else
    {
        a_real const n = ctx->y * ctx->y + ctx->z * ctx->z;
        if (n == 1)
        {
            v->x = 0;
            v->y = 0 + ctx->z;
            v->z = 0 - ctx->y;
        }
        else if (n > 0)
        {
            a_real const s = 1 / a_real_sqrt(n);
            v->x = 0;
            v->y = 0 + ctx->z * s;
            v->z = 0 - ctx->y * s;
        }
        else { return A_FAILURE; }
        u->x = v->y * ctx->z - v->z * ctx->y;
        u->y = 0 + v->z * ctx->x;
        u->z = 0 - v->y * ctx->x;
        a_vector3_unit(u);
    }
    return A_SUCCESS;
}

void a_vector3_rot_(a_vector3 const *ctx, a_vector3 const *dir, a_real sin, a_real cos, a_vector3 *res)
{
    a_real const dot = a_vector3_dot(dir, ctx) * (1 - cos);
    a_vector3 vec;
    a_vector3_cross(dir, ctx, &vec);
    res->x = ctx->x * cos + vec.x * sin + dir->x * dot;
    res->y = ctx->y * cos + vec.y * sin + dir->y * dot;
    res->z = ctx->z * cos + vec.z * sin + dir->z * dot;
}

void a_vector3_rot(a_vector3 const *ctx, a_vector3 const *dir, a_real angle, a_vector3 *res)
{
    a_real const s = a_real_sin(angle);
    a_real const c = a_real_cos(angle);
    a_vector3_rot_(ctx, dir, s, c, res);
}

void a_vector3_rot2d(a_vector3 const *iu, a_vector3 const *iv, a_real angle,
                     a_vector3 *ou, a_vector3 *ov)
{
    a_real const s = a_real_sin(angle);
    a_real const c = a_real_cos(angle);
    a_vector3 u, v;
    u.x = c * iu->x + s * iv->x;
    u.y = c * iu->y + s * iv->y;
    u.z = c * iu->z + s * iv->z;
    v.x = c * iv->x - s * iu->x;
    v.y = c * iv->y - s * iu->y;
    v.z = c * iv->z - s * iu->z;
    *ou = u;
    *ov = v;
}
