/*!
 @file poly.h
 @brief polynomial
*/

#ifndef LIBA_POLY_H
#define LIBA_POLY_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_poly polynomial
 @{
*/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
#if defined(LIBA_POLY_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_POLY_C */

/*!
 @brief swap between \f$ \sum_{i=0}^{n}a_{i}x^{i} \f$ and \f$ \sum_{i=0}^{n}a_{i}x^{n-i} \f$
*/
#if !defined A_HAVE_INLINE || defined(LIBA_POLY_C)
A_EXTERN void a_poly_swap(a_real *a, a_size n);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_poly_swap_(a_real *a, a_real *b);
#if defined(A_HAVE_INLINE) || defined(LIBA_POLY_C)
A_INTERN void a_poly_swap(a_real *a, a_size n)
{
    if (n > 1) { a_poly_swap_(a, a + n); }
}
#endif /* A_HAVE_INLINE */

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
#if !defined A_HAVE_INLINE || defined(LIBA_POLY_C)
A_EXTERN a_real a_poly_eval(a_real const *a, a_size n, a_real x);
#endif /* A_HAVE_INLINE */
A_EXTERN a_real a_poly_eval_(a_real const *a, a_real const *b, a_real x);
#if defined(A_HAVE_INLINE) || defined(LIBA_POLY_C)
A_INTERN a_real a_poly_eval(a_real const *a, a_size n, a_real x)
{
    return n ? a_poly_eval_(a, a + n, x) : 0;
}
#endif /* A_HAVE_INLINE */

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
#if !defined A_HAVE_INLINE || defined(LIBA_POLY_C)
A_EXTERN a_real a_poly_evar(a_real const *a, a_size n, a_real x);
#endif /* A_HAVE_INLINE */
A_EXTERN a_real a_poly_evar_(a_real const *a, a_real const *b, a_real x);
#if defined(A_HAVE_INLINE) || defined(LIBA_POLY_C)
A_INTERN a_real a_poly_evar(a_real const *a, a_size n, a_real x)
{
    return n ? a_poly_evar_(a, a + n, x) : 0;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief compute the matrix A^T * A for polynomial fitting.
 @details This function computes the product of the transpose of a design matrix A with itself (A^T * A),
 which is used in the normal equations for polynomial fitting using least squares method. The matrix A
 is implicitly defined by the input vector x, where each element of x corresponds to a data point.
 @param[in] m number of data points (rows in matrix A).
 @param[in] x points to an array of size m containing the data points.
 @param[in] n degree of the polynomial plus one (columns in matrix A).
 @param[out] A points to an array of size n*n where the result A^T * A will be stored.
*/
A_EXTERN void a_poly_xTx(a_uint m, a_real const *x, a_uint n, a_real *A);

/*!
 @brief compute the vector A^T * y for polynomial fitting.
 @details This function computes the product of the transpose of a design matrix A with a vector y (A^T * y),
 which is used in the normal equations for polynomial fitting using least squares method. The matrix A
 is implicitly defined by the input vector x, where each element of x corresponds to a data point.
 @param[in] m number of data points (rows in matrix A).
 @param[in] x points to an array of size m containing the data points.
 @param[in] y points to an array of size m containing the target values.
 @param[in] n degree of the polynomial plus one (columns in matrix A).
 @param[out] b points to an array of size n where the result A^T * y will be stored.
 */
A_EXTERN void a_poly_xTy(a_uint m, a_real const *x, a_real const *y, a_uint n, a_real *b);

#if defined(LIBA_POLY_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_POLY_C */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} a_poly */

#endif /* a/poly.h */
