from a cimport *

cdef extern from "a/poly.h":
    a_float *a_poly_swap(a_float *a, a_size n)
    a_float a_poly_eval(const a_float *a, a_size n, a_float x)
    a_float *a_poly_evaln(const a_float *a, a_size n, const a_float *ptr, a_size num, a_float *out)
    a_float a_poly_evar(const a_float *a, a_size n, a_float x)
    a_float *a_poly_evarn(const a_float *a, a_size n, const a_float *ptr, a_size num, a_float *out)
