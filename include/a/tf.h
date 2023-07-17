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
typedef struct a_tf_s
{
    a_float_t *input; //!< input
    a_float_t *output; //!< output
    a_float_t const *num_p; //!< numerator
    a_float_t const *den_p; //!< denominator
    unsigned int num_n; //!< numerator number
    unsigned int den_n; //!< denominator number
} a_tf_s;

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
A_EXTERN void a_tf_set_num(a_tf_s *ctx, unsigned int num_n, a_float_t const *num_p, a_float_t *input);

/*!
 @brief set denominator for transfer function
 @param[in,out] ctx points to an instance of transfer function
 @param[in] den_n denominator number
 @param[in] den_p denominator
 @param[in] output output
*/
A_EXTERN void a_tf_set_den(a_tf_s *ctx, unsigned int den_n, a_float_t const *den_p, a_float_t *output);

/*!
 @brief initialize function for transfer function
 @param[in,out] ctx points to an instance of transfer function
 @param[in] num_n numerator number
 @param[in] num_p numerator
 @param[in] input input
 @param[in] den_n denominator number
 @param[in] den_p denominator
 @param[in] output output
*/
A_EXTERN void a_tf_init(a_tf_s *ctx,
                        unsigned int num_n, a_float_t const *num_p, a_float_t *input,
                        unsigned int den_n, a_float_t const *den_p, a_float_t *output);

/*!
 @brief calculate function for transfer function
 @param[in] ctx points to an instance of transfer function
 @param[in] x transfer function input
 @return transfer function output
*/
A_EXTERN a_float_t a_tf_iter(a_tf_s const *ctx, a_float_t x);

/*!
 @brief zero clear function for transfer function
 @param[in] ctx points to an instance of transfer function
*/
A_EXTERN void a_tf_zero(a_tf_s const *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_TF */

#endif /* a/tf.h */
