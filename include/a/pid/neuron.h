/*!
 @file neuron.h
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

#ifndef LIBA_PID_NEURON_H
#define LIBA_PID_NEURON_H

#include "../pid.h"

/*!
 @ingroup A
 @addtogroup A_PID_NEURON single neuron proportional integral derivative controller
 @{
*/

/*!
 @brief instance structure for single neuron PID controller
*/
typedef struct a_pid_neuron_s
{
    a_pid_s pid; //!< instance structure for PID controller
    a_float_u ec; //!< error change
    a_float_u wp; //!< proportional weight
    a_float_u wi; //!< integral weight
    a_float_u wd; //!< derivative weight
    a_float_t k; //!< proportional output coefficient
} a_pid_neuron_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief initialize function for single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
 @param[in] num number of controller channel
*/
A_EXTERN void a_pid_neuron_init(a_pid_neuron_s *ctx, unsigned int num);

/*!
 @brief set buffer for multichannel single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
 @param[in] num number of controller output
 @param[in] out points to controller output
 @param[in] fdb points to cache feedback buffer
 @param[in] tmp points to cache variable buffer
 @param[in] err points to cache error buffer
 @param[in] ec points to error change buffer
 @param[in] wp points to kp's weight buffer
 @param[in] wi points to ki's weight buffer
 @param[in] wd points to kd's weight buffer
*/
A_EXTERN void a_pid_neuron_chan(a_pid_neuron_s *ctx, unsigned int num,
                                a_float_t *out, a_float_t *fdb, a_float_t *tmp, a_float_t *err,
                                a_float_t *ec, a_float_t *wp, a_float_t *wi, a_float_t *wd);

/*!
 @brief set proportional integral derivative constant for single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
 @param[in] k proportional output coefficient
 @param[in] kp proportional learning constant
 @param[in] ki integral learning constant
 @param[in] kd derivative learning constant
*/
A_EXTERN void a_pid_neuron_kpid(a_pid_neuron_s *ctx, a_float_t k, a_float_t kp, a_float_t ki, a_float_t kd);

/*!
 @brief set proportional integral derivative weight for single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
 @param[in] wp proportional weight
 @param[in] wi integral weight
 @param[in] wd derivative lweight
*/
A_EXTERN void a_pid_neuron_wpid(a_pid_neuron_s *ctx, a_float_t wp, a_float_t wi, a_float_t wd);

/*!
 @brief calculate function for single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
 @param[in] set setpoint
 @param[in] fdb feedback
 @return output value
*/
A_EXTERN a_float_t a_pid_neuron_outf(a_pid_neuron_s *ctx, a_float_t set, a_float_t fdb);

/*!
 @brief calculate function for multichannel single neuron PID controller
 @param[in] ctx points to an instance of single neuron PID controller
 @param[in] set points to setpoint
 @param[in] fdb points to feedback
 @return points to output
*/
A_EXTERN a_float_t const *a_pid_neuron_outp(a_pid_neuron_s const *ctx, a_float_t const *set, a_float_t const *fdb);

/*!
 @brief calculate function for single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
 @param[in] set setpoint
 @param[in] fdb feedback
 @return output value
  @retval set when PID controller is off
*/
A_EXTERN a_float_t const *a_pid_neuron_iter(a_pid_neuron_s *ctx, a_float_t const *set, a_float_t const *fdb);

/*!
 @brief zero clear function for single neuron PID controller
 @param[in,out] ctx points to an instance of single neuron PID controller
*/
A_EXTERN void a_pid_neuron_zero(a_pid_neuron_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_PID_NEURON */

#endif /* pid/neuron.h */
