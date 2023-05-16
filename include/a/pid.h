/*!
 @file pid.h
 @brief proportional integral derivative controller
 @details
 A proportional integral derivative controller (PID controller or three-term controller) is
 a control loop mechanism employing feedback that is widely used in industrial control systems
 and a variety of other applications requiring continuously modulated control.
 \f[
  u(t) = K_p\left[e(t)+\frac{1}{T_i}\int{e(t)}\text{dt}+T_d\frac{\text{d}e(t)}{\text{d}t}\right]
 \f]
 \f[
  u(t) = K_p\left[e(t)+\frac{T}{T_i}\sum^k_{i=0}e(i)+\frac{T_d}{T}[e(k)-e(k-1)]\right]
 \f]
 - positional PID controller
 \f{aligned}{
  u(k) &= K_p e(k) + q\sum^k_{i=0} K_i e(i) + K_d [e(k)-e(k-1)] \\
       &= (K_p+K_d) e(k) + q\sum^k_{i=0}K_i e(i) + (-K_d) e(k-1) \\
       &\begin{cases}q=0&|\sum\limits^{k-1}_{i=0}K_ie(i)|>E \bigvee
       [\sum\limits^{k-1}_{i=0}K_ie(i)]K_ke(k)>0 \\ q=1\end{cases}
 \f}
 - incremental PID controller
 \f{aligned}{
  \Delta u(k) &= K_p [e(k)-e(k-1)] + K_i e(k) + K_d [e(k)+e(k-2)-2e(k-1)] \\
              &= (K_p+K_i+K_d) e(k) + (-K_p-2K_i) e(k-1) + K_d e(k-2)
 \f}
 https://en.wikipedia.org/wiki/PID_controller
*/

#ifndef LIBA_PID_H
#define LIBA_PID_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_PID proportional integral derivative controller
 @{
*/

#define A_PID_NUM_BITS 8 // 00000000 11111111
#define A_PID_NUM_MASK ((1U << A_PID_NUM_BITS) - 1U)
#define A_PID_REG_BITS 8 // 00000000 11111111
#define A_PID_REG_MASK ((1U << A_PID_REG_BITS) - 1U)
#define A_PID_MODE_BITS 2 // 00000000 00000011
#define A_PID_MODE_MASK ((1U << A_PID_MODE_BITS) - 1U)

/*!
 @brief instance enumeration for PID controller mode
*/
typedef enum a_pid_e
{
    A_PID_OFF, //!< turn off PID controller
    A_PID_POS, //!< positional PID controller
    A_PID_INC //!< incremental PID controller
} a_pid_e;

/*!
 @brief instance structure for PID controller
*/
typedef struct a_pid_s
{
    a_real_t dt; //!< sampling time unit(s)
    a_real_t kp; //!< proportional constant
    a_real_t ki; //!< integral constant
    a_real_t kd; //!< derivative constant
    a_real_u out; //!< controller output
    a_real_u sum; //!< (integral) output item sum
    a_real_u fdb; //!< cache feedback
    a_real_u ec; //!< error change
    a_real_u e; //!< error input
    a_real_t outmin; //!< minimum final output
    a_real_t outmax; //!< maximum final output
    a_real_t summax; //!< maximum integral output
    a_uint_t num; //!< number register
    a_uint_t reg; //!< status register
} a_pid_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
#if defined(LIBA_PID_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_PID_C */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_real_t a_pid_dt(a_pid_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_real_t a_pid_dt(a_pid_s const *const ctx)
{
    return ctx->dt;
}
#endif /* A_HAVE_INLINE */

A_EXTERN a_void_t a_pid_set_dt(a_pid_s *ctx, a_real_t dt);

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_real_t a_pid_kp(a_pid_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_real_t a_pid_kp(a_pid_s const *const ctx)
{
    return ctx->kp;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_void_t a_pid_set_kp(a_pid_s *ctx, a_real_t kp);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_void_t a_pid_set_kp(a_pid_s *const ctx, a_real_t const kp)
{
    ctx->kp = kp;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_real_t a_pid_ki(a_pid_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_real_t a_pid_ki(a_pid_s const *const ctx)
{
    return ctx->ki / ctx->dt;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_void_t a_pid_set_ki(a_pid_s *ctx, a_real_t ki);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_void_t a_pid_set_ki(a_pid_s *const ctx, a_real_t const ki)
{
    ctx->ki = ki * ctx->dt;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_real_t a_pid_kd(a_pid_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_real_t a_pid_kd(a_pid_s const *const ctx)
{
    return ctx->kd * ctx->dt;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_void_t a_pid_set_kd(a_pid_s *ctx, a_real_t kd);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_void_t a_pid_set_kd(a_pid_s *const ctx, a_real_t const kd)
{
    ctx->kd = kd / ctx->dt;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_uint_t a_pid_num(a_pid_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_uint_t a_pid_num(a_pid_s const *const ctx)
{
    return ctx->num & A_PID_NUM_MASK;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_void_t a_pid_set_num(a_pid_s *ctx, a_uint_t num);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_void_t a_pid_set_num(a_pid_s *const ctx, a_uint_t const num)
{
    ctx->num &= ~A_PID_NUM_MASK;
    ctx->num |= num & A_PID_NUM_MASK;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_uint_t a_pid_reg(a_pid_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_uint_t a_pid_reg(a_pid_s const *const ctx)
{
    return ctx->reg & A_PID_REG_MASK;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_void_t a_pid_set_reg(a_pid_s *ctx, a_uint_t reg);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_void_t a_pid_set_reg(a_pid_s *const ctx, a_uint_t const reg)
{
    ctx->reg &= ~A_PID_REG_MASK;
    ctx->reg |= reg & A_PID_REG_MASK;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_uint_t a_pid_mode(a_pid_s const *mode);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_uint_t a_pid_mode(a_pid_s const *const ctx)
{
    return ctx->reg & A_PID_MODE_MASK;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_C)
A_EXTERN a_void_t a_pid_set_mode(a_pid_s *ctx, a_uint_t mode);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_C)
A_INTERN a_void_t a_pid_set_mode(a_pid_s *const ctx, a_uint_t const mode)
{
    ctx->reg &= ~A_PID_MODE_MASK;
    ctx->reg |= mode & A_PID_MODE_MASK;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief turn off PID controller
 @param[in,out] ctx points to an instance of PID controller
*/
A_EXTERN a_pid_s *a_pid_off(a_pid_s *ctx);

/*!
 @brief incremental PID controller
 @param[in,out] ctx points to an instance of PID controller
*/
A_EXTERN a_pid_s *a_pid_inc(a_pid_s *ctx);

/*!
 @brief positional PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] max maximum intergral output
*/
A_EXTERN a_pid_s *a_pid_pos(a_pid_s *ctx, a_real_t max);

/*!
 @brief set proportional integral derivative constant for PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN a_pid_s *a_pid_kpid(a_pid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd);

/*!
 @brief set buffer for multichannel PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] num number of controllers output
 @param[in] out points to controllers output
 @param[in] fdb points to cache feedback buffer
 @param[in] sum points to (integral) output buffer
 @param[in] ec points to error change buffer
 @param[in] e points to error input buffer
*/
A_EXTERN a_pid_s *a_pid_chan(a_pid_s *ctx, a_uint_t num, a_real_t *out, a_real_t *fdb, a_real_t *sum, a_real_t *ec, a_real_t *e);

/*!
 @brief initialize function for PID controller, default is turn off
 @param[in,out] ctx points to an instance of PID controller
 @param[in] dt sampling time unit(s)
 @param[in] min minimum output
 @param[in] max maximum output
*/
A_EXTERN a_pid_s *a_pid_init(a_pid_s *ctx, a_real_t dt, a_real_t min, a_real_t max);

/*!
 @brief calculate function for PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] set setpoint
 @param[in] fdb feedback
 @return output value
  @retval set when PID controller is off
*/
A_EXTERN a_real_t a_pid_outf(a_pid_s *ctx, a_real_t set, a_real_t fdb);

/*!
 @brief calculate function for multichannel PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] set points to setpoint
 @param[in] fdb points to feedback
 @return points to output
  @retval set when PID controller is off
*/
A_EXTERN a_real_t const *a_pid_outp(a_pid_s *ctx, a_real_t const *set, a_real_t const *fdb);

/*!
 @brief terminate function for PID controller
 @param[in,out] ctx points to an instance of PID controller
*/
A_EXTERN a_pid_s *a_pid_exit(a_pid_s *ctx);

/*!
 @brief zero function for PID controller
 @param[in,out] ctx points to an instance of PID controller
*/
A_EXTERN a_pid_s *a_pid_zero(a_pid_s *ctx);

#if defined(LIBA_PID_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_PID_C */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_PID */

#endif /* pid.h */
