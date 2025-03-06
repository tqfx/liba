/*!
 @file lpf.h
 @brief Low Pass Filter
 @details
 low frequencies are passed, high frequencies are attenuated.
 \f[
  RC\frac{\text{d}V_{\mathrm o}}{\text{dt}}+V_{\mathrm o}=V_{\mathrm i}
 \f]
 \f[
  RC\frac{V_{\mathrm o}(n)-V_{\mathrm o}(n-1)}{T_s}+V_{\mathrm o}(n)=V_{\mathrm i}(n)
 \f]
 \f[
  V_{\mathrm o}(n)=\frac{RC}{RC+T_s}V_{\mathrm o}(n-1)+\frac{T_s}{RC+T_s}V_{\mathrm i}(n)
 \f]
 \f[
  V_{\mathrm o}(n)=(1-\alpha)V_{\mathrm o}(n-1)+\alpha V_{\mathrm i}(n)
 \f]
 \f[
  \alpha=\frac{T_s}{RC+T_s}=\frac{T_s}{{\frac{1}{2\pi f_c}}+T_s}
 \f]
 https://en.wikipedia.org/wiki/Low-pass_filter
*/

#ifndef LIBA_LPF_H
#define LIBA_LPF_H

#include "math.h"

/*!
 @ingroup liba
 @addtogroup a_lpf Low Pass Filter
 @{
*/

/*!
 @brief instance structure for Low Pass Filter
*/
typedef struct a_lpf
{
    a_real alpha; /*!< filter coefficient [0,1] */
    a_real output; /*!< filter output */
#if defined(__cplusplus)
    A_INLINE void gen(a_real fc, a_real ts)
    {
        alpha = ts / (A_REAL_1_TAU / fc + ts);
    }
    A_INLINE a_real operator()(a_real x)
    {
        output *= 1 - alpha;
        output += x * alpha;
        return output;
    }
    A_INLINE void zero() { output = 0; }
#endif /* __cplusplus */
} a_lpf;
#if defined(__cplusplus)
namespace a
{
typedef struct a_lpf lpf;
} /* namespace a */
#endif /* __cplusplus */
/* clang-format off */
#define A_LPF_1(alpha) {a_real_c(alpha), 0}
#define A_LPF_2(fc, ts) {A_LPF_GEN(fc, ts), 0}
/* clang-format on */
#define A_LPF_GEN(fc, ts) (a_real_c(ts) / (A_REAL_1_TAU / a_real_c(fc) + a_real_c(ts)))

/*!
 @brief generate for Low Pass Filter
 \f{cases}{
  \alpha=\frac{T_s}{RC+T_s},&\alpha\in[0,1]\\
  RC=\frac{1}{2\pi f_c}.
 \f}
 \f[
  \alpha=\frac{T_s}{\frac{1}{2\pi f_c}+T_s}
 \f]
 @param[in] fc cut-off frequency unit(hz)
 @param[in] ts sampling time unit(s)
 @return filter coefficient [0,1]
*/
A_INTERN a_real a_lpf_gen(a_real fc, a_real ts)
{
    return ts / (A_REAL_1_TAU / fc + ts);
}

/*!
 @brief initialize for Low Pass Filter
 @param[in,out] ctx points to an instance of Low Pass Filter
 @param[in] alpha filter coefficient [0,1]
*/
A_INTERN void a_lpf_init(a_lpf *ctx, a_real alpha)
{
    ctx->alpha = alpha;
    ctx->output = 0;
}

/*!
 @brief compute for Low Pass Filter
 \f[
  V_{\mathrm o}(n)=(1-\alpha)V_{\mathrm o}(n-1)+\alpha V_{\mathrm i}(n)
 \f]
 @param[in,out] ctx points to an instance of Low Pass Filter
 @param[in] x input value
 @return output value
*/
A_INTERN a_real a_lpf_iter(a_lpf *ctx, a_real x)
{
    ctx->output *= 1 - ctx->alpha;
    ctx->output += x * ctx->alpha;
    return ctx->output;
}

/*!
 @brief zeroing for Low Pass Filter
 @param[in,out] ctx points to an instance of Low Pass Filter
*/
A_INTERN void a_lpf_zero(a_lpf *ctx) { ctx->output = 0; }

/*! @} a_lpf */

#endif /* a/lpf.h */
