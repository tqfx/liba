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

typedef struct a_rbf a_rbf;

#if defined(__cplusplus)
namespace a
{
typedef struct a_rbf rbf;
} /* namespace a */
extern "C" {
#endif /* __cplusplus */

/*!
 @brief calculate for radial basis function
 @param[in] ctx points to an instance of radial basis function
 @return radial basis function output
*/
A_EXTERN a_float const *a_rbf_iter(a_rbf const *ctx);

/*!
 @brief tuning for radial basis function
 @param[in] ctx points to an instance of radial basis function
 @param[in] out points to the desired output buffer
*/
A_EXTERN void a_rbf_tune(a_rbf const *ctx, a_float const *out);

/*!
 @brief zeroing for radial basis function
 @param[in] ctx points to an instance of radial basis function
*/
A_EXTERN void a_rbf_zero(a_rbf const *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief instance structure for radial basis function
*/
struct a_rbf
{
    a_float *input_p; //!< points to input layer
    a_size input_n; //!< number of input layer
    a_float *center_p; //!< points to center array
    a_size center_n; //!< number of center array
    a_float *height_p; //!< points to height array
    a_size height_n; //!< number of height array
    a_float *hidden_p; //!< points to hidden layer
    a_size hidden_n; //!< number of hidden layer
    a_float *output_p; //!< points to output layer
    a_size output_n; //!< number of output layer
    a_float *weight; //!< points to output weight
    a_float *deltaw; //!< points to delta weight
    a_float learn; //!< learning rate
    a_float alpha; //!< momentum factor
#if defined(__cplusplus)
    A_INLINE a_float const *operator()()
    {
        return a_rbf_iter(this);
    }
    A_INLINE void tune(a_float const *out)
    {
        a_rbf_tune(this, out);
    }
    A_INLINE void zero() { a_rbf_zero(this); }
#endif /* __cplusplus */
};

/*! @} A_RBF */

#endif /* a/rbf.h */
