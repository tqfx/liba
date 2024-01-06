from a cimport *

cdef extern from "a/hpf.h":
    ctypedef struct a_hpf_s:
        a_float_t alpha
        a_float_t output
        a_float_t input
    a_float_t a_hpf_gen(a_float_t fc, a_float_t ts)
    void a_hpf_init(a_hpf_s *ctx, a_float_t alpha)
    a_float_t a_hpf_iter(a_hpf_s *ctx, a_float_t x)
    void a_hpf_zero(a_hpf_s *ctx)
