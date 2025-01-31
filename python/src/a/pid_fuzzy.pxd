from a.pid cimport *
from a.fuzzy cimport *

cdef extern from "a/pid_fuzzy.h":
    enum:
        A_PID_FUZZY_CAP
        A_PID_FUZZY_CAP_ALGEBRA
        A_PID_FUZZY_CAP_BOUNDED
        A_PID_FUZZY_CUP
        A_PID_FUZZY_CUP_ALGEBRA
        A_PID_FUZZY_CUP_BOUNDED
        A_PID_FUZZY_EQU
    ctypedef struct a_pid_fuzzy:
        a_pid pid
        a_real kp
        a_real ki
        a_real kd
        a_real (*opr)(a_real, a_real)
        unsigned int nrule
        unsigned int nfuzz
    void a_pid_fuzzy_init(a_pid_fuzzy *ctx) nogil
    a_real (*a_pid_fuzzy_opr(unsigned int opr))(a_real, a_real) nogil
    void a_pid_fuzzy_set_opr(a_pid_fuzzy *ctx, unsigned int opr) nogil
    void *a_pid_fuzzy_bfuzz(a_pid_fuzzy *ctx) nogil
    void a_pid_fuzzy_set_bfuzz(a_pid_fuzzy *ctx, void *ptr, a_size num) nogil
    a_size A_PID_FUZZY_BFUZZ(unsigned int num) nogil
    void a_pid_fuzzy_set_rule(a_pid_fuzzy *ctx, unsigned int nrule, const a_real *me, const a_real *mec, const a_real *mkp, const a_real *mki, const a_real *mkd) nogil
    void a_pid_fuzzy_set_kpid(a_pid_fuzzy *ctx, a_real kp, a_real ki, a_real kd) nogil
    a_real a_pid_fuzzy_run(a_pid_fuzzy *ctx, a_real set, a_real fdb) nogil
    a_real a_pid_fuzzy_pos(a_pid_fuzzy *ctx, a_real set, a_real fdb) nogil
    a_real a_pid_fuzzy_inc(a_pid_fuzzy *ctx, a_real set, a_real fdb) nogil
    void a_pid_fuzzy_zero(a_pid_fuzzy *ctx) nogil
