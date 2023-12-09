from a cimport *

cdef extern from "a/polytraj7.h":
    ctypedef struct a_polytraj7_s:
        a_float_t q[8]
        a_float_t v[7]
        a_float_t a[6]
        a_float_t j[5]
    void a_polytraj7_gen(a_polytraj7_s *ctx, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0, a_float_t v1, a_float_t a0, a_float_t a1, a_float_t j0, a_float_t j1)
    a_float_t a_polytraj7_pos(const a_polytraj7_s *ctx, a_float_t dt)
    a_float_t a_polytraj7_vel(const a_polytraj7_s *ctx, a_float_t dt)
    a_float_t a_polytraj7_acc(const a_polytraj7_s *ctx, a_float_t dt)
    a_float_t a_polytraj7_jer(const a_polytraj7_s *ctx, a_float_t dt)
