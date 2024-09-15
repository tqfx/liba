
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
 @param[out] odm deviation, specified as a numeric vector
 @param[in] p response data, specified as a numeric vector
 @param[in] n number of samples, odm[n], p[n]
 @param[in] p_mean mean of response data
*/
A_EXTERN void a_regress_odm_(a_float *odm, a_float const *p, a_size n, a_float p_mean);

/*!
 @brief calculate observation deviation from mean for regression
 @param[out] odm deviation, specified as a numeric vector
 @param[in] p response data, specified as a numeric vector
 @param[in] n number of samples, odm[n], p[n]
 @return mean of response data
*/
A_EXTERN a_float a_regress_odm(a_float *odm, a_float const *p, a_size n);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} a_regress */

#endif /* a/regress.h */
