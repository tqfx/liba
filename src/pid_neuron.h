#ifndef PID_NEURON_H
#define PID_NEURON_H

#include "pid.h"
#include "a/pid_neuron.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_HIDDEN void a_pid_neuron_outf_(a_pid_neuron_s *ctx, a_float_t fdb, a_float_t ec, a_float_t e);
A_HIDDEN void a_pid_neuron_outp_(a_pid_neuron_s const *ctx, a_float_t fdb, a_float_t ec, a_float_t e, unsigned int i);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid_neuron.h */
