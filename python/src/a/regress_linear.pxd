from a cimport *

cdef extern from "a/regress_linear.h":
    ctypedef struct a_regress_linear:
        a_float *coef_p
        a_size coef_n
        a_float bias
    void a_regress_linear_init(a_regress_linear *ctx, a_float *coef_p, a_size coef_n, a_float bias)
    a_float a_regress_linear_eval(const a_regress_linear *ctx, const a_float *val) nogil
    void a_regress_linear_err(const a_regress_linear *ctx, a_size n, const a_float *x, const a_float *y, a_float *err)
    void a_regress_linear_pdm(const a_regress_linear *ctx, a_size n, const a_float *x, a_float *pdm, a_float y_mean)
    void a_regress_linear_gd(a_regress_linear *ctx, const a_float *input, a_float error, a_float alpha)
    void a_regress_linear_sgd(a_regress_linear *ctx, a_size n, const a_float *x, const a_float *y, a_float alpha)
    void a_regress_linear_bgd(a_regress_linear *ctx, a_size n, const a_float *x, const a_float *err, a_float alpha)
    a_float a_regress_linear_mgd(a_regress_linear *ctx, a_size n, const a_float *x, const a_float *y, a_float *err, a_float delta, a_float lrmax, a_float lrmin, a_size lrtim, a_size epoch, a_size batch)
    void a_regress_linear_zero(a_regress_linear *ctx)
