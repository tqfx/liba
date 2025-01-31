from a cimport *

cdef extern from "a/lpf.h":
    ctypedef struct a_lpf:
        a_real alpha
        a_real output
    a_real a_lpf_gen(a_real fc, a_real ts) nogil
    void a_lpf_init(a_lpf *ctx, a_real alpha) nogil
    a_real a_lpf_iter(a_lpf *ctx, a_real x) nogil
    void a_lpf_zero(a_lpf *ctx) nogil
