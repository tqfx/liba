from a cimport *

cdef extern from "a/polytraj7.h":
    ctypedef struct a_polytraj7:
        a_float q[8]
        a_float v[7]
        a_float a[6]
        a_float j[5]
    void a_polytraj7_gen(a_polytraj7 *ctx, a_float t0, a_float t1, a_float q0, a_float q1, a_float v0, a_float v1, a_float a0, a_float a1, a_float j0, a_float j1)
    a_float a_polytraj7_pos(const a_polytraj7 *ctx, a_float dt)
    a_float a_polytraj7_vel(const a_polytraj7 *ctx, a_float dt)
    a_float a_polytraj7_acc(const a_polytraj7 *ctx, a_float dt)
    a_float a_polytraj7_jer(const a_polytraj7 *ctx, a_float dt)
