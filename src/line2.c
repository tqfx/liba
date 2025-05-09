#include "a/line2.h"

int a_line2_set(a_line2 *ctx, a_point2 const *p, a_point2 const *q)
{
    a_vector2 v;
    a_vector2_set(&v, p, q);
    return a_line2_setv(ctx, p, &v);
}

int a_line2_setv(a_line2 *ctx, a_point2 const *p, a_vector2 const *v)
{
    a_real const max = a_real_hypot(v->x, v->y);
    if (max > 0)
    {
        ctx->orig.x = p->x;
        ctx->orig.y = p->y;
        ctx->dir.x = v->x / max;
        ctx->dir.y = v->y / max;
        ctx->max = max;
        return A_SUCCESS;
    }
    return A_FAILURE;
}

void a_line2_eval(a_line2 const *ctx, a_real w, a_point2 *res)
{
    a_point2 const *const o = &ctx->orig;
    a_vector2 const *const u = &ctx->dir;
    res->x = o->x + u->x * w;
    res->y = o->y + u->y * w;
}

a_real a_line2_proj(a_line2 const *ctx, a_point2 const *p, a_point2 *q)
{
    a_point2 const *const o = &ctx->orig;
    a_vector2 const *const u = &ctx->dir;
    a_real w;
    a_vector2 vec;
    a_vector2_set(&vec, o, p);
    w = a_vector2_dot(&vec, u);
    q->x = o->x + u->x * w;
    q->y = o->y + u->y * w;
    return w;
}

a_real a_line2_dist_(a_line2 const *ctx, a_point2 const *p)
{
    a_point2 const *const o = &ctx->orig;
    a_vector2 const *const u = &ctx->dir;
    a_vector2 v;
    a_vector2_set(&v, o, p);
    return a_vector2_cross(u, &v);
}

a_real a_line2_dist(a_line2 const *ctx, a_point2 const *p)
{
    a_real const r = a_line2_dist_(ctx, p);
    return A_ABS(r);
}
