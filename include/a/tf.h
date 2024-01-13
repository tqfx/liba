/*!
 @file tf.h
 @brief transfer function
*/

#ifndef LIBA_TF_H
#define LIBA_TF_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_TF transfer function
 @{
*/

/*!
 @brief instance structure for transfer function
*/
typedef struct a_tf
{
    a_float *input; //!< input
    a_float *output; //!< output
    a_float const *num_p; //!< numerator
    a_float const *den_p; //!< denominator
    unsigned int num_n; //!< numerator number
    unsigned int den_n; //!< denominator number
} a_tf;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief set numerator for transfer function
 @param[in,out] ctx points to an instance of transfer function
 @param[in] num_n numerator number
 @param[in] num_p numerator
 @param[in] input input
*/
A_EXTERN void a_tf_set_num(a_tf *ctx, unsigned int num_n, a_float const *num_p, a_float *input);

/*!
 @brief set denominator for transfer function
 @param[in,out] ctx points to an instance of transfer function
 @param[in] den_n denominator number
 @param[in] den_p denominator
 @param[in] output output
*/
A_EXTERN void a_tf_set_den(a_tf *ctx, unsigned int den_n, a_float const *den_p, a_float *output);

/*!
 @brief initialize for transfer function
 @param[in,out] ctx points to an instance of transfer function
 @param[in] num_n numerator number
 @param[in] num_p numerator
 @param[in] input input
 @param[in] den_n denominator number
 @param[in] den_p denominator
 @param[in] output output
*/
A_EXTERN void a_tf_init(a_tf *ctx,
                        unsigned int num_n, a_float const *num_p, a_float *input,
                        unsigned int den_n, a_float const *den_p, a_float *output);

/*!
 @brief calculate for transfer function
 @param[in] ctx points to an instance of transfer function
 @param[in] x transfer function input
 @return transfer function output
*/
A_EXTERN a_float a_tf_iter(a_tf const *ctx, a_float x);

/*!
 @brief zeroing for transfer function
 @param[in] ctx points to an instance of transfer function
*/
A_EXTERN void a_tf_zero(a_tf const *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_TF */

#endif /* a/tf.h */
