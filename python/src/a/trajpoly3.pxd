from a cimport *

cdef extern from "a/trajpoly3.h":
    ctypedef struct a_trajpoly3:
        a_float[4] p
        a_float[3] v
        a_float[2] a
    void a_trajpoly3_gen(a_trajpoly3 *ctx, a_float ts, a_float p0, a_float p1, a_float v0, a_float v1)
    a_float a_trajpoly3_pos(const a_trajpoly3 *ctx, a_float x) nogil
    a_float a_trajpoly3_vel(const a_trajpoly3 *ctx, a_float x) nogil
    a_float a_trajpoly3_acc(const a_trajpoly3 *ctx, a_float x) nogil
