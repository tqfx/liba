/*!
 @file real.h
 @brief real number
*/

#ifndef LIBA_REAL_H
#define LIBA_REAL_H

#include "a.h"
#include "math.h"

/*!
 @ingroup A
 @addtogroup A_REAL real number
 @{
*/

/*! \f$ e \f$ */
#define A_REAL_E A_REAL_C(2.71828182845904523536)
/*! \f$ \log_{2}{e}=\frac{1}{\ln{2}} \f$ */
#define A_REAL_LOG2E A_REAL_C(1.44269504088896340736)
/*! \f$ \lg{e}=\frac{1}{\ln{2}+\ln{5}} \f$ */
#define A_REAL_LOG10E A_REAL_C(0.434294481903251827651)
/*! \f$ \ln{2} \f$ */
#define A_REAL_LN2 A_REAL_C(0.693147180559945309417)
/*! \f$ \ln{10} \f$ */
#define A_REAL_LN10 A_REAL_C(2.30258509299404568402)
/*! \f$ \pi \f$ */
#define A_REAL_PI A_REAL_C(3.14159265358979323846)
/*! \f$ \frac{\pi}{2} \f$ */
#define A_REAL_PI_2 A_REAL_C(1.57079632679489661923)
/*! \f$ \frac{\pi}{4} \f$ */
#define A_REAL_PI_4 A_REAL_C(0.785398163397448309616)
/*! \f$ \frac{1}{\pi} \f$ */
#define A_REAL_1_PI A_REAL_C(0.318309886183790671538)
/*! \f$ \frac{2}{\pi} \f$ */
#define A_REAL_2_PI A_REAL_C(0.636619772367581343076)
/*! \f$ \frac{2}{\sqrt{\pi}} \f$ */
#define A_REAL_2_SQRTPI A_REAL_C(1.12837916709551257390)
/*! \f$ \sqrt{2} \f$ */
#define A_REAL_SQRT2 A_REAL_C(1.41421356237309504880)
/*! \f$ \frac{1}{\sqrt{2}}=\frac{\sqrt{2}}{2} \f$ */
#define A_REAL_SQRT1_2 A_REAL_C(0.707106781186547524401)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_EXTERN a_real_t a_real_log1p(a_real_t x);
A_EXTERN a_real_t a_real_hypot(a_real_t x, a_real_t y);
A_EXTERN a_real_t a_real_atan2(a_real_t x, a_real_t y);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#define a_real_fpclassify A_REAL_F(fpclassify)
#define a_real_copysign A_REAL_F(copysign)
#define a_real_isfinite A_REAL_F(isfinite)
#define a_real_isnormal A_REAL_F(isnormal)
#define a_real_signbit A_REAL_F(signbit)
#define a_real_isinf A_REAL_F(isinf)
#define a_real_isnan A_REAL_F(isnan)
#define a_real_islt A_REAL_F(isless)
#define a_real_isle A_REAL_F(islessequal)
#define a_real_isgt A_REAL_F(isgreater)
#define a_real_isge A_REAL_F(isgreaterequal)
#define a_real_islg A_REAL_F(islessgreater)
#define a_real_isun A_REAL_F(isunordered)

#define a_real_ma A_REAL_F(fma)
#define a_real_nan A_REAL_F(nan)
#define a_real_abs A_REAL_F(fabs)
#define a_real_mod A_REAL_F(fmod)
#define a_real_max A_REAL_F(fmax)
#define a_real_min A_REAL_F(fmin)
#define a_real_dim A_REAL_F(fdim)

#define a_real_exp A_REAL_F(exp)
#define a_real_exp2 A_REAL_F(exp2)
#define a_real_expm1 A_REAL_F(expm1)

#define a_real_log A_REAL_F(log)
#define a_real_logb A_REAL_F(logb)
#define a_real_log2 A_REAL_F(log2)
#define a_real_log10 A_REAL_F(log10)
#if defined(A_HAVE_LOG1P) && (A_HAVE_LOG1P + 0 > 0)
#define a_real_log1p A_REAL_F(log1p)
#endif /* A_HAVE_LOG1P */

#define a_real_pow A_REAL_F(pow)
#define a_real_sqrt A_REAL_F(sqrt)
#define a_real_cbrt A_REAL_F(cbrt)
#if defined(A_HAVE_HYPOT) && (A_HAVE_HYPOT + 0 > 0)
#define a_real_hypot A_REAL_F(hypot)
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
#define a_real_asinh A_REAL_F(asinh)
#define a_real_acosh A_REAL_F(acosh)
#define a_real_atanh A_REAL_F(atanh)

/*! @} A_REAL */

#endif /* real.h */
