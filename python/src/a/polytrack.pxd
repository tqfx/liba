from a cimport *

cdef extern from "a/polytrack.h":
    ctypedef struct a_polytrack3_s:
        a_float_t k[4]
    void a_polytrack3_gen(a_polytrack3_s *ctx, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0, a_float_t v1)
    void a_polytrack3_out(const a_polytrack3_s *ctx, a_float_t dt, a_float_t out[3])
    a_float_t a_polytrack3_pos(const a_polytrack3_s *ctx, a_float_t dt)
    a_float_t a_polytrack3_vel(const a_polytrack3_s *ctx, a_float_t dt)
    a_float_t a_polytrack3_acc(const a_polytrack3_s *ctx, a_float_t dt)
    ctypedef struct a_polytrack5_s:
        a_float_t k[6]
    void a_polytrack5_gen(a_polytrack5_s *ctx, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0, a_float_t v1, a_float_t a0, a_float_t a1)
    void a_polytrack5_out(const a_polytrack5_s *ctx, a_float_t dt, a_float_t out[3])
    a_float_t a_polytrack5_pos(const a_polytrack5_s *ctx, a_float_t dt)
    a_float_t a_polytrack5_vel(const a_polytrack5_s *ctx, a_float_t dt)
    a_float_t a_polytrack5_acc(const a_polytrack5_s *ctx, a_float_t dt)
    ctypedef struct a_polytrack7_s:
        a_float_t k[8]
    void a_polytrack7_gen(a_polytrack7_s *ctx, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0, a_float_t v1, a_float_t a0, a_float_t a1, a_float_t j0, a_float_t j1)
    void a_polytrack7_out(const a_polytrack7_s *ctx, a_float_t dt, a_float_t out[4])
    a_float_t a_polytrack7_pos(const a_polytrack7_s *ctx, a_float_t dt)
    a_float_t a_polytrack7_vel(const a_polytrack7_s *ctx, a_float_t dt)
    a_float_t a_polytrack7_acc(const a_polytrack7_s *ctx, a_float_t dt)
    a_float_t a_polytrack7_jer(const a_polytrack7_s *ctx, a_float_t dt)
