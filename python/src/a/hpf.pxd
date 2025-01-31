from a cimport *

cdef extern from "a/hpf.h":
    ctypedef struct a_hpf:
        a_real alpha
        a_real output
        a_real input
    a_real a_hpf_gen(a_real fc, a_real ts) nogil
    void a_hpf_init(a_hpf *ctx, a_real alpha) nogil
    a_real a_hpf_iter(a_hpf *ctx, a_real x) nogil
    void a_hpf_zero(a_hpf *ctx) nogil
