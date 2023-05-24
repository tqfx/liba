#ifndef FPID_H
#define FPID_H

#include "pid.h"
#include "a/fpid.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_HIDDEN a_float_t a_fpid_op_or(a_float_t l, a_float_t r);
A_HIDDEN a_float_t a_fpid_op_and(a_float_t l, a_float_t r);
A_HIDDEN a_float_t a_fpid_op_equ(a_float_t l, a_float_t r);
A_HIDDEN unsigned int a_fpid_mf(a_float_t const *a, a_float_t x, unsigned int *idx, a_float_t *val);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* fpid.h */
