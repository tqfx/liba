from a cimport *
from fuzzy cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid_fuzzy:
    '''fuzzy proportional integral derivative controller'''
    AND_DEFAULT = A_PID_FUZZY_AND_DEFAULT
    AND_ALGEBRA = A_PID_FUZZY_AND_ALGEBRA
    AND_BOUNDED = A_PID_FUZZY_AND_BOUNDED
    OR_DEFAULT = A_PID_FUZZY_OR_DEFAULT
    OR_ALGEBRA = A_PID_FUZZY_OR_ALGEBRA
    OR_BOUNDED = A_PID_FUZZY_OR_BOUNDED
    EQU = A_PID_FUZZY_EQU
    AND = A_PID_FUZZY_AND
    OR = A_PID_FUZZY_OR
    cdef a_pid_fuzzy_s ctx
    cdef array me
    cdef array mec
    cdef array mkp
    cdef array mki
    cdef array mkd
    cdef void *ptr
    def __cinit__(self, a_float_t min = -A_FLOAT_INF, a_float_t max = +A_FLOAT_INF, a_float_t sum = 0):
        self.ctx.pid.summax = sum
        self.ctx.pid.outmax = max
        self.ctx.pid.outmin = min
        a_pid_fuzzy_init(&self.ctx, 0)
        if sum:
            self.ctx.pid.mode = A_PID_POS
        else:
            self.ctx.pid.mode = A_PID_INC
        a_pid_fuzzy_set_op(&self.ctx, A_PID_FUZZY_EQU)
    def rule(self, me, mec, mkp, mki, mkd):
        '''set rule base for fuzzy PID controller'''
        self.me = float.array((col for row in me for col in row))
        self.mec = float.array((col for row in mec for col in row))
        self.mkp = float.array((col for row in mkp for col in row))
        self.mki = float.array((col for row in mki for col in row))
        self.mkd = float.array((col for row in mkd for col in row))
        a_pid_fuzzy_rule(&self.ctx, <unsigned int>len(me),
                         <a_float_t *>self.me.data.as_voidptr,
                         <a_float_t *>self.mec.data.as_voidptr,
                         <a_float_t *>self.mkp.data.as_voidptr,
                         <a_float_t *>self.mki.data.as_voidptr,
                         <a_float_t *>self.mkd.data.as_voidptr)
        return self
    def kpid(self, kp: a_float_t, ki: a_float_t, kd: a_float_t):
        '''set proportional integral derivative constant for fuzzy PID controller'''
        a_pid_fuzzy_kpid(&self.ctx, kp, ki, kd)
        return self
    def buff(self, num: int):
        '''set buffer for fuzzy PID controller'''
        self.ptr = PyMem_Realloc(self.ptr, A_PID_FUZZY_BUF1(num))
        a_pid_fuzzy_buf1(&self.ctx, self.ptr, num)
        return self
    def op(self, op: int):
        '''set fuzzy relational operator for fuzzy PID controller'''
        a_pid_fuzzy_set_op(&self.ctx, op)
        return self
    def __call__(self, set: a_float_t, fdb: a_float_t) -> a_float_t:
        '''calculate function for fuzzy PID controller'''
        return a_pid_fuzzy_outf(&self.ctx, set, fdb)
    def __dealloc__(self):
        '''terminate function for fuzzy PID controller'''
        PyMem_Free(self.ptr)
    def zero(self):
        '''zero clear function for fuzzy PID controller'''
        a_pid_fuzzy_zero(&self.ctx)
        return self
    property kp:
        def __get__(self) -> a_float_t:
            return self.ctx.kp
        def __set__(self, kp: a_float_t):
            self.ctx.pid.kp = kp
            self.ctx.kp = kp
    property ki:
        def __get__(self) -> a_float_t:
            return self.ctx.ki
        def __set__(self, ki: a_float_t):
            self.ctx.pid.ki = ki
            self.ctx.ki = ki
    property kd:
        def __get__(self) -> a_float_t:
            return self.ctx.kd
        def __set__(self, kd: a_float_t):
            self.ctx.pid.kd = kd
            self.ctx.kd = kd
    property summax:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.summax
        def __set__(self, summax: a_float_t):
            self.ctx.pid.summax = summax
    property outmax:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.outmax
        def __set__(self, outmax: a_float_t):
            self.ctx.pid.outmax = outmax
    property outmin:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.outmin
        def __set__(self, outmin: a_float_t):
            self.ctx.pid.outmin = outmin
    property out:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.out.f
    property fdb:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.fdb.f
    property err:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.err.f
    property mode:
        def __get__(self) -> int:
            return self.ctx.pid.mode
        def __set__(self, mode: int):
            self.ctx.pid.mode = mode
    property col:
        def __get__(self) -> int:
            return self.ctx.col
    property buf:
        def __get__(self) -> int:
            return self.ctx.buf
