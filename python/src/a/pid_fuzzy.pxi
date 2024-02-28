from a cimport *
from a.pid_fuzzy cimport *

cdef class pid_fuzzy:
    CAP = A_PID_FUZZY_CAP
    CAP_ALGEBRA = A_PID_FUZZY_CAP_ALGEBRA
    CAP_BOUNDED = A_PID_FUZZY_CAP_BOUNDED
    CUP = A_PID_FUZZY_CUP
    CUP_ALGEBRA = A_PID_FUZZY_CUP_ALGEBRA
    CUP_BOUNDED = A_PID_FUZZY_CUP_BOUNDED
    EQU = A_PID_FUZZY_EQU
    cdef a_pid_fuzzy ctx
    cdef readonly array me
    cdef readonly array mec
    cdef readonly array mkp
    cdef readonly array mki
    cdef readonly array mkd
    def __init__(self):
        self.ctx.pid.summax = +A_FLOAT_INF
        self.ctx.pid.summin = -A_FLOAT_INF
        self.ctx.pid.outmax = +A_FLOAT_INF
        self.ctx.pid.outmin = -A_FLOAT_INF
        self.ctx.kp = self.ctx.pid.kp = 1
        self.ctx.op = a_fuzzy_equ
        a_pid_fuzzy_init(&self.ctx)
    def op(self, unsigned int op):
        a_pid_fuzzy_set_op(&self.ctx, op)
        return self
    def rule(self, me, mec, mkp, mki, mkd):
        self.me = array_num((_2 for _1 in me for _2 in _1))
        self.mec = array_num((_2 for _1 in mec for _2 in _1))
        self.mkp = array_num((_2 for _1 in mkp for _2 in _1))
        self.mki = array_num((_2 for _1 in mki for _2 in _1))
        self.mkd = array_num((_2 for _1 in mkd for _2 in _1))
        a_pid_fuzzy_rule(&self.ctx, <unsigned int>len(me),
                         <a_float *>self.me.data.as_voidptr,
                         <a_float *>self.mec.data.as_voidptr,
                         <a_float *>self.mkp.data.as_voidptr,
                         <a_float *>self.mki.data.as_voidptr,
                         <a_float *>self.mkd.data.as_voidptr)
        return self
    def set_block(self, unsigned int num):
        cdef void *ptr = a_pid_fuzzy_block(&self.ctx)
        ptr = PyMem_Realloc(ptr, A_PID_FUZZY_BLOCK(num))
        a_pid_fuzzy_set_block(&self.ctx, ptr, num)
        return self
    def kpid(self, a_float kp, a_float ki, a_float kd):
        a_pid_fuzzy_kpid(&self.ctx, kp, ki, kd)
        return self
    def run(self, a_float set, a_float fdb):
        return a_pid_fuzzy_run(&self.ctx, set, fdb)
    def pos(self, a_float set, a_float fdb):
        return a_pid_fuzzy_pos(&self.ctx, set, fdb)
    def inc(self, a_float set, a_float fdb):
        return a_pid_fuzzy_inc(&self.ctx, set, fdb)
    def __dealloc__(self):
        PyMem_Free(a_pid_fuzzy_block(&self.ctx))
    def zero(self):
        a_pid_fuzzy_zero(&self.ctx)
        return self
    property kp:
        def __get__(self):
            return self.ctx.kp
        def __set__(self, a_float kp):
            self.ctx.pid.kp = kp
            self.ctx.kp = kp
    property ki:
        def __get__(self):
            return self.ctx.ki
        def __set__(self, a_float ki):
            self.ctx.pid.ki = ki
            self.ctx.ki = ki
    property kd:
        def __get__(self):
            return self.ctx.kd
        def __set__(self, a_float kd):
            self.ctx.pid.kd = kd
            self.ctx.kd = kd
    property summax:
        def __get__(self):
            return self.ctx.pid.summax
        def __set__(self, a_float summax):
            self.ctx.pid.summax = summax
    property summin:
        def __get__(self):
            return self.ctx.pid.summin
        def __set__(self, a_float summin):
            self.ctx.pid.summin = summin
    property sum:
        def __get__(self):
            return self.ctx.pid.sum
    property outmax:
        def __get__(self):
            return self.ctx.pid.outmax
        def __set__(self, a_float outmax):
            self.ctx.pid.outmax = outmax
    property outmin:
        def __get__(self):
            return self.ctx.pid.outmin
        def __set__(self, a_float outmin):
            self.ctx.pid.outmin = outmin
    property out:
        def __get__(self):
            return self.ctx.pid.out
    property fdb:
        def __get__(self):
            return self.ctx.pid.fdb
    property err:
        def __get__(self):
            return self.ctx.pid.err
    property order:
        def __get__(self):
            return self.ctx.order
    property block:
        def __get__(self):
            return self.ctx.block
        def __set__(self, unsigned int block):
            self.set_block(block)
