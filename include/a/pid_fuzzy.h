/*!
 @file pid_fuzzy.h
 @brief fuzzy proportional integral derivative controller
*/

#ifndef LIBA_PID_FUZZY_H
#define LIBA_PID_FUZZY_H

#include "mf.h"
#include "pid.h"
#include "fuzzy.h"

/*!
 @ingroup A
 @addtogroup A_PID_FUZZY fuzzy proportional integral derivative controller
 @{
*/

#define A_PID_FUZZY_BITL A_PID_MODE_BITH
#define A_PID_FUZZY_BIT 0x04 // 00111100
#define A_PID_FUZZY_BITH (A_PID_FUZZY_BITL + A_PID_FUZZY_BIT)
#define A_PID_FUZZY_MSK (~(~0U << A_PID_FUZZY_BITH) & (~0U << A_PID_FUZZY_BITL))

/*!
 @brief instance enumeration for fuzzy PID controller operator
*/
typedef enum a_pid_fuzzy_e
{
    A_PID_FUZZY_EQU, //!< sqrt(l,r)*sqrt(1-(1-r)*(1-r))
    A_PID_FUZZY_AND = (1 << (A_PID_FUZZY_BITL + 2)), // 00010000 + 0100 * 0
    A_PID_FUZZY_AND_DEFAULT = A_PID_FUZZY_AND + (A_FUZZY_DEFAULT << A_PID_FUZZY_BITL), //!< min(l,r)
    A_PID_FUZZY_AND_ALGEBRA = A_PID_FUZZY_AND + (A_FUZZY_ALGEBRA << A_PID_FUZZY_BITL), //!< l*r
    A_PID_FUZZY_AND_BOUNDED = A_PID_FUZZY_AND + (A_FUZZY_BOUNDED << A_PID_FUZZY_BITL), //!< max(l,r)
    A_PID_FUZZY_OR = (1 << (A_PID_FUZZY_BITL + 3)), // 00100000 + 0100 * 0
    A_PID_FUZZY_OR_DEFAULT = A_PID_FUZZY_OR + (A_FUZZY_DEFAULT << A_PID_FUZZY_BITL), //!< max(l,r)
    A_PID_FUZZY_OR_ALGEBRA = A_PID_FUZZY_OR + (A_FUZZY_ALGEBRA << A_PID_FUZZY_BITL), //!< l+r-l*r
    A_PID_FUZZY_OR_BOUNDED = A_PID_FUZZY_OR + (A_FUZZY_BOUNDED << A_PID_FUZZY_BITL) //!< min(l,r)
} a_pid_fuzzy_e;

/*!
 @brief instance structure for fuzzy PID controller
*/
typedef struct a_pid_fuzzy_s
{
    a_pid_s pid; //!< instance structure for PID controller

    a_float_t const *me; //!< points to membership function parameter table, terminated by @ref A_MF_NUL
    a_float_t const *mec; //!< points to membership function parameter table, terminated by @ref A_MF_NUL
    a_float_t const *mkp; //!< points to Kp's rule base table, the rule base must be square matrix
    a_float_t const *mki; //!< points to Ki's rule base table, the rule base must be square matrix
    a_float_t const *mkd; //!< points to Kd's rule base table, the rule base must be square matrix

    unsigned int *idx; //!< the memory cache for membership index, >= 2N
    a_float_t *val; //!< the memory cache for membership value and membership outer product of e and ec, >= (2+N)N
    a_float_t (*op)(a_float_t, a_float_t); //!< fuzzy relational operator

    a_float_t kp; //!< base proportional constant
    a_float_t ki; //!< base integral constant
    a_float_t kd; //!< base derivative constant
} a_pid_fuzzy_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
#if defined(LIBA_PID_FUZZY_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_PID_FUZZY_C */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_FUZZY_C)
A_EXTERN a_size_t A_PID_FUZZY_BUF1(unsigned int max);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_FUZZY_C)
A_INTERN a_size_t A_PID_FUZZY_BUF1(unsigned int const max)
{
    return sizeof(unsigned int) * 2 * max + sizeof(a_float_t) * (2 + max) * max;
}
#endif /* A_HAVE_INLINE */
#define A_PID_FUZZY_BUF1(N) (sizeof(unsigned int) * 2 * (N) + sizeof(a_float_t) * (2 + (N)) * (N))

#if !defined A_HAVE_INLINE || defined(LIBA_PID_FUZZY_C)
A_EXTERN void *a_pid_fuzzy_bufptr(a_pid_fuzzy_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_FUZZY_C)
A_INTERN void *a_pid_fuzzy_bufptr(a_pid_fuzzy_s const *const ctx)
{
    return ctx->idx;
}
#endif /* A_HAVE_INLINE */
#define a_pid_fuzzy_bufptr(ctx) (ctx)->idx

#if !defined A_HAVE_INLINE || defined(LIBA_PID_FUZZY_C)
A_EXTERN unsigned int a_pid_fuzzy_bufnum(a_pid_fuzzy_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_FUZZY_C)
A_INTERN unsigned int a_pid_fuzzy_bufnum(a_pid_fuzzy_s const *const ctx)
{
    return ctx->pid.num >> A_PID_NUM_BITH;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_FUZZY_C)
A_EXTERN void a_pid_fuzzy_set_bufmax(a_pid_fuzzy_s *ctx, unsigned int max);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_FUZZY_C)
A_INTERN void a_pid_fuzzy_set_bufmax(a_pid_fuzzy_s *const ctx, unsigned int const max)
{
    ctx->pid.num = (ctx->pid.num & A_PID_NUM_MSK) | (max << A_PID_NUM_BITH);
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_FUZZY_C)
A_EXTERN unsigned int a_pid_fuzzy_col(a_pid_fuzzy_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_FUZZY_C)
A_INTERN unsigned int a_pid_fuzzy_col(a_pid_fuzzy_s const *const ctx)
{
    return ctx->pid.reg >> A_PID_REG_BITH;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_FUZZY_C)
A_EXTERN void a_pid_fuzzy_set_col(a_pid_fuzzy_s *ctx, unsigned int col);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_FUZZY_C)
A_INTERN void a_pid_fuzzy_set_col(a_pid_fuzzy_s *const ctx, unsigned int const col)
{
    ctx->pid.reg = (ctx->pid.reg & A_PID_REG_MSK) | (col << A_PID_REG_BITH);
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_FUZZY_C)
A_EXTERN unsigned int a_pid_fuzzy_op(a_pid_fuzzy_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_FUZZY_C)
A_INTERN unsigned int a_pid_fuzzy_op(a_pid_fuzzy_s const *const ctx)
{
    return ctx->pid.reg & A_PID_FUZZY_MSK;
}
#endif /* A_HAVE_INLINE */

A_EXTERN void a_pid_fuzzy_set_op(a_pid_fuzzy_s *ctx, unsigned int op);

/*!
 @brief turn off fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
A_EXTERN a_pid_fuzzy_s *a_pid_fuzzy_off(a_pid_fuzzy_s *ctx);

/*!
 @brief incremental fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
A_EXTERN a_pid_fuzzy_s *a_pid_fuzzy_inc(a_pid_fuzzy_s *ctx);

/*!
 @brief positional fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] max maximum intergral output
*/
A_EXTERN a_pid_fuzzy_s *a_pid_fuzzy_pos(a_pid_fuzzy_s *ctx, a_float_t max);

/*!
 @brief set proportional integral derivative constant for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN a_pid_fuzzy_s *a_pid_fuzzy_kpid(a_pid_fuzzy_s *ctx, a_float_t kp, a_float_t ki, a_float_t kd);

/*!
 @brief set one cache buffer for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] ptr points to a buffer at least A_PID_FUZZY_BUF1(max)
 @param[in] max the maximum number triggered by the rule
*/
A_EXTERN a_pid_fuzzy_s *a_pid_fuzzy_buf1(a_pid_fuzzy_s *ctx, void *ptr, a_size_t max);

/*!
 @brief set buffer for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] idx the memory cache for membership index, >= 2N
 @param[in] val the memory cache for membership value and membership outer product of e and ec, >= (2+N)N
*/
A_EXTERN a_pid_fuzzy_s *a_pid_fuzzy_buff(a_pid_fuzzy_s *ctx, unsigned int *idx, a_float_t *val);
#define A_PID_FUZZY_VAL1(N) (sizeof(a_float_t) * (2 + (N)) * (N))
#define A_PID_FUZZY_IDX1(N) (sizeof(unsigned int) * 2 * (N))
#define A_PID_FUZZY_VAL(N) ((2 + (N)) * (N))
#define A_PID_FUZZY_IDX(N) (2 * (N))

/*!
 @brief set buffer for multichannel fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] num number of controllers output
 @param[in] out points to controllers output
 @param[in] fdb points to cache feedback buffer
 @param[in] sum points to (integral) output buffer
 @param[in] ec points to error change buffer
 @param[in] e points to error input buffer
*/
A_EXTERN a_pid_fuzzy_s *a_pid_fuzzy_chan(a_pid_fuzzy_s *ctx, unsigned int num, a_float_t *out, a_float_t *fdb,
                                         a_float_t *sum, a_float_t *ec, a_float_t *e);

/*!
 @brief set rule base for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] col number of columns in the rule base
 @param[in] me points to membership function parameter table, terminated by @ref A_MF_NUL
 @param[in] mec points to membership function parameter table, terminated by @ref A_MF_NUL
 @param[in] mkp points to Kp's rule base table, the rule base must be square
 @param[in] mki points to Ki's rule base table, the rule base must be square
 @param[in] mkd points to Kd's rule base table, the rule base must be square
*/
A_EXTERN a_pid_fuzzy_s *a_pid_fuzzy_base(a_pid_fuzzy_s *ctx, unsigned int col, a_float_t const *me, a_float_t const *const mec,
                                         a_float_t const *mkp, a_float_t const *mki, a_float_t const *mkd);

/*!
 @brief initialize function for fuzzy PID controller, default setting is off
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] dt sampling time unit(s)
 @param[in] col number of columns in the rule base
 @param[in] me points to membership function parameter table, terminated by @ref A_MF_NUL
 @param[in] mec points to membership function parameter table, terminated by @ref A_MF_NUL
 @param[in] mkp points to Kp's rule base table, the rule base must be square
 @param[in] mki points to Ki's rule base table, the rule base must be square
 @param[in] mkd points to Kd's rule base table, the rule base must be square
 @param[in] min mininum output
 @param[in] max maxinum output
*/
A_EXTERN a_pid_fuzzy_s *a_pid_fuzzy_init(a_pid_fuzzy_s *ctx, a_float_t dt, unsigned int col, a_float_t const *me, a_float_t const *mec,
                                         a_float_t const *mkp, a_float_t const *mki, a_float_t const *mkd, a_float_t min, a_float_t max);

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
 @brief terminate function for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
A_EXTERN a_pid_fuzzy_s *a_pid_fuzzy_exit(a_pid_fuzzy_s *ctx);

/*!
 @brief zero function for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
A_EXTERN a_pid_fuzzy_s *a_pid_fuzzy_zero(a_pid_fuzzy_s *ctx);

#if defined(LIBA_PID_FUZZY_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_PID_FUZZY_C */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_PID_FUZZY */

#endif /* pid_fuzzy.h */
