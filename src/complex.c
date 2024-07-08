#include "a/a.h"
#if A_PREREQ_GNUC(3, 0)
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif /* -Wfloat-conversion */
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */
#define LIBA_COMPLEX_C
#include "a/complex.h"
/* compiler built-in complex number type */
#if A_PREREQ_MSVC(18, 0)
#include <complex.h> /* 12.0 */
#if A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
#define A_COMPLEX _Fcomplex
#elif A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE
#define A_COMPLEX _Dcomplex
#elif A_FLOAT_TYPE + 0 == A_FLOAT_EXTEND
#define A_COMPLEX _Lcomplex
#endif /* A_COMPLEX */
#elif defined(__GNUC__) || defined(__clang__)
#include <complex.h>
#define A_COMPLEX _Complex A_FLOAT
#else /* !A_FLOAT_TYPE */
#if A_PREREQ_GNUC(2, 95) || __has_warning("-Waggregate-return")
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* -Waggregate-return */
#endif /* A_FLOAT_TYPE */
#include "a/math.h"
#include <stdlib.h>

void a_complex_polar(a_complex *ctx, a_float rho, a_float theta)
{
    ctx->real = rho * a_float_cos(theta);
    ctx->imag = rho * a_float_sin(theta);
}

unsigned int a_complex_parse(a_complex *ctx, char const *str)
{
#if A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
#define strtonum(string, endptr) strtof(string, endptr)
#elif A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE
#define strtonum(string, endptr) strtod(string, endptr)
#elif A_FLOAT_TYPE + 0 == A_FLOAT_EXTEND
#define strtonum(string, endptr) strtold(string, endptr)
#endif /* A_FLOAT_TYPE */
    union
    {
        char const *s;
        char *p;
    } u;
    u.s = str;
    if (!str) { return 0; }
    for (ctx->real = 0; *u.s; ++u.s)
    {
        if (*u.s == '+' || *u.s == '-' || ('0' <= *u.s && *u.s <= '9') || *u.s == '.')
        {
            ctx->real = strtonum(u.s, &u.p);
            break;
        }
    }
    for (ctx->imag = 0; *u.s; ++u.s)
    {
        if (*u.s == '+' || *u.s == '-' || ('0' <= *u.s && *u.s <= '9') || *u.s == '.')
        {
            ctx->imag = strtonum(u.s, &u.p);
            break;
        }
    }
    return (unsigned int)(u.s - str);
}

a_bool a_complex_eq(a_complex x, a_complex y)
{
    return x.real == y.real && x.imag == y.imag;
}

a_bool a_complex_ne(a_complex x, a_complex y)
{
    return x.real != y.real || x.imag != y.imag;
}

a_float a_complex_logabs(a_complex z)
{
    a_float r, u;
    a_float const xabs = a_float_abs(z.real);
    a_float const yabs = a_float_abs(z.imag);
    if (xabs >= yabs)
    {
        r = xabs;
        u = yabs / xabs;
    }
    else
    {
        r = yabs;
        u = xabs / yabs;
    }
    return a_float_log(r) + A_FLOAT_C(0.5) * a_float_log1p(u * u);
}

a_float a_complex_abs2(a_complex z)
{
    return z.real * z.real + z.imag * z.imag;
}

a_float a_complex_abs(a_complex z)
{
    return a_float_hypot(z.real, z.imag);
}

a_float a_complex_arg(a_complex z)
{
    if (z.real != 0 || z.imag != 0)
    {
        return a_float_atan2(z.imag, z.real);
    }
    return 0;
}

void a_complex_proj_(a_complex *ctx)
{
    if (isinf(ctx->real) || isinf(ctx->imag))
    {
        ctx->real = A_FLOAT_INF;
        ctx->imag = a_float_copysign(0, ctx->imag);
    }
}

void a_complex_mul_(a_complex *ctx, a_complex z)
{
    a_float const real = ctx->real;
    ctx->real = real * z.real - ctx->imag * z.imag;
    ctx->imag = real * z.imag + ctx->imag * z.real;
}

void a_complex_div_(a_complex *ctx, a_complex z)
{
    a_float const inv = 1 / a_complex_abs(z);
    a_float const xr = ctx->real * inv;
    a_float const xi = ctx->imag * inv;
    a_float const yr = z.real * inv;
    a_float const yi = z.imag * inv;
    ctx->real = xr * yr + xi * yi;
    ctx->imag = xi * yr - xr * yi;
}

void a_complex_inv_(a_complex *ctx)
{
    a_float const inv = 1 / a_complex_abs(*ctx);
    ctx->real = +inv * ctx->real * inv;
    ctx->imag = -inv * ctx->imag * inv;
}

#if A_PREREQ_GNUC(2, 95) || __has_warning("-Wimplicit-function-declaration")
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
#endif /* gcc 2.95+ */
#if __has_warning("-Wincompatible-library-redeclaration")
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"
#endif /* clang 4.0+ */
#if A_PREREQ_GNUC(10, 0)
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#endif /* gcc 10.0+ */

#if defined(A_HAVE_CSQRT) && (A_HAVE_CSQRT + 0 < 1)
#undef A_HAVE_CSQRT
#endif /* A_HAVE_CSQRT */
#if defined(A_HAVE_CSQRT) && !defined A_COMPLEX
a_complex A_FLOAT_F(csqrt)(a_complex);
#endif /* A_HAVE_CSQRT */
void a_complex_sqrt_(a_complex *ctx)
{
#if defined(A_HAVE_CSQRT) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(csqrt)(*x);
#elif defined(A_HAVE_CSQRT)
    *ctx = A_FLOAT_F(csqrt)(*ctx);
#else /* !A_HAVE_CSQRT */
    if (ctx->real != 0 || ctx->imag != 0)
    {
        a_float const x = a_float_abs(ctx->real);
        a_float const y = a_float_abs(ctx->imag);
        a_float w;
        if (x >= y)
        {
            a_float u = y / x;
            w = A_FLOAT_SQRT1_2 * a_float_sqrt(x) * a_float_sqrt(a_float_sqrt(u * u + 1) + 1);
        }
        else
        {
            a_float u = x / y;
            w = A_FLOAT_SQRT1_2 * a_float_sqrt(y) * a_float_sqrt(a_float_sqrt(u * u + 1) + u);
        }
        if (ctx->real >= 0)
        {
            ctx->real = w;
            ctx->imag = ctx->imag / (2 * w);
        }
        else
        {
            ctx->real = ctx->imag / (2 * w);
            ctx->imag = ctx->imag < 0 ? -w : w;
        }
    }
#endif /* A_HAVE_CSQRT */
}

void a_complex_sqrt_real(a_complex *ctx, a_float x)
{
    if (x >= 0)
    {
        ctx->real = a_float_sqrt(x);
        ctx->imag = 0;
    }
    else
    {
        ctx->real = 0;
        ctx->imag = a_float_sqrt(-x);
    }
}

#if defined(A_HAVE_CPOW) && (A_HAVE_CPOW + 0 < 1)
#undef A_HAVE_CPOW
#endif /* A_HAVE_CPOW */
#if defined(A_HAVE_CPOW) && !defined A_COMPLEX
a_complex A_FLOAT_F(cpow)(a_complex, a_complex);
#endif /* A_HAVE_CPOW */
void a_complex_pow_(a_complex *ctx, a_complex a)
{
#if defined(A_HAVE_CPOW) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    A_COMPLEX *const y = (A_COMPLEX *)&a;
    *x = A_FLOAT_F(cpow)(*x, *y);
#elif defined(A_HAVE_CPOW)
    *ctx = A_FLOAT_F(cpow)(*ctx, a);
#else /* !A_HAVE_CPOW */
    if (ctx->real != 0 || ctx->imag != 0)
    {
        a_float const logr = a_complex_logabs(*ctx);
        a_float const theta = a_complex_arg(*ctx);
        a_float const rho = a_float_exp(logr * a.real - theta * a.imag);
        a_float const beta = theta * a.real + logr * a.imag;
        a_complex_polar(ctx, rho, beta);
    }
    else
    {
        ctx->real = (a.real == 0 && a.imag == 0) ? 1 : 0;
    }
#endif /* A_HAVE_CPOW */
}

void a_complex_pow_real_(a_complex *ctx, a_float a)
{
    if (ctx->real != 0 || ctx->imag != 0)
    {
        a_float const logr = a_complex_logabs(*ctx);
        a_float const theta = a_complex_arg(*ctx);
        a_float const rho = a_float_exp(logr * a);
        a_float const beta = theta * a;
        a_complex_polar(ctx, rho, beta);
    }
    else
    {
        ctx->real = (a == 0) ? 1 : 0;
    }
}

#if defined(A_HAVE_CEXP) && (A_HAVE_CEXP + 0 < 1)
#undef A_HAVE_CEXP
#endif /* A_HAVE_CEXP */
#if defined(A_HAVE_CEXP) && !defined A_COMPLEX
a_complex A_FLOAT_F(cexp)(a_complex);
#endif /* A_HAVE_CEXP */
void a_complex_exp_(a_complex *ctx)
{
#if defined(A_HAVE_CEXP) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(cexp)(*x);
#elif defined(A_HAVE_CEXP)
    *ctx = A_FLOAT_F(cexp)(*ctx);
#else /* !A_HAVE_CEXP */
    a_complex_polar(ctx, a_float_exp(ctx->real), ctx->imag);
#endif /* A_HAVE_CEXP */
}

#if defined(A_HAVE_CLOG) && (A_HAVE_CLOG + 0 < 1)
#undef A_HAVE_CLOG
#endif /* A_HAVE_CLOG */
#if defined(A_HAVE_CLOG) && !defined A_COMPLEX
a_complex A_FLOAT_F(clog)(a_complex);
#endif /* A_HAVE_CLOG */
void a_complex_log_(a_complex *ctx)
{
#if defined(A_HAVE_CLOG) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(clog)(*x);
#elif defined(A_HAVE_CLOG)
    *ctx = A_FLOAT_F(clog)(*ctx);
#else /* !A_HAVE_CLOG */
    ctx->real = a_complex_logabs(*ctx);
    ctx->imag = a_complex_arg(*ctx);
#endif /* A_HAVE_CLOG */
}

void a_complex_log2_(a_complex *ctx)
{
    a_complex_log_(ctx);
    a_complex_mul_real_(ctx, A_FLOAT_LN1_2);
}

void a_complex_log10_(a_complex *ctx)
{
    a_complex_log_(ctx);
    a_complex_mul_real_(ctx, A_FLOAT_LN1_10);
}

void a_complex_logb_(a_complex *ctx, a_complex b)
{
    a_complex_log_(ctx);
    a_complex_log_(&b);
    a_complex_div_(ctx, b);
}

#if defined(A_HAVE_CSIN) && (A_HAVE_CSIN + 0 < 1)
#undef A_HAVE_CSIN
#endif /* A_HAVE_CSIN */
#if defined(A_HAVE_CSIN) && !defined A_COMPLEX
a_complex A_FLOAT_F(csin)(a_complex);
#endif /* A_HAVE_CSIN */
void a_complex_sin_(a_complex *ctx)
{
#if defined(A_HAVE_CSIN) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(csin)(*x);
#elif defined(A_HAVE_CSIN)
    *ctx = A_FLOAT_F(csin)(*ctx);
#else /* !A_HAVE_CSIN */
    if (ctx->imag != 0)
    {
        a_float const real = ctx->real;
        ctx->real = a_float_sin(real) * a_float_cosh(ctx->imag);
        ctx->imag = a_float_cos(real) * a_float_sinh(ctx->imag);
    }
    else
    {
        ctx->real = a_float_sin(ctx->real);
    }
#endif /* A_HAVE_CSIN */
}

#if defined(A_HAVE_CCOS) && (A_HAVE_CCOS + 0 < 1)
#undef A_HAVE_CCOS
#endif /* A_HAVE_CCOS */
#if defined(A_HAVE_CCOS) && !defined A_COMPLEX
a_complex A_FLOAT_F(ccos)(a_complex);
#endif /* A_HAVE_CCOS */
void a_complex_cos_(a_complex *ctx)
{
#if defined(A_HAVE_CCOS) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(ccos)(*x);
#elif defined(A_HAVE_CCOS)
    *ctx = A_FLOAT_F(ccos)(*ctx);
#else /* !A_HAVE_CCOS */
    if (ctx->imag != 0)
    {
        a_float const real = ctx->real;
        ctx->real = a_float_cos(real) * a_float_cosh(+ctx->imag);
        ctx->imag = a_float_sin(real) * a_float_sinh(-ctx->imag);
    }
    else
    {
        ctx->real = a_float_cos(ctx->real);
    }
#endif /* A_HAVE_CCOS */
}

#if defined(A_HAVE_CTAN) && (A_HAVE_CTAN + 0 < 1)
#undef A_HAVE_CTAN
#endif /* A_HAVE_CTAN */
#if defined(A_HAVE_CTAN) && !defined A_COMPLEX
a_complex A_FLOAT_F(ctan)(a_complex);
#endif /* A_HAVE_CTAN */
void a_complex_tan_(a_complex *ctx)
{
#if defined(A_HAVE_CTAN) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(ctan)(*x);
#elif defined(A_HAVE_CTAN)
    *ctx = A_FLOAT_F(ctan)(*ctx);
#else /* !A_HAVE_CTAN */
    a_float const cr = a_float_cos(ctx->real);
    a_float const si = a_float_sinh(ctx->imag);
    a_float const den = cr * cr + si * si;
    ctx->real = A_FLOAT_C(0.5) * a_float_sin(2 * ctx->real) / den;
    if (a_float_abs(ctx->imag) < 1)
    {
        ctx->imag = A_FLOAT_C(0.5) * a_float_sinh(2 * ctx->imag) / den;
    }
    else
    {
        a_float const d = a_float_pow(cr / si, 2) + 1;
        ctx->imag = 1 / (a_float_tanh(ctx->imag) * d);
    }
#endif /* A_HAVE_CTAN */
}

void a_complex_sec_(a_complex *ctx)
{
    a_complex_cos_(ctx);
    a_complex_inv_(ctx);
}

void a_complex_csc_(a_complex *ctx)
{
    a_complex_sin_(ctx);
    a_complex_inv_(ctx);
}

void a_complex_cot_(a_complex *ctx)
{
    a_complex_tan_(ctx);
    a_complex_inv_(ctx);
}

#if defined(A_HAVE_CASIN) && (A_HAVE_CASIN + 0 < 1)
#undef A_HAVE_CASIN
#endif /* A_HAVE_CASIN */
#if defined(A_HAVE_CASIN) && !defined A_COMPLEX
a_complex A_FLOAT_F(casin)(a_complex);
#endif /* A_HAVE_CASIN */
void a_complex_asin_(a_complex *ctx)
{
#if defined(A_HAVE_CASIN) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(casin)(*x);
#elif defined(A_HAVE_CASIN)
    *ctx = A_FLOAT_F(casin)(*ctx);
#else /* !A_HAVE_CASIN */
    if (ctx->imag != 0)
    {
        a_float const a_crossover = A_FLOAT_C(1.5);
        a_float const b_crossover = A_FLOAT_C(0.6417);
        a_float const x = a_float_abs(ctx->real);
        a_float const y = a_float_abs(ctx->imag);
        a_float const r = a_float_hypot(x + 1, y);
        a_float const s = a_float_hypot(x - 1, y);
        a_float const a = A_FLOAT_C(0.5) * (r + s);
        a_float const b = x / a;
        a_float const y2 = y * y;
        a_float const real = ctx->real;
        a_float const imag = ctx->imag;
        if (b <= b_crossover)
        {
            ctx->real = a_float_asin(b);
        }
        else if (x <= 1)
        {
            a_float const den = A_FLOAT_C(0.5) * (a + x) * (y2 / (r + x + 1) + (s + 1 - x));
            ctx->real = a_float_atan(x / a_float_sqrt(den));
        }
        else
        {
            a_float const apx = a + x;
            a_float const den = A_FLOAT_C(0.5) * (apx / (r + x + 1) + apx / (s + x - 1));
            ctx->real = a_float_atan(x / (a_float_sqrt(den) * y));
        }
        if (a <= a_crossover)
        {
            a_float am1;
            if (x < 1)
            {
                am1 = A_FLOAT_C(0.5) * (y2 / (r + x + 1) + y2 / (s + 1 - x));
            }
            else
            {
                am1 = A_FLOAT_C(0.5) * (y2 / (r + x + 1) + (s + x - 1));
            }
            ctx->imag = a_float_log1p(am1 + a_float_sqrt((a + 1) * am1));
        }
        else
        {
            ctx->imag = a_float_log(a + a_float_sqrt(a * a - 1));
        }
        if (real < 0) { ctx->real = -ctx->real; }
        if (imag < 0) { ctx->imag = -ctx->imag; }
    }
    else
    {
        a_complex_asin_real(ctx, ctx->real);
    }
#endif /* A_HAVE_CASIN */
}

void a_complex_asin_real(a_complex *ctx, a_float x)
{
    if (a_float_abs(x) <= 1)
    {
        ctx->real = a_float_asin(x);
        ctx->imag = 0;
    }
    else
    {
        if (x > 0)
        {
            ctx->real = +A_FLOAT_PI_2;
            ctx->imag = -a_float_acosh(+x);
        }
        else
        {
            ctx->real = -A_FLOAT_PI_2;
            ctx->imag = +a_float_acosh(-x);
        }
    }
}

#if defined(A_HAVE_CACOS) && (A_HAVE_CACOS + 0 < 1)
#undef A_HAVE_CACOS
#endif /* A_HAVE_CACOS */
#if defined(A_HAVE_CACOS) && !defined A_COMPLEX
a_complex A_FLOAT_F(cacos)(a_complex);
#endif /* A_HAVE_CACOS */
void a_complex_acos_(a_complex *ctx)
{
#if defined(A_HAVE_CACOS) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(cacos)(*x);
#elif defined(A_HAVE_CACOS)
    *ctx = A_FLOAT_F(cacos)(*ctx);
#else /* !A_HAVE_CACOS */
    if (ctx->imag != 0)
    {
        a_float const a_crossover = A_FLOAT_C(1.5);
        a_float const b_crossover = A_FLOAT_C(0.6417);
        a_float const x = a_float_abs(ctx->real);
        a_float const y = a_float_abs(ctx->imag);
        a_float const r = a_float_hypot(x + 1, y);
        a_float const s = a_float_hypot(x - 1, y);
        a_float const a = A_FLOAT_C(0.5) * (r + s);
        a_float const b = x / a;
        a_float const y2 = y * y;
        a_float const real = ctx->real;
        a_float const imag = ctx->imag;
        if (b <= b_crossover)
        {
            ctx->real = a_float_acos(b);
        }
        else if (x <= 1)
        {
            a_float const den = A_FLOAT_C(0.5) * (a + x) * (y2 / (r + x + 1) + (s + 1 - x));
            ctx->real = a_float_atan(a_float_sqrt(den) / x);
        }
        else
        {
            a_float const apx = a + x;
            a_float const den = A_FLOAT_C(0.5) * (apx / (r + x + 1) + apx / (s + x - 1));
            ctx->real = a_float_atan(a_float_sqrt(den) * y / x);
        }
        if (a <= a_crossover)
        {
            a_float am1;
            if (x < 1)
            {
                am1 = A_FLOAT_C(0.5) * (y2 / (r + x + 1) + y2 / (s + 1 - x));
            }
            else
            {
                am1 = A_FLOAT_C(0.5) * (y2 / (r + x + 1) + (s + x - 1));
            }
            ctx->imag = a_float_log1p(am1 + a_float_sqrt((a + 1) * am1));
        }
        else
        {
            ctx->imag = a_float_log(a + a_float_sqrt(a * a - 1));
        }
        if (real < 0) { ctx->real = A_FLOAT_PI - ctx->real; }
        if (imag >= 0) { ctx->imag = -ctx->imag; }
    }
    else
    {
        a_complex_acos_real(ctx, ctx->real);
    }
#endif /* A_HAVE_CACOS */
}

void a_complex_acos_real(a_complex *ctx, a_float x)
{
    if (a_float_abs(x) <= 1)
    {
        ctx->real = a_float_acos(x);
        ctx->imag = 0;
    }
    else
    {
        if (x > 0)
        {
            ctx->real = 0;
            ctx->imag = +a_float_acosh(+x);
        }
        else
        {
            ctx->real = A_FLOAT_PI;
            ctx->imag = -a_float_acosh(-x);
        }
    }
}

#if defined(A_HAVE_CATAN) && (A_HAVE_CATAN + 0 < 1)
#undef A_HAVE_CATAN
#endif /* A_HAVE_CATAN */
#if defined(A_HAVE_CATAN) && !defined A_COMPLEX
a_complex A_FLOAT_F(catan)(a_complex);
#endif /* A_HAVE_CATAN */
void a_complex_atan_(a_complex *ctx)
{
#if defined(A_HAVE_CATAN) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(catan)(*x);
#elif defined(A_HAVE_CATAN)
    *ctx = A_FLOAT_F(catan)(*ctx);
#else /* !A_HAVE_CATAN */
    if (ctx->imag != 0)
    {
        a_float const r = a_float_hypot(ctx->real, ctx->imag);
        a_float const u = 2 * ctx->imag / (r * r + 1);
        a_float const imag = ctx->imag;
        if (a_float_abs(u) < A_FLOAT_C(0.1))
        {
            ctx->imag = A_FLOAT_C(0.25) * (a_float_log1p(u) - a_float_log1p(-u));
        }
        else
        {
            a_float const a = a_float_hypot(ctx->real, ctx->imag + 1);
            a_float const b = a_float_hypot(ctx->real, ctx->imag - 1);
            ctx->imag = A_FLOAT_C(0.5) * a_float_log(a / b);
        }
        if (ctx->real != 0)
        {
            ctx->real = A_FLOAT_C(0.5) * a_float_atan2(2 * ctx->real, (1 + r) * (1 - r));
        }
        else
        {
            if (imag > 1)
            {
                ctx->real = +A_FLOAT_PI;
            }
            else if (imag < -1)
            {
                ctx->real = -A_FLOAT_PI;
            }
            else
            {
                ctx->real = 0;
            }
        }
    }
    else
    {
        ctx->real = a_float_atan(ctx->real);
    }
#endif /* A_HAVE_CATAN */
}

void a_complex_asec_(a_complex *ctx)
{
    a_complex_inv_(ctx);
    a_complex_acos_(ctx);
}

void a_complex_asec_real(a_complex *ctx, a_float x)
{
    if (x <= -1 || x >= 1)
    {
        ctx->real = a_float_acos(1 / x);
        ctx->imag = 0;
    }
    else
    {
        if (x >= 0)
        {
            ctx->real = 0;
            ctx->imag = +a_float_acosh(+1 / x);
        }
        else
        {
            ctx->real = A_FLOAT_PI;
            ctx->imag = -a_float_acosh(-1 / x);
        }
    }
}

void a_complex_acsc_(a_complex *ctx)
{
    a_complex_inv_(ctx);
    a_complex_asin_(ctx);
}

void a_complex_acsc_real(a_complex *ctx, a_float x)
{
    if (x <= -1 || x >= 1)
    {
        ctx->real = a_float_asin(1 / x);
        ctx->imag = 0;
    }
    else
    {
        if (x >= 0)
        {
            ctx->real = +A_FLOAT_PI_2;
            ctx->imag = -a_float_acosh(+1 / x);
        }
        else
        {
            ctx->real = -A_FLOAT_PI_2;
            ctx->imag = +a_float_acosh(-1 / x);
        }
    }
}

void a_complex_acot_(a_complex *ctx)
{
    if (ctx->real != 0 || ctx->imag != 0)
    {
        a_complex_inv_(ctx);
        a_complex_atan_(ctx);
    }
    else
    {
        ctx->real = A_FLOAT_PI_2;
    }
}

#if defined(A_HAVE_CSINH) && (A_HAVE_CSINH + 0 < 1)
#undef A_HAVE_CSINH
#endif /* A_HAVE_CSINH */
#if defined(A_HAVE_CSINH) && !defined A_COMPLEX
a_complex A_FLOAT_F(csinh)(a_complex);
#endif /* A_HAVE_CSINH */
void a_complex_sinh_(a_complex *ctx)
{
#if defined(A_HAVE_CSINH) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(csinh)(*x);
#elif defined(A_HAVE_CSINH)
    *ctx = A_FLOAT_F(csinh)(*ctx);
#else /* !A_HAVE_CSINH */
    a_float const real = ctx->real;
    ctx->real = a_float_sinh(real) * a_float_cos(ctx->imag);
    ctx->imag = a_float_cosh(real) * a_float_sin(ctx->imag);
#endif /* A_HAVE_CSINH */
}

#if defined(A_HAVE_CCOSH) && (A_HAVE_CCOSH + 0 < 1)
#undef A_HAVE_CCOSH
#endif /* A_HAVE_CCOSH */
#if defined(A_HAVE_CCOSH) && !defined A_COMPLEX
a_complex A_FLOAT_F(ccosh)(a_complex);
#endif /* A_HAVE_CCOSH */
void a_complex_cosh_(a_complex *ctx)
{
#if defined(A_HAVE_CCOSH) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(ccosh)(*x);
#elif defined(A_HAVE_CCOSH)
    *ctx = A_FLOAT_F(ccosh)(*ctx);
#else /* !A_HAVE_CCOSH */
    a_float const real = ctx->real;
    ctx->real = a_float_cosh(real) * a_float_cos(ctx->imag);
    ctx->imag = a_float_sinh(real) * a_float_sin(ctx->imag);
#endif /* A_HAVE_CCOSH */
}

#if defined(A_HAVE_CTANH) && (A_HAVE_CTANH + 0 < 1)
#undef A_HAVE_CTANH
#endif /* A_HAVE_CTANH */
#if defined(A_HAVE_CTANH) && !defined A_COMPLEX
a_complex A_FLOAT_F(ctanh)(a_complex);
#endif /* A_HAVE_CTANH */
void a_complex_tanh_(a_complex *ctx)
{
#if defined(A_HAVE_CTANH) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(ctanh)(*x);
#elif defined(A_HAVE_CTANH)
    *ctx = A_FLOAT_F(ctanh)(*ctx);
#else /* !A_HAVE_CTANH */
    a_float const ci = a_float_cos(ctx->imag);
    a_float const sr = a_float_sinh(ctx->real);
    a_float const den = ci * ci + sr * sr;
    ctx->imag = A_FLOAT_C(0.5) * a_float_sin(2 * ctx->imag) / den;
    if (a_float_abs(ctx->real) < 1)
    {
        ctx->real = a_float_sinh(ctx->real) * a_float_cosh(ctx->real) / den;
    }
    else
    {
        a_float const d = a_float_pow(ci / sr, 2) + 1;
        ctx->real = 1 / (a_float_tanh(ctx->real) * d);
    }
#endif /* A_HAVE_CTANH */
}

void a_complex_sech_(a_complex *ctx)
{
    a_complex_cosh_(ctx);
    a_complex_inv_(ctx);
}

void a_complex_csch_(a_complex *ctx)
{
    a_complex_sinh_(ctx);
    a_complex_inv_(ctx);
}

void a_complex_coth_(a_complex *ctx)
{
    a_complex_tanh_(ctx);
    a_complex_inv_(ctx);
}

#if defined(A_HAVE_CASINH) && (A_HAVE_CASINH + 0 < 1)
#undef A_HAVE_CASINH
#endif /* A_HAVE_CASINH */
#if defined(A_HAVE_CASINH) && !defined A_COMPLEX
a_complex A_FLOAT_F(casinh)(a_complex);
#endif /* A_HAVE_CASINH */
void a_complex_asinh_(a_complex *ctx)
{
#if defined(A_HAVE_CASINH) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(casinh)(*x);
#elif defined(A_HAVE_CASINH)
    *ctx = A_FLOAT_F(casinh)(*ctx);
#else /* !A_HAVE_CASINH */
    a_complex_mul_imag_(ctx, +1);
    a_complex_asin_(ctx);
    a_complex_mul_imag_(ctx, -1);
#endif /* A_HAVE_CASINH */
}

#if defined(A_HAVE_CACOSH) && (A_HAVE_CACOSH + 0 < 1)
#undef A_HAVE_CACOSH
#endif /* A_HAVE_CACOSH */
#if defined(A_HAVE_CACOSH) && !defined A_COMPLEX
a_complex A_FLOAT_F(cacosh)(a_complex);
#endif /* A_HAVE_CACOSH */
void a_complex_acosh_(a_complex *ctx)
{
#if defined(A_HAVE_CACOSH) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(cacosh)(*x);
#elif defined(A_HAVE_CACOSH)
    *ctx = A_FLOAT_F(cacosh)(*ctx);
#else /* !A_HAVE_CACOSH */
    a_complex_acsc_(ctx);
    a_complex_mul_imag_(ctx, ctx->imag > 0 ? -1 : +1);
#endif /* A_HAVE_CACOSH */
}

void a_complex_acosh_real(a_complex *ctx, a_float x)
{
    if (x >= 1)
    {
        ctx->real = a_float_acosh(+x);
        ctx->imag = 0;
    }
    else if (x >= -1)
    {
        ctx->real = 0;
        ctx->imag = a_float_acos(x);
    }
    else
    {
        ctx->real = a_float_acosh(-x);
        ctx->imag = A_FLOAT_PI;
    }
}

#undef A_HAVE_CATANH
#if defined(A_HAVE_CATANH) && (A_HAVE_CATANH + 0 < 1)
#undef A_HAVE_CATANH
#endif /* A_HAVE_CATANH */
#if defined(A_HAVE_CATANH) && !defined A_COMPLEX
a_complex A_FLOAT_F(catanh)(a_complex);
#endif /* A_HAVE_CATANH */
void a_complex_atanh_(a_complex *ctx)
{
#if defined(A_HAVE_CATANH) && defined(A_COMPLEX)
    A_COMPLEX *const x = (A_COMPLEX *)ctx;
    *x = A_FLOAT_F(catanh)(*x);
#elif defined(A_HAVE_CATANH)
    *ctx = A_FLOAT_F(catanh)(*ctx);
#else /* !A_HAVE_CATANH */
    if (ctx->imag != 0)
    {
        a_complex_mul_imag_(ctx, +1);
        a_complex_atan_(ctx);
        a_complex_mul_imag_(ctx, -1);
    }
    else
    {
        a_complex_atanh_real(ctx, ctx->real);
    }
#endif /* A_HAVE_CATANH */
}

void a_complex_atanh_real(a_complex *ctx, a_float x)
{
    if (x > -1 && x < 1)
    {
        ctx->real = a_float_atanh(x);
        ctx->imag = 0;
    }
    else
    {
        ctx->real = a_float_atanh(1 / x);
        ctx->imag = (x < 0) ? +A_FLOAT_PI_2 : -A_FLOAT_PI_2;
    }
}

void a_complex_asech_(a_complex *ctx)
{
    a_complex_inv_(ctx);
    a_complex_acosh_(ctx);
}

void a_complex_acsch_(a_complex *ctx)
{
    a_complex_inv_(ctx);
    a_complex_asinh_(ctx);
}

void a_complex_acoth_(a_complex *ctx)
{
    a_complex_inv_(ctx);
    a_complex_atanh_(ctx);
}
