/*!
 @file vec.h
 @brief basic vector library
*/

#ifndef LIBA_HOST_VEC_H
#define LIBA_HOST_VEC_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_VEC basic vector library
 @{
*/

/*!
 @brief instance structure for basic vector
*/
typedef struct a_vec_s
{
    void *_ptr; /*!< address of vector */
    a_size_t _num; /*!< number of element */
    a_size_t _mem; /*!< memory of element */
    a_size_t _siz; /*!< size of a element */
} a_vec_s;

/*!
 @brief access address of vector for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN void *a_vec_ptr(a_vec_s const *const ctx) { return ctx->_ptr; }

/*!
 @brief access number of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN a_size_t a_vec_num(a_vec_s const *const ctx) { return ctx->_num; }

/*!
 @brief access memory of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN a_size_t a_vec_mem(a_vec_s const *const ctx) { return ctx->_mem; }

/*!
 @brief access size of a element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN a_size_t a_vec_get(a_vec_s const *const ctx) { return ctx->_siz; }

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than memory
 @note should check for out of bounds
 @return specified element pointer
*/
A_INTERN void *a_vec_at_(a_vec_s const *const ctx, a_size_t const idx)
{
    return a_byte_c(*, ctx->_ptr) + ctx->_siz * idx;
}

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than memory
 @return specified element pointer
  @retval 0 out of bounds
*/
A_INTERN void *a_vec_at(a_vec_s const *const ctx, a_size_t const idx)
{
    return a_likely(idx < ctx->_mem) ? a_vec_at_(ctx, idx) : A_NULL;
}

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element -memory < idx < memory
 @return specified element pointer
  @retval 0 out of bounds
*/
A_INTERN void *a_vec_idx(a_vec_s const *const ctx, a_diff_t const idx)
{
    a_size_t const num = idx < 0 ? a_size_c(, idx) + ctx->_num : a_size_c(, idx);
    return a_likely(num < ctx->_mem) ? a_vec_at_(ctx, num) : A_NULL;
}

/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @note should check if vector is empty
 @return specified element pointer
*/
A_INTERN void *a_vec_top_(a_vec_s const *const ctx)
{
    return a_byte_c(*, ctx->_ptr) + ctx->_siz * (ctx->_num - 1);
}

/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return specified element pointer
  @retval 0 empty vector
*/
A_INTERN void *a_vec_top(a_vec_s const *const ctx)
{
    return a_likely(ctx->_num) ? a_vec_top_(ctx) : A_NULL;
}

/*!
 @brief access end pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return vector end pointer
*/
A_INTERN void *a_vec_end_(a_vec_s const *const ctx)
{
    return a_byte_c(*, ctx->_ptr) + ctx->_siz * ctx->_num;
}

/*!
 @brief access end pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return vector end pointer
  @retval 0 empty vector
*/
A_INTERN void *a_vec_end(a_vec_s const *const ctx)
{
    return a_likely(ctx->_ptr) ? a_vec_end_(ctx) : ctx->_ptr;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to vector structure from memory
 @param[in] size size of element
*/
A_EXTERN a_vec_s *a_vec_new(a_size_t size);

/*!
 @brief deallocate a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor element destructor
*/
A_EXTERN void a_vec_die(a_vec_s *ctx, void (*dtor)(void *));

/*!
 @brief constructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] size size of element
*/
A_EXTERN void a_vec_ctor(a_vec_s *ctx, a_size_t size);

/*!
 @brief destructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor element destructor
*/
A_EXTERN void a_vec_dtor(a_vec_s *ctx, void (*dtor)(void *));

/*!
 @brief initialize a pointer to vector structure by copying
 @param[in] ctx points to an instance of vector structure
 @param[in] obj input source pointing to an instance
 @param[in] dup a function that copies elements
  @arg 0 use function a_copy to copy elements
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_vec_copy(a_vec_s *ctx, a_vec_s const *obj, int (*dup)(void *, void const *));

/*!
 @brief initialize a pointer to vector structure by moving
 @param[in] ctx points to an instance of vector structure
 @param[in] obj input source pointing to an instance
*/
A_EXTERN a_vec_s *a_vec_move(a_vec_s *ctx, a_vec_s *obj);

/*!
 @brief modify size of a element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] size the size of the new element
 @param[in] dtor previous element destructor
*/
A_EXTERN void a_vec_set(a_vec_s *ctx, a_size_t size, void (*dtor)(void *));

/*!
 @brief modify element number for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] num number of all elements in the vector
 @param[in] dtor previous element destructor
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_vec_make(a_vec_s *ctx, a_size_t num, void (*dtor)(void *));

/*!
 @brief drop all the elements for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor current element destructor
*/
A_EXTERN void a_vec_drop(a_vec_s *ctx, void (*dtor)(void *));

/*!
 @brief swap elements lhs and rhs for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] lhs element index on the left
 @param[in] rhs element index on the right
*/
A_EXTERN void a_vec_swap(a_vec_s const *ctx, a_size_t lhs, a_size_t rhs);

/*!
 @brief sort all elements for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_vec_sort(a_vec_s const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert sort foremost element for a pointer to vector structure
 @code{.c}
 T *obj = a_vec_push_fore(T, ctx);
 if (obj)
 {
     CTOR(obj);
     INIT(obj);
     a_vec_sort_fore(ctx, cmp);
 }
 @endcode
 @param[in] ctx points to an instance of vector structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_vec_sort_fore(a_vec_s const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert sort backmost element for a pointer to vector structure
 @code{.c}
 T *obj = a_vec_push_back(T, ctx);
 if (obj)
 {
     CTOR(obj);
     INIT(obj);
     a_vec_sort_back(ctx, cmp);
 }
 @endcode
 @param[in] ctx points to an instance of vector structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_vec_sort_back(a_vec_s const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief search the given element in this vector
 @param[in] ctx points to an instance of vector structure
 @param[in] obj object that serves as key for the search
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
 @return matching element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_search(a_vec_s const *ctx, void const *obj, int (*cmp)(void const *, void const *));

/*!
 @brief insert an element into the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element in this vector
  @arg 0 a_vec_push_fore
  @arg n a_vec_push_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_insert(a_vec_s *ctx, a_size_t idx);

/*!
 @brief remove an element from the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element in this vector
  @arg 0 a_vec_pull_fore
  @arg n a_vec_pull_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_remove(a_vec_s *ctx, a_size_t idx);

/*!
 @brief push an element into the vector forward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_push_fore(a_vec_s *ctx);

/*!
 @brief push an element into the vector backward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_push_back(a_vec_s *ctx);

/*!
 @brief pull an element from the vector forward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_pull_fore(a_vec_s *ctx);

/*!
 @brief pull an element from the vector backward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_pull_back(a_vec_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief push an element into the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_INTERN void *a_vec_push(a_vec_s *ctx) { return a_vec_push_back(ctx); }

/*!
 @brief pull an element from the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_INTERN void *a_vec_pull(a_vec_s *ctx) { return a_vec_pull_back(ctx); }

/*!
 @brief iterate over a vector
 @code{.c}
 a_vec_forenum(i, ctx)
 {
     T *it = (T *)a_vec_at(ctx, i);
     assert(a_vec_get(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vec_forenum(i, ctx) a_forenum(a_size_t, i, (ctx)->_num)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vec_forenum_reverse(i, ctx)
 {
     T *it = (T *)a_vec_at(ctx, i);
     assert(a_vec_get(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vec_forenum_reverse(i, ctx) a_forenum_reverse(a_size_t, i, (ctx)->_num)

/*!
 @brief iterate over a vector
 @code{.c}
 a_vec_foreach(T, it, ctx)
 {
     assert(a_vec_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the vector
 @param it the &a_vec_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vec_foreach(T, it, ctx) a_foreach(T, it, (ctx)->_ptr, (ctx)->_num)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vec_foreach_reverse(T, it, ctx)
 {
     assert(a_vec_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the vector
 @param it the &a_vec_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vec_foreach_reverse(T, it, ctx) a_foreach_reverse(T, it, (ctx)->_ptr, (ctx)->_num)

#define a_vec_ptr(T, ctx) a_cast_s(T *, a_vec_ptr(ctx))
#define a_vec_end(T, ctx) a_cast_s(T *, a_vec_end(ctx))
#define a_vec_top(T, ctx) a_cast_s(T *, a_vec_top(ctx))
#define a_vec_end_(T, ctx) a_cast_s(T *, a_vec_end_(ctx))
#define a_vec_top_(T, ctx) a_cast_s(T *, a_vec_top_(ctx))
#define a_vec_at(T, ctx, idx) a_cast_s(T *, a_vec_at(ctx, idx))
#define a_vec_at_(T, ctx, idx) a_cast_s(T *, a_vec_at_(ctx, idx))
#define a_vec_idx(T, ctx, idx) a_cast_s(T *, a_vec_idx(ctx, idx))
#define a_vec_search(T, ctx, obj, cmp) a_cast_s(T *, a_vec_search(ctx, obj, cmp))
#define a_vec_insert(T, ctx, idx) a_cast_s(T *, a_vec_insert(ctx, idx))
#define a_vec_remove(T, ctx, idx) a_cast_s(T *, a_vec_remove(ctx, idx))
#define a_vec_push_fore(T, ctx) a_cast_s(T *, a_vec_push_fore(ctx))
#define a_vec_push_back(T, ctx) a_cast_s(T *, a_vec_push_back(ctx))
#define a_vec_pull_fore(T, ctx) a_cast_s(T *, a_vec_pull_fore(ctx))
#define a_vec_pull_back(T, ctx) a_cast_s(T *, a_vec_pull_back(ctx))
#define a_vec_push(T, ctx) a_cast_s(T *, a_vec_push(ctx))
#define a_vec_pull(T, ctx) a_cast_s(T *, a_vec_pull(ctx))

/*! @} A_VEC */

#endif /* host/vec.h */
