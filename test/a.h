#define MAIN_(x) A_CAST_2(x, _a)
#include "test.h"
#include <stdlib.h>

static void test_sq(void)
{
    A_ASSERT_BUILD(A_SQ(+2) == 4);
    A_ASSERT_BUILD(A_SQ(-2) == 4);
}

static void test_abs(void)
{
    A_ASSERT_BUILD(A_ABS(~0) > 0);
}

static void test_min(void)
{
    A_ASSERT_BUILD(A_MIN(0, 1) == 0);
    A_ASSERT_BUILD(A_MIN(1, 0) == 0);
}

static void test_max(void)
{
    A_ASSERT_BUILD(A_MAX(0, 1) == 1);
    A_ASSERT_BUILD(A_MAX(1, 0) == 1);
}

static void test_sgn(void)
{
    A_ASSERT_BUILD(A_SGN(0) == 0);
    A_ASSERT_BUILD(A_SGN(+10) == +1);
    A_ASSERT_BUILD(A_SGN(-10) == -1);
}

static void test_sat(void)
{
    A_ASSERT_BUILD(A_SAT(0, -10, +10) == 0);
    A_ASSERT_BUILD(A_SAT(+100, -10, +10) <= +10);
    A_ASSERT_BUILD(A_SAT(-100, -10, +10) >= -10);
}

static void test_bkdr(int argc, char *argv[])
{
    for (int idx = 1; idx < argc; ++idx)
    {
        a_u32_t val = a_u32_c(, a_hash_bkdr(argv[idx], 0));
        debug("case 0x%08" PRIX32 ": // %s\n    break;\n", val, argv[idx]);
    }
}

static void test_for(int argc, char *argv[])
{
    unsigned int n = 10;
    if (argc > 1)
    {
        char *endptr = A_NULL;
        n = a_cast_s(unsigned int, strtoul(argv[1], &endptr, 0));
    }

    int *p = a_new(int, A_NULL, n);
    int *d = p + n;

    a_forenum(unsigned int, i, n)
    {
        p[i] = a_cast_s(int, i);
        debug("%u ", i);
    }
    debug("\n");

    a_foreach(int, it, p, n)
    {
        debug("%i ", *it);
    }
    debug("\n");

    a_iterate(int, it, p, d)
    {
        debug("%i ", it ? *it : ~0);
    }
    debug("\n");

    a_forenum_reverse(unsigned int, i, n)
    {
        p[i] = a_cast_s(int, i);
        debug("%u ", i);
    }
    debug("\n");

    a_foreach_reverse(int, it, p, n)
    {
        debug("%i ", *it);
    }
    debug("\n");

    a_iterate_reverse(int, it, p, d)
    {
        debug("%i ", *it);
    }
    debug("\n");

    a_die(p);
}

static void test_swap(int argc, char *argv[])
{
    a_u64_t lhs = 0;
    a_u64_t rhs = A_U64_MAX;
    debug("0x%016" PRIX64 " 0x%016" PRIX64 " -> ", lhs, rhs);
    a_swap(&lhs, &rhs, 1);
    debug("0x%016" PRIX64 " 0x%016" PRIX64 "  \n", lhs, rhs);
    debug("0x%016" PRIX64 " 0x%016" PRIX64 " -> ", lhs, rhs);
    a_swap(&lhs, &rhs, 2);
    debug("0x%016" PRIX64 " 0x%016" PRIX64 "  \n", lhs, rhs);
    debug("0x%016" PRIX64 " 0x%016" PRIX64 " -> ", lhs, rhs);
    a_swap(&lhs, &rhs, 4);
    debug("0x%016" PRIX64 " 0x%016" PRIX64 "  \n", lhs, rhs);
    debug("0x%016" PRIX64 " 0x%016" PRIX64 " -> ", lhs, rhs);
    a_swap(&lhs, &rhs, 8);
    debug("0x%016" PRIX64 " 0x%016" PRIX64 "  \n", lhs, rhs);
    (void)argc;
    (void)argv;
}

static void test_save(int argc, char *argv[])
{
    a_float_t array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (a_size_t i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_float_t cache[] = {-1};
        a_float_save(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (a_size_t i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_float_t cache[] = {-1, -2};
        a_float_save(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (a_size_t i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_float_t cache[] = {-1, -2, -3, -4};
        a_float_save(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (a_size_t i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_float_t cache[] = {-1, -2, -3, -4, -5, -6, -7, -8};
        a_float_save(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (a_size_t i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_float_t cache[] = {-0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10};
        a_float_save(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (a_size_t i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    (void)argc;
    (void)argv;
}

static void test_roll(int argc, char *argv[])
{
    a_float_t array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    a_float_t shift[16];
    for (a_size_t i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_roll(array, A_LEN(array), shift, 1);
    for (a_size_t i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_roll(array, A_LEN(array), shift, 2);
    for (a_size_t i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_roll(array, A_LEN(array), shift, 4);
    for (a_size_t i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_roll(array, A_LEN(array), shift, 8);
    for (a_size_t i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_roll(array, A_LEN(array), shift, 15);
    for (a_size_t i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    (void)argc;
    (void)argv;
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    test_sq();
    test_min();
    test_max();
    test_abs();
    test_sgn();
    test_sat();
    if (argc < 2)
    {
        test_for(argc, argv);
        test_bkdr(argc, argv);
        test_swap(argc, argv);
        test_save(argc, argv);
        test_roll(argc, argv);
        return 0;
    }
    a_u32_t bkdr = a_u32_c(, a_hash_bkdr(argv[1], 0));
    switch (bkdr)
    {
    case 0x001AEED5: // for
        test_for(argc - 1, argv + 1);
        break;
    case 0x0D3DEDB7: // bkdr
        test_bkdr(argc - 1, argv + 1);
        break;
    case 0x0F8837E3: // swap
        test_swap(argc - 1, argv + 1);
        break;
    case 0x0F827FD1: // save
        test_save(argc - 1, argv + 1);
        break;
    case 0x0F63D79D: // roll
        test_roll(argc - 1, argv + 1);
        break;
    default:
        debug("for\n");
        debug("bkdr\n");
        debug("swap\n");
        debug("save\n");
        debug("roll\n");
    }
    return 0;
}
