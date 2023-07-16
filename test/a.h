#ifndef TEST_A_H
#define TEST_A_H
#define MAIN_(s, argc, argv) A_CASE_2(a, s)(argc, argv)
#include "test.h"
#include <stdlib.h>

static void test_bkdr(int argc, char *argv[])
{
    for (int idx = 1; idx < argc; ++idx)
    {
        a_u32_t val = a_u32_c(, a_hash_bkdr(argv[idx], 0));
#if defined(MAIN_ONCE)
        printf("case 0x%08" PRIX32 ": // %s\n    break;\n", val, argv[idx]);
#else /* !MAIN_ONCE */
        (void)(val);
#endif /* MAIN_ONCE */
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
#if defined(MAIN_ONCE)
        printf("%u ", i);
#endif /* MAIN_ONCE */
    }
#if defined(MAIN_ONCE)
    putchar('\n');
#endif /* MAIN_ONCE */

    a_foreach(int, it, p, n)
    {
#if defined(MAIN_ONCE)
        printf("%i ", *it);
#endif /* MAIN_ONCE */
    }
#if defined(MAIN_ONCE)
    putchar('\n');
#endif /* MAIN_ONCE */

    a_iterate(int, it, p, d)
    {
#if defined(MAIN_ONCE)
        printf("%i ", *it);
#endif /* MAIN_ONCE */
    }
#if defined(MAIN_ONCE)
    putchar('\n');
#endif /* MAIN_ONCE */

    a_forenum_reverse(unsigned int, i, n)
    {
        p[i] = a_cast_s(int, i);
#if defined(MAIN_ONCE)
        printf("%u ", i);
#endif /* MAIN_ONCE */
    }
#if defined(MAIN_ONCE)
    putchar('\n');
#endif /* MAIN_ONCE */

    a_foreach_reverse(int, it, p, n)
    {
#if defined(MAIN_ONCE)
        printf("%i ", *it);
#endif /* MAIN_ONCE */
    }
#if defined(MAIN_ONCE)
    putchar('\n');
#endif /* MAIN_ONCE */

    a_iterate_reverse(int, it, p, d)
    {
#if defined(MAIN_ONCE)
        printf("%i ", *it);
#endif /* MAIN_ONCE */
    }
#if defined(MAIN_ONCE)
    putchar('\n');
#endif /* MAIN_ONCE */

    a_die(int, p);
}

static void test_swap(void)
{
    a_u64_t lhs = 0;
    a_u64_t rhs = A_U64_MAX;
#if defined(MAIN_ONCE)
    printf("0x%016" PRIX64 " 0x%016" PRIX64 " -> ", lhs, rhs);
#endif /* MAIN_ONCE */
    a_swap(&lhs, &rhs, 1);
#if defined(MAIN_ONCE)
    printf("0x%016" PRIX64 " 0x%016" PRIX64 "  \n", lhs, rhs);
#endif /* MAIN_ONCE */
#if defined(MAIN_ONCE)
    printf("0x%016" PRIX64 " 0x%016" PRIX64 " -> ", lhs, rhs);
#endif /* MAIN_ONCE */
    a_swap(&lhs, &rhs, 2);
#if defined(MAIN_ONCE)
    printf("0x%016" PRIX64 " 0x%016" PRIX64 "  \n", lhs, rhs);
#endif /* MAIN_ONCE */
#if defined(MAIN_ONCE)
    printf("0x%016" PRIX64 " 0x%016" PRIX64 " -> ", lhs, rhs);
#endif /* MAIN_ONCE */
    a_swap(&lhs, &rhs, 4);
#if defined(MAIN_ONCE)
    printf("0x%016" PRIX64 " 0x%016" PRIX64 "  \n", lhs, rhs);
#endif /* MAIN_ONCE */
#if defined(MAIN_ONCE)
    printf("0x%016" PRIX64 " 0x%016" PRIX64 " -> ", lhs, rhs);
#endif /* MAIN_ONCE */
    a_swap(&lhs, &rhs, 8);
#if defined(MAIN_ONCE)
    printf("0x%016" PRIX64 " 0x%016" PRIX64 "  \n", lhs, rhs);
#endif /* MAIN_ONCE */
}

static void test_save(void)
{
    a_float_t array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (a_size_t i = 0; i < a_count_of(array); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < a_count_of(array) ? ' ' : '\n');
#endif /* MAIN_ONCE */
    }
    {
        a_float_t cache[] = {-1};
        a_float_save(array, a_count_of(array), cache, a_count_of(cache));
    }
    for (a_size_t i = 0; i < a_count_of(array); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < a_count_of(array) ? ' ' : '\n');
#endif /* MAIN_ONCE */
    }
    {
        a_float_t cache[] = {-1, -2};
        a_float_save(array, a_count_of(array), cache, a_count_of(cache));
    }
    for (a_size_t i = 0; i < a_count_of(array); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < a_count_of(array) ? ' ' : '\n');
#endif /* MAIN_ONCE */
    }
    {
        a_float_t cache[] = {-1, -2, -3, -4};
        a_float_save(array, a_count_of(array), cache, a_count_of(cache));
    }
    for (a_size_t i = 0; i < a_count_of(array); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < a_count_of(array) ? ' ' : '\n');
#endif /* MAIN_ONCE */
    }
    {
        a_float_t cache[] = {-1, -2, -3, -4, -5, -6, -7, -8};
        a_float_save(array, a_count_of(array), cache, a_count_of(cache));
    }
    for (a_size_t i = 0; i < a_count_of(array); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < a_count_of(array) ? ' ' : '\n');
#endif /* MAIN_ONCE */
    }
    {
        a_float_t cache[] = {-0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10};
        a_float_save(array, a_count_of(array), cache, a_count_of(cache));
    }
    for (a_size_t i = 0; i < a_count_of(array); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < a_count_of(array) ? ' ' : '\n');
#endif /* MAIN_ONCE */
    }
}

static void test_roll(void)
{
    a_float_t array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    a_float_t shift[16];
    for (a_size_t i = 0; i < a_count_of(array); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < a_count_of(array) ? ' ' : '\n');
#endif /* MAIN_ONCE */
    }
    a_float_roll(array, a_count_of(array), shift, 1);
    for (a_size_t i = 0; i < a_count_of(array); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < a_count_of(array) ? ' ' : '\n');
#endif /* MAIN_ONCE */
    }
    a_float_roll(array, a_count_of(array), shift, 2);
    for (a_size_t i = 0; i < a_count_of(array); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < a_count_of(array) ? ' ' : '\n');
#endif /* MAIN_ONCE */
    }
    a_float_roll(array, a_count_of(array), shift, 4);
    for (a_size_t i = 0; i < a_count_of(array); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < a_count_of(array) ? ' ' : '\n');
#endif /* MAIN_ONCE */
    }
    a_float_roll(array, a_count_of(array), shift, 8);
    for (a_size_t i = 0; i < a_count_of(array); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < a_count_of(array) ? ' ' : '\n');
#endif /* MAIN_ONCE */
    }
    a_float_roll(array, a_count_of(array), shift, 15);
    for (a_size_t i = 0; i < a_count_of(array); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < a_count_of(array) ? ' ' : '\n');
#endif /* MAIN_ONCE */
    }
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    if (argc < 2)
    {
        test_swap();
        test_save();
        test_roll();
        return 0;
    }
    a_u32_t bkdr = a_u32_c(, a_hash_bkdr(argv[1], 0));
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
