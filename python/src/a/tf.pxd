from a cimport *

cdef extern from "a/tf.h":
    ctypedef struct a_tf_s:
        pass
    void a_tf_set_num(a_tf_s *ctx, unsigned int num_n, const a_float_t *num_p, a_float_t *input)
    void a_tf_set_den(a_tf_s *ctx, unsigned int den_n, const a_float_t *den_p, a_float_t *output)
    void a_tf_init(a_tf_s *ctx, unsigned int num_n, const a_float_t *num_p, a_float_t *input, unsigned int den_n, const a_float_t *den_p, a_float_t *output)
    a_float_t a_tf_iter(const a_tf_s *ctx, a_float_t x)
    void a_tf_zero(const a_tf_s*ctx)
