#include "a/math.h"

#if defined(__MINGW32__) && A_PREREQ_GNUC(3, 0)
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif /* __MINGW32__ */
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

a_f32 a_f32_rsqrt(a_f32 x)
{
#if 1
    return 1 / a_f32_sqrt(x);
#else
    union
    {
        a_f32 x;
        a_u32 u;
    } u;
    u.x = x;
    if (a_likely(x > 0))
    {
        a_f32 xh = A_F32_C(0.5) * x;
        u.u = A_U32_C(0x5F375A86) - (u.u >> 1);
        u.x *= A_F32_C(1.5) - u.x * u.x * xh;
        u.x *= A_F32_C(1.5) - u.x * u.x * xh;
    }
    else if (x < 0)
    {
        u.u = A_F32_NNAN;
    }
    else
    {
        u.u |= A_F32_PINF;
    }
    return u.x;
#endif
}

a_f64 a_f64_rsqrt(a_f64 x)
{
#if 1
    return 1 / a_f64_sqrt(x);
#else
    union
    {
        a_f64 x;
        a_u64 u;
    } u;
    u.x = x;
    if (a_likely(x > 0))
    {
        a_f64 xh = A_F64_C(0.5) * x;
        u.u = A_U64_C(0x5FE6EC85E7DE30DA) - (u.u >> 1);
        u.x *= A_F64_C(1.5) - u.x * u.x * xh;
        u.x *= A_F64_C(1.5) - u.x * u.x * xh;
    }
    else if (x < 0)
    {
        u.u = A_F64_NNAN;
    }
    else
    {
        u.u |= A_F64_PINF;
    }
    return u.x;
#endif
}

a_u16 a_u32_sqrt(a_u32 x)
{
#if 0 /* Newton's method */
    a_u32 x0, x1;
    if (x <= 1) { return (a_u16)x; }
    x1 = x >> 1;
    do {
        x0 = x1;
        x1 = (x0 + x / x0) >> 1;
    } while (x0 > x1);
    return (a_u16)x0;
#else /* Digit-by-digit */
    a_u32 a, b = 1, y = 0;
    for (b <<= sizeof(b) * 8 - 2; b > x; b >>= 2) {}
    for (; b; b >>= 2)
    {
        a = y + b;
        y >>= 1;
        if (x >= a)
        {
            x -= a;
            y |= b;
        }
    }
    return (a_u16)y;
#endif
}

a_u32 a_u64_sqrt(a_u64 x)
{
#if 0 /* Newton's method */
    a_u64 x0, x1;
    if (x <= 1) { return (a_u32)x; }
    x1 = x >> 1;
    do {
        x0 = x1;
        x1 = (x0 + x / x0) >> 1;
    } while (x0 > x1);
    return (a_u32)x0;
#else /* Digit-by-digit */
    a_u64 a, b = 1, y = 0;
    for (b <<= sizeof(b) * 8 - 2; b > x; b >>= 2) {}
    for (; b; b >>= 2)
    {
        a = y + b;
        y >>= 1;
        if (x >= a)
        {
            x -= a;
            y |= b;
        }
    }
    return (a_u32)y;
#endif
}

#undef a_float_log1p
a_float a_float_log1p(a_float x)
{
    a_float volatile a = x + 1;
    a_float y = a_float_log(a);
    if (x < A_FLOAT_EPSILON && a > 0)
    {
        a_float volatile b = a - 1;
        y -= (b - x) / a;
    }
    return y;
}

#undef a_float_atan2
a_float a_float_atan2(a_float x, a_float y)
{
    if (x > 0) { return a_float_atan(y / x); }
    if (x < 0)
    {
        if (y >= 0) { return a_float_atan(y / x) + A_FLOAT_PI; }
        return a_float_atan(y / x) - A_FLOAT_PI;
    }
    if (y > 0) { return +A_FLOAT_PI; }
    if (y < 0) { return -A_FLOAT_PI; }
    return 0;
}

#undef a_float_hypot
a_float a_float_hypot(a_float x, a_float y)
{
    a_float const a = a_float_abs(x);
    a_float const b = a_float_abs(y);
    if (isinf(x) || isinf(y))
    {
        return A_FLOAT_INF;
    }
    if (a <= b)
    {
        x = a;
        y = b;
    }
    else
    {
        x = b;
        y = a;
    }
    x /= y;
    return a_float_sqrt(x * x + 1) * y;
}

a_float a_float_hypot3(a_float x, a_float y, a_float z)
{
    a_float const a = a_float_abs(x);
    a_float const b = a_float_abs(y);
    a_float const c = a_float_abs(z);
    a_float w = a;
    if (isinf(x) || isinf(y) || isinf(z))
    {
        return A_FLOAT_INF;
    }
    if (w < b) { w = b; }
    if (w < c) { w = c; }
    if (w == 0) { return 0; }
    x /= w;
    y /= w;
    z /= w;
    return a_float_sqrt(x * x + y * y + z * z) * w;
}
