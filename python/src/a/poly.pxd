from a cimport *

cdef extern from "a/poly.h":
    void a_poly_swap(a_float *a, a_size n) nogil
    a_float a_poly_eval(const a_float *a, a_size n, a_float x) nogil
    a_float a_poly_evar(const a_float *a, a_size n, a_float x) nogil
