#include "a/line3.h"

int a_line3_set(a_line3 *ctx, a_point3 const *p, a_point3 const *q)
{
    a_vector3 v;
    a_vector3_set(&v, p, q);
    return a_line3_setv(ctx, p, &v);
}

int a_line3_setv(a_line3 *ctx, a_point3 const *p, a_vector3 const *v)
{
    a_real const max = a_real_norm3(v->x, v->y, v->z);
    if (max > 0)
    {
        ctx->orig.x = p->x;
        ctx->orig.y = p->y;
        ctx->orig.z = p->z;
        ctx->dir.x = v->x / max;
        ctx->dir.y = v->y / max;
        ctx->dir.z = v->z / max;
        ctx->max = max;
        return A_SUCCESS;
    }
    return A_FAILURE;
}

void a_line3_eval(a_line3 const *ctx, a_real w, a_point3 *res)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir;
    res->x = o->x + u->x * w;
    res->y = o->y + u->y * w;
    res->z = o->z + u->z * w;
}

a_real a_line3_proj(a_line3 const *ctx, a_point3 const *p, a_point3 *q)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir;
    a_real w;
    a_vector3 vec;
    a_vector3_set(&vec, o, p);
    w = a_vector3_dot(&vec, u);
    q->x = o->x + u->x * w;
    q->y = o->y + u->y * w;
    q->z = o->z + u->z * w;
    return w;
}

a_real a_line3_dist(a_line3 const *ctx, a_point3 const *p)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir;
    a_vector3 v;
    a_vector3_set(&v, o, p);
    a_vector3_cross(&v, u, &v);
    return a_vector3_norm(&v);
}

a_real a_line3_dist1(a_line3 const *ctx, a_point3 const *p)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir;
    a_vector3 v;
    a_vector3_set(&v, o, p);
    a_vector3_cross(&v, u, &v);
    return a_vector3_norm1(&v);
}

a_real a_line3_dist2(a_line3 const *ctx, a_point3 const *p)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir;
    a_vector3 v;
    a_vector3_set(&v, o, p);
    a_vector3_cross(&v, u, &v);
    return a_vector3_norm2(&v);
}
