from a.pid cimport *

cdef extern from "a/pid/neuron.h":
    ctypedef struct a_pid_neuron_s:
        a_pid_s pid
        a_float_t k
        a_float_t wp
        a_float_t wi
        a_float_t wd
        a_float_t ec
    void a_pid_neuron_init(a_pid_neuron_s *ctx)
    void a_pid_neuron_kpid(a_pid_neuron_s *ctx, a_float_t k, a_float_t kp, a_float_t ki, a_float_t kd)
    void a_pid_neuron_wpid(a_pid_neuron_s *ctx, a_float_t wp, a_float_t wi, a_float_t wd)
    a_float_t a_pid_neuron_off(a_pid_neuron_s *ctx, a_float_t set, a_float_t fdb)
    a_float_t a_pid_neuron_inc(a_pid_neuron_s *ctx, a_float_t set, a_float_t fdb)
    void a_pid_neuron_zero(a_pid_neuron_s *ctx)
