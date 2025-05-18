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
    a_vector2 vec;
    a_vector2_set(&vec, o, p);
    w = a_vector2_dot(&vec, u);
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
