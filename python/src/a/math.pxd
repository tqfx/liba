from a cimport *

cdef extern from "a/math.h":
    a_f32_t a_f32_rsqrt(a_f32_t x)
    a_f64_t a_f64_rsqrt(a_f64_t x)
