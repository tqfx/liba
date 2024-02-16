from a cimport *

cdef extern from "a/trajpoly7.h":
    ctypedef struct a_trajpoly7:
        a_float p[8]
        a_float v[7]
        a_float a[6]
        a_float j[5]
    void a_trajpoly7_gen(a_trajpoly7 *ctx, a_float ts, a_float p0, a_float p1, a_float v0, a_float v1, a_float a0, a_float a1, a_float j0, a_float j1)
    a_float a_trajpoly7_pos(const a_trajpoly7 *ctx, a_float dt) nogil
    a_float a_trajpoly7_vel(const a_trajpoly7 *ctx, a_float dt) nogil
    a_float a_trajpoly7_acc(const a_trajpoly7 *ctx, a_float dt) nogil
    a_float a_trajpoly7_jer(const a_trajpoly7 *ctx, a_float dt) nogil
