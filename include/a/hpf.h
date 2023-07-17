/*!
 @file hpf.h
 @brief High Pass Filter
 @details
 high frequencies are passed, low frequencies are attenuated.
 \f[
  V_{out}(n)=\alpha(V_{out}(n-1)+V_{in}(n)-V_{in}(n-1))
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

// clang-format off
#define A_HPF_INIT(alpha) {a_float_c(, alpha), 0, 0}
// clang-format on

/*!
 @brief instance structure for High Pass Filter
*/
typedef struct a_hpf_s
{
    a_float_t alpha; //!< filter coefficient [0,1]
    a_float_t y; //!< filter output
    a_float_t x; //!< filter input
} a_hpf_s;

/*!
 @brief generation function for High Pass Filter
 \f{cases}{
  \alpha=\frac{RC}{RC+T_{s}},&\alpha\in[0,1]\\
  RC=\frac{1}{2\pi{f_c}}.
 \f}
 \f[
  \alpha=\frac{1}{2\pi{f_c}{T_s}+1}
 \f]
 @param[in] fc cut-off frequency unit(hz)
 @param[in] dt sampling time unit(s)
 @return filter coefficient [0,1]
*/
A_INTERN a_float_t a_hpf_gen(a_float_t const fc, a_float_t const dt)
{
    return 1 / (2 * A_FLOAT_PI * fc * dt + 1);
}
#define A_HPF_GEN(fc, dt) (1 / (2 * A_FLOAT_PI * a_float_c(, fc) * a_float_c(, dt) + 1))

/*!
 @brief initialize function for High Pass Filter
 @param[in,out] ctx points to an instance of High Pass Filter
 @param[in] alpha filter coefficient [0,1]
*/
A_INLINE void a_hpf_init(a_hpf_s *const ctx, a_float_t const alpha)
{
    ctx->alpha = alpha;
    ctx->y = 0;
    ctx->x = 0;
}

/*!
 @brief calculate function for High Pass Filter
 \f[
  V_{out}(n)=\alpha(V_{out}(n-1)+V_{in}(n)-V_{in}(n-1))
 \f]
 @param[in,out] ctx points to an instance of High Pass Filter
 @param[in] x input value
 @return output value
*/
A_INTERN a_float_t a_hpf_iter(a_hpf_s *const ctx, a_float_t const x)
{
    ctx->y = (ctx->y + x - ctx->x) * ctx->alpha;
    return (void)(ctx->x = x), ctx->y;
}

/*!
 @brief zero clear function for High Pass Filter
 @param[in,out] ctx points to an instance of High Pass Filter
*/
A_INTERN void a_hpf_zero(a_hpf_s *const ctx) { ctx->y = ctx->x = 0; }

/*! @} A_HPF */

#endif /* a/hpf.h */
