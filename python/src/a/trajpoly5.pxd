from a cimport *

cdef extern from "a/trajpoly5.h":
    ctypedef struct a_trajpoly5:
        a_float q[6]
        a_float v[5]
        a_float a[4]
    void a_trajpoly5_gen(a_trajpoly5 *ctx, a_float ts, a_float q0, a_float q1, a_float v0, a_float v1, a_float a0, a_float a1)
    a_float a_trajpoly5_pos(const a_trajpoly5 *ctx, a_float dt)
    a_float a_trajpoly5_vel(const a_trajpoly5 *ctx, a_float dt)
    a_float a_trajpoly5_acc(const a_trajpoly5 *ctx, a_float dt)
