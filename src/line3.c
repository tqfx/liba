#include "a/line3.h"

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

int a_line3_set_dir(a_line3 *ctx, a_real x, a_real y, a_real z)
{
    a_real s = x * x + y * y + z * z;
    if (s == 1)
    {
        ctx->max = 1;
        ctx->dir_.x = x;
        ctx->dir_.y = y;
        ctx->dir_.z = z;
    }
    else if (s > 0)
    {
        ctx->max = a_real_sqrt(s);
        s = 1 / ctx->max;
        ctx->dir_.x = x * s;
        ctx->dir_.y = y * s;
        ctx->dir_.z = z * s;
    }
    else { return A_FAILURE; }
    return A_SUCCESS;
}

int a_line3_set_tgt(a_line3 *ctx, a_real x, a_real y, a_real z)
{
    x -= ctx->orig.x;
    y -= ctx->orig.y;
    z -= ctx->orig.z;
    return a_line3_set_dir(ctx, x, y, z);
}

int a_line3_set(a_line3 *ctx, a_point3 const *p, a_point3 const *q)
{
    a_line3_set_org(ctx, p->x, p->y, p->z);
    return a_line3_set_tgt(ctx, q->x, q->y, q->z);
}

int a_line3_setv(a_line3 *ctx, a_point3 const *p, a_vector3 const *v)
{
    a_line3_set_org(ctx, p->x, p->y, p->z);
    return a_line3_set_dir(ctx, v->x, v->y, v->z);
}

void a_line3_eval(a_line3 const *ctx, a_real w, a_point3 *res)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir_;
    res->x = o->x + u->x * w;
    res->y = o->y + u->y * w;
    res->z = o->z + u->z * w;
}

a_real a_line3_parm(a_line3 const *ctx, a_point3 const *p)
{
    a_vector3 v;
    a_vector3_set(&v, &ctx->orig, p);
    return a_vector3_dot(&v, &ctx->dir_);
}

a_real a_line3_proj(a_line3 const *ctx, a_point3 const *p, a_point3 *res)
{
    a_real w = a_line3_parm(ctx, p);
    a_line3_eval(ctx, w, res);
    return w;
}

a_real a_line3_dist(a_line3 const *ctx, a_point3 const *rhs)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir_;
    a_vector3 v;
    a_vector3_set(&v, o, rhs);
    a_vector3_cross(&v, u, &v);
    return a_vector3_norm(&v);
}

a_real a_line3_dist1(a_line3 const *ctx, a_point3 const *rhs)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir_;
    a_vector3 v;
    a_vector3_set(&v, o, rhs);
    a_vector3_cross(&v, u, &v);
    return a_vector3_norm1(&v);
}

a_real a_line3_dist2(a_line3 const *ctx, a_point3 const *rhs)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir_;
    a_vector3 v;
    a_vector3_set(&v, o, rhs);
    a_vector3_cross(&v, u, &v);
    return a_vector3_norm2(&v);
}

int a_line3_int0(a_line3 const *ctx, a_point3 const *rhs, a_real min, a_real max, a_real *w)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir_;
    a_vector3 v;
    a_vector3_set(&v, o, rhs);
    if (a_vector3_ispar(&v, u))
    {
        *w = a_vector3_dot(&v, u);
        if (*w > min - A_REAL_EPS &&
            *w < max + A_REAL_EPS)
        {
            return 1;
        }
    }
    return 0;
}

int a_line3_int1(a_line3 const *ctx, a_line3 const *rhs,
                 a_real min1, a_real max1, a_real min2, a_real max2,
                 a_real *w1, a_real *w2)
{
    a_vector3 p12, v12, v;
    a_vector3_set(&p12, &ctx->orig, &rhs->orig);
    a_vector3_cross(&ctx->dir_, &rhs->dir_, &v12);
    if (A_ABS(v12.x) >= A_REAL_EPS ||
        A_ABS(v12.y) >= A_REAL_EPS ||
        A_ABS(v12.z) >= A_REAL_EPS)
    {
        if (a_vector3_isver(&p12, &v12))
        {
            a_real const s = 1 / a_vector3_norm2(&v12);
            a_vector3_cross(&p12, &rhs->dir_, &v);
            *w1 = a_vector3_dot(&v, &v12) * s;
            a_vector3_cross(&p12, &ctx->dir_, &v);
            *w2 = a_vector3_dot(&v, &v12) * s;
            if (*w1 > min1 - A_REAL_EPS &&
                *w1 < max1 + A_REAL_EPS &&
                *w2 > min2 - A_REAL_EPS &&
                *w2 < max2 + A_REAL_EPS) { return 1; }
        }
    }
    else if (a_vector3_ispar(&ctx->dir_, &p12))
    {
        a_real const s = a_vector3_dot(&ctx->dir_, &rhs->dir_);
        a_real const w = a_vector3_dot(&ctx->dir_, &p12);
        if (s < 0)
        {
            a_real const min = min2;
            a_real const max = max2;
            min2 = w - max;
            max2 = w - min;
        }
        else
        {
            min2 += w;
            max2 += w;
        }
        *w1 = (min2 > min1 ? min2 : min1);
        *w2 = (max2 < max1 ? max2 : max1);
        if (*w2 - *w1 >= A_REAL_EPS) { return 2; }
        if (*w2 - *w1 > -A_REAL_EPS)
        {
            *w1 = (*w1 + *w2) * A_REAL_C(0.5);
            *w2 = s < 0 ? (w - *w1) : (*w1 - w);
            return 1;
        }
    }
    return 0;
}
