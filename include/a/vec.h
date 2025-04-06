/*!
 @file vec.h
 @brief basic vector library
*/

#ifndef LIBA_VEC_H
#define LIBA_VEC_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_vec basic vector library
 @{
*/

/*!
 @brief instance structure for basic vector
*/
typedef struct a_vec
{
    void *ptr_; /*!< address of vector */
    a_size siz_; /*!< size of a element */
    a_size num_; /*!< number of element */
    a_size mem_; /*!< memory of element */
} a_vec;

/*!
 @brief access address of vector for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN void *a_vec_ptr(a_vec const *ctx) { return ctx->ptr_; }
#define A_VEC_PTR(T, ctx) a_cast_s(T *, a_vec_ptr(ctx))

/*!
 @brief access size of a element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN a_size a_vec_siz(a_vec const *ctx) { return ctx->siz_; }

/*!
 @brief access number of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN a_size a_vec_num(a_vec const *ctx) { return ctx->num_; }

/*!
 @brief access memory of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INTERN a_size a_vec_mem(a_vec const *ctx) { return ctx->mem_; }

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than memory
 @note should check for out of bounds
 @return specified element pointer
*/
A_INTERN void *a_vec_at_(a_vec const *ctx, a_size idx)
{
    return a_byte_(*, ctx->ptr_) + ctx->siz_ * idx;
}
#define A_VEC_AT_(T, ctx, idx) a_cast_s(T *, a_vec_at_(ctx, idx))

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than memory
 @return specified element pointer
  @retval 0 out of bounds
*/
A_INTERN void *a_vec_at(a_vec const *ctx, a_size idx)
{
    return idx < ctx->mem_ ? a_vec_at_(ctx, idx) : A_NULL;
}
#define A_VEC_AT(T, ctx, idx) a_cast_s(T *, a_vec_at(ctx, idx))

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element -memory < idx < memory
 @return specified element pointer
  @retval 0 out of bounds
*/
A_INTERN void *a_vec_of(a_vec const *ctx, a_diff idx)
{
    a_size const num = idx >= 0 ? a_size_c(idx) : a_size_c(idx) + ctx->num_;
    return num < ctx->mem_ ? a_vec_at_(ctx, num) : A_NULL;
}
#define A_VEC_OF(T, ctx, idx) a_cast_s(T *, a_vec_of(ctx, idx))

/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @note should check if vector is empty
 @return specified element pointer
*/
A_INTERN void *a_vec_top_(a_vec const *ctx)
{
    return a_byte_(*, ctx->ptr_) + ctx->siz_ * (ctx->num_ - 1);
}
#define A_VEC_TOP_(T, ctx) a_cast_s(T *, a_vec_top_(ctx))

/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return specified element pointer
  @retval 0 empty vector
*/
A_INTERN void *a_vec_top(a_vec const *ctx)
{
    return ctx->num_ ? a_vec_top_(ctx) : A_NULL;
}
#define A_VEC_TOP(T, ctx) a_cast_s(T *, a_vec_top(ctx))

/*!
 @brief access end pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return vector end pointer
*/
A_INTERN void *a_vec_end_(a_vec const *ctx)
{
    return a_byte_(*, ctx->ptr_) + ctx->siz_ * ctx->num_;
}
#define A_VEC_END_(T, ctx) a_cast_s(T *, a_vec_end_(ctx))

/*!
 @brief access end pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return vector end pointer
  @retval 0 empty vector
*/
A_INTERN void *a_vec_end(a_vec const *ctx)
{
    return ctx->ptr_ ? a_vec_end_(ctx) : ctx->ptr_;
}
#define A_VEC_END(T, ctx) a_cast_s(T *, a_vec_end(ctx))

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to vector structure from memory
 @param[in] size size of element
*/
A_EXTERN a_vec *a_vec_new(a_size size);

/*!
 @brief deallocate a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor element destructor
*/
A_EXTERN void a_vec_die(a_vec *ctx, void (*dtor)(void *));

/*!
 @brief constructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] size size of element
*/
A_EXTERN void a_vec_ctor(a_vec *ctx, a_size size);

/*!
 @brief destructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor element destructor
*/
A_EXTERN void a_vec_dtor(a_vec *ctx, void (*dtor)(void *));

/*!
 @brief swap the contents of two pointers to vector structure
 @param[in] lhs points to an instance of vector structure
 @param[in] rhs points to an instance of vector structure
*/
A_EXTERN void a_vec_swap(a_vec *lhs, a_vec *rhs);

/*!
 @brief set memory of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] mem new memory of current element
 @return error code value
  @retval 0 success
*/
A_EXTERN int a_vec_setm(a_vec *ctx, a_size mem);

/*!
 @brief set number of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] num new number of current element
 @param[in] dtor current element destructor
 @return error code value
  @retval 0 success
*/
A_EXTERN int a_vec_setn(a_vec *ctx, a_size num, void (*dtor)(void *));

/*!
 @brief set size of a element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] siz the size of the new element
 @param[in] dtor previous element destructor
*/
A_EXTERN void a_vec_setz(a_vec *ctx, a_size siz, void (*dtor)(void *));

/*!
 @brief sort all elements for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_EXTERN void a_vec_sort(a_vec const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert sort foremost element for a pointer to vector structure
 @code{.c}
 T *obj = A_VEC_PUSH_FORE(T, ctx);
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
A_EXTERN void a_vec_sort_fore(a_vec const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert sort backmost element for a pointer to vector structure
 @code{.c}
 T *obj = A_VEC_PUSH_BACK(T, ctx);
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
A_EXTERN void a_vec_sort_back(a_vec const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief push an element into the vector and sort it
 @param[in] ctx points to an instance of vector structure
 @param[in] key the key on the right for insertion sort
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_push_sort(a_vec *ctx, void const *key, int (*cmp)(void const *, void const *));
#define A_VEC_PUSH_SORT(T, ctx, key, cmp) a_cast_s(T *, a_vec_push_sort(ctx, key, cmp))

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
A_EXTERN void *a_vec_search(a_vec const *ctx, void const *obj, int (*cmp)(void const *, void const *));
#define A_VEC_SEARCH(T, ctx, obj, cmp) a_cast_s(T *, a_vec_search(ctx, obj, cmp))

/*!
 @brief insert an element into the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element in this vector
  @arg 0 a_vec_push_fore
  @arg n a_vec_push_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_insert(a_vec *ctx, a_size idx);
#define A_VEC_INSERT(T, ctx, idx) a_cast_s(T *, a_vec_insert(ctx, idx))

/*!
 @brief remove an element from the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element in this vector
  @arg 0 a_vec_pull_fore
  @arg n a_vec_pull_back
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_remove(a_vec *ctx, a_size idx);
#define A_VEC_REMOVE(T, ctx, idx) a_cast_s(T *, a_vec_remove(ctx, idx))

/*!
 @brief push an element into the vector forward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_push_fore(a_vec *ctx);
#define A_VEC_PUSH_FORE(T, ctx) a_cast_s(T *, a_vec_push_fore(ctx))

/*!
 @brief push an element into the vector backward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_push_back(a_vec *ctx);
#define A_VEC_PUSH_BACK(T, ctx) a_cast_s(T *, a_vec_push_back(ctx))

/*!
 @brief pull an element from the vector forward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_pull_fore(a_vec *ctx);
#define A_VEC_PULL_FORE(T, ctx) a_cast_s(T *, a_vec_pull_fore(ctx))

/*!
 @brief pull an element from the vector backward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_EXTERN void *a_vec_pull_back(a_vec *ctx);
#define A_VEC_PULL_BACK(T, ctx) a_cast_s(T *, a_vec_pull_back(ctx))

/*!
 @brief store elements into the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element in this vector
 @param[in] ptr points to array elements
 @param[in] num number of array elements
 @param[in] copy a function that copies elements
  @arg 0 use function a_copy to copy elements
 @return error code value
  @retval 0 success
*/
A_EXTERN int a_vec_store(a_vec *ctx, a_size idx, void *ptr, a_size num, int (*copy)(void *, void const *));

/*!
 @brief erase elements from the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element in this vector
 @param[in] num number of elements to erase
 @param[in] dtor a function that erases elements
  @arg 0 not erase these elements
 @return error code value
  @retval 0 success
*/
A_EXTERN int a_vec_erase(a_vec *ctx, a_size idx, a_size num, void (*dtor)(void *));

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief push an element into the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_INTERN void *a_vec_push(a_vec *ctx) { return a_vec_push_back(ctx); }
#define A_VEC_PUSH(T, ctx) a_cast_s(T *, a_vec_push(ctx))

/*!
 @brief pull an element from the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_INTERN void *a_vec_pull(a_vec *ctx) { return a_vec_pull_back(ctx); }
#define A_VEC_PULL(T, ctx) a_cast_s(T *, a_vec_pull(ctx))

/*!
 @brief iterate over a vector
 @code{.c}
 a_vec_forenum(i, ctx)
 {
     T *it = (T *)a_vec_at(ctx, i);
     assert(a_vec_siz(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vec_forenum(i, ctx) a_forenum(a_size, i, (ctx)->num_)
#define A_VEC_FORENUM(I, i, ctx) A_FORENUM(I, i, (ctx)->num_)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vec_forenum_reverse(i, ctx)
 {
     T *it = (T *)a_vec_at(ctx, i);
     assert(a_vec_siz(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vec_forenum_reverse(i, ctx) a_forenum_reverse(a_size, i, (ctx)->num_)
#define A_VEC_FORENUM_REVERSE(I, i, ctx) A_FORENUM_REVERSE(I, i, (ctx)->num_)

/*!
 @brief iterate over a vector
 @code{.c}
 a_vec_foreach(T, *, it, ctx)
 {
     assert(a_vec_siz(ctx) == sizeof(*it));
 }
 @endcode
 @param T the prefix of the element type
 @param S the suffix of the element type
 @param it the &a_vec to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vec_foreach(T, S, it, ctx) a_forsafe(T, S, it, (ctx)->ptr_, (ctx)->num_)
#define A_VEC_FOREACH(T, it, at, ctx) A_FORSAFE(T, it, at, (ctx)->ptr_, (ctx)->num_)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vec_foreach_reverse(T, *, it, ctx)
 {
     assert(a_vec_siz(ctx) == sizeof(*it));
 }
 @endcode
 @param T the prefix of the element type
 @param S the suffix of the element type
 @param it the &a_vec to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vec_foreach_reverse(T, S, it, ctx) a_forsafe_reverse(T, S, it, (ctx)->ptr_, (ctx)->num_)
#define A_VEC_FOREACH_REVERSE(T, it, at, ctx) A_FORSAFE_REVERSE(T, it, at, (ctx)->ptr_, (ctx)->num_)

/*! @} a_vec */

#endif /* a/vec.h */
