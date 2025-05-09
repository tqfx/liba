#define LIBA_POINT2_C
#include "a/point2.h"

a_real a_point2_dist(a_point2 const *lhs, a_point2 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    return a_real_hypot(x, y);
}

a_real a_point2_dist1(a_point2 const *lhs, a_point2 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    return A_ABS(x) + A_ABS(y);
}

a_real a_point2_dist2(a_point2 const *lhs, a_point2 const *rhs)
{
    a_real const x = rhs->x - lhs->x;
    a_real const y = rhs->y - lhs->y;
    return x * x + y * y;
}
