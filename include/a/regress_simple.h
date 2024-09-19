/*!
 @file regress_simple.h
 @brief simple linear regression
 @details https://en.wikipedia.org/wiki/Simple_linear_regression
*/

#ifndef LIBA_REGRESS_SIMPLE_H
#define LIBA_REGRESS_SIMPLE_H

#include "a.h"

/*!
 @ingroup a_regress
 @addtogroup a_regress_simple simple linear regression
 @{
*/

typedef struct a_regress_simple a_regress_simple;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief initialize for simple linear regression
 @param[in,out] ctx points to an instance of simple linear regression
 @param[in] coef regression coefficient
 @param[in] bias intercept
*/
A_EXTERN void a_regress_simple_init(a_regress_simple *ctx, a_float coef, a_float bias);

/*!
 @brief calculate predicted value for simple linear regression
 @param[in] ctx points to an instance of simple linear regression
 @param[in] val input variable
 @return predicted value
*/
A_EXTERN a_float a_regress_simple_eval(a_regress_simple const *ctx, a_float val);

/*!
 @brief ordinary least squares method for simple linear regression
 @param[in,out] ctx points to an instance of simple linear regression
 @param[in] y response data, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, y[n], x[n]
 @param[in] y_mean mean of response data
 @param[in] x_mean mean of predictor data
*/
A_EXTERN void a_regress_simple_olsm_(a_regress_simple *ctx, a_float const *y, a_float const *x, a_size n, a_float y_mean, a_float x_mean);

/*!
 @brief ordinary least squares method for simple linear regression
 @param[in,out] ctx points to an instance of simple linear regression
 @param[in] y response data, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, y[n], x[n]
*/
A_EXTERN void a_regress_simple_olsm(a_regress_simple *ctx, a_float const *y, a_float const *x, a_size n);

/*!
 @brief zeroing for simple linear regression
 @param[in,out] ctx points to an instance of simple linear regression
*/
A_EXTERN void a_regress_simple_zero(a_regress_simple *ctx);

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_regress_simple regress_simple;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for simple linear regression
*/
struct a_regress_simple
{
    a_float coef; // regression coefficient
    a_float bias; // intercept
#if defined(__cplusplus)
    A_INLINE void init(a_float a, a_float b = 0)
    {
        a_regress_simple_init(this, a, b);
    }
    A_INLINE a_float eval(a_float val) const
    {
        return a_regress_simple_eval(this, val);
    }
    A_INLINE void olsm_(a_float const *y, a_float const *x, a_size n, a_float y_mean, a_float x_mean)
    {
        a_regress_simple_olsm_(this, y, x, n, y_mean, x_mean);
    }
    A_INLINE void olsm(a_float const *y, a_float const *x, a_size n)
    {
        a_regress_simple_olsm(this, y, x, n);
    }
    A_INLINE void zero() { a_regress_simple_zero(this); }
#endif /* __cplusplus */
};

/*! @} a_regress_simple */

#endif /* a/regress_simple.h */
