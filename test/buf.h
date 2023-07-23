#ifndef TEST_BUF_H
#define TEST_BUF_H
#define MAIN_(s, argc, argv) A_CAST_2(buf, s)(argc, argv)
#include "test.h"
#include "a/buf.h"
#include <stdlib.h>

static void dtor(void *ptr)
{
    a_u32_t *obj = a_u32_c(*, ptr);
    printf("%" PRIu32 " ", *obj);
}

static void back(void)
{
    a_buf_s ctx;
    a_u32_t buf[10];
    a_buf_ctor(&ctx, buf, sizeof(a_u32_t), 10);

    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_buf_push_back(a_u32_t, &ctx);
        if (obj)
        {
            *obj = i;
        }
    }

    a_buf_foreach(a_u32_t, it, &ctx)
    {
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_buf_pull_back(a_u32_t, &ctx);
        if (obj)
        {
            printf("%" PRIu32 " ", *obj);
        }
    }
    putchar('\n');

    a_buf_dtor(&ctx, dtor);
}

static void fore(void)
{
    a_buf_s ctx;
    a_u32_t buf[10];
    a_buf_ctor(&ctx, buf, sizeof(a_u32_t), 10);

    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_buf_push_fore(a_u32_t, &ctx);
        if (obj)
        {
            *obj = i;
        }
    }

    a_buf_foreach_reverse(a_u32_t, it, &ctx)
    {
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_buf_pull_fore(a_u32_t, &ctx);
        if (obj)
        {
            printf("%" PRIu32 " ", *obj);
        }
    }
    putchar('\n');

    a_buf_dtor(&ctx, dtor);
}

#include "a/host/str.h"
#include <time.h>

static int cmp(void const *lhs, void const *rhs)
{
    return *a_int_c(const *, lhs) - *a_int_c(const *, rhs);
}

static int cmpr(void const *lhs, void const *rhs)
{
    return *a_int_c(const *, rhs) - *a_int_c(const *, lhs);
}

static int rand10(void)
{
    return a_cast_s(int, rand() / a_cast_s(double, RAND_MAX) * 10); // NOLINT
}

static void test_sort(void)
{
    a_buf_s ctx;
    int buf[10];
    unsigned int t = a_cast_s(unsigned int, time(A_NULL));
    a_buf_ctor(&ctx, buf, sizeof(int), 10);

    srand(t);
    a_buf_drop(&ctx, A_NULL);
    for (int i = 0; i != 10; ++i)
    {
        int *obj = a_buf_push_fore(int, &ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_buf_sort_fore(&ctx, cmp);
        }
    }
    printf("-> ");
    a_buf_foreach(int, it, &ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_buf_drop(&ctx, A_NULL);
    for (int i = 0; i != 10; ++i)
    {
        int *obj = a_buf_push_back(int, &ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_buf_sort_back(&ctx, cmp);
        }
    }
    printf("-> ");
    a_buf_foreach(int, it, &ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_buf_foreach(int, it, &ctx)
    {
        *it = rand10();
        printf("%i ", *it);
    }
    printf("-> ");
    a_buf_sort(&ctx, cmp);
    a_buf_foreach(int, it, &ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_buf_foreach(int, it, &ctx)
    {
        *it = rand10();
        printf("%i ", *it);
    }
    printf("-> ");
    a_buf_sort(&ctx, cmpr);
    a_buf_foreach(int, it, &ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    {
        a_str_s *ok = a_str_new();
        a_str_s *no = a_str_new();
        a_str_puts(ok, "finding ");
        a_str_puts(no, "missing ");
        for (int i = 0; i != 10; ++i)
        {
            int *obj = a_buf_search(int, &ctx, &i, cmp);
            if (obj)
            {
                a_str_printf(ok, "%i ", *obj);
            }
            else
            {
                a_str_printf(no, "%i ", i);
            }
        }
        printf("%s\n%s\n", a_str_ptr(ok), a_str_ptr(no));
        a_str_die(ok);
        a_str_die(no);
    }

    a_buf_dtor(&ctx, A_NULL);
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", A_FUNC);
    back();
    fore();
    test_sort();
    return 0;
}

#endif /* test/buf.h */
