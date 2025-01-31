from a cimport *

cdef extern from "a/trajpoly3.h":
    ctypedef struct a_trajpoly3:
        a_real[4] p
        a_real[3] v
        a_real[2] a
    void a_trajpoly3_gen(a_trajpoly3 *ctx, a_real ts, a_real p0, a_real p1, a_real v0, a_real v1) nogil
    a_real a_trajpoly3_pos(const a_trajpoly3 *ctx, a_real x) nogil
    a_real a_trajpoly3_vel(const a_trajpoly3 *ctx, a_real x) nogil
    a_real a_trajpoly3_acc(const a_trajpoly3 *ctx, a_real x) nogil
