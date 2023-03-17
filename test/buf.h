#ifndef TEST_BUF_H
#define TEST_BUF_H
#define MAIN_(s, argc, argv) buf##s(argc, argv)
#include "test.h"
#include "a/buf.h"
#include <stdlib.h>

static void dtor(a_vptr_t ptr)
{
    a_u32_t *obj = a_u32_p(ptr);
    printf("%" PRIu32 " ", *obj);
}

static void back(void)
{
    a_buf_s ctx[1];
    a_u32_t buf[10];
    a_buf_ctor(ctx, buf, sizeof(a_u32_t), 10);

    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_buf_push_back(a_u32_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }

    a_buf_foreach(a_u32_t, it, ctx)
    {
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_buf_pull_back(a_u32_t, ctx);
        if (obj)
        {
            printf("%" PRIu32 " ", *obj);
        }
    }
    putchar('\n');

    a_buf_dtor(ctx, dtor);
}

static void fore(void)
{
    a_buf_s ctx[1];
    a_u32_t buf[10];
    a_buf_ctor(ctx, buf, sizeof(a_u32_t), 10);

    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_buf_push_fore(a_u32_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }

    a_buf_foreach_reverse(a_u32_t, it, ctx)
    {
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_buf_pull_fore(a_u32_t, ctx);
        if (obj)
        {
            printf("%" PRIu32 " ", *obj);
        }
    }
    putchar('\n');

    a_buf_dtor(ctx, dtor);
}

#include "a/host/str.h"
#include <time.h>

static a_int_t cmp(a_cptr_t lhs, a_cptr_t rhs)
{
    return *A_INT_P(lhs) - *A_INT_P(rhs);
}

static a_int_t cmpr(a_cptr_t lhs, a_cptr_t rhs)
{
    return *A_INT_P(rhs) - *A_INT_P(lhs);
}

static a_int_t rand10(void)
{
    return a_int_c(rand() / a_double_c(RAND_MAX) * 10);
}

static void test_sort(void)
{
    a_buf_s ctx[1];
    a_int_t buf[10];
    a_uint_t t = a_uint_c(time(A_NULL));
    a_buf_ctor(ctx, buf, sizeof(a_int_t), 10);

    srand(t);
    a_buf_drop(ctx, A_NULL);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_int_t *obj = a_buf_push_fore(a_int_t, ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_buf_sort_fore(ctx, cmp);
        }
    }
    printf("-> ");
    a_buf_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_buf_drop(ctx, A_NULL);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_int_t *obj = a_buf_push_back(a_int_t, ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_buf_sort_back(ctx, cmp);
        }
    }
    printf("-> ");
    a_buf_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_buf_foreach(a_int_t, it, ctx)
    {
        *it = rand10();
        printf("%i ", *it);
    }
    printf("-> ");
    a_buf_sort(ctx, cmp);
    a_buf_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_buf_foreach(a_int_t, it, ctx)
    {
        *it = rand10();
        printf("%i ", *it);
    }
    printf("-> ");
    a_buf_sort(ctx, cmpr);
    a_buf_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    {
        a_str_s *ok = a_str_new();
        a_str_s *no = a_str_new();
        a_str_puts(ok, "finding ");
        a_str_puts(no, "missing ");
        for (a_int_t i = 0; i != 10; ++i)
        {
            a_int_t *obj = a_buf_search(a_int_t, ctx, &i, cmp);
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

    a_buf_dtor(ctx, A_NULL);
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

#endif /* buf.h */
