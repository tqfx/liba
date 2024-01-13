from a cimport *

cdef extern from "a/polytraj3.h":
    ctypedef struct a_polytraj3:
        a_float q[4]
        a_float v[3]
        a_float a[2]
    void a_polytraj3_gen(a_polytraj3 *ctx, a_float t0, a_float t1, a_float q0, a_float q1, a_float v0, a_float v1)
    a_float a_polytraj3_pos(const a_polytraj3 *ctx, a_float dt)
    a_float a_polytraj3_vel(const a_polytraj3 *ctx, a_float dt)
    a_float a_polytraj3_acc(const a_polytraj3 *ctx, a_float dt)
