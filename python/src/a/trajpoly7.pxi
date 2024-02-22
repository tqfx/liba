from a.trajpoly7 cimport *

cdef class trajpoly7:
    cdef a_trajpoly7 ctx
    def __init__(self, a_float ts, a_float p0, a_float p1, a_float v0 = 0, a_float v1 = 0, a_float a0 = 0, a_float a1 = 0, a_float j0 = 0, a_float j1 = 0):
        a_trajpoly7_gen(&self.ctx, ts, p0, p1, v0, v1, a0, a1, j0, j1)
    def gen(self, a_float ts, a_float p0, a_float p1, a_float v0 = 0, a_float v1 = 0, a_float a0 = 0, a_float a1 = 0, a_float j0 = 0, a_float j1 = 0):
        a_trajpoly7_gen(&self.ctx, ts, p0, p1, v0, v1, a0, a1, j0, j1)
        return self
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
                p[i] = a_trajpoly7_pos(&self.ctx, p[i])
            return x
        return a_trajpoly7_pos(&self.ctx, dt)
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
                p[i] = a_trajpoly7_vel(&self.ctx, p[i])
            return x
        return a_trajpoly7_vel(&self.ctx, dt)
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
                p[i] = a_trajpoly7_acc(&self.ctx, p[i])
            return x
        return a_trajpoly7_acc(&self.ctx, dt)
    def jer(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajpoly7_jer(&self.ctx, p[i])
            return x
        return a_trajpoly7_jer(&self.ctx, dt)
    property p:
        def __get__(self):
            return self.ctx.p
    property v:
        def __get__(self):
            return self.ctx.v
    property a:
        def __get__(self):
            return self.ctx.a
    property j:
        def __get__(self):
            return self.ctx.j
