#include "a/line3.h"

int a_line3_set_dir(a_line3 *ctx, a_real x, a_real y, a_real z)
{
    ctx->max = a_real_norm3(x, y, z);
    if (ctx->max > 0)
    {
        ctx->dir_.x = x / ctx->max;
        ctx->dir_.y = y / ctx->max;
        ctx->dir_.z = z / ctx->max;
        return A_SUCCESS;
    }
    return A_FAILURE;
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

a_real a_line3_proj(a_line3 const *ctx, a_point3 const *p, a_point3 *res)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir_;
    a_real w;
    a_vector3 vec;
    a_vector3_set(&vec, o, p);
    w = a_vector3_dot(&vec, u);
    res->x = o->x + u->x * w;
    res->y = o->y + u->y * w;
    res->z = o->z + u->z * w;
    return w;
}

a_real a_line3_dist(a_line3 const *ctx, a_point3 const *p)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir_;
    a_vector3 v;
    a_vector3_set(&v, o, p);
    a_vector3_cross(&v, u, &v);
    return a_vector3_norm(&v);
}

a_real a_line3_dist1(a_line3 const *ctx, a_point3 const *p)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir_;
    a_vector3 v;
    a_vector3_set(&v, o, p);
    a_vector3_cross(&v, u, &v);
    return a_vector3_norm1(&v);
}

a_real a_line3_dist2(a_line3 const *ctx, a_point3 const *p)
{
    a_point3 const *const o = &ctx->orig;
    a_vector3 const *const u = &ctx->dir_;
    a_vector3 v;
    a_vector3_set(&v, o, p);
    a_vector3_cross(&v, u, &v);
    return a_vector3_norm2(&v);
}
