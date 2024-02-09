from a.trajpoly7 cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
@cython.auto_pickle(False)
cdef class trajpoly7:
    cdef a_trajpoly7 ctx
    def __init__(self, a_float ts, a_float q0, a_float q1, a_float v0 = 0, a_float v1 = 0, a_float a0 = 0, a_float a1 = 0, a_float j0 = 0, a_float j1 = 0):
        a_trajpoly7_gen(&self.ctx, ts, q0, q1, v0, v1, a0, a1, j0, j1)
    def gen(self, a_float ts, a_float q0, a_float q1, a_float v0 = 0, a_float v1 = 0, a_float a0 = 0, a_float a1 = 0, a_float j0 = 0, a_float j1 = 0):
        a_trajpoly7_gen(&self.ctx, ts, q0, q1, v0, v1, a0, a1, j0, j1)
        return self
    cdef inline pos_n(self, array dt):
        cdef Py_ssize_t i
        cdef Py_ssize_t n = len(dt)
        cdef a_float *p = <a_float *>dt.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_trajpoly7_pos(&self.ctx, p[i])
        return dt
    def pos(self, dt):
        if iterable(dt):
            return self.pos_n(array_num(dt))
        return a_trajpoly7_pos(&self.ctx, dt)
    cdef inline vel_n(self, array dt):
        cdef Py_ssize_t i
        cdef Py_ssize_t n = len(dt)
        cdef a_float *p = <a_float *>dt.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_trajpoly7_vel(&self.ctx, p[i])
        return dt
    def vel(self, dt):
        if iterable(dt):
            return self.vel_n(array_num(dt))
        return a_trajpoly7_vel(&self.ctx, dt)
    cdef inline acc_n(self, array dt):
        cdef Py_ssize_t i
        cdef Py_ssize_t n = len(dt)
        cdef a_float *p = <a_float *>dt.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_trajpoly7_acc(&self.ctx, p[i])
        return dt
    def acc(self, dt):
        if iterable(dt):
            return self.acc_n(array_num(dt))
        return a_trajpoly7_acc(&self.ctx, dt)
    cdef inline jer_n(self, array dt):
        cdef Py_ssize_t i
        cdef Py_ssize_t n = len(dt)
        cdef a_float *p = <a_float *>dt.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_trajpoly7_jer(&self.ctx, p[i])
        return dt
    def jer(self, dt):
        if iterable(dt):
            return self.jer_n(array_num(dt))
        return a_trajpoly7_jer(&self.ctx, dt)
    property q:
        def __get__(self):
            return self.ctx.q
    property v:
        def __get__(self):
            return self.ctx.v
    property a:
        def __get__(self):
            return self.ctx.a
    property j:
        def __get__(self):
            return self.ctx.j
