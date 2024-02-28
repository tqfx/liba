from a cimport *
from a.pid_neuro cimport *

cdef class pid_neuro:
    cdef a_pid_neuro ctx
    def __init__(self):
        self.ctx.pid.summax = +A_FLOAT_INF
        self.ctx.pid.summin = -A_FLOAT_INF
        self.ctx.pid.outmax = +A_FLOAT_INF
        self.ctx.pid.outmin = -A_FLOAT_INF
        self.ctx.k = self.ctx.pid.kp = 1
        self.ctx.wp = 0.1
        self.ctx.wi = 0.1
        self.ctx.wd = 0.1
        a_pid_neuro_init(&self.ctx)
    def kpid(self, a_float k, a_float kp, a_float ki, a_float kd):
        a_pid_neuro_kpid(&self.ctx, k, kp, ki, kd)
        return self
    def wpid(self, a_float wp, a_float wi, a_float wd):
        a_pid_neuro_wpid(&self.ctx, wp, wi, wd)
        return self
    def run(self, a_float set, a_float fdb):
        return a_pid_neuro_run(&self.ctx, set, fdb)
    def inc(self, a_float set, a_float fdb):
        return a_pid_neuro_inc(&self.ctx, set, fdb)
    def zero(self):
        a_pid_neuro_zero(&self.ctx)
        return self
    property k:
        def __get__(self):
            return self.ctx.k
        def __set__(self, a_float k):
            self.ctx.k = k
    property kp:
        def __get__(self):
            return self.ctx.pid.kp
        def __set__(self, a_float kp):
            self.ctx.pid.kp = kp
    property ki:
        def __get__(self):
            return self.ctx.pid.ki
        def __set__(self, a_float ki):
            self.ctx.pid.ki = ki
    property kd:
        def __get__(self):
            return self.ctx.pid.kd
        def __set__(self, a_float kd):
            self.ctx.pid.kd = kd
    property wp:
        def __get__(self):
            return self.ctx.wp
        def __set__(self, a_float wp):
            self.ctx.wp = wp
    property wi:
        def __get__(self):
            return self.ctx.wi
        def __set__(self, a_float wi):
            self.ctx.wi = wi
    property wd:
        def __get__(self):
            return self.ctx.wd
        def __set__(self, a_float wd):
            self.ctx.wd = wd
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
    property ec:
        def __get__(self):
            return self.ctx.ec
