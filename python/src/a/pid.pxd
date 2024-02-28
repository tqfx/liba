from a cimport *

cdef extern from "a/pid.h":
    ctypedef struct a_pid:
        a_float kp
        a_float ki
        a_float kd
        a_float summax
        a_float summin
        a_float sum
        a_float outmax
        a_float outmin
        a_float out
        a_float fdb
        a_float err
    void a_pid_init(a_pid *ctx)
    void a_pid_kpid(a_pid *ctx, a_float kp, a_float ki, a_float kd)
    a_float a_pid_run(a_pid *ctx, a_float set, a_float fdb)
    a_float a_pid_pos(a_pid *ctx, a_float set, a_float fdb)
    a_float a_pid_inc(a_pid *ctx, a_float set, a_float fdb)
    void a_pid_zero(a_pid *ctx)
