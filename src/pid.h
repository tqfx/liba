#ifndef PID_H
#define PID_H

#include "a/pid.h"
#include "a/math.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_HIDDEN a_float_t a_pid_outf_(a_pid_s *ctx, unsigned int mode, a_float_t set, a_float_t fdb, a_float_t ec, a_float_t e);
A_HIDDEN a_float_t a_pid_outp_(a_pid_s *ctx, unsigned int mode, a_float_t set, a_float_t fdb, a_float_t ec, a_float_t e, unsigned int i);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid.h */
