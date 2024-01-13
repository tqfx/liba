from a.pid cimport *

cdef extern from "a/pid_neuro.h":
    ctypedef struct a_pid_neuro:
        a_pid pid
        a_float k
        a_float wp
        a_float wi
        a_float wd
        a_float ec
    void a_pid_neuro_init(a_pid_neuro *ctx)
    void a_pid_neuro_kpid(a_pid_neuro *ctx, a_float k, a_float kp, a_float ki, a_float kd)
    void a_pid_neuro_wpid(a_pid_neuro *ctx, a_float wp, a_float wi, a_float wd)
    a_float a_pid_neuro_run(a_pid_neuro *ctx, a_float set, a_float fdb)
    a_float a_pid_neuro_inc(a_pid_neuro *ctx, a_float set, a_float fdb)
    void a_pid_neuro_zero(a_pid_neuro *ctx)
