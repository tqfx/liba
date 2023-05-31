#ifndef TEST_COMPLEX_H
#define TEST_COMPLEX_H
#define MAIN_(s, argc, argv) complex##s(argc, argv)
#include "test.h"
#if A_PREREQ_GNUC(2, 95) || __has_warning("-Waggregate-return")
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* -Waggregate-return */
#include "a/complex.h"
#include "a/math.h"
#include <stdlib.h>
#include <stdio.h>

static void test(a_complex_s a, a_complex_s b)
{
    a_float_t x = 0;
    a_complex_s c = a_complex_polar(A_FLOAT_C(1.0), a_float_c(, A_PI_2));
    (void)(c);

    x = a_complex_logabs(a);
#if defined(MAIN_ONCE)
    printf("logabs" A_COMPLEX_PRI("", "g", "", "g") "=" A_FLOAT_PRI("", "g\n"), a_complex_real(a), a_complex_imag(a), x);
#endif /* MAIN_ONCE */
    (void)(x);

    x = a_complex_abs2(a);
#if defined(MAIN_ONCE)
    printf("abs2" A_COMPLEX_PRI("", "g", "", "g") "=" A_FLOAT_PRI("", "g\n"), a_complex_real(a), a_complex_imag(a), x);
#endif /* MAIN_ONCE */
    (void)(x);

    x = a_complex_abs(a);
#if defined(MAIN_ONCE)
    printf("abs" A_COMPLEX_PRI("", "g", "", "g") "=" A_FLOAT_PRI("", "g\n"), a_complex_real(a), a_complex_imag(a), x);
#endif /* MAIN_ONCE */
    (void)(x);

    x = a_complex_arg(a);
#if defined(MAIN_ONCE)
    printf("arg" A_COMPLEX_PRI("", "g", "", "g") "=" A_FLOAT_PRI("", "g\n"), a_complex_real(a), a_complex_imag(a), x);
#endif /* MAIN_ONCE */
    (void)(x);

    c = a_complex_conj(a);
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "*=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_neg(a);
#if defined(MAIN_ONCE)
    printf("-" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_add(a, b);
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "+" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_sub(a, b);
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "-" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_mul(a, b);
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "*" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_div(a, b);
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "/" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_add_real(a, a_complex_real(b));
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "+" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), A_FLOAT_C(0.0),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_sub_real(a, a_complex_real(b));
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "-" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), A_FLOAT_C(0.0),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_mul_real(a, a_complex_real(b));
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "*" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), A_FLOAT_C(0.0),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_div_real(a, a_complex_real(b));
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "/" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), A_FLOAT_C(0.0),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_add_imag(a, a_complex_real(b));
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "+" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), A_FLOAT_C(0.0), a_complex_real(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_sub_imag(a, a_complex_real(b));
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "-" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), A_FLOAT_C(0.0), a_complex_real(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_mul_imag(a, a_complex_real(b));
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "*" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), A_FLOAT_C(0.0), a_complex_real(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_div_imag(a, a_complex_real(b));
#if defined(MAIN_ONCE)
    printf(A_COMPLEX_PRI("", "g", "", "g") "/" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), A_FLOAT_C(0.0), a_complex_real(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_inv(a);
#if defined(MAIN_ONCE)
    printf("1/" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_sqrt(a);
#if defined(MAIN_ONCE)
    printf("sqrt" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_sqrt_real(a_complex_real(a));
#if defined(MAIN_ONCE)
    printf("sqrt(" A_FLOAT_PRI("", "g") ")=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_pow(a, b);
#if defined(MAIN_ONCE)
    printf("pow(" A_COMPLEX_PRI("", "g", "", "g") "," A_COMPLEX_PRI("", "g", "", "g") ")=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_pow_real(a, a_complex_real(b));
#if defined(MAIN_ONCE)
    printf("pow(" A_COMPLEX_PRI("", "g", "", "g") "," A_FLOAT_PRI("", "g") ")=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_exp(a);
#if defined(MAIN_ONCE)
    printf("exp" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_log(a);
#if defined(MAIN_ONCE)
    printf("log" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_log2(a);
#if defined(MAIN_ONCE)
    printf("log2" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_log10(a);
#if defined(MAIN_ONCE)
    printf("log10" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);

    c = a_complex_logb(a, b);
#if defined(MAIN_ONCE)
    printf("logb(" A_COMPLEX_PRI("", "g", "", "g") "," A_COMPLEX_PRI("", "g", "", "g") ")=" A_COMPLEX_PRI("", "g", "", "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* MAIN_ONCE */
    (void)(c);
}

static void test_tri(a_complex_s x)
{
    a_complex_s z;

#if defined(MAIN_ONCE)
    printf("sin" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_sin(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("cos" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_cos(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("tan" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_tan(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("sec" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_sec(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("csc" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_csc(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("cot" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_cot(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);
}

static void test_trih(a_complex_s x)
{
    a_complex_s z;

#if defined(MAIN_ONCE)
    printf("sinh" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_sinh(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("cosh" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_cosh(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("tanh" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_tanh(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("sech" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_sech(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("csch" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_csch(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("coth" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_coth(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);
}

static void test_atri(a_complex_s x)
{
    a_complex_s z;

#if defined(MAIN_ONCE)
    printf("asin" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_asin(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("acos" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_acos(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("atan" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_atan(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("asec" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_asec(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("acsc" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_acsc(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("acot" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_acot(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);
}

static void test_atrih(a_complex_s x)
{
    a_complex_s z;

#if defined(MAIN_ONCE)
    printf("asinh" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_asinh(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("acosh" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_acosh(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("atanh" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_atanh(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("asech" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_asech(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("acsch" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_acsch(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);

#if defined(MAIN_ONCE)
    printf("acoth" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
#endif /* MAIN_ONCE */
    z = a_complex_acoth(x);
#if defined(MAIN_ONCE)
    printf("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* MAIN_ONCE */
    (void)(z);
}

#if A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
#define strtoreal(str, endptr) strtof(str, endptr)
#elif A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE
#define strtoreal(str, endptr) strtod(str, endptr)
#elif A_FLOAT_TYPE + 0 == A_FLOAT_EXTEND
#define strtoreal(str, endptr) strtold(str, endptr)
#endif /* A_FLOAT_TYPE */

static a_complex_s strtocomplex(char const *A_RESTRICT str, char **A_RESTRICT endptr)
{
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    a_complex_real(z) = strtoreal(str, endptr);
    if (endptr && *endptr)
    {
        for (str = *endptr; *str; ++str)
        {
            if (*str == '+' || *str == '-' || ('0' <= *str && *str <= '9') || *str == '.')
            {
                a_complex_imag(z) = strtoreal(str, endptr);
                break;
            }
        }
    }
    return z;
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    a_complex_s x = A_COMPLEX_C(0.0, 0.0);
    a_complex_s y = A_COMPLEX_C(0.0, 0.0);
    char *endptr = A_NULL;
    if (argc > 1)
    {
        x = strtocomplex(argv[1], &endptr);
    }
    if (argc > 2)
    {
        y = strtocomplex(argv[2], &endptr);
    }
    test(x, y);
    test_tri(x);
    test_trih(x);
    test_atri(x);
    test_atrih(x);
#if defined(MAIN_ONCE)
    if (argc > 1)
    {
        printf("x=" A_COMPLEX_PRI("", "g", "", "g") " ", a_complex_real(x), a_complex_imag(x));
    }
    if (argc > 2)
    {
        printf("y=" A_COMPLEX_PRI("", "g", "", "g") " ", a_complex_real(y), a_complex_imag(y));
    }
    if (argc > 1)
    {
        putchar('\n');
    }
#endif /* MAIN_ONCE */
    return 0;
}

#endif /* complex.h */
