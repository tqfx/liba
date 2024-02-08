from a.trajtrap cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
@cython.auto_pickle(False)
cdef class trajtrap:
    cdef a_trajtrap ctx
    def gen(self, a_float vm, a_float ac, a_float de, a_float q0, a_float q1, a_float v0 = 0, a_float v1 = 0):
        return a_trajtrap_gen(&self.ctx, vm, ac, de, q0, q1, v0, v1)
    def pos(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajtrap_pos(&self.ctx, it)
            return out
        return a_trajtrap_pos(&self.ctx, dt)
    def vel(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajtrap_vel(&self.ctx, it)
            return out
        return a_trajtrap_vel(&self.ctx, dt)
    def acc(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajtrap_acc(&self.ctx, it)
            return out
        return a_trajtrap_acc(&self.ctx, dt)
    property t:
        def __get__(self):
            return self.ctx.t
    property q0:
        def __get__(self):
            return self.ctx.q0
    property q1:
        def __get__(self):
            return self.ctx.q1
    property v0:
        def __get__(self):
            return self.ctx.v0
    property v1:
        def __get__(self):
            return self.ctx.v1
    property vc:
        def __get__(self):
            return self.ctx.vc
    property ta:
        def __get__(self):
            return self.ctx.ta
    property td:
        def __get__(self):
            return self.ctx.td
    property qa:
        def __get__(self):
            return self.ctx.qa
    property qd:
        def __get__(self):
            return self.ctx.qd
    property ac:
        def __get__(self):
            return self.ctx.ac
    property de:
        def __get__(self):
            return self.ctx.de
