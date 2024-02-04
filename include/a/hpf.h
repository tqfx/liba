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

#include "a.h"
#include "math.h"

/*!
 @ingroup A
 @addtogroup A_HPF High Pass Filter
 @{
*/

/*!
 @brief instance structure for High Pass Filter
*/
typedef struct a_hpf
{
    a_float alpha; //!< filter coefficient [0,1]
    a_float output; //!< filter output
    a_float input; //!< filter input
#if defined(__cplusplus)
    A_INLINE void gen(a_float fc, a_float ts)
    {
        alpha = 1 / (A_FLOAT_TAU * fc * ts + 1);
    }
    A_INLINE a_float operator()(a_float x)
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
// clang-format off
#if defined(__cplusplus)
#define A_HPF_INIT(alpha) {a_float_c(alpha), 0, 0}
#define A_HPF_INIT2(fc, ts) {A_HPF_GEN(fc, ts), 0, 0}
#else /* !__cplusplus */
#define A_HPF_INIT(alpha) (a_hpf){a_float_c(alpha), 0, 0}
#define A_HPF_INIT2(fc, ts) (a_hpf){A_HPF_GEN(fc, ts), 0, 0}
#endif /* __cplusplus */
// clang-format on
#define A_HPF_GEN(fc, ts) (1 / (A_FLOAT_TAU * a_float_c(fc) * a_float_c(ts) + 1))

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
A_INTERN a_float a_hpf_gen(a_float fc, a_float ts)
{
    return 1 / (A_FLOAT_TAU * fc * ts + 1);
}

/*!
 @brief initialize for High Pass Filter
 @param[in,out] ctx points to an instance of High Pass Filter
 @param[in] alpha filter coefficient [0,1]
*/
A_INTERN void a_hpf_init(a_hpf *ctx, a_float alpha)
{
    ctx->alpha = alpha;
    ctx->output = 0;
    ctx->input = 0;
}

/*!
 @brief calculate for High Pass Filter
 \f[
  V_{\mathrm o}(n)=\alpha[V_{\mathrm o}(n-1)+V_{\mathrm i}(n)-V_{\mathrm i}(n-1)]
 \f]
 @param[in,out] ctx points to an instance of High Pass Filter
 @param[in] x input value
 @return output value
*/
A_INTERN a_float a_hpf_iter(a_hpf *ctx, a_float x)
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

/*! @} A_HPF */

#endif /* a/hpf.h */
