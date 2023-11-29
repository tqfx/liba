from a cimport *

cdef extern from "a/polytraj.h":
    ctypedef struct a_polytraj3_s:
        a_float_t q[4]
        a_float_t v[3]
        a_float_t a[2]
    void a_polytraj3_gen(a_polytraj3_s *ctx, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0, a_float_t v1)
    a_float_t a_polytraj3_pos(const a_polytraj3_s *ctx, a_float_t dt)
    a_float_t a_polytraj3_vel(const a_polytraj3_s *ctx, a_float_t dt)
    a_float_t a_polytraj3_acc(const a_polytraj3_s *ctx, a_float_t dt)
    ctypedef struct a_polytraj5_s:
        a_float_t q[6]
        a_float_t v[5]
        a_float_t a[4]
    void a_polytraj5_gen(a_polytraj5_s *ctx, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0, a_float_t v1, a_float_t a0, a_float_t a1)
    a_float_t a_polytraj5_pos(const a_polytraj5_s *ctx, a_float_t dt)
    a_float_t a_polytraj5_vel(const a_polytraj5_s *ctx, a_float_t dt)
    a_float_t a_polytraj5_acc(const a_polytraj5_s *ctx, a_float_t dt)
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
