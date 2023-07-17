from a.pid cimport *

cdef extern from "a/pid/neuron.h":
    ctypedef struct a_pid_neuron_s:
        a_pid_s pid
        a_float_u ec
        a_float_u wp
        a_float_u wi
        a_float_u wd
        a_float_t k
    void a_pid_neuron_init(a_pid_neuron_s *ctx, unsigned int num)
    void a_pid_neuron_chan(a_pid_neuron_s *ctx, unsigned int num, a_float_t *out, a_float_t *fdb, a_float_t *tmp, a_float_t *err)
    void a_pid_neuron_kpid(a_pid_neuron_s *ctx, a_float_t k, a_float_t kp, a_float_t ki, a_float_t kd)
    void a_pid_neuron_wpid(a_pid_neuron_s *ctx, a_float_t wp, a_float_t wi, a_float_t wd)
    a_float_t a_pid_neuron_outf(a_pid_neuron_s *ctx, a_float_t set, a_float_t fdb)
    const a_float_t *a_pid_neuron_outp(const a_pid_neuron_s *ctx, const a_float_t *set, const a_float_t *fdb)
    const a_float_t *a_pid_neuron_iter(a_pid_neuron_s *ctx, const a_float_t *set, const a_float_t *fdb)
    void a_pid_neuron_zero(a_pid_neuron_s *ctx)
