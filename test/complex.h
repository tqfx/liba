#define MAIN(x) complex##x
#include "test.h"
#include "a/math.h"
#include "a/complex.h"

static void test(a_complex a, a_complex b)
{
    a_real x;
    a_complex c;
    a_complex_polar(&c, A_REAL_C(1.0), a_real_c(A_PI_2));

    x = a_complex_logabs(a);
    debug("logabs((%" A_REAL_PRI "g,%" A_REAL_PRI "g))=%" A_REAL_PRI "g\n", a.real, a.imag, x);

    x = a_complex_abs2(a);
    debug("abs2((%" A_REAL_PRI "g,%" A_REAL_PRI "g))=%" A_REAL_PRI "g\n", a.real, a.imag, x);

    x = a_complex_abs(a);
    debug("abs((%" A_REAL_PRI "g,%" A_REAL_PRI "g))=%" A_REAL_PRI "g\n", a.real, a.imag, x);

    x = a_complex_arg(a);
    debug("arg((%" A_REAL_PRI "g,%" A_REAL_PRI "g))=%" A_REAL_PRI "g\n", a.real, a.imag, x);

    a_complex_proj(&c, a);
    debug("proj((%" A_REAL_PRI "g,%" A_REAL_PRI "g))=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, c.real, c.imag);

    a_complex_conj(&c, a);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)'=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, c.real, c.imag);

    a_complex_neg(&c, a);
    debug("-(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, c.real, c.imag);

    a_complex_add(&c, a, b);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)+(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, b.real, b.imag, c.real, c.imag);

    a_complex_sub(&c, a, b);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)-(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, b.real, b.imag, c.real, c.imag);

    a_complex_mul(&c, a, b);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)*(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, b.real, b.imag, c.real, c.imag);

    a_complex_div(&c, a, b);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)/(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, b.real, b.imag, c.real, c.imag);

    a_complex_add_real(&c, a, b.real);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)+(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, b.real, A_REAL_C(0.0), c.real, c.imag);

    a_complex_sub_real(&c, a, b.real);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)-(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, b.real, A_REAL_C(0.0), c.real, c.imag);

    a_complex_mul_real(&c, a, b.real);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)*(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, b.real, A_REAL_C(0.0), c.real, c.imag);

    a_complex_div_real(&c, a, b.real);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)/(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, b.real, A_REAL_C(0.0), c.real, c.imag);

    a_complex_add_imag(&c, a, b.real);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)+(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, A_REAL_C(0.0), b.real, c.real, c.imag);

    a_complex_sub_imag(&c, a, b.real);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)-(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, A_REAL_C(0.0), b.real, c.real, c.imag);

    a_complex_mul_imag(&c, a, b.real);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)*(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, A_REAL_C(0.0), b.real, c.real, c.imag);

    a_complex_div_imag(&c, a, b.real);
    debug("(%" A_REAL_PRI "g,%" A_REAL_PRI "g)/(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, A_REAL_C(0.0), b.real, c.real, c.imag);

    a_complex_inv(&c, a);
    debug("1/(%" A_REAL_PRI "g,%" A_REAL_PRI "g)=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, c.real, c.imag);

    a_complex_sqrt(&c, a);
    debug("sqrt((%" A_REAL_PRI "g,%" A_REAL_PRI "g))=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, c.real, c.imag);

    a_complex_sqrt_real(&c, a.real);
    debug("sqrt(%" A_REAL_PRI "g"
          ")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, c.real, c.imag);

    a_complex_pow(&c, a, b);
    debug("pow((%" A_REAL_PRI "g,%" A_REAL_PRI "g),(%" A_REAL_PRI "g,%" A_REAL_PRI "g))=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, b.real, b.imag, c.real, c.imag);

    a_complex_pow_real(&c, a, b.real);
    debug("pow((%" A_REAL_PRI "g,%" A_REAL_PRI "g),%" A_REAL_PRI "g"
          ")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, b.real, c.real, c.imag);

    a_complex_exp(&c, a);
    debug("exp((%" A_REAL_PRI "g,%" A_REAL_PRI "g))=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, c.real, c.imag);

    a_complex_log(&c, a);
    debug("log((%" A_REAL_PRI "g,%" A_REAL_PRI "g))=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, c.real, c.imag);

    a_complex_log2(&c, a);
    debug("log2((%" A_REAL_PRI "g,%" A_REAL_PRI "g))=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, c.real, c.imag);

    a_complex_log10(&c, a);
    debug("log10((%" A_REAL_PRI "g,%" A_REAL_PRI "g))=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, c.real, c.imag);

    a_complex_logb(&c, a, b);
    debug("logb((%" A_REAL_PRI "g,%" A_REAL_PRI "g),(%" A_REAL_PRI "g,%" A_REAL_PRI "g))=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n",
          a.real, a.imag, b.real, b.imag, c.real, c.imag);
}

static void test_tri(a_complex x)
{
    a_complex z;

    debug("sin((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_sin(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("cos((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_cos(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("tan((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_tan(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("sec((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_sec(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("csc((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_csc(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("cot((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_cot(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);
}

static void test_trih(a_complex x)
{
    a_complex z;

    debug("sinh((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_sinh(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("cosh((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_cosh(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("tanh((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_tanh(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("sech((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_sech(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("csch((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_csch(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("coth((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_coth(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);
}

static void test_atri(a_complex x)
{
    a_complex z;

    debug("asin((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_asin(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("acos((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_acos(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("atan((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_atan(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("asec((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_asec(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("acsc((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_acsc(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("acot((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_acot(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);
}

static void test_atrih(a_complex x)
{
    a_complex z;

    debug("asinh((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_asinh(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("acosh((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_acosh(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("atanh((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_atanh(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("asech((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_asech(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("acsch((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_acsch(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);

    debug("acoth((%" A_REAL_PRI "g,%" A_REAL_PRI "g))", x.real, x.imag);
    a_complex_acoth(&z, x);
    debug(")=(%" A_REAL_PRI "g,%" A_REAL_PRI "g)\n", z.real, z.imag);
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    a_complex x = A_COMPLEX_C(0, 0);
    a_complex y = A_COMPLEX_C(0, 0);
    if (argc > 1)
    {
        a_complex_parse(&x, argv[1]);
    }
    if (argc > 2)
    {
        a_complex_parse(&y, argv[2]);
    }
    test(x, y);
    test_tri(x);
    test_trih(x);
    test_atri(x);
    test_atrih(x);
    if (argc > 1)
    {
        debug("x=(%" A_REAL_PRI "g,%" A_REAL_PRI "g) ", x.real, x.imag);
    }
    if (argc > 2)
    {
        debug("y=(%" A_REAL_PRI "g,%" A_REAL_PRI "g) ", y.real, y.imag);
        if (a_complex_eq(x, y)) { debug("x==y"); }
        if (a_complex_ne(x, y)) { debug("x!=y"); }
    }
    if (argc > 1) { debug("\n"); }
    return 0;
}
