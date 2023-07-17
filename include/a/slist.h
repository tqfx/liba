/*!
 @file slist.h
 @brief circular singly linked list implementation
*/

#ifndef LIBA_SLIST_H
#define LIBA_SLIST_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_SLIST circular singly linked list
 @{
*/

// clang-format off
#define A_SLIST_NODE(node) {&(node)}
#define A_SLIST_INIT(list) {{&(list).head}, &(list).head}
// clang-format on

/*!
 @brief instance structure for circular singly linked list node
*/
typedef union a_slist_u
{
    union a_slist_u *next;
} a_slist_u;

/*!
 @brief cast a list pointer from another type pointer
 @param[in] obj points to circular singly linked list node
 @return a pointer to circular singly linked list node
*/
A_INTERN a_slist_u *a_slist_from(void *const obj) { return a_cast_s(a_slist_u *, obj); }

/*!
 @brief test whether a list node is null
 @param[in] ctx points to circular singly linked list node
 @return int bool
  @retval 0 non-null
  @retval 1 null
*/
A_INTERN a_bool_t a_slist_null(a_slist_u const *const ctx) { return ctx->next == ctx; }

/*!
 @brief test whether a list node is used
 @param[in] ctx points to circular singly linked list node
 @return int bool
  @retval 0 unused
  @retval 1 used
*/
A_INTERN a_bool_t a_slist_used(a_slist_u const *const ctx) { return ctx->next != ctx; }

/*!
 @brief initialize for circular singly linked list node
 @param[in,out] ctx points to circular singly linked list node
*/
A_INTERN void a_slist_node(a_slist_u *const ctx) { ctx->next = ctx; }

/*!
 @brief instance structure for circular singly linked list head
*/
typedef struct a_slist_s
{
    a_slist_u head;
    a_slist_u *tail;
} a_slist_s;

/*!
 @brief access the struct for this entry
 @param ptr the &a_slist_u pointer
 @param type the type of the struct this is embedded in
 @param member the name of the a_slist_u within the struct
*/
#define a_slist_entry(ptr, type, member) a_container_of(ptr, type, member)
#define a_slist_entry_next(ptr, type, member) a_slist_entry((ptr)->next, type, member)

/*!
 @brief iterate over a list
 @param it the &a_slist_u to use as a loop counter
 @param ctx points to circular singly linked list head
*/
#define a_slist_foreach(it, ctx) \
    for (a_slist_u *it = (ctx)->head.next; it != &(ctx)->head; it = it->next)

/*!
 @brief iterate over a list safe against removal of list entry
 @param it the &a_slist_u to use as a loop counter
 @param at another &a_slist_u to use as temporary storage
 @param ctx points to circular singly linked list head
*/
#define a_slist_forsafe(it, at, ctx)                                       \
    for (a_slist_u *at = &(ctx)->head, *it = at->next; it != &(ctx)->head; \
         at = (it && it == at->next) ? it : at, it = at->next)

/*!
 @brief test whether a list head is none
 @param[in] ctx points to circular singly linked list head
 @return int bool
  @retval 0 exist
  @retval 1 none
*/
A_INTERN a_bool_t a_slist_none(a_slist_s const *const ctx) { return &ctx->head == ctx->head.next; }

/*!
 @brief test whether a list node is a tail node
 @param[in] ctx points to circular singly linked list head
 @param[in] node a list node
 @return int bool
  @retval 0 it's not a tail node
  @retval 1 it is a tail node
*/
A_INTERN a_bool_t a_slist_tail(a_slist_s const *const ctx, a_slist_u const *const node) { return &ctx->head == node->next; }

/*!
 @brief constructor for circular singly linked list head
 @param[in,out] ctx points to circular singly linked list head
*/
A_INTERN void a_slist_ctor(a_slist_s *const ctx) { ctx->tail = ctx->head.next = &ctx->head; }

/*!
 @brief initialize for circular singly linked list head
 @param[in,out] ctx points to circular singly linked list head
*/
A_INTERN void a_slist_init(a_slist_s *const ctx) { ctx->tail = ctx->head.next = &ctx->head; }

/*!
 @brief destructor for circular singly linked list head
 @param[in,out] ctx points to circular singly linked list head
*/
A_INTERN void a_slist_dtor(a_slist_s *const ctx) { ctx->tail = ctx->head.next = &ctx->head; }

/*!
 @brief link head node and tail node
 @param[in,out] head the head node of a list
 @param[in,out] tail the tail node of a list
*/
A_INTERN void a_slist_link(a_slist_u *const head, a_slist_u *const tail) { head->next = tail; }

/*!
 @brief insert a node to a list
 @param[in,out] ctx points to circular singly linked list head
 @param[in] prev previous list node
 @param[in] node a list node
*/
A_INTERN void a_slist_add(a_slist_s *const ctx, a_slist_u *const prev, a_slist_u *const node)
{
    if (a_slist_tail(ctx, prev))
    {
        ctx->tail = node;
    }
    a_slist_link(node, prev->next);
    a_slist_link(prev, node);
}

/*!
 @brief insert a node to a list head
 @param[in,out] ctx points to circular singly linked list head
 @param[in] node a list node
*/
A_INTERN void a_slist_add_head(a_slist_s *const ctx, a_slist_u *const node)
{
    if (a_slist_none(ctx))
    {
        ctx->tail = node;
    }
    a_slist_link(node, ctx->head.next);
    a_slist_link(&ctx->head, node);
}

/*!
 @brief insert a node to a list tail
 @param[in,out] ctx points to circular singly linked list head
 @param[in] node a list node
*/
A_INTERN void a_slist_add_tail(a_slist_s *const ctx, a_slist_u *const node)
{
    a_slist_link(node, &ctx->head);
    a_slist_link(ctx->tail, node);
    ctx->tail = node;
}

/*!
 @brief delete a node from a list
 @param[in,out] ctx points to circular singly linked list head
 @param[in] prev previous list node
*/
A_INTERN void a_slist_del(a_slist_s *const ctx, a_slist_u *const prev)
{
    a_slist_u *const node = prev->next;
    a_slist_link(prev, node->next);
    if (a_slist_tail(ctx, node))
    {
        ctx->tail = prev;
    }
}

/*!
 @brief delete a node from a list head
 @param[in,out] ctx points to circular singly linked list head
*/
A_INTERN void a_slist_del_head(a_slist_s *const ctx)
{
    a_slist_u *const node = ctx->head.next;
    a_slist_link(&ctx->head, node->next);
    if (a_slist_tail(ctx, node))
    {
        ctx->tail = &ctx->head;
    }
}

/*!
 @brief moving a list to another list
 @param[in,out] ctx points to circular singly linked list head
 @param[in] at the previous &a_slist_u of the inserted node
 @param[in] src source list
*/
A_INTERN void a_slist_mov(a_slist_s *const ctx, a_slist_u *const at, a_slist_s *const src)
{
    if (a_slist_none(src))
    {
        return;
    }
    if (a_slist_tail(ctx, at))
    {
        ctx->tail = src->tail;
    }
    a_slist_link(src->tail, at->next);
    a_slist_link(at, src->head.next);
}

/*!
 @brief rotate a node in the list
 @param[in,out] ctx points to circular singly linked list head
*/
A_INTERN void a_slist_rot(a_slist_s *const ctx)
{
    a_slist_u *const node = ctx->head.next;
    a_slist_link(&ctx->head, node->next);
    a_slist_link(node, ctx->tail->next);
    a_slist_link(ctx->tail, node);
    ctx->tail = node;
}

/* inline function for generic */
A_INTERN void a_slist_ctor_(void *const ctx) { a_slist_ctor(a_cast_s(a_slist_s *, ctx)); }
A_INTERN void a_slist_dtor_(void *const ctx) { a_slist_dtor(a_cast_s(a_slist_s *, ctx)); }

/*! @} A_SLIST */

#endif /* a/slist.h */
