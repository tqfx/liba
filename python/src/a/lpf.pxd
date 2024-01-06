from a cimport *

cdef extern from "a/lpf.h":
    ctypedef struct a_lpf_s:
        a_float_t alpha
        a_float_t output
    a_float_t a_lpf_gen(a_float_t fc, a_float_t ts)
    void a_lpf_init(a_lpf_s *ctx, a_float_t alpha)
    a_float_t a_lpf_iter(a_lpf_s *ctx, a_float_t x)
    void a_lpf_zero(a_lpf_s *ctx)
