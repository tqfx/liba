#include "a/plane.h"

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

int a_plane_set_dir(a_plane *ctx, a_real x, a_real y, a_real z)
{
    a_real s = x * x + y * y + z * z;
    if (s == 1)
    {
        ctx->dir_.x = x;
        ctx->dir_.y = y;
        ctx->dir_.z = z;
    }
    else if (s > 0)
    {
        s = 1 / a_real_sqrt(s);
        ctx->dir_.x = x * s;
        ctx->dir_.y = y * s;
        ctx->dir_.z = z * s;
    }
    else { return A_FAILURE; }
    return a_vector3_ortho(&ctx->dir_, &ctx->u_, &ctx->v_);
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
    a_real s = a * a + b * b + c * c;
    if (s == 1)
    {
        d = 0 - d;
        ctx->dir_.x = a;
        ctx->dir_.y = b;
        ctx->dir_.z = c;
    }
    else if (s > 0)
    {
        d = 0 - d / s;
        s = 1 / a_real_sqrt(s);
        ctx->dir_.x = a * s;
        ctx->dir_.y = b * s;
        ctx->dir_.z = c * s;
    }
    else { return A_FAILURE; }
    ctx->orig.x = a * d;
    ctx->orig.y = b * d;
    ctx->orig.z = c * d;
    return a_vector3_ortho(&ctx->dir_, &ctx->u_, &ctx->v_);
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
    a_vector3 v;
    a_vector3_set(&v, o, p);
    w = a_vector3_dot(&v, n);
    res->x = p->x - n->x * w;
    res->y = p->y - n->y * w;
    res->z = p->z - n->z * w;
    return w;
}

a_real a_plane_sdist(a_plane const *ctx, a_point3 const *p)
{
    a_vector3 v;
    a_vector3_set(&v, &ctx->orig, p);
    return a_vector3_dot(&v, &ctx->dir_);
}

a_real a_plane_dist(a_plane const *ctx, a_point3 const *p)
{
    a_real const r = a_plane_sdist(ctx, p);
    return A_ABS(r);
}

int a_plane_int0(a_plane const *ctx, a_point3 const *rhs, a_real *u, a_real *v)
{
    a_real w;
    a_vector3 vec;
    a_vector3_set(&vec, &ctx->orig, rhs);
    w = a_vector3_dot(&vec, &ctx->dir_);
    if (A_ABS(w) < A_REAL_EPS)
    {
        *u = a_vector3_dot(&vec, &ctx->u_);
        *v = a_vector3_dot(&vec, &ctx->v_);
        return 1;
    }
    return 0;
}

int a_plane_int1(a_plane const *ctx, a_line3 const *rhs, a_real min, a_real max, a_real *res)
{
    a_real u, w;
    a_vector3 v;
    a_vector3_set(&v, &rhs->orig, &ctx->orig);
    w = a_vector3_dot(&ctx->dir_, &rhs->dir_);
    u = a_vector3_dot(&ctx->dir_, &v);
    if (A_ABS(w) >= A_REAL_EPS)
    {
        *res = u / w;
        if (*res > min - A_REAL_EPS &&
            *res < max + A_REAL_EPS)
        {
            return 1;
        }
    }
    else if (A_ABS(u) < A_REAL_EPS)
    {
        return 2;
    }
    return 0;
}
