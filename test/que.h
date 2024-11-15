#define MAIN(x) que##x
#include "test.h"
#include "a/que.h"

static void dtor(void *ptr)
{
    a_u32 *u = a_u32_(*, ptr);
    printf("%" PRIu32 " ", *u);
}

static void test(void)
{
    a_u32 i, *it, *at;
    a_que *ctx = a_que_new(sizeof(a_u64));
    for (i = 0; i != 10; ++i)
    {
        a_u64 *obj = A_QUE_PUSH_BACK(a_u64, ctx);
        if (obj) { *obj = i; }
    }
    {
        a_u64 *fore = A_QUE_FORE_(a_u64, ctx);
        a_u64 *back = A_QUE_BACK_(a_u64, ctx);
        printf("%" PRIu64 " %" PRIu64 " ", *fore, *back);
    }
    {
        a_u64 *fore = A_QUE_FORE(a_u64, ctx);
        a_u64 *back = A_QUE_BACK(a_u64, ctx);
        if (fore && back)
        {
            printf("%" PRIu64 " %" PRIu64 " ", *fore, *back);
        }
    }
    {
        a_u64 *fore = A_QUE_AT(a_u64, ctx, 0);
        a_u64 *back = A_QUE_AT(a_u64, ctx, ~0);
        if (fore && back)
        {
            printf("%" PRIu64 " %" PRIu64 "\n", *fore, *back);
        }
    }
    for (i = 0; i != 5; ++i)
    {
        a_que_pull_fore(ctx);
    }
    a_que_edit(ctx, sizeof(a_u32) + 8, A_NULL);
    for (i = 5; i--;)
    {
        a_u32 *obj = A_QUE_PUSH_FORE(a_u32, ctx);
        if (obj) { *obj = i; }
    }
    for (i = 5; i != 10; ++i)
    {
        a_u32 *obj = A_QUE_PUSH_BACK(a_u32, ctx);
        if (obj) { *obj = i; }
    }
    {
        a_u32 *obj = A_QUE_INSERT(a_u32, ctx, 0);
        if (obj) { *obj = A_U32_MAX; }
    }
    {
        a_u32 *obj = A_QUE_INSERT(a_u32, ctx, A_SIZE_MAX);
        if (obj) { *obj = A_U32_MAX; }
    }
    a_que_remove(ctx, 0);
    a_que_remove(ctx, A_SIZE_MAX);
    a_que_swap(ctx, 0, A_SIZE_MAX);
    {
        a_u32 *lhs = A_QUE_FORE_(a_u32, ctx);
        a_u32 *rhs = A_QUE_BACK_(a_u32, ctx);
        a_que_swap_(lhs, rhs);
    }
    A_QUE_FOREACH(a_u32 *, it, at, ctx)
    {
        TEST_BUG(a_que_siz(ctx) >= sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    (void)putchar('\n');
    A_QUE_FOREACH_REVERSE(a_u32 *, it, at, ctx)
    {
        TEST_BUG(a_que_siz(ctx) >= sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    (void)putchar('\n');
    for (i = 0; i != 5; ++i)
    {
        a_que_push_back(ctx);
    }
    for (i = 0; i != 5; ++i)
    {
        a_que_push_fore(ctx);
    }
    a_que_die(ctx, dtor);
    (void)putchar('\n');
}

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
    a_que *ctx = a_que_new(sizeof(int));
    int i, x, *it, *at;

    x = -1;
    srand(t);
    a_que_drop(ctx, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        int *obj = A_QUE_PUSH_FORE(int, ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_que_sort_fore(ctx, small);
        }
    }
    printf("-> ");
    A_QUE_FOREACH(int *, it, at, ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }

    x = -1;
    srand(t);
    printf("-> ");
    a_que_drop(ctx, dtor);
    (void)putchar('\n');
    for (i = 0; i != 10; ++i)
    {
        int *obj = A_QUE_PUSH_BACK(int, ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_que_sort_back(ctx, large);
        }
    }
    printf("-> ");
    A_QUE_FOREACH(int *, it, at, ctx)
    {
        if (x >= 0) { TEST_BUG(x >= *it); }
        printf("%i ", *it);
        x = *it;
    }

    x = -1;
    srand(t);
    printf("-> ");
    a_que_drop(ctx, dtor);
    (void)putchar('\n');
    for (i = 0; i != 10; ++i)
    {
        int key = rand10();
        int *obj = A_QUE_PUSH_SORT(int, ctx, &key, small);
        if (obj)
        {
            printf("%i ", key);
            *obj = key;
        }
    }
    printf("-> ");
    A_QUE_FOREACH(int *, it, at, ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }

    printf("-> ");
    a_que_die(ctx, dtor);
    (void)putchar('\n');
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
