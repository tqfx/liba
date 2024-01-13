from a cimport *

cdef extern from "a/hpf.h":
    ctypedef struct a_hpf:
        a_float alpha
        a_float output
        a_float input
    a_float a_hpf_gen(a_float fc, a_float ts)
    void a_hpf_init(a_hpf *ctx, a_float alpha)
    a_float a_hpf_iter(a_hpf *ctx, a_float x)
    void a_hpf_zero(a_hpf *ctx)
