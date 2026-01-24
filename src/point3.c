#define LIBA_POINT3_C
#include "a/point3.h"

a_real a_point3_dist(a_point3 const *lhs, a_point3 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    a_real const z = rhs->z - lhs->z;
    return a_real_sqrt(x * x + y * y + z * z);
}

a_real a_point3_dist2(a_point3 const *lhs, a_point3 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    a_real const z = rhs->z - lhs->z;
    return x * x + y * y + z * z;
}

a_real a_point3_mindist(a_point3 const *ctx, a_point3 const *i_p, a_size i_n,
                        a_point3 *o_p /*=A_NULL*/, a_size *o_i /*=A_NULL*/)
{
    a_real val = +A_REAL_INF, d;
    a_size idx = A_SIZE_MAX, i;
    for (i = 0; i < i_n; ++i)
    {
        d = a_point3_dist2(ctx, i_p + i);
        if (d < val)
        {
            val = d;
            idx = i;
        }
    }
    if (idx < i_n)
    {
        if (o_p) { *o_p = i_p[idx]; }
        val = a_real_sqrt(val);
    }
    if (o_i) { *o_i = idx; }
    return val;
}

a_real a_point3_maxdist(a_point3 const *ctx, a_point3 const *i_p, a_size i_n,
                        a_point3 *o_p /*=A_NULL*/, a_size *o_i /*=A_NULL*/)
{
    a_real val = -A_REAL_INF, d;
    a_size idx = A_SIZE_MAX, i;
    for (i = 0; i < i_n; ++i)
    {
        d = a_point3_dist2(ctx, i_p + i);
        if (d > val)
        {
            val = d;
            idx = i;
        }
    }
    if (idx < i_n)
    {
        if (o_p) { *o_p = i_p[idx]; }
        val = a_real_sqrt(val);
    }
    if (o_i) { *o_i = idx; }
    return val;
}
