from a cimport *
from neuron cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid_neuron:
    '''single neuron proportional integral derivative controller'''
    cdef a_pid_neuron_s ctx
    def __cinit__(self, a_float_t min = -A_FLOAT_INF, a_float_t max = +A_FLOAT_INF, a_float_t sum = 0):
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
    @property
    def kp(self) -> a_float_t:
        return self.ctx.pid.kp
    @kp.setter
    def kp(self, kp: a_float_t):
        self.ctx.pid.kp = kp
    @property
    def ki(self) -> a_float_t:
        return self.ctx.pid.ki
    @ki.setter
    def ki(self, ki: a_float_t):
        self.ctx.pid.ki = ki
    @property
    def kd(self) -> a_float_t:
        return self.ctx.pid.kd
    @kd.setter
    def kd(self, kd: a_float_t):
        self.ctx.pid.kd = kd
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
    def ec(self) -> a_float_t:
        return self.ctx.ec.f
    @property
    def wp(self) -> a_float_t:
        return self.ctx.wp.f
    @wp.setter
    def wp(self, wp: a_float_t):
        self.ctx.wp.f = wp
    @property
    def wi(self) -> a_float_t:
        return self.ctx.wi.f
    @wi.setter
    def wi(self, wi: a_float_t):
        self.ctx.wi.f = wi
    @property
    def wd(self) -> a_float_t:
        return self.ctx.wd.f
    @wd.setter
    def wd(self, wd: a_float_t):
        self.ctx.wd.f = wd
    @property
    def k(self) -> a_float_t:
        return self.ctx.k
    @k.setter
    def k(self, k: a_float_t):
        self.ctx.k = k
