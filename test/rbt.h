#define MAIN(x) rbt##x
#include "test.h"
#include "a/rbt.h"
#include "a/str.h"
#include "a/hash.h"

typedef struct
{
    a_rbt_node node;
    int data;
    int reached;
} int_node;

static A_INLINE int_node *int_entry(void const *node)
{
    return a_cast_r(int_node *, a_cast_r(a_uptr, node) - a_offsetof(int_node, node)); /* NOLINT */
}

static int int_cmp(void const *lhs, void const *rhs)
{
    int a = int_entry(lhs)->data;
    int b = int_entry(rhs)->data;
    return (a > b) - (a < b);
}

static int intcmp(void const *lhs, void const *rhs)
{
    int a = *a_int_(const *, lhs);
    int b = *a_int_(const *, rhs);
    return (a > b) - (a < b);
}

static int test(unsigned long n)
{
    unsigned int i;
    unsigned long x;
    a_rbt_node *cur, *next;
    a_str str = A_STR_INIT;
    a_rbt root = A_RBT_ROOT;
    int *sorted = a_new(int, A_NULL, n);
    int_node *vec = a_new(int_node, A_NULL, n);
    for (i = 0; i < n; ++i)
    {
        a_str_setn_(&str, 0);
        a_str_catf(&str, "%u", i);
        vec[i].data = sorted[i] = a_cast_s(int, a_hash_bkdr(a_str_ptr(&str), 0));
        a_rbt_insert(&root, &vec[i].node, int_cmp);
        if (i % 0x100 == 0)
        {
            debug("insert 0x%04X/0x%04lX\n", i, n);
        }
    }
    a_str_dtor(&str);

    for (i = 0; i < n; ++i)
    {
        TEST_BUG(a_rbt_search(&root, &vec[i].node, int_cmp));
    }

    qsort(sorted, n, sizeof(int), intcmp);

    x = 0;
    for (i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    A_RBT_FOREACH(cur, &root)
    {
        int_node *it = int_entry(cur);
        TEST_BUG(it->data == sorted[x]);
        it->reached = 1;
        ++x;
    }
    for (i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }
    TEST_BUG(x == n);

    x = n;
    for (i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    A_RBT_FOREACH_REVERSE(cur, &root)
    {
        int_node *it = int_entry(cur);
        TEST_BUG(it->data == sorted[--x]);
        it->reached = 1;
    }
    for (i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }
    TEST_BUG(x == 0);

    for (i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    A_RBT_PRE_FOREACH(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    A_RBT_PRE_FOREACH_REVERSE(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    A_RBT_POST_FOREACH(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    A_RBT_POST_FOREACH_REVERSE(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (i = 0; i < n; ++i)
    {
        a_rbt_remove(&root, &vec[i].node);
        if (i % 0x100 == 0)
        {
            debug("remove 0x%04X/0x%04lX\n", i, n);
        }
    }

    TEST_BUG(!a_rbt_search(&root, &vec->node, int_cmp));

    for (i = 0; i < n; ++i)
    {
        a_rbt_insert(&root, &vec[i].node, int_cmp);
        vec[i].reached = 0;
    }
    A_RBT_FORTEAR(cur, next, &root)
    {
        int_entry(cur)->reached = 1;
    }
    for (i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    a_die(sorted);
    a_die(vec);
    return 0;
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    unsigned long n = 0x1000;
    if (argc > 1) { n = strtoul(argv[1], A_NULL, 0); }
    puts(A_FUNC);
    test(n);
    return 0;
}
