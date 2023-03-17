/*!
 @file fpid.h
 @brief fuzzy proportional integral derivative controller
*/

#ifndef LIBA_FPID_H
#define LIBA_FPID_H

#include "mf.h"
#include "pid.h"
#include "fuzzy.h"

/*!
 @ingroup A
 @addtogroup A_FPID fuzzy proportional integral derivative controller
 @{
*/

#define A_FPID_FUZZY_BITS 4 // 00111100
#define A_FPID_FUZZY_BITL A_PID_MODE_BITS
#define A_FPID_FUZZY_BITH (A_FPID_FUZZY_BITS + A_FPID_FUZZY_BITL)
#define A_FPID_FUZZY_MASK (~((1U << A_FPID_FUZZY_BITL) - 1U) & ((1U << A_FPID_FUZZY_BITH) - 1U))

/*!
 @brief instance enumeration for fuzzy PID controller operator
*/
typedef enum a_fpid_e
{
    A_FPID_EQU,
    A_FPID_AND = (1 << (A_FPID_FUZZY_BITL + 2)), // 00010000 + 0100 * 0
    A_FPID_AND_DEFAULT = A_FPID_AND + (A_FUZZY_DEFAULT << A_FPID_FUZZY_BITL),
    A_FPID_AND_ALGEBRA = A_FPID_AND + (A_FUZZY_ALGEBRA << A_FPID_FUZZY_BITL),
    A_FPID_AND_BOUNDED = A_FPID_AND + (A_FUZZY_BOUNDED << A_FPID_FUZZY_BITL),
    A_FPID_OR = (1 << (A_FPID_FUZZY_BITL + 3)), // 00100000 + 0100 * 0
    A_FPID_OR_DEFAULT = A_FPID_OR + (A_FUZZY_DEFAULT << A_FPID_FUZZY_BITL),
    A_FPID_OR_ALGEBRA = A_FPID_OR + (A_FUZZY_ALGEBRA << A_FPID_FUZZY_BITL),
    A_FPID_OR_BOUNDED = A_FPID_OR + (A_FUZZY_BOUNDED << A_FPID_FUZZY_BITL)
} a_fpid_e;

/*!
 @brief instance structure for fuzzy PID controller
*/
typedef struct a_fpid_s
{
    a_pid_s pid[1]; //!< instance structure for PID controller

    a_real_t const *mmp; //!< points to membership function parameter table, an array terminated by @ref A_MF_NUL
    a_real_t const *mkp; //!< points to Kp's rule base table, the rule base must be square
    a_real_t const *mki; //!< points to Ki's rule base table, the rule base must be square
    a_real_t const *mkd; //!< points to Kd's rule base table, the rule base must be square

    a_uint_t *idx; //!< the memory cache for membership index
    /*!< the length must be greater than or equal to twice the maximum number triggered by the rule */
    a_real_t *mms; //!< the memory cache for membership value
    /*!< the length must be greater than or equal to twice the maximum number triggered by the rule */
    a_real_t *mat; //!< the memory cache for matrix of the membership outer product of e and ec
    a_real_t (*op)(a_real_t, a_real_t); //!< fuzzy relational operator

    a_real_t sigma; //!< the coefficient of the input, ((num-1)>>1<<1)/(Imax-Imin)
    a_real_t alpha; //!< the coefficient of the output, (Omax-Omin)/((num-1)>>1<<1)

    a_real_t kp; //!< base proportional constant
    a_real_t ki; //!< base integral constant
    a_real_t kd; //!< base derivative constant
} a_fpid_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
#if defined(LIBA_FPID_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_FPID_C */

#if !defined A_HAVE_INLINE || defined(LIBA_FPID_C)
A_EXTERN a_size_t A_FPID_BUF1(a_uint_t max);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FPID_C)
A_INTERN a_size_t A_FPID_BUF1(a_uint_t const max)
{
    return (sizeof(a_uint_t) << 1) * max + sizeof(a_real_t) * (max + 2) * max;
}
#endif /* A_HAVE_INLINE */
#define A_FPID_BUF1(N) ((sizeof(a_uint_t) << 1) * (N) + sizeof(a_real_t) * ((N) + 2) * (N))

#if !defined A_HAVE_INLINE || defined(LIBA_FPID_C)
A_EXTERN a_vptr_t a_fpid_bufptr(a_fpid_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FPID_C)
A_INTERN a_vptr_t a_fpid_bufptr(a_fpid_s const *const ctx)
{
    return ctx->idx;
}
#endif /* A_HAVE_INLINE */
#define a_fpid_bufptr(ctx) (ctx)->idx

#if !defined A_HAVE_INLINE || defined(LIBA_FPID_C)
A_EXTERN a_uint_t a_fpid_bufnum(a_fpid_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FPID_C)
A_INTERN a_uint_t a_fpid_bufnum(a_fpid_s const *const ctx)
{
    return ctx->pid->num >> A_PID_NUM_BITS;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_FPID_C)
A_EXTERN a_void_t a_fpid_set_bufnum(a_fpid_s *ctx, a_uint_t num);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FPID_C)
A_INTERN a_void_t a_fpid_set_bufnum(a_fpid_s *const ctx, a_uint_t const num)
{
    ctx->pid->num &= A_PID_NUM_MASK;
    ctx->pid->num |= num << A_PID_NUM_BITS;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_FPID_C)
A_EXTERN a_uint_t a_fpid_col(a_fpid_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FPID_C)
A_INTERN a_uint_t a_fpid_col(a_fpid_s const *const ctx)
{
    return ctx->pid->reg >> A_PID_REG_BITS;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_FPID_C)
A_EXTERN a_void_t a_fpid_set_col(a_fpid_s *ctx, a_uint_t reg);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FPID_C)
A_INTERN a_void_t a_fpid_set_col(a_fpid_s *const ctx, a_uint_t const reg)
{
    ctx->pid->reg &= A_PID_REG_MASK;
    ctx->pid->reg |= reg << A_PID_REG_BITS;
}
#endif /* A_HAVE_INLINE */

#if !defined A_HAVE_INLINE || defined(LIBA_FPID_C)
A_EXTERN a_uint_t a_fpid_op(a_fpid_s const *ctx);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FPID_C)
A_INTERN a_uint_t a_fpid_op(a_fpid_s const *const ctx)
{
    return ctx->pid->reg & A_FPID_FUZZY_MASK;
}
#endif /* A_HAVE_INLINE */

A_EXTERN a_void_t a_fpid_set_op(a_fpid_s *ctx, a_uint_t op);

/*!
 @brief turn off fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
A_EXTERN a_fpid_s *a_fpid_off(a_fpid_s *ctx);

/*!
 @brief incremental fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
A_EXTERN a_fpid_s *a_fpid_inc(a_fpid_s *ctx);

/*!
 @brief positional fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] max maximum intergral output
*/
A_EXTERN a_fpid_s *a_fpid_pos(a_fpid_s *ctx, a_real_t max);

/*!
 @brief set input extreme value for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] min mininum input
 @param[in] max maxinum input
*/
A_EXTERN a_fpid_s *a_fpid_ilim(a_fpid_s *ctx, a_real_t min, a_real_t max);

/*!
 @brief set output extreme value for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] min mininum output
 @param[in] max maxinum output
*/
A_EXTERN a_fpid_s *a_fpid_olim(a_fpid_s *ctx, a_real_t min, a_real_t max);

/*!
 @brief set one cache buffer for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] ptr points to a buffer at least A_FPID_BUF1(max)
 @param[in] max the maximum number triggered by the rule
*/
A_EXTERN a_fpid_s *a_fpid_buf1(a_fpid_s *ctx, a_vptr_t ptr, a_size_t max);

/*!
 @brief set proportional integral derivative constant for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN a_fpid_s *a_fpid_kpid(a_fpid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd);

/*!
 @brief set buffer for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] idx the memory cache for membership index
  the length must be greater than or equal to twice the maximum number triggered by the rule
 @param[in] mms the memory cache for membership
  the length must be greater than or equal to twice the maximum number triggered by the rule
 @param[in] mat the memory cache for matrix of the membership outer product of e and ec
*/
A_EXTERN a_fpid_s *a_fpid_buff(a_fpid_s *ctx, a_uint_t *idx, a_real_t *mms, a_real_t *mat);
#define A_FPID_MAT1(N) (sizeof(a_real_t) * (N) * (N))
#define A_FPID_MMS1(N) (sizeof(a_real_t) * 2 * (N))
#define A_FPID_IDX1(N) (sizeof(a_uint_t) * 2 * (N))
#define A_FPID_MAT(N) ((N) * (N))
#define A_FPID_MMS(N) (2 * (N))
#define A_FPID_IDX(N) (2 * (N))

/*!
 @brief set buffer for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] num number of controllers output
 @param[in] out points to controllers output
 @param[in] fdb points to cache feedback buffer
 @param[in] sum points to (integral) output buffer
 @param[in] ec points to error change buffer
 @param[in] e points to error input buffer
*/
A_EXTERN a_fpid_s *a_fpid_setp(a_fpid_s *ctx, a_uint_t num, a_real_t *out, a_real_t *fdb, a_real_t *sum, a_real_t *ec, a_real_t *e);

/*!
 @brief set rule base for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] num number of columns in the rule base
 @param[in] mmp points to membership function parameter table, an array terminated by @ref A_MF_NUL
 @param[in] mkp points to Kp's rule base table, the rule base must be square
 @param[in] mki points to Ki's rule base table, the rule base must be square
 @param[in] mkd points to Kd's rule base table, the rule base must be square
*/
A_EXTERN a_fpid_s *a_fpid_base(a_fpid_s *ctx, a_uint_t num, a_real_t const *mmp, a_real_t const *mkp, a_real_t const *mki, a_real_t const *mkd);

/*!
 @brief initialize function for fuzzy PID controller, default setting is off
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] dt sampling time unit(s)
 @param[in] num number of columns in the rule base
 @param[in] mmp points to membership function parameter table, an array terminated by @ref A_MF_NUL
 @param[in] mkp points to Kp's rule base table, the rule base must be square
 @param[in] mki points to Ki's rule base table, the rule base must be square
 @param[in] mkd points to Kd's rule base table, the rule base must be square
 @param[in] imin mininum input
 @param[in] imax maxinum input
 @param[in] omin mininum output
 @param[in] omax maxinum output
*/
A_EXTERN a_fpid_s *a_fpid_init(a_fpid_s *ctx, a_real_t dt, a_uint_t num, a_real_t const *mmp,
                               a_real_t const *mkp, a_real_t const *mki, a_real_t const *mkd,
                               a_real_t imin, a_real_t imax, a_real_t omin, a_real_t omax);

/*!
 @brief calculate function for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] set setpoint
 @param[in] fdb feedback
 @return output
  @retval set when fuzzy PID controller is off
*/
A_EXTERN a_real_t a_fpid_outv(a_fpid_s *ctx, a_real_t set, a_real_t fdb);

/*!
 @brief calculate function for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] set points to setpoint
 @param[in] fdb points to feedback
 @return points to output
  @retval set when fuzzy PID controller is off
*/
A_EXTERN a_real_t *a_fpid_outp(a_fpid_s *ctx, a_real_t *set, a_real_t *fdb);

/*!
 @brief terminate function for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
A_EXTERN a_fpid_s *a_fpid_exit(a_fpid_s *ctx);

/*!
 @brief zero function for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
*/
A_EXTERN a_fpid_s *a_fpid_zero(a_fpid_s *ctx);

#if defined(LIBA_FPID_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_FPID_C */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_FPID */

#endif /* fpid.h */
