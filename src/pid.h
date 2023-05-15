#ifndef PID_H
#define PID_H

#include "a/pid.h"
#include "a/real.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_HIDDEN a_real_t a_pid_outf_(a_pid_s *ctx, a_uint_t mode, a_real_t set, a_real_t fdb, a_real_t ec, a_real_t e);
A_HIDDEN a_real_t a_pid_outp_(a_pid_s *ctx, a_uint_t mode, a_real_t set, a_real_t fdb, a_real_t ec, a_real_t e, a_uint_t i);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid.h */
