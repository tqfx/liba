from a.trajtrap cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
@cython.auto_pickle(False)
cdef class trajtrap:
    cdef a_trajtrap ctx
    def gen(self, a_float vm, a_float ac, a_float de, a_float q0, a_float q1, a_float v0 = 0, a_float v1 = 0):
        return a_trajtrap_gen(&self.ctx, vm, ac, de, q0, q1, v0, v1)
    cdef inline pos_n(self, array dt):
        cdef Py_ssize_t i
        cdef Py_ssize_t n = len(dt)
        cdef a_float *p = <a_float *>dt.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_trajtrap_pos(&self.ctx, p[i])
        return dt
    def pos(self, dt):
        if iterable(dt):
            return self.pos_n(array_num(dt))
        return a_trajtrap_pos(&self.ctx, dt)
    cdef inline vel_n(self, array dt):
        cdef Py_ssize_t i
        cdef Py_ssize_t n = len(dt)
        cdef a_float *p = <a_float *>dt.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_trajtrap_vel(&self.ctx, p[i])
        return dt
    def vel(self, dt):
        if iterable(dt):
            return self.vel_n(array_num(dt))
        return a_trajtrap_vel(&self.ctx, dt)
    cdef inline acc_n(self, array dt):
        cdef Py_ssize_t i
        cdef Py_ssize_t n = len(dt)
        cdef a_float *p = <a_float *>dt.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_trajtrap_acc(&self.ctx, p[i])
        return dt
    def acc(self, dt):
        if iterable(dt):
            return self.acc_n(array_num(dt))
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
