/*!
 @file math.h
 @brief mathematical algorithm library
*/

#ifndef LIBA_MATH_H
#define LIBA_MATH_H

#include "a.h"
#include <math.h>

/*!
 @ingroup A
 @addtogroup A_MATH mathematical algorithm library
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
 @brief reciprocal of square-root, \f$ \frac{1}{\sqrt{x}} \f$
 @details http://en.wikipedia.org/wiki/Fast_inverse_square_root
 @param[in] x independent variable
 @return calculated result
*/
A_EXTERN a_f32 a_f32_rsqrt(a_f32 x);
A_EXTERN a_f64 a_f64_rsqrt(a_f64 x);

/*!
 @brief square root of an unsigned integer
 @param[in] x independent variable
 @return calculated result
*/
A_EXTERN a_u16 a_u32_sqrt(a_u32 x);
A_EXTERN a_u32 a_u64_sqrt(a_u64 x);

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

/*! @} A_MATH */

/*!
 @ingroup A
 @addtogroup A_FLOAT floating-point number
 @{
*/

/*! \f$ e \f$ */
#define A_FLOAT_E A_FLOAT_C(A_E)
/*! \f$ \log_{2}{e}=\frac{1}{\ln{2}} \f$ */
#define A_FLOAT_LOG2E A_FLOAT_C(A_LOG2E)
/*! \f$ \lg{e}=\frac{1}{\ln{2}+\ln{5}} \f$ */
#define A_FLOAT_LOG10E A_FLOAT_C(A_LOG10E)
/*! \f$ \ln{2} \f$ */
#define A_FLOAT_LN2 A_FLOAT_C(A_LN2)
/*! \f$ \frac{1}{\ln{2}} \f$ */
#define A_FLOAT_LN1_2 A_FLOAT_C(A_LN1_2)
/*! \f$ \ln{10} \f$ */
#define A_FLOAT_LN10 A_FLOAT_C(A_LN10)
/*! \f$ \frac{1}{\ln{10}} \f$ */
#define A_FLOAT_LN1_10 A_FLOAT_C(A_LN1_10)
/*! \f$ \pi \f$ */
#define A_FLOAT_PI A_FLOAT_C(A_PI)
/*! \f$ 2\pi \f$ */
#define A_FLOAT_TAU A_FLOAT_C(A_TAU)
/*! \f$ \frac{\pi}{2} \f$ */
#define A_FLOAT_PI_2 A_FLOAT_C(A_PI_2)
/*! \f$ \frac{\pi}{4} \f$ */
#define A_FLOAT_PI_4 A_FLOAT_C(A_PI_4)
/*! \f$ \frac{1}{\pi} \f$ */
#define A_FLOAT_1_PI A_FLOAT_C(A_1_PI)
/*! \f$ \frac{2}{\pi} \f$ */
#define A_FLOAT_2_PI A_FLOAT_C(A_2_PI)
/*! \f$ \frac{1}{2\pi} \f$ */
#define A_FLOAT_1_TAU A_FLOAT_C(A_1_TAU)
/*! \f$ \frac{2}{\sqrt{\pi}} \f$ */
#define A_FLOAT_2_SQRTPI A_FLOAT_C(A_2_SQRTPI)
/*! \f$ \sqrt{2} \f$ */
#define A_FLOAT_SQRT2 A_FLOAT_C(A_SQRT2)
/*! \f$ \frac{1}{\sqrt{2}}=\frac{\sqrt{2}}{2} \f$ */
#define A_FLOAT_SQRT1_2 A_FLOAT_C(A_SQRT1_2)
/*! \f$ \sqrt{3} \f$ */
#define A_FLOAT_SQRT3 A_FLOAT_C(A_SQRT3)
/*! \f$ \frac{1}{\sqrt{3}}=\frac{\sqrt{3}}{3} \f$ */
#define A_FLOAT_SQRT1_3 A_FLOAT_C(A_SQRT1_3)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_EXTERN a_float a_float_expm1(a_float x);
A_EXTERN a_float a_float_log1p(a_float x);
A_EXTERN a_float a_float_atan2(a_float x, a_float y);
A_EXTERN a_float a_float_hypot(a_float x, a_float y);
A_EXTERN a_float a_float_hypot3(a_float x, a_float y, a_float z);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#define a_float_modf A_FLOAT_F(modf)
#define a_float_frexp A_FLOAT_F(frexp)
#define a_float_ldexp A_FLOAT_F(ldexp)
#define a_float_scalbn A_FLOAT_F(scalbn)
#define a_float_scalbln A_FLOAT_F(scalbln)
#define a_float_nextafter A_FLOAT_F(nextafter)
#define a_float_nexttoward A_FLOAT_F(nexttoward)
#define a_float_copysign A_FLOAT_F(copysign)

#define a_float_ma A_FLOAT_F(fma)
#define a_float_nan A_FLOAT_F(nan)
#define a_float_abs A_FLOAT_F(fabs)
#define a_float_mod A_FLOAT_F(fmod)
#define a_float_max A_FLOAT_F(fmax)
#define a_float_min A_FLOAT_F(fmin)
#define a_float_dim A_FLOAT_F(fdim)
#define a_float_remquo A_FLOAT_F(remquo)
#define a_float_remainder A_FLOAT_F(remainder)

#define a_float_exp A_FLOAT_F(exp)
#define a_float_exp2 A_FLOAT_F(exp2)
#if defined(A_HAVE_EXPM1) && (A_HAVE_EXPM1 + 0 > 0)
#define a_float_expm1 A_FLOAT_F(expm1)
#endif /* A_HAVE_EXPM1 */

#define a_float_log A_FLOAT_F(log)
#define a_float_logb A_FLOAT_F(logb)
#define a_float_log2 A_FLOAT_F(log2)
#define a_float_log10 A_FLOAT_F(log10)
#if defined(A_HAVE_LOG1P) && (A_HAVE_LOG1P + 0 > 0)
#define a_float_log1p A_FLOAT_F(log1p)
#endif /* A_HAVE_LOG1P */
#define a_float_ilogb A_FLOAT_F(ilogb)

#define a_float_pow A_FLOAT_F(pow)
#define a_float_sqrt A_FLOAT_F(sqrt)
#define a_float_cbrt A_FLOAT_F(cbrt)
#if defined(A_HAVE_HYPOT) && (A_HAVE_HYPOT + 0 > 0)
#define a_float_hypot A_FLOAT_F(hypot)
#endif /* A_HAVE_HYPOT */

#define a_float_sin A_FLOAT_F(sin)
#define a_float_cos A_FLOAT_F(cos)
#define a_float_tan A_FLOAT_F(tan)
#define a_float_asin A_FLOAT_F(asin)
#define a_float_acos A_FLOAT_F(acos)
#define a_float_atan A_FLOAT_F(atan)
#if defined(A_HAVE_ATAN2) && (A_HAVE_ATAN2 + 0 > 0)
#define a_float_atan2 A_FLOAT_F(atan2)
#endif /* A_HAVE_ATAN2 */

#define a_float_sinh A_FLOAT_F(sinh)
#define a_float_cosh A_FLOAT_F(cosh)
#define a_float_tanh A_FLOAT_F(tanh)
#define a_float_asinh A_FLOAT_F(asinh)
#define a_float_acosh A_FLOAT_F(acosh)
#define a_float_atanh A_FLOAT_F(atanh)

#define a_float_erf A_FLOAT_F(erf)
#define a_float_erfc A_FLOAT_F(erfc)
#define a_float_tgamma A_FLOAT_F(tgamma)
#define a_float_lgamma A_FLOAT_F(lgamma)

#define a_float_ceil A_FLOAT_F(ceil)
#define a_float_floor A_FLOAT_F(floor)
#define a_float_trunc A_FLOAT_F(trunc)
#define a_float_round A_FLOAT_F(round)
#define a_float_lround A_FLOAT_F(lround)
#define a_float_llround A_FLOAT_F(llround)
#define a_float_nearbyint A_FLOAT_F(nearbyint)
#define a_float_rint A_FLOAT_F(rint)
#define a_float_lrintt A_FLOAT_F(lrint)
#define a_float_llrintt A_FLOAT_F(llrint)

/*! @} A_FLOAT */

#endif /* a/math.h */
