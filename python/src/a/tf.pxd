from a cimport *

cdef extern from "a/tf.h":
    ctypedef struct a_tf:
        pass
    void a_tf_set_num(a_tf *ctx, unsigned int num_n, const a_real *num_p, a_real *input) nogil
    void a_tf_set_den(a_tf *ctx, unsigned int den_n, const a_real *den_p, a_real *output) nogil
    void a_tf_init(a_tf *ctx, unsigned int num_n, const a_real *num_p, a_real *input, unsigned int den_n, const a_real *den_p, a_real *output) nogil
    a_real a_tf_iter(const a_tf *ctx, a_real x) nogil
    void a_tf_zero(const a_tf*ctx) nogil
