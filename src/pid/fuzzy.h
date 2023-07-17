#ifndef PID_FUZZY_H
#define PID_FUZZY_H

#include "../pid.h"
#include "a/pid/fuzzy.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_HIDDEN a_float_t a_pid_fuzzy_op_or(a_float_t l, a_float_t r);
A_HIDDEN a_float_t a_pid_fuzzy_op_and(a_float_t l, a_float_t r);
A_HIDDEN a_float_t a_pid_fuzzy_op_equ(a_float_t l, a_float_t r);
A_HIDDEN unsigned int a_pid_fuzzy_mf(a_float_t x, unsigned int n, a_float_t const *a, unsigned int *idx, a_float_t *val);
A_HIDDEN void a_pid_fuzzy_out_(a_pid_fuzzy_s *const ctx, a_float_t ec, a_float_t e);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid/fuzzy.h */
