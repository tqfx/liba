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
    a_real const r = a_vector3_norm2(ctx);
    return a_real_sqrt(r);
}

a_real a_vector3_dist(a_vector3 const *lhs, a_vector3 const *rhs)
{
    a_real const r = a_vector3_dist2(lhs, rhs);
    return a_real_sqrt(r);
}

a_real a_vector3_angle(a_vector3 const *lhs, a_vector3 const *rhs)
{
    a_real const nn = a_vector3_norm2(lhs) * a_vector3_norm2(rhs);
    if (nn > 0)
    {
        a_real r = a_vector3_dot(lhs, rhs) / a_real_sqrt(nn);
        if (r > +1) { r = +1; }
        if (r < -1) { r = -1; }
        return a_real_acos(r);
    }
    return 0;
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

int a_vector3_proj(a_vector3 const *ctx, a_vector3 const *dir, a_vector3 *res)
{
    a_real n = a_vector3_norm2(dir);
    if (n > 0)
    {
        a_real d = a_vector3_dot(dir, ctx) / n;
        res->x = dir->x * d;
        res->y = dir->y * d;
        res->z = dir->z * d;
        return A_SUCCESS;
    }
    return A_FAILURE;
}

int a_vector3_perp(a_vector3 const *ctx, a_vector3 const *dir, a_vector3 *res)
{
    a_real n = a_vector3_norm2(dir);
    if (n > 0)
    {
        a_real d = a_vector3_dot(dir, ctx) / n;
        res->x = ctx->x - dir->x * d;
        res->y = ctx->y - dir->y * d;
        res->z = ctx->z - dir->z * d;
        return A_SUCCESS;
    }
    return A_FAILURE;
}

int a_vector3_refl(a_vector3 const *ctx, a_vector3 const *dir, a_vector3 *res)
{
    a_real n = a_vector3_norm2(dir);
    if (n > 0)
    {
        a_real d = a_vector3_dot(dir, ctx) * 2 / n;
        res->x = ctx->x - dir->x * d;
        res->y = ctx->y - dir->y * d;
        res->z = ctx->z - dir->z * d;
        return A_SUCCESS;
    }
    return A_FAILURE;
}

int a_vector3_sym1(a_vector3 const *ctx, a_vector3 const *dir, a_vector3 *res)
{
    a_real n = a_vector3_norm2(dir);
    if (n > 0)
    {
        a_real d = a_vector3_dot(dir, ctx) * 2 / n;
        res->x = dir->x * d - ctx->x;
        res->y = dir->y * d - ctx->y;
        res->z = dir->z * d - ctx->z;
        return A_SUCCESS;
    }
    return A_FAILURE;
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
