from a cimport *

cdef extern from "a/math.h":
    a_u16 a_u32_sqrt(a_u32 x) nogil
    a_u32 a_u64_sqrt(a_u64 x) nogil
    a_f32 a_f32_rsqrt(a_f32 x) nogil
    a_f64 a_f64_rsqrt(a_f64 x) nogil
