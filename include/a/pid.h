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

typedef struct a_pid a_pid;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief initialize for PID controller
 @param[in,out] ctx points to an instance of PID controller
*/
#define a_pid_init(ctx) a_pid_zero(ctx)

/*!
 @brief set proportional integral derivative constant for PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN void a_pid_kpid(a_pid *ctx, a_float kp, a_float ki, a_float kd);

/*!
 @brief calculate for PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return setpoint value
*/
A_EXTERN a_float a_pid_run(a_pid *ctx, a_float set, a_float fdb);

/*!
 @brief calculate for positional PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return output value
*/
A_EXTERN a_float a_pid_pos(a_pid *ctx, a_float set, a_float fdb);

/*!
 @brief calculate for incremental PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return output value
*/
A_EXTERN a_float a_pid_inc(a_pid *ctx, a_float set, a_float fdb);

/*!
 @brief zeroing for PID controller
 @param[in,out] ctx points to an instance of PID controller
*/
A_EXTERN void a_pid_zero(a_pid *ctx);

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_pid pid;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for PID controller
*/
struct a_pid
{
    a_float kp; //!< proportional constant
    a_float ki; //!< integral constant
    a_float kd; //!< derivative constant
    a_float summax; //!< maximum integral output
    a_float summin; //!< minimum integral output
    a_float sum; //!< controller integral output
    a_float outmax; //!< maximum final output
    a_float outmin; //!< minimum final output
    a_float out; //!< controller final output
    a_float var; //!< cache variable
    a_float fdb; //!< cache feedback
    a_float err; //!< cache error
#if defined(__cplusplus)
    A_INLINE void init() { a_pid_init(this); }
    A_INLINE void kpid(a_float _kp, a_float _ki, a_float _kd)
    {
        a_pid_kpid(this, _kp, _ki, _kd);
    }
    A_INLINE a_float run(a_float set, a_float _fdb)
    {
        return a_pid_run(this, set, _fdb);
    }
    A_INLINE a_float pos(a_float set, a_float _fdb)
    {
        return a_pid_pos(this, set, _fdb);
    }
    A_INLINE a_float inc(a_float set, a_float _fdb)
    {
        return a_pid_inc(this, set, _fdb);
    }
    A_INLINE void zero() { a_pid_zero(this); }
#endif /* __cplusplus */
};

/*! @} A_PID */

#endif /* a/pid.h */
