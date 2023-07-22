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
/*! \f$ \ln{10} \f$ */
#define A_LN10 2.30258509299404568402
/*! \f$ \pi \f$ */
#define A_PI 3.14159265358979323846
/*! \f$ \frac{\pi}{2} \f$ */
#define A_PI_2 1.57079632679489661923
/*! \f$ \frac{\pi}{4} \f$ */
#define A_PI_4 0.785398163397448309616
/*! \f$ \frac{1}{\pi} \f$ */
#define A_1_PI 0.318309886183790671538
/*! \f$ \frac{2}{\pi} \f$ */
#define A_2_PI 0.636619772367581343076
/*! \f$ \frac{2}{\sqrt{\pi}} \f$ */
#define A_2_SQRTPI 1.12837916709551257390
/*! \f$ \sqrt{2} \f$ */
#define A_SQRT2 1.41421356237309504880
/*! \f$ \frac{1}{\sqrt{2}}=\frac{\sqrt{2}}{2} \f$ */
#define A_SQRT1_2 0.707106781186547524401

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_EXTERN a_f32_t a_f32_hypot(a_f32_t x, a_f32_t y);
A_EXTERN a_f64_t a_f64_hypot(a_f64_t x, a_f64_t y);

/*!
 @brief fast inverse square-root, \f$ \frac{1}{\sqrt{x}} \f$
 @details http://en.wikipedia.org/wiki/Fast_inverse_square_root
 @param[in] x independent variable
 @return calculated result
*/
A_EXTERN a_f32_t a_f32_rsqrt(a_f32_t x);
A_EXTERN a_f64_t a_f64_rsqrt(a_f64_t x);

/*!
 @brief square root of an unsigned integer
 @param[in] x independent variable
 @param[out] o store remainder
 @return calculated result
*/
A_EXTERN a_u32_t a_u32_sqrt(a_u32_t x, a_u32_t *o);
A_EXTERN a_u64_t a_u64_sqrt(a_u64_t x, a_u64_t *o);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#define a_f32_fpclassify A_F32_F(fpclassify)
#define a_f32_copysign A_F32_F(copysign)
#define a_f32_isfinite A_F32_F(isfinite)
#define a_f32_isnormal A_F32_F(isnormal)
#define a_f32_signbit A_F32_F(signbit)
#define a_f32_isinf A_F32_F(isinf)
#define a_f32_isnan A_F32_F(isnan)
#define a_f32_islt A_F32_F(isless)
#define a_f32_isle A_F32_F(islessequal)
#define a_f32_isgt A_F32_F(isgreater)
#define a_f32_isge A_F32_F(isgreaterequal)
#define a_f32_islg A_F32_F(islessgreater)
#define a_f32_isun A_F32_F(isunordered)

#define a_f32_ma A_F32_F(fma)
#define a_f32_nan A_F32_F(nan)
#define a_f32_abs A_F32_F(fabs)
#define a_f32_mod A_F32_F(fmod)
#define a_f32_max A_F32_F(fmax)
#define a_f32_min A_F32_F(fmin)
#define a_f32_dim A_F32_F(fdim)

#define a_f32_exp A_F32_F(exp)
#define a_f32_exp2 A_F32_F(exp2)
#define a_f32_expm1 A_F32_F(expm1)

#define a_f32_log A_F32_F(log)
#define a_f32_logb A_F32_F(logb)
#define a_f32_log2 A_F32_F(log2)
#define a_f32_log10 A_F32_F(log10)
#define a_f32_log1p A_F32_F(log1p)

#define a_f32_pow A_F32_F(pow)
#define a_f32_sqrt A_F32_F(sqrt)
#define a_f32_cbrt A_F32_F(cbrt)
#if defined(A_HAVE_HYPOT)
#define a_f32_hypot A_F32_F(hypot)
#endif /* A_HAVE_HYPOT */

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

#define a_f64_fpclassify A_F64_F(fpclassify)
#define a_f64_copysign A_F64_F(copysign)
#define a_f64_isfinite A_F64_F(isfinite)
#define a_f64_isnormal A_F64_F(isnormal)
#define a_f64_signbit A_F64_F(signbit)
#define a_f64_isinf A_F64_F(isinf)
#define a_f64_isnan A_F64_F(isnan)
#define a_f64_islt A_F64_F(isless)
#define a_f64_isle A_F64_F(islessequal)
#define a_f64_isgt A_F64_F(isgreater)
#define a_f64_isge A_F64_F(isgreaterequal)
#define a_f64_islg A_F64_F(islessgreater)
#define a_f64_isun A_F64_F(isunordered)

#define a_f64_ma A_F64_F(fma)
#define a_f64_nan A_F64_F(nan)
#define a_f64_abs A_F64_F(fabs)
#define a_f64_mod A_F64_F(fmod)
#define a_f64_max A_F64_F(fmax)
#define a_f64_min A_F64_F(fmin)
#define a_f64_dim A_F64_F(fdim)

#define a_f64_exp A_F64_F(exp)
#define a_f64_exp2 A_F64_F(exp2)
#define a_f64_expm1 A_F64_F(expm1)

#define a_f64_log A_F64_F(log)
#define a_f64_logb A_F64_F(logb)
#define a_f64_log2 A_F64_F(log2)
#define a_f64_log10 A_F64_F(log10)
#define a_f64_log1p A_F64_F(log1p)

#define a_f64_pow A_F64_F(pow)
#define a_f64_sqrt A_F64_F(sqrt)
#define a_f64_cbrt A_F64_F(cbrt)
#if defined(A_HAVE_HYPOT)
#define a_f64_hypot A_F64_F(hypot)
#endif /* A_HAVE_HYPOT */

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
/*! \f$ \ln{10} \f$ */
#define A_FLOAT_LN10 A_FLOAT_C(A_LN10)
/*! \f$ \pi \f$ */
#define A_FLOAT_PI A_FLOAT_C(A_PI)
/*! \f$ \frac{\pi}{2} \f$ */
#define A_FLOAT_PI_2 A_FLOAT_C(A_PI_2)
/*! \f$ \frac{\pi}{4} \f$ */
#define A_FLOAT_PI_4 A_FLOAT_C(A_PI_4)
/*! \f$ \frac{1}{\pi} \f$ */
#define A_FLOAT_1_PI A_FLOAT_C(A_1_PI)
/*! \f$ \frac{2}{\pi} \f$ */
#define A_FLOAT_2_PI A_FLOAT_C(A_2_PI)
/*! \f$ \frac{2}{\sqrt{\pi}} \f$ */
#define A_FLOAT_2_SQRTPI A_FLOAT_C(A_2_SQRTPI)
/*! \f$ \sqrt{2} \f$ */
#define A_FLOAT_SQRT2 A_FLOAT_C(A_SQRT2)
/*! \f$ \frac{1}{\sqrt{2}}=\frac{\sqrt{2}}{2} \f$ */
#define A_FLOAT_SQRT1_2 A_FLOAT_C(A_SQRT1_2)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_EXTERN a_float_t a_float_log1p(a_float_t x);
A_EXTERN a_float_t a_float_hypot(a_float_t x, a_float_t y);
A_EXTERN a_float_t a_float_atan2(a_float_t x, a_float_t y);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#define a_float_fpclassify A_FLOAT_F(fpclassify)
#define a_float_copysign A_FLOAT_F(copysign)
#define a_float_isfinite A_FLOAT_F(isfinite)
#define a_float_isnormal A_FLOAT_F(isnormal)
#define a_float_signbit A_FLOAT_F(signbit)
#define a_float_isinf A_FLOAT_F(isinf)
#define a_float_isnan A_FLOAT_F(isnan)
#define a_float_islt A_FLOAT_F(isless)
#define a_float_isle A_FLOAT_F(islessequal)
#define a_float_isgt A_FLOAT_F(isgreater)
#define a_float_isge A_FLOAT_F(isgreaterequal)
#define a_float_islg A_FLOAT_F(islessgreater)
#define a_float_isun A_FLOAT_F(isunordered)

#define a_float_ma A_FLOAT_F(fma)
#define a_float_nan A_FLOAT_F(nan)
#define a_float_abs A_FLOAT_F(fabs)
#define a_float_mod A_FLOAT_F(fmod)
#define a_float_max A_FLOAT_F(fmax)
#define a_float_min A_FLOAT_F(fmin)
#define a_float_dim A_FLOAT_F(fdim)

#define a_float_exp A_FLOAT_F(exp)
#define a_float_exp2 A_FLOAT_F(exp2)
#define a_float_expm1 A_FLOAT_F(expm1)

#define a_float_log A_FLOAT_F(log)
#define a_float_logb A_FLOAT_F(logb)
#define a_float_log2 A_FLOAT_F(log2)
#define a_float_log10 A_FLOAT_F(log10)
#if defined(A_HAVE_LOG1P) && (A_HAVE_LOG1P + 0 > 0)
#define a_float_log1p A_FLOAT_F(log1p)
#endif /* A_HAVE_LOG1P */

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

/*! @} A_FLOAT */

#endif /* a/math.h */
