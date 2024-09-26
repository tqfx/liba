from a cimport *

cdef extern from "a/regress_simple.h":
    ctypedef struct a_regress_simple:
        a_float coef
        a_float bias
    void a_regress_simple_init(a_regress_simple *ctx, a_float coef, a_float bias)
    a_float a_regress_simple_eval(const a_regress_simple *ctx, a_float val) nogil
    a_float a_regress_simple_evar(const a_regress_simple *ctx, a_float val) nogil
    void a_regress_simple_ols_(a_regress_simple *ctx, a_size n, const a_float *x, const a_float *y, a_float x_mean, a_float y_mean)
    void a_regress_simple_olsx(a_regress_simple *ctx, a_size n, const a_float *x, const a_float *y, a_float x_mean)
    void a_regress_simple_olsy(a_regress_simple *ctx, a_size n, const a_float *x, const a_float *y, a_float y_mean)
    void a_regress_simple_ols(a_regress_simple *ctx, a_size n, const a_float *x, const a_float *y)
    void a_regress_simple_zero(a_regress_simple *ctx)
