from a cimport *

cdef extern from "a/traptraj.h":
    ctypedef struct a_traptraj:
        a_float ac
        a_float de
        a_float q1
        a_float q2
        a_float t1
        a_float t2
        a_float vs
        a_float vc
        a_float ve
        a_float q
        a_float t
    a_float a_traptraj_gen(a_traptraj *ctx, a_float qm, a_float vm, a_float ac, a_float de, a_float vs, a_float ve)
    a_float a_traptraj_pos(const a_traptraj *ctx, a_float dt)
    a_float a_traptraj_vel(const a_traptraj *ctx, a_float dt)
    a_float a_traptraj_acc(const a_traptraj *ctx, a_float dt)
