from a cimport *

cdef extern from "a/trajpoly7.h":
    ctypedef struct a_trajpoly7:
        a_real[8] p
        a_real[7] v
        a_real[6] a
        a_real[5] j
    void a_trajpoly7_gen(a_trajpoly7 *ctx, a_real ts, a_real p0, a_real p1, a_real v0, a_real v1, a_real a0, a_real a1, a_real j0, a_real j1)
    a_real a_trajpoly7_pos(const a_trajpoly7 *ctx, a_real x) nogil
    a_real a_trajpoly7_vel(const a_trajpoly7 *ctx, a_real x) nogil
    a_real a_trajpoly7_acc(const a_trajpoly7 *ctx, a_real x) nogil
    a_real a_trajpoly7_jer(const a_trajpoly7 *ctx, a_real x) nogil
