from a cimport *
from a.pid_neuro cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid_neuro:
    '''single neuron proportional integral derivative controller'''
    cdef a_pid_neuro ctx
    def __init__(self):
        self.ctx.pid.summax = +A_FLOAT_INF
        self.ctx.pid.summin = -A_FLOAT_INF
        self.ctx.pid.outmax = +A_FLOAT_INF
        self.ctx.pid.outmin = -A_FLOAT_INF
        self.ctx.k = 1
        self.ctx.wp = 0.1
        self.ctx.wi = 0.1
        self.ctx.wd = 0.1
        a_pid_neuro_init(&self.ctx)
    def kpid(self, k: a_float, kp: a_float, ki: a_float, kd: a_float):
        '''set proportional integral derivative constant for single neuron PID controller'''
        a_pid_neuro_kpid(&self.ctx, k, kp, ki, kd)
        return self
    def wpid(self, wp: a_float, wi: a_float, wd: a_float):
        '''set proportional integral derivative weight for single neuron PID controller'''
        a_pid_neuro_wpid(&self.ctx, wp, wi, wd)
        return self
    def run(self, set: a_float, fdb: a_float) -> a_float:
        '''calculate for single neuron PID controller'''
        return a_pid_neuro_run(&self.ctx, set, fdb)
    def inc(self, set: a_float, fdb: a_float) -> a_float:
        '''calculate for incremental single neuron PID controller'''
        return a_pid_neuro_inc(&self.ctx, set, fdb)
    def zero(self):
        '''zeroing for single neuron PID controller'''
        a_pid_neuro_zero(&self.ctx)
        return self
    property k:
        def __get__(self) -> a_float:
            return self.ctx.k
        def __set__(self, k: a_float):
            self.ctx.k = k
    property kp:
        def __get__(self) -> a_float:
            return self.ctx.pid.kp
        def __set__(self, kp: a_float):
            self.ctx.pid.kp = kp
    property ki:
        def __get__(self) -> a_float:
            return self.ctx.pid.ki
        def __set__(self, ki: a_float):
            self.ctx.pid.ki = ki
    property kd:
        def __get__(self) -> a_float:
            return self.ctx.pid.kd
        def __set__(self, kd: a_float):
            self.ctx.pid.kd = kd
    property wp:
        def __get__(self) -> a_float:
            return self.ctx.wp
        def __set__(self, wp: a_float):
            self.ctx.wp = wp
    property wi:
        def __get__(self) -> a_float:
            return self.ctx.wi
        def __set__(self, wi: a_float):
            self.ctx.wi = wi
    property wd:
        def __get__(self) -> a_float:
            return self.ctx.wd
        def __set__(self, wd: a_float):
            self.ctx.wd = wd
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
            return self.ctx.pid.out
    property fdb:
        def __get__(self) -> a_float:
            return self.ctx.pid.fdb
    property err:
        def __get__(self) -> a_float:
            return self.ctx.pid.err
    property ec:
        def __get__(self) -> a_float:
            return self.ctx.ec
