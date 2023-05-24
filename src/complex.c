#define LIBA_COMPLEX_C
#include "a/math.h"
#if A_PREREQ_GNUC(2, 95) || __has_warning("-Waggregate-return")
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* -Waggregate-return */
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */
#include "complex.h"

a_complex_s a_complex_polar(a_float_t const r, a_float_t const theta)
{
    a_complex_s z;
    z.real = r * a_float_cos(theta);
    z.imag = r * a_float_sin(theta);
    return z;
}

a_float_t a_complex_logabs(a_complex_s const z)
{
    a_float_t const xabs = a_float_abs(z.real);
    a_float_t const yabs = a_float_abs(z.imag);
    a_float_t max, u;
    if (xabs >= yabs)
    {
        max = xabs;
        u = yabs / xabs;
    }
    else
    {
        max = yabs;
        u = xabs / yabs;
    }
    return a_float_log(max) + a_float_log1p(u * u) * A_FLOAT_C(0.5);
}

a_float_t a_complex_abs2(a_complex_s const z)
{
    return z.real * z.real + z.imag * z.imag;
}

a_float_t a_complex_abs(a_complex_s const z)
{
    return a_float_hypot(z.real, z.imag);
}

a_float_t a_complex_arg(a_complex_s const z)
{
    if (z.real == 0 && z.imag == 0)
    {
        return 0;
    }
    return a_float_atan2(z.imag, z.real);
}

a_complex_s a_complex_add(a_complex_s x, a_complex_s const y)
{
    x.real += y.real;
    x.imag += y.imag;
    return x;
}

a_complex_s a_complex_add_real(a_complex_s x, a_float_t const y)
{
    x.real += y;
    return x;
}

a_complex_s a_complex_add_imag(a_complex_s x, a_float_t const y)
{
    x.imag += y;
    return x;
}

a_complex_s a_complex_sub(a_complex_s x, a_complex_s const y)
{
    x.real -= y.real;
    x.imag -= y.imag;
    return x;
}

a_complex_s a_complex_sub_real(a_complex_s x, a_float_t const y)
{
    x.real -= y;
    return x;
}

a_complex_s a_complex_sub_imag(a_complex_s x, a_float_t const y)
{
    x.imag -= y;
    return x;
}

a_complex_s a_complex_mul(a_complex_s x, a_complex_s const y)
{
    a_complex_s z;
    z.real = x.real * y.real - x.imag * y.imag;
    z.imag = x.real * y.imag + x.imag * y.real;
    return z;
}

a_complex_s a_complex_mul_real(a_complex_s x, a_float_t const y)
{
    x.real *= y;
    x.imag *= y;
    return x;
}

a_complex_s a_complex_mul_imag(a_complex_s x, a_float_t const y)
{
    a_complex_s z;
    z.real = -x.imag * y;
    z.imag = x.real * y;
    return z;
}

a_complex_s a_complex_div(a_complex_s x, a_complex_s y)
{
    a_complex_s z;
    a_float_t const inv = 1 / a_complex_abs(y);
    y.real *= inv;
    y.imag *= inv;
    z.real = (x.real * y.real + x.imag * y.imag) * inv;
    z.imag = (x.imag * y.real - x.real * y.imag) * inv;
    return z;
}

a_complex_s a_complex_div_real(a_complex_s x, a_float_t const y)
{
    x.real /= y;
    x.imag /= y;
    return x;
}

a_complex_s a_complex_div_imag(a_complex_s x, a_float_t const y)
{
    a_complex_s z;
    z.real = x.imag / y;
    z.imag = -x.real / y;
    return z;
}

a_complex_s a_complex_inv(a_complex_s z)
{
    a_float_t const inv = 1 / a_complex_abs(z);
    z.real *= inv;
    z.imag *= inv;
    z.real *= inv;
    z.imag *= -inv;
    return z;
}

#if A_PREREQ_GNUC(2, 95) || __has_warning("-Wimplicit-function-declaration")
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
#endif /* gcc 2.95+ */
#if __has_warning("-Wincompatible-library-redeclaration")
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"
#endif /* clang 4.0+ */
#if A_PREREQ_GNUC(10, 1)
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#endif /* gcc 10.1+ */

#if defined(A_HAVE_CSQRT) && (A_HAVE_CSQRT + 0 < 1)
#undef A_HAVE_CSQRT
#endif /* A_HAVE_CSQRT */
#if defined(A_HAVE_CSQRT) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(csqrt, a_complex_t);
#endif /* A_HAVE_CSQRT */
a_complex_s a_complex_sqrt(a_complex_s z)
{
#if defined(A_HAVE_CSQRT) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(csqrt, u.z);
    return u.s;
#elif defined(A_HAVE_CSQRT)
    return A_FLOAT_F1(csqrt, z);
#else /* !A_HAVE_CSQRT */
    if (z.real == 0 && z.imag == 0)
    {
        return z;
    }
    a_float_t const x = a_float_abs(z.real);
    a_float_t const y = a_float_abs(z.imag);
    a_float_t w;
    if (x >= y)
    {
        a_float_t t = y / x;
        w = a_float_sqrt(x) * a_float_sqrt((a_float_sqrt(t * t + 1) + 1) * A_FLOAT_C(0.5));
    }
    else
    {
        a_float_t t = x / y;
        w = a_float_sqrt(y) * a_float_sqrt((a_float_sqrt(t * t + 1) + t) * A_FLOAT_C(0.5));
    }
    if (z.real >= 0)
    {
        z.real = w;
        z.imag = z.imag / (w * 2);
        return z;
    }
    if (z.imag < 0)
    {
        w = -w;
    }
    z.real = z.imag / (w * 2);
    z.imag = w;
    return z;
#endif /* A_HAVE_CSQRT */
}

a_complex_s a_complex_sqrt_real(a_float_t const x)
{
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    if (x >= 0)
    {
        z.real = a_float_sqrt(x);
        return z;
    }
    z.imag = a_float_sqrt(-x);
    return z;
}

#if defined(A_HAVE_CPOW) && (A_HAVE_CPOW + 0 < 1)
#undef A_HAVE_CPOW
#endif /* A_HAVE_CPOW */
#if defined(A_HAVE_CPOW) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F2(cpow, a_complex_t, a_complex_t);
#endif /* A_HAVE_CPOW */
a_complex_s a_complex_pow(a_complex_s z, a_complex_s const a)
{
#if defined(A_HAVE_CPOW) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u, v;
    u.s = z;
    v.s = a;
    u.z = A_FLOAT_F2(cpow, u.z, v.z);
    return u.s;
#elif defined(A_HAVE_CPOW)
    return A_FLOAT_F2(cpow, z, a);
#else /* !A_HAVE_CPOW */
    if (z.real == 0 && z.imag == 0)
    {
        if (a.real == 0 && a.imag == 0)
        {
            z.real = A_FLOAT_C(1.0);
        }
        return z;
    }
    a_float_t const logr = a_complex_logabs(z);
    a_float_t const theta = a_complex_arg(z);
    a_float_t const rho = a_float_exp(logr * a.real - theta * a.imag);
    a_float_t const beta = theta * a.real + logr * a.imag;
    return a_complex_polar(rho, beta);
#endif /* A_HAVE_CPOW */
}

a_complex_s a_complex_pow_real(a_complex_s z, a_float_t const a)
{
    if (z.real == 0 && z.imag == 0)
    {
        if (a == 0)
        {
            z.real = A_FLOAT_C(1.0);
        }
        return z;
    }
    a_float_t const logr = a_complex_logabs(z);
    a_float_t const theta = a_complex_arg(z);
    a_float_t const rho = a_float_exp(logr * a);
    a_float_t const beta = theta * a;
    return a_complex_polar(rho, beta);
}

#if defined(A_HAVE_CEXP) && (A_HAVE_CEXP + 0 < 1)
#undef A_HAVE_CEXP
#endif /* A_HAVE_CEXP */
#if defined(A_HAVE_CEXP) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(cexp, a_complex_t);
#endif /* A_HAVE_CEXP */
a_complex_s a_complex_exp(a_complex_s z)
{
#if defined(A_HAVE_CEXP) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(cexp, u.z);
    return u.s;
#elif defined(A_HAVE_CEXP)
    return A_FLOAT_F1(cexp, z);
#else /* !A_HAVE_CEXP */
    a_float_t const rho = a_float_exp(z.real);
    return a_complex_polar(rho, z.imag);
#endif /* A_HAVE_CEXP */
}

#if defined(A_HAVE_CLOG) && (A_HAVE_CLOG + 0 < 1)
#undef A_HAVE_CLOG
#endif /* A_HAVE_CLOG */
#if defined(A_HAVE_CLOG) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(clog, a_complex_t);
#endif /* A_HAVE_CLOG */
a_complex_s a_complex_log(a_complex_s z)
{
#if defined(A_HAVE_CLOG) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(clog, u.z);
    return u.s;
#elif defined(A_HAVE_CLOG)
    return A_FLOAT_F1(clog, z);
#else /* !A_HAVE_CLOG */
    a_float_t const logr = a_complex_logabs(z);
    a_float_t const theta = a_complex_arg(z);
    z.real = logr;
    z.imag = theta;
    return z;
#endif /* A_HAVE_CLOG */
}

a_complex_s a_complex_log2(a_complex_s const z)
{
    return a_complex_mul_real(a_complex_log(z), 1 / A_FLOAT_LN2);
}

a_complex_s a_complex_log10(a_complex_s const z)
{
    return a_complex_mul_real(a_complex_log(z), 1 / A_FLOAT_LN10);
}

a_complex_s a_complex_logb(a_complex_s const z, a_complex_s const b)
{
    return a_complex_div(a_complex_log(z), a_complex_log(b));
}

#if defined(A_HAVE_CSIN) && (A_HAVE_CSIN + 0 < 1)
#undef A_HAVE_CSIN
#endif /* A_HAVE_CSIN */
#if defined(A_HAVE_CSIN) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(csin, a_complex_t);
#endif /* A_HAVE_CSIN */
a_complex_s a_complex_sin(a_complex_s z)
{
#if defined(A_HAVE_CSIN) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(csin, u.z);
    return u.s;
#elif defined(A_HAVE_CSIN)
    return A_FLOAT_F1(csin, z);
#else /* !A_HAVE_CSIN */
    if (z.imag == 0)
    {
        z.real = a_float_sin(z.real);
        return z;
    }
    z.real = a_float_sin(z.real) * a_float_cosh(z.imag);
    z.imag = a_float_cos(z.real) * a_float_sinh(z.imag);
    return z;
#endif /* A_HAVE_CSIN */
}

#if defined(A_HAVE_CCOS) && (A_HAVE_CCOS + 0 < 1)
#undef A_HAVE_CCOS
#endif /* A_HAVE_CCOS */
#if defined(A_HAVE_CCOS) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(ccos, a_complex_t);
#endif /* A_HAVE_CCOS */
a_complex_s a_complex_cos(a_complex_s z)
{
#if defined(A_HAVE_CCOS) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(ccos, u.z);
    return u.s;
#elif defined(A_HAVE_CCOS)
    return A_FLOAT_F1(ccos, z);
#else /* !A_HAVE_CCOS */
    if (z.imag == 0)
    {
        z.real = a_float_cos(z.real);
        return z;
    }
    z.real = a_float_cos(z.real) * a_float_cosh(z.imag);
    z.imag = a_float_sin(z.real) * a_float_sinh(-z.imag);
    return z;
#endif /* A_HAVE_CCOS */
}

#if defined(A_HAVE_CTAN) && (A_HAVE_CTAN + 0 < 1)
#undef A_HAVE_CTAN
#endif /* A_HAVE_CTAN */
#if defined(A_HAVE_CTAN) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(ctan, a_complex_t);
#endif /* A_HAVE_CTAN */
a_complex_s a_complex_tan(a_complex_s z)
{
#if defined(A_HAVE_CTAN) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(ctan, u.z);
    return u.s;
#elif defined(A_HAVE_CTAN)
    return A_FLOAT_F1(ctan, z);
#else /* !A_HAVE_CTAN */
    a_float_t const cr = a_float_cos(z.real);
    a_float_t const si = a_float_sinh(z.imag);
    a_float_t const inv = A_FLOAT_C(0.5) / (cr * cr + si * si);
    z.real = a_float_sin(z.real * 2) * inv;
    if (a_float_abs(z.imag) < 1)
    {
        z.imag = a_float_sinh(z.imag * 2) * inv;
        return z;
    }
    a_float_t const den = a_float_pow(cr / si, 2) + 1;
    z.imag = 1 / (a_float_tanh(z.imag) * den);
    return z;
#endif /* A_HAVE_CTAN */
}

a_complex_s a_complex_sec(a_complex_s const z)
{
    return a_complex_inv(a_complex_cos(z));
}

a_complex_s a_complex_csc(a_complex_s const z)
{
    return a_complex_inv(a_complex_sin(z));
}

a_complex_s a_complex_cot(a_complex_s const z)
{
    return a_complex_inv(a_complex_tan(z));
}

#if defined(A_HAVE_CASIN) && (A_HAVE_CASIN + 0 < 1)
#undef A_HAVE_CASIN
#endif /* A_HAVE_CASIN */
#if defined(A_HAVE_CASIN) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(casin, a_complex_t);
#endif /* A_HAVE_CASIN */
a_complex_s a_complex_asin(a_complex_s z)
{
#if defined(A_HAVE_CASIN) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(casin, u.z);
    return u.s;
#elif defined(A_HAVE_CASIN)
    return A_FLOAT_F1(casin, z);
#else /* !A_HAVE_CASIN */
    if (z.imag == 0)
    {
        return a_complex_asin_real(z.real);
    }
    a_float_t const a_crossover = A_FLOAT_C(1.5);
    a_float_t const b_crossover = A_FLOAT_C(0.6417);
    a_float_t const x = a_float_abs(z.real);
    a_float_t const y = a_float_abs(z.imag);
    a_float_t const r = a_float_hypot(x + 1, y);
    a_float_t const s = a_float_hypot(x - 1, y);
    a_float_t const a = A_FLOAT_C(0.5) * (r + s);
    a_float_t const b = x / a;
    a_float_t const y2 = y * y;
    a_float_t const real = z.real;
    if (b <= b_crossover)
    {
        z.real = a_float_asin(b);
    }
    else if (x <= 1)
    {
        a_float_t const den = A_FLOAT_C(0.5) * (a + x) * (y2 / (r + x + 1) + (s + 1 - x));
        z.real = a_float_atan(x / a_float_sqrt(den));
    }
    else
    {
        a_float_t const ax = a + x;
        a_float_t const den = A_FLOAT_C(0.5) * (ax / (r + x + 1) + ax / (s + x - 1));
        z.real = a_float_atan(x / (a_float_sqrt(den) * y));
    }
    if (real < 0)
    {
        z.real = -z.real;
    }
    a_float_t const imag = z.imag;
    if (a <= a_crossover)
    {
        a_float_t a1;
        if (x < 1)
        {
            a1 = A_FLOAT_C(0.5) * (y2 / (r + x + 1) + y2 / (s + 1 - x));
        }
        else
        {
            a1 = A_FLOAT_C(0.5) * (y2 / (r + x + 1) + (s + x - 1));
        }
        z.imag = a_float_log1p(a1 + a_float_sqrt((a + 1) * a1));
    }
    else
    {
        z.imag = a_float_log(a + a_float_sqrt(a * a - 1));
    }
    if (imag < 0)
    {
        z.imag = -z.imag;
    }
    return z;
#endif /* A_HAVE_CASIN */
}

a_complex_s a_complex_asin_real(a_float_t const x)
{
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    if (a_float_abs(x) <= 1)
    {
        z.real = a_float_asin(0);
        return z;
    }
    if (x < 0)
    {
        z.imag = a_float_acosh(-x);
        z.real = -A_FLOAT_PI_2;
        return z;
    }
    z.imag = -a_float_acosh(x);
    z.real = A_FLOAT_PI_2;
    return z;
}

#if defined(A_HAVE_CACOS) && (A_HAVE_CACOS + 0 < 1)
#undef A_HAVE_CACOS
#endif /* A_HAVE_CACOS */
#if defined(A_HAVE_CACOS) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(cacos, a_complex_t);
#endif /* A_HAVE_CACOS */
a_complex_s a_complex_acos(a_complex_s z)
{
#if defined(A_HAVE_CACOS) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(cacos, u.z);
    return u.s;
#elif defined(A_HAVE_CACOS)
    return A_FLOAT_F1(cacos, z);
#else /* !A_HAVE_CACOS */
    if (z.imag == 0)
    {
        return a_complex_acos_real(z.real);
    }
    a_float_t const a_crossover = A_FLOAT_C(1.5);
    a_float_t const b_crossover = A_FLOAT_C(0.6417);
    a_float_t const x = a_float_abs(z.real);
    a_float_t const y = a_float_abs(z.imag);
    a_float_t const r = a_float_hypot(x + 1, y);
    a_float_t const s = a_float_hypot(x - 1, y);
    a_float_t const a = A_FLOAT_C(0.5) * (r + s);
    a_float_t const b = x / a;
    a_float_t const y2 = y * y;
    a_float_t const real = z.real;
    if (b <= b_crossover)
    {
        z.real = a_float_acos(b);
    }
    else if (x <= 1)
    {
        a_float_t const den = A_FLOAT_C(0.5) * (a + x) * (y2 / (r + x + 1) + (s + 1 - x));
        z.real = a_float_atan(a_float_sqrt(den) / x);
    }
    else
    {
        a_float_t const ax = a + x;
        a_float_t const den = A_FLOAT_C(0.5) * (ax / (r + x + 1) + ax / (s + x - 1));
        z.real = a_float_atan(a_float_sqrt(den) * y / x);
    }
    if (real < 0)
    {
        z.real = A_FLOAT_PI - z.real;
    }
    a_float_t const imag = z.imag;
    if (a <= a_crossover)
    {
        a_float_t a1;
        if (x < 1)
        {
            a1 = A_FLOAT_C(0.5) * (y2 / (r + x + 1) + y2 / (s + 1 - x));
        }
        else
        {
            a1 = A_FLOAT_C(0.5) * (y2 / (r + x + 1) + (s + x - 1));
        }
        z.imag = a_float_log1p(a1 + a_float_sqrt((a + 1) * a1));
    }
    else
    {
        z.imag = a_float_log(a + a_float_sqrt(a * a - 1));
    }
    if (imag >= 0)
    {
        z.imag = -z.imag;
    }
    return z;
#endif /* A_HAVE_CACOS */
}

a_complex_s a_complex_acos_real(a_float_t const x)
{
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    if (a_float_abs(x) <= 1)
    {
        z.real = a_float_acos(0);
        return z;
    }
    if (x < 0)
    {
        z.imag = -a_float_acosh(-x);
        z.real = A_FLOAT_PI;
        return z;
    }
    z.imag = a_float_acosh(x);
    return z;
}

#if defined(A_HAVE_CATAN) && (A_HAVE_CATAN + 0 < 1)
#undef A_HAVE_CATAN
#endif /* A_HAVE_CATAN */
#if defined(A_HAVE_CATAN) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(catan, a_complex_t);
#endif /* A_HAVE_CATAN */
a_complex_s a_complex_atan(a_complex_s z)
{
#if defined(A_HAVE_CATAN) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(catan, u.z);
    return u.s;
#elif defined(A_HAVE_CATAN)
    return A_FLOAT_F1(catan, z);
#else /* !A_HAVE_CATAN */
    if (z.imag == 0)
    {
        z.real = a_float_atan(z.real);
        return z;
    }
    a_float_t const r = a_float_hypot(z.real, z.imag);
    a_float_t const u = 2 * z.imag / (r * r + 1);
    a_float_t const imag = z.imag;
    if (a_float_abs(u) < 0.1)
    {
        z.imag = A_FLOAT_C(0.25) * (a_float_log1p(u) - a_float_log1p(-u));
    }
    else
    {
        a_float_t const a = a_float_hypot(z.real, z.imag + 1);
        a_float_t const b = a_float_hypot(z.real, z.imag - 1);
        z.imag = A_FLOAT_C(0.5) * a_float_log(a / b);
    }
    if (z.real == 0)
    {
        if (imag > 1)
        {
            z.real = A_FLOAT_PI;
        }
        else if (imag < -1)
        {
            z.real = -A_FLOAT_PI;
        }
        return z;
    }
    z.real = A_FLOAT_C(0.5) * a_float_atan2(z.real * 2, (1 + r) * (1 - r));
    return z;
#endif /* A_HAVE_CATAN */
}

a_complex_s a_complex_asec(a_complex_s const z)
{
    return a_complex_acos(a_complex_inv(z));
}

a_complex_s a_complex_asec_real(a_float_t const x)
{
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    if (x <= -1 || x >= 1)
    {
        z.real = a_float_acos(1 / x);
        return z;
    }
    if (x >= 0)
    {
        z.imag = a_float_acosh(1 / x);
        return z;
    }
    z.imag = -a_float_acosh(-1 / x);
    z.real = A_FLOAT_PI;
    return z;
}

a_complex_s a_complex_acsc(a_complex_s const z)
{
    return a_complex_asin(a_complex_inv(z));
}

a_complex_s a_complex_acsc_real(a_float_t const x)
{
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    if (x <= -1 || x >= 1)
    {
        z.real = a_float_asin(1 / x);
        return z;
    }
    if (x >= 0)
    {
        z.imag = -a_float_acosh(1 / x);
        z.real = A_FLOAT_PI_2;
        return z;
    }
    z.imag = a_float_acosh(-1 / x);
    z.real = -A_FLOAT_PI_2;
    return z;
}

a_complex_s a_complex_acot(a_complex_s z)
{
    if (z.real == 0 && z.imag == 0)
    {
        z.real = A_FLOAT_PI_2;
        return z;
    }
    return a_complex_atan(a_complex_inv(z));
}

#if defined(A_HAVE_CSINH) && (A_HAVE_CSINH + 0 < 1)
#undef A_HAVE_CSINH
#endif /* A_HAVE_CSINH */
#if defined(A_HAVE_CSINH) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(csinh, a_complex_t);
#endif /* A_HAVE_CSINH */
a_complex_s a_complex_sinh(a_complex_s z)
{
#if defined(A_HAVE_CSINH) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(csinh, u.z);
    return u.s;
#elif defined(A_HAVE_CSINH)
    return A_FLOAT_F1(csinh, z);
#else /* !A_HAVE_CSINH */
    a_float_t const real = z.real;
    a_float_t const imag = z.imag;
    z.real = a_float_sinh(real) * a_float_cos(imag);
    z.imag = a_float_cosh(real) * a_float_sin(imag);
    return z;
#endif /* A_HAVE_CSINH */
}

#if defined(A_HAVE_CCOSH) && (A_HAVE_CCOSH + 0 < 1)
#undef A_HAVE_CCOSH
#endif /* A_HAVE_CCOSH */
#if defined(A_HAVE_CCOSH) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(ccosh, a_complex_t);
#endif /* A_HAVE_CCOSH */
a_complex_s a_complex_cosh(a_complex_s z)
{
#if defined(A_HAVE_CCOSH) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(ccosh, u.z);
    return u.s;
#elif defined(A_HAVE_CCOSH)
    return A_FLOAT_F1(ccosh, z);
#else /* !A_HAVE_CCOSH */
    a_float_t const real = z.real;
    a_float_t const imag = z.imag;
    z.real = a_float_cosh(real) * a_float_cos(imag);
    z.imag = a_float_sinh(real) * a_float_sin(imag);
    return z;
#endif /* A_HAVE_CCOSH */
}

#if defined(A_HAVE_CTANH) && (A_HAVE_CTANH + 0 < 1)
#undef A_HAVE_CTANH
#endif /* A_HAVE_CTANH */
#if defined(A_HAVE_CTANH) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(ctanh, a_complex_t);
#endif /* A_HAVE_CTANH */
a_complex_s a_complex_tanh(a_complex_s z)
{
#if defined(A_HAVE_CTANH) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(ctanh, u.z);
    return u.s;
#elif defined(A_HAVE_CTANH)
    return A_FLOAT_F1(ctanh, z);
#else /* !A_HAVE_CTANH */
    a_float_t const ci = a_float_cos(z.imag);
    a_float_t const sr = a_float_sinh(z.real);
    a_float_t const inv = 1 / (ci * ci + sr * sr);
    z.imag = a_float_sin(z.imag * 2) * inv * A_FLOAT_C(0.5);
    if (a_float_abs(z.real) < 1)
    {
        z.real = a_float_sinh(z.real) * a_float_cosh(z.real) * inv;
        return z;
    }
    a_float_t const den = a_float_pow(ci / sr, 2) + 1;
    z.real = 1 / (a_float_tanh(z.real) * den);
    return z;
#endif /* A_HAVE_CTANH */
}

a_complex_s a_complex_sech(a_complex_s const z)
{
    return a_complex_inv(a_complex_cosh(z));
}

a_complex_s a_complex_csch(a_complex_s const z)
{
    return a_complex_inv(a_complex_sinh(z));
}

a_complex_s a_complex_coth(a_complex_s const z)
{
    return a_complex_inv(a_complex_tanh(z));
}

#if defined(A_HAVE_CASINH) && (A_HAVE_CASINH + 0 < 1)
#undef A_HAVE_CASINH
#endif /* A_HAVE_CASINH */
#if defined(A_HAVE_CASINH) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(casinh, a_complex_t);
#endif /* A_HAVE_CASINH */
a_complex_s a_complex_asinh(a_complex_s z)
{
#if defined(A_HAVE_CASINH) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(casinh, u.z);
    return u.s;
#elif defined(A_HAVE_CASINH)
    return A_FLOAT_F1(casinh, z);
#else /* !A_HAVE_CASINH */
    z = a_complex_mul_imag(z, 1);
    z = a_complex_asin(z);
    return a_complex_mul_imag(z, -1);
#endif /* A_HAVE_CASINH */
}

#if defined(A_HAVE_CACOSH) && (A_HAVE_CACOSH + 0 < 1)
#undef A_HAVE_CACOSH
#endif /* A_HAVE_CACOSH */
#if defined(A_HAVE_CACOSH) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(cacosh, a_complex_t);
#endif /* A_HAVE_CACOSH */
a_complex_s a_complex_acosh(a_complex_s z)
{
#if defined(A_HAVE_CACOSH) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(cacosh, u.z);
    return u.s;
#elif defined(A_HAVE_CACOSH)
    return A_FLOAT_F1(cacosh, z);
#else /* !A_HAVE_CACOSH */
    z = a_complex_acsc(z);
    return a_complex_mul_imag(z, z.imag > 0 ? -1 : 1);
#endif /* A_HAVE_CACOSH */
}

a_complex_s a_complex_acosh_real(a_float_t const x)
{
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    if (x >= 1)
    {
        z.real = a_float_acosh(x);
        return z;
    }
    if (x >= -1)
    {
        z.imag = a_float_acos(x);
        return z;
    }
    z.real = a_float_acos(-x);
    z.imag = A_FLOAT_PI;
    return z;
}

#if defined(A_HAVE_CATANH) && (A_HAVE_CATANH + 0 < 1)
#undef A_HAVE_CATANH
#endif /* A_HAVE_CATANH */
#if defined(A_HAVE_CATANH) && !defined A_COMPLEX_T
a_complex_t A_FLOAT_F1(catanh, a_complex_t);
#endif /* A_HAVE_CATANH */
a_complex_s a_complex_atanh(a_complex_s z)
{
#if defined(A_HAVE_CATANH) && defined(A_COMPLEX_T)
    union
    {
        a_complex_s s;
        A_COMPLEX_T z;
    } u;
    u.s = z;
    u.z = A_FLOAT_F1(catanh, u.z);
    return u.s;
#elif defined(A_HAVE_CATANH)
    return A_FLOAT_F1(catanh, z);
#else /* !A_HAVE_CATANH */
    if (z.imag == 0)
    {
        return a_complex_atanh_real(z.real);
    }
    z = a_complex_mul_imag(z, 1);
    z = a_complex_atan(z);
    return a_complex_mul_imag(z, -1);
#endif /* A_HAVE_CATANH */
}

a_complex_s a_complex_atanh_real(a_float_t const x)
{
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    if (x > -1 && x < 1)
    {
        z.real = a_float_atanh(x);
        return z;
    }
    z.real = a_float_atanh(1 / x);
    if (x < 0)
    {
        z.imag = A_FLOAT_PI_2;
        return z;
    }
    z.imag = -A_FLOAT_PI_2;
    return z;
}

a_complex_s a_complex_asech(a_complex_s const z)
{
    return a_complex_acosh(a_complex_inv(z));
}

a_complex_s a_complex_acsch(a_complex_s const z)
{
    return a_complex_asinh(a_complex_inv(z));
}

a_complex_s a_complex_acoth(a_complex_s const z)
{
    return a_complex_atanh(a_complex_inv(z));
}
