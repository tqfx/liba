from a.pid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid:
    '''proportional integral derivative controller'''
    RUN = A_PID_RUN
    POS = A_PID_POS
    INC = A_PID_INC
    cdef a_pid ctx
    def __init__(self):
        self.ctx.kp = 1
        self.ctx.summax = +A_FLOAT_INF
        self.ctx.summin = -A_FLOAT_INF
        self.ctx.outmax = +A_FLOAT_INF
        self.ctx.outmin = -A_FLOAT_INF
        a_pid_init(&self.ctx)
    def kpid(self, kp: a_float, ki: a_float, kd: a_float):
        '''set proportional integral derivative constant for PID controller'''
        a_pid_kpid(&self.ctx, kp, ki, kd)
        return self
    def run(self, set: a_float, fdb: a_float) -> a_float:
        '''calculate for PID controller'''
        return a_pid_run(&self.ctx, set, fdb)
    def pos(self, set: a_float, fdb: a_float) -> a_float:
        '''calculate for positional PID controller'''
        return a_pid_pos(&self.ctx, set, fdb)
    def inc(self, set: a_float, fdb: a_float) -> a_float:
        '''calculate for incremental PID controller'''
        return a_pid_inc(&self.ctx, set, fdb)
    def zero(self):
        '''zeroing for PID controller'''
        a_pid_zero(&self.ctx)
        return self
    property kp:
        def __get__(self) -> a_float:
            return self.ctx.kp
        def __set__(self, kp: a_float):
            self.ctx.kp = kp
    property ki:
        def __get__(self) -> a_float:
            return self.ctx.ki
        def __set__(self, ki: a_float):
            self.ctx.ki = ki
    property kd:
        def __get__(self) -> a_float:
            return self.ctx.kd
        def __set__(self, kd: a_float):
            self.ctx.kd = kd
    property summax:
        def __get__(self) -> a_float:
            return self.ctx.summax
        def __set__(self, summax: a_float):
            self.ctx.summax = summax
    property summin:
        def __get__(self) -> a_float:
            return self.ctx.summin
        def __set__(self, summin: a_float):
            self.ctx.summin = summin
    property outmax:
        def __get__(self) -> a_float:
            return self.ctx.outmax
        def __set__(self, outmax: a_float):
            self.ctx.outmax = outmax
    property outmin:
        def __get__(self) -> a_float:
            return self.ctx.outmin
        def __set__(self, outmin: a_float):
            self.ctx.outmin = outmin
    property out:
        def __get__(self) -> a_float:
            return self.ctx.out
    property fdb:
        def __get__(self) -> a_float:
            return self.ctx.fdb
    property err:
        def __get__(self) -> a_float:
            return self.ctx.err
