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
  u(k) = K_p\left[e(k)+\frac{T}{T_i}\sum^k_{i=0}e(i)+\frac{T_d}{T}[e(k)-e(k-1)]\right]
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

/*!
 @brief enumeration for PID controller
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
    a_float_t kp; //!< proportional constant
    a_float_t ki; //!< integral constant
    a_float_t kd; //!< derivative constant
    a_float_t summax; //!< maximum integral output
    a_float_t summin; //!< minimum integral output
    a_float_t sum; //!< controller integral output
    a_float_t outmax; //!< maximum final output
    a_float_t outmin; //!< minimum final output
    a_float_t out; //!< controller output
    a_float_t fdb; //!< cache feedback
    a_float_t var; //!< cache variable
    a_float_t err; //!< cache error
} a_pid_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief zeroing for PID controller
 @param[in,out] ctx points to an instance of PID controller
*/
A_EXTERN void a_pid_zero(a_pid_s *ctx);

/*!
 @brief initialize for PID controller
 @param[in,out] ctx points to an instance of PID controller
*/
A_EXTERN void a_pid_init(a_pid_s *ctx);

/*!
 @brief set proportional integral derivative constant for PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN void a_pid_kpid(a_pid_s *ctx, a_float_t kp, a_float_t ki, a_float_t kd);

/*!
 @brief calculate for PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return setpoint value
*/
A_EXTERN a_float_t a_pid_off(a_pid_s *ctx, a_float_t set, a_float_t fdb);

/*!
 @brief calculate for positional PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return output value
*/
A_EXTERN a_float_t a_pid_pos(a_pid_s *ctx, a_float_t set, a_float_t fdb);

/*!
 @brief calculate for incremental PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return output value
*/
A_EXTERN a_float_t a_pid_inc(a_pid_s *ctx, a_float_t set, a_float_t fdb);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_PID */

#endif /* a/pid.h */
