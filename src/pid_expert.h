#ifndef PID_EXPERT_H
#define PID_EXPERT_H

#include "pid.h"
#include "a/pid_expert.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_HIDDEN void a_pid_expert_zero_(a_pid_expert_s *ctx, unsigned int num);
A_HIDDEN void a_pid_expert_outf_(a_pid_expert_s *ctx, a_float_t fdb, a_float_t ec, a_float_t e);
A_HIDDEN void a_pid_expert_outp_(a_pid_expert_s *ctx, a_float_t fdb, a_float_t ec, a_float_t e, unsigned int i);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid_expert.h */
