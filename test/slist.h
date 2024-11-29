#define MAIN(x) slist##x
#include "test.h"
#include "a/slist.h"

static a_size a_slist_len(a_slist const *ctx)
{
    a_size count = 0;
    a_slist_node *it;
    A_SLIST_FOREACH(it, ctx) { ++count; }
    return count;
}

static void test(void)
{
    typedef struct
    {
        a_slist_node node;
        a_cast data;
    } data;
    int i;
    a_slist_node *it, *at;
    a_slist *list1, *list2, *list3;
    list1 = a_new(a_slist, A_NULL, 1);
    a_slist_ctor(list1);
    for (i = 0; i != 10; ++i)
    {
        data *node = a_new(data, A_NULL, 1);
        node->data.i = i;
        a_slist_add_tail(list1, &node->node);
    }
    list2 = a_new(a_slist, A_NULL, 1);
    a_slist_ctor(list2);
    for (i = 14; i != 9; --i)
    {
        data *node = a_new(data, A_NULL, 1);
        node->data.i = i;
        a_slist_add_head(list2, &node->node);
    }
    list3 = a_new(a_slist, A_NULL, 1);
    a_slist_ctor(list3);
    for (i = 15; i != 20; ++i)
    {
        data *node = a_new(data, A_NULL, 1);
        node->data.i = i;
        a_slist_add(list3, list3->tail, &node->node);
    }
    a_slist_rot(list1);
    a_slist_mov(list2, list3, &list3->head);
    a_slist_dtor(list2);
    a_slist_mov(list3, list1, list1->tail);
    a_slist_dtor(list3);
    A_SLIST_FOREACH(it, list1)
    {
        data *node = a_slist_entry(it, data, node); /* NOLINT(performance-no-int-to-ptr) */
        printf("%i ", node->data.i);
    }
    printf("%" A_PRIz "u", a_slist_len(list1));
    for (i = 0; i != 10; ++i)
    {
        data *node = a_slist_entry_next(&list1->head, data, node); /* NOLINT(performance-no-int-to-ptr) */
        a_slist_del_head(list1);
        a_die(node);
    }
    A_SLIST_FORSAFE(it, at, list1)
    {
        data *node = a_slist_entry(it, data, node); /* NOLINT(performance-no-int-to-ptr) */
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
    (void)putchar('\n');
    a_die(list3);
    a_die(list2);
    a_die(list1);
}

static void null(void)
{
    static a_slist_node node1 = A_SLIST_NODE;
    static a_slist_node node2 = A_SLIST_NODE;
    static a_slist list1 = A_SLIST_INIT(list1);
    static a_slist list2 = A_SLIST_INIT(list2);

    a_slist_rot(&list1);
    a_slist_rot(&list1);
    a_slist_mov(&list2, &list1, &list1.head);
    a_slist_mov(&list2, &list1, list1.tail);
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
    a_slist_mov(&list2, &list1, &list1.head);
    a_slist_mov(&list2, &list1, list1.tail);
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    puts(A_FUNC);
    test();
    null();
    (void)argc;
    (void)argv;
    return 0;
}
