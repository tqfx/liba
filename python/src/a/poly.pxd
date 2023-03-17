from a cimport *

cdef extern from "a/poly.h":
    a_real_t *a_poly_inv(a_real_t *a, a_size_t n)
    a_real_t a_poly_eval(const a_real_t *a, a_size_t n, a_real_t x)
    a_real_t *a_poly_evaln(const a_real_t *a, a_size_t n, const a_real_t *ptr, a_size_t num, a_real_t *out)
    a_real_t a_poly_evar(const a_real_t *a, a_size_t n, a_real_t x)
    a_real_t *a_poly_evarn(const a_real_t *a, a_size_t n, const a_real_t *ptr, a_size_t num, a_real_t *out)
