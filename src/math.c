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
#define isinf(x) ((x) + (x) == (x) && (x) != 0)
#endif /* isinf */
#if !defined isnan
#define isnan(x) ((x) != (x))
#endif /* isnan */
#endif /* __STDC_VERSION__ */

#if A_REAL_TYPE + 0 == A_REAL_SINGLE
#define A_REAL_SQRT_EPSILON 3.4526698300124393e-4F
#else /* !A_REAL_TYPE */
#define A_REAL_SQRT_EPSILON 1.4901161193847656e-8
#endif /* A_REAL_TYPE */

static A_INLINE a_real polevl(a_real const *p, a_size n, a_real x)
{
    a_real y = *p++;
    do {
        y = y * x + *p++;
    } while (--n);
    return y;
}

a_u32 a_u32_gcd(a_u32 a, a_u32 b)
{
    while (b)
    {
        a_u32 const r = a % b;
        a = b;
        b = r;
    }
    return a;
}

a_u64 a_u64_gcd(a_u64 a, a_u64 b)
{
    while (b)
    {
        a_u64 const r = a % b;
        a = b;
        b = r;
    }
    return a;
}

a_u32 a_u32_lcm(a_u32 a, a_u32 b)
{
    a_u32 r = a_u32_gcd(a, b);
    if (r) { r = a / r * b; }
    return r;
}

a_u64 a_u64_lcm(a_u64 a, a_u64 b)
{
    a_u64 r = a_u64_gcd(a, b);
    if (r) { r = a / r * b; }
    return r;
}

#if (__has_builtin(__builtin_clz) || A_PREREQ_GNUC(3, 4)) && (ULONG_MAX == 0xFFFFFFFFUL)
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

#if (__has_builtin(__builtin_clz) || A_PREREQ_GNUC(3, 4)) && (ULONG_MAX == 0xFFFFFFFFUL)
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

#undef a_real_asinh
a_real a_real_asinh(a_real x)
{
    a_real const a = a_real_abs(x);
    a_real const s = x < 0 ? -1 : 1;
    if (a > 1 / A_REAL_SQRT_EPSILON)
    {
        return s * (a_real_log(a) + A_REAL_LN2);
    }
    if (a > 2)
    {
        return s * a_real_log(1 / (a_real_sqrt(a * a + 1) + a) + a * 2);
    }
    if (a > A_REAL_SQRT_EPSILON)
    {
        a_real const aa = a * a;
        return s * a_real_log1p(aa / (a_real_sqrt(aa + 1) + 1) + a);
    }
    return x;
}

#undef a_real_acosh
a_real a_real_acosh(a_real x)
{
    if (x > 1 / A_REAL_SQRT_EPSILON)
    {
        return a_real_log(x) + A_REAL_LN2;
    }
    if (x > 2)
    {
        return a_real_log(-1 / (a_real_sqrt(x * x - 1) + x) + x * 2);
    }
    if (x > 1)
    {
        a_real const t = x - 1;
        return a_real_log1p(a_real_sqrt(t * t + t * 2) + t);
    }
    if (x == 1) { return 0; }
    return A_REAL_NAN;
}

#undef a_real_atanh
a_real a_real_atanh(a_real x)
{
    a_real const a = a_real_abs(x);
    a_real const s = x < 0 ? A_REAL_C(-0.5) : A_REAL_C(0.5);
    if (a > 1) { return A_REAL_NAN; }
    if (a == 1)
    {
        if (x < 0) { return -A_REAL_INF; }
        return A_REAL_INF;
    }
    if (a >= A_REAL_C(0.5))
    {
        return s * a_real_log1p((a + a) / (1 - a));
    }
    if (a > A_REAL_EPSILON)
    {
        return s * a_real_log1p((a + a) * (a / (1 - a) + 1));
    }
    return x;
}

#undef a_real_expm1
a_real a_real_expm1(a_real x)
{
    static a_real const P[] = {
        A_REAL_C(1.2617719307481059087798E-4),
        A_REAL_C(3.0299440770744196129956E-2),
        A_REAL_C(9.9999999999999999991025E-1),
    };
    static a_real const Q[] = {
        A_REAL_C(3.0019850513866445504159E-6),
        A_REAL_C(2.5244834034968410419224E-3),
        A_REAL_C(2.2726554820815502876593E-1),
        A_REAL_C(2.0000000000000000000897E-0),
    };
    a_real xx, y;
    if (isnan(x)) { return x; }
    if (isinf(x)) { return x > 0 ? x : -1; }
    if (x < -A_REAL_C(0.5) || x > A_REAL_C(0.5))
    {
        return a_real_exp(x) - 1;
    }
    xx = x * x;
    y = polevl(P, A_LEN(P) - 1, xx) * x;
    y /= polevl(Q, A_LEN(Q) - 1, xx) - y;
    return y + y;
}

#undef a_real_log1p
a_real a_real_log1p(a_real x)
{
    a_real volatile a = x + 1;
    a_real y = a_real_log(a);
    if (x < A_REAL_EPSILON && a > 0)
    {
        a_real volatile b = a - 1;
        y -= (b - x) / a;
    }
    return y;
}

#undef a_real_atan2
a_real a_real_atan2(a_real y, a_real x)
{
    if (x > 0) { return a_real_atan(y / x); }
    if (x < 0)
    {
        a_real const r = a_real_atan(y / x);
        if (y >= 0) { return r + A_REAL_PI; }
        return r - A_REAL_PI;
    }
    if (y > 0) { return +A_REAL_PI; }
    if (y < 0) { return -A_REAL_PI; }
    return 0;
}

a_real a_real_norm2(a_real x, a_real y)
{
    a_real w;
    x = a_real_abs(x);
    if (isinf(x)) { return A_REAL_INF; }
    y = a_real_abs(y);
    if (isinf(y)) { return A_REAL_INF; }
    if (x > y)
    {
        w = x;
        x = y;
        y = w;
    }
    if (y == 0) { return 0; }
    x /= y;
    return a_real_sqrt(x * x + 1) * y;
}

a_real a_real_norm3(a_real x, a_real y, a_real z)
{
    a_real w;
    x = a_real_abs(x);
    if (isinf(x)) { return A_REAL_INF; }
    y = a_real_abs(y);
    if (isinf(y)) { return A_REAL_INF; }
    z = a_real_abs(z);
    if (isinf(z)) { return A_REAL_INF; }
    if (x > y)
    {
        w = x;
        x = y;
        y = w;
    }
    if (y > z)
    {
        w = y;
        y = z;
        z = w;
    }
    if (z == 0) { return 0; }
    x /= z;
    y /= z;
    return a_real_sqrt(x * x + y * y + 1) * z;
}

a_real a_real_norm(a_size n, a_real const *p)
{
    a_size i;
    a_real w = 0, s = 0;
    for (i = 0; i < n; ++i)
    {
        a_real const x = a_real_abs(p[i]);
        if (isinf(x)) { return A_REAL_INF; }
        if (x > w) { w = x; }
    }
    if (w <= 0) { return 0; }
    for (i = 0; i < n; ++i)
    {
        a_real const x = p[i] / w;
        s += x * x;
    }
    return a_real_sqrt(s) * w;
}

a_real a_real_norm_(a_size n, a_real const *p, a_size c)
{
    a_size i;
    a_real w = 0, s = 0;
    a_size const nc = n * c;
    for (i = 0; i < nc; i += c)
    {
        a_real const x = a_real_abs(p[i]);
        if (isinf(x)) { return A_REAL_INF; }
        if (x > w) { w = x; }
    }
    if (w <= 0) { return 0; }
    for (i = 0; i < nc; i += c)
    {
        a_real const x = p[i] / w;
        s += x * x;
    }
    return a_real_sqrt(s) * w;
}

a_real a_real_sum(a_size n, a_real const *p)
{
    a_real r = 0;
    for (; n; --n, ++p) { r += *p; }
    return r;
}

a_real a_real_sum_(a_size n, a_real const *p, a_size c)
{
    a_real r = 0;
    for (; n; --n, p += c) { r += *p; }
    return r;
}

a_real a_real_sum1(a_size n, a_real const *p)
{
    a_real r = 0;
    for (; n; --n, ++p) { r += A_ABS(*p); }
    return r;
}

a_real a_real_sum1_(a_size n, a_real const *p, a_size c)
{
    a_real r = 0;
    for (; n; --n, p += c) { r += A_ABS(*p); }
    return r;
}

a_real a_real_sum2(a_size n, a_real const *p)
{
    a_real r = 0;
    for (; n; --n, ++p) { r += A_SQ(*p); }
    return r;
}

a_real a_real_sum2_(a_size n, a_real const *p, a_size c)
{
    a_real r = 0;
    for (; n; --n, p += c) { r += A_SQ(*p); }
    return r;
}

a_real a_real_mean(a_size n, a_real const *p)
{
    a_real r = 0;
    a_real const i = 1 / (a_real)n;
    for (; n; --n, ++p) { r += *p * i; }
    return r;
}

a_real a_real_mean_(a_size n, a_real const *p, a_size c)
{
    a_real r = 0;
    a_real const i = 1 / (a_real)n;
    for (; n; --n, p += c) { r += *p * i; }
    return r;
}

a_real a_real_dot(a_size n, a_real const *X, a_real const *Y)
{
    a_real r = 0;
    for (; n; --n, ++X, ++Y) { r += *X * *Y; }
    return r;
}

a_real a_real_dot_(a_size n, a_real const *X, a_size Xc, a_real const *Y, a_size Yc)
{
    a_real r = 0;
    for (; n; --n, X += Xc, Y += Yc) { r += *X * *Y; }
    return r;
}

void a_real_copy(a_size n, a_real *__restrict dst, a_real const *__restrict src)
{
    a_copy(dst, src, sizeof(a_real) * n);
}

void a_real_copy_(a_size n, a_real *dst, a_size dc, a_real const *src, a_size sc)
{
    for (; n; --n, dst += dc, src += sc) { *dst = *src; }
}

void a_real_swap(a_size n, a_real *__restrict lhs, a_real *__restrict rhs)
{
    for (; n; --n, ++lhs, ++rhs)
    {
        a_real swap;
        swap = *lhs;
        *lhs = *rhs;
        *rhs = swap;
    }
}

void a_real_swap_(a_size n, a_real *lhs, a_size lc, a_real *rhs, a_size rc)
{
    for (; n; --n, lhs += lc, rhs += rc)
    {
        a_real swap;
        swap = *lhs;
        *lhs = *rhs;
        *rhs = swap;
    }
}

void a_real_fill(a_size n, a_real *p, a_real v)
{
    for (; n; --n, ++p) { *p = v; }
}

void a_real_zero(a_size n, a_real *p)
{
    for (; n; --n, ++p) { *p = 0; }
}

void a_real_push_fore(a_real *p, a_size n, a_real x)
{
    if (n--)
    {
        a_move(p + 1, p, sizeof(a_real) * n);
        p[0] = x;
    }
}

void a_real_push_back(a_real *p, a_size n, a_real x)
{
    if (n--)
    {
        a_move(p, p + 1, sizeof(a_real) * n);
        p[n] = x;
    }
}

void a_real_push_fore_(a_real *block_p, a_size block_n,
                       a_real const *cache_p, a_size cache_n)
{
    a_size const n = A_MIN(cache_n, block_n);
    if (n)
    {
        a_size const m = block_n - n;
        cache_p = cache_p + cache_n - n;
        a_move(block_p + n, block_p, sizeof(a_real) * m);
        a_copy(block_p, cache_p, sizeof(a_real) * n);
    }
}

void a_real_push_back_(a_real *block_p, a_size block_n,
                       a_real const *cache_p, a_size cache_n)
{
    a_size const n = A_MIN(cache_n, block_n);
    if (n)
    {
        a_size const m = block_n - n;
        cache_p = cache_p + cache_n - n;
        a_move(block_p, block_p + n, sizeof(a_real) * m);
        a_copy(block_p + m, cache_p, sizeof(a_real) * n);
    }
}

void a_real_roll_fore(a_real *p, a_size n)
{
    if (n--)
    {
        a_real x = p[0];
        a_move(p, p + 1, sizeof(a_real) * n);
        p[n] = x;
    }
}

void a_real_roll_back(a_real *p, a_size n)
{
    if (n--)
    {
        a_real x = p[n];
        a_move(p + 1, p, sizeof(a_real) * n);
        p[0] = x;
    }
}

void a_real_roll_fore_(a_real *block_p, a_size block_n,
                       a_real *shift_p, a_size shift_n)
{
    shift_n %= block_n;
    block_n -= shift_n;
    a_copy(shift_p, block_p, sizeof(a_real) * shift_n);
    a_move(block_p, block_p + shift_n, sizeof(a_real) * block_n);
    a_copy(block_p + block_n, shift_p, sizeof(a_real) * shift_n);
}

void a_real_roll_back_(a_real *block_p, a_size block_n,
                       a_real *shift_p, a_size shift_n)
{
    shift_n %= block_n;
    block_n -= shift_n;
    a_copy(shift_p, block_p + block_n, sizeof(a_real) * shift_n);
    a_move(block_p + shift_n, block_p, sizeof(a_real) * block_n);
    a_copy(block_p, shift_p, sizeof(a_real) * shift_n);
}
