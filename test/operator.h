#define MAIN(x) operator##x
#include "test.h"
#include "a/operator.h"

static void test(void)
{
    {
        int x = 1;
        printf("inc(%i) ", x);
        printf("= %i\n", a_inc(x));
    }
    {
        int x = 1;
        printf("dec(%i) ", x);
        printf("= %i\n", a_dec(x));
    }
    {
        int x = a_pos(1);
        printf("pos(1) = %+i\n", x);
    }
    {
        int x = a_neg(1);
        printf("neg(1) = %+i\n", x);
    }
    {
        int x = a_not(1);
        printf("not(1) = %i\n", x);
    }
    {
        int x = a_compl(1);
        printf("compl(1) = %i\n", x);
    }
    {
        int a = 2;
        int b = 2;
        printf("mul(%i, %i) = %i\n", a, b, a_mul(a, b));
    }
    {
        int a = 2;
        int b = 2;
        printf("div(%i, %i) = %i\n", a, b, a_div(a, b));
    }
    {
        int a = 2;
        int b = 2;
        printf("mod(%i, %i) = %i\n", a, b, a_mod(a, b));
    }
    {
        int a = 2;
        int b = 2;
        printf("add(%i, %i) = %i\n", a, b, a_add(a, b));
    }
    {
        int a = 2;
        int b = 2;
        printf("sub(%i, %i) = %i\n", a, b, a_sub(a, b));
    }
    {
        int a = 2;
        int b = 1;
        printf("lshift(%i, %i) = %i\n", a, b, a_lshift(a, b));
    }
    {
        int a = 2;
        int b = 1;
        printf("rshift(%i, %i) = %i\n", a, b, a_rshift(a, b));
    }
    {
        int a = 2;
        int b = 2;
        printf("eq(%i, %i) = %i\n", a, b, a_cast_s(int, a_eq(a, b)));
    }
    {
        int a = 2;
        int b = 2;
        printf("ne(%i, %i) = %i\n", a, b, a_cast_s(int, a_ne(a, b)));
    }
    {
        int a = 1;
        int b = 2;
        printf("lt(%i, %i) = %i\n", a, b, a_cast_s(int, a_lt(a, b)));
    }
    {
        int a = 2;
        int b = 1;
        printf("gt(%i, %i) = %i\n", a, b, a_cast_s(int, a_gt(a, b)));
    }
    {
        int a = 1;
        int b = 2;
        printf("le(%i, %i) = %i\n", a, b, a_cast_s(int, a_le(a, b)));
    }
    {
        int a = 2;
        int b = 1;
        printf("ge(%i, %i) = %i\n", a, b, a_cast_s(int, a_ge(a, b)));
    }
    {
        int a = 2;
        int b = 0;
        printf("bitand(%i, %i) = %i\n", a, b, a_bitand(a, b));
    }
    {
        int a = 2;
        int b = 0;
        printf("bitxor(%i, %i) = %i\n", a, b, a_bitxor(a, b));
    }
    {
        int a = 9;
        int b = 2;
        printf("bitor(%i, %i) = %i\n", a, b, a_bitor(a, b));
    }
    {
        int a = 2;
        int b = 0;
        printf("and(%i, %i) = %i\n", a, b, a_cast_s(int, a_and(a, b)));
    }
    {
        int a = 0;
        int b = 2;
        printf("or(%i, %i) = %i\n", a, b, a_cast_s(int, a_or(a, b)));
    }
    {
        int a = 1;
        int b = 1;
        int c = a;
        a_add_eq(c, b);
        printf("add_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 1;
        int b = 1;
        int c = a;
        a_sub_eq(c, b);
        printf("sub_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 2;
        int c = a;
        a_mul_eq(c, b);
        printf("mul_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 2;
        int c = a;
        a_div_eq(c, b);
        printf("div_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 3;
        int b = 2;
        int c = a;
        a_mod_eq(c, b);
        printf("mod_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 1;
        int c = a;
        a_shl_eq(c, b);
        printf("shl_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 1;
        int c = a;
        a_shr_eq(c, b);
        printf("shr_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 2;
        int c = a;
        a_and_eq(c, b);
        printf("and_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 9;
        int b = 2;
        int c = a;
        a_xor_eq(c, b);
        printf("xor_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 0;
        int c = a;
        a_or_eq(c, b);
        printf("or_eq(%i, %i) = %i\n", a, b, c);
    }
}

int main(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)argc;
    (void)argv;
    printf("%s\n", A_FUNC);
    test();
    return 0;
}
