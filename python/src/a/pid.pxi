from a.pid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid:
    '''proportional integral derivative controller'''
    OFF = A_PID_OFF
    POS = A_PID_POS
    INC = A_PID_INC
    cdef a_pid_s ctx
    def __init__(self):
        self.ctx.kp = 1
        self.ctx.summax = +A_FLOAT_INF
        self.ctx.summin = -A_FLOAT_INF
        self.ctx.outmax = +A_FLOAT_INF
        self.ctx.outmin = -A_FLOAT_INF
        a_pid_init(&self.ctx)
    def kpid(self, kp: a_float_t, ki: a_float_t, kd: a_float_t):
        '''set proportional integral derivative constant for PID controller'''
        a_pid_kpid(&self.ctx, kp, ki, kd)
        return self
    def off(self, set: a_float_t, fdb: a_float_t) -> a_float_t:
        '''calculate for PID controller'''
        return a_pid_off(&self.ctx, set, fdb)
    def pos(self, set: a_float_t, fdb: a_float_t) -> a_float_t:
        '''calculate for positional PID controller'''
        return a_pid_pos(&self.ctx, set, fdb)
    def inc(self, set: a_float_t, fdb: a_float_t) -> a_float_t:
        '''calculate for incremental PID controller'''
        return a_pid_inc(&self.ctx, set, fdb)
    def zero(self):
        '''zeroing for PID controller'''
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
    property summin:
        def __get__(self) -> a_float_t:
            return self.ctx.summin
        def __set__(self, summin: a_float_t):
            self.ctx.summin = summin
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
            return self.ctx.out
    property fdb:
        def __get__(self) -> a_float_t:
            return self.ctx.fdb
    property err:
        def __get__(self) -> a_float_t:
            return self.ctx.err

include "pid/fuzzy.pxi"
include "pid/neuron.pxi"
