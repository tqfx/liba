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

void a_point2_lerp(a_point2 const *lhs, a_point2 const *rhs, a_real val, a_point2 *res)
{
    res->x = lhs->x + (rhs->x - lhs->x) * val;
    res->y = lhs->y + (rhs->y - lhs->y) * val;
}

a_real a_point2_tricir(a_point2 const *p1, a_point2 const *p2, a_point2 const *p3, a_point2 *pc)
{
    a_real r = a_point2_tricir2(p1, p2, p3, pc);
    return a_real_sqrt(r);
}

a_real a_point2_tricir2(a_point2 const *p1, a_point2 const *p2, a_point2 const *p3, a_point2 *pc)
{
    a_real const x21 = p2->x - p1->x, y21 = p2->y - p1->y;
    a_real const x31 = p3->x - p1->x, y31 = p3->y - p1->y;
    a_real d = x21 * y31 - y21 * x31;
    if (A_ABS(d) >= A_REAL_EPS)
    {
        a_real const b21 = x21 * (p2->x + p1->x) + y21 * (p2->y + p1->y);
        a_real const b31 = x31 * (p3->x + p1->x) + y31 * (p3->y + p1->y);
        d = A_REAL_C(0.5) / d;
        pc->x = (b21 * y31 - y21 * b31) * d;
        pc->y = (x21 * b31 - b21 * x31) * d;
        return a_point2_dist2(pc, p1);
    }
    return 0;
}

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */
#if A_PREREQ_MSVC(19, 30)
#pragma warning(disable : 5250)
#endif /* msvc 17.0+ */

int a_point2_cmpx(a_point2 const *lhs, a_point2 const *rhs)
{
    if (lhs->x != rhs->x) { return A_SGN_(lhs->x, rhs->x); }
    return A_SGN_(lhs->y, rhs->y);
}

int a_point2_cmpy(a_point2 const *lhs, a_point2 const *rhs)
{
    if (lhs->y != rhs->y) { return A_SGN_(lhs->y, rhs->y); }
    return A_SGN_(lhs->x, rhs->x);
}
