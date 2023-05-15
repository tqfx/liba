#ifndef FPID_H
#define FPID_H

#include "pid.h"
#include "a/fpid.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_HIDDEN a_real_t a_fpid_op_or(a_real_t l, a_real_t r);
A_HIDDEN a_real_t a_fpid_op_and(a_real_t l, a_real_t r);
A_HIDDEN a_real_t a_fpid_op_equ(a_real_t l, a_real_t r);
A_HIDDEN a_uint_t a_fpid_mf(a_real_t const *a, a_real_t x, a_uint_t *idx, a_real_t *val);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* fpid.h */
