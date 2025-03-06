/*!
 @file pid_fuzzy.h
 @brief fuzzy proportional integral derivative controller
*/

#ifndef LIBA_PID_FUZZY_H
#define LIBA_PID_FUZZY_H

#include "pid.h"
#include "fuzzy.h"

/*!
 @ingroup liba
 @addtogroup a_pid_fuzzy fuzzy proportional integral derivative controller
 @{
*/

typedef struct a_pid_fuzzy a_pid_fuzzy;

/*!
 @brief enumeration for fuzzy PID controller operator
*/
enum
{
    A_PID_FUZZY_EQU, /*!< sqrt(a,b)*sqrt(1-(1-a)*(1-b)) */
    A_PID_FUZZY_CAP, /*!< min(a,b) */
    A_PID_FUZZY_CAP_ALGEBRA, /*!< a*b */
    A_PID_FUZZY_CAP_BOUNDED, /*!< max(a+b-1,0) */
    A_PID_FUZZY_CUP, /*!< max(a,b) */
    A_PID_FUZZY_CUP_ALGEBRA, /*!< a+b-a*b */
    A_PID_FUZZY_CUP_BOUNDED /*!< min(a+b,1) */
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
 @param[in] opr enumeration for fuzzy PID controller operator
 @return fuzzy relational operator for fuzzy PID controller
*/
A_EXTERN a_real (*a_pid_fuzzy_opr(unsigned int opr))(a_real, a_real);

/*!
 @brief set fuzzy relational operator for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] opr enumeration for fuzzy PID controller operator
*/
A_EXTERN void a_pid_fuzzy_set_opr(a_pid_fuzzy *ctx, unsigned int opr);

/*!
 @brief get memory block for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @return memory block for fuzzy PID controller
*/
A_EXTERN void *a_pid_fuzzy_bfuzz(a_pid_fuzzy const *ctx);

/*!
 @brief set memory block for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] ptr points to a buffer at least A_PID_FUZZY_BFUZZ(num)
 @param[in] num the maximum number triggered by the rule
*/
A_EXTERN void a_pid_fuzzy_set_bfuzz(a_pid_fuzzy *ctx, void *ptr, a_size num);

/*!
 @brief compute size of memory block for fuzzy PID controller
 @param[in] n the maximum number triggered by the rule
*/
#define A_PID_FUZZY_BFUZZ(n) (sizeof(unsigned int) * (n) * 2 + sizeof(a_real) * (n) * (2 + (n)))

/*!
 @brief set rule base for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] nrule number of order in the square matrix
 @param[in] me points to e's membership function parameter table
 @param[in] mec points to ec's membership function parameter table
 @param[in] mkp points to Kp's rule base table which must be a square matrix
 @param[in] mki points to Ki's rule base table which must be a square matrix
 @param[in] mkd points to Kd's rule base table which must be a square matrix
*/
A_EXTERN void a_pid_fuzzy_set_rule(a_pid_fuzzy *ctx, unsigned int nrule, a_real const *me, a_real const *mec,
                                   a_real const *mkp, a_real const *mki, a_real const *mkd);

/*!
 @brief set proportional integral derivative constant for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN void a_pid_fuzzy_set_kpid(a_pid_fuzzy *ctx, a_real kp, a_real ki, a_real kd);

/*!
 @brief compute for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return setpoint value
*/
A_EXTERN a_real a_pid_fuzzy_run(a_pid_fuzzy *ctx, a_real set, a_real fdb);

/*!
 @brief compute for positional fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return output value
*/
A_EXTERN a_real a_pid_fuzzy_pos(a_pid_fuzzy *ctx, a_real set, a_real fdb);

/*!
 @brief compute for incremental fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return output value
*/
A_EXTERN a_real a_pid_fuzzy_inc(a_pid_fuzzy *ctx, a_real set, a_real fdb);

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
    a_pid pid; /*!< instance structure for PID controller */

    a_real const *me; /*!< points to e's membership function parameter table */
    a_real const *mec; /*!< points to ec's membership function parameter table */
    a_real const *mkp; /*!< points to Kp's rule base, which must be a square matrix */
    a_real const *mki; /*!< points to Ki's rule base, which must be a square matrix */
    a_real const *mkd; /*!< points to Kd's rule base, which must be a square matrix */

    unsigned int *idx; /*!< the memory block for membership index, >= 2N */
    a_real *val; /*!< the memory block for membership value and membership outer product of e and ec, >= (2+N)N */

    a_real (*opr)(a_real, a_real); /*!< fuzzy relational operator */

    a_real kp; /*!< base proportional constant */
    a_real ki; /*!< base integral constant */
    a_real kd; /*!< base derivative constant */

    unsigned int nrule; /*!< number of order in the square matrix */
    unsigned int nfuzz; /*!< maximum number triggered by the rule */
#if defined(__cplusplus)
    A_INLINE void init() { a_pid_fuzzy_init(this); }
    A_INLINE void set_opr(unsigned int opr_)
    {
        a_pid_fuzzy_set_opr(this, opr_);
    }
    A_INLINE void *bfuzz() const { return a_pid_fuzzy_bfuzz(this); }
    A_INLINE void set_bfuzz(void *ptr, a_size num)
    {
        a_pid_fuzzy_set_bfuzz(this, ptr, num);
    }
    A_INLINE void set_rule(unsigned int nrule_, a_real const *me_, a_real const *mec_,
                           a_real const *mkp_, a_real const *mki_, a_real const *mkd_)
    {
        a_pid_fuzzy_set_rule(this, nrule_, me_, mec_, mkp_, mki_, mkd_);
    }
    A_INLINE void set_kpid(a_real kp_, a_real ki_, a_real kd_)
    {
        a_pid_fuzzy_set_kpid(this, kp_, ki_, kd_);
    }
    A_INLINE a_real run(a_real set, a_real fdb)
    {
        return a_pid_fuzzy_run(this, set, fdb);
    }
    A_INLINE a_real pos(a_real set, a_real fdb)
    {
        return a_pid_fuzzy_pos(this, set, fdb);
    }
    A_INLINE a_real inc(a_real set, a_real fdb)
    {
        return a_pid_fuzzy_inc(this, set, fdb);
    }
    A_INLINE void zero() { a_pid_fuzzy_zero(this); }
#endif /* __cplusplus */
};

/*! @} a_pid_fuzzy */

#endif /* a/pid_fuzzy.h */
