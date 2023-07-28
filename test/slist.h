#ifndef TEST_SLIST_H
#define TEST_SLIST_H
#define MAIN_(s, argc, argv) A_CAST_2(slist, s)(argc, argv)
#include "test.h"
#include "a/slist.h"
#include <stdlib.h>

typedef struct
{
    a_slist_u list;
    a_cast_u data;
} a_data_s;

static a_size_t a_slist_len(a_slist_s const *const ctx)
{
    a_size_t count = 0;
    if (ctx && ctx->head.next != &ctx->head)
    {
        a_slist_foreach(it, ctx)
        {
            if (it->next == it)
            {
                printf("\nwarning endless loop!\n");
                break;
            }
            ++count;
        }
    }
    return count;
}

static void test(void)
{
    a_slist_s *list1 = a_new(a_slist_s, A_NULL, 1);
    a_slist_ctor(list1);
    for (int i = 0; i != 10; ++i)
    {
        a_data_s *node = a_new(a_data_s, A_NULL, 1);
        node->data.i = i;
        a_slist_add_tail(list1, &node->list);
    }
    a_slist_s *list2 = a_new(a_slist_s, A_NULL, 1);
    a_slist_ctor(list2);
    for (int i = 14; i != 9; --i)
    {
        a_data_s *node = a_new(a_data_s, A_NULL, 1);
        node->data.i = i;
        a_slist_add_head(list2, &node->list);
    }
    a_slist_s *list3 = a_new(a_slist_s, A_NULL, 1);
    a_slist_ctor(list3);
    for (int i = 15; i != 20; ++i)
    {
        a_data_s *node = a_new(a_data_s, A_NULL, 1);
        node->data.i = i;
        a_slist_add(list3, list3->tail, &node->list);
    }
    a_slist_rot(list1);
    a_slist_mov(list3, &list3->head, list2);
    a_slist_dtor(list2);
    a_slist_mov(list1, list1->tail, list3);
    a_slist_dtor(list3);
    a_slist_foreach(it, list1)
    {
        a_data_s *node = a_slist_entry(it, a_data_s, list); // NOLINT(performance-no-int-to-ptr)
        printf("%i ", node->data.i);
    }
    printf("%" PRIzu, a_slist_len(list1));
    for (int i = 0; i != 10; ++i)
    {
        a_data_s *node = a_slist_entry_next(&list1->head, a_data_s, list); // NOLINT(performance-no-int-to-ptr)
        a_slist_del_head(list1);
        a_die(node);
    }
    a_slist_forsafe(it, at, list1)
    {
        a_data_s *node = a_slist_entry(it, a_data_s, list); // NOLINT(performance-no-int-to-ptr)
        a_slist_del(list1, at);
        a_die(node);
        it = A_NULL;
    }
    if (list1->head.next == &list1->head &&
        list2->head.next == &list2->head &&
        list3->head.next == &list3->head)
    {
        printf(" ok");
    }
    putchar('\n');
    a_die(list3);
    a_die(list2);
    a_die(list1);
}

static void null(void)
{
    a_slist_u node1 = A_SLIST_NODE(node1);
    a_slist_u node2 = A_SLIST_NODE(node2);
    a_slist_s list1 = A_SLIST_INIT(list1);
    a_slist_s list2 = A_SLIST_INIT(list2);

    a_slist_rot(&list1);
    a_slist_rot(&list1);
    a_slist_mov(&list1, &list1.head, &list2);
    a_slist_mov(&list1, list1.tail, &list2);
    a_slist_del(&list1, &list1.head);
    a_slist_del(&list1, list1.tail);
    a_slist_del_head(&list2);
    a_slist_del_head(&list2);

    a_slist_init(&list1);
    a_slist_init(&list2);
    a_slist_add(&list1, &list1.head, &node1);
    a_slist_add(&list1, &list1.head, &node1);
    a_slist_del(&list1, &node1);
    a_slist_add(&list1, list1.tail, &node1);
    a_slist_add(&list1, &node1, &node1);
    a_slist_add_head(&list1, &node1);
    a_slist_add_tail(&list2, &node2);
    a_slist_mov(&list1, &list1.head, &list2);
    a_slist_mov(&list1, list1.tail, &list2);
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", A_FUNC);
    test();
    null();
    return 0;
}

#endif /* test/slist.h */
