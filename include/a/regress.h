
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
 @brief calculate observation deviation from mean for regression
 @param[in] n number of samples, p[n], odm[n]
 @param[in] p response data, specified as a numeric vector
 @param[in,out] odm deviation, specified as a numeric vector
 @param[in] p_mean mean of response data
*/
A_EXTERN void a_regress_odm_(a_size n, a_float const *p, a_float *odm, a_float p_mean);

/*!
 @brief calculate observation deviation from mean for regression
 @param[in] n number of samples, p[n], odm[n]
 @param[in] p response data, specified as a numeric vector
 @param[in,out] odm deviation, specified as a numeric vector
 @return mean of response data
*/
A_EXTERN a_float a_regress_odm(a_size n, a_float const *p, a_float *odm);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} a_regress */

#endif /* a/regress.h */
