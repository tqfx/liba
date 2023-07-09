/*!
 @file pid_expert.h
 @brief expert proportional integral derivative controller
*/

#ifndef LIBA_PID_EXPERT_H
#define LIBA_PID_EXPERT_H

#include "pid.h"

/*!
 @ingroup A
 @addtogroup A_PID_EXPERT expert proportional integral derivative controller
 @{
*/

/*!
 @brief instance structure for expert PID controller
*/
typedef struct a_pid_expert_s
{
    a_pid_s pid; //!< instance structure for PID controller
    a_float_u ec; //!< error change
    a_float_t epsilon; //!< precision
    a_float_t max1; //!< first error bound
    a_float_t gain; //!< gain coefficient
    a_float_t max2; //!< second error bound
    a_float_t loss; //!< loss coefficient
} a_pid_expert_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
#if defined(LIBA_PID_EXPERT_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_PID_EXPERT_C */

/*!
 @brief set proportional integral derivative constant for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN a_pid_expert_s *a_pid_expert_kpid(a_pid_expert_s *ctx, a_float_t kp, a_float_t ki, a_float_t kd);

/*!
 @brief set buffer for multichannel expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] num number of controller output
 @param[in] out points to controller output
 @param[in] fdb points to cache feedback buffer
 @param[in] tmp points to cache variable buffer
 @param[in] err points to cache error buffer
 @param[in] ec points to error change buffer
*/
A_EXTERN a_pid_expert_s *a_pid_expert_chan(a_pid_expert_s *ctx, unsigned int num, a_float_t *out, a_float_t *fdb,
                                           a_float_t *tmp, a_float_t *err, a_float_t *ec);

/*!
 @brief initialize function for expert PID controller, default is incremental
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] dt sampling time unit(s)
 @param[in] min mininum output
 @param[in] max maxinum output
 @param[in] max1 first error bound
 @param[in] gain gain coefficient
 @param[in] max2 second error bound
 @param[in] loss loss coefficient
 @param[in] epsilon precision
*/
A_EXTERN a_pid_expert_s *a_pid_expert_init(a_pid_expert_s *ctx, a_float_t dt, a_float_t min, a_float_t max,
                                           a_float_t max1, a_float_t gain, a_float_t max2, a_float_t loss,
                                           a_float_t epsilon);

/*!
 @brief calculate function for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] set setpoint
 @param[in] fdb feedback
 @return output value
*/
A_EXTERN a_float_t a_pid_expert_outf(a_pid_expert_s *ctx, a_float_t set, a_float_t fdb);

/*!
 @brief calculate function for multichannel expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] set points to setpoint
 @param[in] fdb points to feedback
 @return points to output
*/
A_EXTERN a_float_t const *a_pid_expert_outp(a_pid_expert_s *ctx, a_float_t const *set, a_float_t const *fdb);

/*!
 @brief zero clear function for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
*/
A_EXTERN a_pid_expert_s *a_pid_expert_zero(a_pid_expert_s *ctx);

#if defined(LIBA_PID_EXPERT_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_PID_EXPERT_C */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_PID_EXPERT */

#endif /* pid_expert.h */
