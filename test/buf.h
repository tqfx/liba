#define MAIN(x) buf##x
#include "test.h"
#include "a/buf.h"
#include <stdlib.h>

static void dtor(void *ptr)
{
    a_u32 *obj = a_u32_(*, ptr);
    debug("%" A_PRI32 "u ", *obj);
}

static int copy(void *dst, void const *src)
{
    *a_u32_(*, dst) = *a_u32_(const *, src);
    debug("%" A_PRI32 "u ", *a_u32_(const *, src));
    return 0;
}

static void test(void)
{
    {
        a_buf *ctx = a_buf_new(sizeof(a_u64), 8);
        TEST_BUG(A_BUF_AT(a_u64, ctx, 0) != A_NULL);
        TEST_BUG(A_BUF_PTR(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_TOP(a_u64, ctx) == A_NULL);
        TEST_BUG(A_BUF_END(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_PUSH(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_TOP(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_PULL(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_TOP(a_u64, ctx) == A_NULL);
        TEST_BUG(A_BUF_PULL(a_u64, ctx) == A_NULL);
        TEST_BUG(A_BUF_AT(a_u64, ctx, 0) != A_NULL);
        TEST_BUG(A_BUF_PTR(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_END(a_u64, ctx) != A_NULL);
        a_buf_die(ctx, A_NULL);
    }
    {
        a_buf *ctx = a_buf_new(sizeof(a_u64), 8);
        TEST_BUG(A_BUF_PULL_FORE(a_u64, ctx) == A_NULL);
        TEST_BUG(A_BUF_PUSH_FORE(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_PUSH_FORE(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_PULL_FORE(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_PULL_FORE(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_PULL_FORE(a_u64, ctx) == A_NULL);
        a_buf_die(ctx, A_NULL);
    }
    {
        a_buf *ctx = a_buf_new(sizeof(a_u64), 8);
        TEST_BUG(A_BUF_PULL_BACK(a_u64, ctx) == A_NULL);
        TEST_BUG(A_BUF_PUSH_BACK(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_PUSH_BACK(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_PULL_BACK(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_PULL_BACK(a_u64, ctx) != A_NULL);
        TEST_BUG(A_BUF_PULL_BACK(a_u64, ctx) == A_NULL);
        a_buf_die(ctx, A_NULL);
    }
    {
        a_buf *ctx = a_buf_new(sizeof(a_u64), 8);
        TEST_BUG(A_BUF_REMOVE(a_u64, ctx, 0) == A_NULL);
        TEST_BUG(A_BUF_INSERT(a_u64, ctx, 1) != A_NULL);
        TEST_BUG(A_BUF_INSERT(a_u64, ctx, 1) != A_NULL);
        TEST_BUG(A_BUF_REMOVE(a_u64, ctx, 1) != A_NULL);
        TEST_BUG(A_BUF_REMOVE(a_u64, ctx, 1) != A_NULL);
        TEST_BUG(A_BUF_REMOVE(a_u64, ctx, 0) == A_NULL);
        a_buf_die(ctx, A_NULL);
    }
    {
        a_buf *ctx = a_buf_new(sizeof(a_u64), 0);
        a_buf *obj = a_buf_new(sizeof(a_u64), 0);
        TEST_BUG(a_buf_store(ctx, 0, a_buf_ptr(obj), a_buf_num(obj), copy) == 0);
        TEST_BUG(a_buf_store(ctx, 0, a_buf_ptr(obj), a_buf_num(obj), A_NULL) == 0);
        TEST_BUG(a_buf_store(ctx, ~0U, a_buf_ptr(obj), a_buf_num(obj), copy) == 0);
        TEST_BUG(a_buf_store(ctx, ~0U, a_buf_ptr(obj), a_buf_num(obj), A_NULL) == 0);
        a_buf_die(ctx, dtor);
        a_buf_die(obj, A_NULL);
    }
    {
        a_u64 buf[] = {0, 1, 2, 3};
        a_buf *ctx = a_buf_new(sizeof(a_u64), 8);
        TEST_BUG(a_buf_store(ctx, 0, buf, A_LEN(buf), A_NULL) == 0);
        TEST_BUG(A_BUF_PTR(a_u64, ctx)[0] == 0);
        TEST_BUG(A_BUF_PTR(a_u64, ctx)[1] == 1);
        TEST_BUG(A_BUF_PTR(a_u64, ctx)[2] == 2);
        TEST_BUG(A_BUF_PTR(a_u64, ctx)[3] == 3);
        TEST_BUG(a_buf_erase(ctx, 9, 9, A_NULL) != 0);
        TEST_BUG(a_buf_erase(ctx, 9, 0, A_NULL) != 0);
        TEST_BUG(a_buf_erase(ctx, 0, 2, A_NULL) == 0);
        TEST_BUG(A_BUF_PTR(a_u64, ctx)[0] == 2);
        TEST_BUG(A_BUF_PTR(a_u64, ctx)[1] == 3);
        TEST_BUG(a_buf_num(ctx) == 2);
        TEST_BUG(a_buf_erase(ctx, 1, 2, A_NULL) == 0);
        TEST_BUG(A_BUF_PTR(a_u64, ctx)[0] == 2);
        TEST_BUG(a_buf_num(ctx) == 1);
        a_buf_die(ctx, A_NULL);
    }
    {
        a_u32 u32[] = {0, 1, 2, 3};
        a_u64 u64[] = {0, 1, 2, 3};
        a_buf *ctx = a_buf_new(sizeof(a_u32), 4);
        TEST_BUG(a_buf_store(ctx, 0, u32, A_LEN(u32), A_NULL) == 0);
        TEST_BUG(A_BUF_PTR(a_u32, ctx)[0] == 0);
        TEST_BUG(A_BUF_PTR(a_u32, ctx)[1] == 1);
        TEST_BUG(A_BUF_PTR(a_u32, ctx)[2] == 2);
        TEST_BUG(A_BUF_PTR(a_u32, ctx)[3] == 3);
        TEST_BUG(a_buf_num(ctx) == 4);
        a_buf_setz(ctx, sizeof(a_u64), A_NULL);
        ctx = a_buf_setm(ctx, 4);
        TEST_BUG(a_buf_store(ctx, 0, u64, A_LEN(u64), A_NULL) == 0);
        TEST_BUG(A_BUF_PTR(a_u64, ctx)[0] == 0);
        TEST_BUG(A_BUF_PTR(a_u64, ctx)[1] == 1);
        TEST_BUG(A_BUF_PTR(a_u64, ctx)[2] == 2);
        TEST_BUG(A_BUF_PTR(a_u64, ctx)[3] == 3);
        TEST_BUG(a_buf_num(ctx) == 4);
        a_buf_die(ctx, A_NULL);
    }
    {
        a_u32 i, *it, *at;
        a_u32 u32[] = {0, 1, 2, 3};
        a_buf *ctx = a_buf_new(sizeof(a_u32), 8);
        A_BUF_FORENUM(a_u32, i, ctx)
        {
            TEST_BUG(a_buf_siz(ctx) == sizeof(*it));
        }
        A_BUF_FORENUM_REVERSE(a_u32, i, ctx)
        {
            TEST_BUG(a_buf_siz(ctx) == sizeof(*it));
        }
        A_BUF_FOREACH(a_u32 *, it, at, ctx)
        {
            TEST_BUG(a_buf_siz(ctx) == sizeof(*it));
        }
        A_BUF_FOREACH_REVERSE(a_u32 *, it, at, ctx)
        {
            TEST_BUG(a_buf_siz(ctx) == sizeof(*it));
        }
        TEST_BUG(a_buf_store(ctx, 0, u32, A_LEN(u32), A_NULL) == 0);
        A_BUF_FORENUM(a_u32, i, ctx)
        {
            TEST_BUG(a_buf_siz(ctx) == sizeof(*it));
        }
        A_BUF_FORENUM_REVERSE(a_u32, i, ctx)
        {
            TEST_BUG(a_buf_siz(ctx) == sizeof(*it));
        }
        A_BUF_FOREACH(a_u32 *, it, at, ctx)
        {
            TEST_BUG(a_buf_siz(ctx) == sizeof(*it));
        }
        A_BUF_FOREACH_REVERSE(a_u32 *, it, at, ctx)
        {
            TEST_BUG(a_buf_siz(ctx) == sizeof(*it));
        }
        a_buf_die(ctx, A_NULL);
    }
}

#include "a/str.h"
#include <time.h>

typedef struct kv kv;
struct kv
{
    int key;
    int val;
};

static int small(void const *lhs, void const *rhs)
{
    kv const *a = a_cast_s(kv const *, lhs);
    kv const *b = a_cast_s(kv const *, rhs);
    return (a->key > b->key) - (a->key < b->key);
}

static int large(void const *lhs, void const *rhs)
{
    kv const *a = a_cast_s(kv const *, lhs);
    kv const *b = a_cast_s(kv const *, rhs);
    return (a->key < b->key) - (a->key > b->key);
}

static int rand10(void)
{
    return a_cast_s(int, rand() / a_cast_s(double, RAND_MAX) * 10); /* NOLINT */
}

static void test_sort(void)
{
    unsigned int t = a_cast_s(unsigned int, time(A_NULL));
    struct a_buf_kv
    {
        A_BUF_DEF;
        kv buf[10];
    } ctx_, *ctx = &ctx_;
    kv x, *it, *at;
    int i;

    a_buf_ctor(ctx, sizeof(kv), 10);
    a_buf_setn(ctx, 10, A_NULL);

    i = 0;
    srand(t);
    A_BUF_FOREACH(kv *, it, at, ctx)
    {
        it->key = rand10();
        it->val = i++;
    }
    a_buf_sort(ctx, large);
    x.key = INT_MIN;
    x.val = INT_MIN;
    A_BUF_FOREACH(kv *, it, at, ctx)
    {
        if (x.key >= 0) { TEST_BUG(x.key >= it->key); }
        x = *it;
    }

    i = 0;
    srand(t);
    A_BUF_FOREACH(kv *, it, at, ctx)
    {
        it->key = rand10();
        it->val = i++;
    }
    a_buf_sort(ctx, small);
    x.key = INT_MIN;
    x.val = INT_MIN;
    A_BUF_FOREACH(kv *, it, at, ctx)
    {
        if (x.key >= 0) { TEST_BUG(x.key <= it->key); }
        x = *it;
    }

    srand(t);
    a_buf_setn(ctx, 0, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        kv *obj = A_BUF_PUSH_FORE(kv, ctx);
        if (obj)
        {
            obj->val = 10 - i;
            obj->key = rand10();
            a_buf_sort_fore(ctx, small);
        }
    }
    x.key = INT_MIN;
    x.val = INT_MIN;
    A_BUF_FOREACH(kv *, it, at, ctx)
    {
        if (x.key >= 0) { TEST_BUG(x.key <= it->key); }
        if (x.key == it->key) { TEST_BUG(x.val < it->val); }
        x = *it;
    }

    srand(t);
    a_buf_setn(ctx, 0, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        kv *obj = A_BUF_PUSH_BACK(kv, ctx);
        if (obj)
        {
            obj->val = i;
            obj->key = rand10();
            a_buf_sort_back(ctx, small);
        }
    }
    x.key = INT_MIN;
    x.val = INT_MIN;
    A_BUF_FOREACH(kv *, it, at, ctx)
    {
        if (x.key >= 0) { TEST_BUG(x.key <= it->key); }
        if (x.key == it->key) { TEST_BUG(x.val < it->val); }
        x = *it;
    }

    srand(t);
    a_buf_setn(ctx, 0, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        kv *obj;
        x.key = rand10();
        x.val = i;
        obj = A_BUF_PUSH_SORT(kv, ctx, &x, small);
        if (obj) { *obj = x; }
    }
    x.key = INT_MIN;
    x.val = INT_MIN;
    A_BUF_FOREACH(kv *, it, at, ctx)
    {
        if (x.key >= 0) { TEST_BUG(x.key <= it->key); }
        if (x.key == it->key) { TEST_BUG(x.val < it->val); }
        x = *it;
    }

    {
        a_str *ok = a_str_new();
        a_str *no = a_str_new();
        a_str_cats(ok, "finding ");
        a_str_cats(no, "missing ");
        for (i = 0; i != 10; ++i)
        {
            kv *obj;
            x.key = i;
            obj = A_BUF_SEARCH(kv, ctx, &i, small);
            if (obj)
            {
                a_str_catf(ok, "%i ", obj->key);
            }
            else
            {
                a_str_catf(no, "%i ", i);
            }
        }
        debug("%s\n%s\n", a_str_ptr(ok), a_str_ptr(no));
        a_str_die(ok);
        a_str_die(no);
    }
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    test();
    test_sort();
    (void)argc;
    (void)argv;
    return 0;
}
