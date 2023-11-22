from a cimport *
from neuron cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid_neuron:
    '''single neuron proportional integral derivative controller'''
    cdef a_pid_neuron_s ctx
    def __init__(self):
        self.ctx.pid.summax = +A_FLOAT_INF
        self.ctx.pid.summin = -A_FLOAT_INF
        self.ctx.pid.outmax = +A_FLOAT_INF
        self.ctx.pid.outmin = -A_FLOAT_INF
        self.ctx.k = 1
        self.ctx.wp = 0.1
        self.ctx.wi = 0.1
        self.ctx.wd = 0.1
        a_pid_neuron_init(&self.ctx)
    def kpid(self, k: a_float_t, kp: a_float_t, ki: a_float_t, kd: a_float_t):
        '''set proportional integral derivative constant for single neuron PID controller'''
        a_pid_neuron_kpid(&self.ctx, k, kp, ki, kd)
        return self
    def wpid(self, wp: a_float_t, wi: a_float_t, wd: a_float_t):
        '''set proportional integral derivative weight for single neuron PID controller'''
        a_pid_neuron_wpid(&self.ctx, wp, wi, wd)
        return self
    def off(self, set: a_float_t, fdb: a_float_t) -> a_float_t:
        '''calculate for single neuron PID controller'''
        return a_pid_neuron_off(&self.ctx, set, fdb)
    def inc(self, set: a_float_t, fdb: a_float_t) -> a_float_t:
        '''calculate for incremental single neuron PID controller'''
        return a_pid_neuron_inc(&self.ctx, set, fdb)
    def zero(self):
        '''zeroing for single neuron PID controller'''
        a_pid_neuron_zero(&self.ctx)
        return self
    property k:
        def __get__(self) -> a_float_t:
            return self.ctx.k
        def __set__(self, k: a_float_t):
            self.ctx.k = k
    property kp:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.kp
        def __set__(self, kp: a_float_t):
            self.ctx.pid.kp = kp
    property ki:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.ki
        def __set__(self, ki: a_float_t):
            self.ctx.pid.ki = ki
    property kd:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.kd
        def __set__(self, kd: a_float_t):
            self.ctx.pid.kd = kd
    property wp:
        def __get__(self) -> a_float_t:
            return self.ctx.wp
        def __set__(self, wp: a_float_t):
            self.ctx.wp = wp
    property wi:
        def __get__(self) -> a_float_t:
            return self.ctx.wi
        def __set__(self, wi: a_float_t):
            self.ctx.wi = wi
    property wd:
        def __get__(self) -> a_float_t:
            return self.ctx.wd
        def __set__(self, wd: a_float_t):
            self.ctx.wd = wd
    property summax:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.summax
        def __set__(self, summax: a_float_t):
            self.ctx.pid.summax = summax
    property summin:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.summin
        def __set__(self, summin: a_float_t):
            self.ctx.pid.summin = summin
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
            return self.ctx.pid.out
    property fdb:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.fdb
    property err:
        def __get__(self) -> a_float_t:
            return self.ctx.pid.err
    property ec:
        def __get__(self) -> a_float_t:
            return self.ctx.ec
