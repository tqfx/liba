from a cimport *

cdef extern from "a/pid.h":
    ctypedef struct a_pid:
        a_real kp
        a_real ki
        a_real kd
        a_real summax
        a_real summin
        a_real sum
        a_real outmax
        a_real outmin
        a_real out
        a_real fdb
        a_real err
    void a_pid_init(a_pid *ctx) nogil
    void a_pid_set_kpid(a_pid *ctx, a_real kp, a_real ki, a_real kd) nogil
    a_real a_pid_run(a_pid *ctx, a_real set, a_real fdb) nogil
    a_real a_pid_pos(a_pid *ctx, a_real set, a_real fdb) nogil
    a_real a_pid_inc(a_pid *ctx, a_real set, a_real fdb) nogil
    void a_pid_zero(a_pid *ctx) nogil
