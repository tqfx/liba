
/*!
 @file regress.h
 @brief regression
 @details https://en.wikipedia.org/wiki/Regression
*/

#ifndef LIBA_REGRESS_H
#define LIBA_REGRESS_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_regress regression
 @{
*/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief compute observation deviation from mean for regression
 @param[in] n number of samples, p[n], odm[n]
 @param[in] p response data, specified as a numeric vector
 @param[in,out] odm deviation, specified as a numeric vector
 @param[in] p_mean mean of response data
*/
A_EXTERN void a_regress_odm_(a_size n, a_real const *p, a_real *odm, a_real p_mean);

/*!
 @brief compute observation deviation from mean for regression
 @param[in] n number of samples, p[n], odm[n]
 @param[in] p response data, specified as a numeric vector
 @param[in,out] odm deviation, specified as a numeric vector
 @return mean of response data
*/
A_EXTERN a_real a_regress_odm(a_size n, a_real const *p, a_real *odm);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} a_regress */

#endif /* a/regress.h */
