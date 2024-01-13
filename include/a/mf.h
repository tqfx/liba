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
 @brief enumeration for membership function
*/
enum
{
    A_MF_NUL, //!< none
    A_MF_GAUSS, //!< gaussian membership function
    A_MF_GAUSS2, //!< gaussian combination membership function
    A_MF_GBELL, //!< generalized bell-shaped membership function
    A_MF_SIG, //!< sigmoidal membership function
    A_MF_DSIG, //!< difference between two sigmoidal membership functions
    A_MF_PSIG, //!< product of two sigmoidal membership functions
    A_MF_TRAP, //!< trapezoidal membership function
    A_MF_TRI, //!< triangular membership function
    A_MF_LINS, //!< linear s-shaped saturation membership function
    A_MF_LINZ, //!< linear z-shaped saturation membership function
    A_MF_S, //!< s-shaped membership function
    A_MF_Z, //!< z-shaped membership function
    A_MF_PI //!< pi-shaped membership function
};

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief gaussian membership function
 \f[
  f(x,\sigma,c)=e^{-\frac{(x-c)^2}{2\sigma^2}}
 \f]
 @param[in] x input value for which to compute membership value.
 @param[in] sigma is the standard deviation.
 @param[in] c is the mean.
 @return membership value.
*/
A_EXTERN a_float a_mf_gauss(a_float x, a_float sigma, a_float c);

/*!
 @brief gaussian combination membership function
 \f[
  f(x,\sigma_1,c_1,\sigma_2,c_2)=\begin{cases}
  e^{-\frac{(x-c_1)^2}{2\sigma_1^2}} & x \lt c_1 \\
  1 & c_1 \le x \le c_2 \\
  e^{-\frac{(x-c_2)^2}{2\sigma_2^2}} & x \gt c_2 \\
  \end{cases}
 \f]
 @param[in] x input value for which to compute membership value.
 @param[in] sigma1 is the standard deviation of the left gaussian function.
 @param[in] c1 is the mean of the left gaussian function.
 @param[in] sigma2 is the standard deviation of the right gaussian function.
 @param[in] c2 is the mean of the right gaussian function.
 @return membership value.
*/
A_EXTERN a_float a_mf_gauss2(a_float x, a_float sigma1, a_float c1, a_float sigma2, a_float c2);

/*!
 @brief generalized bell-shaped membership function
 \f[
  f(x,a,b,c)=\frac{1}{1+\left|\frac{x-c}{a}\right|^{2b}}
 \f]
 @param[in] x input value for which to compute membership value.
 @param[in] a defines the width of the membership function, where a larger value creates a wider membership function.
 @param[in] b defines the shape of the curve on either side of the central plateau, where a larger value creates a more steep transition.
 @param[in] c defines the center of the membership function.
 @return membership value.
*/
A_EXTERN a_float a_mf_gbell(a_float x, a_float a, a_float b, a_float c);

/*!
 @brief sigmoidal membership function
 \f[
  f(x,a,c)=\frac{1}{1+e^{-a(x-c)}}
 \f]
 @param[in] x input value for which to compute membership value.
 @param[in] a defines the width of the transition area.
 @param[in] c defines the center of the transition area.
 @return membership value.
*/
A_EXTERN a_float a_mf_sig(a_float x, a_float a, a_float c);

/*!
 @brief difference between two sigmoidal membership functions
 \f[
  f(x,a_1,c_1,a_2,c_2)=\frac{1}{1+e^{-a_1(x-c_1)}}-\frac{1}{1+e^{-a_2(x-c_2)}}
 \f]
 @param[in] x input value for which to compute membership value.
 @param[in] a1 defines the width of the first transition area.
 @param[in] c1 defines the center of the first transition area.
 @param[in] a2 defines the width of the second transition area.
 @param[in] c2 defines the center of the second transition area.
 @return membership value.
*/
A_EXTERN a_float a_mf_dsig(a_float x, a_float a1, a_float c1, a_float a2, a_float c2);

/*!
 @brief product of two sigmoidal membership functions
 \f[
  f(x,a_1,c_1,a_2,c_2)=\frac{1}{1+e^{-a_1(x-c_1)}}\times\frac{1}{1+e^{-a_2(x-c_2)}}
 \f]
 @param[in] x input value for which to compute membership value.
 @param[in] a1 defines the width of the first transition area.
 @param[in] c1 defines the center of the first transition area.
 @param[in] a2 defines the width of the second transition area.
 @param[in] c2 defines the center of the second transition area.
 @return membership value.
*/
A_EXTERN a_float a_mf_psig(a_float x, a_float a1, a_float c1, a_float a2, a_float c2);

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
 @param[in] x input value for which to compute membership value.
 @param[in] a defines its left foot.
 @param[in] b defines its left shoulder.
 @param[in] c defines its right shoulder.
 @param[in] d defines its right foot.
 @return membership value.
*/
A_EXTERN a_float a_mf_trap(a_float x, a_float a, a_float b, a_float c, a_float d);

/*!
 @brief triangular membership function
 \f[
  f(x,a,b)=\begin{cases}
  0 & x \le a \\
  \frac{x-a}{b-a} & a \le x \le b \\
  \frac{c-x}{c-b} & b \le x \le c \\
  0 & x \ge c \\
  \end{cases}
 \f]
 @param[in] x input value for which to compute membership value.
 @param[in] a defines its left foot.
 @param[in] b defines its peak.
 @param[in] c defines its right foot.
 @return membership value.
*/
A_EXTERN a_float a_mf_tri(a_float x, a_float a, a_float b, a_float c);

/*!
 @brief linear s-shaped saturation membership function
 \f[
  f(x,a,b)=\begin{cases}
  0 & x \lt a \\
  \frac{x-a}{b-a} & a \le x \le b \\
  1 & x \gt b \\
  \end{cases}
 \f]
 @param[in] x input value for which to compute membership value.
 @param[in] a defines its foot.
 @param[in] b defines its shoulder.
 @return membership value.
*/
A_EXTERN a_float a_mf_lins(a_float x, a_float a, a_float b);

/*!
 @brief linear z-shaped saturation membership function
 \f[
  f(x,a,b)=\begin{cases}
  1 & x \lt a \\
  \frac{b-x}{b-a} & a \le x \le b \\
  0 & x \gt b \\
  \end{cases}
 \f]
 @param[in] x input value for which to compute membership value.
 @param[in] a defines its shoulder.
 @param[in] b defines its foot.
 @return membership value.
*/
A_EXTERN a_float a_mf_linz(a_float x, a_float a, a_float b);

/*!
 @brief s-shaped membership function
 \f[
  f(x,a,b)=\begin{cases}
  0 & x \le a \\
  2(\frac{x-a}{b-a})^2 & a \le x \le \frac{a+b}{2} \\
  1-2(\frac{b-x}{b-a})^2 & \frac{a+b}{2} \le x \le b \\
  1 & x \ge b \\
  \end{cases}
 \f]
 @param[in] x input value for which to compute membership value.
 @param[in] a defines its foot.
 @param[in] b defines its shoulder.
 @return membership value.
*/
A_EXTERN a_float a_mf_s(a_float x, a_float a, a_float b);

/*!
 @brief z-shaped membership function
 \f[
  f(x,a,b)=\begin{cases}
  1 & x \le a \\
  1-2(\frac{x-a}{b-a})^2 & a \le x \le \frac{a+b}{2} \\
  2(\frac{b-x}{b-a})^2 & \frac{a+b}{2} \le x \le b \\
  0 & x \ge b \\
  \end{cases}
 \f]
 @param[in] x input value for which to compute membership value.
 @param[in] a defines its shoulder.
 @param[in] b defines its foot.
 @return membership value.
*/
A_EXTERN a_float a_mf_z(a_float x, a_float a, a_float b);

/*!
 @brief pi-shaped membership function
 \f[
  f(x,a,b,c,d)=\begin{cases}
  0 & x \le a \\
  2(\frac{x-a}{b-a})^2 & a \le x \le \frac{a+b}{2} \\
  1-2(\frac{b-x}{b-a})^2 & \frac{a+b}{2} \le x \le b \\
  1 & b \le x \le c \\
  1-2(\frac{x-c}{d-c})^2 & c \le x \le \frac{c+d}{2} \\
  2(\frac{d-x}{d-c})^2 & \frac{c+d}{2} \le x \le d \\
  1 & x \ge d \\
  \end{cases}
 \f]
 @param[in] x input value for which to compute membership value.
 @param[in] a defines its left foot.
 @param[in] b defines its left shoulder.
 @param[in] c defines its right shoulder.
 @param[in] d defines its right foot.
 @return membership value.
*/
A_EXTERN a_float a_mf_pi(a_float x, a_float a, a_float b, a_float c, a_float d);

/*!
 @brief membership function
 @param[in] e enumeration for membership function
 |                   |                                        |
 | :---------------- | -------------------------------------- |
 | \ref A_MF_GAUSS   | a_mf_gauss(x, sigma, c)                |
 | \ref A_MF_GAUSS2  | a_mf_gauss2(x, sigma1, c1, sigma2, c2) |
 | \ref A_MF_GBELL   | a_mf_gbell(x, a, b, c)                 |
 | \ref A_MF_SIG     | a_mf_sig(x, a, c)                      |
 | \ref A_MF_DSIG    | a_mf_dsig(x, a1, c1, a2, c2)           |
 | \ref A_MF_PSIG    | a_mf_psig(x, a1, c1, a2, c2)           |
 | \ref A_MF_TRAP    | a_mf_trap(x, a, b, c, d)               |
 | \ref A_MF_TRI     | a_mf_tri(x, a, b, c)                   |
 | \ref A_MF_LINS    | a_mf_lins(x, a, b)                     |
 | \ref A_MF_LINZ    | a_mf_linz(x, a, b)                     |
 | \ref A_MF_S       | a_mf_s(x, a, b)                        |
 | \ref A_MF_Z       | a_mf_z(x, a, b)                        |
 | \ref A_MF_PI      | a_mf_pi(x, a, b, c, d)                 |
 @param[in] x input value for which to compute membership value.
 @param[in] a is an array that stores parameters.
  @arg \b a[2] \ref a_mf_gauss \ref a_mf_sig \ref a_mf_lins \ref a_mf_linz \ref a_mf_s \ref a_mf_z
  @arg \b a[3] \ref a_mf_gbell \ref a_mf_tri
  @arg \b a[4] \ref a_mf_gauss2 \ref a_mf_dsig \ref a_mf_psig \ref a_mf_trap \ref a_mf_pi
 @return membership value.
*/
A_EXTERN a_float a_mf(unsigned int e, a_float x, a_float const *a);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_MF */

#endif /* a/mf.h */
