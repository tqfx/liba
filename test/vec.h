#define MAIN(x) vec##x
#include "test.h"
#include "a/vec.h"

static void dtor(void *ptr)
{
    a_u32 *obj = a_u32_(*, ptr);
    printf("%" PRIu32 " ", *obj);
}

static int u32dup(void *dst, void const *src)
{
    *a_u32_(*, dst) = *a_u32_(const *, src);
    printf("%" PRIu32 " ", *a_u32_(const *, src));
    return 0;
}

static void test(void)
{
    a_vec *ctx = a_vec_new(sizeof(a_u64));

    for (a_u64 i = 0; i != 10; ++i)
    {
        a_u64 *obj = A_VEC_PUSH(a_u64, ctx);
        if (obj) { *obj = i; }
    }
    a_vec_edit(ctx, sizeof(a_u32), A_NULL);
    for (a_u32 i = 0; i != 20; ++i)
    {
        a_u32 *obj = A_VEC_PUSH(a_u32, ctx);
        if (obj) { *obj = i; }
    }
    for (a_u32 i = 0; i != 10; ++i)
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

    a_vec_forenum(i, ctx)
    {
        a_u32 *it = A_VEC_AT(a_u32, ctx, i);
        TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        if (it) { printf("%" PRIu32 " ", *it); }
    }
    putchar('\n');
    a_vec_forenum_reverse(i, ctx)
    {
        a_u32 *it = A_VEC_AT(a_u32, ctx, i);
        TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        if (it) { printf("%" PRIu32 " ", *it); }
    }
    putchar('\n');

    a_vec_foreach(a_u32, *, it, ctx)
    {
        TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        TEST_BUG(sizeof(a_u32) == sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    a_vec_foreach_reverse(a_u32, *, it, ctx)
    {
        TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        TEST_BUG(sizeof(a_u32) == sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    {
        a_vec obj;
        a_vec_copy(&obj, ctx, u32dup);
        putchar('\n');
        a_vec_dtor(ctx, A_NULL);
        a_vec_move(ctx, &obj);
    }

    a_vec_die(ctx, dtor);
    putchar('\n');

    {
        ctx = a_vec_new(sizeof(a_u32));
        for (a_u32 i = 5; i != 10; ++i)
        {
            a_u32 *obj = A_VEC_INSERT(a_u32, ctx, i);
            if (obj) { *obj = i; }
        }
        for (a_u32 i = 0; i != 5; ++i)
        {
            a_u32 *obj = A_VEC_INSERT(a_u32, ctx, i);
            if (obj) { *obj = i; }
        }
        a_vec_foreach(a_u32, *, it, ctx)
        {
            printf("%" PRIu32 " ", *it);
        }
        putchar('\n');
        for (a_u32 i = 0; i != 5; ++i)
        {
            a_u32 *obj = A_VEC_REMOVE(a_u32, ctx, i);
            if (obj) { printf("%" PRIu32 " ", *obj); }
        }
        for (a_u32 i = 0; i != 5; ++i)
        {
            a_u32 *obj = A_VEC_REMOVE(a_u32, ctx, 0);
            if (obj) { printf("%" PRIu32 " ", *obj); }
        }
        putchar('\n');
        a_vec_die(ctx, A_NULL);
    }
    {
        ctx = a_vec_new(sizeof(a_u32));
        for (a_u32 i = 5; i != 10; ++i)
        {
            a_u32 *obj = A_VEC_PUSH_BACK(a_u32, ctx);
            if (obj) { *obj = i; }
        }
        for (a_u32 i = 5; i != 10; ++i)
        {
            a_u32 *obj = A_VEC_PULL_BACK(a_u32, ctx);
            if (obj) { printf("%" PRIu32 " ", *obj); }
        }
        for (a_u32 i = 0; i != 5; ++i)
        {
            a_u32 *obj = A_VEC_PUSH_FORE(a_u32, ctx);
            if (obj) { *obj = i; }
        }
        for (a_u32 i = 0; i != 5; ++i)
        {
            a_u32 *obj = A_VEC_PULL_FORE(a_u32, ctx);
            if (obj) { printf("%" PRIu32 " ", *obj); }
        }
        putchar('\n');
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
    return a_cast_s(int, rand() / a_cast_s(double, RAND_MAX) * 10); // NOLINT
}

static void test_sort(void)
{
    unsigned int t = a_cast_s(unsigned int, time(A_NULL));
    a_vec *ctx = a_vec_new(sizeof(int));
    int x;

    a_vec_make(ctx, 10, A_NULL);

    x = -1;
    srand(t);
    a_vec_foreach(int, *, it, ctx)
    {
        *it = rand10();
        printf("%i ", *it);
    }
    printf("-> ");
    a_vec_sort(ctx, large);
    a_vec_foreach(int, *, it, ctx)
    {
        if (x >= 0) { TEST_BUG(x >= *it); }
        printf("%i ", *it);
        x = *it;
    }
    putchar('\n');

    x = -1;
    srand(t);
    a_vec_foreach(int, *, it, ctx)
    {
        *it = rand10();
        printf("%i ", *it);
    }
    printf("-> ");
    a_vec_sort(ctx, small);
    a_vec_foreach(int, *, it, ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }
    putchar('\n');

    x = -1;
    srand(t);
    a_vec_drop(ctx, A_NULL);
    for (int i = 0; i != 10; ++i)
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
    a_vec_foreach(int, *, it, ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }
    putchar('\n');

    x = -1;
    srand(t);
    a_vec_drop(ctx, A_NULL);
    for (int i = 0; i != 10; ++i)
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
    a_vec_foreach(int, *, it, ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }
    putchar('\n');

    x = -1;
    srand(t);
    a_vec_drop(ctx, A_NULL);
    for (int i = 0; i != 10; ++i)
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
    a_vec_foreach(int, *, it, ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }
    putchar('\n');

    {
        a_str *ok = a_str_new();
        a_str *no = a_str_new();
        a_str_puts(ok, "finding ");
        a_str_puts(no, "missing ");
        for (int i = 0; i != 10; ++i)
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

int main(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)argc;
    (void)argv;
    printf("%s\n", A_FUNC);
    test();
    test_sort();
    return 0;
}
