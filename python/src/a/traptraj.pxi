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
    property q1:
        def __get__(self):
            return self.ctx.q1
    property q2:
        def __get__(self):
            return self.ctx.q2
    property t1:
        def __get__(self):
            return self.ctx.t1
    property t2:
        def __get__(self):
            return self.ctx.t2
    property vs:
        def __get__(self):
            return self.ctx.vs
    property vc:
        def __get__(self):
            return self.ctx.vc
    property ve:
        def __get__(self):
            return self.ctx.ve
    property q:
        def __get__(self):
            return self.ctx.q
    property t:
        def __get__(self):
            return self.ctx.t
