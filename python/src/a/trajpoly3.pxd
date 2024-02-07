from a cimport *

cdef extern from "a/trajpoly3.h":
    ctypedef struct a_trajpoly3:
        a_float q[4]
        a_float v[3]
        a_float a[2]
    void a_trajpoly3_gen(a_trajpoly3 *ctx, a_float ts, a_float q0, a_float q1, a_float v0, a_float v1)
    a_float a_trajpoly3_pos(const a_trajpoly3 *ctx, a_float dt)
    a_float a_trajpoly3_vel(const a_trajpoly3 *ctx, a_float dt)
    a_float a_trajpoly3_acc(const a_trajpoly3 *ctx, a_float dt)
