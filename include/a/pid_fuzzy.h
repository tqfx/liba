/*!
 @file pid_fuzzy.h
 @brief fuzzy proportional integral derivative controller
*/

#ifndef LIBA_PID_FUZZY_H
#define LIBA_PID_FUZZY_H

#include "pid.h"
#include "fuzzy.h"

/*!
 @ingroup A
 @addtogroup A_PID_FUZZY fuzzy proportional integral derivative controller
 @{
*/

typedef struct a_pid_fuzzy a_pid_fuzzy;

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

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief initialize for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
#define a_pid_fuzzy_init(ctx) a_pid_fuzzy_zero(ctx)

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
 @brief set rule base for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] order number of order in the square matrix
 @param[in] me points to e's membership function parameter table
 @param[in] mec points to ec's membership function parameter table
 @param[in] mkp points to Kp's rule base table which must be a square matrix
 @param[in] mki points to Ki's rule base table which must be a square matrix
 @param[in] mkd points to Kd's rule base table which must be a square matrix
*/
A_EXTERN void a_pid_fuzzy_rule(a_pid_fuzzy *ctx, unsigned int order, a_float const *me, a_float const *mec,
                               a_float const *mkp, a_float const *mki, a_float const *mkd);

/*!
 @brief compute size of memory block for fuzzy PID controller
 @param[in] n the maximum number triggered by the rule
*/
#define A_PID_FUZZY_BLOCK(n) (sizeof(unsigned int) * (n) * 2 + sizeof(a_float) * (n) * (2 + (n)))

/*!
 @brief set memory block for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] ptr points to a buffer at least A_PID_FUZZY_BLOCK(num)
 @param[in] num the maximum number triggered by the rule
*/
A_EXTERN void a_pid_fuzzy_set_block(a_pid_fuzzy *ctx, void *ptr, a_size num);

/*!
 @brief get memory block for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @return memory block for fuzzy PID controller
*/
A_EXTERN void *a_pid_fuzzy_block(a_pid_fuzzy *ctx);

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

/*!
 @brief zeroing for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
A_EXTERN void a_pid_fuzzy_zero(a_pid_fuzzy *ctx);

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_pid_fuzzy pid_fuzzy;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for fuzzy PID controller
*/
struct a_pid_fuzzy
{
    a_pid pid; //!< instance structure for PID controller

    a_float const *me; //!< points to e's membership function parameter table
    a_float const *mec; //!< points to ec's membership function parameter table
    a_float const *mkp; //!< points to Kp's rule base, which must be a square matrix
    a_float const *mki; //!< points to Ki's rule base, which must be a square matrix
    a_float const *mkd; //!< points to Kd's rule base, which must be a square matrix

    unsigned int *idx; //!< the memory block for membership index, >= 2N
    a_float *val; //!< the memory block for membership value and membership outer product of e and ec, >= (2+N)N

    a_float (*op)(a_float, a_float); //!< fuzzy relational operator

    a_float kp; //!< base proportional constant
    a_float ki; //!< base integral constant
    a_float kd; //!< base derivative constant

    unsigned int order; //!< number of order in the square matrix
    unsigned int block; //!< maximum number triggered by the rule
#if defined(__cplusplus)
    A_INLINE void init() { a_pid_fuzzy_init(this); }
    A_INLINE void set_op(unsigned int _op)
    {
        a_pid_fuzzy_set_op(this, _op);
    }
    A_INLINE void set_block(void *ptr, a_size num)
    {
        a_pid_fuzzy_set_block(this, ptr, num);
    }
    A_INLINE void rule(unsigned int _order, a_float const *_me, a_float const *_mec,
                       a_float const *_mkp, a_float const *_mki, a_float const *_mkd)
    {
        a_pid_fuzzy_rule(this, _order, _me, _mec, _mkp, _mki, _mkd);
    }
    A_INLINE void kpid(a_float _kp, a_float _ki, a_float _kd)
    {
        a_pid_fuzzy_kpid(this, _kp, _ki, _kd);
    }
    A_INLINE a_float run(a_float set, a_float fdb)
    {
        return a_pid_fuzzy_run(this, set, fdb);
    }
    A_INLINE a_float pos(a_float set, a_float fdb)
    {
        return a_pid_fuzzy_pos(this, set, fdb);
    }
    A_INLINE a_float inc(a_float set, a_float fdb)
    {
        return a_pid_fuzzy_inc(this, set, fdb);
    }
    A_INLINE void zero() { a_pid_fuzzy_zero(this); }
#endif /* __cplusplus */
};

/*! @} A_PID_FUZZY */

#endif /* a/pid_fuzzy.h */
