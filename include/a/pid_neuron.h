/*!
 @file pid_neuron.h
 @brief neuron proportional integral derivative controller
*/

#ifndef LIBA_PID_NEURON_H
#define LIBA_PID_NEURON_H

#include "pid.h"

/*!
 @ingroup A
 @addtogroup A_PID_NEURON neuron proportional integral derivative controller
 @{
*/

/*!
 @brief instance structure for neuron PID controller
*/
typedef struct a_pid_neuron_s
{
    a_pid_s pid; //!< instance structure for PID controller
    a_float_u ec; //!< error change
    a_float_u wp; //!< proportional constant weight
    a_float_u wi; //!< integral constant weight
    a_float_u wd; //!< derivative constant weight
    a_float_t ko; //!< output ratio
} a_pid_neuron_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief initialize function for neuron PID controller
 @param[in,out] ctx points to an instance of neuron PID controller
 @param[in] num number of controller channel
*/
A_EXTERN a_pid_neuron_s *a_pid_neuron_init(a_pid_neuron_s *ctx, unsigned int num);

/*!
 @brief set buffer for multichannel neuron PID controller
 @param[in,out] ctx points to an instance of neuron PID controller
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
A_EXTERN a_pid_neuron_s *a_pid_neuron_chan(a_pid_neuron_s *ctx, unsigned int num,
                                           a_float_t *out, a_float_t *fdb, a_float_t *tmp, a_float_t *err,
                                           a_float_t *ec, a_float_t *wp, a_float_t *wi, a_float_t *wd);

/*!
 @brief set proportional integral derivative constant for neuron PID controller
 @param[in,out] ctx points to an instance of neuron PID controller
 @param[in] kp proportional learning constant
 @param[in] ki integral learning constant
 @param[in] kd derivative learning constant
*/
A_EXTERN a_pid_neuron_s *a_pid_neuron_kpid(a_pid_neuron_s *ctx, a_float_t kp, a_float_t ki, a_float_t kd);

/*!
 @brief calculate function for neuron PID controller
 @param[in,out] ctx points to an instance of neuron PID controller
 @param[in] set setpoint
 @param[in] fdb feedback
 @return output value
*/
A_EXTERN a_float_t a_pid_neuron_outf(a_pid_neuron_s *ctx, a_float_t set, a_float_t fdb);

/*!
 @brief calculate function for multichannel neuron PID controller
 @param[in,out] ctx points to an instance of neuron PID controller
 @param[in] set points to setpoint
 @param[in] fdb points to feedback
 @return points to output
*/
A_EXTERN a_float_t const *a_pid_neuron_outp(a_pid_neuron_s *ctx, a_float_t const *set, a_float_t const *fdb);

/*!
 @brief zero clear function for neuron PID controller
 @param[in,out] ctx points to an instance of neuron PID controller
*/
A_EXTERN a_pid_neuron_s *a_pid_neuron_zero(a_pid_neuron_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_PID_NEURON */

#endif /* pid_neuron.h */
