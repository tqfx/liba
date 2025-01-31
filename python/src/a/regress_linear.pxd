from a cimport *

cdef extern from "a/regress_linear.h":
    ctypedef struct a_regress_linear:
        a_real *coef_p
        a_size coef_n
        a_real bias
    void a_regress_linear_init(a_regress_linear *ctx, a_real *coef_p, a_size coef_n, a_real bias) nogil
    a_real a_regress_linear_eval(const a_regress_linear *ctx, const a_real *val) nogil
    void a_regress_linear_err(const a_regress_linear *ctx, a_size n, const a_real *x, const a_real *y, a_real *err) nogil
    void a_regress_linear_pdm(const a_regress_linear *ctx, a_size n, const a_real *x, a_real *pdm, a_real y_mean) nogil
    void a_regress_linear_gd(a_regress_linear *ctx, const a_real *input, a_real error, a_real alpha) nogil
    void a_regress_linear_sgd(a_regress_linear *ctx, a_size n, const a_real *x, const a_real *y, a_real alpha) nogil
    void a_regress_linear_bgd(a_regress_linear *ctx, a_size n, const a_real *x, const a_real *err, a_real alpha) nogil
    a_real a_regress_linear_mgd(a_regress_linear *ctx, a_size n, const a_real *x, const a_real *y, a_real *err, a_real delta, a_real lrmax, a_real lrmin, a_size lrtim, a_size epoch, a_size batch) nogil
    void a_regress_linear_zero(a_regress_linear *ctx) nogil
