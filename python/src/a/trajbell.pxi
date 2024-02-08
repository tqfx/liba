from a.trajbell cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
@cython.auto_pickle(False)
cdef class trajbell:
    cdef a_trajbell ctx
    def gen(self, a_float jm, a_float am, a_float vm, a_float q0, a_float q1, a_float v0 = 0, a_float v1 = 0):
        return a_trajbell_gen(&self.ctx, jm, am, vm, q0, q1, v0, v1)
    def pos(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajbell_pos(&self.ctx, it)
            return out
        return a_trajbell_pos(&self.ctx, dt)
    def vel(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajbell_vel(&self.ctx, it)
            return out
        return a_trajbell_vel(&self.ctx, dt)
    def acc(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajbell_acc(&self.ctx, it)
            return out
        return a_trajbell_acc(&self.ctx, dt)
    def jer(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajbell_jer(&self.ctx, it)
            return out
        return a_trajbell_jer(&self.ctx, dt)
    property t:
        def __get__(self):
            return self.ctx.t
    property tv:
        def __get__(self):
            return self.ctx.tv
    property ta:
        def __get__(self):
            return self.ctx.ta
    property td:
        def __get__(self):
            return self.ctx.td
    property taj:
        def __get__(self):
            return self.ctx.taj
    property tdj:
        def __get__(self):
            return self.ctx.tdj
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
    property vm:
        def __get__(self):
            return self.ctx.vm
    property jm:
        def __get__(self):
            return self.ctx.jm
    property am:
        def __get__(self):
            return self.ctx.am
    property dm:
        def __get__(self):
            return self.ctx.dm
