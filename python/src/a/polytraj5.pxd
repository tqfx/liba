from a cimport *

cdef extern from "a/polytraj5.h":
    ctypedef struct a_polytraj5_s:
        a_float_t q[6]
        a_float_t v[5]
        a_float_t a[4]
    void a_polytraj5_gen(a_polytraj5_s *ctx, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0, a_float_t v1, a_float_t a0, a_float_t a1)
    a_float_t a_polytraj5_pos(const a_polytraj5_s *ctx, a_float_t dt)
    a_float_t a_polytraj5_vel(const a_polytraj5_s *ctx, a_float_t dt)
    a_float_t a_polytraj5_acc(const a_polytraj5_s *ctx, a_float_t dt)
