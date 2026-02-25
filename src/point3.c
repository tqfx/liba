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

a_real a_point3_tetsph(a_point3 const *p1, a_point3 const *p2, a_point3 const *p3, a_point3 const *p4,
                       a_point3 *pc)
{
    a_real r = a_point3_tetsph2(p1, p2, p3, p4, pc);
    return a_real_sqrt(r);
}
a_real a_point3_tetsph2(a_point3 const *p1, a_point3 const *p2, a_point3 const *p3, a_point3 const *p4,
                        a_point3 *pc)
{
    a_real d;
    a_vector3 v12, v13, v14, v23;
    a_vector3_set(&v12, p1, p2);
    a_vector3_set(&v13, p1, p3);
    a_vector3_set(&v14, p1, p4);
    a_vector3_cross(&v12, &v13, &v23);
    d = a_vector3_dot(&v23, &v14);
    if (A_ABS(d) >= A_REAL_EPS)
    {
        a_real const b21 = v12.x * (p2->x + p1->x) + v12.y * (p2->y + p1->y) + v12.z * (p2->z + p1->z);
        a_real const b31 = v13.x * (p3->x + p1->x) + v13.y * (p3->y + p1->y) + v13.z * (p3->z + p1->z);
        a_real const b41 = v14.x * (p4->x + p1->x) + v14.y * (p4->y + p1->y) + v14.z * (p4->z + p1->z);
        a_real const bx = b21 * v13.x - b31 * v12.x;
        a_real const by = b21 * v13.y - b31 * v12.y;
        a_real const bz = b21 * v13.z - b31 * v12.z;
        d = A_REAL_C(0.5) / d;
        pc->x = (b41 * v23.x - v14.y * bz + v14.z * by) * d;
        pc->y = (b41 * v23.y - v14.z * bx + v14.x * bz) * d;
        pc->z = (b41 * v23.z - v14.x * by + v14.y * bx) * d;
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
