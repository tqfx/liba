/*!
 @file slist.h
 @brief singly linked list implementation
*/

#ifndef LIBA_SLIST_H
#define LIBA_SLIST_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_SLIST singly linked list
 @{
*/

// clang-format off
#define A_SLIST_NODE {A_NULL}
#define A_SLIST_INIT(list) {{A_NULL}, &(list).head}
// clang-format on

/*!
 @brief instance structure for singly linked list node
*/
typedef struct a_slist_node
{
    struct a_slist_node *next;
} a_slist_node;

/*!
 @brief cast a list pointer from another type pointer
 @param[in] _ additional attributes of specified type
 @param[in] x points to singly linked list node
 @return a pointer to singly linked list node
*/
#define a_slist_(_, x) a_cast_s(a_slist_node _, a_cast_s(void _, x))

/*!
 @brief instance structure for singly linked list head
*/
typedef struct a_slist
{
    a_slist_node head;
    a_slist_node *tail;
} a_slist;

/*!
 @brief access the struct for this entry
 @param ptr the &a_slist_node pointer
 @param type the type of the struct this is embedded in
 @param member the name of the a_slist_node within the struct
*/
#define a_slist_entry(ptr, type, member) a_container_of(ptr, type, member)
#define a_slist_entry_next(ptr, type, member) a_slist_entry((ptr)->next, type, member)

/*!
 @brief iterate over a list
 @param it the &a_slist_node to use as a loop counter
 @param ctx points to singly linked list head
*/
#define a_slist_foreach(it, ctx) \
    for (a_slist_node *it = (ctx)->head.next; it; it = it->next)

/*!
 @brief iterate over a list safe against removal of list entry
 @param it the &a_slist_node to use as a loop counter
 @param at another &a_slist_node to use as temporary storage
 @param ctx points to singly linked list head
*/
#define a_slist_forsafe(it, at, ctx)                      \
    for (a_slist_node *at = &(ctx)->head, *it = at->next; \
         it; at = it ? it : at, it = at->next)

/*!
 @brief constructor for singly linked list head
 @param[in,out] ctx points to singly linked list head
*/
A_INTERN void a_slist_ctor(a_slist *ctx)
{
    ctx->head.next = A_NULL;
    ctx->tail = &ctx->head;
}

/*!
 @brief initialize for singly linked list head
 @param[in,out] ctx points to singly linked list head
*/
A_INTERN void a_slist_init(a_slist *ctx)
{
    ctx->head.next = A_NULL;
    ctx->tail = &ctx->head;
}

/*!
 @brief destructor for singly linked list head
 @param[in,out] ctx points to singly linked list head
*/
A_INTERN void a_slist_dtor(a_slist *ctx)
{
    ctx->head.next = A_NULL;
    ctx->tail = &ctx->head;
}

/*!
 @brief link head node and tail node
 @param[in,out] head the head node of a list
 @param[in,out] tail the tail node of a list
*/
A_INTERN void a_slist_link(a_slist_node *head, a_slist_node *tail) { head->next = tail; }

/*!
 @brief insert a node to a list
 @param[in,out] ctx points to singly linked list head
 @param[in] prev previous singly linked list node
 @param[in] node a singly linked list node
*/
A_INTERN void a_slist_add(a_slist *ctx, a_slist_node *prev, a_slist_node *node)
{
    if (!prev->next) { ctx->tail = node; }
    a_slist_link(node, prev->next);
    a_slist_link(prev, node);
}

/*!
 @brief insert a node to a list head
 @param[in,out] ctx points to singly linked list head
 @param[in] node a singly linked list node
*/
A_INTERN void a_slist_add_head(a_slist *ctx, a_slist_node *node)
{
    a_slist_add(ctx, &ctx->head, node);
}

/*!
 @brief insert a node to a list tail
 @param[in,out] ctx points to singly linked list head
 @param[in] node a singly linked list node
*/
A_INTERN void a_slist_add_tail(a_slist *ctx, a_slist_node *node)
{
    a_slist_link(ctx->tail, node);
    node->next = A_NULL;
    ctx->tail = node;
}

/*!
 @brief delete a node from a list
 @param[in,out] ctx points to singly linked list head
 @param[in] prev previous singly linked list node
*/
A_INTERN void a_slist_del(a_slist *ctx, a_slist_node *prev)
{
    a_slist_node *const node = prev->next;
    if (node)
    {
        a_slist_link(prev, node->next);
        if (!node->next) { ctx->tail = prev; }
    }
}

/*!
 @brief delete a node from a list head
 @param[in,out] ctx points to singly linked list head
*/
A_INTERN void a_slist_del_head(a_slist *ctx)
{
    a_slist_node *const node = ctx->head.next;
    if (node)
    {
        a_slist_link(&ctx->head, node->next);
        if (!node->next) { ctx->tail = &ctx->head; }
    }
}

/*!
 @brief moving a list to another list
 @param[in] ctx points to singly linked list head
 @param[in,out] to another linked list to be inserted
 @param[in] at the previous &a_slist_node of the inserted node
*/
A_INTERN void a_slist_mov(a_slist *ctx, a_slist *to, a_slist_node *at)
{
    a_slist_node *const node = ctx->head.next;
    if (node)
    {
        if (!at->next) { to->tail = ctx->tail; }
        a_slist_link(ctx->tail, at->next);
        a_slist_link(at, node);
    }
}

/*!
 @brief rotate a node in the list
 @param[in,out] ctx points to singly linked list head
*/
A_INTERN void a_slist_rot(a_slist *ctx)
{
    a_slist_node *const node = ctx->head.next;
    if (node)
    {
        a_slist_link(&ctx->head, node->next);
        a_slist_link(ctx->tail, node);
        node->next = A_NULL;
        ctx->tail = node;
    }
}

/*! @} A_SLIST */

#endif /* a/slist.h */
