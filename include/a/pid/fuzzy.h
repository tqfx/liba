/*!
 @file fuzzy.h
 @brief fuzzy proportional integral derivative controller
*/

#ifndef LIBA_PID_FUZZY_H
#define LIBA_PID_FUZZY_H

#include "../pid.h"

/*!
 @ingroup A
 @addtogroup A_PID_FUZZY fuzzy proportional integral derivative controller
 @{
*/

/*!
 @brief instance enumeration for fuzzy PID controller operator
*/
typedef enum a_pid_fuzzy_e
{
    A_PID_FUZZY_EQU, //!< sqrt(a,b)*sqrt(1-(1-a)*(1-b))
    A_PID_FUZZY_CAP, //!< min(a,b)
    A_PID_FUZZY_CAP_ALGEBRA, //!< a*b
    A_PID_FUZZY_CAP_BOUNDED, //!< max(a+b-1,0)
    A_PID_FUZZY_CUP, //!< max(a,b)
    A_PID_FUZZY_CUP_ALGEBRA, //!< a+b-a*b
    A_PID_FUZZY_CUP_BOUNDED, //!< min(a+b,1)
} a_pid_fuzzy_e;

/*!
 @brief instance structure for fuzzy PID controller
*/
typedef struct a_pid_fuzzy_s
{
    a_pid_s pid; //!< instance structure for PID controller

    a_float_t const *me; //!< points to e's membership function parameter table
    a_float_t const *mec; //!< points to ec's membership function parameter table
    a_float_t const *mkp; //!< points to Kp's rule base, which must be a square matrix
    a_float_t const *mki; //!< points to Ki's rule base, which must be a square matrix
    a_float_t const *mkd; //!< points to Kd's rule base, which must be a square matrix

    unsigned int *idx; //!< the memory cache for membership index, >= 2N
    a_float_t *val; //!< the memory cache for membership value and membership outer product of e and ec, >= (2+N)N
    a_float_t (*op)(a_float_t, a_float_t); //!< fuzzy relational operator

    a_float_t kp; //!< base proportional constant
    a_float_t ki; //!< base integral constant
    a_float_t kd; //!< base derivative constant

    unsigned int order; //!< number of order in the square matrix
    unsigned int joint; //!< maximum number triggered by the rule
} a_pid_fuzzy_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief get fuzzy relational operator for fuzzy PID controller
 @param[in] op enumeration for fuzzy PID controller operator
 @return fuzzy relational operator for fuzzy PID controller
*/
A_EXTERN a_float_t (*a_pid_fuzzy_op(unsigned int op))(a_float_t, a_float_t);

/*!
 @brief set fuzzy relational operator for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] op enumeration for fuzzy PID controller operator
*/
A_EXTERN void a_pid_fuzzy_set_op(a_pid_fuzzy_s *ctx, unsigned int op);

/*!
 @brief initialize function for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] num number of controller channel
*/
A_EXTERN void a_pid_fuzzy_init(a_pid_fuzzy_s *ctx, unsigned int num);

/*!
 @brief set buffer for multichannel fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] num number of controller output
 @param[in] out points to controller output
 @param[in] fdb points to cache feedback buffer
 @param[in] tmp points to cache variable buffer
 @param[in] err points to cache error buffer
*/
A_EXTERN void a_pid_fuzzy_chan(a_pid_fuzzy_s *ctx, unsigned int num, a_float_t *out, a_float_t *fdb, a_float_t *tmp, a_float_t *err);

/*!
 @brief set rule base for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] order number of order in the square matrix
 @param[in] me points to e's membership function parameter table
 @param[in] mec points to ec's membership function parameter table
 @param[in] mkp points to Kp's rule base table which must be a square matrix
 @param[in] mki points to Ki's rule base table which must be a square matrix
 @param[in] mkd points to Kd's rule base table which must be a square matrix
*/
A_EXTERN void a_pid_fuzzy_rule(a_pid_fuzzy_s *ctx, unsigned int order, a_float_t const *me, a_float_t const *const mec,
                               a_float_t const *mkp, a_float_t const *mki, a_float_t const *mkd);

/*!
 @brief compute size of joint buffer for fuzzy PID controller
 @param n the maximum number triggered by the rule
*/
#define A_PID_FUZZY_JOINT(n) (sizeof(unsigned int) * (n) * 2 + sizeof(a_float_t) * (n) * (2 + (n)))

/*!
 @brief set joint buffer for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] ptr points to a buffer at least A_PID_FUZZY_JOINT(num)
 @param[in] num the maximum number triggered by the rule
*/
A_EXTERN void a_pid_fuzzy_joint(a_pid_fuzzy_s *ctx, void *ptr, a_size_t num);

/*!
 @brief set proportional integral derivative constant for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN void a_pid_fuzzy_kpid(a_pid_fuzzy_s *ctx, a_float_t kp, a_float_t ki, a_float_t kd);

/*!
 @brief calculate function for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] set setpoint
 @param[in] fdb feedback
 @return output value
  @retval set when fuzzy PID controller is off
*/
A_EXTERN a_float_t a_pid_fuzzy_outf(a_pid_fuzzy_s *ctx, a_float_t set, a_float_t fdb);

/*!
 @brief calculate function for multichannel fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] set points to setpoint
 @param[in] fdb points to feedback
 @return points to output
  @retval set when fuzzy PID controller is off
*/
A_EXTERN a_float_t const *a_pid_fuzzy_outp(a_pid_fuzzy_s *ctx, a_float_t const *set, a_float_t const *fdb);

/*!
 @brief calculate function for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] set setpoint
 @param[in] fdb feedback
 @return output value
  @retval set when PID controller is off
*/
A_EXTERN a_float_t const *a_pid_fuzzy_iter(a_pid_fuzzy_s *ctx, a_float_t const *set, a_float_t const *fdb);

/*!
 @brief zero clear function for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
A_EXTERN void a_pid_fuzzy_zero(a_pid_fuzzy_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_PID_FUZZY */

#endif /* a/pid/fuzzy.h */
