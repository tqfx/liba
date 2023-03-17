#include "a/real.h"

#undef a_real_log1p
a_real_t a_real_log1p(a_real_t const x)
{
    return A_REAL_F1(log, x + 1);
}

#undef a_real_hypot
a_real_t a_real_hypot(a_real_t const x, a_real_t const y)
{
#if A_REAL_TYPE == A_REAL_SINGLE
    return a_f32_hypot(x, y);
#elif A_REAL_TYPE == A_REAL_DOUBLE
    return a_f64_hypot(x, y);
#elif A_REAL_TYPE == A_REAL_EXTEND
    return A_REAL_F1(sqrt, x * x + y * y);
#endif /* A_REAL_TYPE */
}

#undef a_real_atan2
a_real_t a_real_atan2(a_real_t const x, a_real_t const y)
{
    if (x > 0)
    {
        return A_REAL_F1(atan, y / x);
    }
    if (x < 0)
    {
        if (y >= 0)
        {
            return A_REAL_F1(atan, y / x) + A_REAL_PI;
        }
        return A_REAL_F1(atan, y / x) - A_REAL_PI;
    }
    if (y > 0)
    {
        return +A_REAL_PI;
    }
    if (y < 0)
    {
        return -A_REAL_PI;
    }
    return 0;
}
