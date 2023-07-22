from a cimport *
from neuron cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid_neuron:
    '''single neuron proportional integral derivative controller'''
    cdef a_pid_neuron_s ctx
    def __init__(self, a_float_t min = -A_FLOAT_INF, a_float_t max = +A_FLOAT_INF, a_float_t sum = 0):
        self.ctx.pid.summax = sum
        self.ctx.pid.outmax = max
        self.ctx.pid.outmin = min
        a_pid_neuron_init(&self.ctx, 0)
        if sum:
            self.ctx.pid.mode = A_PID_POS
        else:
            self.ctx.pid.mode = A_PID_INC
    def kpid(self, k: a_float_t, kp: a_float_t, ki: a_float_t, kd: a_float_t):
        '''set proportional integral derivative constant for single neuron PID controller'''
        a_pid_neuron_kpid(&self.ctx, k, kp, ki, kd)
        return self
    def wpid(self, wp: a_float_t, wi: a_float_t, wd: a_float_t):
        '''set proportional integral derivative weight for single neuron PID controller'''
        a_pid_neuron_wpid(&self.ctx, wp, wi, wd)
        return self
    def __call__(self, set: a_float_t, fdb: a_float_t) -> a_float_t:
        '''calculate function for single neuron PID controller'''
        return a_pid_neuron_outf(&self.ctx, set, fdb)
    def zero(self):
        '''zero clear function for single neuron PID controller'''
        a_pid_neuron_zero(&self.ctx)
        return self
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
    property ec:
        def __get__(self) -> a_float_t:
            return self.ctx.ec.f
    property wp:
        def __get__(self) -> a_float_t:
            return self.ctx.wp.f
        def __set__(self, wp: a_float_t):
            self.ctx.wp.f = wp
    property wi:
        def __get__(self) -> a_float_t:
            return self.ctx.wi.f
        def __set__(self, wi: a_float_t):
            self.ctx.wi.f = wi
    property wd:
        def __get__(self) -> a_float_t:
            return self.ctx.wd.f
        def __set__(self, wd: a_float_t):
            self.ctx.wd.f = wd
    property k:
        def __get__(self) -> a_float_t:
            return self.ctx.k
        def __set__(self, k: a_float_t):
            self.ctx.k = k
