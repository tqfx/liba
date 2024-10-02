/*!
 @file regress_linear.h
 @brief linear regression
 @details https://en.wikipedia.org/wiki/Linear_regression
*/

#ifndef LIBA_REGRESS_LINEAR_H
#define LIBA_REGRESS_LINEAR_H

#include "a.h"

/*!
 @ingroup a_regress
 @addtogroup a_regress_linear linear regression
 @{
*/

typedef struct a_regress_linear a_regress_linear;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief initialize for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[in] coef_p points to regression coefficients
 @param[in] coef_n number of regression coefficients
 @param[in] bias intercept
*/
A_EXTERN void a_regress_linear_init(a_regress_linear *ctx, a_float *coef_p, a_size coef_n, a_float bias);

/*!
 @brief calculate predicted value for linear regression
 @param[in] ctx points to an instance of linear regression
 @param[in] val independent variables
 @return predicted value
*/
A_EXTERN a_float a_regress_linear_eval(a_regress_linear const *ctx, a_float const *val);

/*!
 @brief calculate residuals for linear regression
 @param[in] ctx points to an instance of linear regression
 @param[in] n number of samples, x[n*coef_n], y[n], err[n]
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] y response data, specified as a numeric vector
 @param[in,out] err residuals, specified as a numeric vector
*/
A_EXTERN void a_regress_linear_err(a_regress_linear const *ctx, a_size n, a_float const *x, a_float const *y, a_float *err);

/*!
 @brief calculate prediction deviation from mean for linear regression
 @param[in] ctx points to an instance of linear regression
 @param[in] n number of samples, x[n*coef_n], pdm[n]
 @param[in] x predictor data, specified as a numeric matrix
 @param[in,out] pdm deviation, specified as a numeric vector
 @param[in] y_mean mean of response data
*/
A_EXTERN void a_regress_linear_pdm(a_regress_linear const *ctx, a_size n, a_float const *x, a_float *pdm, a_float y_mean);

/*!
 @brief gradient descent for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[in] input predictor data, specified as a numeric vector
 @param[in] error residual, specified as a numeric scalar
 @param[in] alpha learning rate for gradient descent
*/
A_EXTERN void a_regress_linear_gd(a_regress_linear *ctx, a_float const *input, a_float error, a_float alpha);

/*!
 @brief stochastic gradient descent for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[in] n number of samples, x[n*coef_n], y[n]
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] y response data, specified as a numeric vector
 @param[in] alpha learning rate for gradient descent
*/
A_EXTERN void a_regress_linear_sgd(a_regress_linear *ctx, a_size n, a_float const *x, a_float const *y, a_float alpha);

/*!
 @brief batch gradient descent for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[in] n number of samples, x[n*coef_n], err[n]
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] err residuals, specified as a numeric vector
 @param[in] alpha learning rate for gradient descent
*/
A_EXTERN void a_regress_linear_bgd(a_regress_linear *ctx, a_size n, a_float const *x, a_float const *err, a_float alpha);

/*!
 @brief mini-batch gradient descent for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[in] n number of samples, x[n*coef_n], y[n], err[n]
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] y response data, specified as a numeric vector
 @param[in,out] err residuals, specified as a numeric vector
 @param[in] delta threshold for gradient descent value
 @param[in] lrmin minimum learning rate of iterations
 @param[in] lrmax maximum learning rate of iterations
 @param[in] lrtim total number of learning rate steps
 @param[in] epoch maximum number of epochs
 @param[in] batch batch size of data
 @return change in loss function
*/
A_EXTERN a_float a_regress_linear_mgd(a_regress_linear *ctx, a_size n, a_float const *x, a_float const *y, a_float *err,
                                      a_float delta, a_float lrmax, a_float lrmin, a_size lrtim, a_size epoch, a_size batch);

/*!
 @brief zeroing for linear regression
 @param[in,out] ctx points to an instance of linear regression
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
 @brief instance structure for linear regression
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
    A_INLINE void err(a_size n, a_float const *x, a_float const *y, a_float *err) const
    {
        a_regress_linear_err(this, n, x, y, err);
    }
    A_INLINE void pdm(a_size n, a_float const *x, a_float *pdm, a_float y_mean) const
    {
        a_regress_linear_pdm(this, n, x, pdm, y_mean);
    }
    A_INLINE void gd(a_float const *input, a_float error, a_float alpha)
    {
        a_regress_linear_gd(this, input, error, alpha);
    }
    A_INLINE void sgd(a_size n, a_float const *x, a_float const *y, a_float alpha)
    {
        a_regress_linear_sgd(this, n, x, y, alpha);
    }
    A_INLINE void bgd(a_size n, a_float const *x, a_float const *err, a_float alpha)
    {
        a_regress_linear_bgd(this, n, x, err, alpha);
    }
    A_INLINE a_float mgd(a_size n, a_float const *x, a_float const *y, a_float *err, a_float delta,
                         a_float lrmax, a_float lrmin, a_size lrtim, a_size epoch, a_size batch)
    {
        return a_regress_linear_mgd(this, n, x, y, err, delta, lrmax, lrmin, lrtim, epoch, batch);
    }
    A_INLINE void zero() { a_regress_linear_zero(this); }
#endif /* __cplusplus */
};

/*! @} a_regress_linear */

#endif /* a/regress_linear.h */
