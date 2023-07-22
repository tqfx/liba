#ifndef TEST_AVL_H
#define TEST_AVL_H
#define MAIN_(s, argc, argv) A_CAST_2(avl, s)(argc, argv)
#include "test.h"
#include "a/avl.h"
#include "a/host/str.h"

typedef struct
{
    a_avl_s node;
    int data;
    int height;
    int reached;
} int_node;

static A_INLINE int int_factor(a_avl_s *node)
{
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 3)
    return a_cast_s(int, node->_parent & 3) - 1;
#else /* !A_SIZE_POINTER */
    return node->factor;
#endif /* A_SIZE_POINTER */
}

static A_INLINE int_node *int_entry(void const *node)
{
    return a_cast_r(int_node *, a_cast_r(a_uptr_t, node) - a_offsetof(int_node, node)); // NOLINT
}

static int int_cmp(void const *lhs, void const *rhs)
{
    return int_entry(lhs)->data - int_entry(rhs)->data;
}

#define int_max(a, b) ((a) > (b) ? (a) : (b))
#define int_height(node) ((node) ? int_entry(node)->height : 0)
static void set_height(a_avl_s *node) // NOLINT
{
    if (node)
    {
        TEST_BUG(node->left != node);
        TEST_BUG(node->right != node);
        set_height(node->left);
        set_height(node->right);
        int hl = int_height(node->left);
        int hr = int_height(node->right);
        int_entry(node)->height = int_max(hl, hr) + 1;
    }
}

static void check_tree(a_avl_s *node) // NOLINT
{
    if (node)
    {
        int e = int_factor(node);
        TEST_BUG(-1 <= e && e <= 1);
        TEST_BUG(int_height(node->right) - int_height(node->left) == e);
        if (node->left)
        {
            TEST_BUG(int_entry(node->left)->data < int_entry(node)->data);
            check_tree(node->left);
        }
        if (node->right)
        {
            TEST_BUG(int_entry(node->right)->data > int_entry(node)->data);
            check_tree(node->right);
        }
    }
}

static int intcmp(void const *lhs, void const *rhs)
{
    return *a_int_c(const *, lhs) - *a_int_c(const *, rhs);
}

static int test(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);

    unsigned int const n = 0x1000;

    a_str_s str = A_STR_NUL;
    a_avl_u root = A_AVL_ROOT;
    int_node *vec = a_new(int_node, A_NULL, n);
    int *sorted = a_new(int, A_NULL, n);
    for (unsigned int i = 0; i < n; ++i)
    {
        a_str_printf(&str, "%u", i);
        vec[i].data = a_cast_s(int, a_hash_bkdr(a_str_ptr(&str), 0));
        a_str_drop(&str);
        sorted[i] = vec[i].data;
        a_avl_insert(&root, &vec[i].node, int_cmp);
        set_height(root.node);
        check_tree(root.node);
#if defined(MAIN_ONCE)
        if (i % 0x100 == 0)
        {
            printf("insert 0x%04X/0x%04X\n", i, n);
        }
#endif /* MAIN_ONCE */
    }
    a_str_dtor(&str);

    for (unsigned int i = 0; i < n; ++i)
    {
        TEST_BUG(a_avl_search(&root, &vec[i].node, int_cmp));
    }

    unsigned int x;
    qsort(sorted, n, sizeof(int), intcmp);

    x = 0;
    for (unsigned int i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_avl_foreach(cur, &root)
    {
        int_node *it = int_entry(cur);
        TEST_BUG(it->data == sorted[x]);
        it->reached = 1;
        ++x;
    }
    for (unsigned int i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }
    TEST_BUG(x == n);

    x = n;
    for (unsigned int i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_avl_foreach_reverse(cur, &root)
    {
        int_node *it = int_entry(cur);
        TEST_BUG(it->data == sorted[--x]);
        it->reached = 1;
    }
    for (unsigned int i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }
    TEST_BUG(x == 0);

    for (unsigned int i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_avl_pre_foreach(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (unsigned int i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (unsigned int i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_avl_pre_foreach_reverse(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (unsigned int i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (unsigned int i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_avl_post_foreach(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (unsigned int i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (unsigned int i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_avl_post_foreach_reverse(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (unsigned int i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (unsigned int i = 0; i < n; ++i)
    {
        a_avl_remove(&root, &vec[i].node);
        set_height(root.node);
        check_tree(root.node);
#if defined(MAIN_ONCE)
        if (i % 0x100 == 0)
        {
            printf("remove 0x%04X/0x%04X\n", i, n);
        }
#endif /* MAIN_ONCE */
    }

    TEST_BUG(a_avl_search(&root, &vec->node, int_cmp) == A_NULL);

    for (unsigned int i = 0; i < n; ++i)
    {
        a_avl_insert(&root, &vec[i].node, int_cmp);
        vec[i].reached = 0;
    }
    a_avl_fortear(cur, next, &root)
    {
        int_entry(cur)->reached = 1;
    }
    for (unsigned int i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    a_die(int_node, vec);
    a_die(int, sorted);
    return 0;
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    printf("%s\n", A_FUNC);
    test(argc, argv);
    return 0;
}

#endif /* test/avl.h */
