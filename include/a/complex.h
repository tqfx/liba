/*!
 @file complex.h
 @brief complex number
*/

#ifndef LIBA_COMPLEX_H
#define LIBA_COMPLEX_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_COMPLEX complex number
 @{
*/

// clang-format off
/*! format constants for the fprintf family of functions */
#define A_COMPLEX_PRI(RF, RC, IF, IC) "(" A_FLOAT_PRI(RF, RC) "," A_FLOAT_PRI(IF, IC) ")"
/*! constructs a complex number constant from real and imaginary parts */
#if !defined __cplusplus
#define A_COMPLEX_C(R, I) (a_complex){A_FLOAT_C(R), A_FLOAT_C(I)}
#else /* !__cplusplus */
#define A_COMPLEX_C(R, I) {A_FLOAT_C(R), A_FLOAT_C(I)}
#endif /* __cplusplus */
/*! constructs a complex number from real and imaginary parts */
#if !defined __cplusplus
#define a_complex_c(r, i) (a_complex){a_float_c(r), a_float_c(i)}
#else /* !__cplusplus */
#define a_complex_c(r, i) {a_float_c(r), a_float_c(i)}
#endif /* __cplusplus */
// clang-format on

/*!
 @brief instance structure for complex number
*/
typedef struct a_complex
{
    a_float real; //!< real part of complex number
    a_float imag; //!< imaginary part of complex number
} a_complex;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
#if defined(LIBA_COMPLEX_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_COMPLEX_C */

/*!
 @brief constructs a complex number from real and imaginary parts
 @param _z = \f$ (\rm{Re},\rm{Im}) \f$
 @param real real part of complex number
 @param imag imaginary part of complex number
*/
static A_INLINE void a_complex_rect(a_complex *_z, a_float real, a_float imag)
{
    _z->real = real;
    _z->imag = imag;
}

/*!
 @brief constructs a complex number from polar form
 @param _z = \f$ (\rho\cos\theta,\rho\sin\theta{i}) \f$
 @param rho a distance from a reference point
 @param theta an angle from a reference direction
*/
A_EXTERN void a_complex_polar(a_complex *_z, a_float rho, a_float theta);

/*!
 @brief parse a string into a complex number
 @param _z points to an instance structure for complex number
 @param str complex number string to be parsed
 @return number of parsed characters
*/
A_EXTERN unsigned int a_complex_parse(a_complex *_z, char const *str);

/*!
 @brief complex number x is equal to complex number y
 @param x complex number on the left
 @param y complex number on the right
 @return result of comparison
*/
A_EXTERN a_bool a_complex_eq(a_complex x, a_complex y);

/*!
 @brief complex number x is not equal to complex number y
 @param x complex number on the left
 @param y complex number on the right
 @return result of comparison
*/
A_EXTERN a_bool a_complex_ne(a_complex x, a_complex y);

/* Properties of complex numbers */

/*!
 @brief computes the natural logarithm of magnitude of a complex number
 @param z a complex number
 @return = \f$ \log\left|x\right| \f$
*/
A_EXTERN a_float a_complex_logabs(a_complex z);

/*!
 @brief computes the squared magnitude of a complex number
 @param z a complex number
 @return = \f$ a^2+b^2 \f$
*/
A_EXTERN a_float a_complex_abs2(a_complex z);

/*!
 @brief computes the magnitude of a complex number
 @param z a complex number
 @return = \f$ \sqrt{a^2+b^2} \f$
*/
A_EXTERN a_float a_complex_abs(a_complex z);

/*!
 @brief computes the phase angle of a complex number
 @param z a complex number
 @return = \f$ \arctan\frac{b}{a} \f$
*/
A_EXTERN a_float a_complex_arg(a_complex z);

/* Complex arithmetic operators */

/*!
 @brief computes the projection on Riemann sphere
 @param _z = \f$ z \f$ or \f$ (\inf,\rm{copysign}(0,b)i) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_proj(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_proj_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_proj(a_complex *_z, a_complex z)
{
    a_complex_proj_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex conjugate
 @param _z = \f$ (a,-b{i}) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_conj(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_conj(a_complex *_z, a_complex z)
{
    _z->real = +z.real;
    _z->imag = -z.imag;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_conj_(a_complex *_z);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_conj_(a_complex *_z)
{
    _z->imag = -_z->imag;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex negative
 @param _z = \f$ (-a,-b{i}) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_neg(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_neg(a_complex *_z, a_complex z)
{
    _z->real = -z.real;
    _z->imag = -z.imag;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_neg_(a_complex *_z);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_neg_(a_complex *_z)
{
    _z->real = -_z->real;
    _z->imag = -_z->imag;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief addition of complex numbers \f[ (a+b i)+(c+d i)=(a+c)+(b+d)i \f]
 @param _z = \f$ x + y \f$
 @param x complex number on the left
 @param y complex number on the right
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_add(a_complex *_z, a_complex x, a_complex y);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_add(a_complex *_z, a_complex x, a_complex y)
{
    _z->real = x.real + y.real;
    _z->imag = x.imag + y.imag;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_add_(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_add_(a_complex *_z, a_complex z)
{
    _z->real += z.real;
    _z->imag += z.imag;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_add_real(a_complex *_z, a_complex x, a_float y);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_add_real(a_complex *_z, a_complex x, a_float y)
{
    _z->real = x.real + y;
    _z->imag = x.imag;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_add_real_(a_complex *_z, a_float x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_add_real_(a_complex *_z, a_float x)
{
    _z->real += x;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_add_imag(a_complex *_z, a_complex x, a_float y);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_add_imag(a_complex *_z, a_complex x, a_float y)
{
    _z->real = x.real;
    _z->imag = x.imag + y;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_add_imag_(a_complex *_z, a_float x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_add_imag_(a_complex *_z, a_float x)
{
    _z->imag += x;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief subtraction of complex numbers \f[ (a+b i)-(c+d i)=(a-c)+(b-d)i \f]
 @param _z = \f$ x - y \f$
 @param x complex number on the left
 @param y complex number on the right
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_sub(a_complex *_z, a_complex x, a_complex y);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_sub(a_complex *_z, a_complex x, a_complex y)
{
    _z->real = x.real - y.real;
    _z->imag = x.imag - y.imag;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_sub_(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_sub_(a_complex *_z, a_complex z)
{
    _z->real -= z.real;
    _z->imag -= z.imag;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_sub_real(a_complex *_z, a_complex x, a_float y);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_sub_real(a_complex *_z, a_complex x, a_float y)
{
    _z->real = x.real - y;
    _z->imag = x.imag;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_sub_real_(a_complex *_z, a_float x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_sub_real_(a_complex *_z, a_float x)
{
    _z->real -= x;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_sub_imag(a_complex *_z, a_complex x, a_float y);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_sub_imag(a_complex *_z, a_complex x, a_float y)
{
    _z->real = x.real;
    _z->imag = x.imag - y;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_sub_imag_(a_complex *_z, a_float x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_sub_imag_(a_complex *_z, a_float x)
{
    _z->imag -= x;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief multiplication of complex numbers \f[ (a+b i)(c+d i)=a c+b c i+a d i+b d i^{2}=(a c-b d)+(b c+a d) i \f]
 @param _z = \f$ x \times y \f$
 @param x complex number on the left
 @param y complex number on the right
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_mul(a_complex *_z, a_complex x, a_complex y);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_mul_(a_complex *_z, a_complex z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_mul(a_complex *_z, a_complex x, a_complex y)
{
    a_complex_mul_(&x, y);
    *_z = x;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_mul_real(a_complex *_z, a_complex x, a_float y);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_mul_real(a_complex *_z, a_complex x, a_float y)
{
    _z->real = x.real * y;
    _z->imag = x.imag * y;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_mul_real_(a_complex *_z, a_float x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_mul_real_(a_complex *_z, a_float x)
{
    _z->real *= x;
    _z->imag *= x;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_mul_imag(a_complex *_z, a_complex x, a_float y);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_mul_imag(a_complex *_z, a_complex x, a_float y)
{
    _z->real = -x.imag * y;
    _z->imag = x.real * y;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_mul_imag_(a_complex *_z, a_float x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_mul_imag_(a_complex *_z, a_float x)
{
    a_float const real = _z->real;
    _z->real = -_z->imag * x;
    _z->imag = real * x;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief division of complex numbers \f[ \frac{(a+b i)}{(c+d i)}=\frac{(a+b i)(c-d i)}{(c+d i)(c-d i)}=\frac{a c+b c i-a d i-b d i^{2}}{c^{2}-(d i)^{2}}=\frac{(a c+b d)+(b c-a d) i}{c^{2}+d^{2}}=\left(\frac{a c+b d}{c^{2}+d^{2}}\right)+\left(\frac{b c-a d}{c^{2}+d^{2}}\right) i \f]
 @param _z = \f$ x \div y \f$
 @param x complex number on the left
 @param y complex number on the right
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_div(a_complex *_z, a_complex x, a_complex y);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_div_(a_complex *_z, a_complex z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_div(a_complex *_z, a_complex x, a_complex y)
{
    a_complex_div_(&x, y);
    *_z = x;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_div_real(a_complex *_z, a_complex x, a_float y);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_div_real(a_complex *_z, a_complex x, a_float y)
{
    _z->real = x.real / y;
    _z->imag = x.imag / y;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_div_real_(a_complex *_z, a_float x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_div_real_(a_complex *_z, a_float x)
{
    _z->real /= x;
    _z->imag /= x;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_div_imag(a_complex *_z, a_complex x, a_float y);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_div_imag(a_complex *_z, a_complex x, a_float y)
{
    _z->real = -x.imag / y;
    _z->imag = x.real / y;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_div_imag_(a_complex *_z, a_float x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_div_imag_(a_complex *_z, a_float x)
{
    a_float const real = _z->real;
    _z->real = -_z->imag / x;
    _z->imag = real / x;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief inverse of a complex number \f[ \frac{a-bi}{a^2+b^2}=\left(\frac{a}{a^2+b^2}\right)-\left(\frac{b}{a^2+b^2}\right)i \f]
 @param _z inverse or reciprocal \f$ \frac{1}{z} \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_inv(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_inv_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_inv(a_complex *_z, a_complex z)
{
    a_complex_inv_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/* Elementary Complex Functions */

/*!
 @brief computes the complex square root
 @param _z = \f$ \sqrt{z} \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_sqrt(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_sqrt_(a_complex *_z);
A_EXTERN void a_complex_sqrt_real(a_complex *_z, a_float x);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_sqrt(a_complex *_z, a_complex z)
{
    a_complex_sqrt_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief complex number z raised to complex power a
 @param _z = \f$ z^a \f$
 @param z a complex number
 @param a a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_pow(a_complex *_z, a_complex z, a_complex a);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_pow_(a_complex *_z, a_complex a);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_pow(a_complex *_z, a_complex z, a_complex a)
{
    a_complex_pow_(&z, a);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief complex number z raised to real power a
 @param _z = \f$ z^a \f$
 @param z a complex number
 @param a a real number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_pow_real(a_complex *_z, a_complex z, a_float a);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_pow_real_(a_complex *_z, a_float a);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_pow_real(a_complex *_z, a_complex z, a_float a)
{
    a_complex_pow_real_(&z, a);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex base-e exponential
 @param _z = \f$ e^z \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_exp(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_exp_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_exp(a_complex *_z, a_complex z)
{
    a_complex_exp_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex natural logarithm
 @param _z = \f$ \ln{z} \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_log(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_log_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_log(a_complex *_z, a_complex z)
{
    a_complex_log_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex base-2 logarithm
 @param _z = \f$ \log_{2}{z} \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_log2(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_log2_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_log2(a_complex *_z, a_complex z)
{
    a_complex_log2_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex base-10 logarithm
 @param _z = \f$ \lg{z} \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_log10(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_log10_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_log10(a_complex *_z, a_complex z)
{
    a_complex_log10_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex base-b logarithm
 @param _z = \f$ \log_{b}{z} \f$
 @param z a complex number
 @param b a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_logb(a_complex *_z, a_complex z, a_complex b);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_logb_(a_complex *_z, a_complex b);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_logb(a_complex *_z, a_complex z, a_complex b)
{
    a_complex_logb_(&z, b);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/* Complex Trigonometric Functions */

/*!
 @brief computes the complex sine \f[ \sin(z)=\frac{\exp(z{i})-\exp(-z{i})}{2{i}} \f]
 @param _z = \f$ \sin(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_sin(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_sin_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_sin(a_complex *_z, a_complex z)
{
    a_complex_sin_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex cosine \f[ \cos(z)=\frac{\exp(z{i})+\exp(-z{i})}{2} \f]
 @param _z = \f$ \cos(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_cos(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_cos_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_cos(a_complex *_z, a_complex z)
{
    a_complex_cos_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex tangent \f[ \tan(z)=\frac{\sin(z)}{\cos(z)} \f]
 @param _z = \f$ \tan(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_tan(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_tan_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_tan(a_complex *_z, a_complex z)
{
    a_complex_tan_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex secant \f[ \sec(z)=\frac{1}{\cos(z)} \f]
 @param _z = \f$ \sec(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_sec(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_sec_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_sec(a_complex *_z, a_complex z)
{
    a_complex_sec_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex cosecant \f[ \csc(z)=\frac{1}{\sin(z)} \f]
 @param _z = \f$ \csc(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_csc(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_csc_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_csc(a_complex *_z, a_complex z)
{
    a_complex_csc_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex cotangent \f[ \cot(z)=\frac{1}{\tan(z)} \f]
 @param _z = \f$ \cot(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_cot(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_cot_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_cot(a_complex *_z, a_complex z)
{
    a_complex_cot_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/* Inverse Complex Trigonometric Functions */

/*!
 @brief computes the complex arc sine
 @param _z = \f$ \arcsin(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_asin(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_asin_(a_complex *_z);
A_EXTERN void a_complex_asin_real(a_complex *_z, a_float x);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_asin(a_complex *_z, a_complex z)
{
    a_complex_asin_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex arc cosine
 @param _z = \f$ \arccos(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_acos(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_acos_(a_complex *_z);
A_EXTERN void a_complex_acos_real(a_complex *_z, a_float x);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_acos(a_complex *_z, a_complex z)
{
    a_complex_acos_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex arc tangent
 @param _z = \f$ \arctan(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_atan(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_atan_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_atan(a_complex *_z, a_complex z)
{
    a_complex_atan_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex arc secant \f[ \mathrm{arcsec}(z)=\mathrm{arccos}(\frac{1}{z}) \f]
 @param _z = \f$ \mathrm{arcsec}(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_asec(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_asec_(a_complex *_z);
A_EXTERN void a_complex_asec_real(a_complex *_z, a_float x);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_asec(a_complex *_z, a_complex z)
{
    a_complex_asec_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex arc cosecant \f[ \mathrm{arccsc}(z)=\mathrm{arcsin}(\frac{1}{z}) \f]
 @param _z = \f$ \mathrm{arccsc}(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_acsc(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_acsc_(a_complex *_z);
A_EXTERN void a_complex_acsc_real(a_complex *_z, a_float x);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_acsc(a_complex *_z, a_complex z)
{
    a_complex_acsc_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex arc cotangent \f[ \mathrm{arccot}(z)=\mathrm{arctan}(\frac{1}{z}) \f]
 @param _z = \f$ \mathrm{arccot}(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_acot(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_acot_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_acot(a_complex *_z, a_complex z)
{
    a_complex_acot_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/* Complex Hyperbolic Functions */

/*!
 @brief computes the complex hyperbolic sine \f[ \sinh(z)=\frac{\exp(z)-\exp(-z)}{2} \f]
 @param _z = \f$ \sinh(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_sinh(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_sinh_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_sinh(a_complex *_z, a_complex z)
{
    a_complex_sinh_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex hyperbolic cosine \f[ \cosh(z)=\frac{\exp(z)+\exp(-z)}{2} \f]
 @param _z = \f$ \cosh(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_cosh(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_cosh_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_cosh(a_complex *_z, a_complex z)
{
    a_complex_cosh_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex hyperbolic tangent \f[ \tanh(z)=\frac{\sinh(z)}{\cosh(z)} \f]
 @param _z = \f$ \tanh(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_tanh(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_tanh_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_tanh(a_complex *_z, a_complex z)
{
    a_complex_tanh_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex hyperbolic secant \f[ \mathrm{sech}(z)=\frac{1}{\cosh(z)} \f]
 @param _z = \f$ \mathrm{sech}(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_sech(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_sech_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_sech(a_complex *_z, a_complex z)
{
    a_complex_sech_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex hyperbolic cosecant \f[ \mathrm{csch}(z)=\frac{1}{\sinh(z)} \f]
 @param _z = \f$ \mathrm{csch}(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_csch(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_csch_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_csch(a_complex *_z, a_complex z)
{
    a_complex_csch_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex hyperbolic cotangent \f[ \mathrm{coth}(z)=\frac{1}{\tanh(z)} \f]
 @param _z = \f$ \mathrm{coth}(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_coth(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_coth_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_coth(a_complex *_z, a_complex z)
{
    a_complex_coth_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/* Inverse Complex Hyperbolic Functions */

/*!
 @brief computes the complex arc hyperbolic sine
 @param _z = \f$ \mathrm{arcsinh}(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_asinh(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_asinh_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_asinh(a_complex *_z, a_complex z)
{
    a_complex_asinh_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex arc hyperbolic cosine \f[ \mathrm{arccosh}(z)=\log(z-\sqrt{z^2-1}) \f]
 @param _z = \f$ \mathrm{arccosh}(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_acosh(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_acosh_(a_complex *_z);
A_EXTERN void a_complex_acosh_real(a_complex *_z, a_float x);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_acosh(a_complex *_z, a_complex z)
{
    a_complex_acosh_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex arc hyperbolic tangent
 @param _z = \f$ \mathrm{arctanh}(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_atanh(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_atanh_(a_complex *_z);
A_EXTERN void a_complex_atanh_real(a_complex *_z, a_float x);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_atanh(a_complex *_z, a_complex z)
{
    a_complex_atanh_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex arc hyperbolic secant \f[ \mathrm{arcsech}(z)=\mathrm{arccosh}(\frac{1}{z}) \f]
 @param _z = \f$ \mathrm{arcsech}(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_asech(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_asech_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_asech(a_complex *_z, a_complex z)
{
    a_complex_asech_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex arc hyperbolic cosecant \f[ \mathrm{arccsch}(z)=\mathrm{arcsinh}(\frac{1}{z}) \f]
 @param _z = \f$ \mathrm{arccsch}(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_acsch(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_acsch_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_acsch(a_complex *_z, a_complex z)
{
    a_complex_acsch_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex arc hyperbolic cotangent \f[ \mathrm{arccoth}(z)=\mathrm{arctanh}(\frac{1}{z}) \f]
 @param _z = \f$ \mathrm{arccoth}(z) \f$
 @param z a complex number
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN void a_complex_acoth(a_complex *_z, a_complex z);
#endif /* A_HAVE_INLINE */
A_EXTERN void a_complex_acoth_(a_complex *_z);
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN void a_complex_acoth(a_complex *_z, a_complex z)
{
    a_complex_acoth_(&z);
    *_z = z;
}
#endif /* A_HAVE_INLINE */

#if defined(LIBA_COMPLEX_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_COMPLEX_C */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_COMPLEX */

#endif /* a/complex.h */
