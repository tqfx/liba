from a cimport *
from a.pid_fuzzy cimport *

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
        self.me = floats((col for row in me for col in row))
        self.mec = floats((col for row in mec for col in row))
        self.mkp = floats((col for row in mkp for col in row))
        self.mki = floats((col for row in mki for col in row))
        self.mkd = floats((col for row in mkd for col in row))
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
    @property
    def kp(self) -> a_float_t:
        return self.ctx.kp
    @kp.setter
    def kp(self, kp: a_float_t):
        self.ctx.pid.kp = kp
        self.ctx.kp = kp
    @property
    def ki(self) -> a_float_t:
        return self.ctx.ki
    @ki.setter
    def ki(self, ki: a_float_t):
        self.ctx.pid.ki = ki
        self.ctx.ki = ki
    @property
    def kd(self) -> a_float_t:
        return self.ctx.kd
    @kd.setter
    def kd(self, kd: a_float_t):
        self.ctx.pid.kd = kd
        self.ctx.kd = kd
    @property
    def summax(self) -> a_float_t:
        return self.ctx.pid.summax
    @summax.setter
    def summax(self, summax: a_float_t):
        self.ctx.pid.summax = summax
    @property
    def outmax(self) -> a_float_t:
        return self.ctx.pid.outmax
    @outmax.setter
    def outmax(self, outmax: a_float_t):
        self.ctx.pid.outmax = outmax
    @property
    def outmin(self) -> a_float_t:
        return self.ctx.pid.outmin
    @outmin.setter
    def outmin(self, outmin: a_float_t):
        self.ctx.pid.outmin = outmin
    @property
    def out(self) -> a_float_t:
        return self.ctx.pid.out.f
    @property
    def fdb(self) -> a_float_t:
        return self.ctx.pid.fdb.f
    @property
    def err(self) -> a_float_t:
        return self.ctx.pid.err.f
    @property
    def mode(self) -> int:
        return self.ctx.pid.mode
    @mode.setter
    def mode(self, mode: int):
        self.ctx.pid.mode = mode
    @property
    def col(self) -> int:
        return self.ctx.col
    @property
    def buf(self) -> int:
        return self.ctx.buf
