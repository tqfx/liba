from a cimport *

cdef extern from "a/polytraj5.h":
    ctypedef struct a_polytraj5:
        a_float q[6]
        a_float v[5]
        a_float a[4]
    void a_polytraj5_gen(a_polytraj5 *ctx, a_float t0, a_float t1, a_float q0, a_float q1, a_float v0, a_float v1, a_float a0, a_float a1)
    a_float a_polytraj5_pos(const a_polytraj5 *ctx, a_float dt)
    a_float a_polytraj5_vel(const a_polytraj5 *ctx, a_float dt)
    a_float a_polytraj5_acc(const a_polytraj5 *ctx, a_float dt)
