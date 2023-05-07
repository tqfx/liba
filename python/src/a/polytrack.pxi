from a.polytrack cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytrack3:
    '''cubic polynomial trajectory'''
    cdef a_polytrack3_s ctx
    def __cinit__(self, a_real_t t0, a_real_t t1, a_real_t q0, a_real_t q1, a_real_t v0 = 0, a_real_t v1 = 0):
        a_polytrack3_init(&self.ctx, t0, t1, q0, q1, v0, v1)
    def __call__(self, ts):
        '''calculate all'''
        cdef a_real_t out[3]
        if iterable(ts):
            p = reals(ts)
            v = reals(ts)
            a = reals(ts)
            for i, it in enumerate(ts):
                a_polytrack3_out(&self.ctx, it, out)
                p[i] = out[0]
                v[i] = out[1]
                a[i] = out[2]
            return p, v, a
        a_polytrack3_out(&self.ctx, ts, out)
        return out[0], out[1], out[2]
    def pos(self, ts):
        '''calculate position'''
        if iterable(ts):
            out = reals(ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack3_pos(&self.ctx, it)
            return out
        return a_polytrack3_pos(&self.ctx, ts)
    def vec(self, ts):
        '''calculate velocity'''
        if iterable(ts):
            out = reals(ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack3_vec(&self.ctx, it)
            return out
        return a_polytrack3_vec(&self.ctx, ts)
    def acc(self, ts):
        '''calculate acceleration'''
        if iterable(ts):
            out = reals(ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack3_acc(&self.ctx, it)
            return out
        return a_polytrack3_acc(&self.ctx, ts)
    def gen(self):
        '''generation function'''
        a_polytrack3_gen(&self.ctx)

    @property
    def k(self):
        return self.ctx.k

    @property
    def t(self):
        return self.ctx.t
    @t.setter
    def t(self, val):
        self.ctx.t[0] = val[0]
        self.ctx.t[1] = val[1]

    @property
    def q(self):
        return self.ctx.q
    @q.setter
    def q(self, val):
        self.ctx.q[0] = val[0]
        self.ctx.q[1] = val[1]

    @property
    def v(self):
        return self.ctx.v
    @v.setter
    def v(self, val):
        self.ctx.v[0] = val[0]
        self.ctx.v[1] = val[1]

    @property
    def t0(self) -> a_real_t:
        return self.ctx.t[0]
    @t0.setter
    def t0(self, val: a_real_t):
        self.ctx.t[0] = val

    @property
    def q0(self) -> a_real_t:
        return self.ctx.q[0]
    @q0.setter
    def q0(self, val: a_real_t):
        self.ctx.q[0] = val

    @property
    def v0(self) -> a_real_t:
        return self.ctx.v[0]
    @v0.setter
    def v0(self, val: a_real_t):
        self.ctx.v[0] = val

    @property
    def t1(self) -> a_real_t:
        return self.ctx.t[1]
    @t1.setter
    def t1(self, val: a_real_t):
        self.ctx.t[1] = val

    @property
    def q1(self) -> a_real_t:
        return self.ctx.q[1]
    @q1.setter
    def q1(self, val: a_real_t):
        self.ctx.q[1] = val

    @property
    def v1(self) -> a_real_t:
        return self.ctx.v[1]
    @v1.setter
    def v1(self, val: a_real_t):
        self.ctx.v[1] = val

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytrack5:
    '''quintic polynomial trajectory'''
    cdef a_polytrack5_s ctx
    def __cinit__(self, a_real_t t0, a_real_t t1, a_real_t q0, a_real_t q1, a_real_t v0 = 0, a_real_t v1 = 0, a_real_t a0 = 0, a_real_t a1 = 0):
        a_polytrack5_init(&self.ctx, t0, t1, q0, q1, v0, v1, a0, a1)
    def __call__(self, ts):
        '''calculate all'''
        cdef a_real_t out[3]
        if iterable(ts):
            p = reals(ts)
            v = reals(ts)
            a = reals(ts)
            for i, it in enumerate(ts):
                a_polytrack5_out(&self.ctx, it, out)
                p[i] = out[0]
                v[i] = out[1]
                a[i] = out[2]
            return p, v, a
        a_polytrack5_out(&self.ctx, ts, out)
        return out[0], out[1], out[2]
    def pos(self, ts):
        '''calculate position'''
        if iterable(ts):
            out = reals(ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack5_pos(&self.ctx, it)
            return out
        return a_polytrack5_pos(&self.ctx, ts)
    def vec(self, ts):
        '''calculate velocity'''
        if iterable(ts):
            out = reals(ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack5_vec(&self.ctx, it)
            return out
        return a_polytrack5_vec(&self.ctx, ts)
    def acc(self, ts):
        '''calculate acceleration'''
        if iterable(ts):
            out = reals(ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack5_acc(&self.ctx, it)
            return out
        return a_polytrack5_acc(&self.ctx, ts)
    def gen(self):
        '''generation function'''
        a_polytrack5_gen(&self.ctx)

    @property
    def k(self):
        return self.ctx.k

    @property
    def t(self):
        return self.ctx.t
    @t.setter
    def t(self, val):
        self.ctx.t[0] = val[0]
        self.ctx.t[1] = val[1]

    @property
    def q(self):
        return self.ctx.q
    @q.setter
    def q(self, val):
        self.ctx.q[0] = val[0]
        self.ctx.q[1] = val[1]

    @property
    def v(self):
        return self.ctx.v
    @v.setter
    def v(self, val):
        self.ctx.v[0] = val[0]
        self.ctx.v[1] = val[1]

    @property
    def a(self):
        return self.ctx.a
    @a.setter
    def a(self, val):
        self.ctx.a[0] = val[0]
        self.ctx.a[1] = val[1]

    @property
    def t0(self) -> a_real_t:
        return self.ctx.t[0]
    @t0.setter
    def t0(self, val: a_real_t):
        self.ctx.t[0] = val

    @property
    def q0(self) -> a_real_t:
        return self.ctx.q[0]
    @q0.setter
    def q0(self, val: a_real_t):
        self.ctx.q[0] = val

    @property
    def v0(self) -> a_real_t:
        return self.ctx.v[0]
    @v0.setter
    def v0(self, val: a_real_t):
        self.ctx.v[0] = val

    @property
    def a0(self) -> a_real_t:
        return self.ctx.a[0]
    @a0.setter
    def a0(self, val: a_real_t):
        self.ctx.a[0] = val

    @property
    def t1(self) -> a_real_t:
        return self.ctx.t[1]
    @t1.setter
    def t1(self, val: a_real_t):
        self.ctx.t[1] = val

    @property
    def q1(self) -> a_real_t:
        return self.ctx.q[1]
    @q1.setter
    def q1(self, val: a_real_t):
        self.ctx.q[1] = val

    @property
    def v1(self) -> a_real_t:
        return self.ctx.v[1]
    @v1.setter
    def v1(self, val: a_real_t):
        self.ctx.v[1] = val

    @property
    def a1(self) -> a_real_t:
        return self.ctx.a[1]
    @a1.setter
    def a1(self, val: a_real_t):
        self.ctx.a[1] = val

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytrack7:
    '''hepta polynomial trajectory'''
    cdef a_polytrack7_s ctx
    def __cinit__(self, a_real_t t0, a_real_t t1, a_real_t q0, a_real_t q1, a_real_t v0 = 0, a_real_t v1 = 0, a_real_t a0 = 0, a_real_t a1 = 0, a_real_t j0 = 0, a_real_t j1 = 0):
        a_polytrack7_init(&self.ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1)
    def __call__(self, ts):
        '''calculate all'''
        cdef a_real_t out[4]
        if iterable(ts):
            p = reals(ts)
            v = reals(ts)
            a = reals(ts)
            j = reals(ts)
            for i, it in enumerate(ts):
                a_polytrack7_out(&self.ctx, it, out)
                p[i] = out[0]
                v[i] = out[1]
                a[i] = out[2]
                j[i] = out[3]
            return p, v, a, j
        a_polytrack7_out(&self.ctx, ts, out)
        return out[0], out[1], out[2], out[3]
    def pos(self, ts):
        '''calculate position'''
        if iterable(ts):
            out = reals(ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack7_pos(&self.ctx, it)
            return out
        return a_polytrack7_pos(&self.ctx, ts)
    def vec(self, ts):
        '''calculate velocity'''
        if iterable(ts):
            out = reals(ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack7_vec(&self.ctx, it)
            return out
        return a_polytrack7_vec(&self.ctx, ts)
    def acc(self, ts):
        '''calculate acceleration'''
        if iterable(ts):
            out = reals(ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack7_acc(&self.ctx, it)
            return out
        return a_polytrack7_acc(&self.ctx, ts)
    def jer(self, ts):
        '''calculate jerk'''
        if iterable(ts):
            out = reals(ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack7_jer(&self.ctx, it)
            return out
        return a_polytrack7_jer(&self.ctx, ts)
    def gen(self):
        '''generation function'''
        a_polytrack7_gen(&self.ctx)

    @property
    def k(self):
        return self.ctx.k

    @property
    def t(self):
        return self.ctx.t
    @t.setter
    def t(self, val):
        self.ctx.t[0] = val[0]
        self.ctx.t[1] = val[1]

    @property
    def q(self):
        return self.ctx.q
    @q.setter
    def q(self, val):
        self.ctx.q[0] = val[0]
        self.ctx.q[1] = val[1]

    @property
    def v(self):
        return self.ctx.v
    @v.setter
    def v(self, val):
        self.ctx.v[0] = val[0]
        self.ctx.v[1] = val[1]

    @property
    def a(self):
        return self.ctx.a
    @a.setter
    def a(self, val):
        self.ctx.a[0] = val[0]
        self.ctx.a[1] = val[1]

    @property
    def j(self):
        return self.ctx.j
    @j.setter
    def j(self, val):
        self.ctx.j[0] = val[0]
        self.ctx.j[1] = val[1]

    @property
    def t0(self) -> a_real_t:
        return self.ctx.t[0]
    @t0.setter
    def t0(self, val: a_real_t):
        self.ctx.t[0] = val

    @property
    def q0(self) -> a_real_t:
        return self.ctx.q[0]
    @q0.setter
    def q0(self, val: a_real_t):
        self.ctx.q[0] = val

    @property
    def v0(self) -> a_real_t:
        return self.ctx.v[0]
    @v0.setter
    def v0(self, val: a_real_t):
        self.ctx.v[0] = val

    @property
    def a0(self) -> a_real_t:
        return self.ctx.a[0]
    @a0.setter
    def a0(self, val: a_real_t):
        self.ctx.a[0] = val

    @property
    def j0(self) -> a_real_t:
        return self.ctx.j[0]
    @j0.setter
    def j0(self, val: a_real_t):
        self.ctx.j[0] = val

    @property
    def t1(self) -> a_real_t:
        return self.ctx.t[1]
    @t1.setter
    def t1(self, val: a_real_t):
        self.ctx.t[1] = val

    @property
    def q1(self) -> a_real_t:
        return self.ctx.q[1]
    @q1.setter
    def q1(self, val: a_real_t):
        self.ctx.q[1] = val

    @property
    def v1(self) -> a_real_t:
        return self.ctx.v[1]
    @v1.setter
    def v1(self, val: a_real_t):
        self.ctx.v[1] = val

    @property
    def a1(self) -> a_real_t:
        return self.ctx.a[1]
    @a1.setter
    def a1(self, val: a_real_t):
        self.ctx.a[1] = val

    @property
    def j1(self) -> a_real_t:
        return self.ctx.j[1]
    @j1.setter
    def j1(self, val: a_real_t):
        self.ctx.j[1] = val
