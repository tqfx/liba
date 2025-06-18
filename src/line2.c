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
    a_real const x = q->x - p->x, y = q->y - p->y;
    if (a_line2_set_dir(ctx, x, y) == 0)
    {
        a_line2_set_org(ctx, p->x, p->y);
        return A_SUCCESS;
    }
    return A_FAILURE;
}

int a_line2_setv(a_line2 *ctx, a_point2 const *p, a_vector2 const *v)
{
    if (a_line2_set_dir(ctx, v->x, v->y) == 0)
    {
        a_line2_set_org(ctx, p->x, p->y);
        return A_SUCCESS;
    }
    return A_FAILURE;
}

void a_line2_eval(a_line2 const *ctx, a_real w, a_point2 *res)
{
    a_point2 const *const o = &ctx->orig;
    a_vector2 const *const u = &ctx->dir_;
    res->x = o->x + u->x * w;
    res->y = o->y + u->y * w;
}

a_real a_line2_parm(a_line2 const *ctx, a_point2 const *p)
{
    a_vector2 v;
    a_vector2_set(&v, &ctx->orig, p);
    return a_vector2_dot(&v, &ctx->dir_);
}

a_real a_line2_proj(a_line2 const *ctx, a_point2 const *p, a_point2 *res)
{
    a_real w = a_line2_parm(ctx, p);
    a_line2_eval(ctx, w, res);
    return w;
}

a_real a_line2_sdist(a_line2 const *ctx, a_point2 const *rhs)
{
    a_point2 const *const o = &ctx->orig;
    a_vector2 const *const u = &ctx->dir_;
    a_vector2 v;
    a_vector2_set(&v, o, rhs);
    return a_vector2_cross(u, &v);
}

a_real a_line2_dist(a_line2 const *ctx, a_point2 const *rhs)
{
    a_real const r = a_line2_sdist(ctx, rhs);
    return A_ABS(r);
}

int a_line2_int0(a_line2 const *ctx, a_point2 const *rhs, a_real min, a_real max, a_real *w)
{
    a_point2 const *const o = &ctx->orig;
    a_vector2 const *const u = &ctx->dir_;
    a_vector2 v;
    a_vector2_set(&v, o, rhs);
    if (a_vector2_ispar(&v, u))
    {
        *w = a_vector2_dot(&v, u);
        if (*w > min - A_REAL_EPS &&
            *w < max + A_REAL_EPS)
        {
            return 1;
        }
    }
    return 0;
}

int a_line2_int1(a_line2 const *ctx, a_line2 const *rhs,
                 a_real min1, a_real max1, a_real min2, a_real max2,
                 a_real *w1, a_real *w2)
{
    a_vector2 v;
    a_real const z = a_vector2_cross(&ctx->dir_, &rhs->dir_);
    a_vector2_set(&v, &ctx->orig, &rhs->orig);
    if (A_ABS(z) >= A_REAL_EPS)
    {
        *w1 = a_vector2_cross(&v, &rhs->dir_) / z;
        *w2 = a_vector2_cross(&v, &ctx->dir_) / z;
        if (*w1 > min1 - A_REAL_EPS &&
            *w1 < max1 + A_REAL_EPS &&
            *w2 > min2 - A_REAL_EPS &&
            *w2 < max2 + A_REAL_EPS) { return 1; }
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

void a_line2_rot(a_line2 const *ctx, a_point2 const *rhs, a_real angle, a_line2 *res)
{
    a_real const s = a_real_sin(angle);
    a_real const c = a_real_cos(angle);
    a_vector2 vec;
    a_vector2_rot_(&ctx->dir_, s, c, &res->dir_);
    a_vector2_set(&vec, rhs, &ctx->orig);
    a_vector2_rot_(&vec, s, c, &vec);
    a_point2_add(rhs, &vec, &res->orig);
    res->max = ctx->max;
}
