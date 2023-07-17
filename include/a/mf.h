/*!
 @file mf.h
 @brief membership function
*/

#ifndef LIBA_MF_H
#define LIBA_MF_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_MF membership function
 @{
*/

/*!
 @brief instance enumeration for membership function
*/
typedef enum a_mf_e
{
    A_MF_NUL, //!< none
    A_MF_GAUSS, //!< gaussian membership function
    A_MF_GBELL, //!< generalized bell-shaped membership function
    A_MF_SIG, //!< sigmoidal membership function
    A_MF_TRAP, //!< trapezoidal membership function
    A_MF_TRI, //!< triangular membership function
    A_MF_Z //!< z-shaped membership function
} a_mf_e;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief gaussian membership function
 \f[
  f(x,\sigma,c)=e^{-\frac{(x-c)^2}{2\sigma^2}}
 \f]
 @param[in] x any element
 @param[in] sigma sigma
 @param[in] c c
*/
A_EXTERN a_float_t a_mf_gauss(a_float_t x, a_float_t sigma, a_float_t c);

/*!
 @brief generalized bell-shaped membership function
 \f[
  f(x,a,b,c)=\frac{1}{1+\left|\frac{x-c}{a}\right|^{2b}}
 \f]
 @param[in] x any element
 @param[in] a a
 @param[in] b b
 @param[in] c c
*/
A_EXTERN a_float_t a_mf_gbell(a_float_t x, a_float_t a, a_float_t b, a_float_t c);

/*!
 @brief sigmoidal membership function
 \f[
  f(x,a,c)=\frac{1}{1+e^{-a(x-c)}}
 \f]
 @param[in] x any element
 @param[in] a a
 @param[in] c c
*/
A_EXTERN a_float_t a_mf_sig(a_float_t x, a_float_t a, a_float_t c);

/*!
 @brief trapezoidal membership function
 \f[
  f(x,a,b,c,d)=\begin{cases}
  0 & x \le a \\
  \frac{x-a}{b-a} & a \le x \le b \\
  1 & b \le x \le c \\
  \frac{d-x}{d-c} & c \le x \le d \\
  0 & x \ge d \\
  \end{cases}
 \f]
 @param[in] x any element
 @param[in] a a
 @param[in] b b
 @param[in] c c
 @param[in] d d
*/
A_EXTERN a_float_t a_mf_trap(a_float_t x, a_float_t a, a_float_t b, a_float_t c, a_float_t d);

/*!
 @brief triangular membership function
 \f[
  f(x,a,b,c,d)=\begin{cases}
  0 & x \le a \\
  \frac{x-a}{b-a} & a \le x \le b \\
  \frac{c-x}{c-b} & b \le x \le c \\
  0 & x \ge c \\
  \end{cases}
 \f]
 @param[in] x any element
 @param[in] a a
 @param[in] b b
 @param[in] c c
*/
A_EXTERN a_float_t a_mf_tri(a_float_t x, a_float_t a, a_float_t b, a_float_t c);

/*!
 @brief z-shaped membership function
 \f[
  f(x,a,b,c,d)=\begin{cases}
  1 & x \le a \\
  1-2(\frac{x-a}{b-a})^2 & a \le x \le \frac{a+b}{2} \\
  2(\frac{x-b}{b-a})^2 & \frac{a+b}{2} \le x \le b \\
  0 & x \ge c \\
  \end{cases}
 \f]
 @param[in] x any element
 @param[in] a a
 @param[in] b b
*/
A_EXTERN a_float_t a_mf_z(a_float_t x, a_float_t a, a_float_t b);

/*!
 @brief membership function
 @param[in] e type for membership function
 |                   |                          |
 | :---------------- | ------------------------ |
 | \ref A_MF_GAUSS   | a_mf_gauss(x, sigma, c)  |
 | \ref A_MF_GBELL   | a_mf_gbell(x, a, b, c)   |
 | \ref A_MF_SIG     | a_mf_sig(x, a, c)        |
 | \ref A_MF_TRAP    | a_mf_trap(x, a, b, c, d) |
 | \ref A_MF_TRI     | a_mf_tri(x, a, b, c)     |
 | \ref A_MF_Z       | a_mf_z(x, a, b)          |
 @param[in] x any element
 @param[in] a paramarrays
  @arg \b a[2] \ref a_mf_gauss \ref a_mf_sig \ref a_mf_z
  @arg \b a[3] \ref a_mf_gbell \ref a_mf_tri
  @arg \b a[4] \ref a_mf_trap
*/
A_EXTERN a_float_t a_mf(unsigned int e, a_float_t x, a_float_t const *a);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_MF */

#endif /* a/mf.h */
