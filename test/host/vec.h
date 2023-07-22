#ifndef TEST_HOST_VEC_H
#define TEST_HOST_VEC_H
#define MAIN_(s, argc, argv) A_CAST_2(vec, s)(argc, argv)
#include "../test.h"
#include "a/host/vec.h"
#include <string.h>

static void dtor(void *ptr)
{
    a_u32_t *obj = a_u32_c(*, ptr);
    printf("%" PRIu32 " ", *obj);
}

static int u32dup(void *dst, void const *src)
{
    *a_u32_c(*, dst) = *a_u32_c(const *, src);
    printf("%" PRIu32 " ", *a_u32_c(const *, src));
    return 0;
}

static void test(void)
{
    a_vec_s *ctx = a_vec_new(sizeof(a_u64_t));
    a_vec_foreach(a_u64_t, it, ctx);
    a_vec_foreach_reverse(a_u64_t, it, ctx);
    for (a_u64_t i = 0; i != 10; ++i)
    {
        a_u64_t *obj = a_vec_push(a_u64_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }
    a_vec_set(ctx, sizeof(a_u32_t), A_NULL);
    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_vec_push(a_u32_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }
    for (a_u32_t i = 0; i != 10; ++i)
    {
        (void)(a_vec_pull(a_u32_t, ctx));
    }

    {
        a_u8_t *end = a_vec_end(a_u8_t, ctx);
        a_u8_t *top = a_vec_top(a_u8_t, ctx);
        TEST_BUG(a_vec_get(ctx) == a_size_c(, end - top));
    }

    a_vec_swap(ctx, 0, 0);
    a_vec_swap(ctx, 0, ~0U);
    a_vec_swap(ctx, ~0U, 0);
    a_vec_swap(ctx, 4, 6);
    a_vec_swap(ctx, 6, 4);

    a_vec_forenum(i, ctx)
    {
        a_u32_t *it = a_vec_at(a_u32_t, ctx, i);
        TEST_BUG(a_vec_get(ctx) == sizeof(*it));
        if (it)
        {
            printf("%" PRIu32 " ", *it);
        }
    }
    putchar('\n');
    a_vec_forenum_reverse(i, ctx)
    {
        a_u32_t *it = a_vec_at(a_u32_t, ctx, i);
        TEST_BUG(a_vec_get(ctx) == sizeof(*it));
        if (it)
        {
            printf("%" PRIu32 " ", *it);
        }
    }
    putchar('\n');

    a_vec_foreach(a_u32_t, it, ctx)
    {
        TEST_BUG(a_vec_get(ctx) == sizeof(*it));
        TEST_BUG(sizeof(a_u32_t) == sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    a_vec_foreach_reverse(a_u32_t, it, ctx)
    {
        TEST_BUG(a_vec_get(ctx) == sizeof(*it));
        TEST_BUG(sizeof(a_u32_t) == sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    {
        a_vec_s obj;
        a_vec_copy(&obj, ctx, u32dup);
        putchar('\n');
        a_vec_dtor(ctx, A_NULL);
        a_vec_move(ctx, &obj);
    }

    a_vec_die(ctx, dtor);
    putchar('\n');

    {
        ctx = a_vec_new(sizeof(a_u32_t));
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *obj = a_vec_insert(a_u32_t, ctx, i);
            if (obj)
            {
                *obj = i;
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *obj = a_vec_insert(a_u32_t, ctx, i);
            if (obj)
            {
                *obj = i;
            }
        }
        a_vec_foreach(a_u32_t, it, ctx)
        {
            printf("%" PRIu32 " ", *it);
        }
        putchar('\n');
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *obj = a_vec_remove(a_u32_t, ctx, i);
            if (obj)
            {
                printf("%" PRIu32 " ", *obj);
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *obj = a_vec_remove(a_u32_t, ctx, 0);
            if (obj)
            {
                printf("%" PRIu32 " ", *obj);
            }
        }
        putchar('\n');
        a_vec_die(ctx, A_NULL);
    }
    {
        ctx = a_vec_new(sizeof(a_u32_t));
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *obj = a_vec_push_back(a_u32_t, ctx);
            if (obj)
            {
                *obj = i;
            }
        }
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *obj = a_vec_pull_back(a_u32_t, ctx);
            if (obj)
            {
                printf("%" PRIu32 " ", *obj);
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *obj = a_vec_push_fore(a_u32_t, ctx);
            if (obj)
            {
                *obj = i;
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *obj = a_vec_pull_fore(a_u32_t, ctx);
            if (obj)
            {
                printf("%" PRIu32 " ", *obj);
            }
        }
        putchar('\n');
        a_vec_die(ctx, A_NULL);
    }
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

static void test_sort(void)
{
    unsigned int t = a_cast_s(unsigned int, time(A_NULL));
    a_vec_s *ctx = a_vec_new(sizeof(int));

    a_vec_make(ctx, 10, A_NULL);

    srand(t);
    a_vec_foreach(int, it, ctx)
    {
        *it = rand() % 10;
        printf("%i ", *it);
    }
    printf("-> ");
    a_vec_sort(ctx, cmpr);
    a_vec_foreach(int, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_vec_foreach(int, it, ctx)
    {
        *it = rand() % 10;
        printf("%i ", *it);
    }
    printf("-> ");
    a_vec_sort(ctx, cmp);
    a_vec_foreach(int, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_vec_drop(ctx, A_NULL);
    for (int i = 0; i != 10; ++i)
    {
        int *obj = a_vec_push_fore(int, ctx);
        if (obj)
        {
            *obj = rand() % 10;
            printf("%i ", *obj);
            a_vec_sort_fore(ctx, cmp);
        }
    }
    printf("-> ");
    a_vec_foreach(int, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_vec_drop(ctx, A_NULL);
    for (int i = 0; i != 10; ++i)
    {
        int *obj = a_vec_push_back(int, ctx);
        if (obj)
        {
            *obj = rand() % 10;
            printf("%i ", *obj);
            a_vec_sort_back(ctx, cmp);
        }
    }
    printf("-> ");
    a_vec_foreach(int, it, ctx)
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
            int *obj = a_vec_search(int, ctx, &i, cmp);
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

    a_vec_die(ctx, A_NULL);
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", A_FUNC);
    test();
    test_sort();
    return 0;
}

#endif /* test/host/vec.h */
