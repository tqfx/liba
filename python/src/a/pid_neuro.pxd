from a.pid cimport *

cdef extern from "a/pid_neuro.h":
    ctypedef struct a_pid_neuro:
        a_pid pid
        a_real k
        a_real wp
        a_real wi
        a_real wd
        a_real ec
    void a_pid_neuro_init(a_pid_neuro *ctx) nogil
    void a_pid_neuro_set_kpid(a_pid_neuro *ctx, a_real k, a_real kp, a_real ki, a_real kd) nogil
    void a_pid_neuro_set_wpid(a_pid_neuro *ctx, a_real wp, a_real wi, a_real wd) nogil
    a_real a_pid_neuro_run(a_pid_neuro *ctx, a_real set, a_real fdb) nogil
    a_real a_pid_neuro_inc(a_pid_neuro *ctx, a_real set, a_real fdb) nogil
    void a_pid_neuro_zero(a_pid_neuro *ctx) nogil
