#define MAIN(x) list##x
#include "test.h"
#include "a/list.h"

static a_size a_list_len(a_list const *ctx)
{
    a_size count = 0;
    if (!ctx) {}
    else if (ctx != ctx->next)
    {
        a_list *it;
        A_LIST_FOREACH_NEXT(it, ctx)
        {
            if (it == it->next)
            {
                printf("\nwarning endless loop!\n");
                break;
            }
            ++count;
        }
    }
    else if (ctx != ctx->prev)
    {
        a_list *it;
        A_LIST_FOREACH_PREV(it, ctx)
        {
            if (it == it->prev)
            {
                printf("\nwarning endless loop!\n");
                break;
            }
            ++count;
        }
    }
    return count;
}

typedef struct
{
    a_list node;
    a_cast data;
} data;

static void test_next(void)
{
    int i;
    a_list *list1, *list2;
    a_list *it, *at, *next;
    list1 = a_new(a_list, A_NULL, 1);
    a_list_ctor(list1);
    for (i = 0; i != 10; ++i)
    {
        data *node = a_new(data, A_NULL, 1);
        node->data.i = i;
        a_list_add_prev(list1, &node->node);
    }
    a_list_rot_prev(list1);
    list2 = a_new(a_list, A_NULL, 1);
    a_list_ctor(list2);
    for (i = 10; i != 21; ++i)
    {
        data *node = a_new(data, A_NULL, 1);
        node->data.i = i;
        a_list_add_prev(list2, &node->node);
    }
    {
        data *node = a_list_entry_prev(list2, data, node); /* NOLINT(performance-no-int-to-ptr) */
        a_list_del_prev(list2);
        a_die(node);
    }
    next = list2->next;
    a_list_mov_prev(list1, list2);
    A_LIST_FOREACH_NEXT(it, list1)
    {
        data *node = a_list_entry(it, data, node); /* NOLINT(performance-no-int-to-ptr) */
        printf("%i ", node->data.i);
    }
    printf("%" A_PRIz "u", a_list_len(list1));
    A_LIST_FORSAFE_NEXT(it, at, list1)
    {
        data *node = a_list_entry(it, data, node); /* NOLINT(performance-no-int-to-ptr) */
        a_list_del_node(&node->node);
        a_die(node);
    }
    if (list1->next == list1 && list2->next == next)
    {
        printf(" ok");
    }
    (void)putchar('\n');
    a_die(list1);
    a_die(list2);
}

static void test_prev(void)
{
    int i;
    a_list *list1, *list2;
    a_list *it, *at, *prev;
    list1 = a_new(a_list, A_NULL, 1);
    a_list_ctor(list1);
    for (i = 0; i != 10; ++i)
    {
        data *node = a_new(data, A_NULL, 1);
        node->data.i = i;
        a_list_add_next(list1, &node->node);
    }
    a_list_rot_next(list1);
    list2 = a_new(a_list, A_NULL, 1);
    a_list_ctor(list2);
    for (i = 10; i != 21; ++i)
    {
        data *node = a_new(data, A_NULL, 1);
        node->data.i = i;
        a_list_add_next(list2, &node->node);
    }
    {
        data *node = a_list_entry_next(list2, data, node); /* NOLINT(performance-no-int-to-ptr) */
        a_list_del_next(list2);
        a_die(node);
    }
    prev = list2->prev;
    a_list_mov_next(list1, list2);
    A_LIST_FOREACH_PREV(it, list1)
    {
        data *node = a_list_entry(it, data, node); /* NOLINT(performance-no-int-to-ptr) */
        printf("%i ", node->data.i);
    }
    printf("%" A_PRIz "u", a_list_len(list1));
    A_LIST_FORSAFE_PREV(it, at, list1)
    {
        data *node = a_list_entry(it, data, node); /* NOLINT(performance-no-int-to-ptr) */
        a_list_del_node(&node->node);
        a_die(node);
    }
    if (list1->prev == list1 && list2->prev == prev)
    {
        printf(" ok");
    }
    (void)putchar('\n');
    a_die(list1);
    a_die(list2);
}

static void test_func(void)
{
    int i;
    data *ctx;
    a_list *it, *at;
    a_list *list1, *list2;
    list1 = a_new(a_list, A_NULL, 1);
    a_list_ctor(list1);
    for (i = 0; i != 10; ++i)
    {
        data *node = a_new(data, A_NULL, 1);
        node->data.i = i;
        a_list_add_prev(list1, &node->node);
    }
    list2 = a_new(a_list, A_NULL, 1);
    a_list_ctor(list2);
    for (i = 10; i != 20; ++i)
    {
        data *node = a_new(data, A_NULL, 1);
        node->data.i = i;
        a_list_add_prev(list2, &node->node);
    }
    ctx = a_new(data, A_NULL, 1);
    ctx->data.i = -1;
    {
        a_list *ptr = list2->prev;
        a_list_set_node(ptr, &ctx->node);
        ctx = a_list_entry(ptr, data, node); /* NOLINT(performance-no-int-to-ptr) */
    }
    a_list_swap_node(list2->prev, list2->next);
    A_LIST_FOREACH_NEXT(it, list1)
    {
        data *node = a_list_entry(it, data, node); /* NOLINT(performance-no-int-to-ptr) */
        printf("%i ", node->data.i);
    }
    A_LIST_FOREACH_NEXT(it, list2)
    {
        data *node = a_list_entry(it, data, node); /* NOLINT(performance-no-int-to-ptr) */
        printf("%i ", node->data.i);
    }
    printf("%" A_PRIz "u", a_list_len(list1) + a_list_len(list2));
    A_LIST_FORSAFE_NEXT(it, at, list1)
    {
        data *node = a_list_entry(it, data, node); /* NOLINT(performance-no-int-to-ptr) */
        a_list_del_node(&node->node);
        a_die(node);
    }
    A_LIST_FORSAFE_NEXT(it, at, list2)
    {
        data *node = a_list_entry(it, data, node); /* NOLINT(performance-no-int-to-ptr) */
        a_list_del_node(&node->node);
        a_die(node);
    }
    if (list1->next == list1 && list2->next == list2)
    {
        printf(" ok");
    }
    (void)putchar('\n');
    a_die(list1);
    a_die(list2);
    a_die(ctx);
}

static void test_null(void)
{
    static a_list list1 = A_LIST_INIT(list1);
    static a_list list2 = A_LIST_INIT(list2);
    a_size len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_add_next(&list1, &list1);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_add_prev(&list1, &list1);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_add_next(&list1, &list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_add_prev(&list1, &list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_del_node(&list1);
    a_list_del_node(&list1);
    a_list_del_next(&list1);
    a_list_del_prev(&list1);
    a_list_ctor(&list1);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_rot_next(&list1);
    a_list_rot_prev(&list1);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_link(&list1, &list2);
    a_list_loop(&list1, &list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_rot_next(&list1);
    a_list_rot_prev(&list1);
    a_list_rot_prev(&list1);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_swap_node(&list1, &list1);
    a_list_swap_node(&list2, &list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_swap_node(&list1, &list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_swap_node(&list2, &list1);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_set_node(&list1, &list1);
    a_list_set_node(&list2, &list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }

    a_list_set_node(&list2, &list1);
    a_list_init(&list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" A_PRIz "u\n", __FILE__, __LINE__, len);
    }
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    puts(A_FUNC);
    test_next();
    test_prev();
    test_func();
    test_null();
    (void)argc;
    (void)argv;
    return 0;
}
