#include "a/line2.h"

int a_line2_set_dir(a_line2 *ctx, a_real x, a_real y)
{
    ctx->max = a_real_hypot(x, y);
    if (ctx->max > 0)
    {
        ctx->dir_.x = x / ctx->max;
        ctx->dir_.y = y / ctx->max;
        return A_SUCCESS;
    }
    return A_FAILURE;
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
