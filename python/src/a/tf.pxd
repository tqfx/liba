from a cimport *

cdef extern from "a/tf.h":
    ctypedef struct a_tf_s:
        pass
    void a_tf_set_num(a_tf_s *ctx, unsigned int m, const a_float_t *num, a_float_t *u)
    void a_tf_set_den(a_tf_s *ctx, unsigned int n, const a_float_t *den, a_float_t *v)
    a_tf_s *a_tf_init(a_tf_s *ctx, unsigned int m, const a_float_t *num, a_float_t *u, unsigned int n, const a_float_t *den, a_float_t *v)
    a_float_t a_tf_iter(a_tf_s *ctx, a_float_t x)
    a_tf_s *a_tf_exit(a_tf_s *ctx)
    a_tf_s *a_tf_zero(a_tf_s *ctx)
