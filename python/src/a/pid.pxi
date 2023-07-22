from a.pid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid:
    '''proportional integral derivative controller'''
    OFF = A_PID_OFF
    POS = A_PID_POS
    INC = A_PID_INC
    cdef a_pid_s ctx
    def __init__(self, a_float_t min = -A_FLOAT_INF, a_float_t max = +A_FLOAT_INF, a_float_t sum = 0):
        self.ctx.summax = sum
        self.ctx.outmax = max
        self.ctx.outmin = min
        a_pid_init(&self.ctx, 0)
        if sum:
            self.ctx.mode = A_PID_POS
        else:
            self.ctx.mode = A_PID_INC
    def kpid(self, kp: a_float_t, ki: a_float_t, kd: a_float_t):
        '''set proportional integral derivative constant for PID controller'''
        a_pid_kpid(&self.ctx, kp, ki, kd)
        return self
    def __call__(self, set: a_float_t, fdb: a_float_t) -> a_float_t:
        '''calculate function for PID controller'''
        return a_pid_outf(&self.ctx, set, fdb)
    def zero(self):
        '''zero clear function for PID controller'''
        a_pid_zero(&self.ctx)
        return self
    property kp:
        def __get__(self) -> a_float_t:
            return self.ctx.kp
        def __set__(self, kp: a_float_t):
            self.ctx.kp = kp
    property ki:
        def __get__(self) -> a_float_t:
            return self.ctx.ki
        def __set__(self, ki: a_float_t):
            self.ctx.ki = ki
    property kd:
        def __get__(self) -> a_float_t:
            return self.ctx.kd
        def __set__(self, kd: a_float_t):
            self.ctx.kd = kd
    property summax:
        def __get__(self) -> a_float_t:
            return self.ctx.summax
        def __set__(self, summax: a_float_t):
            self.ctx.summax = summax
    property outmax:
        def __get__(self) -> a_float_t:
            return self.ctx.outmax
        def __set__(self, outmax: a_float_t):
            self.ctx.outmax = outmax
    property outmin:
        def __get__(self) -> a_float_t:
            return self.ctx.outmin
        def __set__(self, outmin: a_float_t):
            self.ctx.outmin = outmin
    property out:
        def __get__(self) -> a_float_t:
            return self.ctx.out.f
    property fdb:
        def __get__(self) -> a_float_t:
            return self.ctx.fdb.f
    property err:
        def __get__(self) -> a_float_t:
            return self.ctx.err.f
    property mode:
        def __get__(self) -> int:
            return self.ctx.mode
        def __set__(self, mode: int):
            self.ctx.mode = mode

include "pid/fuzzy.pxi"
include "pid/neuron.pxi"
