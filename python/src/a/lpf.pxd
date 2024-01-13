from a cimport *

cdef extern from "a/lpf.h":
    ctypedef struct a_lpf:
        a_float alpha
        a_float output
    a_float a_lpf_gen(a_float fc, a_float ts)
    void a_lpf_init(a_lpf *ctx, a_float alpha)
    a_float a_lpf_iter(a_lpf *ctx, a_float x)
    void a_lpf_zero(a_lpf *ctx)
