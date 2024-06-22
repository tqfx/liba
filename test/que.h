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
    a_que *ctx = a_que_new(sizeof(a_u64));
    for (a_u64 i = 0; i != 10; ++i)
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
    for (a_u64 i = 0; i != 5; ++i)
    {
        a_que_pull_fore(ctx);
    }
    a_que_edit(ctx, sizeof(a_u32) + 8, A_NULL);
    for (a_u32 i = 5; i--;)
    {
        a_u32 *obj = A_QUE_PUSH_FORE(a_u32, ctx);
        if (obj) { *obj = i; }
    }
    for (a_u32 i = 5; i != 10; ++i)
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
    a_que_foreach(a_u32, *, it, ctx)
    {
        TEST_BUG(a_que_siz(ctx) >= sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    a_que_foreach_reverse(a_u32, *, it, ctx)
    {
        TEST_BUG(a_que_siz(ctx) >= sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    for (a_u32 i = 0; i != 5; ++i)
    {
        a_que_push_back(ctx);
    }
    for (a_u32 i = 0; i != 5; ++i)
    {
        a_que_push_fore(ctx);
    }
    a_que_die(ctx, dtor);
    putchar('\n');
}

#include <time.h>

static int cmp(void const *lhs, void const *rhs)
{
    int a = *a_int_(const *, lhs);
    int b = *a_int_(const *, rhs);
    if (a == b) { return 0; }
    return a < b ? -1 : +1;
}

static int cmpr(void const *lhs, void const *rhs)
{
    int a = *a_int_(const *, lhs);
    int b = *a_int_(const *, rhs);
    if (a == b) { return 0; }
    return a > b ? -1 : +1;
}

static int rand10(void)
{
    return a_cast_s(int, rand() / a_cast_s(double, RAND_MAX) * 10); // NOLINT
}

static void test_sort(void)
{
    unsigned int t = a_cast_s(unsigned int, time(A_NULL));
    a_que *ctx = a_que_new(sizeof(int));
    int x;

    x = -1;
    srand(t);
    a_que_drop(ctx, A_NULL);
    for (int i = 0; i != 10; ++i)
    {
        int *obj = A_QUE_PUSH_FORE(int, ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_que_sort_fore(ctx, cmp);
        }
    }
    printf("-> ");
    a_que_foreach(int, *, it, ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }

    x = -1;
    srand(t);
    printf("-> ");
    a_que_drop(ctx, dtor);
    putchar('\n');
    for (int i = 0; i != 10; ++i)
    {
        int *obj = A_QUE_PUSH_BACK(int, ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_que_sort_back(ctx, cmpr);
        }
    }
    printf("-> ");
    a_que_foreach(int, *, it, ctx)
    {
        if (x >= 0) { TEST_BUG(x >= *it); }
        printf("%i ", *it);
        x = *it;
    }

    x = -1;
    srand(t);
    printf("-> ");
    a_que_drop(ctx, dtor);
    putchar('\n');
    for (int i = 0; i != 10; ++i)
    {
        int key = rand10();
        int *obj = A_QUE_PUSH_SORT(int, ctx, &key, cmp);
        if (obj)
        {
            printf("%i ", key);
            *obj = key;
        }
    }
    printf("-> ");
    a_que_foreach(int, *, it, ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }

    printf("-> ");
    a_que_die(ctx, dtor);
    putchar('\n');
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
