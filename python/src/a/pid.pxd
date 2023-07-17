from a cimport *

cdef extern from "a/pid.h":
    ctypedef enum a_pid_e:
        A_PID_OFF
        A_PID_POS
        A_PID_INC
    ctypedef struct a_pid_s:
        a_float_t kp
        a_float_t ki
        a_float_t kd
        a_float_t summax
        a_float_t outmax
        a_float_t outmin
        a_float_u out
        a_float_u fdb
        a_float_u err
        unsigned int chan
        unsigned int mode
    void a_pid_init(a_pid_s *ctx, unsigned int num)
    void a_pid_chan(a_pid_s *ctx, unsigned int num, a_float_t *out, a_float_t *fdb, a_float_t *tmp, a_float_t *err)
    void a_pid_kpid(a_pid_s *ctx, a_float_t kp, a_float_t ki, a_float_t kd)
    a_float_t a_pid_outf(a_pid_s *ctx, a_float_t set, a_float_t fdb)
    const a_float_t *a_pid_outp(const a_pid_s *ctx, const a_float_t *set, const a_float_t *fdb)
    const a_float_t *a_pid_iter(a_pid_s *ctx, const a_float_t *set, const a_float_t *fdb)
    void a_pid_zero(a_pid_s *ctx)
