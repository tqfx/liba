#ifndef TEST_POLY_H
#define TEST_POLY_H
#define MAIN_(s, argc, argv) A_CAST_2(poly, s)(argc, argv)
#include "test.h"
#include "a/poly.h"

static void print(a_float_t const *const a, a_size_t const n)
{
    putchar('{');
    a_forenum(a_size_t, i, n)
    {
        printf(A_FLOAT_PRI("", "g"), a[i]);
        if (i < n - 1)
        {
            putchar(',');
        }
    }
    putchar('}');
}

static void test(void)
{
    a_float_t x3[] = {A_FLOAT_C(1.0), A_FLOAT_C(2.0), A_FLOAT_C(3.0)};
    print(x3, 3);
    printf("=" A_FLOAT_PRI("", "g") "\n", a_poly_eval(x3, 3, 2));
    a_poly_swap(x3, 3);
    print(x3, 3);
    printf("=" A_FLOAT_PRI("", "g") "\n", a_poly_eval(x3, 3, 2));
    print(x3, 3);
    printf("=" A_FLOAT_PRI("", "g") "\n", a_poly_evar(x3, 3, 2));

    a_float_t x4[] = {A_FLOAT_C(1.0), A_FLOAT_C(2.0), A_FLOAT_C(3.0), A_FLOAT_C(4.0)};
    print(x4, 4);
    printf("=" A_FLOAT_PRI("", "g") "\n", a_poly_eval(x4, 4, 2));
    a_poly_swap(x4, 4);
    print(x4, 4);
    printf("=" A_FLOAT_PRI("", "g") "\n", a_poly_eval(x4, 4, 2));
    print(x4, 4);
    printf("=" A_FLOAT_PRI("", "g") "\n", a_poly_evar(x4, 4, 2));
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", A_FUNC);
    test();
    return 0;
}

#endif /* test/poly.h */
