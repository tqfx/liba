/*!
 @file fuzzy.h
 @brief fuzzy proportional integral derivative controller
*/

#ifndef LIBA_PID_FUZZY_H
#define LIBA_PID_FUZZY_H

#include "../mf.h"
#include "../pid.h"
#include "../fuzzy.h"

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
    A_PID_FUZZY_EQU, //!< sqrt(l,r)*sqrt(1-(1-r)*(1-r))
    A_PID_FUZZY_AND_DEFAULT, //!< min(l,r)
    A_PID_FUZZY_AND_ALGEBRA, //!< l*r
    A_PID_FUZZY_AND_BOUNDED, //!< max(l,r)
    A_PID_FUZZY_OR_DEFAULT, //!< max(l,r)
    A_PID_FUZZY_OR_ALGEBRA, //!< l+r-l*r
    A_PID_FUZZY_OR_BOUNDED, //!< min(l,r)
    A_PID_FUZZY_AND = A_PID_FUZZY_AND_DEFAULT,
    A_PID_FUZZY_OR = A_PID_FUZZY_OR_DEFAULT
} a_pid_fuzzy_e;

/*!
 @brief instance structure for fuzzy PID controller
*/
typedef struct a_pid_fuzzy_s
{
    a_pid_s pid; //!< instance structure for PID controller

    a_float_t const *me; //!< points to e's membership function parameter table
    a_float_t const *mec; //!< points to ec's membership function parameter table
    a_float_t const *mkp; //!< points to Kp's rule base table, the rule base must be square matrix
    a_float_t const *mki; //!< points to Ki's rule base table, the rule base must be square matrix
    a_float_t const *mkd; //!< points to Kd's rule base table, the rule base must be square matrix

    unsigned int *idx; //!< the memory cache for membership index, >= 2N
    a_float_t *val; //!< the memory cache for membership value and membership outer product of e and ec, >= (2+N)N
    a_float_t (*op)(a_float_t, a_float_t); //!< fuzzy relational operator

    a_float_t kp; //!< base proportional constant
    a_float_t ki; //!< base integral constant
    a_float_t kd; //!< base derivative constant

    unsigned int col; //!< number of columns in the rule base
    unsigned int buf; //!< maximum number triggered by the rule
} a_pid_fuzzy_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
#if defined(LIBA_PID_FUZZY_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_PID_FUZZY_C */

#if !defined A_HAVE_INLINE || defined(LIBA_PID_FUZZY_C)
A_EXTERN a_size_t A_PID_FUZZY_BUF1(unsigned int num);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_PID_FUZZY_C)
A_INTERN a_size_t A_PID_FUZZY_BUF1(unsigned int const num)
{
    return sizeof(unsigned int) * 2 * num + sizeof(a_float_t) * (2 + num) * num;
}
#endif /* A_HAVE_INLINE */
#define A_PID_FUZZY_BUF1(N) (sizeof(unsigned int) * 2 * (N) + sizeof(a_float_t) * (2 + (N)) * (N))

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
 @param[in] col number of columns in the rule base
 @param[in] me points to e's membership function parameter table
 @param[in] mec points to ec's membership function parameter table
 @param[in] mkp points to Kp's rule base table, the rule base must be square
 @param[in] mki points to Ki's rule base table, the rule base must be square
 @param[in] mkd points to Kd's rule base table, the rule base must be square
*/
A_EXTERN void a_pid_fuzzy_rule(a_pid_fuzzy_s *ctx, unsigned int col, a_float_t const *me, a_float_t const *const mec,
                               a_float_t const *mkp, a_float_t const *mki, a_float_t const *mkd);

/*!
 @brief set proportional integral derivative constant for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN void a_pid_fuzzy_kpid(a_pid_fuzzy_s *ctx, a_float_t kp, a_float_t ki, a_float_t kd);

/*!
 @brief set one cache buffer for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] ptr points to a buffer at least A_PID_FUZZY_BUF1(num)
 @param[in] num the maximum number triggered by the rule
*/
A_EXTERN void a_pid_fuzzy_buf1(a_pid_fuzzy_s *ctx, void *ptr, a_size_t num);

/*!
 @brief set buffer for fuzzy PID controller
 @param[in,out] ctx points to an instance of fuzzy PID controller
 @param[in] idx the memory cache for membership index, >= 2N
 @param[in] val the memory cache for membership value and membership outer product of e and ec, >= (2+N)N
*/
A_EXTERN void a_pid_fuzzy_buff(a_pid_fuzzy_s *ctx, unsigned int *idx, a_float_t *val);
#define A_PID_FUZZY_VAL1(N) (sizeof(a_float_t) * (2 + (N)) * (N))
#define A_PID_FUZZY_IDX1(N) (sizeof(unsigned int) * 2 * (N))
#define A_PID_FUZZY_VAL(N) ((2 + (N)) * (N))
#define A_PID_FUZZY_IDX(N) (2 * (N))

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

#if defined(LIBA_PID_FUZZY_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_PID_FUZZY_C */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_PID_FUZZY */

#endif /* pid/fuzzy.h */
