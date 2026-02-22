/*!
 @file rand.h
 @brief pseudorandom number generator
 @details https://en.wikipedia.org/wiki/Pseudorandom_number_generator
*/

#ifndef LIBA_RAND_H
#define LIBA_RAND_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_rand pseudorandom number generator
 @{
*/

/* clang-format off */
#define A_RAND_LCG48_INIT {A_U64_C(0x5DEECE66D), A_U16_C(0xB), {A_U16_C(0x330E), A_U16_C(0xABCD), A_U16_C(0x1234)}}
/* clang-format on */

typedef struct a_rand_lcg48 a_rand_lcg48;

#if defined(__cplusplus)
namespace a
{
typedef struct a_rand_lcg48 rand_lcg48;
} /* namespace a */
extern "C" {
#endif /* __cplusplus */
#if !defined A_HAVE_INLINE || defined(LIBA_RAND_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN A_PUBLIC extern
/*! @endcond */
#endif /* A_HAVE_INLINE */

/*!
 @brief initialize with a seed value for the linear congruential generator and 48-bit integer arithmetic.
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @param[in] x is the seed value
*/
A_EXTERN A_NONULL((1)) void a_rand_lcg48_init(a_rand_lcg48 *ctx, a_i64 x);
/*!
 @brief initialize with a specific state for the linear congruential generator and 48-bit integer arithmetic.
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @param[in] x is the specific state. If null, use the internal state.
*/
A_EXTERN A_NONULL((1)) void a_rand_lcg48_seed(a_rand_lcg48 *ctx, a_u16 const x[3]);
/*!
 @brief perform one iteration for the linear congruential generator and 48-bit integer arithmetic.
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @param[in,out] x points to the state array
 @return the result before being truncated
*/
A_EXTERN A_NONULL((1, 2)) a_u64 a_rand_lcg48_iter(a_rand_lcg48 *ctx, a_u16 x[3]);

/*!
 @brief generate a signed 32-bit random integer.
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @return a signed 32-bit random integer
*/
A_INTERN A_NONULL((1)) a_i32 a_rand_lcg48i(a_rand_lcg48 *ctx);
/*!
 @brief generate a signed 32-bit random integer.
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @param[in,out] x points to the state array
 @return a signed 32-bit random integer
*/
A_EXTERN A_NONULL((1, 2)) a_i32 a_rand_lcg48i_(a_rand_lcg48 *ctx, a_u16 x[3]);
/*!
 @brief generate an unsigned 32-bit random integer.
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @return an unsigned 32-bit random integer
*/
A_INTERN A_NONULL((1)) a_u32 a_rand_lcg48u(a_rand_lcg48 *ctx);
/*!
 @brief generate an unsigned 32-bit random integer.
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @param[in,out] x points to the state array. If null, use the internal state.
 @return an unsigned 32-bit random integer
*/
A_EXTERN A_NONULL((1, 2)) a_u32 a_rand_lcg48u_(a_rand_lcg48 *ctx, a_u16 x[3]);
/*!
 @brief generate a 64-bit floating-point random number in [0,1).
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @return a 64-bit floating-point random number in [0,1)
*/
A_INTERN A_NONULL((1)) a_f64 a_rand_lcg48f(a_rand_lcg48 *ctx);
/*!
 @brief generate a 64-bit floating-point random number in [0,1).
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @param[in,out] x points to the state array. If null, use the internal state.
 @return a 64-bit floating-point random number in [0,1)
*/
A_EXTERN A_NONULL((1, 2)) a_f64 a_rand_lcg48f_(a_rand_lcg48 *ctx, a_u16 x[3]);

/*!
 @brief shuffle the elements of an array in place using the Fisher-Yates (Knuth) shuffle algorithm.
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @param[in] ptr points to the elements in the array
 @param[in] num number of the elements in the array
 @param[in] siz size of each element in the array
*/
A_EXTERN A_NONULL((1)) void a_rand_lcg48_shuf(a_rand_lcg48 *ctx, void *ptr, a_size num, a_size siz);

#if !defined A_HAVE_INLINE || defined(LIBA_RAND_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN static A_INLINE
/*! @endcond */
#endif /* A_HAVE_INLINE */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief instance structure for the linear congruential generator and 48-bit integer arithmetic
*/
struct a_rand_lcg48
{
    a_u64 a; /*!< multiplier term */
    a_u16 c; /*!< increment term */
    a_u16 x[3]; /*!< random value */
#if defined(__cplusplus)
    /*! @copybrief a_rand_lcg48_init @see a_rand_lcg48_init */
    A_INLINE void init(a_i64 x_) { a_rand_lcg48_init(this, x_); }
    /*! @copybrief a_rand_lcg48_seed @see a_rand_lcg48_seed */
    A_INLINE void seed(a_u16 const x_[3] = A_NULL) { a_rand_lcg48_seed(this, x_); }
    /*! @copybrief a_rand_lcg48_iter @see a_rand_lcg48_iter */
    A_INLINE A_NONULL((2)) a_u64 iter(a_u16 x_[3]) { return a_rand_lcg48_iter(this, x_); }
    /*! @copybrief a_rand_lcg48i @see a_rand_lcg48i @see a_rand_lcg48i_ */
    A_INLINE a_i32 i(a_u16 x_[3] = A_NULL)
    {
        if (x_) { return a_rand_lcg48i_(this, x_); }
        return a_rand_lcg48i_(this, x);
    }
    /*! @copybrief a_rand_lcg48u @see a_rand_lcg48u @see a_rand_lcg48u_ */
    A_INLINE a_u32 u(a_u16 x_[3] = A_NULL)
    {
        if (x_) { return a_rand_lcg48u_(this, x_); }
        return a_rand_lcg48u_(this, x);
    }
    /*! @copybrief a_rand_lcg48f @see a_rand_lcg48f @see a_rand_lcg48f_ */
    A_INLINE a_f64 f(a_u16 x_[3] = A_NULL)
    {
        if (x_) { return a_rand_lcg48f_(this, x_); }
        return a_rand_lcg48f_(this, x);
    }
    /*! @copybrief a_rand_lcg48_shuf @see a_rand_lcg48_shuf */
    A_INLINE void shuf(void *ptr, a_size num, a_size siz)
    {
        a_rand_lcg48_shuf(this, ptr, num, siz);
    }
#endif /* __cplusplus */
};

#if defined(LIBA_RAND_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN A_INLINE
/*! @endcond */
#endif /* LIBA_RAND_C */
#if defined(A_HAVE_INLINE) || defined(LIBA_RAND_C)

A_INTERN a_i32 a_rand_lcg48i(a_rand_lcg48 *ctx) { return a_rand_lcg48i_(ctx, ctx->x); }
A_INTERN a_u32 a_rand_lcg48u(a_rand_lcg48 *ctx) { return a_rand_lcg48u_(ctx, ctx->x); }
A_INTERN a_f64 a_rand_lcg48f(a_rand_lcg48 *ctx) { return a_rand_lcg48f_(ctx, ctx->x); }

#endif /* A_HAVE_INLINE */
#if defined(LIBA_RAND_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN static A_INLINE
/*! @endcond */
#endif /* LIBA_RAND_C */

/*! @} a_rand */

#endif /* a/rand.h */
