#include "a/a.h"
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */
#include "a/complex.h"
/* compiler built-in complex number type */
#if A_PREREQ_MSVC(18, 0)
#include <complex.h> // 12.0
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
#endif /* A_FLOAT_TYPE */
#include "a/math.h"

void a_complex_polar(a_complex *_z, a_float rho, a_float theta)
{
    _z->real = rho * a_float_cos(theta);
    _z->imag = rho * a_float_sin(theta);
}

unsigned int a_complex_parse(a_complex *_z, char const *str)
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
    for (_z->real = 0; *u.s; ++u.s)
    {
        if (*u.s == '+' || *u.s == '-' || ('0' <= *u.s && *u.s <= '9') || *u.s == '.')
        {
            _z->real = strtonum(u.s, &u.p);
            break;
        }
    }
    for (_z->imag = 0; *u.s; ++u.s)
    {
        if (*u.s == '+' || *u.s == '-' || ('0' <= *u.s && *u.s <= '9') || *u.s == '.')
        {
            _z->imag = strtonum(u.s, &u.p);
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

void a_complex_proj(a_complex *_z, a_complex z)
{
    *_z = z;
#if defined(__MINGW32__) && A_PREREQ_GNUC(3, 0)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif /* __MINGW32__ */
    if (isinf(z.real) || isinf(z.imag))
    {
        _z->real = A_FLOAT_INF;
        _z->imag = a_float_copysign(0, z.imag);
    }
#if defined(__MINGW32__) && A_PREREQ_GNUC(3, 0)
#pragma GCC diagnostic pop
#endif /* __MINGW32__ */
}

void a_complex_conj(a_complex *_z, a_complex z)
{
    _z->real = +z.real;
    _z->imag = -z.imag;
}

void a_complex_neg(a_complex *_z, a_complex z)
{
    _z->real = -z.real;
    _z->imag = -z.imag;
}

void a_complex_add(a_complex *_z, a_complex x, a_complex y)
{
    _z->real = x.real + y.real;
    _z->imag = x.imag + y.imag;
}

void a_complex_add_real(a_complex *_z, a_complex x, a_float y)
{
    _z->real = x.real + y;
    _z->imag = x.imag;
}

void a_complex_add_imag(a_complex *_z, a_complex x, a_float y)
{
    _z->real = x.real;
    _z->imag = x.imag + y;
}

void a_complex_sub(a_complex *_z, a_complex x, a_complex y)
{
    _z->real = x.real - y.real;
    _z->imag = x.imag - y.imag;
}

void a_complex_sub_real(a_complex *_z, a_complex x, a_float y)
{
    _z->real = x.real - y;
    _z->imag = x.imag;
}

void a_complex_sub_imag(a_complex *_z, a_complex x, a_float y)
{
    _z->real = x.real;
    _z->imag = x.imag - y;
}

void a_complex_mul(a_complex *_z, a_complex x, a_complex y)
{
    _z->real = x.real * y.real - x.imag * y.imag;
    _z->imag = x.real * y.imag + x.imag * y.real;
}

void a_complex_mul_real(a_complex *_z, a_complex x, a_float y)
{
    _z->real = x.real * y;
    _z->imag = x.imag * y;
}

void a_complex_mul_imag(a_complex *_z, a_complex x, a_float y)
{
    _z->real = -x.imag * y;
    _z->imag = +x.real * y;
}

void a_complex_div(a_complex *_z, a_complex x, a_complex y)
{
    a_float const inv = 1 / a_complex_abs(y);
    x.real *= inv;
    x.imag *= inv;
    y.real *= inv;
    y.imag *= inv;
    _z->real = x.real * y.real + x.imag * y.imag;
    _z->imag = x.imag * y.real - x.real * y.imag;
}

void a_complex_div_real(a_complex *_z, a_complex x, a_float y)
{
    _z->real = x.real / y;
    _z->imag = x.imag / y;
}

void a_complex_div_imag(a_complex *_z, a_complex x, a_float y)
{
    _z->real = +x.imag / y;
    _z->imag = -x.real / y;
}

void a_complex_inv(a_complex *_z, a_complex z)
{
    a_float const inv = 1 / a_complex_abs(z);
    _z->real = +inv * z.real * inv;
    _z->imag = -inv * z.imag * inv;
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
#if defined(A_HAVE_CSQRT) && !defined A_COMPLEX
a_complex A_FLOAT_F1(csqrt, a_complex);
#endif /* A_HAVE_CSQRT */
void a_complex_sqrt(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CSQRT) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(csqrt, *u.z);
#elif defined(A_HAVE_CSQRT)
    *_z = A_FLOAT_F1(csqrt, z);
#else /* !A_HAVE_CSQRT */
    if (z.real != 0 || z.imag != 0)
    {
        a_float const x = a_float_abs(z.real);
        a_float const y = a_float_abs(z.imag);
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
        if (z.real >= 0)
        {
            _z->real = w;
            _z->imag = z.imag / (2 * w);
        }
        else
        {
            _z->real = z.imag / (2 * w);
            _z->imag = z.imag < 0 ? -w : w;
        }
    }
    else
    {
        _z->real = 0;
        _z->imag = 0;
    }
#endif /* A_HAVE_CSQRT */
}

void a_complex_sqrt_real(a_complex *_z, a_float x)
{
    if (x >= 0)
    {
        _z->real = a_float_sqrt(x);
        _z->imag = 0;
    }
    else
    {
        _z->real = 0;
        _z->imag = a_float_sqrt(-x);
    }
}

#if defined(A_HAVE_CPOW) && (A_HAVE_CPOW + 0 < 1)
#undef A_HAVE_CPOW
#endif /* A_HAVE_CPOW */
#if defined(A_HAVE_CPOW) && !defined A_COMPLEX
a_complex A_FLOAT_F2(cpow, a_complex, a_complex);
#endif /* A_HAVE_CPOW */
void a_complex_pow(a_complex *_z, a_complex z, a_complex a)
{
#if defined(A_HAVE_CPOW) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v, w;
    u._z = &z;
    v._z = &a;
    w._z = _z;
    *w.z = A_FLOAT_F2(cpow, *u.z, *v.z);
#elif defined(A_HAVE_CPOW)
    *_z = A_FLOAT_F2(cpow, z, a);
#else /* !A_HAVE_CPOW */
    if (z.real != 0 || z.imag != 0)
    {
        a_float const logr = a_complex_logabs(z);
        a_float const theta = a_complex_arg(z);
        a_float const rho = a_float_exp(logr * a.real - theta * a.imag);
        a_float const beta = theta * a.real + logr * a.imag;
        a_complex_polar(_z, rho, beta);
    }
    else
    {
        _z->real = (a.real == 0 && a.imag == 0) ? 1 : 0;
        _z->imag = 0;
    }
#endif /* A_HAVE_CPOW */
}

void a_complex_pow_real(a_complex *_z, a_complex z, a_float a)
{
    if (z.real != 0 || z.imag != 0)
    {
        a_float const logr = a_complex_logabs(z);
        a_float const theta = a_complex_arg(z);
        a_float const rho = a_float_exp(logr * a);
        a_float const beta = theta * a;
        a_complex_polar(_z, rho, beta);
    }
    else
    {
        _z->real = (a == 0) ? 1 : 0;
        _z->imag = 0;
    }
}

#if defined(A_HAVE_CEXP) && (A_HAVE_CEXP + 0 < 1)
#undef A_HAVE_CEXP
#endif /* A_HAVE_CEXP */
#if defined(A_HAVE_CEXP) && !defined A_COMPLEX
a_complex A_FLOAT_F1(cexp, a_complex);
#endif /* A_HAVE_CEXP */
void a_complex_exp(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CEXP) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(cexp, *u.z);
#elif defined(A_HAVE_CEXP)
    *_z = A_FLOAT_F1(cexp, z);
#else /* !A_HAVE_CEXP */
    a_complex_polar(_z, a_float_exp(z.real), z.imag);
#endif /* A_HAVE_CEXP */
}

#if defined(A_HAVE_CLOG) && (A_HAVE_CLOG + 0 < 1)
#undef A_HAVE_CLOG
#endif /* A_HAVE_CLOG */
#if defined(A_HAVE_CLOG) && !defined A_COMPLEX
a_complex A_FLOAT_F1(clog, a_complex);
#endif /* A_HAVE_CLOG */
void a_complex_log(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CLOG) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(clog, *u.z);
#elif defined(A_HAVE_CLOG)
    *_z = A_FLOAT_F1(clog, z);
#else /* !A_HAVE_CLOG */
    _z->real = a_complex_logabs(z);
    _z->imag = a_complex_arg(z);
#endif /* A_HAVE_CLOG */
}

void a_complex_log2(a_complex *_z, a_complex z)
{
    a_complex_log(&z, z);
    a_complex_mul_real(_z, z, 1 / A_FLOAT_LN2);
}

void a_complex_log10(a_complex *_z, a_complex z)
{
    a_complex_log(&z, z);
    a_complex_mul_real(_z, z, 1 / A_FLOAT_LN10);
}

void a_complex_logb(a_complex *_z, a_complex z, a_complex b)
{
    a_complex_log(&z, z);
    a_complex_log(&b, b);
    a_complex_div(_z, z, b);
}

#if defined(A_HAVE_CSIN) && (A_HAVE_CSIN + 0 < 1)
#undef A_HAVE_CSIN
#endif /* A_HAVE_CSIN */
#if defined(A_HAVE_CSIN) && !defined A_COMPLEX
a_complex A_FLOAT_F1(csin, a_complex);
#endif /* A_HAVE_CSIN */
void a_complex_sin(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CSIN) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(csin, *u.z);
#elif defined(A_HAVE_CSIN)
    *_z = A_FLOAT_F1(csin, z);
#else /* !A_HAVE_CSIN */
    if (z.imag != 0)
    {
        _z->real = a_float_sin(z.real) * a_float_cosh(z.imag);
        _z->imag = a_float_cos(z.real) * a_float_sinh(z.imag);
    }
    else
    {
        _z->real = a_float_sin(z.real);
        _z->imag = 0;
    }
#endif /* A_HAVE_CSIN */
}

#if defined(A_HAVE_CCOS) && (A_HAVE_CCOS + 0 < 1)
#undef A_HAVE_CCOS
#endif /* A_HAVE_CCOS */
#if defined(A_HAVE_CCOS) && !defined A_COMPLEX
a_complex A_FLOAT_F1(ccos, a_complex);
#endif /* A_HAVE_CCOS */
void a_complex_cos(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CCOS) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(ccos, *u.z);
#elif defined(A_HAVE_CCOS)
    *_z = A_FLOAT_F1(ccos, z);
#else /* !A_HAVE_CCOS */
    if (z.imag != 0)
    {
        _z->real = a_float_cos(z.real) * a_float_cosh(+z.imag);
        _z->imag = a_float_sin(z.real) * a_float_sinh(-z.imag);
    }
    else
    {
        _z->real = a_float_cos(z.real);
        _z->imag = 0;
    }
#endif /* A_HAVE_CCOS */
}

#if defined(A_HAVE_CTAN) && (A_HAVE_CTAN + 0 < 1)
#undef A_HAVE_CTAN
#endif /* A_HAVE_CTAN */
#if defined(A_HAVE_CTAN) && !defined A_COMPLEX
a_complex A_FLOAT_F1(ctan, a_complex);
#endif /* A_HAVE_CTAN */
void a_complex_tan(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CTAN) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(ctan, *u.z);
#elif defined(A_HAVE_CTAN)
    *_z = A_FLOAT_F1(ctan, z);
#else /* !A_HAVE_CTAN */
    a_float const cr = a_float_cos(z.real);
    a_float const si = a_float_sinh(z.imag);
    a_float const inv = A_FLOAT_C(0.5) / (cr * cr + si * si);
    _z->real = a_float_sin(2 * z.real) * inv;
    if (a_float_abs(z.imag) < 1)
    {
        _z->imag = a_float_sinh(2 * z.imag) * inv;
    }
    else
    {
        a_float const den = a_float_pow(cr / si, 2) + 1;
        _z->imag = 1 / (a_float_tanh(z.imag) * den);
    }
#endif /* A_HAVE_CTAN */
}

void a_complex_sec(a_complex *_z, a_complex z)
{
    a_complex_cos(&z, z);
    a_complex_inv(_z, z);
}

void a_complex_csc(a_complex *_z, a_complex z)
{
    a_complex_sin(&z, z);
    a_complex_inv(_z, z);
}

void a_complex_cot(a_complex *_z, a_complex z)
{
    a_complex_tan(&z, z);
    a_complex_inv(_z, z);
}

#if defined(A_HAVE_CASIN) && (A_HAVE_CASIN + 0 < 1)
#undef A_HAVE_CASIN
#endif /* A_HAVE_CASIN */
#if defined(A_HAVE_CASIN) && !defined A_COMPLEX
a_complex A_FLOAT_F1(casin, a_complex);
#endif /* A_HAVE_CASIN */
void a_complex_asin(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CASIN) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(casin, *u.z);
#elif defined(A_HAVE_CASIN)
    *_z = A_FLOAT_F1(casin, z);
#else /* !A_HAVE_CASIN */
    if (z.imag != 0)
    {
        a_float const a_crossover = A_FLOAT_C(1.5);
        a_float const b_crossover = A_FLOAT_C(0.6417);
        a_float const x = a_float_abs(z.real);
        a_float const y = a_float_abs(z.imag);
        a_float const r = a_float_hypot(x + 1, y);
        a_float const s = a_float_hypot(x - 1, y);
        a_float const a = A_FLOAT_C(0.5) * (r + s);
        a_float const b = x / a;
        a_float const y2 = y * y;
        a_float const real = z.real;
        a_float const imag = z.imag;
        if (b <= b_crossover)
        {
            _z->real = a_float_asin(b);
        }
        else if (x <= 1)
        {
            a_float const den = A_FLOAT_C(0.5) * (a + x) * (y2 / (r + x + 1) + (s + 1 - x));
            _z->real = a_float_atan(x / a_float_sqrt(den));
        }
        else
        {
            a_float const apx = a + x;
            a_float const den = A_FLOAT_C(0.5) * (apx / (r + x + 1) + apx / (s + x - 1));
            _z->real = a_float_atan(x / (a_float_sqrt(den) * y));
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
            _z->imag = a_float_log1p(am1 + a_float_sqrt((a + 1) * am1));
        }
        else
        {
            _z->imag = a_float_log(a + a_float_sqrt(a * a - 1));
        }
        if (real < 0) { _z->real = -_z->real; }
        if (imag < 0) { _z->imag = -_z->imag; }
    }
    else
    {
        a_complex_asin_real(_z, z.real);
    }
#endif /* A_HAVE_CASIN */
}

void a_complex_asin_real(a_complex *_z, a_float x)
{
    if (a_float_abs(x) <= 1)
    {
        _z->real = a_float_asin(x);
        _z->imag = 0;
    }
    else
    {
        if (x > 0)
        {
            _z->real = +A_FLOAT_PI_2;
            _z->imag = -a_float_acosh(+x);
        }
        else
        {
            _z->real = -A_FLOAT_PI_2;
            _z->imag = +a_float_acosh(-x);
        }
    }
}

#if defined(A_HAVE_CACOS) && (A_HAVE_CACOS + 0 < 1)
#undef A_HAVE_CACOS
#endif /* A_HAVE_CACOS */
#if defined(A_HAVE_CACOS) && !defined A_COMPLEX
a_complex A_FLOAT_F1(cacos, a_complex);
#endif /* A_HAVE_CACOS */
void a_complex_acos(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CACOS) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(cacos, *u.z);
#elif defined(A_HAVE_CACOS)
    *_z = A_FLOAT_F1(cacos, z);
#else /* !A_HAVE_CACOS */
    if (z.imag != 0)
    {
        a_float const a_crossover = A_FLOAT_C(1.5);
        a_float const b_crossover = A_FLOAT_C(0.6417);
        a_float const x = a_float_abs(z.real);
        a_float const y = a_float_abs(z.imag);
        a_float const r = a_float_hypot(x + 1, y);
        a_float const s = a_float_hypot(x - 1, y);
        a_float const a = A_FLOAT_C(0.5) * (r + s);
        a_float const b = x / a;
        a_float const y2 = y * y;
        a_float const real = z.real;
        a_float const imag = z.imag;
        if (b <= b_crossover)
        {
            _z->real = a_float_acos(b);
        }
        else if (x <= 1)
        {
            a_float const den = A_FLOAT_C(0.5) * (a + x) * (y2 / (r + x + 1) + (s + 1 - x));
            _z->real = a_float_atan(a_float_sqrt(den) / x);
        }
        else
        {
            a_float const apx = a + x;
            a_float const den = A_FLOAT_C(0.5) * (apx / (r + x + 1) + apx / (s + x - 1));
            _z->real = a_float_atan(a_float_sqrt(den) * y / x);
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
            _z->imag = a_float_log1p(am1 + a_float_sqrt((a + 1) * am1));
        }
        else
        {
            _z->imag = a_float_log(a + a_float_sqrt(a * a - 1));
        }
        if (real < 0) { _z->real = A_FLOAT_PI - _z->real; }
        if (imag >= 0) { _z->imag = -_z->imag; }
    }
    else
    {
        a_complex_acos_real(_z, z.real);
    }
#endif /* A_HAVE_CACOS */
}

void a_complex_acos_real(a_complex *_z, a_float x)
{
    if (a_float_abs(x) <= 1)
    {
        _z->real = a_float_acos(x);
        _z->imag = 0;
    }
    else
    {
        if (x > 0)
        {
            _z->real = 0;
            _z->imag = +a_float_acosh(+x);
        }
        else
        {
            _z->real = A_FLOAT_PI;
            _z->imag = -a_float_acosh(-x);
        }
    }
}

#if defined(A_HAVE_CATAN) && (A_HAVE_CATAN + 0 < 1)
#undef A_HAVE_CATAN
#endif /* A_HAVE_CATAN */
#if defined(A_HAVE_CATAN) && !defined A_COMPLEX
a_complex A_FLOAT_F1(catan, a_complex);
#endif /* A_HAVE_CATAN */
void a_complex_atan(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CATAN) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(catan, *u.z);
#elif defined(A_HAVE_CATAN)
    *_z = A_FLOAT_F1(catan, z);
#else /* !A_HAVE_CATAN */
    if (z.imag != 0)
    {
        a_float const r = a_float_hypot(z.real, z.imag);
        a_float const u = 2 * z.imag / (r * r + 1);
        a_float const imag = z.imag;
        if (a_float_abs(u) < 0.1)
        {
            _z->imag = A_FLOAT_C(0.25) * (a_float_log1p(u) - a_float_log1p(-u));
        }
        else
        {
            a_float const a = a_float_hypot(z.real, z.imag + 1);
            a_float const b = a_float_hypot(z.real, z.imag - 1);
            _z->imag = A_FLOAT_C(0.5) * a_float_log(a / b);
        }
        if (z.real != 0)
        {
            _z->real = A_FLOAT_C(0.5) * a_float_atan2(2 * z.real, (1 + r) * (1 - r));
        }
        else
        {
            if (imag > 1)
            {
                _z->real = +A_FLOAT_PI;
            }
            else if (imag < -1)
            {
                _z->real = -A_FLOAT_PI;
            }
            else
            {
                _z->real = 0;
            }
        }
    }
    else
    {
        _z->real = a_float_atan(z.real);
        _z->imag = 0;
    }
#endif /* A_HAVE_CATAN */
}

void a_complex_asec(a_complex *_z, a_complex z)
{
    a_complex_inv(&z, z);
    a_complex_acos(_z, z);
}

void a_complex_asec_real(a_complex *_z, a_float x)
{
    if (x <= -1 || x >= 1)
    {
        _z->real = a_float_acos(1 / x);
        _z->imag = 0;
    }
    else
    {
        if (x >= 0)
        {
            _z->real = 0;
            _z->imag = +a_float_acosh(+1 / x);
        }
        else
        {
            _z->real = A_FLOAT_PI;
            _z->imag = -a_float_acosh(-1 / x);
        }
    }
}

void a_complex_acsc(a_complex *_z, a_complex z)
{
    a_complex_inv(&z, z);
    a_complex_asin(_z, z);
}

void a_complex_acsc_real(a_complex *_z, a_float x)
{
    if (x <= -1 || x >= 1)
    {
        _z->real = a_float_asin(1 / x);
        _z->imag = 0;
    }
    else
    {
        if (x >= 0)
        {
            _z->real = +A_FLOAT_PI_2;
            _z->imag = -a_float_acosh(+1 / x);
        }
        else
        {
            _z->real = -A_FLOAT_PI_2;
            _z->imag = +a_float_acosh(-1 / x);
        }
    }
}

void a_complex_acot(a_complex *_z, a_complex z)
{
    if (z.real != 0 || z.imag != 0)
    {
        a_complex_inv(&z, z);
        a_complex_atan(_z, z);
    }
    else
    {
        _z->real = A_FLOAT_PI_2;
        _z->imag = 0;
    }
}

#if defined(A_HAVE_CSINH) && (A_HAVE_CSINH + 0 < 1)
#undef A_HAVE_CSINH
#endif /* A_HAVE_CSINH */
#if defined(A_HAVE_CSINH) && !defined A_COMPLEX
a_complex A_FLOAT_F1(csinh, a_complex);
#endif /* A_HAVE_CSINH */
void a_complex_sinh(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CSINH) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(csinh, *u.z);
#elif defined(A_HAVE_CSINH)
    *_z = A_FLOAT_F1(csinh, z);
#else /* !A_HAVE_CSINH */
    a_float const real = z.real;
    a_float const imag = z.imag;
    _z->real = a_float_sinh(real) * a_float_cos(imag);
    _z->imag = a_float_cosh(real) * a_float_sin(imag);
#endif /* A_HAVE_CSINH */
}

#if defined(A_HAVE_CCOSH) && (A_HAVE_CCOSH + 0 < 1)
#undef A_HAVE_CCOSH
#endif /* A_HAVE_CCOSH */
#if defined(A_HAVE_CCOSH) && !defined A_COMPLEX
a_complex A_FLOAT_F1(ccosh, a_complex);
#endif /* A_HAVE_CCOSH */
void a_complex_cosh(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CCOSH) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(ccosh, *u.z);
#elif defined(A_HAVE_CCOSH)
    *_z = A_FLOAT_F1(ccosh, z);
#else /* !A_HAVE_CCOSH */
    a_float const real = z.real;
    a_float const imag = z.imag;
    _z->real = a_float_cosh(real) * a_float_cos(imag);
    _z->imag = a_float_sinh(real) * a_float_sin(imag);
#endif /* A_HAVE_CCOSH */
}

#if defined(A_HAVE_CTANH) && (A_HAVE_CTANH + 0 < 1)
#undef A_HAVE_CTANH
#endif /* A_HAVE_CTANH */
#if defined(A_HAVE_CTANH) && !defined A_COMPLEX
a_complex A_FLOAT_F1(ctanh, a_complex);
#endif /* A_HAVE_CTANH */
void a_complex_tanh(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CTANH) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(ctanh, *u.z);
#elif defined(A_HAVE_CTANH)
    *_z = A_FLOAT_F1(ctanh, z);
#else /* !A_HAVE_CTANH */
    a_float const ci = a_float_cos(z.imag);
    a_float const sr = a_float_sinh(z.real);
    a_float const inv = 1 / (ci * ci + sr * sr);
    _z->imag = A_FLOAT_C(0.5) * a_float_sin(2 * z.imag) * inv;
    if (a_float_abs(z.real) < 1)
    {
        _z->real = a_float_sinh(z.real) * a_float_cosh(z.real) * inv;
    }
    else
    {
        a_float const den = a_float_pow(ci / sr, 2) + 1;
        _z->real = 1 / (a_float_tanh(z.real) * den);
    }
#endif /* A_HAVE_CTANH */
}

void a_complex_sech(a_complex *_z, a_complex z)
{
    a_complex_cosh(&z, z);
    a_complex_inv(_z, z);
}

void a_complex_csch(a_complex *_z, a_complex z)
{
    a_complex_sinh(&z, z);
    a_complex_inv(_z, z);
}

void a_complex_coth(a_complex *_z, a_complex z)
{
    a_complex_tanh(&z, z);
    a_complex_inv(_z, z);
}

#if defined(A_HAVE_CASINH) && (A_HAVE_CASINH + 0 < 1)
#undef A_HAVE_CASINH
#endif /* A_HAVE_CASINH */
#if defined(A_HAVE_CASINH) && !defined A_COMPLEX
a_complex A_FLOAT_F1(casinh, a_complex);
#endif /* A_HAVE_CASINH */
void a_complex_asinh(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CASINH) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(casinh, *u.z);
#elif defined(A_HAVE_CASINH)
    *_z = A_FLOAT_F1(casinh, z);
#else /* !A_HAVE_CASINH */
    a_complex_mul_imag(&z, z, +1);
    a_complex_asin(&z, z);
    a_complex_mul_imag(_z, z, -1);
#endif /* A_HAVE_CASINH */
}

#if defined(A_HAVE_CACOSH) && (A_HAVE_CACOSH + 0 < 1)
#undef A_HAVE_CACOSH
#endif /* A_HAVE_CACOSH */
#if defined(A_HAVE_CACOSH) && !defined A_COMPLEX
a_complex A_FLOAT_F1(cacosh, a_complex);
#endif /* A_HAVE_CACOSH */
void a_complex_acosh(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CACOSH) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(cacosh, *u.z);
#elif defined(A_HAVE_CACOSH)
    *_z = A_FLOAT_F1(cacosh, z);
#else /* !A_HAVE_CACOSH */
    a_complex_acsc(&z, z);
    a_complex_mul_imag(_z, z, z.imag > 0 ? -1 : +1);
#endif /* A_HAVE_CACOSH */
}

void a_complex_acosh_real(a_complex *_z, a_float x)
{
    if (x >= 1)
    {
        _z->real = a_float_acosh(+x);
        _z->imag = 0;
    }
    else if (x >= -1)
    {
        _z->real = 0;
        _z->imag = a_float_acos(x);
    }
    else
    {
        _z->real = a_float_acosh(-x);
        _z->imag = A_FLOAT_PI;
    }
}

#if defined(A_HAVE_CATANH) && (A_HAVE_CATANH + 0 < 1)
#undef A_HAVE_CATANH
#endif /* A_HAVE_CATANH */
#if defined(A_HAVE_CATANH) && !defined A_COMPLEX
a_complex A_FLOAT_F1(catanh, a_complex);
#endif /* A_HAVE_CATANH */
void a_complex_atanh(a_complex *_z, a_complex z)
{
#if defined(A_HAVE_CATANH) && defined(A_COMPLEX)
    union
    {
        a_complex *_z;
        A_COMPLEX *z;
    } u, v;
    u._z = &z;
    v._z = _z;
    *v.z = A_FLOAT_F1(catanh, *u.z);
#elif defined(A_HAVE_CATANH)
    *_z = A_FLOAT_F1(catanh, z);
#else /* !A_HAVE_CATANH */
    if (z.imag != 0)
    {
        a_complex_mul_imag(&z, z, +1);
        a_complex_atan(&z, z);
        a_complex_mul_imag(_z, z, -1);
    }
    a_complex_atanh_real(_z, z.real);
#endif /* A_HAVE_CATANH */
}

void a_complex_atanh_real(a_complex *_z, a_float x)
{
    if (x > -1 && x < 1)
    {
        _z->real = a_float_atanh(x);
        _z->imag = 0;
    }
    else
    {
        _z->real = a_float_atanh(1 / x);
        _z->imag = (x < 0) ? +A_FLOAT_PI_2 : -A_FLOAT_PI_2;
    }
}

void a_complex_asech(a_complex *_z, a_complex z)
{
    a_complex_inv(&z, z);
    a_complex_acosh(_z, z);
}

void a_complex_acsch(a_complex *_z, a_complex z)
{
    a_complex_inv(&z, z);
    a_complex_asinh(_z, z);
}

void a_complex_acoth(a_complex *_z, a_complex z)
{
    a_complex_inv(&z, z);
    a_complex_atanh(_z, z);
}
