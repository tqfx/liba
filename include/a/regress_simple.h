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

/* clang-format off */
#define A_REGRESS_SIMPLE_2(coef, bias) {a_real_c(coef), a_real_c(bias)}
/* clang-format on */
#define A_REGRESS_SIMPLE_1(coef) A_REGRESS_SIMPLE_2(coef, 0)
#define A_REGRESS_SIMPLE_0() A_REGRESS_SIMPLE_1(1)

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
A_EXTERN void a_regress_simple_init(a_regress_simple *ctx, a_real coef, a_real bias);

/*!
 @brief compute predicted value for simple linear regression
 @param[in] ctx points to an instance of simple linear regression
 @param[in] val independent variable
 @return predicted value
*/
A_EXTERN a_real a_regress_simple_eval(a_regress_simple const *ctx, a_real val);

/*!
 @brief compute predicted value for simple linear regression
 @param[in] ctx points to an instance of simple linear regression
 @param[in] val dependent variable
 @return predicted value
*/
A_EXTERN a_real a_regress_simple_evar(a_regress_simple const *ctx, a_real val);

/*!
 @brief ordinary least squares for simple linear regression
 @param[in,out] ctx points to an instance of simple linear regression
 @param[in] n number of samples, x[n], y[n]
 @param[in] x predictor data, specified as a numeric vector
 @param[in] y response data, specified as a numeric vector
 @param[in] x_mean mean of predictor data
 @param[in] y_mean mean of response data
*/
A_EXTERN void a_regress_simple_ols_(a_regress_simple *ctx, a_size n, a_real const *x, a_real const *y, a_real x_mean, a_real y_mean);

/*!
 @brief ordinary least squares for simple linear regression
 @param[in,out] ctx points to an instance of simple linear regression
 @param[in] n number of samples, x[n], y[n]
 @param[in] x predictor data, specified as a numeric vector
 @param[in] y response data, specified as a numeric vector
 @param[in] x_mean mean of predictor data
*/
A_EXTERN void a_regress_simple_olsx(a_regress_simple *ctx, a_size n, a_real const *x, a_real const *y, a_real x_mean);

/*!
 @brief ordinary least squares for simple linear regression
 @param[in,out] ctx points to an instance of simple linear regression
 @param[in] n number of samples, x[n], y[n]
 @param[in] x predictor data, specified as a numeric vector
 @param[in] y response data, specified as a numeric vector
 @param[in] y_mean mean of response data
*/
A_EXTERN void a_regress_simple_olsy(a_regress_simple *ctx, a_size n, a_real const *x, a_real const *y, a_real y_mean);

/*!
 @brief ordinary least squares for simple linear regression
 @param[in,out] ctx points to an instance of simple linear regression
 @param[in] n number of samples, x[n], y[n]
 @param[in] x predictor data, specified as a numeric vector
 @param[in] y response data, specified as a numeric vector
*/
A_EXTERN void a_regress_simple_ols(a_regress_simple *ctx, a_size n, a_real const *x, a_real const *y);

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
    a_real coef; /*!< regression coefficient */
    a_real bias; /*!< intercept */
#if defined(__cplusplus)
    A_INLINE void init(a_real a = 1, a_real b = 0)
    {
        a_regress_simple_init(this, a, b);
    }
    A_INLINE a_real eval(a_real val) const
    {
        return a_regress_simple_eval(this, val);
    }
    A_INLINE a_real evar(a_real val) const
    {
        return a_regress_simple_evar(this, val);
    }
    A_INLINE void ols(a_size n, a_real const *x, a_real const *y, a_real x_mean, a_real y_mean)
    {
        a_regress_simple_ols_(this, n, x, y, x_mean, y_mean);
    }
    A_INLINE void olsx(a_size n, a_real const *x, a_real const *y, a_real x_mean)
    {
        a_regress_simple_olsx(this, n, x, y, x_mean);
    }
    A_INLINE void olsy(a_size n, a_real const *x, a_real const *y, a_real y_mean)
    {
        a_regress_simple_olsy(this, n, x, y, y_mean);
    }
    A_INLINE void ols(a_size n, a_real const *x, a_real const *y)
    {
        a_regress_simple_ols(this, n, x, y);
    }
    A_INLINE void zero() { a_regress_simple_zero(this); }
#endif /* __cplusplus */
};

/*! @} a_regress_simple */

#endif /* a/regress_simple.h */
