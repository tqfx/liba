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

void a_point3_lerp(a_point3 const *lhs, a_point3 const *rhs, a_real val, a_point3 *res)
{
    res->x = lhs->x + (rhs->x - lhs->x) * val;
    res->y = lhs->y + (rhs->y - lhs->y) * val;
    res->z = lhs->z + (rhs->z - lhs->z) * val;
}

a_real a_point3_tricir(a_point3 const *p1, a_point3 const *p2, a_point3 const *p3, a_point3 *pc)
{
    a_real r = a_point3_tricir2(p1, p2, p3, pc);
    return a_real_sqrt(r);
}

a_real a_point3_tricir2(a_point3 const *p1, a_point3 const *p2, a_point3 const *p3, a_point3 *pc)
{
    a_vector3 v12, v13;
    a_real a, b, c, d, u, v;
    a_vector3_set(&v12, p1, p2);
    a_vector3_set(&v13, p1, p3);
    a = a_vector3_dot(&v12, &v12);
    b = a_vector3_dot(&v12, &v13);
    c = a_vector3_dot(&v13, &v13);
    d = a * c - b * b;
    if (A_ABS(d) >= A_REAL_EPS)
    {
        d = A_REAL_C(0.5) / d;
        u = c * (a - b) * d;
        v = a * (c - b) * d;
        pc->x = p1->x + u * v12.x + v * v13.x;
        pc->y = p1->y + u * v12.y + v * v13.y;
        pc->z = p1->z + u * v12.z + v * v13.z;
        return a_point3_dist2(pc, p1);
    }
    return 0;
}

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */
#if A_PREREQ_MSVC(19, 30)
#pragma warning(disable : 5250)
#endif /* msvc 17.0+ */

int a_point3_cmpxy(a_point3 const *lhs, a_point3 const *rhs)
{
    if (lhs->x != rhs->x) { return A_SGN_(lhs->x, rhs->x); }
    if (lhs->y != rhs->y) { return A_SGN_(lhs->y, rhs->y); }
    return A_SGN_(lhs->z, rhs->z);
}

int a_point3_cmpyx(a_point3 const *lhs, a_point3 const *rhs)
{
    if (lhs->y != rhs->y) { return A_SGN_(lhs->y, rhs->y); }
    if (lhs->x != rhs->x) { return A_SGN_(lhs->x, rhs->x); }
    return A_SGN_(lhs->z, rhs->z);
}
