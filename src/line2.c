#include "a/line2.h"

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

int a_line2_set_dir(a_line2 *ctx, a_real x, a_real y)
{
    a_real s = x * x + y * y;
    if (s == 1)
    {
        ctx->max = 1;
        ctx->dir_.x = x;
        ctx->dir_.y = y;
    }
    else if (s > 0)
    {
        ctx->max = a_real_sqrt(s);
        s = 1 / ctx->max;
        ctx->dir_.x = x * s;
        ctx->dir_.y = y * s;
    }
    else { return A_FAILURE; }
    return A_SUCCESS;
}

int a_line2_set_tgt(a_line2 *ctx, a_real x, a_real y)
{
    x -= ctx->orig.x;
    y -= ctx->orig.y;
    return a_line2_set_dir(ctx, x, y);
}

int a_line2_set(a_line2 *ctx, a_point2 const *p, a_point2 const *q)
{
    a_line2_set_org(ctx, p->x, p->y);
    return a_line2_set_tgt(ctx, q->x, q->y);
}

int a_line2_setv(a_line2 *ctx, a_point2 const *p, a_vector2 const *v)
{
    a_line2_set_org(ctx, p->x, p->y);
    return a_line2_set_dir(ctx, v->x, v->y);
}

void a_line2_eval(a_line2 const *ctx, a_real w, a_point2 *res)
{
    a_point2 const *const o = &ctx->orig;
    a_vector2 const *const u = &ctx->dir_;
    res->x = o->x + u->x * w;
    res->y = o->y + u->y * w;
}

a_real a_line2_proj(a_line2 const *ctx, a_point2 const *p, a_point2 *res)
{
    a_point2 const *const o = &ctx->orig;
    a_vector2 const *const u = &ctx->dir_;
    a_real w;
    a_vector2 v;
    a_vector2_set(&v, o, p);
    w = a_vector2_dot(&v, u);
    res->x = o->x + u->x * w;
    res->y = o->y + u->y * w;
    return w;
}

a_real a_line2_sdist(a_line2 const *ctx, a_point2 const *p)
{
    a_point2 const *const o = &ctx->orig;
    a_vector2 const *const u = &ctx->dir_;
    a_vector2 v;
    a_vector2_set(&v, o, p);
    return a_vector2_cross(u, &v);
}

a_real a_line2_dist(a_line2 const *ctx, a_point2 const *p)
{
    a_real const r = a_line2_sdist(ctx, p);
    return A_ABS(r);
}

int a_line2_int0(a_line2 const *ctx, a_point2 const *rhs, a_real min, a_real max, a_real *res)
{
    a_point2 const *const o = &ctx->orig;
    a_vector2 const *const u = &ctx->dir_;
    a_vector2 v;
    a_vector2_set(&v, o, rhs);
    if (a_vector2_ispar(&v, u))
    {
        *res = a_vector2_dot(&v, u);
        if (*res > min - A_REAL_EPS &&
            *res < max + A_REAL_EPS)
        {
            return 1;
        }
    }
    return 0;
}

int a_line2_int1(a_line2 const *ctx, a_line2 const *rhs,
                 a_real min1, a_real max1, a_real min2, a_real max2,
                 a_real *res1, a_real *res2)
{
    a_vector2 v;
    a_real const z = a_vector2_cross(&ctx->dir_, &rhs->dir_);
    a_vector2_set(&v, &ctx->orig, &rhs->orig);
    if (A_ABS(z) >= A_REAL_EPS)
    {
        *res1 = a_vector2_cross(&v, &rhs->dir_) / z;
        *res2 = a_vector2_cross(&v, &ctx->dir_) / z;
        if (*res1 > min1 - A_REAL_EPS &&
            *res1 < max1 + A_REAL_EPS &&
            *res2 > min2 - A_REAL_EPS &&
            *res2 < max2 + A_REAL_EPS) { return 1; }
    }
    else if (a_vector2_ispar(&ctx->dir_, &v))
    {
        a_real const s = a_vector2_dot(&ctx->dir_, &rhs->dir_);
        a_real const w = a_vector2_dot(&ctx->dir_, &v);
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
        *res1 = (min2 > min1 ? min2 : min1);
        *res2 = (max2 < max1 ? max2 : max1);
        if (*res2 - *res1 >= A_REAL_EPS) { return 2; }
        if (*res2 - *res1 > -A_REAL_EPS)
        {
            *res1 = (*res1 + *res2) * A_REAL_C(0.5);
            *res2 = s < 0 ? (w - *res1) : (*res1 - w);
            return 1;
        }
    }
    return 0;
}
