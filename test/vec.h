#define MAIN(x) vec##x
#include "test.h"
#include "a/vec.h"

static void dtor(void *ptr)
{
    a_u32 *obj = a_u32_(*, ptr);
    printf("%" A_PRI32 "u ", *obj);
}

static int u32dup(void *dst, void const *src)
{
    *a_u32_(*, dst) = *a_u32_(const *, src);
    printf("%" A_PRI32 "u ", *a_u32_(const *, src));
    return 0;
}

static void test(void)
{
    a_u32 i, *it, *at;
    a_vec *ctx = a_vec_new(sizeof(a_u64));

    for (i = 0; i != 10; ++i)
    {
        a_u64 *obj = A_VEC_PUSH(a_u64, ctx);
        if (obj) { *obj = i; }
    }
    a_vec_setz(ctx, sizeof(a_u32), A_NULL);
    for (i = 0; i != 20; ++i)
    {
        a_u32 *obj = A_VEC_PUSH(a_u32, ctx);
        if (obj) { *obj = i; }
    }
    for (i = 0; i != 10; ++i)
    {
        a_vec_pull(ctx);
    }

    {
        a_u8 *end = A_VEC_END(a_u8, ctx);
        a_u8 *top = A_VEC_TOP(a_u8, ctx);
        TEST_BUG(a_vec_siz(ctx) == a_size_c(end - top));
    }

    a_vec_swap(ctx, 0, 0);
    a_vec_swap(ctx, 0, ~0U);
    a_vec_swap(ctx, ~0U, 0);
    a_vec_swap(ctx, 4, 6);
    a_vec_swap(ctx, 6, 4);

    A_VEC_FORENUM(a_u32, i, ctx)
    {
        it = A_VEC_AT(a_u32, ctx, i);
        TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        if (it) { printf("%" A_PRI32 "u ", *it); }
    }
    (void)putchar('\n');
    A_VEC_FORENUM_REVERSE(a_u32, i, ctx)
    {
        it = A_VEC_AT(a_u32, ctx, i);
        TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        if (it) { printf("%" A_PRI32 "u ", *it); }
    }
    (void)putchar('\n');

    A_VEC_FOREACH(a_u32 *, it, at, ctx)
    {
        TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        TEST_BUG(sizeof(a_u32) == sizeof(*it));
        printf("%" A_PRI32 "u ", *it);
    }
    (void)putchar('\n');
    A_VEC_FOREACH_REVERSE(a_u32 *, it, at, ctx)
    {
        TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        TEST_BUG(sizeof(a_u32) == sizeof(*it));
        printf("%" A_PRI32 "u ", *it);
    }
    (void)putchar('\n');

    {
        a_vec obj;
        a_vec_copy(&obj, ctx, u32dup);
        (void)putchar('\n');
        a_vec_dtor(ctx, A_NULL);
        a_vec_move(ctx, &obj);
    }

    a_vec_die(ctx, dtor);
    (void)putchar('\n');

    {
        ctx = a_vec_new(sizeof(a_u32));
        for (i = 5; i != 10; ++i)
        {
            a_u32 *obj = A_VEC_INSERT(a_u32, ctx, i);
            if (obj) { *obj = i; }
        }
        for (i = 0; i != 5; ++i)
        {
            a_u32 *obj = A_VEC_INSERT(a_u32, ctx, i);
            if (obj) { *obj = i; }
        }
        A_VEC_FOREACH(a_u32 *, it, at, ctx)
        {
            printf("%" A_PRI32 "u ", *it);
        }
        (void)putchar('\n');
        for (i = 0; i != 5; ++i)
        {
            a_u32 *obj = A_VEC_REMOVE(a_u32, ctx, i);
            if (obj) { printf("%" A_PRI32 "u ", *obj); }
        }
        for (i = 0; i != 5; ++i)
        {
            a_u32 *obj = A_VEC_REMOVE(a_u32, ctx, 0);
            if (obj) { printf("%" A_PRI32 "u ", *obj); }
        }
        (void)putchar('\n');
        a_vec_die(ctx, A_NULL);
    }
    {
        ctx = a_vec_new(sizeof(a_u32));
        for (i = 5; i != 10; ++i)
        {
            a_u32 *obj = A_VEC_PUSH_BACK(a_u32, ctx);
            if (obj) { *obj = i; }
        }
        for (i = 5; i != 10; ++i)
        {
            a_u32 *obj = A_VEC_PULL_BACK(a_u32, ctx);
            if (obj) { printf("%" A_PRI32 "u ", *obj); }
        }
        for (i = 0; i != 5; ++i)
        {
            a_u32 *obj = A_VEC_PUSH_FORE(a_u32, ctx);
            if (obj) { *obj = i; }
        }
        for (i = 0; i != 5; ++i)
        {
            a_u32 *obj = A_VEC_PULL_FORE(a_u32, ctx);
            if (obj) { printf("%" A_PRI32 "u ", *obj); }
        }
        (void)putchar('\n');
        a_vec_die(ctx, A_NULL);
    }
}

#include "a/str.h"
#include <time.h>

static int small(void const *lhs, void const *rhs)
{
    int a = *a_int_(const *, lhs);
    int b = *a_int_(const *, rhs);
    return (a > b) - (a < b);
}

static int large(void const *lhs, void const *rhs)
{
    int a = *a_int_(const *, lhs);
    int b = *a_int_(const *, rhs);
    return (a < b) - (a > b);
}

static int rand10(void)
{
    return a_cast_s(int, rand() / a_cast_s(double, RAND_MAX) * 10); /* NOLINT */
}

static void test_sort(void)
{
    unsigned int t = a_cast_s(unsigned int, time(A_NULL));
    a_vec *ctx = a_vec_new(sizeof(int));
    int i, x, *it, *at;

    a_vec_setn(ctx, 10, A_NULL);

    x = -1;
    srand(t);
    A_VEC_FOREACH(int *, it, at, ctx)
    {
        *it = rand10();
        printf("%i ", *it);
    }
    printf("-> ");
    a_vec_sort(ctx, large);
    A_VEC_FOREACH(int *, it, at, ctx)
    {
        if (x >= 0) { TEST_BUG(x >= *it); }
        printf("%i ", *it);
        x = *it;
    }
    (void)putchar('\n');

    x = -1;
    srand(t);
    A_VEC_FOREACH(int *, it, at, ctx)
    {
        *it = rand10();
        printf("%i ", *it);
    }
    printf("-> ");
    a_vec_sort(ctx, small);
    A_VEC_FOREACH(int *, it, at, ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }
    (void)putchar('\n');

    x = -1;
    srand(t);
    a_vec_setn(ctx, 0, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        int *obj = A_VEC_PUSH_FORE(int, ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_vec_sort_fore(ctx, small);
        }
    }
    printf("-> ");
    A_VEC_FOREACH(int *, it, at, ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }
    (void)putchar('\n');

    x = -1;
    srand(t);
    a_vec_setn(ctx, 0, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        int *obj = A_VEC_PUSH_BACK(int, ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_vec_sort_back(ctx, small);
        }
    }
    printf("-> ");
    A_VEC_FOREACH(int *, it, at, ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }
    (void)putchar('\n');

    x = -1;
    srand(t);
    a_vec_setn(ctx, 0, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        int key = rand10();
        int *obj = A_VEC_PUSH_SORT(int, ctx, &key, small);
        if (obj)
        {
            printf("%i ", key);
            *obj = key;
        }
    }
    printf("-> ");
    A_VEC_FOREACH(int *, it, at, ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }
    (void)putchar('\n');

    {
        a_str *ok = a_str_new();
        a_str *no = a_str_new();
        a_str_puts(ok, "finding ");
        a_str_puts(no, "missing ");
        for (i = 0; i != 10; ++i)
        {
            int *obj = A_VEC_SEARCH(int, ctx, &i, small);
            if (obj)
            {
                a_str_putf(ok, "%i ", *obj);
            }
            else
            {
                a_str_putf(no, "%i ", i);
            }
        }
        printf("%s\n%s\n", a_str_ptr(ok), a_str_ptr(no));
        a_str_die(ok);
        a_str_die(no);
    }

    a_vec_die(ctx, A_NULL);
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    puts(A_FUNC);
    test();
    test_sort();
    (void)argc;
    (void)argv;
    return 0;
}
