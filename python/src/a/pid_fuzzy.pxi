from a cimport *
from a.pid_fuzzy cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid_fuzzy:
    '''fuzzy proportional integral derivative controller'''
    CAP = A_PID_FUZZY_CAP
    CAP_ALGEBRA = A_PID_FUZZY_CAP_ALGEBRA
    CAP_BOUNDED = A_PID_FUZZY_CAP_BOUNDED
    CUP = A_PID_FUZZY_CUP
    CUP_ALGEBRA = A_PID_FUZZY_CUP_ALGEBRA
    CUP_BOUNDED = A_PID_FUZZY_CUP_BOUNDED
    EQU = A_PID_FUZZY_EQU
    cdef a_pid_fuzzy ctx
    cdef array me
    cdef array mec
    cdef array mkp
    cdef array mki
    cdef array mkd
    def __init__(self):
        self.ctx.pid.summax = +A_FLOAT_INF
        self.ctx.pid.summin = -A_FLOAT_INF
        self.ctx.pid.outmax = +A_FLOAT_INF
        self.ctx.pid.outmin = -A_FLOAT_INF
        self.ctx.kp = 1
        a_pid_fuzzy_set_op(&self.ctx, A_PID_FUZZY_EQU)
        a_pid_fuzzy_init(&self.ctx)
    def op(self, op: int):
        '''set fuzzy relational operator for fuzzy PID controller'''
        a_pid_fuzzy_set_op(&self.ctx, op)
        return self
    def rule(self, me, mec, mkp, mki, mkd):
        '''set rule base for fuzzy PID controller'''
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
    def set_joint(self, num: int):
        '''set joint buffer for fuzzy PID controller'''
        cdef void *ptr = a_pid_fuzzy_joint(&self.ctx);
        ptr = PyMem_Realloc(ptr, A_PID_FUZZY_JOINT(num))
        a_pid_fuzzy_set_joint(&self.ctx, ptr, num)
        return self
    def kpid(self, kp: a_float, ki: a_float, kd: a_float):
        '''set proportional integral derivative constant for fuzzy PID controller'''
        a_pid_fuzzy_kpid(&self.ctx, kp, ki, kd)
        return self
    def run(self, set: a_float, fdb: a_float) -> a_float:
        '''calculate for fuzzy PID controller'''
        return a_pid_fuzzy_run(&self.ctx, set, fdb)
    def pos(self, set: a_float, fdb: a_float) -> a_float:
        '''calculate for positional fuzzy PID controller'''
        return a_pid_fuzzy_pos(&self.ctx, set, fdb)
    def inc(self, set: a_float, fdb: a_float) -> a_float:
        '''calculate for incremental fuzzy PID controller'''
        return a_pid_fuzzy_inc(&self.ctx, set, fdb)
    def __dealloc__(self):
        '''terminate for fuzzy PID controller'''
        PyMem_Free(a_pid_fuzzy_joint(&self.ctx))
    def zero(self):
        '''zeroing for fuzzy PID controller'''
        a_pid_fuzzy_zero(&self.ctx)
        return self
    property joint:
        def __get__(self) -> int:
            return self.ctx.joint
        def __set__(self, joint: int):
            self.set_joint(joint)
    property kp:
        def __get__(self) -> a_float:
            return self.ctx.kp
        def __set__(self, kp: a_float):
            self.ctx.pid.kp = kp
            self.ctx.kp = kp
    property ki:
        def __get__(self) -> a_float:
            return self.ctx.ki
        def __set__(self, ki: a_float):
            self.ctx.pid.ki = ki
            self.ctx.ki = ki
    property kd:
        def __get__(self) -> a_float:
            return self.ctx.kd
        def __set__(self, kd: a_float):
            self.ctx.pid.kd = kd
            self.ctx.kd = kd
    property summax:
        def __get__(self) -> a_float:
            return self.ctx.pid.summax
        def __set__(self, summax: a_float):
            self.ctx.pid.summax = summax
    property summin:
        def __get__(self) -> a_float:
            return self.ctx.pid.summin
        def __set__(self, summin: a_float):
            self.ctx.pid.summin = summin
    property outmax:
        def __get__(self) -> a_float:
            return self.ctx.pid.outmax
        def __set__(self, outmax: a_float):
            self.ctx.pid.outmax = outmax
    property outmin:
        def __get__(self) -> a_float:
            return self.ctx.pid.outmin
        def __set__(self, outmin: a_float):
            self.ctx.pid.outmin = outmin
    property out:
        def __get__(self) -> a_float:
            return self.ctx.pid.out.f
    property fdb:
        def __get__(self) -> a_float:
            return self.ctx.pid.fdb.f
    property err:
        def __get__(self) -> a_float:
            return self.ctx.pid.err.f
    property order:
        def __get__(self) -> int:
            return self.ctx.order
