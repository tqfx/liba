#define LIBA_POINT3_C
#include "a/point3.h"

a_real a_point3_dist(a_point3 const *lhs, a_point3 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    a_real const z = rhs->z - lhs->z;
    return a_real_norm3(x, y, z);
}

a_real a_point3_dist1(a_point3 const *lhs, a_point3 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    a_real const z = rhs->z - lhs->z;
    return A_ABS(x) + A_ABS(y) + A_ABS(z);
}

a_real a_point3_dist2(a_point3 const *lhs, a_point3 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    a_real const z = rhs->z - lhs->z;
    return x * x + y * y + z * z;
}
