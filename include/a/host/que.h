/*!
 @file que.h
 @brief basic queue library
*/

#ifndef LIBA_HOST_QUE_H
#define LIBA_HOST_QUE_H

#include "a.h"
#include "../list.h"

/*!
 @ingroup A
 @addtogroup A_QUE basic queue library
 @{
*/

/*!
 @brief instance structure for basic queue node
*/
typedef struct a_que_node_s
{
    a_list_s _node; /*!< element node */
    void *_data; /*!< element data */
} a_que_node_s;

/*!
 @brief cast a list pointer from another type pointer
 @param[in] obj points to basic queue node
 @return a pointer to basic queue node
*/
A_INTERN a_que_node_s *a_que_from(void *const obj) { return a_cast_s(a_que_node_s *, obj); }

/*!
 @brief instance structure for basic queue
*/
typedef struct a_que_s
{
    a_que_node_s **_ptr; /*!< mempool block */
    a_list_s _head; /*!< element head */
    a_size_t _size; /*!< element sizeof */
    a_size_t _num; /*!< element number */
    a_size_t _cur; /*!< mempool cursor */
    a_size_t _mem; /*!< mempool memory */
} a_que_s;

/*!
 @brief access size of a element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
*/
A_INTERN a_size_t a_que_get(a_que_s const *const ctx) { return ctx->_size; }

/*!
 @brief access number of element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
*/
A_INTERN a_size_t a_que_num(a_que_s const *const ctx) { return ctx->_num; }

/*!
 @brief access foremost element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @note should check if queue is empty
 @return element pointer
*/
A_INTERN void *a_que_fore_(a_que_s const *const ctx)
{
    return a_que_from(ctx->_head.next)->_data;
}

/*!
 @brief access backmost element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @note should check if queue is empty
 @return element pointer
*/
A_INTERN void *a_que_back_(a_que_s const *const ctx)
{
    return a_que_from(ctx->_head.prev)->_data;
}

/*!
 @brief access foremost element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 empty queue
*/
A_INTERN void *a_que_fore(a_que_s const *const ctx)
{
    return a_likely(a_list_used(&ctx->_head)) ? a_que_fore_(ctx) : A_NULL;
}

/*!
 @brief access backmost element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 empty queue
*/
A_INTERN void *a_que_back(a_que_s const *const ctx)
{
    return a_likely(a_list_used(&ctx->_head)) ? a_que_back_(ctx) : A_NULL;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to queue structure from memory
 @param[in] size size of element
*/
A_EXTERN a_que_s *a_que_new(a_size_t size);

/*!
 @brief deallocate a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] dtor element destructor
*/
A_EXTERN void a_que_die(a_que_s *ctx, void (*dtor)(void *));

/*!
 @brief constructor for queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] size size of element
*/
A_EXTERN void a_que_ctor(a_que_s *ctx, a_size_t size);

/*!
 @brief destructor for queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] dtor element destructor
*/
A_EXTERN void a_que_dtor(a_que_s *ctx, void (*dtor)(void *));

/*!
 @brief initialize a pointer to queue structure by moving
 @param[in] ctx points to an instance of queue structure
 @param[in] obj input source pointing to an instance
*/
A_EXTERN a_que_s *a_que_move(a_que_s *ctx, a_que_s *obj);

/*!
 @brief access specified element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] idx index of element, 0 ~ n-1, -n ~ -1
 @return element pointer
  @retval 0 out of bounds
*/
A_EXTERN void *a_que_at(a_que_s const *ctx, a_imax_t idx);

/*!
 @brief modify size of a element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] size the size of the new element
 @param[in] dtor previous element destructor
*/
A_EXTERN void a_que_set(a_que_s *ctx, a_size_t size, void (*dtor)(void *));

/*!
 @brief drop all the elements for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] dtor current element destructor
*/
A_EXTERN void a_que_drop(a_que_s *ctx, void (*dtor)(void *));

/*!
 @brief swap elements lhs and rhs for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] lhs element pointer on the left
 @param[in] rhs element pointer on the right
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_que_swap_(a_que_s const *ctx, void *lhs, void *rhs);

/*!
 @brief swap elements lhs and rhs for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] lhs element index on the left
 @param[in] rhs element index on the right
*/
A_EXTERN void a_que_swap(a_que_s const *ctx, a_size_t lhs, a_size_t rhs);

/*!
 @brief insert sort foremost element for a pointer to queue structure
 @code{.c}
 T *obj = a_que_push_fore(T, ctx);
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
A_EXTERN void a_que_sort_fore(a_que_s const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert sort backmost element for a pointer to queue structure
 @code{.c}
 T *obj = a_que_push_back(T, ctx);
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
A_EXTERN void a_que_sort_back(a_que_s const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief push an element into the queue forward
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_push_fore(a_que_s *ctx);

/*!
 @brief push an element into the queue backward
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_push_back(a_que_s *ctx);

/*!
 @brief pull an element from the queue forward
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_pull_fore(a_que_s *ctx);

/*!
 @brief pull an element from the queue backward
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_pull_back(a_que_s *ctx);

/*!
 @brief insert an element into the queue
 @param[in] ctx points to an instance of queue structure
 @param[in] idx index of element in this queue
  @arg 0 a_que_push_fore
  @arg n a_que_push_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_insert(a_que_s *ctx, a_size_t idx);

/*!
 @brief remove an element from the queue
 @param[in] ctx points to an instance of queue structure
 @param[in] idx index of element in this queue
  @arg 0 a_que_pull_fore
  @arg n a_que_pull_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_que_remove(a_que_s *ctx, a_size_t idx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief iterate over a queue
 @code{.c}
 a_que_foreach(T, it, ctx)
 {
     assert(a_que_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the queue
 @param it the &a_que_s to use as a loop counter
 @param ctx points to an instance of queue structure
*/
#define a_que_foreach(T, it, ctx)                                     \
    for (T *it = a_cast_r(T *, (ctx)->_head.next),                    \
           *it##_ = a_cast_r(T *, a_list_from(it)->next);             \
         a_list_from(it) != &(ctx)->_head                             \
             ? ((void)(it = a_cast_s(T *, a_que_from(it)->_data)), 1) \
             : (0);                                                   \
         it = it##_, it##_ = a_cast_r(T *, a_list_from(it)->next))

/*!
 @brief iterate over a queue in reverse
 @code{.c}
 a_que_foreach_reverse(T, it, ctx)
 {
     assert(a_que_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the queue
 @param it the &a_que_s to use as a loop counter
 @param ctx points to an instance of queue structure
*/
#define a_que_foreach_reverse(T, it, ctx)                             \
    for (T *it = a_cast_r(T *, (ctx)->_head.prev),                    \
           *it##_ = a_cast_r(T *, a_list_from(it)->prev);             \
         a_list_from(it) != &(ctx)->_head                             \
             ? ((void)(it = a_cast_s(T *, a_que_from(it)->_data)), 1) \
             : (0);                                                   \
         it = it##_, it##_ = a_cast_r(T *, a_list_from(it)->prev))

#define a_que_fore(T, ctx) a_cast_s(T *, a_que_fore(ctx))
#define a_que_back(T, ctx) a_cast_s(T *, a_que_back(ctx))
#define a_que_fore_(T, ctx) a_cast_s(T *, a_que_fore_(ctx))
#define a_que_back_(T, ctx) a_cast_s(T *, a_que_back_(ctx))
#define a_que_at(T, ctx, idx) a_cast_s(T *, a_que_at(ctx, idx))
#define a_que_push_fore(T, ctx) a_cast_s(T *, a_que_push_fore(ctx))
#define a_que_push_back(T, ctx) a_cast_s(T *, a_que_push_back(ctx))
#define a_que_pull_fore(T, ctx) a_cast_s(T *, a_que_pull_fore(ctx))
#define a_que_pull_back(T, ctx) a_cast_s(T *, a_que_pull_back(ctx))
#define a_que_insert(T, ctx, idx) a_cast_s(T *, a_que_insert(ctx, idx))
#define a_que_remove(T, ctx, idx) a_cast_s(T *, a_que_remove(ctx, idx))

/*! @} A_QUE */

#endif /* host/que.h */
