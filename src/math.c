#include "math.h"

a_f64_t a_f64_sq(a_f64_t x, a_f64_t *const o)
{
#undef U
#if defined(_MSC_VER) && (_MSC_VER < 1914)
    const union
    {
        a_u64_t u;
        a_f64_t x;
    } u = {A_U64_C(0x41A0000000000000)};
#define U u.x
#else
#define U A_F64_C(0x1P27)
#endif
    a_f64_t xh, xl, xc;
    xc = x * (U + 1);
    xh = x - xc + xc;
    xl = x - xh;
    x *= x;
    *o = xh * xh - x + 2 * xh * xl + xl * xl;
    return x;
#undef U
}

#undef a_f32_hypot
a_f32_t a_f32_hypot(a_f32_t x, a_f32_t y)
{
#undef MIN
#undef MAX
#if defined(_MSC_VER) && (_MSC_VER < 1914)
    const union
    {
        a_u32_t u;
        a_f32_t x;
    } max = {A_U32_C(0x6C800000)},
      min = {A_U32_C(0x12800000)};
#define MAX max.x
#define MIN min.x
#else
#define MAX A_F32_C(0x1P+90)
#define MIN A_F32_C(0x1P-90)
#endif
    union
    {
        a_f32_t x;
        a_u32_t u;
    } ux, uy;
    a_f32_t z;

    ux.x = x;
    uy.x = y;
    ux.u &= A_U32_C(~0) >> 1;
    uy.u &= A_U32_C(~0) >> 1;
    if (ux.u < uy.u)
    {
        ux.u ^= uy.u;
        uy.u ^= ux.u;
        ux.u ^= uy.u;
    }

    x = ux.x;
    y = uy.x;
    if (uy.u == 0xFF << 23)
    {
        return y;
    }
    if (ux.u >= 0xFF << 23 || uy.u == 0 || ux.u - uy.u >= 25 << 23)
    {
        return x + y;
    }

    z = 1;
    if (ux.u >= (0x7F + 60) << 23)
    {
        z = MAX;
        x *= MIN;
        y *= MIN;
    }
    else if (uy.u < (0x7F - 60) << 23)
    {
        z = MIN;
        x *= MAX;
        y *= MAX;
    }
    return z * a_f32_sqrt((a_f32_t)((a_f64_t)x * (a_f64_t)x + (a_f64_t)y * (a_f64_t)y));
#undef MIN
#undef MAX
}

#undef a_f64_hypot
a_f64_t a_f64_hypot(a_f64_t x, a_f64_t y)
{
#undef MIN
#undef MAX
#if defined(_MSC_VER) && (_MSC_VER < 1914)
    const union
    {
        a_u64_t u;
        a_f64_t x;
    } max = {A_U64_C(0x6BB0000000000000)},
      min = {A_U64_C(0x1430000000000000)};
#define MAX max.x
#define MIN min.x
#else
#define MAX A_F64_C(0x1P+700)
#define MIN A_F64_C(0x1P-700)
#endif
    union
    {
        a_f64_t x;
        a_u64_t u;
    } ux, uy;
    unsigned int ex, ey;
    a_f64_t hx, lx, hy, ly, z;

    ux.x = x;
    uy.x = y;
    ux.u &= A_U64_C(~0) >> 1;
    uy.u &= A_U64_C(~0) >> 1;
    if (ux.u < uy.u)
    {
        ux.u ^= uy.u;
        uy.u ^= ux.u;
        ux.u ^= uy.u;
    }

    x = ux.x;
    y = uy.x;
    ex = (unsigned int)(ux.u >> 52);
    ey = (unsigned int)(uy.u >> 52);
    /* hypot(inf,nan) == inf */
    if (ey == 0x7FF)
    {
        return y;
    }
    if (ex == 0x7FF || uy.u == 0)
    {
        return x;
    }
    if (ex - ey > 64)
    {
        return x + y;
    }

    z = 1;
    if (ex > 0x3FF + 510)
    {
        z = MAX;
        x *= MIN;
        y *= MIN;
    }
    else if (ey < 0x3FF - 450)
    {
        z = MIN;
        x *= MAX;
        y *= MAX;
    }
    hx = a_f64_sq(x, &lx);
    hy = a_f64_sq(y, &ly);
    return z * a_f64_sqrt(ly + lx + hy + hx);
#undef MIN
#undef MAX
}

a_f32_t a_f32_rsqrt(a_f32_t const x)
{
#if 0
    return 1 / a_f32_sqrt(x);
#else
#undef U
#define U 0x5F375A86
    union
    {
        a_f32_t x;
        a_u32_t u;
    } u;
    u.x = x;
    if (a_likely(x > 0))
    {
        a_f32_t xh = A_F32_C(0.5) * x;
        u.u = A_U32_C(U) - (u.u >> 1);
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
#undef U
#endif
}

a_f64_t a_f64_rsqrt(a_f64_t const x)
{
#if 0
    return 1 / a_f64_sqrt(x);
#else
#undef U
#define U 0x5FE6EC85E7DE30DA
    union
    {
        a_f64_t x;
        a_u64_t u;
    } u;
    u.x = x;
    if (a_likely(x > 0))
    {
        a_f64_t xh = A_F64_C(0.5) * x;
        u.u = A_U64_C(U) - (u.u >> 1);
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
#undef U
#endif
}

a_u32_t a_u32_sqrt(a_u32_t x, a_u32_t *const o)
{
    a_u32_t y = 0;
    for (unsigned int i = 0; i < 32; i += 2)
    {
        a_u32_t k = A_U32_C(0x40000000) >> i;
        a_u32_t j = y + k;
        if (x >= j)
        {
            x -= j;
            y = (y >> 1) | k;
        }
        else
        {
            y >>= 1;
        }
    }
    if (o)
    {
        *o = x;
    }
    return y;
}

a_u64_t a_u64_sqrt(a_u64_t x, a_u64_t *const o)
{
    a_u64_t y = 0;
    for (unsigned int i = 0; i < 64; i += 2)
    {
        a_u64_t k = A_U64_C(0x4000000000000000) >> i;
        a_u64_t j = y + k;
        if (x >= j)
        {
            x -= j;
            y = (y >> 1) | k;
        }
        else
        {
            y >>= 1;
        }
    }
    if (o)
    {
        *o = x;
    }
    return y;
}

#undef a_float_log1p
a_float_t a_float_log1p(a_float_t const x)
{
    return A_FLOAT_F1(log, x + 1);
}

#undef a_float_hypot
a_float_t a_float_hypot(a_float_t const x, a_float_t const y)
{
#if A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
    return a_f32_hypot(x, y);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE
    return a_f64_hypot(x, y);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_EXTEND
    return A_FLOAT_F1(sqrt, x * x + y * y);
#endif /* A_FLOAT_TYPE */
}

#undef a_float_atan2
a_float_t a_float_atan2(a_float_t const x, a_float_t const y)
{
    if (x > 0)
    {
        return A_FLOAT_F1(atan, y / x);
    }
    if (x < 0)
    {
        if (y >= 0)
        {
            return A_FLOAT_F1(atan, y / x) + A_FLOAT_PI;
        }
        return A_FLOAT_F1(atan, y / x) - A_FLOAT_PI;
    }
    if (y > 0)
    {
        return +A_FLOAT_PI;
    }
    if (y < 0)
    {
        return -A_FLOAT_PI;
    }
    return 0;
}
