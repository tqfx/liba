#ifndef TEST_A_H
#define TEST_A_H
#define MAIN_(s, argc, argv) a##s(argc, argv)
#include "test.h"
#include <stdlib.h>

static void test_bkdr(int argc, char *argv[])
{
    for (int idx = 1; idx < argc; ++idx)
    {
        a_u32_t val = a_u32_c(a_hash_bkdr(argv[idx], 0));
#if defined(MAIN_ONCE)
        printf("case 0x%08" PRIX32 ": // %s\n    break;\n", val, argv[idx]);
#else /* !MAIN_ONCE */
        (void)(val);
#endif /* MAIN_ONCE */
    }
}

static void test_for(int argc, char *argv[])
{
    a_uint_t n = 10;
    if (argc > 1)
    {
        a_str_t endptr = A_NULL;
        n = a_uint_c(strtoul(argv[1], &endptr, 0));
    }

    a_int_t *p = a_new(a_int_t, A_NULL, n);
    a_int_t *d = p + n;

    a_forenum(a_uint_t, i, n)
    {
        p[i] = a_int_c(i);
#if defined(MAIN_ONCE)
        printf("%u ", i);
#endif /* MAIN_ONCE */
    }
#if defined(MAIN_ONCE)
    putchar('\n');
#endif /* MAIN_ONCE */

    a_foreach(a_int_t, it, p, n)
    {
#if defined(MAIN_ONCE)
        printf("%i ", *it);
#endif /* MAIN_ONCE */
    }
#if defined(MAIN_ONCE)
    putchar('\n');
#endif /* MAIN_ONCE */

    a_iterate(a_int_t, it, p, d)
    {
#if defined(MAIN_ONCE)
        printf("%i ", *it);
#endif /* MAIN_ONCE */
    }
#if defined(MAIN_ONCE)
    putchar('\n');
#endif /* MAIN_ONCE */

    a_forenum_reverse(a_uint_t, i, n)
    {
        p[i] = a_int_c(i);
#if defined(MAIN_ONCE)
        printf("%u ", i);
#endif /* MAIN_ONCE */
    }
#if defined(MAIN_ONCE)
    putchar('\n');
#endif /* MAIN_ONCE */

    a_foreach_reverse(a_int_t, it, p, n)
    {
#if defined(MAIN_ONCE)
        printf("%i ", *it);
#endif /* MAIN_ONCE */
    }
#if defined(MAIN_ONCE)
    putchar('\n');
#endif /* MAIN_ONCE */

    a_iterate_reverse(a_int_t, it, p, d)
    {
#if defined(MAIN_ONCE)
        printf("%i ", *it);
#endif /* MAIN_ONCE */
    }
#if defined(MAIN_ONCE)
    putchar('\n');
#endif /* MAIN_ONCE */

    p = a_die(a_int_t, p);
}

static void test_swap(void)
{
    {
        a_i8_t lhs = A_I8_MIN;
        a_i8_t rhs = A_I8_MAX;
#if defined(MAIN_ONCE)
        printf("%+" PRIi8 " %+" PRIi8 " -> ", lhs, rhs);
#endif /* MAIN_ONCE */
        a_swap1(&lhs, &rhs);
#if defined(MAIN_ONCE)
        printf("%+" PRIi8 " %+" PRIi8 "  \n", lhs, rhs);
#endif /* MAIN_ONCE */
    }
    {
        a_i16_t lhs = A_I16_MIN;
        a_i16_t rhs = A_I16_MAX;
#if defined(MAIN_ONCE)
        printf("%+" PRIi16 " %+" PRIi16 " -> ", lhs, rhs);
#endif /* MAIN_ONCE */
        a_swap2(&lhs, &rhs);
#if defined(MAIN_ONCE)
        printf("%+" PRIi16 " %+" PRIi16 "  \n", lhs, rhs);
#endif /* MAIN_ONCE */
    }
    {
        a_i32_t lhs = A_I32_MIN;
        a_i32_t rhs = A_I32_MAX;
#if defined(MAIN_ONCE)
        printf("%+" PRIi32 " %+" PRIi32 " -> ", lhs, rhs);
#endif /* MAIN_ONCE */
        a_swap4(&lhs, &rhs);
#if defined(MAIN_ONCE)
        printf("%+" PRIi32 " %+" PRIi32 "  \n", lhs, rhs);
#endif /* MAIN_ONCE */
    }
    {
        a_i64_t lhs = A_I64_MIN;
        a_i64_t rhs = A_I64_MAX;
#if defined(MAIN_ONCE)
        printf("%+" PRIi64 " %+" PRIi64 " -> ", lhs, rhs);
#endif /* MAIN_ONCE */
        a_swap8(&lhs, &rhs);
#if defined(MAIN_ONCE)
        printf("%+" PRIi64 " %+" PRIi64 "  \n", lhs, rhs);
#endif /* MAIN_ONCE */
    }
    {
        a_size_t lhs = 0;
        a_size_t rhs = A_SIZE_MAX;
#if defined(MAIN_ONCE)
        printf("%" PRIzu " %" PRIzu " -> ", lhs, rhs);
#endif /* MAIN_ONCE */
        a_swapz(&lhs, &rhs);
#if defined(MAIN_ONCE)
        printf("%" PRIzu " %" PRIzu "  \n", lhs, rhs);
#endif /* MAIN_ONCE */
    }
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    if (argc < 2)
    {
        test_swap();
        return 0;
    }
    a_u32_t bkdr = a_u32_c(a_hash_bkdr(argv[1], 0));
    switch (bkdr)
    {
    case 0x0D3DEDB7: // bkdr
        test_bkdr(argc - 1, argv + 1);
        break;
    case 0x001AEED5: // for
        test_for(argc - 1, argv + 1);
        break;
    default:;
#if defined(MAIN_ONCE)
        puts("bkdr");
        puts("for");
#endif /* MAIN_ONCE */
    }
    return 0;
}

#endif /* a.h */
