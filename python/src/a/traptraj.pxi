from a.traptraj cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class traptraj:
    cdef a_traptraj ctx
    def __init__(self, a_float qm, a_float vm, a_float ac, a_float de, a_float vs = 0, a_float ve = 0):
        a_traptraj_gen(&self.ctx, qm, vm, ac, de, vs, ve)
    def gen(self, a_float qm, a_float vm, a_float ac, a_float de, a_float vs = 0, a_float ve = 0):
        return a_traptraj_gen(&self.ctx, qm, vm, ac, de, vs, ve)
    def pos(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_traptraj_pos(&self.ctx, it)
            return out
        return a_traptraj_pos(&self.ctx, dt)
    def vel(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_traptraj_vel(&self.ctx, it)
            return out
        return a_traptraj_vel(&self.ctx, dt)
    def acc(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_traptraj_acc(&self.ctx, it)
            return out
        return a_traptraj_acc(&self.ctx, dt)
    property ac:
        def __get__(self):
            return self.ctx.ac
    property de:
        def __get__(self):
            return self.ctx.de
    property ta:
        def __get__(self):
            return self.ctx.ta
    property qa:
        def __get__(self):
            return self.ctx.qa
    property tc:
        def __get__(self):
            return self.ctx.tc
    property qc:
        def __get__(self):
            return self.ctx.qc
    property td:
        def __get__(self):
            return self.ctx.td
    property qd:
        def __get__(self):
            return self.ctx.qd
    property vs:
        def __get__(self):
            return self.ctx.vs
    property vc:
        def __get__(self):
            return self.ctx.vc
    property ve:
        def __get__(self):
            return self.ctx.ve
