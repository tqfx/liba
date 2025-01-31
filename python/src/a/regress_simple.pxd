from a cimport *

cdef extern from "a/regress_simple.h":
    ctypedef struct a_regress_simple:
        a_real coef
        a_real bias
    void a_regress_simple_init(a_regress_simple *ctx, a_real coef, a_real bias) nogil
    a_real a_regress_simple_eval(const a_regress_simple *ctx, a_real val) nogil
    a_real a_regress_simple_evar(const a_regress_simple *ctx, a_real val) nogil
    void a_regress_simple_ols_(a_regress_simple *ctx, a_size n, const a_real *x, const a_real *y, a_real x_mean, a_real y_mean) nogil
    void a_regress_simple_olsx(a_regress_simple *ctx, a_size n, const a_real *x, const a_real *y, a_real x_mean) nogil
    void a_regress_simple_olsy(a_regress_simple *ctx, a_size n, const a_real *x, const a_real *y, a_real y_mean) nogil
    void a_regress_simple_ols(a_regress_simple *ctx, a_size n, const a_real *x, const a_real *y) nogil
    void a_regress_simple_zero(a_regress_simple *ctx) nogil
