#ifndef TEST_LIST_H
#define TEST_LIST_H
#define MAIN_(s, argc, argv) list##s(argc, argv)
#include "test.h"
#include "a/list.h"
#include <stdlib.h>

typedef struct
{
    a_list_s list;
    a_cast_u data;
} a_data_s;

static a_size_t a_list_len(a_list_s const *ctx)
{
    a_size_t count = 0;
    if (!ctx)
    {
    }
    else if (ctx != ctx->next)
    {
        a_list_foreach_next(it, ctx)
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
        a_list_foreach_prev(it, ctx)
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

static void test_next(void)
{
    a_list_s *list1 = a_new(a_list_s, A_NULL, 1);
    a_list_ctor(list1);
    for (int i = 0; i != 10; ++i)
    {
        a_data_s *node = a_new(a_data_s, A_NULL, 1);
        node->data.i = i;
        a_list_add_prev(list1, &node->list);
    }
    a_list_rot_prev(list1);
    a_list_s *list2 = a_new(a_list_s, A_NULL, 1);
    a_list_ctor(list2);
    for (int i = 10; i != 21; ++i)
    {
        a_data_s *node = a_new(a_data_s, A_NULL, 1);
        node->data.i = i;
        a_list_add_prev(list2, &node->list);
    }
    {
        a_data_s *node = a_list_entry_prev(list2, a_data_s, list);
        a_list_del_prev(list2);
        a_die(a_data_s, node);
    }
    a_list_mov_prev(list1, list2);
    a_list_init(list2);
    a_list_foreach_next(it, list1)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        printf("%i ", node->data.i);
    }
    printf("%" PRIzu, a_list_len(list1));
    a_list_forsafe_next(it, pre, list1)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        a_list_del_node(&node->list);
        a_die(a_data_s, node);
    }
    if (a_list_null(list1) && a_list_null(list2))
    {
        printf(" ok");
    }
    putchar('\n');
    a_die(a_list_s, list1);
    a_die(a_list_s, list2);
}

static void test_prev(void)
{
    a_list_s *list1 = a_new(a_list_s, A_NULL, 1);
    a_list_ctor(list1);
    for (int i = 0; i != 10; ++i)
    {
        a_data_s *node = a_new(a_data_s, A_NULL, 1);
        node->data.i = i;
        a_list_add_next(list1, &node->list);
    }
    a_list_rot_next(list1);
    a_list_s *list2 = a_new(a_list_s, A_NULL, 1);
    a_list_ctor(list2);
    for (int i = 10; i != 21; ++i)
    {
        a_data_s *node = a_new(a_data_s, A_NULL, 1);
        node->data.i = i;
        a_list_add_next(list2, &node->list);
    }
    {
        a_data_s *node = a_list_entry_next(list2, a_data_s, list);
        a_list_del_next(list2);
        a_die(a_data_s, node);
    }
    a_list_mov_next(list1, list2);
    a_list_init(list2);
    a_list_foreach_prev(it, list1)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        printf("%i ", node->data.i);
    }
    printf("%" PRIzu, a_list_len(list1));
    a_list_forsafe_prev(it, pre, list1)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        a_list_del_node(&node->list);
        a_die(a_data_s, node);
    }
    if (a_list_null(list1) && a_list_null(list2))
    {
        printf(" ok");
    }
    putchar('\n');
    a_die(a_list_s, list1);
    a_die(a_list_s, list2);
}

static void test_func(void)
{
    a_list_s *list1 = a_new(a_list_s, A_NULL, 1);
    a_list_ctor(list1);
    for (int i = 0; i != 10; ++i)
    {
        a_data_s *node = a_new(a_data_s, A_NULL, 1);
        node->data.i = i;
        a_list_add_prev(list1, &node->list);
    }
    a_list_s *list2 = a_new(a_list_s, A_NULL, 1);
    a_list_ctor(list2);
    for (int i = 10; i != 20; ++i)
    {
        a_data_s *node = a_new(a_data_s, A_NULL, 1);
        node->data.i = i;
        a_list_add_prev(list2, &node->list);
    }
    a_data_s *ctx = a_new(a_data_s, A_NULL, 1);
    ctx->data.i = -1;
    {
        a_list_s *ptr = list2->prev;
        a_list_shift_node(list2->prev, &ctx->list);
        ctx = a_list_entry(ptr, a_data_s, list);
    }
    a_list_swap_node(list2->prev, list2->next);
    a_list_foreach_next(it, list1)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        printf("%i ", node->data.i);
    }
    a_list_foreach_next(it, list2)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        printf("%i ", node->data.i);
    }
    printf("%" PRIzu, a_list_len(list1) + a_list_len(list2));
    a_list_forsafe_next(it, at, list1)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        a_list_del_node(&node->list);
        a_die(a_data_s, node);
    }
    a_list_forsafe_next(it, at, list2)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        a_list_del_node(&node->list);
        a_die(a_data_s, node);
    }
    if (a_list_null(list1) && a_list_null(list2))
    {
        printf(" ok");
    }
    putchar('\n');
    a_die(a_list_s, list1);
    a_die(a_list_s, list2);
    a_die(a_data_s, ctx);
}

static void test_null(void)
{
    a_list_s list1 = A_LIST_INIT(list1);
    a_list_s list2 = A_LIST_INIT(list2);
    a_size_t len = a_list_len(&list1) + a_list_len(&list2);

    a_list_add_next(&list1, &list1);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_add_prev(&list1, &list1);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_add_next(&list1, &list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_add_prev(&list1, &list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_del_node(&list1);
    a_list_del_node(&list1);
    a_list_del_next(&list1);
    a_list_del_prev(&list1);
    a_list_ctor(&list1);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_rot_next(&list1);
    a_list_rot_prev(&list1);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_link(&list1, &list2);
    a_list_loop(&list1, &list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_rot_next(&list1);
    a_list_rot_prev(&list1);
    a_list_rot_prev(&list1);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_swap_node(&list1, &list1);
    a_list_swap_node(&list2, &list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_swap_node(&list1, &list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_swap_node(&list2, &list1);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_shift_node(&list1, &list1);
    a_list_shift_node(&list2, &list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_shift_node(&list2, &list1);
    a_list_init(&list2);
    len = a_list_len(&list1) + a_list_len(&list2);
    if (len != 0)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", A_FUNC);
    test_next();
    test_prev();
    test_func();
    test_null();
    return 0;
}

#endif /* list.h */
