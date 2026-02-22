#define MAIN(x) vec##x
#include "test.h"
#include "a/vec.h"

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
        a_vec *ctx = a_vec_new(sizeof(a_u64));
        TEST_BUG(A_VEC_AT(a_u64, ctx, 0) == A_NULL);
        TEST_BUG(A_VEC_PTR(a_u64, ctx) == A_NULL);
        TEST_BUG(A_VEC_TOP(a_u64, ctx) == A_NULL);
        TEST_BUG(A_VEC_END(a_u64, ctx) == A_NULL);
        TEST_BUG(A_VEC_PUSH(a_u64, ctx) != A_NULL);
        TEST_BUG(A_VEC_TOP(a_u64, ctx) != A_NULL);
        TEST_BUG(A_VEC_PULL(a_u64, ctx) != A_NULL);
        TEST_BUG(A_VEC_TOP(a_u64, ctx) == A_NULL);
        TEST_BUG(A_VEC_PULL(a_u64, ctx) == A_NULL);
        TEST_BUG(A_VEC_AT(a_u64, ctx, 0) != A_NULL);
        TEST_BUG(A_VEC_PTR(a_u64, ctx) != A_NULL);
        TEST_BUG(A_VEC_END(a_u64, ctx) != A_NULL);
        a_vec_die(ctx, A_NULL);
    }
    {
        a_vec *ctx = a_vec_new(sizeof(a_u64));
        TEST_BUG(A_VEC_PULL_FORE(a_u64, ctx) == A_NULL);
        TEST_BUG(A_VEC_PUSH_FORE(a_u64, ctx) != A_NULL);
        TEST_BUG(A_VEC_PUSH_FORE(a_u64, ctx) != A_NULL);
        TEST_BUG(A_VEC_PULL_FORE(a_u64, ctx) != A_NULL);
        TEST_BUG(A_VEC_PULL_FORE(a_u64, ctx) != A_NULL);
        TEST_BUG(A_VEC_PULL_FORE(a_u64, ctx) == A_NULL);
        a_vec_die(ctx, A_NULL);
    }
    {
        a_vec *ctx = a_vec_new(sizeof(a_u64));
        TEST_BUG(A_VEC_PULL_BACK(a_u64, ctx) == A_NULL);
        TEST_BUG(A_VEC_PUSH_BACK(a_u64, ctx) != A_NULL);
        TEST_BUG(A_VEC_PUSH_BACK(a_u64, ctx) != A_NULL);
        TEST_BUG(A_VEC_PULL_BACK(a_u64, ctx) != A_NULL);
        TEST_BUG(A_VEC_PULL_BACK(a_u64, ctx) != A_NULL);
        TEST_BUG(A_VEC_PULL_BACK(a_u64, ctx) == A_NULL);
        a_vec_die(ctx, A_NULL);
    }
    {
        a_vec *ctx = a_vec_new(sizeof(a_u64));
        TEST_BUG(A_VEC_REMOVE(a_u64, ctx, 0) == A_NULL);
        TEST_BUG(A_VEC_INSERT(a_u64, ctx, 1) != A_NULL);
        TEST_BUG(A_VEC_INSERT(a_u64, ctx, 1) != A_NULL);
        TEST_BUG(A_VEC_REMOVE(a_u64, ctx, 1) != A_NULL);
        TEST_BUG(A_VEC_REMOVE(a_u64, ctx, 1) != A_NULL);
        TEST_BUG(A_VEC_REMOVE(a_u64, ctx, 0) == A_NULL);
        a_vec_die(ctx, A_NULL);
    }
    {
        a_vec *ctx = a_vec_new(sizeof(a_u64));
        TEST_BUG(a_vec_store(ctx, 0, A_NULL, 0, copy) == 0);
        TEST_BUG(a_vec_store(ctx, 0, A_NULL, 0, A_NULL) == 0);
        TEST_BUG(a_vec_store(ctx, ~0U, A_NULL, 0, copy) == 0);
        TEST_BUG(a_vec_store(ctx, ~0U, A_NULL, 0, A_NULL) == 0);
        TEST_BUG(a_vec_erase(ctx, 0, 0, dtor) != 0);
        a_vec_die(ctx, dtor);
    }
    {
        a_u64 buf[] = {0, 1, 2, 3};
        a_vec *ctx = a_vec_new(sizeof(a_u64));
        TEST_BUG(a_vec_store(ctx, 0, buf, A_LEN(buf), A_NULL) == 0);
        TEST_BUG(A_VEC_PTR(a_u64, ctx)[0] == 0);
        TEST_BUG(A_VEC_PTR(a_u64, ctx)[1] == 1);
        TEST_BUG(A_VEC_PTR(a_u64, ctx)[2] == 2);
        TEST_BUG(A_VEC_PTR(a_u64, ctx)[3] == 3);
        TEST_BUG(a_vec_erase(ctx, 9, 9, A_NULL) != 0);
        TEST_BUG(a_vec_erase(ctx, 9, 0, A_NULL) != 0);
        TEST_BUG(a_vec_erase(ctx, 0, 2, A_NULL) == 0);
        TEST_BUG(A_VEC_PTR(a_u64, ctx)[0] == 2);
        TEST_BUG(A_VEC_PTR(a_u64, ctx)[1] == 3);
        TEST_BUG(a_vec_num(ctx) == 2);
        TEST_BUG(a_vec_erase(ctx, 1, 2, A_NULL) == 0);
        TEST_BUG(A_VEC_PTR(a_u64, ctx)[0] == 2);
        TEST_BUG(a_vec_num(ctx) == 1);
        a_vec_die(ctx, A_NULL);
    }
    {
        a_u32 u32[] = {0, 1, 2, 3};
        a_u64 u64[] = {0, 1, 2, 3};
        a_vec *ctx = a_vec_new(sizeof(a_u32));
        TEST_BUG(a_vec_store(ctx, 0, u32, A_LEN(u32), A_NULL) == 0);
        TEST_BUG(A_VEC_PTR(a_u32, ctx)[0] == 0);
        TEST_BUG(A_VEC_PTR(a_u32, ctx)[1] == 1);
        TEST_BUG(A_VEC_PTR(a_u32, ctx)[2] == 2);
        TEST_BUG(A_VEC_PTR(a_u32, ctx)[3] == 3);
        TEST_BUG(a_vec_num(ctx) == 4);
        a_vec_setz(ctx, sizeof(a_u64), A_NULL);
        TEST_BUG(a_vec_store(ctx, 0, u64, A_LEN(u64), A_NULL) == 0);
        TEST_BUG(A_VEC_PTR(a_u64, ctx)[0] == 0);
        TEST_BUG(A_VEC_PTR(a_u64, ctx)[1] == 1);
        TEST_BUG(A_VEC_PTR(a_u64, ctx)[2] == 2);
        TEST_BUG(A_VEC_PTR(a_u64, ctx)[3] == 3);
        TEST_BUG(a_vec_num(ctx) == 4);
        a_vec_die(ctx, A_NULL);
    }
    {
        a_u32 i, *it, *at;
        a_u32 u32[] = {0, 1, 2, 3};
        a_vec *ctx = a_vec_new(sizeof(a_u32));
        A_VEC_FORENUM(a_u32, i, ctx)
        {
            TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        }
        A_VEC_FORENUM_REVERSE(a_u32, i, ctx)
        {
            TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        }
        A_VEC_FOREACH(a_u32 *, it, at, ctx)
        {
            TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        }
        A_VEC_FOREACH_REVERSE(a_u32 *, it, at, ctx)
        {
            TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        }
        TEST_BUG(a_vec_store(ctx, 0, u32, A_LEN(u32), A_NULL) == 0);
        A_VEC_FORENUM(a_u32, i, ctx)
        {
            TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        }
        A_VEC_FORENUM_REVERSE(a_u32, i, ctx)
        {
            TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        }
        A_VEC_FOREACH(a_u32 *, it, at, ctx)
        {
            TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        }
        A_VEC_FOREACH_REVERSE(a_u32 *, it, at, ctx)
        {
            TEST_BUG(a_vec_siz(ctx) == sizeof(*it));
        }
        a_vec_die(ctx, A_NULL);
    }
}

#include "a/rand.h"
#include "a/str.h"

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

static void test_sort(void)
{
    a_rand_lcg48 lcg = A_RAND_LCG48_INIT;
    a_i64 seed = a_cast_r(a_iptr, &lcg);
    a_vec *ctx = a_vec_new(sizeof(kv));
    kv x, *it, *at;
    int i;

    a_vec_setn(ctx, 10, A_NULL);

    i = 0;
    a_rand_lcg48_init(&lcg, seed);
    A_VEC_FOREACH(kv *, it, at, ctx)
    {
        it->key = a_cast_s(int, a_rand_lcg48f(&lcg) * 10);
        it->val = i++;
    }
    a_vec_sort(ctx, large);
    x.key = INT_MIN;
    x.val = INT_MIN;
    A_VEC_FOREACH(kv *, it, at, ctx)
    {
        if (x.key >= 0) { TEST_BUG(x.key >= it->key); }
        x = *it;
    }

    i = 0;
    a_rand_lcg48_init(&lcg, seed);
    A_VEC_FOREACH(kv *, it, at, ctx)
    {
        it->key = a_cast_s(int, a_rand_lcg48f(&lcg) * 10);
        it->val = i++;
    }
    a_vec_sort(ctx, small);
    x.key = INT_MIN;
    x.val = INT_MIN;
    A_VEC_FOREACH(kv *, it, at, ctx)
    {
        if (x.key >= 0) { TEST_BUG(x.key <= it->key); }
        x = *it;
    }

    a_rand_lcg48_init(&lcg, seed);
    a_vec_setn(ctx, 0, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        kv *obj = A_VEC_PUSH_FORE(kv, ctx);
        if (obj)
        {
            obj->val = 10 - i;
            obj->key = a_cast_s(int, a_rand_lcg48f(&lcg) * 10);
            a_vec_sort_fore(ctx, small);
        }
    }
    x.key = INT_MIN;
    x.val = INT_MIN;
    A_VEC_FOREACH(kv *, it, at, ctx)
    {
        if (x.key >= 0) { TEST_BUG(x.key <= it->key); }
        if (x.key == it->key) { TEST_BUG(x.val < it->val); }
        x = *it;
    }

    a_rand_lcg48_init(&lcg, seed);
    a_vec_setn(ctx, 0, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        kv *obj = A_VEC_PUSH_BACK(kv, ctx);
        if (obj)
        {
            obj->val = i;
            obj->key = a_cast_s(int, a_rand_lcg48f(&lcg) * 10);
            a_vec_sort_back(ctx, small);
        }
    }
    x.key = INT_MIN;
    x.val = INT_MIN;
    A_VEC_FOREACH(kv *, it, at, ctx)
    {
        if (x.key >= 0) { TEST_BUG(x.key <= it->key); }
        if (x.key == it->key) { TEST_BUG(x.val < it->val); }
        x = *it;
    }

    a_rand_lcg48_init(&lcg, seed);
    a_vec_setn(ctx, 0, A_NULL);
    for (i = 0; i != 10; ++i)
    {
        kv *obj;
        x.key = a_cast_s(int, a_rand_lcg48f(&lcg) * 10);
        x.val = i;
        obj = A_VEC_PUSH_SORT(kv, ctx, &x, small);
        if (obj) { *obj = x; }
    }
    x.key = INT_MIN;
    x.val = INT_MIN;
    A_VEC_FOREACH(kv *, it, at, ctx)
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
            obj = A_VEC_SEARCH(kv, ctx, &i, small);
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

    a_vec_die(ctx, A_NULL);
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    test();
    test_sort();
    (void)argc;
    (void)argv;
    return 0;
}
