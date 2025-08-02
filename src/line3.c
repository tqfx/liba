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
    a_real const x = q->x - p->x, y = q->y - p->y, z = q->z - p->z;
    if (a_line3_set_dir(ctx, x, y, z) == 0)
    {
        a_line3_set_org(ctx, p->x, p->y, p->z);
        return A_SUCCESS;
    }
    return A_FAILURE;
}

int a_line3_setv(a_line3 *ctx, a_point3 const *p, a_vector3 const *v)
{
    if (a_line3_set_dir(ctx, v->x, v->y, v->z) == 0)
    {
        a_line3_set_org(ctx, p->x, p->y, p->z);
        return A_SUCCESS;
    }
    return A_FAILURE;
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
a_real a_line3_limparm(a_line3 const *ctx, a_real min, a_real max, a_point3 const *p)
{
    a_real w = a_line3_parm(ctx, p);
    if (min <= max)
    {
        if (w < min) { w = min; }
        if (w > max) { w = max; }
    }
    else if (min > max)
    {
        if (w > min) { w = min; }
        if (w < max) { w = max; }
    }
    return w;
}

a_real a_line3_proj(a_line3 const *ctx, a_point3 const *p, a_point3 *res)
{
    a_real w = a_line3_parm(ctx, p);
    a_line3_eval(ctx, w, res);
    return w;
}
a_real a_line3_limproj(a_line3 const *ctx, a_real min, a_real max, a_point3 const *p, a_point3 *res)
{
    a_real w = a_line3_limparm(ctx, min, max, p);
    a_line3_eval(ctx, w, res);
    return w;
}

void a_line3_sdist(a_line3 const *ctx, a_point3 const *rhs, a_vector3 *res)
{
    a_vector3 v;
    a_vector3_set(&v, &ctx->orig, rhs);
    a_vector3_cross(&ctx->dir_, &v, res);
}

a_real a_line3_dist(a_line3 const *ctx, a_point3 const *rhs)
{
    a_vector3 v;
    a_line3_sdist(ctx, rhs, &v);
    return a_vector3_norm(&v);
}

a_real a_line3_dist1(a_line3 const *ctx, a_point3 const *rhs)
{
    a_vector3 v;
    a_line3_sdist(ctx, rhs, &v);
    return a_vector3_norm1(&v);
}

a_real a_line3_dist2(a_line3 const *ctx, a_point3 const *rhs)
{
    a_vector3 v;
    a_line3_sdist(ctx, rhs, &v);
    return a_vector3_norm2(&v);
}

a_real a_line3_limdist(a_line3 const *ctx, a_real min, a_real max, a_point3 const *rhs, a_real *w, a_point3 *res)
{
    *w = a_line3_limproj(ctx, min, max, rhs, res);
    return a_point3_dist(rhs, res);
}

a_real a_line3_limdist1(a_line3 const *ctx, a_real min, a_real max, a_point3 const *rhs, a_real *w, a_point3 *res)
{
    *w = a_line3_limproj(ctx, min, max, rhs, res);
    return a_point3_dist1(rhs, res);
}

a_real a_line3_limdist2(a_line3 const *ctx, a_real min, a_real max, a_point3 const *rhs, a_real *w, a_point3 *res)
{
    *w = a_line3_limproj(ctx, min, max, rhs, res);
    return a_point3_dist2(rhs, res);
}

a_real a_line3_segdist(a_line3 const *ctx, a_line3 const *rhs,
                       a_real min1, a_real max1, a_real min2, a_real max2,
                       a_real *w1, a_real *w2, a_point3 *p1, a_point3 *p2)
{
    a_real s = a_line3_segdist2(ctx, rhs, min1, max1, min2, max2, w1, w2, p1, p2);
    return a_real_sqrt(s);
}

a_real a_line3_segdist2(a_line3 const *ctx, a_line3 const *rhs,
                        a_real min1, a_real max1, a_real min2, a_real max2,
                        a_real *w1, a_real *w2, a_point3 *p1, a_point3 *p2)
{
    a_real res, w12, v12;
    a_point3 pt1, pt2;
    if (min1 > max1)
    {
        w12 = min1;
        min1 = max1;
        max1 = w12;
    }
    if (min2 > max2)
    {
        w12 = min2;
        min2 = max2;
        max2 = w12;
    }
    v12 = a_vector3_dot(&ctx->dir_, &rhs->dir_);
    if (A_ABS(v12) < 1 - A_REAL_EPS2)
    {
        int win = 1;
        a_vector3 p12;
        a_real pv1, pv2;
        a_real const s = 1 / (1 - v12 * v12);
        a_vector3_set(&p12, &ctx->orig, &rhs->orig);
        pv1 = a_vector3_dot(&p12, &ctx->dir_);
        pv2 = a_vector3_dot(&p12, &rhs->dir_);
        *w1 = (pv1 - pv2 * v12) * s;
        *w2 = (pv1 * v12 - pv2) * s;
        if (*w1 < min1)
        {
            *w1 = min1;
            win = 0;
        }
        else if (*w1 > max1)
        {
            *w1 = max1;
            win = 0;
        }
        if (*w2 < min2)
        {
            *w2 = min2;
            win = 0;
        }
        else if (*w2 > max2)
        {
            *w2 = max2;
            win = 0;
        }
        a_line3_eval(ctx, *w1, p1);
        a_line3_eval(rhs, *w2, p2);
        if (win) { return a_point3_dist2(p1, p2); }
        res = a_line3_limdist2(rhs, min2, max2, p1, &pv2, &pt2);
        v12 = a_line3_limdist2(ctx, min1, max1, p2, &pv1, &pt1);
        if (v12 < res)
        {
            res = v12;
            *w1 = pv1;
            *p1 = pt1;
        }
        else
        {
            *w2 = pv2;
            *p2 = pt2;
        }
        return res;
    }
    *w1 = min1;
    a_line3_eval(ctx, min1, p1);
    res = a_line3_limdist2(rhs, min2, max2, p1, w2, p2);
    a_line3_eval(ctx, max1, &pt1);
    v12 = a_line3_limdist2(rhs, min2, max2, &pt1, &w12, &pt2);
    if (v12 < res)
    {
        res = v12;
        *w1 = max1;
        *w2 = w12;
        *p1 = pt1;
        *p2 = pt2;
    }
    a_line3_eval(rhs, min2, &pt2);
    v12 = a_line3_limdist2(ctx, min1, max1, &pt2, &w12, &pt1);
    if (v12 < res)
    {
        res = v12;
        *w1 = w12;
        *w2 = min2;
        *p1 = pt1;
        *p2 = pt2;
    }
    a_line3_eval(rhs, max2, &pt2);
    v12 = a_line3_limdist2(ctx, min1, max1, &pt2, &w12, &pt1);
    if (v12 < res)
    {
        res = v12;
        *w1 = w12;
        *w2 = max2;
        *p1 = pt1;
        *p2 = pt2;
    }
    return res;
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
            if (s < 0) { *w2 = w - *w1; }
            else { *w2 = *w1 - w; }
            return 1;
        }
    }
    return 0;
}

void a_line3_rot(a_line3 const *ctx, a_line3 const *rhs, a_real angle, a_line3 *res)
{
    a_real const s = a_real_sin(angle);
    a_real const c = a_real_cos(angle);
    a_vector3 vec;
    a_vector3_rot_(&ctx->dir_, &rhs->dir_, s, c, &res->dir_);
    a_vector3_set(&vec, &rhs->orig, &ctx->orig);
    a_vector3_rot_(&vec, &rhs->dir_, s, c, &vec);
    a_point3_add(&rhs->orig, &vec, &res->orig);
    res->max = ctx->max;
}
