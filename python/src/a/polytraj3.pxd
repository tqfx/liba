from a cimport *

cdef extern from "a/polytraj3.h":
    ctypedef struct a_polytraj3_s:
        a_float_t q[4]
        a_float_t v[3]
        a_float_t a[2]
    void a_polytraj3_gen(a_polytraj3_s *ctx, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0, a_float_t v1)
    a_float_t a_polytraj3_pos(const a_polytraj3_s *ctx, a_float_t dt)
    a_float_t a_polytraj3_vel(const a_polytraj3_s *ctx, a_float_t dt)
    a_float_t a_polytraj3_acc(const a_polytraj3_s *ctx, a_float_t dt)
