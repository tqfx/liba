from a.pid cimport *

cdef class pid:
    cdef a_pid ctx
    def __init__(self):
        self.ctx.kp = 1
        self.ctx.summax = +A_FLOAT_INF
        self.ctx.summin = -A_FLOAT_INF
        self.ctx.outmax = +A_FLOAT_INF
        self.ctx.outmin = -A_FLOAT_INF
        a_pid_init(&self.ctx)
    def kpid(self, a_float kp, a_float ki, a_float kd):
        a_pid_kpid(&self.ctx, kp, ki, kd)
        return self
    def run(self, a_float set, a_float fdb):
        return a_pid_run(&self.ctx, set, fdb)
    def pos(self, a_float set, a_float fdb):
        return a_pid_pos(&self.ctx, set, fdb)
    def inc(self, a_float set, a_float fdb):
        return a_pid_inc(&self.ctx, set, fdb)
    def zero(self):
        a_pid_zero(&self.ctx)
        return self
    property kp:
        def __get__(self):
            return self.ctx.kp
        def __set__(self, a_float kp):
            self.ctx.kp = kp
    property ki:
        def __get__(self):
            return self.ctx.ki
        def __set__(self, a_float ki):
            self.ctx.ki = ki
    property kd:
        def __get__(self):
            return self.ctx.kd
        def __set__(self, a_float kd):
            self.ctx.kd = kd
    property summax:
        def __get__(self):
            return self.ctx.summax
        def __set__(self, a_float summax):
            self.ctx.summax = summax
    property summin:
        def __get__(self):
            return self.ctx.summin
        def __set__(self, a_float summin):
            self.ctx.summin = summin
    property sum:
        def __get__(self):
            return self.ctx.sum
    property outmax:
        def __get__(self):
            return self.ctx.outmax
        def __set__(self, a_float outmax):
            self.ctx.outmax = outmax
    property outmin:
        def __get__(self):
            return self.ctx.outmin
        def __set__(self, a_float outmin):
            self.ctx.outmin = outmin
    property out:
        def __get__(self):
            return self.ctx.out
    property fdb:
        def __get__(self):
            return self.ctx.fdb
    property err:
        def __get__(self):
            return self.ctx.err
