from a cimport *

cdef extern from "a/poly.h":
    a_float_t *a_poly_swap(a_float_t *a, a_size_t n)
    a_float_t a_poly_eval(const a_float_t *a, a_size_t n, a_float_t x)
    a_float_t *a_poly_evaln(const a_float_t *a, a_size_t n, const a_float_t *ptr, a_size_t num, a_float_t *out)
    a_float_t a_poly_evar(const a_float_t *a, a_size_t n, a_float_t x)
    a_float_t *a_poly_evarn(const a_float_t *a, a_size_t n, const a_float_t *ptr, a_size_t num, a_float_t *out)
