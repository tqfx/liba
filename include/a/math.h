/*!
 @file math.h
 @brief mathematical algorithm library
*/

#ifndef LIBA_MATH_H
#define LIBA_MATH_H

#include "a.h"
#include <math.h>

/*!
 @ingroup liba
 @addtogroup a_math mathematical algorithm library
 @{
*/

/*! \f$ e \f$ */
#define A_E 2.71828182845904523536
/*! \f$ \log_{2}{e}=\frac{1}{\ln{2}} \f$ */
#define A_LOG2E 1.44269504088896340736
/*! \f$ \lg{e}=\frac{1}{\ln{2}+\ln{5}} \f$ */
#define A_LOG10E 0.434294481903251827651
/*! \f$ \ln{2} \f$ */
#define A_LN2 0.693147180559945309417
/*! \f$ \frac{1}{\ln{2}} \f$ */
#define A_LN1_2 3.32192809488736218171
/*! \f$ \ln{10} \f$ */
#define A_LN10 2.30258509299404568402
/*! \f$ \frac{1}{\ln{10}} \f$ */
#define A_LN1_10 0.434294481903251827651
/*! \f$ \pi \f$ */
#define A_PI 3.14159265358979323846
/*! \f$ 2\pi \f$ */
#define A_TAU 6.28318530717958647693
/*! \f$ \frac{\pi}{2} \f$ */
#define A_PI_2 1.57079632679489661923
/*! \f$ \frac{\pi}{4} \f$ */
#define A_PI_4 0.785398163397448309616
/*! \f$ \frac{1}{\pi} \f$ */
#define A_1_PI 0.318309886183790671538
/*! \f$ \frac{2}{\pi} \f$ */
#define A_2_PI 0.636619772367581343076
/*! \f$ \frac{1}{2\pi} \f$ */
#define A_1_TAU 0.159154943091895335769
/*! \f$ \frac{2}{\sqrt{\pi}} \f$ */
#define A_2_SQRTPI 1.12837916709551257390
/*! \f$ \sqrt{2} \f$ */
#define A_SQRT2 1.41421356237309504880
/*! \f$ \frac{1}{\sqrt{2}}=\frac{\sqrt{2}}{2} \f$ */
#define A_SQRT1_2 0.707106781186547524401
/*! \f$ \sqrt{3} \f$ */
#define A_SQRT3 1.73205080756887729352
/*! \f$ \frac{1}{\sqrt{3}}=\frac{\sqrt{3}}{3} \f$ */
#define A_SQRT1_3 0.57735026918962576450

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief compute the greatest common divisor of two unsigned integers
 @param[in] a unsigned integer
 @param[in] b unsigned integer
 @return greatest common divisor
*/
A_EXTERN a_u32 a_u32_gcd(a_u32 a, a_u32 b);
A_EXTERN a_u64 a_u64_gcd(a_u64 a, a_u64 b);

/*!
 @brief compute the least common multiple of two unsigned integers
 @param[in] a unsigned integer
 @param[in] b unsigned integer
 @return least common multiple
*/
A_EXTERN a_u32 a_u32_lcm(a_u32 a, a_u32 b);
A_EXTERN a_u64 a_u64_lcm(a_u64 a, a_u64 b);

/*!
 @brief compute the square root of an unsigned integer
 @param[in] x independent variable
 @return square root
*/
A_EXTERN a_u16 a_u32_sqrt(a_u32 x);
A_EXTERN a_u32 a_u64_sqrt(a_u64 x);

/*!
 @brief compute the reciprocal of square-root, \f$ \frac{1}{\sqrt{x}} \f$
 @details http://en.wikipedia.org/wiki/Fast_inverse_square_root
 @param[in] x independent variable
 @return reciprocal of square-root
*/
A_EXTERN a_f32 a_f32_rsqrt(a_f32 x);
A_EXTERN a_f64 a_f64_rsqrt(a_f64 x);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#define a_f32_modf A_F32_F(modf)
#define a_f32_frexp A_F32_F(frexp)
#define a_f32_ldexp A_F32_F(ldexp)
#define a_f32_scalbn A_F32_F(scalbn)
#define a_f32_scalbln A_F32_F(scalbln)
#define a_f32_nextafter A_F32_F(nextafter)
#define a_f32_nexttoward A_F32_F(nexttoward)
#define a_f32_copysign A_F32_F(copysign)

#define a_f32_ma A_F32_F(fma)
#define a_f32_nan A_F32_F(nan)
#define a_f32_abs A_F32_F(fabs)
#define a_f32_mod A_F32_F(fmod)
#define a_f32_max A_F32_F(fmax)
#define a_f32_min A_F32_F(fmin)
#define a_f32_dim A_F32_F(fdim)
#define a_f32_remquo A_F32_F(remquo)
#define a_f32_remainder A_F32_F(remainder)

#define a_f32_exp A_F32_F(exp)
#define a_f32_exp2 A_F32_F(exp2)
#define a_f32_expm1 A_F32_F(expm1)

#define a_f32_log A_F32_F(log)
#define a_f32_logb A_F32_F(logb)
#define a_f32_log2 A_F32_F(log2)
#define a_f32_log10 A_F32_F(log10)
#define a_f32_log1p A_F32_F(log1p)
#define a_f32_ilogb A_F32_F(ilogb)

#define a_f32_pow A_F32_F(pow)
#define a_f32_sqrt A_F32_F(sqrt)
#define a_f32_cbrt A_F32_F(cbrt)
#define a_f32_hypot A_F32_F(hypot)

#define a_f32_sin A_F32_F(sin)
#define a_f32_cos A_F32_F(cos)
#define a_f32_tan A_F32_F(tan)
#define a_f32_asin A_F32_F(asin)
#define a_f32_acos A_F32_F(acos)
#define a_f32_atan A_F32_F(atan)
#define a_f32_atan2 A_F32_F(atan2)

#define a_f32_sinh A_F32_F(sinh)
#define a_f32_cosh A_F32_F(cosh)
#define a_f32_tanh A_F32_F(tanh)
#define a_f32_asinh A_F32_F(asinh)
#define a_f32_acosh A_F32_F(acosh)
#define a_f32_atanh A_F32_F(atanh)

#define a_f32_erf A_F32_F(erf)
#define a_f32_erfc A_F32_F(erfc)
#define a_f32_tgamma A_F32_F(tgamma)
#define a_f32_lgamma A_F32_F(lgamma)

#define a_f32_ceil A_F32_F(ceil)
#define a_f32_floor A_F32_F(floor)
#define a_f32_trunc A_F32_F(trunc)
#define a_f32_round A_F32_F(round)
#define a_f32_lround A_F32_F(lround)
#define a_f32_llround A_F32_F(llround)
#define a_f32_nearbyint A_F32_F(nearbyint)
#define a_f32_rint A_F32_F(rint)
#define a_f32_lrintt A_F32_F(lrint)
#define a_f32_llrintt A_F32_F(llrint)

#define a_f64_modf A_F64_F(modf)
#define a_f64_frexp A_F64_F(frexp)
#define a_f64_ldexp A_F64_F(ldexp)
#define a_f64_scalbn A_F64_F(scalbn)
#define a_f64_scalbln A_F64_F(scalbln)
#define a_f64_nextafter A_F64_F(nextafter)
#define a_f64_nexttoward A_F64_F(nexttoward)
#define a_f64_copysign A_F64_F(copysign)

#define a_f64_ma A_F64_F(fma)
#define a_f64_nan A_F64_F(nan)
#define a_f64_abs A_F64_F(fabs)
#define a_f64_mod A_F64_F(fmod)
#define a_f64_max A_F64_F(fmax)
#define a_f64_min A_F64_F(fmin)
#define a_f64_dim A_F64_F(fdim)
#define a_f64_remquo A_F64_F(remquo)
#define a_f64_remainder A_F64_F(remainder)

#define a_f64_exp A_F64_F(exp)
#define a_f64_exp2 A_F64_F(exp2)
#define a_f64_expm1 A_F64_F(expm1)

#define a_f64_log A_F64_F(log)
#define a_f64_logb A_F64_F(logb)
#define a_f64_log2 A_F64_F(log2)
#define a_f64_log10 A_F64_F(log10)
#define a_f64_log1p A_F64_F(log1p)
#define a_f64_ilogb A_F64_F(ilogb)

#define a_f64_pow A_F64_F(pow)
#define a_f64_sqrt A_F64_F(sqrt)
#define a_f64_cbrt A_F64_F(cbrt)
#define a_f64_hypot A_F64_F(hypot)

#define a_f64_sin A_F64_F(sin)
#define a_f64_cos A_F64_F(cos)
#define a_f64_tan A_F64_F(tan)
#define a_f64_asin A_F64_F(asin)
#define a_f64_acos A_F64_F(acos)
#define a_f64_atan A_F64_F(atan)
#define a_f64_atan2 A_F64_F(atan2)

#define a_f64_sinh A_F64_F(sinh)
#define a_f64_cosh A_F64_F(cosh)
#define a_f64_tanh A_F64_F(tanh)
#define a_f64_asinh A_F64_F(asinh)
#define a_f64_acosh A_F64_F(acosh)
#define a_f64_atanh A_F64_F(atanh)

#define a_f64_erf A_F64_F(erf)
#define a_f64_erfc A_F64_F(erfc)
#define a_f64_tgamma A_F64_F(tgamma)
#define a_f64_lgamma A_F64_F(lgamma)

#define a_f64_ceil A_F64_F(ceil)
#define a_f64_floor A_F64_F(floor)
#define a_f64_trunc A_F64_F(trunc)
#define a_f64_round A_F64_F(round)
#define a_f64_lround A_F64_F(lround)
#define a_f64_llround A_F64_F(llround)
#define a_f64_nearbyint A_F64_F(nearbyint)
#define a_f64_rint A_F64_F(rint)
#define a_f64_lrintt A_F64_F(lrint)
#define a_f64_llrintt A_F64_F(llrint)

/*! @} a_math */

/*!
 @ingroup liba
 @addtogroup a_real floating-point number
 @{
*/

/*! \f$ e \f$ */
#define A_REAL_E A_REAL_C(A_E)
/*! \f$ \log_{2}{e}=\frac{1}{\ln{2}} \f$ */
#define A_REAL_LOG2E A_REAL_C(A_LOG2E)
/*! \f$ \lg{e}=\frac{1}{\ln{2}+\ln{5}} \f$ */
#define A_REAL_LOG10E A_REAL_C(A_LOG10E)
/*! \f$ \ln{2} \f$ */
#define A_REAL_LN2 A_REAL_C(A_LN2)
/*! \f$ \frac{1}{\ln{2}} \f$ */
#define A_REAL_LN1_2 A_REAL_C(A_LN1_2)
/*! \f$ \ln{10} \f$ */
#define A_REAL_LN10 A_REAL_C(A_LN10)
/*! \f$ \frac{1}{\ln{10}} \f$ */
#define A_REAL_LN1_10 A_REAL_C(A_LN1_10)
/*! \f$ \pi \f$ */
#define A_REAL_PI A_REAL_C(A_PI)
/*! \f$ 2\pi \f$ */
#define A_REAL_TAU A_REAL_C(A_TAU)
/*! \f$ \frac{\pi}{2} \f$ */
#define A_REAL_PI_2 A_REAL_C(A_PI_2)
/*! \f$ \frac{\pi}{4} \f$ */
#define A_REAL_PI_4 A_REAL_C(A_PI_4)
/*! \f$ \frac{1}{\pi} \f$ */
#define A_REAL_1_PI A_REAL_C(A_1_PI)
/*! \f$ \frac{2}{\pi} \f$ */
#define A_REAL_2_PI A_REAL_C(A_2_PI)
/*! \f$ \frac{1}{2\pi} \f$ */
#define A_REAL_1_TAU A_REAL_C(A_1_TAU)
/*! \f$ \frac{2}{\sqrt{\pi}} \f$ */
#define A_REAL_2_SQRTPI A_REAL_C(A_2_SQRTPI)
/*! \f$ \sqrt{2} \f$ */
#define A_REAL_SQRT2 A_REAL_C(A_SQRT2)
/*! \f$ \frac{1}{\sqrt{2}}=\frac{\sqrt{2}}{2} \f$ */
#define A_REAL_SQRT1_2 A_REAL_C(A_SQRT1_2)
/*! \f$ \sqrt{3} \f$ */
#define A_REAL_SQRT3 A_REAL_C(A_SQRT3)
/*! \f$ \frac{1}{\sqrt{3}}=\frac{\sqrt{3}}{3} \f$ */
#define A_REAL_SQRT1_3 A_REAL_C(A_SQRT1_3)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_EXTERN a_real a_real_asinh(a_real x);
A_EXTERN a_real a_real_acosh(a_real x);
A_EXTERN a_real a_real_atanh(a_real x);
A_EXTERN a_real a_real_expm1(a_real x);
A_EXTERN a_real a_real_log1p(a_real x);
A_EXTERN a_real a_real_atan2(a_real y, a_real x);
A_EXTERN a_real a_real_norm2(a_real x, a_real y);
A_EXTERN a_real a_real_norm3(a_real x, a_real y, a_real z);

/*!
 @brief compute the magnitude of a vector
 @param[in] n number of a float array
 @param[in] p points to a float array
 @return the magnitude of a vector
*/
A_EXTERN a_real a_real_norm(a_size n, a_real const *p);
A_EXTERN a_real a_real_norm_(a_size n, a_real const *p, a_size c);

/*!
 @brief compute the sum of a float array
 @param[in] n number of a float array
 @param[in] p points to a float array
 @return sum of a float array
*/
A_EXTERN a_real a_real_sum(a_size n, a_real const *p);
A_EXTERN a_real a_real_sum_(a_size n, a_real const *p, a_size c);

/*!
 @brief compute the absolute sum of a float array
 @param[in] n number of a float array
 @param[in] p points to a float array
 @return absolute sum of a float array
*/
A_EXTERN a_real a_real_sum1(a_size n, a_real const *p);
A_EXTERN a_real a_real_sum1_(a_size n, a_real const *p, a_size c);

/*!
 @brief compute the sum of squares of a float array
 @param[in] n number of a float array
 @param[in] p points to a float array
 @return sum of squares of a float array
*/
A_EXTERN a_real a_real_sum2(a_size n, a_real const *p);
A_EXTERN a_real a_real_sum2_(a_size n, a_real const *p, a_size c);

/*!
 @brief compute the mean of a float array
 @param[in] n number of a float array
 @param[in] p points to a float array
 @return mean of a float array
*/
A_EXTERN a_real a_real_mean(a_size n, a_real const *p);
A_EXTERN a_real a_real_mean_(a_size n, a_real const *p, a_size c);

/*!
 @brief compute the dot product of two vectors.
 @param[in] n number of elements in each of the vectors X and Y.
 @param[in] X points to the first vector.
 @param[in] Y points to the second vector.
 @return dot product of vectors X and Y.
*/
A_EXTERN a_real a_real_dot(a_size n, a_real const *X, a_real const *Y);

/*!
 @brief compute the dot product of two vectors.
 @param[in] n number of elements in each of the vectors X and Y.
 @param[in] X points to the first vector.
 @param[in] Xc increment of the first vector.
 @param[in] Y points to the second vector.
 @param[in] Yc increment of the second vector.
 @return dot product of vectors X and Y.
*/
A_EXTERN a_real a_real_dot_(a_size n, a_real const *X, a_size Xc, a_real const *Y, a_size Yc);

/*!
 @brief copy `n` elements from the source array `src` to the destination array `dst`.
 @param[in] n number of elements to copy
 @param[out] dst points to the destination array
 @param[in] src points to the source array
*/
A_EXTERN A_NONULL((2, 3)) void a_real_copy(a_size n, a_real *__restrict dst, a_real const *__restrict src);
A_EXTERN void a_real_copy_(a_size n, a_real *dst, a_size dc, a_real const *src, a_size sc);

/*!
 @brief swap two different a_real blocks of the same size
 @param[in] n the number of a_real block being swapped
 @param[in,out] lhs points to a_real block on the left
 @param[in,out] rhs points to a_real block on the right
*/
A_EXTERN A_NONULL((2, 3)) void a_real_swap(a_size n, a_real *__restrict lhs, a_real *__restrict rhs);
A_EXTERN void a_real_swap_(a_size n, a_real *lhs, a_size lc, a_real *rhs, a_size rc);

/*!
 @brief fill an array of `a_real` numbers with a specified value.
 @param[in] n number of elements in the array to fill.
 @param[out] p points to the array to fill with the value `v`.
 @param[in] v the value to fill the array with.
*/
A_EXTERN void a_real_fill(a_size n, a_real *p, a_real v);

/*!
 @brief set all elements of an array of `a_real` numbers to zero.
 @param[in] n the number of elements in the array to set to zero.
 @param[out] p points to the array whose elements will be set to zero.
*/
A_EXTERN void a_real_zero(a_size n, a_real *p);

/*!
 @brief push an element into the front of a float array
 @param[in] p points to a float array
 @param[in] n number of a float array
 @param[in] x value
*/
A_EXTERN void a_real_push_fore(a_real *p, a_size n, a_real x);

/*!
 @brief push an element into the end of a float array
 @param[in] p points to a float array
 @param[in] n number of a float array
 @param[in] x value
*/
A_EXTERN void a_real_push_back(a_real *p, a_size n, a_real x);

/*!
 @brief push the elements into the front of a float array
 @param[in] block_p points to a float array
 @param[in] block_n number of a float array
 @param[in] cache_p points to a cache array
 @param[in] cache_n number of a cache array
*/
A_EXTERN void a_real_push_fore_(a_real *block_p, a_size block_n,
                                a_real const *cache_p, a_size cache_n);

/*!
 @brief push the elements into the end of a float array
 @param[in] block_p points to a float array
 @param[in] block_n number of a float array
 @param[in] cache_p points to a cache array
 @param[in] cache_n number of a cache array
*/
A_EXTERN void a_real_push_back_(a_real *block_p, a_size block_n,
                                a_real const *cache_p, a_size cache_n);

/*!
 @brief roll forward the elements of a float array circularly
 @param[in] p points to a float array
 @param[in] n number of a float array
*/
A_EXTERN void a_real_roll_fore(a_real *p, a_size n);

/*!
 @brief roll backward the elements of a float array circularly
 @param[in] p points to a float array
 @param[in] n number of a float array
*/
A_EXTERN void a_real_roll_back(a_real *p, a_size n);

/*!
 @brief roll forward the elements of a float array circularly
 @param[in] block_p points to a float array
 @param[in] block_n number of a float array
 @param[in] shift_p points to a shift array
 @param[in] shift_n number of a shift array
*/
A_EXTERN void a_real_roll_fore_(a_real *block_p, a_size block_n,
                                a_real *shift_p, a_size shift_n);

/*!
 @brief roll backward the elements of a float array circularly
 @param[in] block_p points to a float array
 @param[in] block_n number of a float array
 @param[in] shift_p points to a shift array
 @param[in] shift_n number of a shift array
*/
A_EXTERN void a_real_roll_back_(a_real *block_p, a_size block_n,
                                a_real *shift_p, a_size shift_n);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#define a_real_modf A_REAL_F(modf)
#define a_real_frexp A_REAL_F(frexp)
#define a_real_ldexp A_REAL_F(ldexp)
#define a_real_scalbn A_REAL_F(scalbn)
#define a_real_scalbln A_REAL_F(scalbln)
#define a_real_nextafter A_REAL_F(nextafter)
#define a_real_nexttoward A_REAL_F(nexttoward)
#define a_real_copysign A_REAL_F(copysign)

#define a_real_ma A_REAL_F(fma)
#define a_real_nan A_REAL_F(nan)
#define a_real_abs A_REAL_F(fabs)
#define a_real_mod A_REAL_F(fmod)
#define a_real_max A_REAL_F(fmax)
#define a_real_min A_REAL_F(fmin)
#define a_real_dim A_REAL_F(fdim)
#define a_real_remquo A_REAL_F(remquo)
#define a_real_remainder A_REAL_F(remainder)

#define a_real_exp A_REAL_F(exp)
#define a_real_exp2 A_REAL_F(exp2)
#if defined(A_HAVE_EXPM1) && (A_HAVE_EXPM1 + 0 > 0)
#define a_real_expm1 A_REAL_F(expm1)
#endif /* A_HAVE_EXPM1 */

#define a_real_log A_REAL_F(log)
#define a_real_logb A_REAL_F(logb)
#define a_real_log2 A_REAL_F(log2)
#define a_real_log10 A_REAL_F(log10)
#if defined(A_HAVE_LOG1P) && (A_HAVE_LOG1P + 0 > 0)
#define a_real_log1p A_REAL_F(log1p)
#endif /* A_HAVE_LOG1P */
#define a_real_ilogb A_REAL_F(ilogb)

#define a_real_pow A_REAL_F(pow)
#define a_real_sqrt A_REAL_F(sqrt)
#define a_real_cbrt A_REAL_F(cbrt)
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define a_real_hypot A_REAL_F(_hypot)
#elif defined(A_HAVE_HYPOT) && (A_HAVE_HYPOT + 0 > 0)
#define a_real_hypot A_REAL_F(hypot)
#else /* !A_HAVE_HYPOT */
#define a_real_hypot a_real_norm2
#endif /* A_HAVE_HYPOT */

#define a_real_sin A_REAL_F(sin)
#define a_real_cos A_REAL_F(cos)
#define a_real_tan A_REAL_F(tan)
#define a_real_asin A_REAL_F(asin)
#define a_real_acos A_REAL_F(acos)
#define a_real_atan A_REAL_F(atan)
#if defined(A_HAVE_ATAN2) && (A_HAVE_ATAN2 + 0 > 0)
#define a_real_atan2 A_REAL_F(atan2)
#endif /* A_HAVE_ATAN2 */

#define a_real_sinh A_REAL_F(sinh)
#define a_real_cosh A_REAL_F(cosh)
#define a_real_tanh A_REAL_F(tanh)
#if defined(A_HAVE_ASINH) && (A_HAVE_ASINH + 0 > 0)
#define a_real_asinh A_REAL_F(asinh)
#endif /* A_HAVE_ASINH */
#if defined(A_HAVE_ACOSH) && (A_HAVE_ACOSH + 0 > 0)
#define a_real_acosh A_REAL_F(acosh)
#endif /* A_HAVE_ACOSH */
#if defined(A_HAVE_ATANH) && (A_HAVE_ATANH + 0 > 0)
#define a_real_atanh A_REAL_F(atanh)
#endif /* A_HAVE_ATANH */

#define a_real_erf A_REAL_F(erf)
#define a_real_erfc A_REAL_F(erfc)
#define a_real_tgamma A_REAL_F(tgamma)
#define a_real_lgamma A_REAL_F(lgamma)

#define a_real_ceil A_REAL_F(ceil)
#define a_real_floor A_REAL_F(floor)
#define a_real_trunc A_REAL_F(trunc)
#define a_real_round A_REAL_F(round)
#define a_real_lround A_REAL_F(lround)
#define a_real_llround A_REAL_F(llround)
#define a_real_nearbyint A_REAL_F(nearbyint)
#define a_real_rint A_REAL_F(rint)
#define a_real_lrintt A_REAL_F(lrint)
#define a_real_llrintt A_REAL_F(llrint)

/*! @} a_real */

#endif /* a/math.h */
