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
    else if (s >= A_REAL_EPS)
    {
        s = 1 / a_real_sqrt(s);
        ctx->dir_.x = x * s;
        ctx->dir_.y = y * s;
        ctx->dir_.z = z * s;
    }
    else { return A_FAILURE; }
    return a_vector3_ortho(&ctx->dir_, &ctx->u_, &ctx->v_);
}

int a_plane_set_uv(a_plane *ctx, a_vector3 const *u, a_vector3 const *v)
{
    a_vector3 u_, v_, n_;
    u_ = *u;
    if (a_vector3_unit(&u_) < A_REAL_EPS) { return A_FAILURE; }
    v_ = *v;
    if (a_vector3_unit(&v_) < A_REAL_EPS) { return A_FAILURE; }
    a_vector3_cross(&u_, &v_, &n_);
    if (a_vector3_unit(&n_) >= 1 - A_REAL_EPS)
    {
        ctx->dir_ = n_;
        ctx->u_ = u_;
        ctx->v_ = v_;
        return A_SUCCESS;
    }
    return A_FAILURE;
}

int a_plane_set_u(a_plane *ctx, a_vector3 const *n, a_vector3 const *u)
{
    a_vector3 u_, v_;
    a_vector3_cross(n, u, &v_);
    if (a_vector3_unit(&v_) < A_REAL_EPS) { return A_FAILURE; }
    a_vector3_cross(&v_, n, &u_);
    if (a_vector3_unit(&u_) < A_REAL_EPS) { return A_FAILURE; }
    a_vector3_cross(&u_, &v_, &ctx->dir_);
    ctx->u_ = u_;
    ctx->v_ = v_;
    return A_SUCCESS;
}

int a_plane_set_v(a_plane *ctx, a_vector3 const *n, a_vector3 const *v)
{
    a_vector3 u_, v_;
    a_vector3_cross(v, n, &u_);
    if (a_vector3_unit(&u_) < A_REAL_EPS) { return A_FAILURE; }
    a_vector3_cross(n, &u_, &v_);
    if (a_vector3_unit(&v_) < A_REAL_EPS) { return A_FAILURE; }
    a_vector3_cross(&u_, &v_, &ctx->dir_);
    ctx->u_ = u_;
    ctx->v_ = v_;
    return A_SUCCESS;
}

int a_plane_set(a_plane *ctx, a_point3 const *p, a_vector3 const *n)
{
    if (a_plane_set_dir(ctx, n->x, n->y, n->z) == 0)
    {
        ctx->orig.x = p->x;
        ctx->orig.y = p->y;
        ctx->orig.z = p->z;
        return A_SUCCESS;
    }
    return A_FAILURE;
}

int a_plane_set3(a_plane *ctx, a_point3 const *p1, a_point3 const *p2, a_point3 const *p3)
{
    a_point3 o;
    a_vector3 v12, v13, n;
    a_real a, b, c, d, u, v;
    a_vector3_set(&v12, p1, p2);
    a_vector3_set(&v13, p1, p3);
    a = a_vector3_dot(&v12, &v12);
    b = a_vector3_dot(&v12, &v13);
    c = a_vector3_dot(&v13, &v13);
    d = a * c - b * b;
    if (A_ABS(d) >= A_REAL_EPS)
    {
        d = A_REAL_C(0.5) / d;
        u = c * (a - b) * d;
        v = a * (c - b) * d;
        o.x = p1->x + u * v12.x + v * v13.x;
        o.y = p1->y + u * v12.y + v * v13.y;
        o.z = p1->z + u * v12.z + v * v13.z;
        a_vector3_set(&n, p2, p3);
        a_vector3_cross(&v12, &n, &n);
        a_vector3_set(&v12, &o, p1);
        if (a_plane_set_u(ctx, &n, &v12) == 0)
        {
            ctx->orig.x = o.x;
            ctx->orig.y = o.y;
            ctx->orig.z = o.z;
            return A_SUCCESS;
        }
    }
    return A_FAILURE;
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
    else if (s >= A_REAL_EPS)
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

a_real a_plane_sdist(a_plane const *ctx, a_point3 const *rhs)
{
    a_vector3 v;
    a_vector3_set(&v, &ctx->orig, rhs);
    return a_vector3_dot(&v, &ctx->dir_);
}

a_real a_plane_dist(a_plane const *ctx, a_point3 const *rhs)
{
    a_real const r = a_plane_sdist(ctx, rhs);
    return A_ABS(r);
}

int a_plane_int0(a_plane const *ctx, a_point3 const *rhs, a_real *u, a_real *v)
{
    a_real w;
    a_vector3 vec;
    a_vector3_set(&vec, &ctx->orig, rhs);
    w = a_vector3_dot(&vec, &ctx->dir_);
    if (A_ABS(w) < A_REAL_TOL)
    {
        *u = a_vector3_dot(&vec, &ctx->u_);
        *v = a_vector3_dot(&vec, &ctx->v_);
        return 1;
    }
    return 0;
}

int a_plane_int1(a_plane const *ctx, a_line3 const *rhs, a_real min, a_real max, a_real *w)
{
    a_real s, u;
    a_vector3 v;
    a_vector3_set(&v, &rhs->orig, &ctx->orig);
    u = a_vector3_dot(&ctx->dir_, &rhs->dir_);
    s = a_vector3_dot(&ctx->dir_, &v);
    if (A_ABS(u) >= A_REAL_TOL)
    {
        *w = s / u;
        if (*w - min > -A_REAL_TOL &&
            *w - max < +A_REAL_TOL)
        {
            return 1;
        }
    }
    else if (A_ABS(s) < A_REAL_TOL)
    {
        return 2;
    }
    return 0;
}

int a_plane_int2(a_plane const *ctx, a_plane const *rhs, a_line3 *res)
{
    a_real w;
    a_vector3 *v3 = &res->dir_;
    a_point3 const *p1 = &ctx->orig, *p2 = &rhs->orig;
    a_vector3 const *v1 = &ctx->dir_, *v2 = &rhs->dir_;
    a_vector3_cross(v1, v2, v3);
    w = a_vector3_norm2(v3);
    if (w >= A_REAL_TOL)
    {
        a_real u, v;
        a_vector3 v23, v31;
        a_point3 *p3 = &res->orig;
        u = a_vector3_dot((a_vector3 const *)p1, v1);
        v = a_vector3_dot((a_vector3 const *)p2, v2);
        a_vector3_cross(v2, v3, &v23);
        a_vector3_cross(v3, v1, &v31);
        p3->x = v23.x * u + v31.x * v;
        p3->y = v23.y * u + v31.y * v;
        p3->z = v23.z * u + v31.z * v;
        if (w != 1)
        {
            w = 1 / w;
            p3->x *= w;
            p3->y *= w;
            p3->z *= w;
            w = a_real_sqrt(w);
            v3->x *= w;
            v3->y *= w;
            v3->z *= w;
        }
        res->max = 1;
        return 1;
    }
    a_vector3_set(v3, p1, p2);
    w = a_vector3_dot(v1, v3);
    if (A_ABS(w) < A_REAL_TOL)
    {
        return 2;
    }
    return 0;
}

void a_plane_rot2d(a_plane *ctx, a_real angle)
{
    a_vector3 *u = &ctx->u_, *v = &ctx->v_;
    a_vector3_rot2d(u, v, angle, u, v);
}
