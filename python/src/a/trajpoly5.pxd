from a cimport *

cdef extern from "a/trajpoly5.h":
    ctypedef struct a_trajpoly5:
        a_float[6] p
        a_float[5] v
        a_float[4] a
    void a_trajpoly5_gen(a_trajpoly5 *ctx, a_float ts, a_float p0, a_float p1, a_float v0, a_float v1, a_float a0, a_float a1)
    a_float a_trajpoly5_pos(const a_trajpoly5 *ctx, a_float x) nogil
    a_float a_trajpoly5_vel(const a_trajpoly5 *ctx, a_float x) nogil
    a_float a_trajpoly5_acc(const a_trajpoly5 *ctx, a_float x) nogil
