from a cimport *

cdef extern from "a/traptraj.h":
    ctypedef struct a_traptraj:
        a_float ac
        a_float de
        a_float ta
        a_float qa
        a_float tc
        a_float qc
        a_float td
        a_float qd
        a_float vs
        a_float vc
        a_float ve
    a_float a_traptraj_gen(a_traptraj *ctx, a_float qm, a_float vm, a_float ac, a_float de, a_float vs, a_float ve)
    a_float a_traptraj_pos(const a_traptraj *ctx, a_float dt)
    a_float a_traptraj_vel(const a_traptraj *ctx, a_float dt)
    a_float a_traptraj_acc(const a_traptraj *ctx, a_float dt)
