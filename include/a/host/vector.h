/*!
 @file vector.h
 @brief basic vector library
*/

#ifndef LIBA_HOST_VECTOR_H
#define LIBA_HOST_VECTOR_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_VECTOR basic vector library
 @{
*/

/*!
 @brief instance structure for basic vector
*/
typedef struct a_vector_s
{
    void (*ctor)(void *); /*!< element constructor */
    void (*dtor)(void *); /*!< element destructor */
    void *_head; /*!< head address */
    void *_tail; /*!< tail address */
    void *_last; /*!< last address */
    a_size_t _siz; /*!< size element */
    a_size_t _num; /*!< count number */
    a_size_t _mem; /*!< count memory */
} a_vector_s;

/*!
 @brief access vector head pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN void *a_vector_ptr(a_vector_s const *const ctx) { return ctx->_head; }

/*!
 @brief access vector tail pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN void *a_vector_end(a_vector_s const *const ctx) { return ctx->_tail; }

/*!
 @brief access size of a element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN a_size_t a_vector_get(a_vector_s const *const ctx) { return ctx->_siz; }

/*!
 @brief access number of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN a_size_t a_vector_num(a_vector_s const *const ctx) { return ctx->_num; }

/*!
 @brief access capacity of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN a_size_t a_vector_mem(a_vector_s const *const ctx) { return ctx->_mem; }

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than capacity
 @note should check for out of bounds
 @return specified element pointer
*/
A_INTERN void *a_vector_at_(a_vector_s const *const ctx, a_size_t idx)
{
    return a_byte_c(*, ctx->_head) + ctx->_siz * idx;
}

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than capacity
 @return specified element pointer
  @retval 0 out of bounds
*/
A_INTERN void *a_vector_at(a_vector_s const *const ctx, a_size_t idx)
{
    return a_likely(idx < ctx->_mem) ? a_vector_at_(ctx, idx) : A_NULL;
}

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element -capacity < idx < capacity
 @return specified element pointer
  @retval 0 out of bounds
*/
A_INTERN void *a_vector_idx(a_vector_s const *const ctx, a_diff_t const idx)
{
    a_size_t const num = idx < 0 ? a_size_c(, idx) + ctx->_num : a_size_c(, idx);
    return a_likely(num < ctx->_mem) ? a_vector_at_(ctx, num) : A_NULL;
}

/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @note should check if vector is empty
 @return specified element pointer
*/
A_INTERN void *a_vector_top_(a_vector_s const *const ctx)
{
    return a_byte_c(*, ctx->_tail) - ctx->_siz;
}

/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return specified element pointer
  @retval 0 empty vector
*/
A_INTERN void *a_vector_top(a_vector_s const *const ctx)
{
    return a_likely(ctx->_num) ? a_vector_top_(ctx) : A_NULL;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to vector structure from memory
 @param[in] size the size of the element
 @param[in] ctor element constructor
 @param[in] dtor element destructor
*/
A_EXTERN a_vector_s *a_vector_new(a_size_t size,
                                  void (*ctor)(void *),
                                  void (*dtor)(void *));

/*!
 @brief deallocate a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_EXTERN void a_vector_die(a_vector_s *ctx);

/*!
 @brief constructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] size the size of the element
 @param[in] ctor element constructor
 @param[in] dtor element destructor
*/
A_EXTERN void a_vector_ctor(a_vector_s *ctx, a_size_t size,
                            void (*ctor)(void *),
                            void (*dtor)(void *));

/*!
 @brief destructor for vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_EXTERN void a_vector_dtor(a_vector_s *ctx);

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
A_EXTERN int a_vector_copy(a_vector_s *ctx, a_vector_s const *obj, int (*dup)(void *, void const *));

/*!
 @brief initialize a pointer to vector structure by moving
 @param[in] ctx points to an instance of vector structure
 @param[in] obj input source pointing to an instance
*/
A_EXTERN a_vector_s *a_vector_move(a_vector_s *ctx, a_vector_s *obj);

/*!
 @brief modify size of a element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] size the size of the new element
 @param[in] ctor current element constructor
 @param[in] dtor current element destructor
*/
A_EXTERN void a_vector_set(a_vector_s *ctx, a_size_t size,
                           void (*ctor)(void *),
                           void (*dtor)(void *));

/*!
 @brief modify element number for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] num number of all elements in the vector
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_vector_make(a_vector_s *ctx, a_size_t num);

/*!
 @brief drop all the elements for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_EXTERN void a_vector_drop(a_vector_s *ctx);

/*!
 @brief swap elements lhs and rhs for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] lhs element index on the left
 @param[in] rhs element index on the right
*/
A_EXTERN void a_vector_swap(a_vector_s const *ctx, a_size_t lhs, a_size_t rhs);

/*!
 @brief sort all elements for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_vector_sort(a_vector_s const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert sort foremost element for a pointer to vector structure
 @code{.c}
 T *obj = a_vector_push_fore(T, ctx);
 if (obj)
 {
     CTOR(obj);
     INIT(obj);
     a_vector_sort_fore(ctx, cmp);
 }
 @endcode
 @param[in] ctx points to an instance of vector structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_vector_sort_fore(a_vector_s const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert sort backmost element for a pointer to vector structure
 @code{.c}
 T *obj = a_vector_push_back(T, ctx);
 if (obj)
 {
     CTOR(obj);
     INIT(obj);
     a_vector_sort_back(ctx, cmp);
 }
 @endcode
 @param[in] ctx points to an instance of vector structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_vector_sort_back(a_vector_s const *ctx, int (*cmp)(void const *, void const *));

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
A_EXTERN void *a_vector_search(a_vector_s const *ctx, void const *obj, int (*cmp)(void const *, void const *));

/*!
 @brief insert an element into the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element in this vector
  @arg 0 a_vector_push_fore
  @arg n a_vector_push_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vector_insert(a_vector_s *ctx, a_size_t idx);

/*!
 @brief remove an element from the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element in this vector
  @arg 0 a_vector_pull_fore
  @arg n a_vector_pull_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vector_remove(a_vector_s *ctx, a_size_t idx);

/*!
 @brief push an element into the vector forward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vector_push_fore(a_vector_s *ctx);

/*!
 @brief push an element into the vector backward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vector_push_back(a_vector_s *ctx);

/*!
 @brief pull an element from the vector forward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vector_pull_fore(a_vector_s *ctx);

/*!
 @brief pull an element from the vector backward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vector_pull_back(a_vector_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief push an element into the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_INTERN void *a_vector_push(a_vector_s *ctx) { return a_vector_push_back(ctx); }

/*!
 @brief pull an element from the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_INTERN void *a_vector_pull(a_vector_s *ctx) { return a_vector_pull_back(ctx); }

/*!
 @brief iterate over a vector
 @code{.c}
 a_vector_forenum(i, ctx)
 {
     T *it = (T *)a_vector_at(ctx, i);
     assert(a_vector_get(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vector_forenum(i, ctx) a_forenum(a_size_t, i, (ctx)->_num)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vector_forenum_reverse(i, ctx)
 {
     T *it = (T *)a_vector_at(ctx, i);
     assert(a_vector_get(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vector_forenum_reverse(i, ctx) a_forenum_reverse(a_size_t, i, (ctx)->_num)

/*!
 @brief iterate over a vector
 @code{.c}
 a_vector_foreach(T, it, ctx)
 {
     assert(a_vector_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the vector
 @param it the &a_vector_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vector_foreach(T, it, ctx) a_iterate(T, it, (ctx)->_head, (ctx)->_tail)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vector_foreach_reverse(T, it, ctx)
 {
     assert(a_vector_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the vector
 @param it the &a_vector_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vector_foreach_reverse(T, it, ctx) a_iterate_reverse(T, it, (ctx)->_head, (ctx)->_tail)

#define a_vector_ptr(T, ctx) a_cast_s(T *, a_vector_ptr(ctx))
#define a_vector_end(T, ctx) a_cast_s(T *, a_vector_end(ctx))
#define a_vector_top(T, ctx) a_cast_s(T *, a_vector_top(ctx))
#define a_vector_top_(T, ctx) a_cast_s(T *, a_vector_top_(ctx))
#define a_vector_at(T, ctx, idx) a_cast_s(T *, a_vector_at(ctx, idx))
#define a_vector_at_(T, ctx, idx) a_cast_s(T *, a_vector_at_(ctx, idx))
#define a_vector_idx(T, ctx, idx) a_cast_s(T *, a_vector_idx(ctx, idx))
#define a_vector_search(T, ctx, obj, cmp) a_cast_s(T *, a_vector_search(ctx, obj, cmp))
#define a_vector_insert(T, ctx, idx) a_cast_s(T *, a_vector_insert(ctx, idx))
#define a_vector_remove(T, ctx, idx) a_cast_s(T *, a_vector_remove(ctx, idx))
#define a_vector_push_fore(T, ctx) a_cast_s(T *, a_vector_push_fore(ctx))
#define a_vector_push_back(T, ctx) a_cast_s(T *, a_vector_push_back(ctx))
#define a_vector_pull_fore(T, ctx) a_cast_s(T *, a_vector_pull_fore(ctx))
#define a_vector_pull_back(T, ctx) a_cast_s(T *, a_vector_pull_back(ctx))
#define a_vector_push(T, ctx) a_cast_s(T *, a_vector_push(ctx))
#define a_vector_pull(T, ctx) a_cast_s(T *, a_vector_pull(ctx))

/*! @} A_VECTOR */

#endif /* host/vector.h */
