from a.trajpoly3 cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
@cython.auto_pickle(False)
cdef class trajpoly3:
    cdef a_trajpoly3 ctx
    def __init__(self, a_float ts, a_float q0, a_float q1, a_float v0 = 0, a_float v1 = 0):
        a_trajpoly3_gen(&self.ctx, ts, q0, q1, v0, v1)
    def gen(self, a_float ts, a_float q0, a_float q1, a_float v0 = 0, a_float v1 = 0):
        a_trajpoly3_gen(&self.ctx, ts, q0, q1, v0, v1)
        return self
    def pos(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajpoly3_pos(&self.ctx, it)
            return out
        return a_trajpoly3_pos(&self.ctx, dt)
    def vel(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajpoly3_vel(&self.ctx, it)
            return out
        return a_trajpoly3_vel(&self.ctx, dt)
    def acc(self, dt):
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_trajpoly3_acc(&self.ctx, it)
            return out
        return a_trajpoly3_acc(&self.ctx, dt)
    property q:
        def __get__(self):
            return self.ctx.q
    property v:
        def __get__(self):
            return self.ctx.v
    property a:
        def __get__(self):
            return self.ctx.a
