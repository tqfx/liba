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

/*! format constants for the fprintf family of functions */
#define A_COMPLEX_PRI(RF, RC, IF, IC) "(" A_FLOAT_PRI(RF, RC) "," A_FLOAT_PRI(IF, IC) ")"

/*! constructs a complex number constant from real and imaginary parts */
#if !defined __cplusplus
#define a_complex_c(r, i)          \
    (a_complex_s)                  \
    {                              \
        a_float_c(r), a_float_c(i) \
    }
#else /* !__cplusplus */
#define a_complex_c(r, i)          \
    {                              \
        a_float_c(r), a_float_c(i) \
    }
#endif /* __cplusplus */

/*! constructs a complex number from real and imaginary parts */
#if !defined __cplusplus
#define A_COMPLEX_C(R, I)          \
    (a_complex_s)                  \
    {                              \
        A_FLOAT_C(R), A_FLOAT_C(I) \
    }
#else /* !__cplusplus */
#define A_COMPLEX_C(R, I)          \
    {                              \
        A_FLOAT_C(R), A_FLOAT_C(I) \
    }
#endif /* __cplusplus */

/*! real part of complex number */
#define a_complex_real(ctx) (ctx).real
/*! imaginary part of complex number */
#define a_complex_imag(ctx) (ctx).imag

/*!
 @brief instance structure for complex number
*/
typedef struct a_complex_s
{
    a_float_t real; //!< real part of complex number
    a_float_t imag; //!< imaginary part of complex number
} a_complex_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
#if defined(LIBA_COMPLEX_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_COMPLEX_C */

/*!
 @brief constructs a complex number from polar form
 @param r a distance from a reference point
 @param theta an angle from a reference direction
 @return = \f$ (r\cos\theta,r\sin\theta{i}) \f$
*/
A_EXTERN a_complex_s a_complex_polar(a_float_t r, a_float_t theta);

/* Properties of complex numbers */

/*!
 @brief computes the natural logarithm of magnitude of a complex number
 @param z a complex number
 @return = \f$ \log\left|x\right| \f$
*/
A_EXTERN a_float_t a_complex_logabs(a_complex_s z);

/*!
 @brief computes the squared magnitude of a complex number
 @param z a complex number
 @return = \f$ a^2+b^2 \f$
*/
A_EXTERN a_float_t a_complex_abs2(a_complex_s z);

/*!
 @brief computes the magnitude of a complex number
 @param z a complex number
 @return = \f$ \sqrt{a^2+b^2} \f$
*/
A_EXTERN a_float_t a_complex_abs(a_complex_s z);

/*!
 @brief computes the phase angle of a complex number
 @param z a complex number
 @return = \f$ \arctan\frac{b}{a} \f$
*/
A_EXTERN a_float_t a_complex_arg(a_complex_s z);

/* Complex arithmetic operators */

/*!
 @brief computes the complex conjugate
 @param z a complex number
 @return = \f$ (a,-b{i}) \f$
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN a_complex_s a_complex_conj(a_complex_s z);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN a_complex_s a_complex_conj(a_complex_s z)
{
    z.imag = -z.imag;
    return z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief computes the complex negative
 @param z a complex number
 @return \f$ (-a,-b{i}) \f$
*/
#if !defined A_HAVE_INLINE || defined(LIBA_COMPLEX_C)
A_EXTERN a_complex_s a_complex_neg(a_complex_s z);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_COMPLEX_C)
A_INTERN a_complex_s a_complex_neg(a_complex_s z)
{
    z.real = -z.real;
    z.imag = -z.imag;
    return z;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief addition of complex numbers \f[ (a+b i)+(c+d i)=(a+c)+(b+d)i \f]
 @param x complex number on the left
 @param y complex number on the right
 @return = \f$ x + y \f$
*/
A_EXTERN a_complex_s a_complex_add(a_complex_s x, a_complex_s y);
A_EXTERN a_complex_s a_complex_add_real(a_complex_s x, a_float_t y);
A_EXTERN a_complex_s a_complex_add_imag(a_complex_s x, a_float_t y);

/*!
 @brief subtraction of complex numbers \f[ (a+b i)-(c+d i)=(a-c)+(b-d)i \f]
 @param x complex number on the left
 @param y complex number on the right
 @return = \f$ x - y \f$
*/
A_EXTERN a_complex_s a_complex_sub(a_complex_s x, a_complex_s y);
A_EXTERN a_complex_s a_complex_sub_real(a_complex_s x, a_float_t y);
A_EXTERN a_complex_s a_complex_sub_imag(a_complex_s x, a_float_t y);

/*!
 @brief multiplication of complex numbers \f[ (a+b i)(c+d i)=a c+b c i+a d i+b d i^{2}=(a c-b d)+(b c+a d) i \f]
 @param x complex number on the left
 @param y complex number on the right
 @return = \f$ x \times y \f$
*/
A_EXTERN a_complex_s a_complex_mul(a_complex_s x, a_complex_s y);
A_EXTERN a_complex_s a_complex_mul_real(a_complex_s x, a_float_t y);
A_EXTERN a_complex_s a_complex_mul_imag(a_complex_s x, a_float_t y);

/*!
 @brief division of complex numbers \f[ \frac{(a+b i)}{(c+d i)}=\frac{(a+b i)(c-d i)}{(c+d i)(c-d i)}=\frac{a c+b c i-a d i-b d i^{2}}{c^{2}-(d i)^{2}}=\frac{(a c+b d)+(b c-a d) i}{c^{2}+d^{2}}=\left(\frac{a c+b d}{c^{2}+d^{2}}\right)+\left(\frac{b c-a d}{c^{2}+d^{2}}\right) i \f]
 @param x complex number on the left
 @param y complex number on the right
 @return = \f$ x \div y \f$
*/
A_EXTERN a_complex_s a_complex_div(a_complex_s x, a_complex_s y);
A_EXTERN a_complex_s a_complex_div_real(a_complex_s x, a_float_t y);
A_EXTERN a_complex_s a_complex_div_imag(a_complex_s x, a_float_t y);

/*!
 @brief inverse of a complex number \f[ \frac{a-bi}{a^2+b^2}=\left(\frac{a}{a^2+b^2}\right)-\left(\frac{b}{a^2+b^2}\right)i \f]
 @param z a complex number
 @return inverse or reciprocal \f$ \frac{1}{z} \f$
*/
A_EXTERN a_complex_s a_complex_inv(a_complex_s z);

/* Elementary Complex Functions */

/*!
 @brief square root of a complex number
 @param z a complex number
 @return = \f$ \sqrt{z} \f$
*/
A_EXTERN a_complex_s a_complex_sqrt(a_complex_s z);

/*!
 @brief complex square root of a real number
 @param x a real number
 @return = \f$ \sqrt{x} \f$
*/
A_EXTERN a_complex_s a_complex_sqrt_real(a_float_t x);

/*!
 @brief complex number z raised to complex power a
 @param z a complex number
 @param a a complex number
 @return = \f$ z^a \f$
*/
A_EXTERN a_complex_s a_complex_pow(a_complex_s z, a_complex_s a);

/*!
 @brief complex number z raised to real power a
 @param z a complex number
 @param a a real number
 @return = \f$ z^a \f$
*/
A_EXTERN a_complex_s a_complex_pow_real(a_complex_s z, a_float_t a);

/*!
 @brief computes the complex base-e exponential
 @param z a complex number
 @return = \f$ e^z \f$
*/
A_EXTERN a_complex_s a_complex_exp(a_complex_s z);

/*!
 @brief computes the complex natural logarithm
 @param z a complex number
 @return = \f$ \ln{z} \f$
*/
A_EXTERN a_complex_s a_complex_log(a_complex_s z);
/*!
 @brief computes the complex base-2 logarithm
 @param z a complex number
 @return = \f$ \log_{2}{z} \f$
*/
A_EXTERN a_complex_s a_complex_log2(a_complex_s z);
/*!
 @brief computes the complex base-10 logarithm
 @param z a complex number
 @return = \f$ \lg{z} \f$
*/
A_EXTERN a_complex_s a_complex_log10(a_complex_s z);
/*!
 @brief computes the complex base-b logarithm
 @param z a complex number
 @param b a complex number
 @return = \f$ \log_{b}{z} \f$
*/
A_EXTERN a_complex_s a_complex_logb(a_complex_s z, a_complex_s b);

/* Complex Trigonometric Functions */

/*!
 @brief computes the complex sine \f[ \sin(z)=\frac{\exp(z{i})-\exp(-z{i})}{2{i}} \f]
 @param z a complex number
 @return = \f$ \sin(z) \f$
*/
A_EXTERN a_complex_s a_complex_sin(a_complex_s z);
/*!
 @brief computes the complex cosine \f[ \cos(z)=\frac{\exp(z{i})+\exp(-z{i})}{2} \f]
 @param z a complex number
 @return = \f$ \cos(z) \f$
*/
A_EXTERN a_complex_s a_complex_cos(a_complex_s z);
/*!
 @brief computes the complex tangent \f[ \tan(z)=\frac{\sin(z)}{\cos(z)} \f]
 @param z a complex number
 @return = \f$ \tan(z) \f$
*/
A_EXTERN a_complex_s a_complex_tan(a_complex_s z);
/*!
 @brief computes the complex secant \f[ \sec(z)=\frac{1}{\cos(z)} \f]
 @param z a complex number
 @return = \f$ \sec(z) \f$
*/
A_EXTERN a_complex_s a_complex_sec(a_complex_s z);
/*!
 @brief computes the complex cosecant \f[ \csc(z)=\frac{1}{\sin(z)} \f]
 @param z a complex number
 @return = \f$ \csc(z) \f$
*/
A_EXTERN a_complex_s a_complex_csc(a_complex_s z);
/*!
 @brief computes the complex cotangent \f[ \cot(z)=\frac{1}{\tan(z)} \f]
 @param z a complex number
 @return = \f$ \cot(z) \f$
*/
A_EXTERN a_complex_s a_complex_cot(a_complex_s z);

/* Inverse Complex Trigonometric Functions */

/*!
 @brief computes the complex arc sine
 @param z a complex number
 @return = \f$ \arcsin(z) \f$
*/
A_EXTERN a_complex_s a_complex_asin(a_complex_s z);
A_EXTERN a_complex_s a_complex_asin_real(a_float_t x);
/*!
 @brief computes the complex arc cosine
 @param z a complex number
 @return = \f$ \arccos(z) \f$
*/
A_EXTERN a_complex_s a_complex_acos(a_complex_s z);
A_EXTERN a_complex_s a_complex_acos_real(a_float_t x);
/*!
 @brief computes the complex arc tangent
 @param z a complex number
 @return = \f$ \arctan(z) \f$
*/
A_EXTERN a_complex_s a_complex_atan(a_complex_s z);
/*!
 @brief computes the complex arc secant \f[ \mathrm{arcsec}(z)=\mathrm{arccos}(\frac{1}{z}) \f]
 @param z a complex number
 @return = \f$ \mathrm{arcsec}(z) \f$
*/
A_EXTERN a_complex_s a_complex_asec(a_complex_s z);
A_EXTERN a_complex_s a_complex_asec_real(a_float_t x);
/*!
 @brief computes the complex arc cosecant \f[ \mathrm{arccsc}(z)=\mathrm{arcsin}(\frac{1}{z}) \f]
 @param z a complex number
 @return = \f$ \mathrm{arccsc}(z) \f$
*/
A_EXTERN a_complex_s a_complex_acsc(a_complex_s z);
A_EXTERN a_complex_s a_complex_acsc_real(a_float_t x);
/*!
 @brief computes the complex arc cotangent \f[ \mathrm{arccot}(z)=\mathrm{arctan}(\frac{1}{z}) \f]
 @param z a complex number
 @return = \f$ \mathrm{arccot}(z) \f$
*/
A_EXTERN a_complex_s a_complex_acot(a_complex_s z);

/* Complex Hyperbolic Functions */

/*!
 @brief computes the complex hyperbolic sine \f[ \sinh(z)=\frac{\exp(z)-\exp(-z)}{2} \f]
 @param z a complex number
 @return = \f$ \sinh(z) \f$
*/
A_EXTERN a_complex_s a_complex_sinh(a_complex_s z);
/*!
 @brief computes the complex hyperbolic cosine \f[ \cosh(z)=\frac{\exp(z)+\exp(-z)}{2} \f]
 @param z a complex number
 @return = \f$ \cosh(z) \f$
*/
A_EXTERN a_complex_s a_complex_cosh(a_complex_s z);
/*!
 @brief computes the complex hyperbolic tangent \f[ \tanh(z)=\frac{\sinh(z)}{\cosh(z)} \f]
 @param z a complex number
 @return = \f$ \tanh(z) \f$
*/
A_EXTERN a_complex_s a_complex_tanh(a_complex_s z);
/*!
 @brief computes the complex hyperbolic secant \f[ \mathrm{sech}(z)=\frac{1}{\cosh(z)} \f]
 @param z a complex number
 @return = \f$ \mathrm{sech}(z) \f$
*/
A_EXTERN a_complex_s a_complex_sech(a_complex_s z);
/*!
 @brief computes the complex hyperbolic cosecant \f[ \mathrm{csch}(z)=\frac{1}{\sinh(z)} \f]
 @param z a complex number
 @return = \f$ \mathrm{csch}(z) \f$
*/
A_EXTERN a_complex_s a_complex_csch(a_complex_s z);
/*!
 @brief computes the complex hyperbolic cotangent \f[ \mathrm{coth}(z)=\frac{1}{\tanh(z)} \f]
 @param z a complex number
 @return = \f$ \mathrm{coth}(z) \f$
*/
A_EXTERN a_complex_s a_complex_coth(a_complex_s z);

/* Inverse Complex Hyperbolic Functions */

/*!
 @brief computes the complex arc hyperbolic sine
 @param z a complex number
 @return = \f$ \mathrm{arcsinh}(z) \f$
*/
A_EXTERN a_complex_s a_complex_asinh(a_complex_s z);
/*!
 @brief computes the complex arc hyperbolic cosine \f[ \mathrm{arccosh}(z)=\log(z-\sqrt{z^2-1}) \f]
 @param z a complex number
 @return = \f$ \mathrm{arccosh}(z) \f$
*/
A_EXTERN a_complex_s a_complex_acosh(a_complex_s z);
A_EXTERN a_complex_s a_complex_acosh_real(a_float_t x);
/*!
 @brief computes the complex arc hyperbolic tangent
 @param z a complex number
 @return = \f$ \mathrm{arctanh}(z) \f$
*/
A_EXTERN a_complex_s a_complex_atanh(a_complex_s z);
A_EXTERN a_complex_s a_complex_atanh_real(a_float_t x);
/*!
 @brief computes the complex arc hyperbolic secant \f[ \mathrm{arcsech}(z)=\mathrm{arccosh}(\frac{1}{z}) \f]
 @param z a complex number
 @return = \f$ \mathrm{arcsech}(z) \f$
*/
A_EXTERN a_complex_s a_complex_asech(a_complex_s z);
/*!
 @brief computes the complex arc hyperbolic cosecant \f[ \mathrm{arccsch}(z)=\mathrm{arcsinh}(\frac{1}{z}) \f]
 @param z a complex number
 @return = \f$ \mathrm{arccsch}(z) \f$
*/
A_EXTERN a_complex_s a_complex_acsch(a_complex_s z);
/*!
 @brief computes the complex arc hyperbolic cotangent \f[ \mathrm{arccoth}(z)=\mathrm{arctanh}(\frac{1}{z}) \f]
 @param z a complex number
 @return = \f$ \mathrm{arccoth}(z) \f$
*/
A_EXTERN a_complex_s a_complex_acoth(a_complex_s z);

#if defined(LIBA_COMPLEX_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_COMPLEX_C */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_COMPLEX */

#endif /* a/complex.h */
