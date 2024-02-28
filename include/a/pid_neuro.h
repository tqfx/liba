/*!
 @file pid_neuro.h
 @brief single neuron proportional integral derivative controller
 @details
 \f{cases}{
  x_i=e(k)\\
  x_p=e(k)-e(k-1)\\
  x_d=e(k)-2e(k-1)+e(k-2)
 \f}
 \f{cases}{
  \omega_{p}(k)=\omega_{p}(k-1)+\eta_{p}e(k)u(k)x_{p}(k)\\
  \omega_{i}(k)=\omega_{i}(k-1)+\eta_{i}e(k)u(k)x_{i}(k)\\
  \omega_{d}(k)=\omega_{d}(k-1)+\eta_{d}e(k)u(k)x_{d}(k)
 \f}
 \f[
  u(k)=u(k-1)+K\frac{w_{p}(k)x_{p}(k)+w_{i}(k)x_{i}(k)+w_{d}(k)x_{d}(k)}
                    {|\omega_{p}(k)|+|\omega_{i}(k)|+|\omega_{d}(k)|}
 \f]
*/

#ifndef LIBA_PID_NEURO_H
#define LIBA_PID_NEURO_H

#include "pid.h"

/*!
 @ingroup A
 @addtogroup A_PID_NEURO single neuron proportional integral derivative controller
 @{
*/

typedef struct a_pid_neuro a_pid_neuro;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief initialize for single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
*/
#define a_pid_neuro_init(ctx) a_pid_neuro_zero(ctx)

/*!
 @brief set proportional integral derivative constant for single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
 @param[in] k proportional output coefficient
 @param[in] kp proportional learning constant
 @param[in] ki integral learning constant
 @param[in] kd derivative learning constant
*/
A_EXTERN void a_pid_neuro_kpid(a_pid_neuro *ctx, a_float k, a_float kp, a_float ki, a_float kd);

/*!
 @brief set proportional integral derivative weight for single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
 @param[in] wp proportional weight
 @param[in] wi integral weight
 @param[in] wd derivative lweight
*/
A_EXTERN void a_pid_neuro_wpid(a_pid_neuro *ctx, a_float wp, a_float wi, a_float wd);

/*!
 @brief calculate for single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return setpoint value
*/
A_EXTERN a_float a_pid_neuro_run(a_pid_neuro *ctx, a_float set, a_float fdb);

/*!
 @brief calculate for incremental single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return output value
*/
A_EXTERN a_float a_pid_neuro_inc(a_pid_neuro *ctx, a_float set, a_float fdb);

/*!
 @brief zeroing for single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
*/
A_EXTERN void a_pid_neuro_zero(a_pid_neuro *ctx);

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_pid_neuro pid_neuro;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for single neuron PID controller
*/
struct a_pid_neuro
{
    a_pid pid; //!< instance structure for PID controller
    a_float k; //!< proportional output coefficient
    a_float wp; //!< proportional weight
    a_float wi; //!< integral weight
    a_float wd; //!< derivative weight
    a_float ec; //!< error change
#if defined(__cplusplus)
    A_INLINE void init() { a_pid_neuro_init(this); }
    A_INLINE void kpid(a_float _k, a_float kp, a_float ki, a_float kd)
    {
        a_pid_neuro_kpid(this, _k, kp, ki, kd);
    }
    A_INLINE void wpid(a_float _wp, a_float _wi, a_float _wd)
    {
        a_pid_neuro_wpid(this, _wp, _wi, _wd);
    }
    A_INLINE a_float run(a_float set, a_float fdb)
    {
        return a_pid_neuro_run(this, set, fdb);
    }
    A_INLINE a_float inc(a_float set, a_float fdb)
    {
        return a_pid_neuro_inc(this, set, fdb);
    }
    A_INLINE void zero() { a_pid_neuro_zero(this); }
#endif /* __cplusplus */
};

/*! @} A_PID_NEURO */

#endif /* a/pid_neuro.h */
