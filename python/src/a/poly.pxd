from a cimport *

cdef extern from "a/poly.h":
    void a_poly_swap(a_real *a, a_size n) nogil
    a_real a_poly_eval(const a_real *a, a_size n, a_real x) nogil
    a_real a_poly_evar(const a_real *a, a_size n, a_real x) nogil
