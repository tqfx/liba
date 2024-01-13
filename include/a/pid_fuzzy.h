/*!
 @file pid_fuzzy.h
 @brief fuzzy proportional integral derivative controller
*/

#ifndef LIBA_PID_FUZZY_H
#define LIBA_PID_FUZZY_H

#include "pid.h"

/*!
 @ingroup A
 @addtogroup A_PID_FUZZY fuzzy proportional integral derivative controller
 @{
*/

/*!
 @brief enumeration for fuzzy PID controller operator
*/
enum
{
    A_PID_FUZZY_EQU, //!< sqrt(a,b)*sqrt(1-(1-a)*(1-b))
    A_PID_FUZZY_CAP, //!< min(a,b)
    A_PID_FUZZY_CAP_ALGEBRA, //!< a*b
    A_PID_FUZZY_CAP_BOUNDED, //!< max(a+b-1,0)
    A_PID_FUZZY_CUP, //!< max(a,b)
    A_PID_FUZZY_CUP_ALGEBRA, //!< a+b-a*b
    A_PID_FUZZY_CUP_BOUNDED //!< min(a+b,1)
};

/*!
 @brief instance structure for fuzzy PID controller
*/
typedef struct a_pid_fuzzy
{
    a_pid pid; //!< instance structure for PID controller

    a_float const *me; //!< points to e's membership function parameter table
    a_float const *mec; //!< points to ec's membership function parameter table
    a_float const *mkp; //!< points to Kp's rule base, which must be a square matrix
    a_float const *mki; //!< points to Ki's rule base, which must be a square matrix
    a_float const *mkd; //!< points to Kd's rule base, which must be a square matrix

    unsigned int *idx; //!< the memory cache for membership index, >= 2N
    a_float *val; //!< the memory cache for membership value and membership outer product of e and ec, >= (2+N)N
    a_float (*op)(a_float, a_float); //!< fuzzy relational operator

    a_float kp; //!< base proportional constant
    a_float ki; //!< base integral constant
    a_float kd; //!< base derivative constant

    unsigned int order; //!< number of order in the square matrix
    unsigned int joint; //!< maximum number triggered by the rule
} a_pid_fuzzy;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief get fuzzy relational operator for fuzzy PID controller
 @param[in] op enumeration for fuzzy PID controller operator
 @return fuzzy relational operator for fuzzy PID controller
*/
A_EXTERN a_float (*a_pid_fuzzy_op(unsigned int op))(a_float, a_float);

/*!
 @brief set fuzzy relational operator for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] op enumeration for fuzzy PID controller operator
*/
A_EXTERN void a_pid_fuzzy_set_op(a_pid_fuzzy *ctx, unsigned int op);

/*!
 @brief zeroing for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
A_EXTERN void a_pid_fuzzy_zero(a_pid_fuzzy *ctx);

/*!
 @brief initialize for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
A_EXTERN void a_pid_fuzzy_init(a_pid_fuzzy *ctx);

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
A_EXTERN void a_pid_fuzzy_rule(a_pid_fuzzy *ctx, unsigned int order, a_float const *me, a_float const *const mec,
                               a_float const *mkp, a_float const *mki, a_float const *mkd);

/*!
 @brief get joint buffer for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @return joint buffer for fuzzy PID controller
*/
A_EXTERN void *a_pid_fuzzy_joint(a_pid_fuzzy *ctx);

/*!
 @brief set joint buffer for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] ptr points to a buffer at least A_PID_FUZZY_JOINT(num)
 @param[in] num the maximum number triggered by the rule
*/
A_EXTERN void a_pid_fuzzy_set_joint(a_pid_fuzzy *ctx, void *ptr, a_size num);

/*!
 @brief compute size of joint buffer for fuzzy PID controller
 @param n the maximum number triggered by the rule
*/
#define A_PID_FUZZY_JOINT(n) (sizeof(unsigned int) * (n) * 2 + sizeof(a_float) * (n) * (2 + (n)))

/*!
 @brief set proportional integral derivative constant for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN void a_pid_fuzzy_kpid(a_pid_fuzzy *ctx, a_float kp, a_float ki, a_float kd);

/*!
 @brief calculate for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return setpoint value
*/
A_EXTERN a_float a_pid_fuzzy_run(a_pid_fuzzy *ctx, a_float set, a_float fdb);

/*!
 @brief calculate for positional fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return output value
*/
A_EXTERN a_float a_pid_fuzzy_pos(a_pid_fuzzy *ctx, a_float set, a_float fdb);

/*!
 @brief calculate for incremental fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return output value
*/
A_EXTERN a_float a_pid_fuzzy_inc(a_pid_fuzzy *ctx, a_float set, a_float fdb);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_PID_FUZZY */

#endif /* a/pid_fuzzy.h */
