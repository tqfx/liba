from a cimport *

cdef extern from "a/trajtrap.h":
    ctypedef struct a_trajtrap:
        a_float t
        a_float p0
        a_float p1
        a_float v0
        a_float v1
        a_float vc
        a_float ta
        a_float td
        a_float pa
        a_float pd
        a_float ac
        a_float de
    a_float a_trajtrap_gen(a_trajtrap *ctx, a_float vm, a_float ac, a_float de, a_float p0, a_float p1, a_float v0, a_float v1)
    a_float a_trajtrap_pos(const a_trajtrap *ctx, a_float dt) nogil
    a_float a_trajtrap_vel(const a_trajtrap *ctx, a_float dt) nogil
    a_float a_trajtrap_acc(const a_trajtrap *ctx, a_float dt) nogil
