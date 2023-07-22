from a.polytrack cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytrack3:
    '''cubic polynomial trajectory'''
    cdef a_polytrack3_s ctx
    def __init__(self, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0 = 0, a_float_t v1 = 0):
        a_polytrack3_gen(&self.ctx, t0, t1, q0, q1, v0, v1)
    def gen(self, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0 = 0, a_float_t v1 = 0):
        '''generation function'''
        a_polytrack3_gen(&self.ctx, t0, t1, q0, q1, v0, v1)
    def __call__(self, dt):
        '''calculate all'''
        cdef a_float_t out[3]
        if iterable(dt):
            p = float.array(dt)
            v = float.array(dt)
            a = float.array(dt)
            for i, it in enumerate(dt):
                a_polytrack3_out(&self.ctx, it, out)
                p[i] = out[0]
                v[i] = out[1]
                a[i] = out[2]
            return p, v, a
        a_polytrack3_out(&self.ctx, dt, out)
        return out[0], out[1], out[2]
    def pos(self, dt):
        '''calculate position'''
        if iterable(dt):
            out = float.array(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytrack3_pos(&self.ctx, it)
            return out
        return a_polytrack3_pos(&self.ctx, dt)
    def vel(self, dt):
        '''calculate velocity'''
        if iterable(dt):
            out = float.array(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytrack3_vel(&self.ctx, it)
            return out
        return a_polytrack3_vel(&self.ctx, dt)
    def acc(self, dt):
        '''calculate acceleration'''
        if iterable(dt):
            out = float.array(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytrack3_acc(&self.ctx, it)
            return out
        return a_polytrack3_acc(&self.ctx, dt)
    property k:
        def __get__(self):
            return self.ctx.k

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytrack5:
    '''quintic polynomial trajectory'''
    cdef a_polytrack5_s ctx
    def __init__(self, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0 = 0, a_float_t v1 = 0, a_float_t a0 = 0, a_float_t a1 = 0):
        a_polytrack5_gen(&self.ctx, t0, t1, q0, q1, v0, v1, a0, a1)
    def gen(self, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0 = 0, a_float_t v1 = 0, a_float_t a0 = 0, a_float_t a1 = 0):
        '''generation function'''
        a_polytrack5_gen(&self.ctx, t0, t1, q0, q1, v0, v1, a0, a1)
    def __call__(self, dt):
        '''calculate all'''
        cdef a_float_t out[3]
        if iterable(dt):
            p = float.array(dt)
            v = float.array(dt)
            a = float.array(dt)
            for i, it in enumerate(dt):
                a_polytrack5_out(&self.ctx, it, out)
                p[i] = out[0]
                v[i] = out[1]
                a[i] = out[2]
            return p, v, a
        a_polytrack5_out(&self.ctx, dt, out)
        return out[0], out[1], out[2]
    def pos(self, dt):
        '''calculate position'''
        if iterable(dt):
            out = float.array(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytrack5_pos(&self.ctx, it)
            return out
        return a_polytrack5_pos(&self.ctx, dt)
    def vel(self, dt):
        '''calculate velocity'''
        if iterable(dt):
            out = float.array(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytrack5_vel(&self.ctx, it)
            return out
        return a_polytrack5_vel(&self.ctx, dt)
    def acc(self, dt):
        '''calculate acceleration'''
        if iterable(dt):
            out = float.array(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytrack5_acc(&self.ctx, it)
            return out
        return a_polytrack5_acc(&self.ctx, dt)
    property k:
        def __get__(self):
            return self.ctx.k

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytrack7:
    '''hepta polynomial trajectory'''
    cdef a_polytrack7_s ctx
    def __init__(self, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0 = 0, a_float_t v1 = 0, a_float_t a0 = 0, a_float_t a1 = 0, a_float_t j0 = 0, a_float_t j1 = 0):
        a_polytrack7_gen(&self.ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1)
    def gen(self, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0 = 0, a_float_t v1 = 0, a_float_t a0 = 0, a_float_t a1 = 0, a_float_t j0 = 0, a_float_t j1 = 0):
        '''generation function'''
        a_polytrack7_gen(&self.ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1)
    def __call__(self, dt):
        '''calculate all'''
        cdef a_float_t out[4]
        if iterable(dt):
            p = float.array(dt)
            v = float.array(dt)
            a = float.array(dt)
            j = float.array(dt)
            for i, it in enumerate(dt):
                a_polytrack7_out(&self.ctx, it, out)
                p[i] = out[0]
                v[i] = out[1]
                a[i] = out[2]
                j[i] = out[3]
            return p, v, a, j
        a_polytrack7_out(&self.ctx, dt, out)
        return out[0], out[1], out[2], out[3]
    def pos(self, dt):
        '''calculate position'''
        if iterable(dt):
            out = float.array(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytrack7_pos(&self.ctx, it)
            return out
        return a_polytrack7_pos(&self.ctx, dt)
    def vel(self, dt):
        '''calculate velocity'''
        if iterable(dt):
            out = float.array(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytrack7_vel(&self.ctx, it)
            return out
        return a_polytrack7_vel(&self.ctx, dt)
    def acc(self, dt):
        '''calculate acceleration'''
        if iterable(dt):
            out = float.array(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytrack7_acc(&self.ctx, it)
            return out
        return a_polytrack7_acc(&self.ctx, dt)
    def jer(self, dt):
        '''calculate jerk'''
        if iterable(dt):
            out = float.array(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytrack7_jer(&self.ctx, it)
            return out
        return a_polytrack7_jer(&self.ctx, dt)
    property k:
        def __get__(self):
            return self.ctx.k
