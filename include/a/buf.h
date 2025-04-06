/*!
 @file buf.h
 @brief basic buffer library
*/

#ifndef LIBA_BUF_H
#define LIBA_BUF_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_buf basic buffer library
 @{
*/

#define A_BUF_DEF a_size num_, mem_, siz_
/*!
 @brief instance structure for basic buffer
*/
typedef struct a_buf
{
    A_BUF_DEF;
} a_buf;

/*!
 @brief cast a buffer pointer from another type pointer
 @param[in] _ additional attributes of specified type
 @param[in] x points to basic buffer
 @return a pointer to basic buffer
*/
#define a_buf_(_, x) a_cast_s(a_buf _, a_cast_s(void _, x))

/*!
 @brief access number of element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
*/
A_INTERN a_size a_buf_num(void const *ctx) { return a_buf_(const *, ctx)->num_; }

/*!
 @brief access memory of element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
*/
A_INTERN a_size a_buf_mem(void const *ctx) { return a_buf_(const *, ctx)->mem_; }

/*!
 @brief access size of a element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
*/
A_INTERN a_size a_buf_siz(void const *ctx) { return a_buf_(const *, ctx)->siz_; }

/*!
 @brief access address of buffer for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
*/
A_INTERN void *a_buf_ptr(void const *ctx)
{
    return a_cast_r(a_buf *, a_cast_r(a_uptr, ctx)) + 1;
}
#define A_BUF_PTR(T, ctx) a_cast_s(T *, a_buf_ptr(ctx))

/*!
 @brief access specified element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] idx index of element less than memory
 @note should check for out of bounds
 @return specified element pointer
*/
A_INTERN void *a_buf_at_(void const *ctx, a_size idx)
{
    return a_byte_(*, a_buf_ptr(ctx)) + a_buf_siz(ctx) * idx;
}
#define A_BUF_AT_(T, ctx, idx) a_cast_s(T *, a_buf_at_(ctx, idx))

/*!
 @brief access specified element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] idx index of element less than memory
 @return specified element pointer
  @retval 0 out of bounds
*/
A_INTERN void *a_buf_at(void const *ctx, a_size idx)
{
    return idx < a_buf_mem(ctx) ? a_buf_at_(ctx, idx) : A_NULL;
}
#define A_BUF_AT(T, ctx, idx) a_cast_s(T *, a_buf_at(ctx, idx))

/*!
 @brief access specified element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] idx index of element -memory < idx < memory
 @return specified element pointer
  @retval 0 out of bounds
*/
A_INTERN void *a_buf_of(void const *ctx, a_diff idx)
{
    a_size const num = idx >= 0 ? a_size_c(idx) : a_size_c(idx) + a_buf_num(ctx);
    return num < a_buf_mem(ctx) ? a_buf_at_(ctx, num) : A_NULL;
}
#define A_BUF_OF(T, ctx, idx) a_cast_s(T *, a_buf_of(ctx, idx))

/*!
 @brief access top element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @note should check if buffer is empty
 @return specified element pointer
*/
A_INTERN void *a_buf_top_(void const *ctx)
{
    return a_byte_(*, a_buf_ptr(ctx)) + a_buf_siz(ctx) * (a_buf_num(ctx) - 1);
}
#define A_BUF_TOP_(T, ctx) a_cast_s(T *, a_buf_top_(ctx))

/*!
 @brief access top element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @return specified element pointer
  @retval 0 empty buffer
*/
A_INTERN void *a_buf_top(void const *ctx)
{
    return a_buf_num(ctx) ? a_buf_top_(ctx) : A_NULL;
}
#define A_BUF_TOP(T, ctx) a_cast_s(T *, a_buf_top(ctx))

/*!
 @brief access end pointer for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @return buffer end pointer
*/
A_INTERN void *a_buf_end(void const *ctx)
{
    return a_byte_(*, a_buf_ptr(ctx)) + a_buf_siz(ctx) * a_buf_num(ctx);
}
#define A_BUF_END(T, ctx) a_cast_s(T *, a_buf_end(ctx))

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to buffer structure from memory
 @param[in] siz size of a element
 @param[in] num number of element
*/
A_EXTERN a_buf *a_buf_new(a_size siz, a_size num);

/*!
 @brief deallocate a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] dtor element destructor
*/
A_EXTERN void a_buf_die(a_buf *ctx, void (*dtor)(void *));

/*!
 @brief constructor for buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] siz size of a element
 @param[in] num number of element
*/
A_EXTERN void a_buf_ctor(void *ctx, a_size siz, a_size num);

/*!
 @brief destructor for buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] dtor element destructor
*/
A_EXTERN void a_buf_dtor(void *ctx, void (*dtor)(void *));

/*!
 @brief set memory of element for a pointer to buffer structure
 @param[in] ctx points to an instance of string structure
 @param[in] mem new memory of current element
 @return error code value
  @retval 0 success
*/
A_EXTERN a_buf *a_buf_setm(a_buf *ctx, a_size mem);

/*!
 @brief set number of element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] num new number of current element
 @param[in] dtor current element destructor
*/
A_EXTERN void a_buf_setn(void *ctx, a_size num, void (*dtor)(void *));

/*!
 @brief set size of a element for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] siz the size of the new element
 @param[in] dtor previous element destructor
*/
A_EXTERN void a_buf_setz(void *ctx, a_size siz, void (*dtor)(void *));

/*!
 @brief sort all elements for a pointer to buffer structure
 @param[in] ctx points to an instance of buffer structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_buf_sort(void const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert sort foremost element for a pointer to buffer structure
 @code{.c}
 T *obj = A_BUF_PUSH_FORE(T, ctx);
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
A_EXTERN void a_buf_sort_fore(void const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert sort backmost element for a pointer to buffer structure
 @code{.c}
 T *obj = A_BUF_PUSH_BACK(T, ctx);
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
A_EXTERN void a_buf_sort_back(void const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief push an element into the buffer and sort it
 @param[in] ctx points to an instance of buffer structure
 @param[in] key the key on the right for insertion sort
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_push_sort(void *ctx, void const *key, int (*cmp)(void const *, void const *));
#define A_BUF_PUSH_SORT(T, ctx, key, cmp) a_cast_s(T *, a_buf_push_sort(ctx, key, cmp))

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
A_EXTERN void *a_buf_search(void const *ctx, void const *obj, int (*cmp)(void const *, void const *));
#define A_BUF_SEARCH(T, ctx, obj, cmp) a_cast_s(T *, a_buf_search(ctx, obj, cmp))

/*!
 @brief insert an element into the buffer
 @param[in] ctx points to an instance of buffer structure
 @param[in] idx index of element in this buffer
  @arg 0 a_buf_push_fore
  @arg n a_buf_push_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_insert(void *ctx, a_size idx);
#define A_BUF_INSERT(T, ctx, idx) a_cast_s(T *, a_buf_insert(ctx, idx))

/*!
 @brief remove an element from the buffer
 @param[in] ctx points to an instance of buffer structure
 @param[in] idx index of element in this buffer
  @arg 0 a_buf_pull_fore
  @arg n a_buf_pull_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_remove(void *ctx, a_size idx);
#define A_BUF_REMOVE(T, ctx, idx) a_cast_s(T *, a_buf_remove(ctx, idx))

/*!
 @brief push an element into the buffer forward
 @param[in] ctx points to an instance of buffer structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_push_fore(void *ctx);
#define A_BUF_PUSH_FORE(T, ctx) a_cast_s(T *, a_buf_push_fore(ctx))

/*!
 @brief push an element into the buffer backward
 @param[in] ctx points to an instance of buffer structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_push_back(void *ctx);
#define A_BUF_PUSH_BACK(T, ctx) a_cast_s(T *, a_buf_push_back(ctx))

/*!
 @brief pull an element from the buffer forward
 @param[in] ctx points to an instance of buffer structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_pull_fore(void *ctx);
#define A_BUF_PULL_FORE(T, ctx) a_cast_s(T *, a_buf_pull_fore(ctx))

/*!
 @brief pull an element from the buffer backward
 @param[in] ctx points to an instance of buffer structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_buf_pull_back(void *ctx);
#define A_BUF_PULL_BACK(T, ctx) a_cast_s(T *, a_buf_pull_back(ctx))

/*!
 @brief store elements into the buffer
 @param[in] ctx points to an instance of buffer structure
 @param[in] idx index of element in this buffer
 @param[in] ptr points to array elements
 @param[in] num number of array elements
 @param[in] copy a function that copies elements
  @arg 0 use function a_copy to copy elements
 @return error code value
  @retval 0 success
*/
A_EXTERN int a_buf_store(void *ctx, a_size idx, void *ptr, a_size num, int (*copy)(void *, void const *));

/*!
 @brief erase elements from the buffer
 @param[in] ctx points to an instance of buffer structure
 @param[in] idx index of element in this buffer
 @param[in] num number of elements to erase
 @param[in] dtor a function that erases elements
  @arg 0 not erase these elements
 @return error code value
  @retval 0 success
*/
A_EXTERN int a_buf_erase(void *ctx, a_size idx, a_size num, void (*dtor)(void *));

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief push an element into the buffer
 @param[in] ctx points to an instance of buffer structure
 @return element pointer
  @retval 0 failure
*/
A_INTERN void *a_buf_push(void *ctx) { return a_buf_push_back(ctx); }
#define A_BUF_PUSH(T, ctx) a_cast_s(T *, a_buf_push(ctx))

/*!
 @brief pull an element from the buffer
 @param[in] ctx points to an instance of buffer structure
 @return element pointer
  @retval 0 failure
*/
A_INTERN void *a_buf_pull(void *ctx) { return a_buf_pull_back(ctx); }
#define A_BUF_PULL(T, ctx) a_cast_s(T *, a_buf_pull(ctx))

/*!
 @brief iterate over a buffer
 @code{.c}
 a_buf_forenum(i, ctx)
 {
     T *it = (T *)a_buf_at(ctx, i);
     assert(a_buf_siz(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the buffer
 @param ctx points to an instance of buffer structure
*/
#define a_buf_forenum(i, ctx) a_forenum(a_size, i, a_buf_num(ctx))
#define A_BUF_FORENUM(I, i, ctx) A_FORENUM(I, i, a_buf_num(ctx))

/*!
 @brief iterate over a buffer in reverse
 @code{.c}
 a_buf_forenum_reverse(i, ctx)
 {
     T *it = (T *)a_buf_at(ctx, i);
     assert(a_buf_siz(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the buffer
 @param ctx points to an instance of buffer structure
*/
#define a_buf_forenum_reverse(i, ctx) a_forenum_reverse(a_size, i, a_buf_num(ctx))
#define A_BUF_FORENUM_REVERSE(I, i, ctx) A_FORENUM_REVERSE(I, i, a_buf_num(ctx))

/*!
 @brief iterate over a buffer
 @code{.c}
 a_buf_foreach(T, *, it, ctx)
 {
     assert(a_buf_siz(ctx) == sizeof(*it));
 }
 @endcode
 @param T the prefix of the element type
 @param S the suffix of the element type
 @param it the &a_buf to use as a loop counter
 @param ctx points to an instance of buffer structure
*/
#define a_buf_foreach(T, S, it, ctx) a_foreach(T, S, it, a_buf_ptr(ctx), a_buf_num(ctx))
#define A_BUF_FOREACH(T, it, at, ctx) A_FOREACH(T, it, at, a_buf_ptr(ctx), a_buf_num(ctx))

/*!
 @brief iterate over a buffer in reverse
 @code{.c}
 a_buf_foreach_reverse(T, *, it, ctx)
 {
     assert(a_buf_siz(ctx) == sizeof(*it));
 }
 @endcode
 @param T the prefix of the element type
 @param S the suffix of the element type
 @param it the &a_buf to use as a loop counter
 @param ctx points to an instance of buffer structure
*/
#define a_buf_foreach_reverse(T, S, it, ctx) a_foreach_reverse(T, S, it, a_buf_ptr(ctx), a_buf_num(ctx))
#define A_BUF_FOREACH_REVERSE(T, it, at, ctx) A_FOREACH_REVERSE(T, it, at, a_buf_ptr(ctx), a_buf_num(ctx))

/*! @} a_buf */

#endif /* a/buf.h */
