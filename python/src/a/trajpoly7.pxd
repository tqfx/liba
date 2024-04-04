from a cimport *

cdef extern from "a/trajpoly7.h":
    ctypedef struct a_trajpoly7:
        a_float[8] p
        a_float[7] v
        a_float[6] a
        a_float[5] j
    void a_trajpoly7_gen(a_trajpoly7 *ctx, a_float ts, a_float p0, a_float p1, a_float v0, a_float v1, a_float a0, a_float a1, a_float j0, a_float j1)
    a_float a_trajpoly7_pos(const a_trajpoly7 *ctx, a_float x) nogil
    a_float a_trajpoly7_vel(const a_trajpoly7 *ctx, a_float x) nogil
    a_float a_trajpoly7_acc(const a_trajpoly7 *ctx, a_float x) nogil
    a_float a_trajpoly7_jer(const a_trajpoly7 *ctx, a_float x) nogil
