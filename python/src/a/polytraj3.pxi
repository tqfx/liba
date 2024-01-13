from a.polytraj3 cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytraj3:
    '''cubic polynomial trajectory'''
    cdef a_polytraj3 ctx
    def __init__(self, a_float t0, a_float t1, a_float q0, a_float q1, a_float v0 = 0, a_float v1 = 0):
        a_polytraj3_gen(&self.ctx, t0, t1, q0, q1, v0, v1)
    def gen(self, a_float t0, a_float t1, a_float q0, a_float q1, a_float v0 = 0, a_float v1 = 0):
        '''generation function'''
        a_polytraj3_gen(&self.ctx, t0, t1, q0, q1, v0, v1)
        return self
    def pos(self, dt):
        '''calculate position'''
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytraj3_pos(&self.ctx, it)
            return out
        return a_polytraj3_pos(&self.ctx, dt)
    def vel(self, dt):
        '''calculate velocity'''
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytraj3_vel(&self.ctx, it)
            return out
        return a_polytraj3_vel(&self.ctx, dt)
    def acc(self, dt):
        '''calculate acceleration'''
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytraj3_acc(&self.ctx, it)
            return out
        return a_polytraj3_acc(&self.ctx, dt)
    property q:
        def __get__(self):
            return self.ctx.q
    property v:
        def __get__(self):
            return self.ctx.v
    property a:
        def __get__(self):
            return self.ctx.a
