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
    a_real const r = a_vector2_norm2(ctx);
    return a_real_sqrt(r);
}

a_real a_vector2_dist(a_vector2 const *lhs, a_vector2 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    return a_real_sqrt(x * x + y * y);
}

a_real a_vector2_angle(a_vector2 const *lhs, a_vector2 const *rhs)
{
    a_real const nn = a_vector2_norm2(lhs) * a_vector2_norm2(rhs);
    if (nn > 0)
    {
        a_real r = a_vector2_dot(lhs, rhs) / a_real_sqrt(nn);
        if (r > +1) { r = +1; }
        if (r < -1) { r = -1; }
        return a_real_acos(r);
    }
    return 0;
}

int a_vector2_decom(a_vector2 const *ctx, a_vector2 const *dir, a_vector2 *u, a_vector2 *v)
{
    a_real n = a_vector2_norm2(dir);
    if (n > 0)
    {
        a_real d = a_vector2_dot(dir, ctx) / n;
        u->x = dir->x * d;
        u->y = dir->y * d;
        v->x = ctx->x - u->x;
        v->y = ctx->y - u->y;
        return A_SUCCESS;
    }
    return A_FAILURE;
}

int a_vector2_proj(a_vector2 const *ctx, a_vector2 const *dir, a_vector2 *res)
{
    a_real n = a_vector2_norm2(dir);
    if (n > 0)
    {
        a_real d = a_vector2_dot(dir, ctx) / n;
        res->x = dir->x * d;
        res->y = dir->y * d;
        return A_SUCCESS;
    }
    return A_FAILURE;
}

int a_vector2_perp(a_vector2 const *ctx, a_vector2 const *dir, a_vector2 *res)
{
    a_real n = a_vector2_norm2(dir);
    if (n > 0)
    {
        a_real d = a_vector2_dot(dir, ctx) / n;
        res->x = ctx->x - dir->x * d;
        res->y = ctx->y - dir->y * d;
        return A_SUCCESS;
    }
    return A_FAILURE;
}

int a_vector2_refl(a_vector2 const *ctx, a_vector2 const *dir, a_vector2 *res)
{
    a_real n = a_vector2_norm2(dir);
    if (n > 0)
    {
        a_real d = a_vector2_dot(dir, ctx) * 2 / n;
        res->x = dir->x * d - ctx->x;
        res->y = dir->y * d - ctx->y;
        return A_SUCCESS;
    }
    return A_FAILURE;
}

void a_vector2_rot(a_vector2 const *ctx, a_real angle, a_vector2 *res)
{
    a_real const s = a_real_sin(angle);
    a_real const c = a_real_cos(angle);
    a_vector2_rot_(ctx, s, c, res);
}
