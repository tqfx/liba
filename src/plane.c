#include "a/plane.h"

int a_plane_set_dir(a_plane *ctx, a_real x, a_real y, a_real z)
{
    a_real const n = a_real_norm3(x, y, z);
    if (n > 0)
    {
        ctx->dir_.x = x / n;
        ctx->dir_.y = y / n;
        ctx->dir_.z = z / n;
        a_vector3_ortho(&ctx->dir_, &ctx->u_, &ctx->v_);
        return A_SUCCESS;
    }
    return A_FAILURE;
}

int a_plane_set(a_plane *ctx, a_point3 const *p, a_vector3 const *v)
{
    int rc = a_plane_set_dir(ctx, v->x, v->y, v->z);
    if (rc == 0)
    {
        ctx->orig.x = p->x;
        ctx->orig.y = p->y;
        ctx->orig.z = p->z;
    }
    return rc;
}

int a_plane_set3(a_plane *ctx, a_point3 const *a, a_point3 const *b, a_point3 const *c)
{
    a_vector3 u, v, n;
    a_vector3_set(&u, a, b);
    a_vector3_set(&v, b, c);
    a_vector3_cross(&u, &v, &n);
    return a_plane_set(ctx, a, &n);
}

int a_plane_set4(a_plane *ctx, a_real a, a_real b, a_real c, a_real d)
{
    a_real const s = a * a + b * b + c * c;
    if (s > 0)
    {
        a_real const n = a_real_sqrt(s);
        a_real const t = 0 - d / s;
        ctx->orig.x = a * t;
        ctx->orig.y = b * t;
        ctx->orig.z = c * t;
        ctx->dir_.x = a / n;
        ctx->dir_.y = b / n;
        ctx->dir_.z = c / n;
        a_vector3_ortho(&ctx->dir_, &ctx->u_, &ctx->v_);
        return A_SUCCESS;
    }
    return A_FAILURE;
}

void a_plane_eval(a_plane const *ctx, a_real u, a_real v, a_point3 *res)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const U = &ctx->u_;
    a_vector3 const *const V = &ctx->v_;
    res->x = o->x + U->x * u + V->x * v;
    res->y = o->y + U->y * u + V->y * v;
    res->z = o->z + U->z * u + V->z * v;
}

void a_plane_parm(a_plane const *ctx, a_point3 const *p, a_real *u, a_real *v)
{
    a_vector3 vec;
    a_vector3_set(&vec, &ctx->orig, p);
    *u = a_vector3_dot(&vec, &ctx->u_);
    *v = a_vector3_dot(&vec, &ctx->v_);
}

a_real a_plane_proj(a_plane const *ctx, a_point3 const *p, a_point3 *res)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const n = &ctx->dir_;
    a_real w;
    a_vector3 vec;
    a_vector3_set(&vec, p, o);
    w = a_vector3_dot(&vec, n);
    res->x = p->x + n->x * w;
    res->y = p->y + n->y * w;
    res->z = p->z + n->z * w;
    return 0 - w;
}

a_real a_plane_sdist(a_plane const *ctx, a_point3 const *p)
{
    a_vector3 vec;
    a_vector3_set(&vec, &ctx->orig, p);
    return a_vector3_dot(&vec, &ctx->dir_);
}

a_real a_plane_dist(a_plane const *ctx, a_point3 const *p)
{
    a_real const r = a_plane_sdist(ctx, p);
    return A_ABS(r);
}
