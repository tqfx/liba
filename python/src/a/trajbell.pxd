from a cimport *

cdef extern from "a/trajbell.h":
    ctypedef struct a_trajbell:
        a_float t
        a_float tv
        a_float ta
        a_float td
        a_float taj
        a_float tdj
        a_float p0
        a_float p1
        a_float v0
        a_float v1
        a_float vm
        a_float jm
        a_float am
        a_float dm
    a_float a_trajbell_gen(a_trajbell *ctx, a_float jm, a_float am, a_float vm, a_float p0, a_float p1, a_float v0, a_float v1)
    a_float a_trajbell_pos(const a_trajbell *ctx, a_float dt) nogil
    a_float a_trajbell_vel(const a_trajbell *ctx, a_float dt) nogil
    a_float a_trajbell_acc(const a_trajbell *ctx, a_float dt) nogil
    a_float a_trajbell_jer(const a_trajbell *ctx, a_float dt) nogil
