from a cimport *

cdef extern from "a/trajpoly5.h":
    ctypedef struct a_trajpoly5:
        a_real[6] c
    void a_trajpoly5_gen(a_trajpoly5 *ctx, a_real ts, a_real p0, a_real p1, a_real v0, a_real v1, a_real a0, a_real a1) nogil
    a_real a_trajpoly5_pos(const a_trajpoly5 *ctx, a_real x) nogil
    a_real a_trajpoly5_vel(const a_trajpoly5 *ctx, a_real x) nogil
    a_real a_trajpoly5_acc(const a_trajpoly5 *ctx, a_real x) nogil
    void a_trajpoly5_c0(const a_trajpoly5 *ctx, a_real[6] c) nogil
    void a_trajpoly5_c1(const a_trajpoly5 *ctx, a_real[5] c) nogil
    void a_trajpoly5_c2(const a_trajpoly5 *ctx, a_real[4] c) nogil
