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

#include "a.h"
#include "math.h"

/*!
 @ingroup A
 @addtogroup A_LPF Low Pass Filter
 @{
*/

// clang-format off
#define A_LPF_INIT(alpha) {a_float_c(alpha), 0}
// clang-format on

/*!
 @brief instance structure for Low Pass Filter
*/
typedef struct a_lpf
{
    a_float alpha; //!< filter coefficient [0,1]
    a_float output; //!< filter output
} a_lpf;

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
A_INTERN a_float a_lpf_gen(a_float const fc, a_float const ts)
{
    return ts / (A_FLOAT_1_PI / 2 / fc + ts);
}
#define A_LPF_GEN(fc, ts) (a_float_c(ts) / (A_FLOAT_1_PI / 2 / a_float_c(fc) + a_float_c(ts)))

/*!
 @brief initialize for Low Pass Filter
 @param[in,out] ctx points to an instance of Low Pass Filter
 @param[in] alpha filter coefficient [0,1]
*/
A_INTERN void a_lpf_init(a_lpf *const ctx, a_float const alpha)
{
    ctx->alpha = alpha;
    ctx->output = 0;
}

/*!
 @brief calculate for Low Pass Filter
 \f[
  V_{\mathrm o}(n)=(1-\alpha)V_{\mathrm o}(n-1)+\alpha V_{\mathrm i}(n)
 \f]
 @param[in,out] ctx points to an instance of Low Pass Filter
 @param[in] x input value
 @return output value
*/
A_INTERN a_float a_lpf_iter(a_lpf *const ctx, a_float const x)
{
    ctx->output *= 1 - ctx->alpha;
    ctx->output += x * ctx->alpha;
    return ctx->output;
}

/*!
 @brief zeroing for Low Pass Filter
 @param[in,out] ctx points to an instance of Low Pass Filter
*/
A_INTERN void a_lpf_zero(a_lpf *const ctx) { ctx->output = 0; }

/*! @} A_LPF */

#endif /* a/lpf.h */
