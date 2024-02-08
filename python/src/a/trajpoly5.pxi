from a.trajpoly5 cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
@cython.auto_pickle(False)
cdef class trajpoly5:
    cdef a_trajpoly5 ctx
    def __init__(self, a_float ts, a_float q0, a_float q1, a_float v0 = 0, a_float v1 = 0, a_float a0 = 0, a_float a1 = 0):
        a_trajpoly5_gen(&self.ctx, ts, q0, q1, v0, v1, a0, a1)
    def gen(self, a_float ts, a_float q0, a_float q1, a_float v0 = 0, a_float v1 = 0, a_float a0 = 0, a_float a1 = 0):
        a_trajpoly5_gen(&self.ctx, ts, q0, q1, v0, v1, a0, a1)
        return self
    def pos(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajpoly5_pos(&self.ctx, it)
            return out
        return a_trajpoly5_pos(&self.ctx, dt)
    def vel(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajpoly5_vel(&self.ctx, it)
            return out
        return a_trajpoly5_vel(&self.ctx, dt)
    def acc(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajpoly5_acc(&self.ctx, it)
            return out
        return a_trajpoly5_acc(&self.ctx, dt)
    property q:
        def __get__(self):
            return self.ctx.q
    property v:
        def __get__(self):
            return self.ctx.v
    property a:
        def __get__(self):
            return self.ctx.a
