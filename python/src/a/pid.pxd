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
        a_float_t summin
        a_float_t outmax
        a_float_t outmin
        a_float_t out
        a_float_t fdb
        a_float_t err
    void a_pid_init(a_pid_s *ctx)
    void a_pid_kpid(a_pid_s *ctx, a_float_t kp, a_float_t ki, a_float_t kd)
    a_float_t a_pid_off(a_pid_s *ctx, a_float_t set, a_float_t fdb)
    a_float_t a_pid_pos(a_pid_s *ctx, a_float_t set, a_float_t fdb)
    a_float_t a_pid_inc(a_pid_s *ctx, a_float_t set, a_float_t fdb)
    void a_pid_zero(a_pid_s *ctx)
