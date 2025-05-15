#define MAIN(x) a##x
#include "test.h"
#include <stdlib.h>

static void test_sq(void)
{
    A_BUILD_ASSERT(A_SQ(+2) == 4);
    A_BUILD_ASSERT(A_SQ(-2) == 4);
}

static void test_abs(void)
{
    A_BUILD_ASSERT(A_ABS(+1) > 0);
    A_BUILD_ASSERT(A_ABS(-1) > 0);
    A_BUILD_ASSERT(A_ABS_(+1, -1) > 0);
    A_BUILD_ASSERT(A_ABS_(-1, +1) > 0);
}

static void test_min(void)
{
    A_BUILD_ASSERT(A_MIN(0, 1) == 0);
    A_BUILD_ASSERT(A_MIN(1, 0) == 0);
}

static void test_max(void)
{
    A_BUILD_ASSERT(A_MAX(0, 1) == 1);
    A_BUILD_ASSERT(A_MAX(1, 0) == 1);
}

static void test_sgn(void)
{
    A_BUILD_ASSERT(A_SGN(0) == 0);
    A_BUILD_ASSERT(A_SGN(+10) == +1);
    A_BUILD_ASSERT(A_SGN(-10) == -1);
    A_BUILD_ASSERT(A_SGN_(0, 0) == 0);
    A_BUILD_ASSERT(A_SGN_(+1, -1) == +1);
    A_BUILD_ASSERT(A_SGN_(-1, +1) == -1);
}

static void test_sat(void)
{
    a_real const nan = A_REAL_NAN;
    A_BUILD_ASSERT(A_SAT(0, -10, +10) == 0);
    A_BUILD_ASSERT(A_SAT(+100, -10, +10) <= +10);
    A_BUILD_ASSERT(A_SAT(-100, -10, +10) >= -10);
    TEST_NOT(A_SAT(nan, -10, +10) <= 100);
}

static void test_for(int argc, char *argv[])
{
    int *p, *d, *it, *at;
    unsigned int i, n = 10;

    if (argc > 1)
    {
        char *endptr = argv[1];
        unsigned long u = strtoul(argv[1], &endptr, 0);
        if (u > n) { n = a_cast_s(unsigned int, u); }
    }

    p = a_new(int, A_NULL, n);
    d = p + n;
    {
        A_ASSUME(p);
    }

    A_FORENUM(unsigned int, i, n)
    {
        p[i] = a_cast_s(int, i);
        debug("%u ", i);
    }
    debug("\n");

    A_FOREACH(int *, it, at, p, n) { debug("%i ", *it); }
    debug("\n");

    A_ITERATE(int *, it, at, p, d) { debug("%i ", *it); }
    debug("\n");

    A_FORENUM_REVERSE(unsigned int, i, n)
    {
        p[i] = a_cast_s(int, i);
        debug("%u ", i);
    }
    debug("\n");

    A_FOREACH_REVERSE(int *, it, at, p, n) { debug("%i ", *it); }
    debug("\n");

    A_ITERATE_REVERSE(int *, it, at, p, d) { debug("%i ", *it); }
    debug("\n");

    a_die(p);
}

static void test_swap(int argc, char *argv[])
{
    a_u64 lhs = 0;
    a_u64 rhs = A_U64_MAX;
    debug("0x%016" A_PRI64 "X 0x%016" A_PRI64 "X -> ", lhs, rhs);
    a_swap(&lhs, &rhs, 1);
    debug("0x%016" A_PRI64 "X 0x%016" A_PRI64 "X  \n", lhs, rhs);
    debug("0x%016" A_PRI64 "X 0x%016" A_PRI64 "X -> ", lhs, rhs);
    a_swap(&lhs, &rhs, 2);
    debug("0x%016" A_PRI64 "X 0x%016" A_PRI64 "X  \n", lhs, rhs);
    debug("0x%016" A_PRI64 "X 0x%016" A_PRI64 "X -> ", lhs, rhs);
    a_swap(&lhs, &rhs, 4);
    debug("0x%016" A_PRI64 "X 0x%016" A_PRI64 "X  \n", lhs, rhs);
    debug("0x%016" A_PRI64 "X 0x%016" A_PRI64 "X -> ", lhs, rhs);
    a_swap(&lhs, &rhs, 8);
    debug("0x%016" A_PRI64 "X 0x%016" A_PRI64 "X  \n", lhs, rhs);
    (void)argc;
    (void)argv;
}

#include "a/hash.h"

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
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
        test_swap(argc, argv);
        return 0;
    }
    switch (a_hash_bkdr(argv[1], 0))
    {
    case 0x001AEED5: /* for */
        test_for(argc - 1, argv + 1);
        break;
    case 0x0F8837E3: /* swap */
        test_swap(argc - 1, argv + 1);
        break;
    default:
        debug("for\n");
        debug("swap\n");
    }
    return 0;
}
