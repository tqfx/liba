from a cimport *

cdef extern from "a/trajtrap.h":
    ctypedef struct a_trajtrap:
        a_real t
        a_real p0
        a_real p1
        a_real v0
        a_real v1
        a_real vc
        a_real ta
        a_real td
        a_real pa
        a_real pd
        a_real ac
        a_real de
    a_real a_trajtrap_gen(a_trajtrap *ctx, a_real vm, a_real ac, a_real de, a_real p0, a_real p1, a_real v0, a_real v1) nogil
    a_real a_trajtrap_pos(const a_trajtrap *ctx, a_real x) nogil
    a_real a_trajtrap_vel(const a_trajtrap *ctx, a_real x) nogil
    a_real a_trajtrap_acc(const a_trajtrap *ctx, a_real x) nogil
