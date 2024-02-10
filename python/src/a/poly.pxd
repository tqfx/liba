from a cimport *

cdef extern from "a/poly.h":
    a_float *a_poly_swap(a_float *a, a_size n)
    a_float a_poly_eval(const a_float *a, a_size n, a_float x) nogil
    a_float a_poly_evar(const a_float *a, a_size n, a_float x) nogil
