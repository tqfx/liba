#define LIBA_POINT2_C
#include "a/point2.h"

a_real a_point2_dist(a_point2 const *lhs, a_point2 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    return a_real_sqrt(x * x + y * y);
}

a_real a_point2_dist2(a_point2 const *lhs, a_point2 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    return x * x + y * y;
}

a_real a_point2_mindist(a_point2 const *ctx, a_point2 const *i_p, a_size i_n,
                        a_point2 *o_p /*=A_NULL*/, a_size *o_i /*=A_NULL*/)
{
    a_real val = +A_REAL_INF, d;
    a_size idx = A_SIZE_MAX, i;
    for (i = 0; i < i_n; ++i)
    {
        d = a_point2_dist2(ctx, i_p + i);
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

a_real a_point2_maxdist(a_point2 const *ctx, a_point2 const *i_p, a_size i_n,
                        a_point2 *o_p /*=A_NULL*/, a_size *o_i /*=A_NULL*/)
{
    a_real val = -A_REAL_INF, d;
    a_size idx = A_SIZE_MAX, i;
    for (i = 0; i < i_n; ++i)
    {
        d = a_point2_dist2(ctx, i_p + i);
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
