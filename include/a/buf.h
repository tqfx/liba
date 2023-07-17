/*!
 @file buf.h
 @brief basic buffer library
*/

#ifndef LIBA_BUF_H
#define LIBA_BUF_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_BUF basic buffer library
 @{
*/

/*!
 @brief instance structure for basic buffer
*/
typedef struct a_buf_s
{
    void *_ptr; /*!< address of memory */
    a_size_t _num; /*!< number of element */
    a_size_t _mem; /*!< memory of element */
    a_size_t _siz; /*!< size of a element */
} a_buf_s;

/*!
 @brief access address of buffer for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
*/
A_INTERN void *a_buf_ptr(a_buf_s const *const ctx) { return ctx->_ptr; }

/*!
 @brief access number of element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
*/
A_INTERN a_size_t a_buf_num(a_buf_s const *const ctx) { return ctx->_num; }

/*!
 @brief access memory of element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
*/
A_INTERN a_size_t a_buf_mem(a_buf_s const *const ctx) { return ctx->_mem; }

/*!
 @brief access size of a element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
*/
A_INTERN a_size_t a_buf_get(a_buf_s const *const ctx) { return ctx->_siz; }

/*!
 @brief access specified element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] idx index of element less than memory
 @note should check for out of bounds
 @return specified element pointer
*/
A_INTERN void *a_buf_at_(a_buf_s const *const ctx, a_size_t const idx)
{
    return a_byte_c(*, ctx->_ptr) + ctx->_siz * idx;
}

/*!
 @brief access specified element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] idx index of element less than memory
 @return specified element pointer
  @retval 0 out of bounds
*/
A_INTERN void *a_buf_at(a_buf_s const *const ctx, a_size_t const idx)
{
    return a_likely(idx < ctx->_mem) ? a_buf_at_(ctx, idx) : A_NULL;
}

/*!
 @brief access specified element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] idx index of element -memory < idx < memory
 @return specified element pointer
  @retval 0 out of bounds
*/
A_INTERN void *a_buf_idx(a_buf_s const *const ctx, a_diff_t const idx)
{
    a_size_t const num = idx < 0 ? a_size_c(, idx) + ctx->_num : a_size_c(, idx);
    return a_likely(num < ctx->_mem) ? a_buf_at_(ctx, num) : A_NULL;
}

/*!
 @brief access top element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @note should check if buffer is empty
 @return specified element pointer
*/
A_INTERN void *a_buf_top_(a_buf_s const *const ctx)
{
    return a_byte_c(*, ctx->_ptr) + ctx->_siz * (ctx->_num - 1);
}

/*!
 @brief access top element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @return specified element pointer
  @retval 0 empty buffer
*/
A_INTERN void *a_buf_top(a_buf_s const *const ctx)
{
    return a_likely(ctx->_num) ? a_buf_top_(ctx) : A_NULL;
}

/*!
 @brief access end pointer for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @return buffer end pointer
*/
A_INTERN void *a_buf_end(a_buf_s const *const ctx)
{
    return a_byte_c(*, ctx->_ptr) + ctx->_siz * ctx->_num;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief constructor for buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] ptr address of memory
 @param[in] siz size of a element
 @param[in] num number of element
*/
A_EXTERN void a_buf_ctor(a_buf_s *ctx, void *ptr, a_size_t siz, a_size_t num);

/*!
 @brief destructor for buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] dtor element destructor
*/
A_EXTERN void a_buf_dtor(a_buf_s *ctx, void (*dtor)(void *));

/*!
 @brief initialize a pointer to buffer structure by moving
 @param[in] ctx points to an instance of buffer structure
 @param[in] obj input source pointing to an instance
*/
A_EXTERN a_buf_s *a_buf_move(a_buf_s *ctx, a_buf_s *obj);

/*!
 @brief drop all the elements for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] dtor current element destructor
*/
A_EXTERN void a_buf_drop(a_buf_s *ctx, void (*dtor)(void *));

/*!
 @brief swap elements lhs and rhs for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] lhs element index on the left
 @param[in] rhs element index on the right
*/
A_EXTERN void a_buf_swap(a_buf_s const *ctx, a_size_t lhs, a_size_t rhs);

/*!
 @brief sort all elements for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_buf_sort(a_buf_s const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert sort foremost element for a pointer to buffer structure
 @code{.c}
 T *obj = a_buf_push_fore(T, ctx);
 if (obj)
 {
     CTOR(obj);
     INIT(obj);
     a_buf_sort_fore(ctx, cmp);
 }
 @endcode
 @param[in] ctx points to an instance of buffer structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_buf_sort_fore(a_buf_s const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert sort backmost element for a pointer to buffer structure
 @code{.c}
 T *obj = a_buf_push_back(T, ctx);
 if (obj)
 {
     CTOR(obj);
     INIT(obj);
     a_buf_sort_back(ctx, cmp);
 }
 @endcode
 @param[in] ctx points to an instance of buffer structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_buf_sort_back(a_buf_s const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief search the given element in this buffer
 @param[in] ctx points to an instance of buffer structure
 @param[in] obj object that serves as key for the search
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
 @return matching element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_search(a_buf_s const *ctx, void const *obj, int (*cmp)(void const *, void const *));

/*!
 @brief insert an element into the buffer
 @param[in] ctx points to an instance of buffer structure
 @param[in] idx index of element in this buffer
  @arg 0 a_buf_push_fore
  @arg n a_buf_push_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_insert(a_buf_s *ctx, a_size_t idx);

/*!
 @brief remove an element from the buffer
 @param[in] ctx points to an instance of buffer structure
 @param[in] idx index of element in this buffer
  @arg 0 a_buf_pull_fore
  @arg n a_buf_pull_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_remove(a_buf_s *ctx, a_size_t idx);

/*!
 @brief push an element into the buffer forward
 @param[in] ctx points to an instance of buffer structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_push_fore(a_buf_s *ctx);

/*!
 @brief push an element into the buffer backward
 @param[in] ctx points to an instance of buffer structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_push_back(a_buf_s *ctx);

/*!
 @brief pull an element from the buffer forward
 @param[in] ctx points to an instance of buffer structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_pull_fore(a_buf_s *ctx);

/*!
 @brief pull an element from the buffer backward
 @param[in] ctx points to an instance of buffer structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_pull_back(a_buf_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief push an element into the buffer
 @param[in] ctx points to an instance of buffer structure
 @return element pointer
  @retval 0 failure
*/
A_INTERN void *a_buf_push(a_buf_s *ctx) { return a_buf_push_back(ctx); }

/*!
 @brief pull an element from the buffer
 @param[in] ctx points to an instance of buffer structure
 @return element pointer
  @retval 0 failure
*/
A_INTERN void *a_buf_pull(a_buf_s *ctx) { return a_buf_pull_back(ctx); }

/*!
 @brief iterate over a buffer
 @code{.c}
 a_buf_forenum(i, ctx)
 {
     T *it = (T *)a_buf_at(ctx, i);
     assert(a_buf_get(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the buffer
 @param ctx points to an instance of buffer structure
*/
#define a_buf_forenum(i, ctx) a_forenum(a_size_t, i, (ctx)->_num)

/*!
 @brief iterate over a buffer in reverse
 @code{.c}
 a_buf_forenum_reverse(i, ctx)
 {
     T *it = (T *)a_buf_at(ctx, i);
     assert(a_buf_get(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the buffer
 @param ctx points to an instance of buffer structure
*/
#define a_buf_forenum_reverse(i, ctx) a_forenum_reverse(a_size_t, i, (ctx)->_num)

/*!
 @brief iterate over a buffer
 @code{.c}
 a_buf_foreach(T, it, ctx)
 {
     assert(a_buf_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the buffer
 @param it the &a_buf_s to use as a loop counter
 @param ctx points to an instance of buffer structure
*/
#define a_buf_foreach(T, it, ctx) a_foreach(T, it, (ctx)->_ptr, (ctx)->_num)

/*!
 @brief iterate over a buffer in reverse
 @code{.c}
 a_buf_foreach_reverse(T, it, ctx)
 {
     assert(a_buf_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the buffer
 @param it the &a_buf_s to use as a loop counter
 @param ctx points to an instance of buffer structure
*/
#define a_buf_foreach_reverse(T, it, ctx) a_foreach_reverse(T, it, (ctx)->_ptr, (ctx)->_num)

#define a_buf_ptr(T, ctx) a_cast_s(T *, a_buf_ptr(ctx))
#define a_buf_end(T, ctx) a_cast_s(T *, a_buf_end(ctx))
#define a_buf_top(T, ctx) a_cast_s(T *, a_buf_top(ctx))
#define a_buf_top_(T, ctx) a_cast_s(T *, a_buf_top_(ctx))
#define a_buf_at(T, ctx, idx) a_cast_s(T *, a_buf_at(ctx, idx))
#define a_buf_at_(T, ctx, idx) a_cast_s(T *, a_buf_at_(ctx, idx))
#define a_buf_idx(T, ctx, idx) a_cast_s(T *, a_buf_idx(ctx, idx))
#define a_buf_search(T, ctx, obj, cmp) a_cast_s(T *, a_buf_search(ctx, obj, cmp))
#define a_buf_insert(T, ctx, idx) a_cast_s(T *, a_buf_insert(ctx, idx))
#define a_buf_remove(T, ctx, idx) a_cast_s(T *, a_buf_remove(ctx, idx))
#define a_buf_push_fore(T, ctx) a_cast_s(T *, a_buf_push_fore(ctx))
#define a_buf_push_back(T, ctx) a_cast_s(T *, a_buf_push_back(ctx))
#define a_buf_pull_fore(T, ctx) a_cast_s(T *, a_buf_pull_fore(ctx))
#define a_buf_pull_back(T, ctx) a_cast_s(T *, a_buf_pull_back(ctx))
#define a_buf_push(T, ctx) a_cast_s(T *, a_buf_push(ctx))
#define a_buf_pull(T, ctx) a_cast_s(T *, a_buf_pull(ctx))

/*! @} A_BUF */

#endif /* a/buf.h */
