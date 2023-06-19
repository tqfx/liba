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
    a_float_t *u; //!< input
    a_float_t *v; //!< output
    a_float_t const *num; //!< numerator
    a_float_t const *den; //!< denominator
    unsigned int m; //!< numerator number
    unsigned int n; //!< denominator number
} a_tf_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief set numerator for transfer function
 @param[in,out] ctx points to an instance of transfer function
 @param[in] m numerator number
 @param[in] num numerator
 @param[in] u input buffer
*/
A_EXTERN void a_tf_set_num(a_tf_s *ctx, unsigned int m, a_float_t const *num, a_float_t *u);

/*!
 @brief set denominator for transfer function
 @param[in,out] ctx points to an instance of transfer function
 @param[in] n denominator number
 @param[in] den denominator
 @param[in] v output buffer
*/
A_EXTERN void a_tf_set_den(a_tf_s *ctx, unsigned int n, a_float_t const *den, a_float_t *v);

/*!
 @brief initialize function for transfer function
 @param[in,out] ctx points to an instance of transfer function
 @param[in] m numerator number
 @param[in] num numerator
 @param[in] u input buffer
 @param[in] n denominator number
 @param[in] den denominator
 @param[in] v output buffer
*/
A_EXTERN a_tf_s *a_tf_init(a_tf_s *ctx,
                           unsigned int m, a_float_t const *num, a_float_t *u,
                           unsigned int n, a_float_t const *den, a_float_t *v);

/*!
 @brief calculate function for transfer function
 @param[in,out] ctx points to an instance of transfer function
 @param[in] x controller output
 @return feedback
*/
A_EXTERN a_float_t a_tf_iter(a_tf_s *ctx, a_float_t x);

/*!
 @brief zero clear function for transfer function
 @param[in,out] ctx points to an instance of transfer function
*/
A_EXTERN a_tf_s *a_tf_zero(a_tf_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_TF */

#endif /* tf.h */
