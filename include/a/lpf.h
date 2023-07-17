/*!
 @file lpf.h
 @brief Low Pass Filter
 @details
 low frequencies are passed, high frequencies are attenuated.
 \f[
  V_{out}(n)=(1-\alpha)V_{out}(n-1)+\alpha V_{in}
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
#define A_LPF_INIT(alpha) {a_float_c(, alpha), 0}
// clang-format on

/*!
 @brief instance structure for Low Pass Filter
*/
typedef struct a_lpf_s
{
    a_float_t alpha; //!< filter coefficient [0,1]
    a_float_t y; //!< filter output
} a_lpf_s;

/*!
 @brief generation function for Low Pass Filter
 \f{cases}{
  \alpha=\frac{T_{s}}{T_{s}+RC},&\alpha\in[0,1]\\
  RC=\frac{1}{2\pi{f_c}}.
 \f}
 \f[
  \alpha=\frac{T_s}{T_s+\frac{1}{2\pi{f_c}}}
 \f]
 @param[in] fc cut-off frequency unit(hz)
 @param[in] dt sampling time unit(s)
 @return filter coefficient [0,1]
*/
A_INTERN a_float_t a_lpf_gen(a_float_t const fc, a_float_t const dt)
{
    return dt / (dt + A_FLOAT_1_PI / 2 / fc);
}
#define A_LPF_GEN(fc, dt) (a_float_c(, dt) / (a_float_c(, dt) + A_FLOAT_1_PI / 2 / a_float_c(, fc)))

/*!
 @brief initialize function for Low Pass Filter
 @param[in,out] ctx points to an instance of Low Pass Filter
 @param[in] alpha filter coefficient [0,1]
*/
A_INLINE void a_lpf_init(a_lpf_s *const ctx, a_float_t const alpha)
{
    ctx->alpha = alpha;
    ctx->y = 0;
}

/*!
 @brief calculate function for Low Pass Filter
 \f[
  V_{out}(n)=(1-\alpha)V_{out}(n-1)+\alpha V_{in}
 \f]
 @param[in,out] ctx points to an instance of Low Pass Filter
 @param[in] x input value
 @return output value
*/
A_INTERN a_float_t a_lpf_iter(a_lpf_s *const ctx, a_float_t const x)
{
    ctx->y *= 1 - ctx->alpha;
    ctx->y += x * ctx->alpha;
    return ctx->y;
}

/*!
 @brief zero clear function for Low Pass Filter
 @param[in,out] ctx points to an instance of Low Pass Filter
*/
A_INTERN void a_lpf_zero(a_lpf_s *const ctx) { ctx->y = 0; }

/*! @} A_LPF */

#endif /* a/lpf.h */
