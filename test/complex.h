#define MAIN_(x) A_CAST_2(x, _complex)
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

    x = a_complex_logabs(a);
    debug("logabs" A_COMPLEX_PRI("", "g", "", "g") "=" A_FLOAT_PRI("", "g\n"), a_complex_real(a), a_complex_imag(a), x);

    x = a_complex_abs2(a);
    debug("abs2" A_COMPLEX_PRI("", "g", "", "g") "=" A_FLOAT_PRI("", "g\n"), a_complex_real(a), a_complex_imag(a), x);

    x = a_complex_abs(a);
    debug("abs" A_COMPLEX_PRI("", "g", "", "g") "=" A_FLOAT_PRI("", "g\n"), a_complex_real(a), a_complex_imag(a), x);

    x = a_complex_arg(a);
    debug("arg" A_COMPLEX_PRI("", "g", "", "g") "=" A_FLOAT_PRI("", "g\n"), a_complex_real(a), a_complex_imag(a), x);

    c = a_complex_conj(a);
    debug(A_COMPLEX_PRI("", "g", "", "g") "*=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));

    c = a_complex_neg(a);
    debug("-" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));

    c = a_complex_add(a, b);
    debug(A_COMPLEX_PRI("", "g", "", "g") "+" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_sub(a, b);
    debug(A_COMPLEX_PRI("", "g", "", "g") "-" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_mul(a, b);
    debug(A_COMPLEX_PRI("", "g", "", "g") "*" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_div(a, b);
    debug(A_COMPLEX_PRI("", "g", "", "g") "/" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_add_real(a, a_complex_real(b));
    debug(A_COMPLEX_PRI("", "g", "", "g") "+" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(b), A_FLOAT_C(0.0),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_sub_real(a, a_complex_real(b));
    debug(A_COMPLEX_PRI("", "g", "", "g") "-" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(b), A_FLOAT_C(0.0),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_mul_real(a, a_complex_real(b));
    debug(A_COMPLEX_PRI("", "g", "", "g") "*" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(b), A_FLOAT_C(0.0),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_div_real(a, a_complex_real(b));
    debug(A_COMPLEX_PRI("", "g", "", "g") "/" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(b), A_FLOAT_C(0.0),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_add_imag(a, a_complex_real(b));
    debug(A_COMPLEX_PRI("", "g", "", "g") "+" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), A_FLOAT_C(0.0), a_complex_real(b),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_sub_imag(a, a_complex_real(b));
    debug(A_COMPLEX_PRI("", "g", "", "g") "-" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), A_FLOAT_C(0.0), a_complex_real(b),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_mul_imag(a, a_complex_real(b));
    debug(A_COMPLEX_PRI("", "g", "", "g") "*" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), A_FLOAT_C(0.0), a_complex_real(b),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_div_imag(a, a_complex_real(b));
    debug(A_COMPLEX_PRI("", "g", "", "g") "/" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), A_FLOAT_C(0.0), a_complex_real(b),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_inv(a);
    debug("1/" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));

    c = a_complex_sqrt(a);
    debug("sqrt" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));

    c = a_complex_sqrt_real(a_complex_real(a));
    debug("sqrt(" A_FLOAT_PRI("", "g") ")=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_real(c), a_complex_imag(c));

    c = a_complex_pow(a, b);
    debug("pow(" A_COMPLEX_PRI("", "g", "", "g") "," A_COMPLEX_PRI("", "g", "", "g") ")=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_pow_real(a, a_complex_real(b));
    debug("pow(" A_COMPLEX_PRI("", "g", "", "g") "," A_FLOAT_PRI("", "g") ")=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(b),
          a_complex_real(c), a_complex_imag(c));

    c = a_complex_exp(a);
    debug("exp" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));

    c = a_complex_log(a);
    debug("log" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));

    c = a_complex_log2(a);
    debug("log2" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));

    c = a_complex_log10(a);
    debug("log10" A_COMPLEX_PRI("", "g", "", "g") "=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));

    c = a_complex_logb(a, b);
    debug("logb(" A_COMPLEX_PRI("", "g", "", "g") "," A_COMPLEX_PRI("", "g", "", "g") ")=" A_COMPLEX_PRI("", "g", "", "g") "\n",
          a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
          a_complex_real(c), a_complex_imag(c));
}

static void test_tri(a_complex_s x)
{
    a_complex_s z;

    debug("sin" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_sin(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("cos" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_cos(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("tan" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_tan(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("sec" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_sec(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("csc" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_csc(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("cot" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_cot(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
}

static void test_trih(a_complex_s x)
{
    a_complex_s z;

    debug("sinh" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_sinh(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("cosh" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_cosh(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("tanh" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_tanh(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("sech" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_sech(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("csch" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_csch(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("coth" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_coth(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
}

static void test_atri(a_complex_s x)
{
    a_complex_s z;

    debug("asin" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_asin(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("acos" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_acos(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("atan" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_atan(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("asec" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_asec(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("acsc" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_acsc(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("acot" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_acot(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
}

static void test_atrih(a_complex_s x)
{
    a_complex_s z;

    debug("asinh" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_asinh(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("acosh" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_acosh(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("atanh" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_atanh(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("asech" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_asech(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("acsch" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_acsch(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));

    debug("acoth" A_COMPLEX_PRI("", "g", "", "g"), a_complex_real(x), a_complex_imag(x));
    z = a_complex_acoth(x);
    debug("=" A_COMPLEX_PRI("", "g", "", "g") "\n", a_complex_real(z), a_complex_imag(z));
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
    a_complex_s y = a_complex_c(0.0, 0.0);
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
    if (argc > 1)
    {
        debug("x=" A_COMPLEX_PRI("", "g", "", "g") " ", a_complex_real(x), a_complex_imag(x));
    }
    if (argc > 2)
    {
        debug("y=" A_COMPLEX_PRI("", "g", "", "g") " ", a_complex_real(y), a_complex_imag(y));
    }
    if (argc > 1)
    {
        debug("\n");
    }
    return 0;
}
