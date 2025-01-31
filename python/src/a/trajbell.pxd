from a cimport *

cdef extern from "a/trajbell.h":
    ctypedef struct a_trajbell:
        a_real t
        a_real tv
        a_real ta
        a_real td
        a_real taj
        a_real tdj
        a_real p0
        a_real p1
        a_real v0
        a_real v1
        a_real vm
        a_real jm
        a_real am
        a_real dm
    a_real a_trajbell_gen(a_trajbell *ctx, a_real jm, a_real am, a_real vm, a_real p0, a_real p1, a_real v0, a_real v1) nogil
    a_real a_trajbell_pos(const a_trajbell *ctx, a_real x) nogil
    a_real a_trajbell_vel(const a_trajbell *ctx, a_real x) nogil
    a_real a_trajbell_acc(const a_trajbell *ctx, a_real x) nogil
    a_real a_trajbell_jer(const a_trajbell *ctx, a_real x) nogil
