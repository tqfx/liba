#ifndef TEST_RBT_H
#define TEST_RBT_H
#define MAIN_(s, argc, argv) rbt##s(argc, argv)
#include "test.h"
#include "a/rbt.h"
#include "a/host/str.h"

typedef struct
{
    a_rbt_s node;
    a_int_t data;
    a_int_t reached;
} int_node;

static A_INLINE int_node *int_entry(a_cptr_t node)
{
    return a_rbt_entry(node, int_node, node); // NOLINT
}

static a_int_t int_cmp(a_cptr_t lhs, a_cptr_t rhs)
{
    return int_entry(lhs)->data - int_entry(rhs)->data;
}

static a_int_t intcmp(a_cptr_t lhs, a_cptr_t rhs)
{
    return *A_INT_P(lhs) - *A_INT_P(rhs);
}

static int test(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);

    const a_uint_t n = 0x1000;

    a_str_s str = A_STR_NUL;
    a_rbt_u root = A_RBT_ROOT;
    int_node *vec = a_new(int_node, A_NULL, n);
    a_int_t *sorted = a_new(a_int_t, A_NULL, n);
    for (a_uint_t i = 0; i < n; ++i)
    {
        a_str_printf(&str, "%u", i);
        vec[i].data = a_int_c(a_hash_bkdr(a_str_ptr(&str), 0));
        a_str_drop(&str);
        sorted[i] = vec[i].data;
        a_rbt_insert(&root, &vec[i].node, int_cmp);
#if defined(MAIN_ONCE)
        if (i % 0x100 == 0)
        {
            printf("insert 0x%04X/0x%04X\n", i, n);
        }
#endif /* MAIN_ONCE */
    }
    a_str_dtor(&str);

    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(a_rbt_search(&root, &vec[i].node, int_cmp));
    }

    a_uint_t x;
    qsort(sorted, n, sizeof(int), intcmp);

    x = 0;
    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_rbt_foreach(cur, &root)
    {
        int_node *it = int_entry(cur);
        TEST_BUG(it->data == sorted[x]);
        it->reached = 1;
        ++x;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }
    TEST_BUG(x == n);

    x = n;
    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_rbt_foreach_reverse(cur, &root)
    {
        int_node *it = int_entry(cur);
        TEST_BUG(it->data == sorted[--x]);
        it->reached = 1;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }
    TEST_BUG(x == 0);

    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_rbt_pre_foreach(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_rbt_pre_foreach_reverse(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_rbt_post_foreach(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_rbt_post_foreach_reverse(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (a_uint_t i = 0; i < n; ++i)
    {
        a_rbt_remove(&root, &vec[i].node);
#if defined(MAIN_ONCE)
        if (i % 0x100 == 0)
        {
            printf("remove 0x%04X/0x%04X\n", i, n);
        }
#endif /* MAIN_ONCE */
    }

    TEST_BUG(a_rbt_search(&root, &vec->node, int_cmp) == A_NULL);

    for (a_uint_t i = 0; i < n; ++i)
    {
        a_rbt_insert(&root, &vec[i].node, int_cmp);
        vec[i].reached = 0;
    }
    a_rbt_fortear(cur, next, &root)
    {
        int_entry(cur)->reached = 1;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    sorted = a_die(a_int_t, sorted);
    vec = a_die(int_node, vec);
    return 0;
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    printf("%s\n", A_FUNC);
    test(argc, argv);
    return 0;
}

#endif /* rbt.h */
