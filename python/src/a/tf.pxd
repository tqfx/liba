from a cimport *

cdef extern from "a/tf.h":
    ctypedef struct a_tf:
        pass
    void a_tf_set_num(a_tf *ctx, unsigned int num_n, const a_float *num_p, a_float *input)
    void a_tf_set_den(a_tf *ctx, unsigned int den_n, const a_float *den_p, a_float *output)
    void a_tf_init(a_tf *ctx, unsigned int num_n, const a_float *num_p, a_float *input, unsigned int den_n, const a_float *den_p, a_float *output)
    a_float a_tf_iter(const a_tf *ctx, a_float x)
    void a_tf_zero(const a_tf*ctx)
