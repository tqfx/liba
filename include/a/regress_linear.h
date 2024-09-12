/*!
 @file regress_linear.h
 @brief linear regression
 @details https://en.wikipedia.org/wiki/Linear_regression
*/

#ifndef LIBA_REGRESS_LINEAR_H
#define LIBA_REGRESS_LINEAR_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_regress_linear linear regression
 @{
*/

typedef struct a_regress_linear a_regress_linear;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief initialize for regress linear
 @param[in,out] ctx points to an instance of regress linear
 @param[in] coef_p points to regression coefficients
 @param[in] coef_n number of regression coefficients
 @param[in] bias intercept
*/
A_EXTERN void a_regress_linear_init(a_regress_linear *ctx, a_float *coef_p, a_size coef_n, a_float bias);

/*!
 @brief calculate for regress linear
 @param[in] ctx points to an instance of regress linear
 @param[in] val input variables
 @return predicted value
*/
A_EXTERN a_float a_regress_linear_eval(a_regress_linear const *ctx, a_float const *val);

/*!
 @brief stochastic gradient descent for positional regress linear
 @param[in,out] ctx points to an instance of regress linear
 @param[in] alpha learning rate for gradient descent
 @param[in] y response data
 @param[in] x predictor data
 @return residual
*/
A_EXTERN a_float a_regress_linear_sdg(a_regress_linear *ctx, a_float alpha, a_float y, a_float const *x);

/*!
 @brief stochastic gradient descent for positional regress linear
 @param[in,out] ctx points to an instance of regress linear
 @param[in] alpha learning rate for gradient descent
 @param[in] y response data, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, y[n], x[coef_n*n]
 @param[in] error temporary buffer for residuals
 @return sum of absolute residuals
*/
A_EXTERN a_float a_regress_linear_sdg1(a_regress_linear *ctx, a_float alpha, a_float const *y, a_float const *x, a_size n, a_float *error);

/*!
 @brief stochastic gradient descent for positional regress linear
 @param[in,out] ctx points to an instance of regress linear
 @param[in] alpha learning rate for gradient descent
 @param[in] y response data, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, y[n], x[n][coef_n]
 @param[in] error temporary buffer for residuals
 @return sum of absolute residuals
*/
A_EXTERN a_float a_regress_linear_sdg2(a_regress_linear *ctx, a_float alpha, a_float const *y, a_float const *const *x, a_size n, a_float *error);

/*!
 @brief batch gradient descent for positional regress linear
 @param[in,out] ctx points to an instance of regress linear
 @param[in] alpha learning rate for gradient descent
 @param[in] y response data, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, y[n], x[coef_n*n]
 @param[in] error temporary buffer for residuals
 @return sum of absolute residuals
*/
A_EXTERN a_float a_regress_linear_bdg1(a_regress_linear *ctx, a_float alpha, a_float const *y, a_float const *x, a_size n, a_float *error);

/*!
 @brief batch gradient descent for positional regress linear
 @param[in,out] ctx points to an instance of regress linear
 @param[in] alpha learning rate for gradient descent
 @param[in] y response data, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, y[n], x[n][coef_n]
 @param[in] error temporary buffer for residuals
 @return sum of absolute residuals
*/
A_EXTERN a_float a_regress_linear_bdg2(a_regress_linear *ctx, a_float alpha, a_float const *y, a_float const *const *x, a_size n, a_float *error);

/*!
 @brief zeroing for regress linear
 @param[in,out] ctx points to an instance of regress linear
*/
A_EXTERN void a_regress_linear_zero(a_regress_linear *ctx);

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_regress_linear regress_linear;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for regress linear
*/
struct a_regress_linear
{
    a_float *coef_p; // points to regression coefficients
    a_size coef_n; // number of regression coefficients
    a_float bias; // intercept
#if defined(__cplusplus)
    A_INLINE void init(a_float *p, a_size n, a_float b = 0)
    {
        a_regress_linear_init(this, p, n, b);
    }
    A_INLINE a_float eval(a_float const *val) const
    {
        return a_regress_linear_eval(this, val);
    }
    A_INLINE a_float sdg(a_float alpha, a_float y, a_float const *x)
    {
        return a_regress_linear_sdg(this, alpha, y, x);
    }
    A_INLINE a_float sdg1(a_float alpha, a_float const *y, a_float const *x, a_size n, a_float *error)
    {
        return a_regress_linear_bdg1(this, alpha, y, x, n, error);
    }
    A_INLINE a_float sdg2(a_float alpha, a_float const *y, a_float const *const *x, a_size n, a_float *error)
    {
        return a_regress_linear_bdg2(this, alpha, y, x, n, error);
    }
    A_INLINE a_float bdg1(a_float alpha, a_float const *y, a_float const *x, a_size n, a_float *error)
    {
        return a_regress_linear_bdg1(this, alpha, y, x, n, error);
    }
    A_INLINE a_float bdg2(a_float alpha, a_float const *y, a_float const *const *x, a_size n, a_float *error)
    {
        return a_regress_linear_bdg2(this, alpha, y, x, n, error);
    }
    A_INLINE void zero() { a_regress_linear_zero(this); }
#endif /* __cplusplus */
};

/*! @} a_regress_linear */

#endif /* a/regress_linear.h */
