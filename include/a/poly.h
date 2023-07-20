/*!
 @file poly.h
 @brief polynomial
*/

#ifndef LIBA_POLY_H
#define LIBA_POLY_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_POLY polynomial
 @{
*/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief swap between \f$ \sum_{i=0}^{n}a_{i}x^{i} \f$ and \f$ \sum_{i=0}^{n}a_{i}x^{n-i} \f$
*/
A_EXTERN a_float_t *a_poly_swap(a_float_t *a, a_size_t n);

/*!
 @brief horner function for polynomial \f$ \sum_{i=0}^{n}a_{i}x^{i} \f$
 \f[
  \left\{\begin{array}{l}
  S_n = a_n\\
  S_i = xS_{i+1} + a_i,\quad(i=n-1,n-2,\cdots,1,0)\\
  P(x) = S_0
  \end{array}\right.
 \f]
*/
A_EXTERN a_float_t a_poly_eval(a_float_t const *a, a_size_t n, a_float_t x);
A_EXTERN a_float_t *a_poly_evaln(a_float_t const *a, a_size_t n, a_float_t const *ptr, a_size_t num, a_float_t *out);

/*!
 @brief horner function for polynomial \f$ \sum_{i=0}^{n}a_{i}x^{n-i} \f$
 \f[
  \left\{\begin{array}{l}
  S_0 = a_0\\
  S_i = xS_{i-1} + a_i,\quad(i=1,2,\cdots,n-1,n)\\
  P(x) = S_n
  \end{array}\right.
 \f]
*/
A_EXTERN a_float_t a_poly_evar(a_float_t const *a, a_size_t n, a_float_t x);
A_EXTERN a_float_t *a_poly_evarn(a_float_t const *a, a_size_t n, a_float_t const *ptr, a_size_t num, a_float_t *out);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_POLY */

#endif /* a/poly.h */
