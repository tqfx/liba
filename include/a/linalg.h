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
 @param[in] n the order of square matrix A.
 @param[in,out] A an n x n square matrix.
 */
A_EXTERN void a_real_T1(a_uint n, a_real *A);

/*!
 @brief transpose a given m x n matrix A into an n x m matrix T.
 @param[in] m the rows in the input matrix A.
 @param[in] n the columns in the input matrix A.
 @param[in] A the input matrix A (m x n), stored in row-major order.
 @param[out] T the output matrix where the transposed matrix T (n x m) will be stored.
*/
A_EXTERN void a_real_T2(a_uint m, a_uint n, a_real const *__restrict A, a_real *__restrict T);

/*!
 @brief generate an m x n matrix with ones on the diagonal and zeros elsewhere.
 @param[in] n the order of the diagonal matrix (n x n).
 @param[out] E the output matrix where the result will be stored.
*/
A_EXTERN void a_real_eye1(a_uint n, a_real *E);

/*!
 @brief generate an m x n matrix with ones on the diagonal and zeros elsewhere.
 @param[in] m the rows in the input matrix A.
 @param[in] n the columns in the input matrix A.
 @param[out] E the output matrix where the result will be stored.
*/
A_EXTERN void a_real_eye2(a_uint m, a_uint n, a_real *E);

/*!
 @brief generate an m x n matrix with ones in the lower triangular part and zeros elsewhere.
 @param[in] n the order of the diagonal matrix (n x n).
 @param[out] L the output matrix where the result will be stored.
*/
A_EXTERN void a_real_tri1(a_uint n, a_real *L);

/*!
 @brief generate an m x n matrix with ones in the lower triangular part and zeros elsewhere.
 @param[in] m the rows in the input matrix A.
 @param[in] n the columns in the input matrix A.
 @param[out] L the output matrix where the result will be stored.
*/
A_EXTERN void a_real_tri2(a_uint m, a_uint n, a_real *L);

/*!
 @brief compute a diagonal matrix from a given diagonal vector.
 @param[in] n the order of the diagonal matrix (n x n).
 @param[in] a the input diagonal vector.
 @param[out] A the output diagonal matrix.
*/
A_EXTERN void a_real_diag(a_uint n, a_real const *__restrict a, a_real *__restrict A);

/*!
 @brief extract a diagonal vector from a given diagonal matrix.
 @param[in] n the order of the diagonal matrix (n x n).
 @param[in] A the input diagonal matrix.
 @param[out] a the output diagonal vector.
*/
A_EXTERN void a_real_diag1(a_uint n, a_real const *__restrict A, a_real *__restrict a);

/*!
 @brief extract a diagonal vector from a given diagonal matrix.
 @param[in] m the rows in the input matrix A.
 @param[in] n the columns in the input matrix A.
 @param[in] A the input diagonal matrix.
 @param[out] a the output diagonal vector.
*/
A_EXTERN void a_real_diag2(a_uint m, a_uint n, a_real const *__restrict A, a_real *__restrict a);

/*!
 @brief extract the lower triangular part of a square matrix, including the diagonal.
 @param[in] n the order of square matrix A.
 @param[in] A the input matrix A (n x n), stored in row-major order.
 @param[out] L the output matrix where the lower triangular L (n x n) will be stored.
*/
A_EXTERN void a_real_triL(a_uint n, a_real const *__restrict A, a_real *__restrict L);

/*!
 @brief extract the lower triangular part of a square matrix, set the diagonal to 1.
 @param[in] n the order of square matrix A.
 @param[in] A the input matrix A (n x n), stored in row-major order.
 @param[out] L the output matrix where the lower triangular L (n x n) will be stored.
*/
A_EXTERN void a_real_triL1(a_uint n, a_real const *__restrict A, a_real *__restrict L);

/*!
 @brief extract the lower triangular part of a square matrix, including the diagonal.
 @param[in] m the rows in the input matrix A.
 @param[in] n the columns in the input matrix A.
 @param[in] A the input matrix A (m x n), stored in row-major order.
 @param[out] L the output matrix where the lower triangular L (m x n) will be stored.
*/
A_EXTERN void a_real_triL2(a_uint m, a_uint n, a_real const *__restrict A, a_real *__restrict L);

/*!
 @brief extract the upper triangular part of a square matrix, including the diagonal.
 @param[in] n the order of square matrix A.
 @param[in] A the input matrix A (n x n), stored in row-major order.
 @param[out] U the output matrix where the upper triangular U (n x n) will be stored.
*/
A_EXTERN void a_real_triU(a_uint n, a_real const *__restrict A, a_real *__restrict U);

/*!
 @brief extract the upper triangular part of a square matrix, set the diagonal to 1.
 @param[in] n the order of square matrix A.
 @param[in] A the input matrix A (n x n), stored in row-major order.
 @param[out] U the output matrix where the upper triangular U (n x n) will be stored.
*/
A_EXTERN void a_real_triU1(a_uint n, a_real const *__restrict A, a_real *__restrict U);

/*!
 @brief extract the upper triangular part of a square matrix, including the diagonal.
 @param[in] m the rows in the input matrix A.
 @param[in] n the columns in the input matrix A.
 @param[in] A the input matrix A (m x n), stored in row-major order.
 @param[out] U the output matrix where the upper triangular U (m x n) will be stored.
*/
A_EXTERN void a_real_triU2(a_uint m, a_uint n, a_real const *__restrict A, a_real *__restrict U);

/*!
 @brief multiply two matrices X and Y, storing the result in Z.
 \f{aligned}{
  \pmb Z_{rc}&=\pmb X_{rn}\pmb Y_{nc}
  \\&=
  \begin{bmatrix}
  x_{11} & \cdots & x_{1n} \\
  \vdots & \ddots & \vdots \\
  x_{r1} & \cdots & x_{rn} \\
  \end{bmatrix}
  \begin{bmatrix}
  y_{11} & \cdots & y_{1c} \\
  \vdots & \ddots & \vdots \\
  y_{n1} & \cdots & y_{nc} \\
  \end{bmatrix}
  \\&=
  \begin{bmatrix}
  (x_{11}y_{11}+\ldots+x_{1n}y_{n1}) & \cdots & (x_{11}y_{1c}+\ldots+x_{1n}y_{nc}) \\
  \vdots & \ddots & \vdots \\
  (x_{r1}y_{11}+\ldots+x_{rn}y_{n1}) & \cdots & (x_{r1}y_{1c}+\ldots+x_{rn}y_{nc}) \\
  \end{bmatrix}
 \f}
 @param[in] row rows matrix Z and rows in matrix X.
 @param[in] c_r columns in matrix X and rows in matrix Y.
 @param[in] col columns in matrix Z and columns in matrix Y.
 @param[in] X the first input matrix.
 @param[in] Y the second input matrix.
 @param[out] Z the output matrix where the result will be stored.
*/
A_EXTERN void a_real_mulmm(a_uint row, a_uint c_r, a_uint col, a_real const *__restrict X, a_real const *__restrict Y, a_real *__restrict Z);

/*!
 @brief multiply the transpose of matrix X with matrix Y, storing the result in Z.
 \f{aligned}{
  \pmb Z_{rc}&=\pmb X_{nr}^{T}\pmb Y_{nc}
  \\&=
  \begin{bmatrix}
  x_{11} & \cdots & x_{1r} \\
  \vdots & \ddots & \vdots \\
  x_{n1} & \cdots & x_{nr} \\
  \end{bmatrix}^T
  \begin{bmatrix}
  y_{11} & \cdots & y_{1c} \\
  \vdots & \ddots & \vdots \\
  y_{n1} & \cdots & y_{nc} \\
  \end{bmatrix}
  \\&=
  \begin{bmatrix}
  (x_{11}y_{11}+\ldots+x_{n1}y_{n1}) & \cdots & (x_{11}y_{1c}+\ldots+x_{n1}y_{nc}) \\
  \vdots & \ddots & \vdots \\
  (x_{1r}y_{11}+\ldots+x_{nr}y_{n1}) & \cdots & (x_{1r}y_{1c}+\ldots+x_{nr}y_{nc}) \\
  \end{bmatrix}
  \\&=
  \begin{bmatrix}
  x_{11}y_{11} & \cdots & x_{11}y_{1c} \\
  \vdots & \ddots & \vdots \\
  x_{1r}y_{11} & \cdots & x_{1r}y_{1c} \\
  \end{bmatrix}+\cdots+
  \begin{bmatrix}
  x_{n1}y_{n1} & \cdots & x_{n1}y_{nc} \\
  \vdots & \ddots & \vdots \\
  x_{nr}y_{n1} & \cdots & x_{nr}y_{nc} \\
  \end{bmatrix}
 \f}
 @param[in] c_r rows in matrix X and rows in matrix Y.
 @param[in] row rows in matrix Z and columns in matrix X.
 @param[in] col columns in matrix Z and columns in matrix Y.
 @param[in] X the first input matrix that will be transposed during multiplication.
 @param[in] Y the second input matrix.
 @param[out] Z the output matrix where the result will be stored.
*/
A_EXTERN void a_real_mulTm(a_uint c_r, a_uint row, a_uint col, a_real const *__restrict X, a_real const *__restrict Y, a_real *__restrict Z);

/*!
 @brief multiply matrix X with the transpose of matrix Y, storing the result in Z.
 \f{aligned}{
  \pmb Z_{rc}&=\pmb X_{rn}\pmb Y_{cn}^T
  \\&=
  \begin{bmatrix}
  x_{11} & \cdots & x_{1n} \\
  \vdots & \ddots & \vdots \\
  x_{r1} & \cdots & x_{rn} \\
  \end{bmatrix}
  \begin{bmatrix}
  y_{11} & \cdots & y_{1n} \\
  \vdots & \ddots & \vdots \\
  y_{c1} & \cdots & y_{cn} \\
  \end{bmatrix}^T
  \\&=
  \begin{bmatrix}
  (x_{11}y_{11}+\ldots+x_{1n}y_{1n}) & \cdots & (x_{11}y_{c1}+\ldots+x_{1n}y_{cn}) \\
  \vdots & \ddots & \vdots \\
  (x_{r1}y_{11}+\ldots+x_{rn}y_{1n}) & \cdots & (x_{r1}y_{c1}+\ldots+x_{rn}y_{cn}) \\
  \end{bmatrix}
 \f}
 @param[in] row rows matrix Z and rows in matrix X.
 @param[in] col columns in matrix Z and rows in matrix Y.
 @param[in] c_r columns in matrix X and columns in matrix Y.
 @param[in] X the first input matrix.
 @param[in] Y the second input matrix that will be transposed during multiplication.
 @param[out] Z the output matrix where the result will be stored.
*/
A_EXTERN void a_real_mulmT(a_uint row, a_uint col, a_uint c_r, a_real const *__restrict X, a_real const *__restrict Y, a_real *__restrict Z);

/*!
 @brief multiply the transpose of matrix X with the transpose of matrix Y, storing the result in Z.
 \f{aligned}{
  \pmb Z_{rc}&=\pmb X_{nr}^T\pmb Y_{cn}^T
  \\&=
  \begin{bmatrix}
  x_{11} & \cdots & x_{1r} \\
  \vdots & \ddots & \vdots \\
  x_{n1} & \cdots & x_{nr} \\
  \end{bmatrix}^T
  \begin{bmatrix}
  y_{11} & \cdots & y_{1n} \\
  \vdots & \ddots & \vdots \\
  y_{c1} & \cdots & y_{cn} \\
  \end{bmatrix}^T
  \\&=
  \begin{bmatrix}
  (x_{11}y_{11}+\ldots+x_{n1}y_{1n}) & \cdots & (x_{11}y_{c1}+\ldots+x_{n1}y_{cn}) \\
  \vdots & \ddots & \vdots \\
  (x_{1r}y_{11}+\ldots+x_{nr}y_{1n}) & \cdots & (x_{1r}y_{c1}+\ldots+x_{nr}y_{cn}) \\
  \end{bmatrix}
 \f}
 @param[in] row rows matrix Z and columns in matrix X.
 @param[in] c_r rows in matrix X and columns in matrix Y.
 @param[in] col columns in matrix Z and rows in matrix Y.
 @param[in] X the first input matrix that will be transposed during multiplication.
 @param[in] Y the second input matrix that will be transposed during multiplication.
 @param[out] Z the output matrix where the result will be stored.
*/
A_EXTERN void a_real_mulTT(a_uint row, a_uint c_r, a_uint col, a_real const *__restrict X, a_real const *__restrict Y, a_real *__restrict Z);

/*!
 @brief compute LU decomposition of a square matrix with partial pivoting.
 @details This function performs an LU decomposition on the given square matrix A,
 where L is a lower triangular matrix, and U is an upper triangular matrix.
 Partial pivoting is used to improve numerical stability during the decomposition process.
 The result is stored in the original matrix A, with L stored below, and U stored in the diagonal and above.
 Additionally, it computes a permutation matrix P that records the row exchanges made during partial pivoting,
 and determines the sign of the permutation (which can be used to find the determinant's sign).
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in,out] A an n x n square matrix.
  on input, contains the matrix to decompose. on output, contains the L and U matrices.
 @param[out] p the row permutation indices after partial pivoting.
 @param[out] sign store the sign of the permutation (+1 or -1).
 @return 0 on success, or a non-zero error code if the decomposition fails.
  @retval -1 on failure, A is a singular matrix.
 */
A_EXTERN int a_real_plu(a_uint n, a_real *A, a_uint *p, int *sign);

/*!
 @brief construct the permutation matrix P from a permutation vector p.
 @param[in] n the order of the square matrix that was decomposed.
 @param[in] p the row permutation indices after partial pivoting.
 @param[out] P the output matrix where the permutation matrix will be stored.
*/
A_EXTERN void a_real_plu_P(a_uint n, a_uint const *__restrict p, a_real *__restrict P);
A_EXTERN void a_real_plu_P_(a_uint n, a_uint const *__restrict p, a_real *__restrict P);

/*!
 @brief extract the lower triangular matrix L from matrix A.
 @param[in] n the order of the square matrix that was decomposed.
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[out] L the output matrix where the lower triangular matrix will be stored.
*/
A_EXTERN void a_real_plu_L(a_uint n, a_real const *__restrict A, a_real *__restrict L);

/*!
 @brief extract the upper triangular matrix U from matrix A.
 @param[in] n the order of the square matrix that was decomposed.
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[out] U the output matrix where the upper triangular matrix will be stored.
*/
A_EXTERN void a_real_plu_U(a_uint n, a_real const *__restrict A, a_real *__restrict U);

/*!
 @brief apply the permutation P to the vector b, producing Pb.
 @param[in] n the order of the square matrix that was decomposed.
 @param[in] p the row permutation indices after partial pivoting.
 @param[in] b the input vector of size n that will be permuted.
 @param[out] Pb the output vector where the permuted result will be stored.
*/
A_EXTERN void a_real_plu_apply(a_uint n, a_uint const *__restrict p, a_real const *__restrict b, a_real *__restrict Pb);

/*!
 @brief solve the lower triangular system Ly = Pb for y.
 @param[in] n the order of the square matrix L (number of rows and columns).
 @param[in] L the lower triangular matrix L, stored in row-major order.
 @param[in,out] y on input, contains the permuted vector Pb. on output, contains the solution vector y.
*/
A_EXTERN void a_real_plu_lower(a_uint n, a_real const *L, a_real *y);
A_EXTERN void a_real_plu_lower_(a_uint n, a_real const *L, a_real *y);

/*!
 @brief solve the upper triangular system Ux = y for x.
 @param[in] n the order of the square matrix U (number of rows and columns).
 @param[in] U the upper triangular matrix U, stored in row-major order.
 @param[in,out] x on input, contains the vector y. on output, contains the solution vector x.
*/
A_EXTERN void a_real_plu_upper(a_uint n, a_real const *U, a_real *x);
A_EXTERN void a_real_plu_upper_(a_uint n, a_real const *U, a_real *x);

/*!
 @brief solve the linear system Ax = b using LU decomposition with partial pivoting.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[in] p the permutation indices obtained during LU decomposition.
 @param[in] b the input vector b of the linear system.
 @param[out] x the output vector x where the solution will be stored.
*/
A_EXTERN void a_real_plu_solve(a_uint n, a_real const *A, a_uint const *p, a_real const *b, a_real *x);

/*!
 @brief compute the inverse of a matrix using its LU decomposition and permutation matrix.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[in] p the permutation indices obtained during LU decomposition.
 @param[in] b a pre-allocated temporary buffer of size n for intermediate computations.
 @param[out] I the output matrix where the inverse of A will be stored.
*/
A_EXTERN void a_real_plu_inv(a_uint n, a_real const *A, a_uint const *p, a_real *b, a_real *I);
A_EXTERN void a_real_plu_inv_(a_uint n, a_real const *A, a_uint const *p, a_real *I);

/*!
 @brief compute the determinant of a matrix using its LU decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[in] sign the sign of the permutation matrix P (+1 or -1).
 @return the determinant of matrix A.
*/
A_EXTERN a_real a_real_plu_det(a_uint n, a_real const *A, int sign);

/*!
 @brief compute the natural logarithm of the absolute value of the determinant of a matrix using its LU decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @return the natural logarithm of the absolute value of the determinant.
*/
A_EXTERN a_real a_real_plu_lndet(a_uint n, a_real const *A);

/*!
 @brief compute the sign of the determinant of a matrix using its LU decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L and U in a compact form after LU decomposition.
 @param[in] sign the sign of the permutation matrix P (+1 or -1).
 @return the sign of the determinant: -1, 0, +1.
*/
A_EXTERN int a_real_plu_sgndet(a_uint n, a_real const *A, int sign);

/*!
 @brief compute LDL decomposition of a symmetric matrix.
 @details The matrix A is modified in-place to store the lower triangular matrix L and the diagonal matrix D.
 The decomposition satisfies the equation A = LDL^T, where L is a unit lower triangular matrix,
 and D is a diagonal matrix. This function assumes that the input matrix A is symmetric.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in,out] A an n x n square matrix.
  on input, contains the matrix to decompose. on output, contains the L and D matrices.
 @return 0 on success, or a non-zero error code if the decomposition fails.
  @retval -1 on failure, A is a singular matrix.
*/
A_EXTERN int a_real_ldl(a_uint n, a_real *A);

/*!
 @brief extract the lower triangular matrix L from matrix A.
 @param[in] n the order of the square matrix that was decomposed.
 @param[in] A the matrix containing L and D in a compact form after LDL decomposition.
 @param[out] L the output matrix where the lower triangular matrix will be stored.
*/
A_EXTERN void a_real_ldl_L(a_uint n, a_real const *__restrict A, a_real *__restrict L);

/*!
 @brief extract the diagonal vector D from matrix A.
 @param[in] n the order of the square matrix that was decomposed.
 @param[in] A the matrix containing L and D in a compact form after LDL decomposition.
 @param[out] d the output vector where the diagonal vector will be stored.
*/
A_EXTERN void a_real_ldl_D(a_uint n, a_real const *__restrict A, a_real *__restrict d);

/*!
 @brief solve the lower triangular system Ly = b for y.
 @param[in] n the order of the square matrix L (number of rows and columns).
 @param[in] L the matrix containing L and D in a compact form after LDL decomposition.
 @param[in,out] y on input, contains the vector b. on output, contains the solution vector y.
*/
A_EXTERN void a_real_ldl_lower(a_uint n, a_real const *L, a_real *y);
A_EXTERN void a_real_ldl_lower_(a_uint n, a_real const *L, a_real *y);

/*!
 @brief solve the upper triangular system D L^T x = y for x.
 @param[in] n the order of the square matrix L (number of rows and columns).
 @param[in] L the matrix containing L and D in a compact form after LDL decomposition.
 @param[in,out] x on input, contains the vector y. on output, contains the solution vector x.
*/
A_EXTERN void a_real_ldl_upper(a_uint n, a_real const *L, a_real *x);
A_EXTERN void a_real_ldl_upper_(a_uint n, a_real const *L, a_real *x);

/*!
 @brief solve the linear system Ax = b using the LDL factorization A = LDL^T.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L and D in a compact form after LDL decomposition.
 @param[in,out] x on input, contains the vector b. on output, contains the solution vector x.
*/
A_EXTERN void a_real_ldl_solve(a_uint n, a_real const *A, a_real *x);

/*!
 @brief compute the inverse of a matrix using its LDL factorization A = LDL^T.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L and D in a compact form after LDL decomposition.
 @param[in] b a pre-allocated temporary buffer of size n for intermediate computations.
 @param[out] I the output matrix where the inverse of A will be stored.
*/
A_EXTERN void a_real_ldl_inv(a_uint n, a_real const *A, a_real *b, a_real *I);
A_EXTERN void a_real_ldl_inv_(a_uint n, a_real const *A, a_real *I);

/*!
 @brief compute the determinant of a matrix using its LDL decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L and D in a compact form after LDL decomposition.
 @return the determinant of matrix A.
*/
A_EXTERN a_real a_real_ldl_det(a_uint n, a_real const *A);

/*!
 @brief compute the natural logarithm of the absolute value of the determinant of a matrix using its LDL decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L and D in a compact form after LDL decomposition.
 @return the natural logarithm of the absolute value of the determinant.
*/
A_EXTERN a_real a_real_ldl_lndet(a_uint n, a_real const *A);

/*!
 @brief compute the sign of the determinant of a matrix using its LDL decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L and D in a compact form after LDL decomposition.
 @return the sign of the determinant: -1, 0, +1.
*/
A_EXTERN int a_real_ldl_sgndet(a_uint n, a_real const *A);

/*!
 @brief compute Cholesky decomposition of a symmetric positive-definite matrix.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in,out] A an n x n square matrix.
  on input, contains the matrix to decompose. on output, contains the L matrix.
 @return 0 on success, or a non-zero error code if the decomposition fails.
  @retval -1 on failure, A is a singular matrix.
*/
A_EXTERN int a_real_llt(a_uint n, a_real *A);

/*!
 @brief extract the lower triangular matrix L from matrix A.
 @param[in] n the order of the square matrix that was decomposed.
 @param[in] A the matrix containing L form after Cholesky decomposition.
 @param[out] L the output matrix where the lower triangular matrix will be stored.
*/
A_EXTERN void a_real_llt_L(a_uint n, a_real const *__restrict A, a_real *__restrict L);

/*!
 @brief solve the lower triangular system Ly = b for y.
 @param[in] n the order of the square matrix L (number of rows and columns).
 @param[in] L the lower triangular matrix L, stored in row-major order.
 @param[in,out] y on input, contains the vector b. on output, contains the solution vector y.
*/
A_EXTERN void a_real_llt_lower(a_uint n, a_real const *L, a_real *y);
A_EXTERN void a_real_llt_lower_(a_uint n, a_real const *L, a_real *y);

/*!
 @brief solve the upper triangular system L^T x = y for x.
 @param[in] n the order of the square matrix L (number of rows and columns).
 @param[in] L the lower triangular matrix L, stored in row-major order.
 @param[in,out] x on input, contains the vector y. on output, contains the solution vector x.
*/
A_EXTERN void a_real_llt_upper(a_uint n, a_real const *L, a_real *x);
A_EXTERN void a_real_llt_upper_(a_uint n, a_real const *L, a_real *x);

/*!
 @brief solve the linear system Ax = b using the Cholesky factorization A = LL^T.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L form after Cholesky decomposition.
 @param[in,out] x on input, contains the vector b. on output, contains the solution vector x.
*/
A_EXTERN void a_real_llt_solve(a_uint n, a_real const *A, a_real *x);

/*!
 @brief compute the inverse of a matrix using its Cholesky factorization A = LL^T.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L form after Cholesky decomposition.
 @param[in] b a pre-allocated temporary buffer of size n for intermediate computations.
 @param[out] I the output matrix where the inverse of A will be stored.
*/
A_EXTERN void a_real_llt_inv(a_uint n, a_real const *A, a_real *b, a_real *I);
A_EXTERN void a_real_llt_inv_(a_uint n, a_real const *A, a_real *I);

/*!
 @brief compute the determinant of a matrix using its Cholesky decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L form after Cholesky decomposition.
 @return the determinant of matrix A.
*/
A_EXTERN a_real a_real_llt_det(a_uint n, a_real const *A);

/*!
 @brief compute the natural logarithm of the absolute value of the determinant of a matrix using its Cholesky decomposition.
 @param[in] n the order of the square matrix A (number of rows and columns).
 @param[in] A the matrix containing L form after Cholesky decomposition.
 @return the natural logarithm of the absolute value of the determinant.
*/
A_EXTERN a_real a_real_llt_lndet(a_uint n, a_real const *A);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} a_linalg */

#endif /* a/linalg.h */
