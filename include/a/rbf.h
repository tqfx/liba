/*!
 @file rbf.h
 @brief radial basis function
*/

#ifndef LIBA_RBF_H
#define LIBA_RBF_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_RBF radial basis function
 @{
*/

/*!
 @brief instance structure for radial basis function
*/
typedef struct a_rbf_s
{
    a_float_t *input_p; //!< points to input layer
    a_size_t input_n; //!< number of input layer
    a_float_t *center_p; //!< points to center array
    a_size_t center_n; //!< number of center array
    a_float_t *height_p; //!< points to height array
    a_size_t height_n; //!< number of height array
    a_float_t *hidden_p; //!< points to hidden layer
    a_size_t hidden_n; //!< number of hidden layer
    a_float_t *output_p; //!< points to output layer
    a_size_t output_n; //!< number of output layer
    a_float_t *weight; //!< points to output weight
    a_float_t *deltaw; //!< points to delta weight
    a_float_t learn; //!< learning rate
    a_float_t alpha; //!< momentum factor
} a_rbf_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief calculate function for radial basis function
 @param[in] ctx points to an instance of radial basis function
 @return radial basis function output
*/
A_EXTERN a_float_t const *a_rbf_iter(a_rbf_s const *ctx);

/*!
 @brief tuning function for radial basis function
 @param[in] ctx points to an instance of radial basis function
 @param[in] out points to the desired output buffer
*/
A_EXTERN void a_rbf_tune(a_rbf_s const *ctx, a_float_t const *out);

/*!
 @brief zero clear function for radial basis function
 @param[in] ctx points to an instance of radial basis function
*/
A_EXTERN void a_rbf_zero(a_rbf_s const *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_RBF */

#endif /* a/rbf.h */
