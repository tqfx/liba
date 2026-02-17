#include "a/bounding.h"

int a_bounding_box2(a_point2 const *i_p, a_size i_n,
                    a_real *xmin_, a_real *xmax_,
                    a_real *ymin_, a_real *ymax_)
{
    a_real xmin = +A_REAL_INF, xmax = -A_REAL_INF;
    a_real ymin = +A_REAL_INF, ymax = -A_REAL_INF;
    for (; i_n; --i_n, ++i_p)
    {
        if (i_p->x < xmin) { xmin = i_p->x; }
        if (i_p->x > xmax) { xmax = i_p->x; }
        if (i_p->y < ymin) { ymin = i_p->y; }
        if (i_p->y > ymax) { ymax = i_p->y; }
    }
    if (xmin <= xmax && ymin <= ymax)
    {
        if (xmin_) { *xmin_ = xmin; }
        if (xmax_) { *xmax_ = xmax; }
        if (ymin_) { *ymin_ = ymin; }
        if (ymax_) { *ymax_ = ymax; }
        return A_SUCCESS;
    }
    return A_FAILURE;
}

int a_bounding_box3(a_point3 const *i_p, a_size i_n,
                    a_real *xmin_, a_real *xmax_,
                    a_real *ymin_, a_real *ymax_,
                    a_real *zmin_, a_real *zmax_)
{
    a_real xmin = +A_REAL_INF, xmax = -A_REAL_INF;
    a_real ymin = +A_REAL_INF, ymax = -A_REAL_INF;
    a_real zmin = +A_REAL_INF, zmax = -A_REAL_INF;
    for (; i_n; --i_n, ++i_p)
    {
        if (i_p->x < xmin) { xmin = i_p->x; }
        if (i_p->x > xmax) { xmax = i_p->x; }
        if (i_p->y < ymin) { ymin = i_p->y; }
        if (i_p->y > ymax) { ymax = i_p->y; }
        if (i_p->z < zmin) { zmin = i_p->z; }
        if (i_p->z > zmax) { zmax = i_p->z; }
    }
    if (xmin <= xmax && ymin <= ymax && zmin <= zmax)
    {
        if (xmin_) { *xmin_ = xmin; }
        if (xmax_) { *xmax_ = xmax; }
        if (ymin_) { *ymin_ = ymin; }
        if (ymax_) { *ymax_ = ymax; }
        if (zmin_) { *zmin_ = zmin; }
        if (zmax_) { *zmax_ = zmax; }
        return A_SUCCESS;
    }
    return A_FAILURE;
}

#include "a/convexhull.h"

a_size a_bounding_obb2(a_point2 *i_p, a_size i_n, a_point2 *o_p, a_size o_n,
                       a_point2 *o, a_vector2 *u, a_vector2 *v, a_real *umax, a_real *vmax)
{
    a_real uv_min = A_REAL_INF;
    a_size iumax = 0, ivmax = 0, iumin = 0, i;
    o_n = a_convexhull2(i_p, i_n, o_p, o_n, 'y', 0);
    for (i = 1; i < o_n; ++i)
    {
        a_point2 const *p = o_p + i;
        if (p->x > o_p[iumax].x) { iumax = i; }
        if (p->y > o_p[ivmax].y) { ivmax = i; }
        if (p->x < o_p[iumin].x) { iumin = i; }
    }
    if (o_n)
    {
        a_point2_set_val(o, o_p[iumin].x, o_p[0].y);
        a_vector2_set_val(u, 1, 0);
        a_vector2_set_val(v, 0, 1);
        *umax = o_p[iumax].x - o->x;
        *vmax = o_p[ivmax].y - o->y;
        uv_min = *umax * *vmax;
    }
    for (i = 0; i < o_n; ++i)
    {
        a_point2 const *p = o_p + i;
        a_vector2 u_, v_;
        a_real umax_, vmax_, umin_, uv;
        a_real new_umax, new_vmax, new_umin;
        a_size new_iumax, new_ivmax, new_iumin;
        a_vector2_set(&u_, p, o_p + (i + 1) % o_n);
        if (a_vector2_unit(&u_) < A_REAL_EPSILON)
        {
            a_vector2_set_val(&u_, 1, 0);
        }
        a_vector2_set_val(&v_, -u_.y, u_.x);
        umax_ = (o_p[iumax].x - p->x) * u_.x + (o_p[iumax].y - p->y) * u_.y;
        new_iumax = (iumax + 1) % o_n;
        new_umax = (o_p[new_iumax].x - p->x) * u_.x + (o_p[new_iumax].y - p->y) * u_.y;
        while (new_umax > umax_)
        {
            umax_ = new_umax;
            iumax = new_iumax;
            new_iumax = (iumax + 1) % o_n;
            new_umax = (o_p[new_iumax].x - p->x) * u_.x + (o_p[new_iumax].y - p->y) * u_.y;
        }
        vmax_ = (o_p[ivmax].x - p->x) * v_.x + (o_p[ivmax].y - p->y) * v_.y;
        new_ivmax = (ivmax + 1) % o_n;
        new_vmax = (o_p[new_ivmax].x - p->x) * v_.x + (o_p[new_ivmax].y - p->y) * v_.y;
        while (new_vmax > vmax_)
        {
            vmax_ = new_vmax;
            ivmax = new_ivmax;
            new_ivmax = (ivmax + 1) % o_n;
            new_vmax = (o_p[new_ivmax].x - p->x) * v_.x + (o_p[new_ivmax].y - p->y) * v_.y;
        }
        umin_ = (o_p[iumin].x - p->x) * u_.x + (o_p[iumin].y - p->y) * u_.y;
        new_iumin = (iumin + 1) % o_n;
        new_umin = (o_p[new_iumin].x - p->x) * u_.x + (o_p[new_iumin].y - p->y) * u_.y;
        while (new_umin < umin_)
        {
            umin_ = new_umin;
            iumin = new_iumin;
            new_iumin = (iumin + 1) % o_n;
            new_umin = (o_p[new_iumin].x - p->x) * u_.x + (o_p[new_iumin].y - p->y) * u_.y;
        }
        uv = (umax_ - umin_) * vmax_;
        if (uv < uv_min)
        {
            o->x = p->x + u_.x * umin_;
            o->y = p->y + u_.y * umin_;
            *u = u_;
            *v = v_;
            *umax = umax_ - umin_;
            *vmax = vmax_;
            uv_min = uv;
        }
    }
    return o_n;
}
