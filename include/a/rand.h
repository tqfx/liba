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

typedef struct a_rand_lcg48 a_rand_lcg48;

/* clang-format off */
#define A_RAND_LCG48_INIT {A_U64_C(0x5DEECE66D), A_U16_C(0xB), {A_U16_C(0x330E), A_U16_C(0xABCD), A_U16_C(0x1234)}}
/* clang-format on */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief initialize with a seed value for the linear congruential generator and 48-bit integer arithmetic.
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @param[in] x is the seed value
*/
A_EXTERN void a_rand_lcg48_init(a_rand_lcg48 *ctx, long x);
/*!
 @brief initialize with a specific state for the linear congruential generator and 48-bit integer arithmetic.
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @param[in] x is the specific state. If null, use the internal state.
*/
A_EXTERN void a_rand_lcg48_seed(a_rand_lcg48 *ctx, a_u16 const x[3]);
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
 @param[in,out] x points to the state array. If null, use the internal state.
 @return a signed 32-bit random integer.
*/
A_EXTERN a_i32 a_rand_lcg48i(a_rand_lcg48 *ctx, a_u16 x[3]);
/*!
 @brief generate an unsigned 32-bit random integer.
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @param[in,out] x points to the state array. If null, use the internal state.
 @return an unsigned 32-bit random integer.
*/
A_EXTERN a_u32 a_rand_lcg48u(a_rand_lcg48 *ctx, a_u16 x[3]);
/*!
 @brief generate a 64-bit floating-point random number in [0,1).
 @param[in,out] ctx points to an instance of the linear congruential generator and 48-bit integer arithmetic
 @param[in,out] x points to the state array. If null, use the internal state.
 @return a 64-bit floating-point random number in [0,1).
*/
A_EXTERN a_f64 a_rand_lcg48f(a_rand_lcg48 *ctx, a_u16 x[3]);

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
};

/*! @} a_rand */

#endif /* a/rand.h */
