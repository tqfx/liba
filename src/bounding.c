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
