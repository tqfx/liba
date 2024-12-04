#include "a/math.h"

#if A_PREREQ_GNUC(3, 0)
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif /* -Wfloat-conversion */
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */
#if A_PREREQ_MSVC(19, 30)
#pragma warning(disable : 5250)
#endif /* msvc 17.0+ */

#if !defined __STDC_VERSION__ || (defined(_MSC_VER) && (_MSC_VER < 1800))
#if !defined isinf
#define isinf(x) ((x) + (x) == (x) && (x))
#endif /* isinf */
#if !defined isnan
#define isnan(x) ((x) != (x))
#endif /* isnan */
#endif /* __STDC_VERSION__ */

#if A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
#define A_FLOAT_SQRT_EPSILON 3.4526698300124393e-04F
#else /* !A_FLOAT_TYPE */
#define A_FLOAT_SQRT_EPSILON 1.4901161193847656e-08
#endif /* A_FLOAT_TYPE */

static A_INLINE a_float polevl(a_float const *p, a_size n, a_float x)
{
    a_float y = *p++;
    do {
        y = y * x + *p++;
    } while (--n);
    return y;
}

a_f32 a_f32_rsqrt(a_f32 x)
{
    a_u32 *const u = (a_u32 *)&x;
#if defined(__STDC_VERSION__) || A_PREREQ_MSVC(18, 0)
    if (x > 0) { return 1 / a_f32_sqrt(x); }
#else
    if (x > 0)
    {
        a_f32 xh = A_F32_C(0.5) * x;
        *u = A_U32_C(0x5F375A86) - (*u >> 1);
        x *= A_F32_C(1.5) - x * x * xh;
        x *= A_F32_C(1.5) - x * x * xh;
        return x;
    }
#endif
    if (x < 0) { return A_F32_NAN; }
    *u |= A_F32_PINF;
    return x;
}

a_f64 a_f64_rsqrt(a_f64 x)
{
    a_u64 *const u = (a_u64 *)&x;
#if 1
    if (x > 0) { return 1 / a_f64_sqrt(x); }
#else
    if (x > 0)
    {
        a_f64 xh = A_F64_C(0.5) * x;
        *u = A_U64_C(0x5FE6EC85E7DE30DA) - (*u >> 1);
        x *= A_F64_C(1.5) - x * x * xh;
        x *= A_F64_C(1.5) - x * x * xh;
        return x;
    }
#endif
    if (x < 0) { return A_F64_NAN; }
    *u |= A_F64_PINF;
    return x;
}

#if (__has_builtin(__builtin_clz) || A_PREREQ_GNUC(3, 4)) && (ULONG_MAX == A_U32_MAX)
#define A_U32_BSR(x) (31 - __builtin_clzl(x))
#elif __has_builtin(__builtin_clz) || A_PREREQ_GNUC(3, 4)
#define A_U32_BSR(x) (31 - __builtin_clz(x))
#elif defined(_MSC_VER)
#pragma intrinsic(_BitScanReverse)
#define A_U32_BSR(x) BitScanReverse(x)
static A_INLINE int A_U32_BSR(a_u32 x)
{
    unsigned long i = 0;
    _BitScanReverse(&i, x);
    return (int)i;
}
#endif /* A_U32_BSR */

a_u16 a_u32_sqrt(a_u32 x)
{
#if defined(A_U32_BSR) /* Newton's method */
    a_u32 x0, x1 = 1;
    if (x <= 1) { return (a_u16)x; }
    x1 <<= (A_U32_BSR(x) + 1) >> 1;
    do {
        x0 = x1;
        x1 = (x0 + x / x0) >> 1;
    } while (x0 > x1);
    return (a_u16)x0;
#else /* Digit-by-digit */
    a_u32 a, b = 1, y = 0;
    b <<= sizeof(b) * 8 - 2;
    while (b > x) { b >>= 2; }
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

#if (__has_builtin(__builtin_clz) || A_PREREQ_GNUC(3, 4)) && (ULONG_MAX == A_U32_MAX)
#define A_U64_BSR(x) (63 - __builtin_clzll(x))
#elif __has_builtin(__builtin_clz) || A_PREREQ_GNUC(3, 4)
#define A_U64_BSR(x) (63 - __builtin_clzl(x))
#elif defined(_MSC_VER) && defined(_WIN64)
#pragma intrinsic(_BitScanReverse64)
#define A_U64_BSR(x) BitScanReverse64(x)
static A_INLINE int A_U64_BSR(a_u64 x)
{
    unsigned long i = 0;
    _BitScanReverse64(&i, x);
    return (int)i;
}
#elif defined(_MSC_VER)
#define A_U64_BSR(x) BitScanReverse64(x)
static A_INLINE int A_U64_BSR(a_u64 x)
{
    unsigned long i = 0, hi = 0;
    if (_BitScanReverse(&hi, x >> 32))
    {
        return (int)hi + 32;
    }
    _BitScanReverse(&i, (a_u32)x);
    return (int)i;
}
#endif /* A_U64_BSR */

a_u32 a_u64_sqrt(a_u64 x)
{
#if defined(A_U64_BSR) /* Newton's method */
    a_u64 x0, x1 = 1;
    if (x <= 1) { return (a_u32)x; }
    x1 <<= (A_U64_BSR(x) + 1) >> 1;
    do {
        x0 = x1;
        x1 = (x0 + x / x0) >> 1;
    } while (x0 > x1);
    return (a_u32)x0;
#else /* Digit-by-digit */
    a_u64 a, b = 1, y = 0;
    b <<= sizeof(b) * 8 - 2;
    while (b > x) { b >>= 2; }
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

#undef a_float_asinh
a_float a_float_asinh(a_float x)
{
    a_float a = a_float_abs(x);
    a_float s = (x < 0) ? -1 : 1;
    if (a > 1 / A_FLOAT_SQRT_EPSILON)
    {
        return s * (a_float_log(a) + A_FLOAT_LN2);
    }
    if (a > 2)
    {
        return s * a_float_log(1 / (a_float_sqrt(a * a + 1) + a) + a * 2);
    }
    if (a > A_FLOAT_SQRT_EPSILON)
    {
        a_float aa = a * a;
        return s * a_float_log1p(aa / (a_float_sqrt(aa + 1) + 1) + a);
    }
    return x;
}

#undef a_float_acosh
a_float a_float_acosh(a_float x)
{
    if (x > 1.0 / A_FLOAT_SQRT_EPSILON)
    {
        return a_float_log(x) + A_FLOAT_LN2;
    }
    if (x > 2)
    {
        return a_float_log(-1 / (a_float_sqrt(x * x - 1) + x) + x * 2);
    }
    if (x > 1)
    {
        a_float t = x - 1;
        return a_float_log1p(a_float_sqrt(t * t + t * 2) + t);
    }
    if (x == 1) { return 0; }
    return A_FLOAT_NAN;
}

#undef a_float_atanh
a_float a_float_atanh(a_float x)
{
    a_float a = a_float_abs(x);
    a_float s = (x < 0) ? A_FLOAT_C(-0.5) : A_FLOAT_C(0.5);
    if (a > 1) { return A_FLOAT_NAN; }
    if (a == 1)
    {
        if (x < 0) { return -A_FLOAT_INF; }
        return A_FLOAT_INF;
    }
    if (a >= A_FLOAT_C(0.5))
    {
        return s * a_float_log1p((a + a) / (1 - a));
    }
    if (a > A_FLOAT_EPSILON)
    {
        return s * a_float_log1p((a + a) * (a / (1 - a) + 1));
    }
    return x;
}

#undef a_float_expm1
a_float a_float_expm1(a_float x)
{
    static a_float const P[] = {
        A_FLOAT_C(1.2617719307481059087798E-4),
        A_FLOAT_C(3.0299440770744196129956E-2),
        A_FLOAT_C(9.9999999999999999991025E-1),
    };
    static a_float const Q[] = {
        A_FLOAT_C(3.0019850513866445504159E-6),
        A_FLOAT_C(2.5244834034968410419224E-3),
        A_FLOAT_C(2.2726554820815502876593E-1),
        A_FLOAT_C(2.0000000000000000000897E-0),
    };
    a_float xx, y;
    if (isnan(x)) { return x; }
    if (isinf(x)) { return x > 0 ? x : -1; }
    if (x < -A_FLOAT_C(0.5) || x > A_FLOAT_C(0.5))
    {
        return a_float_exp(x) - 1;
    }
    xx = x * x;
    y = polevl(P, A_LEN(P) - 1, xx) * x;
    y /= polevl(Q, A_LEN(Q) - 1, xx) - y;
    return y + y;
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
    a_float a = a_float_abs(x);
    a_float const b = a_float_abs(y);
    a_float const c = a_float_abs(z);
    if (isinf(x) || isinf(y) || isinf(z))
    {
        return A_FLOAT_INF;
    }
    if (a < b) { a = b; }
    if (a < c) { a = c; }
    if (!a) { return 0; }
    x /= a;
    y /= a;
    z /= a;
    return a_float_sqrt(x * x + y * y + z * z) * a;
}

a_float a_float_sum(a_float const *p, a_size n)
{
    a_float r = 0;
    for (; n; --n, ++p) { r += *p; }
    return r;
}

a_float a_float_sum1(a_float const *p, a_size n)
{
    a_float r = 0;
    for (; n; --n, ++p) { r += A_ABS(*p); }
    return r;
}

a_float a_float_sum2(a_float const *p, a_size n)
{
    a_float r = 0;
    for (; n; --n, ++p) { r += A_SQ(*p); }
    return r;
}

a_float a_float_mean(a_float const *p, a_size n)
{
    a_float r = 0;
    a_float const i = 1 / (a_float)n;
    for (; n; --n, ++p) { r += *p * i; }
    return r;
}

void a_float_push_fore(a_float *p, a_size n, a_float x)
{
    if (n--)
    {
        a_move(p + 1, p, sizeof(a_float) * n);
        p[0] = x;
    }
}

void a_float_push_back(a_float *p, a_size n, a_float x)
{
    if (n--)
    {
        a_move(p, p + 1, sizeof(a_float) * n);
        p[n] = x;
    }
}

void a_float_push_fore_(a_float *block_p, a_size block_n,
                        a_float const *cache_p, a_size cache_n)
{
    a_size const n = A_MIN(cache_n, block_n);
    if (n)
    {
        a_size const m = block_n - n;
        cache_p = cache_p + cache_n - n;
        a_move(block_p + n, block_p, sizeof(a_float) * m);
        a_copy(block_p, cache_p, sizeof(a_float) * n);
    }
}

void a_float_push_back_(a_float *block_p, a_size block_n,
                        a_float const *cache_p, a_size cache_n)
{
    a_size const n = A_MIN(cache_n, block_n);
    if (n)
    {
        a_size const m = block_n - n;
        cache_p = cache_p + cache_n - n;
        a_move(block_p, block_p + n, sizeof(a_float) * m);
        a_copy(block_p + m, cache_p, sizeof(a_float) * n);
    }
}

void a_float_roll_fore(a_float *p, a_size n)
{
    if (n--)
    {
        a_float x = p[0];
        a_move(p, p + 1, sizeof(a_float) * n);
        p[n] = x;
    }
}

void a_float_roll_back(a_float *p, a_size n)
{
    if (n--)
    {
        a_float x = p[n];
        a_move(p + 1, p, sizeof(a_float) * n);
        p[0] = x;
    }
}

void a_float_roll_fore_(a_float *block_p, a_size block_n,
                        a_float *shift_p, a_size shift_n)
{
    shift_n %= block_n;
    block_n -= shift_n;
    a_copy(shift_p, block_p, sizeof(a_float) * shift_n);
    a_move(block_p, block_p + shift_n, sizeof(a_float) * block_n);
    a_copy(block_p + block_n, shift_p, sizeof(a_float) * shift_n);
}

void a_float_roll_back_(a_float *block_p, a_size block_n,
                        a_float *shift_p, a_size shift_n)
{
    shift_n %= block_n;
    block_n -= shift_n;
    a_copy(shift_p, block_p + block_n, sizeof(a_float) * shift_n);
    a_move(block_p + shift_n, block_p, sizeof(a_float) * block_n);
    a_copy(block_p, shift_p, sizeof(a_float) * shift_n);
}
