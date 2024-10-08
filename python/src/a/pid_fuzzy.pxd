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
        a_float kp
        a_float ki
        a_float kd
        a_float (*opr)(a_float, a_float)
        unsigned int nrule
        unsigned int nfuzz
    void a_pid_fuzzy_init(a_pid_fuzzy *ctx)
    a_float (*a_pid_fuzzy_opr(unsigned int opr))(a_float, a_float)
    void a_pid_fuzzy_set_opr(a_pid_fuzzy *ctx, unsigned int opr)
    void *a_pid_fuzzy_bfuzz(a_pid_fuzzy *ctx)
    void a_pid_fuzzy_set_bfuzz(a_pid_fuzzy *ctx, void *ptr, a_size num)
    a_size A_PID_FUZZY_BFUZZ(unsigned int num)
    void a_pid_fuzzy_set_rule(a_pid_fuzzy *ctx, unsigned int nrule, const a_float *mec, const a_float *mec, const a_float *mkp, const a_float *mki, const a_float *mkd)
    void a_pid_fuzzy_set_kpid(a_pid_fuzzy *ctx, a_float kp, a_float ki, a_float kd)
    a_float a_pid_fuzzy_run(a_pid_fuzzy *ctx, a_float set, a_float fdb)
    a_float a_pid_fuzzy_pos(a_pid_fuzzy *ctx, a_float set, a_float fdb)
    a_float a_pid_fuzzy_inc(a_pid_fuzzy *ctx, a_float set, a_float fdb)
    void a_pid_fuzzy_zero(a_pid_fuzzy *ctx)
