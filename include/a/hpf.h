/*!
 @file hpf.h
 @brief High Pass Filter
 @details
 high frequencies are passed, low frequencies are attenuated.
 \f[
  RC\frac{\text{d}(V_{\mathrm i}-V_{\mathrm o})}{\text{dt}}=V_{\mathrm o}
 \f]
 \f[
  RC\frac{[V_{\mathrm i}(n)-V_{\mathrm i}(n-1)]-[V_{\mathrm o}(n)-V_{\mathrm o}(n-1)]}{T_s}=V_{\mathrm o}(n)
 \f]
 \f[
  V_{\mathrm o}(n)=\frac{RC}{RC+T_s}[V_{\mathrm o}(n-1)+V_{\mathrm i}(n)-V_{\mathrm i}(n-1)]
 \f]
 \f[
  \alpha=\frac{RC}{RC+T_s}=\frac{1}{2\pi f_c T_s + 1}
 \f]
 \f[
  V_{\mathrm o}(n)=\alpha[V_{\mathrm o}(n-1)+V_{\mathrm i}(n)-V_{\mathrm i}(n-1)]
 \f]
 https://en.wikipedia.org/wiki/High-pass_filter
*/

#ifndef LIBA_HPF_H
#define LIBA_HPF_H

#include "math.h"

/*!
 @ingroup liba
 @addtogroup a_hpf High Pass Filter
 @{
*/

/*!
 @brief instance structure for High Pass Filter
*/
typedef struct a_hpf
{
    a_real alpha; /*!< filter coefficient [0,1] */
    a_real output; /*!< filter output */
    a_real input; /*!< filter input */
#if defined(__cplusplus)
    A_INLINE void gen(a_real fc, a_real ts)
    {
        alpha = 1 / (A_REAL_TAU * fc * ts + 1);
    }
    A_INLINE a_real operator()(a_real x)
    {
        output = alpha * (output + x - input);
        return (void)(input = x), output;
    }
    A_INLINE void zero()
    {
        output = 0;
        input = 0;
    }
#endif /* __cplusplus */
} a_hpf;
#if defined(__cplusplus)
namespace a
{
typedef struct a_hpf hpf;
} /* namespace a */
#endif /* __cplusplus */
/* clang-format off */
#define A_HPF_1(alpha) {a_real_c(alpha), 0, 0}
#define A_HPF_2(fc, ts) {A_HPF_GEN(fc, ts), 0, 0}
/* clang-format on */
#define A_HPF_GEN(fc, ts) (1 / (A_REAL_TAU * a_real_c(fc) * a_real_c(ts) + 1))

/*!
 @brief generate for High Pass Filter
 \f{cases}{
  \alpha=\frac{RC}{RC+T_s},&\alpha\in[0,1]\\
  RC=\frac{1}{2\pi f_c}.
 \f}
 \f[
  \alpha=\frac{1}{2\pi f_c T_s+1}
 \f]
 @param[in] fc cut-off frequency unit(hz)
 @param[in] ts sampling time unit(s)
 @return filter coefficient [0,1]
*/
A_INTERN a_real a_hpf_gen(a_real fc, a_real ts)
{
    return 1 / (A_REAL_TAU * fc * ts + 1);
}

/*!
 @brief initialize for High Pass Filter
 @param[in,out] ctx points to an instance of High Pass Filter
 @param[in] alpha filter coefficient [0,1]
*/
A_INTERN void a_hpf_init(a_hpf *ctx, a_real alpha)
{
    ctx->alpha = alpha;
    ctx->output = 0;
    ctx->input = 0;
}

/*!
 @brief compute for High Pass Filter
 \f[
  V_{\mathrm o}(n)=\alpha[V_{\mathrm o}(n-1)+V_{\mathrm i}(n)-V_{\mathrm i}(n-1)]
 \f]
 @param[in,out] ctx points to an instance of High Pass Filter
 @param[in] x input value
 @return output value
*/
A_INTERN a_real a_hpf_iter(a_hpf *ctx, a_real x)
{
    ctx->output = ctx->alpha * (ctx->output + x - ctx->input);
    return (void)(ctx->input = x), ctx->output;
}

/*!
 @brief zeroing for High Pass Filter
 @param[in,out] ctx points to an instance of High Pass Filter
*/
A_INTERN void a_hpf_zero(a_hpf *ctx)
{
    ctx->output = 0;
    ctx->input = 0;
}

/*! @} a_hpf */

#endif /* a/hpf.h */
