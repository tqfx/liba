/*!
 @file que.h
 @brief basic queue library
*/

#ifndef LIBA_QUE_H
#define LIBA_QUE_H

#include "list.h"

/*!
 @ingroup liba
 @addtogroup a_que basic queue library
 @{
*/

/*!
 @brief instance structure for basic queue
*/
typedef struct a_que
{
    a_list head_; /*!< element head */
    a_list **ptr_; /*!< mempool block */
    a_size siz_; /*!< element sizeof */
    a_size num_; /*!< element number */
    a_size cur_; /*!< mempool cursor */
    a_size mem_; /*!< mempool memory */
} a_que;

/*!
 @brief access size of a element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
*/
A_INTERN a_size a_que_siz(a_que const *ctx) { return ctx->siz_; }

/*!
 @brief access number of element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
*/
A_INTERN a_size a_que_num(a_que const *ctx) { return ctx->num_; }

/*!
 @brief access foremost element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @note should check if queue is empty
 @return element pointer
*/
A_INTERN void *a_que_fore_(a_que const *ctx)
{
    return a_cast_s(void *, ctx->head_.next + 1);
}
#define A_QUE_FORE_(T, ctx) a_cast_s(T *, a_que_fore_(ctx))

/*!
 @brief access backmost element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @note should check if queue is empty
 @return element pointer
*/
A_INTERN void *a_que_back_(a_que const *ctx)
{
    return a_cast_s(void *, ctx->head_.prev + 1);
}
#define A_QUE_BACK_(T, ctx) a_cast_s(T *, a_que_back_(ctx))

/*!
 @brief access foremost element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 empty queue
*/
A_INTERN void *a_que_fore(a_que const *ctx)
{
    return ctx->head_.next != &ctx->head_ ? a_que_fore_(ctx) : A_NULL;
}
#define A_QUE_FORE(T, ctx) a_cast_s(T *, a_que_fore(ctx))

/*!
 @brief access backmost element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 empty queue
*/
A_INTERN void *a_que_back(a_que const *ctx)
{
    return ctx->head_.prev != &ctx->head_ ? a_que_back_(ctx) : A_NULL;
}
#define A_QUE_BACK(T, ctx) a_cast_s(T *, a_que_back(ctx))

/*!
 @brief swap elements lhs and rhs for a pointer to queue structure
 @param[in] lhs element pointer on the left
 @param[in] rhs element pointer on the right
*/
A_INTERN void a_que_swap_(void *lhs, void *rhs)
{
    a_list_swap_node(a_cast_s(a_list *, lhs) - 1, a_cast_s(a_list *, rhs) - 1);
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to queue structure from memory
 @param[in] size size of element
*/
A_EXTERN a_que *a_que_new(a_size size);

/*!
 @brief deallocate a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] dtor element destructor
*/
A_EXTERN void a_que_die(a_que *ctx, void (*dtor)(void *));

/*!
 @brief constructor for queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] size size of element
*/
A_EXTERN void a_que_ctor(a_que *ctx, a_size size);

/*!
 @brief destructor for queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] dtor element destructor
*/
A_EXTERN void a_que_dtor(a_que *ctx, void (*dtor)(void *));

/*!
 @brief initialize a pointer to queue structure by moving
 @param[in] lhs points to an instance of queue structure
 @param[in] rhs points to an instance of queue structure
*/
A_EXTERN void a_que_swap(a_que *lhs, a_que *rhs);

/*!
 @brief drop all the elements for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] dtor current element destructor
 @return error code value
  @retval 0 success
*/
A_EXTERN int a_que_drop(a_que *ctx, void (*dtor)(void *));

/*!
 @brief set size of a element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] siz the size of the new element
 @param[in] dtor previous element destructor
 @return error code value
  @retval 0 success
*/
A_EXTERN int a_que_setz(a_que *ctx, a_size siz, void (*dtor)(void *));

/*!
 @brief access specified element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] idx index of element, 0 ~ n-1, -n ~ -1
 @return element pointer
  @retval 0 out of bounds
*/
A_EXTERN void *a_que_at(a_que const *ctx, a_diff idx);
#define A_QUE_AT(T, ctx, idx) a_cast_s(T *, a_que_at(ctx, idx))

/*!
 @brief insert sort foremost element for a pointer to queue structure
 @code{.c}
 T *obj = A_QUE_PUSH_FORE(T, ctx);
 if (obj)
 {
     CTOR(obj);
     INIT(obj);
     a_que_sort_fore(ctx, cmp);
 }
 @endcode
 @param[in] ctx points to an instance of queue structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_que_sort_fore(a_que const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert sort backmost element for a pointer to queue structure
 @code{.c}
 T *obj = A_QUE_PUSH_BACK(T, ctx);
 if (obj)
 {
     CTOR(obj);
     INIT(obj);
     a_que_sort_back(ctx, cmp);
 }
 @endcode
 @param[in] ctx points to an instance of queue structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_que_sort_back(a_que const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief push an element into the queue and sort it
 @param[in] ctx points to an instance of queue structure
 @param[in] key the key on the right for insertion sort
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_push_sort(a_que *ctx, void const *key, int (*cmp)(void const *, void const *));
#define A_QUE_PUSH_SORT(T, ctx, key, cmp) a_cast_s(T *, a_que_push_sort(ctx, key, cmp))

/*!
 @brief push an element into the queue forward
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_push_fore(a_que *ctx);
#define A_QUE_PUSH_FORE(T, ctx) a_cast_s(T *, a_que_push_fore(ctx))

/*!
 @brief push an element into the queue backward
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_push_back(a_que *ctx);
#define A_QUE_PUSH_BACK(T, ctx) a_cast_s(T *, a_que_push_back(ctx))

/*!
 @brief pull an element from the queue forward
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_pull_fore(a_que *ctx);
#define A_QUE_PULL_FORE(T, ctx) a_cast_s(T *, a_que_pull_fore(ctx))

/*!
 @brief pull an element from the queue backward
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_pull_back(a_que *ctx);
#define A_QUE_PULL_BACK(T, ctx) a_cast_s(T *, a_que_pull_back(ctx))

/*!
 @brief insert an element into the queue
 @param[in] ctx points to an instance of queue structure
 @param[in] idx index of element in this queue
  @arg 0 a_que_push_fore
  @arg n a_que_push_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_insert(a_que *ctx, a_size idx);
#define A_QUE_INSERT(T, ctx, idx) a_cast_s(T *, a_que_insert(ctx, idx))

/*!
 @brief remove an element from the queue
 @param[in] ctx points to an instance of queue structure
 @param[in] idx index of element in this queue
  @arg 0 a_que_pull_fore
  @arg n a_que_pull_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_remove(a_que *ctx, a_size idx);
#define A_QUE_REMOVE(T, ctx, idx) a_cast_s(T *, a_que_remove(ctx, idx))

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief iterate over a queue
 @code{.c}
 a_que_foreach(T, *, it, ctx)
 {
     assert(a_que_siz(ctx) >= sizeof(*it));
 }
 @endcode
 @param T the prefix of the element type
 @param S the suffix of the element type
 @param it the &a_que to use as a loop counter
 @param ctx points to an instance of queue structure
*/
#define a_que_foreach(T, S, it, ctx)                               \
    for (T S it = a_cast_r(T S, (ctx)->head_.next),                \
             S it##_ = a_cast_r(T S, a_list_(*, it)->next);        \
         a_list_(*, it) != &(ctx)->head_                           \
             ? ((void)(it = a_cast_r(T S, a_list_(*, it) + 1)), 1) \
             : (0);                                                \
         it = it##_, it##_ = a_cast_r(T S, a_list_(*, it)->next))
#define A_QUE_FOREACH(T, it, at, ctx)                            \
    for ((void)(it = a_cast_r(T, (ctx)->head_.next)),            \
         at = a_cast_r(T, a_list_(*, it)->next);                 \
         a_list_(*, it) != &(ctx)->head_                         \
             ? ((void)(it = a_cast_r(T, a_list_(*, it) + 1)), 1) \
             : (0);                                              \
         it = at, at = a_cast_r(T, a_list_(*, it)->next))

/*!
 @brief iterate over a queue in reverse
 @code{.c}
 a_que_foreach_reverse(T, *, it, ctx)
 {
     assert(a_que_siz(ctx) >= sizeof(*it));
 }
 @endcode
 @param T the prefix of the element type
 @param S the suffix of the element type
 @param it the &a_que to use as a loop counter
 @param ctx points to an instance of queue structure
*/
#define a_que_foreach_reverse(T, S, it, ctx)                       \
    for (T S it = a_cast_r(T S, (ctx)->head_.prev),                \
             S it##_ = a_cast_r(T S, a_list_(*, it)->prev);        \
         a_list_(*, it) != &(ctx)->head_                           \
             ? ((void)(it = a_cast_r(T S, a_list_(*, it) + 1)), 1) \
             : (0);                                                \
         it = it##_, it##_ = a_cast_r(T S, a_list_(*, it)->prev))
#define A_QUE_FOREACH_REVERSE(T, it, at, ctx)                    \
    for ((void)(it = a_cast_r(T, (ctx)->head_.prev)),            \
         at = a_cast_r(T, a_list_(*, it)->prev);                 \
         a_list_(*, it) != &(ctx)->head_                         \
             ? ((void)(it = a_cast_r(T, a_list_(*, it) + 1)), 1) \
             : (0);                                              \
         it = at, at = a_cast_r(T, a_list_(*, it)->prev))

/*! @} a_que */

#endif /* a/que.h */
