/*!
 @file linalg.h
 @brief linear algebra functions
*/

#ifndef LIBA_LINALG_H
#define LIBA_LINALG_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_linalg linear algebra functions
 @{
*/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief transpose an n x n square matrix in-place.
 @param[in,out] A an n x n square matrix
 @param[in] n order of square matrix A
 */
A_EXTERN void a_linalg_Tnn(a_float *A, a_uint n);

/*!
 @brief compute LU decomposition of a square matrix with partial pivoting.
 @details This function performs an LU decomposition on the given square matrix A,
 where L is a lower triangular matrix, and U is an upper triangular matrix.
 Partial pivoting is used to improve numerical stability during the decomposition process.
 The result is stored in the original matrix A, with L stored below, and U stored in the diagonal and above.
 Additionally, it calculates a permutation matrix P that records the row exchanges made during partial pivoting,
 and determines the sign of the permutation (which can be used to find the determinant's sign).
 @param[in,out] A an n x n square matrix.
  on input, contains the matrix to decompose. on output, contains the L and U matrices.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[out] p the row permutation indices after partial pivoting.
 @param[out] sign store the sign of the permutation (+1 or -1).
 @return 0 on success, or a non-zero error code if the decomposition fails.
  @retval -1 on failure, A is a singular matrix.
 */
A_EXTERN int a_linalg_plu(a_float *A, a_uint n, a_uint *p, int *sign);

/*!
 @brief construct the permutation matrix P from a permutation vector p.
 @param[in] p the row permutation indices after partial pivoting.
 @param[in] n the order of the square matrix that was decomposed.
 @param[out] P the output matrix where the permutation matrix will be stored.
*/
A_EXTERN void a_linalg_plu_get_P(a_uint const *p, a_uint n, a_float *P);

/*!
 @brief extract the lower triangular matrix L from matrix A.
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[in] n the order of the square matrix that was decomposed.
 @param[out] L the output matrix where the lower triangular matrix will be stored.
*/
A_EXTERN void a_linalg_plu_get_L(a_float const *A, a_uint n, a_float *L);

/*!
 @brief extract the upper triangular matrix U from matrix A.
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[in] n the order of the square matrix that was decomposed.
 @param[out] U the output matrix where the upper triangular matrix will be stored.
*/
A_EXTERN void a_linalg_plu_get_U(a_float const *A, a_uint n, a_float *U);

/*!
 @brief apply the permutation P to the vector b, producing Pb.
 @param[in] p the row permutation indices after partial pivoting.
 @param[in] n the order of the square matrix that was decomposed.
 @param[in] b the input vector of size n that will be permuted.
 @param[out] Pb the output vector where the permuted result will be stored.
*/
A_EXTERN void a_linalg_plu_apply(a_uint const *p, a_uint n, a_float const *b, a_float *Pb);

/*!
 @brief solve the lower triangular system Ly = Pb for y.
 @param[in] L the lower triangular matrix L, stored in row-major order.
 @param[in] n the order of the square matrix L (number of rows and columns).
 @param[in,out] y on input, contains the permuted vector Pb. on output, contains the solution vector y.
*/
A_EXTERN void a_linalg_plu_lower(a_float const *L, a_uint n, a_float *y);

/*!
 @brief solve the upper triangular system Ux = y for x.
 @param[in] U the upper triangular matrix U, stored in row-major order.
 @param[in] n the order of the square matrix U (number of rows and columns).
 @param[in,out] x on input, contains the vector y. on output, contains the solution vector x.
*/
A_EXTERN void a_linalg_plu_upper(a_float const *U, a_uint n, a_float *x);

/*!
 @brief solve the linear system Ax = b using LU decomposition with partial pivoting.
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] p the permutation indices obtained during LU decomposition.
 @param[in] b the input vector b of the linear system.
 @param[out] x the output vector x where the solution will be stored.
*/
A_EXTERN void a_linalg_plu_solve(a_float const *A, a_uint n, a_uint const *p, a_float const *b, a_float *x);

/*!
 @brief compute the inverse of a matrix using its LU decomposition and permutation matrix.
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] p the permutation indices obtained during LU decomposition.
 @param[in] b a pre-allocated temporary buffer of size n for intermediate computations.
 @param[out] I the output matrix where the inverse of A will be stored.
*/
A_EXTERN void a_linalg_plu_inv(a_float const *A, a_uint n, a_uint const *p, a_float *b, a_float *I);

/*!
 @brief compute the determinant of a matrix using its LU decomposition.
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] sign the sign of the permutation matrix P (+1 or -1).
 @return the determinant of matrix A.
*/
A_EXTERN a_float a_linalg_plu_det(a_float const *A, a_uint n, int sign);

/*!
 @brief compute the natural logarithm of the absolute value of the determinant of a matrix using its LU decomposition.
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @return the natural logarithm of the absolute value of the determinant.
*/
A_EXTERN a_float a_linalg_plu_lndet(a_float const *A, a_uint n);

/*!
 @brief compute the sign of the determinant of a matrix using its LU decomposition.
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] sign the sign of the permutation matrix P (+1 or -1).
 @return the sign of the determinant: -1, 0, +1.
*/
A_EXTERN int a_linalg_plu_sgndet(a_float const *A, a_uint n, int sign);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} a_linalg */

#endif /* a/linalg.h */
