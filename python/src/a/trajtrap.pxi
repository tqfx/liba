from a.trajtrap cimport *

cdef class trajtrap:
    cdef a_trajtrap ctx
    def gen(self, a_float vm, a_float ac, a_float de, a_float p0, a_float p1, a_float v0 = 0, a_float v1 = 0):
        return a_trajtrap_gen(&self.ctx, vm, ac, de, p0, p1, v0, v1)
    def pos(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajtrap_pos(&self.ctx, p[i])
            return x
        return a_trajtrap_pos(&self.ctx, dt)
    def vel(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajtrap_vel(&self.ctx, p[i])
            return x
        return a_trajtrap_vel(&self.ctx, dt)
    def acc(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajtrap_acc(&self.ctx, p[i])
            return x
        return a_trajtrap_acc(&self.ctx, dt)
    property t:
        def __get__(self):
            return self.ctx.t
    property p0:
        def __get__(self):
            return self.ctx.p0
    property p1:
        def __get__(self):
            return self.ctx.p1
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
    property pa:
        def __get__(self):
            return self.ctx.pa
    property pd:
        def __get__(self):
            return self.ctx.pd
    property ac:
        def __get__(self):
            return self.ctx.ac
    property de:
        def __get__(self):
            return self.ctx.de
