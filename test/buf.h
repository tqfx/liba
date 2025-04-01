#define MAIN(x) buf##x
#include "test.h"
#include "a/buf.h"
#include <stdlib.h>

static void dtor(void *ptr)
{
    a_u32 *obj = a_u32_(*, ptr);
    printf("%" A_PRI32 "u ", *obj);
}

static void back(void)
{
    a_buf ctx;
    a_u32 buf[10], i, *it, *at;
    a_buf_ctor(&ctx, buf, sizeof(a_u32), 10);

    for (i = 0; i != 20; ++i)
    {
        a_u32 *obj = A_BUF_PUSH_BACK(a_u32, &ctx);
        if (obj) { *obj = i; }
    }

    A_BUF_FOREACH(a_u32 *, it, at, &ctx)
    {
        printf("%" A_PRI32 "u ", *it);
    }
    (void)putchar('\n');

    for (i = 0; i != 20; ++i)
    {
        a_u32 *obj = A_BUF_PULL_BACK(a_u32, &ctx);
        if (obj) { printf("%" A_PRI32 "u ", *obj); }
    }
    (void)putchar('\n');

    a_buf_dtor(&ctx, dtor);
}

static void fore(void)
{
    a_buf ctx;
    a_u32 buf[10], i, *it, *at;
    a_buf_ctor(&ctx, buf, sizeof(a_u32), 10);

    for (i = 0; i != 20; ++i)
    {
        a_u32 *obj = A_BUF_PUSH_FORE(a_u32, &ctx);
        if (obj) { *obj = i; }
    }

    A_BUF_FOREACH_REVERSE(a_u32 *, it, at, &ctx)
    {
        printf("%" A_PRI32 "u ", *it);
    }
    (void)putchar('\n');

    for (i = 0; i != 20; ++i)
    {
        a_u32 *obj = A_BUF_PULL_FORE(a_u32, &ctx);
        if (obj) { printf("%" A_PRI32 "u ", *obj); }
    }
    (void)putchar('\n');

    a_buf_dtor(&ctx, dtor);
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
    int i, x;
    a_buf ctx;
    int buf[10], *it, *at;
    unsigned int t = a_cast_s(unsigned int, time(A_NULL));
    a_buf_ctor(&ctx, buf, sizeof(int), 10);

    x = -1;
    srand(t);
    a_buf_setn(&ctx, 0, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        int *obj = A_BUF_PUSH_FORE(int, &ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_buf_sort_fore(&ctx, small);
        }
    }
    printf("-> ");
    A_BUF_FOREACH(int *, it, at, &ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }
    (void)putchar('\n');

    x = -1;
    srand(t);
    a_buf_setn(&ctx, 0, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        int *obj = A_BUF_PUSH_BACK(int, &ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_buf_sort_back(&ctx, small);
        }
    }
    printf("-> ");
    A_BUF_FOREACH(int *, it, at, &ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }
    (void)putchar('\n');

    x = -1;
    srand(t);
    a_buf_setn(&ctx, 0, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        int key = rand10();
        int *obj = A_BUF_PUSH_SORT(int, &ctx, &key, small);
        if (obj)
        {
            printf("%i ", key);
            *obj = key;
        }
    }
    printf("-> ");
    A_BUF_FOREACH(int *, it, at, &ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }
    (void)putchar('\n');

    x = -1;
    srand(t);
    A_BUF_FOREACH(int *, it, at, &ctx)
    {
        *it = rand10();
        printf("%i ", *it);
    }
    printf("-> ");
    a_buf_sort(&ctx, small);
    A_BUF_FOREACH(int *, it, at, &ctx)
    {
        if (x >= 0) { TEST_BUG(x <= *it); }
        printf("%i ", *it);
        x = *it;
    }
    (void)putchar('\n');

    x = -1;
    srand(t);
    A_BUF_FOREACH(int *, it, at, &ctx)
    {
        *it = rand10();
        printf("%i ", *it);
    }
    printf("-> ");
    a_buf_sort(&ctx, large);
    A_BUF_FOREACH(int *, it, at, &ctx)
    {
        if (x >= 0) { TEST_BUG(x >= *it); }
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
            int *obj = A_BUF_SEARCH(int, &ctx, &i, large);
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

    a_buf_dtor(&ctx, A_NULL);
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    puts(A_FUNC);
    back();
    fore();
    test_sort();
    (void)argc;
    (void)argv;
    return 0;
}
