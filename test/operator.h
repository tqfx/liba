#ifndef TEST_OPERATOR_H
#define TEST_OPERATOR_H
#define MAIN_(s, argc, argv) operator##s(argc, argv)
#include "test.h"
#include "a/operator.h"

static void test(void)
{
    {
        a_int_t x = 1;
        printf("inc(%i) ", x);
        printf("= %i\n", a_inc(x));
    }
    {
        a_int_t x = 1;
        printf("dec(%i) ", x);
        printf("= %i\n", a_dec(x));
    }
    {
        a_int_t x = a_pos(1);
        printf("pos(1) = %+i\n", x);
    }
    {
        a_int_t x = a_neg(1);
        printf("neg(1) = %+i\n", x);
    }
    {
        a_int_t x = a_not(1);
        printf("not(1) = %i\n", x);
    }
    {
        a_int_t x = a_compl(1);
        printf("compl(1) = %i\n", x);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("mul(%i, %i) = %i\n", a, b, a_mul(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("div(%i, %i) = %i\n", a, b, a_div(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("mod(%i, %i) = %i\n", a, b, a_mod(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("add(%i, %i) = %i\n", a, b, a_add(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("sub(%i, %i) = %i\n", a, b, a_sub(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        printf("lshift(%i, %i) = %i\n", a, b, a_lshift(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        printf("rshift(%i, %i) = %i\n", a, b, a_rshift(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("eq(%i, %i) = %i\n", a, b, a_eq(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("ne(%i, %i) = %i\n", a, b, a_ne(a, b));
    }
    {
        a_int_t a = 1;
        a_int_t b = 2;
        printf("lt(%i, %i) = %i\n", a, b, a_lt(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        printf("gt(%i, %i) = %i\n", a, b, a_gt(a, b));
    }
    {
        a_int_t a = 1;
        a_int_t b = 2;
        printf("le(%i, %i) = %i\n", a, b, a_le(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        printf("ge(%i, %i) = %i\n", a, b, a_ge(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 0;
        printf("bitand(%i, %i) = %i\n", a, b, a_bitand(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 0;
        printf("bitxor(%i, %i) = %i\n", a, b, a_bitxor(a, b));
    }
    {
        a_int_t a = 9;
        a_int_t b = 2;
        printf("bitor(%i, %i) = %i\n", a, b, a_bitor(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 0;
        printf("and(%i, %i) = %i\n", a, b, a_and(a, b));
    }
    {
        a_int_t a = 0;
        a_int_t b = 2;
        printf("or(%i, %i) = %i\n", a, b, a_or(a, b));
    }
    {
        a_int_t a = 1;
        a_int_t b = 1;
        a_int_t c = a;
        a_add_eq(c, b);
        printf("add_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 1;
        a_int_t b = 1;
        a_int_t c = a;
        a_sub_eq(c, b);
        printf("sub_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        a_int_t c = a;
        a_mul_eq(c, b);
        printf("mul_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        a_int_t c = a;
        a_div_eq(c, b);
        printf("div_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 3;
        a_int_t b = 2;
        a_int_t c = a;
        a_mod_eq(c, b);
        printf("mod_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        a_int_t c = a;
        a_shl_eq(c, b);
        printf("shl_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        a_int_t c = a;
        a_shr_eq(c, b);
        printf("shr_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        a_int_t c = a;
        a_and_eq(c, b);
        printf("and_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 9;
        a_int_t b = 2;
        a_int_t c = a;
        a_xor_eq(c, b);
        printf("xor_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 0;
        a_int_t c = a;
        a_or_eq(c, b);
        printf("or_eq(%i, %i) = %i\n", a, b, c);
    }
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", A_FUNC);
    test();
    return 0;
}

#endif /* operator.h */
