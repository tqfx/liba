from a.pid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid:
    '''proportional integral derivative controller'''
    OFF = A_PID_OFF
    POS = A_PID_POS
    INC = A_PID_INC
    cdef a_pid_s ctx
    def __cinit__(self, a_real_t dt, a_real_t min, a_real_t max, a_real_t sum = 0):
        a_pid_init(&self.ctx, dt, min, max)
        if sum:
            a_pid_pos(&self.ctx, sum)
        else:
            a_pid_inc(&self.ctx)
    def __call__(self, set: a_real_t, fdb: a_real_t) -> a_real_t:
        '''calculate function for PID controller'''
        return a_pid_outf(&self.ctx, set, fdb)
    def __dealloc__(self):
        '''terminate function for PID controller'''
        a_pid_exit(&self.ctx)
    def zero(self):
        '''zero function for PID controller'''
        a_pid_zero(&self.ctx)
        return self
    def kpid(self, kp: a_real_t, ki: a_real_t, kd: a_real_t):
        '''set proportional integral derivative constant for PID controller'''
        a_pid_kpid(&self.ctx, kp, ki, kd)
        return self
    def pos(self, max: a_real_t):
        '''positional PID controller'''
        a_pid_pos(&self.ctx, max)
        return self
    def inc(self):
        '''incremental PID controller'''
        a_pid_inc(&self.ctx)
        return self
    def off(self):
        '''turn off PID controller'''
        a_pid_off(&self.ctx)
        return self

    @property
    def outmin(self) -> a_real_t:
        return self.ctx.outmin
    @outmin.setter
    def outmin(self, outmin: a_real_t):
        self.ctx.outmin = outmin

    @property
    def outmax(self) -> a_real_t:
        return self.ctx.outmax
    @outmax.setter
    def outmax(self, outmax: a_real_t):
        self.ctx.outmax = outmax

    @property
    def summax(self) -> a_real_t:
        return self.ctx.summax
    @summax.setter
    def summax(self, summax: a_real_t):
        self.ctx.summax = summax

    @property
    def mode(self) -> a_uint_t:
        return a_pid_mode(&self.ctx)
    @mode.setter
    def mode(self, mode: a_uint_t):
        a_pid_set_mode(&self.ctx, mode)

    @property
    def dt(self) -> a_real_t:
        return a_pid_dt(&self.ctx)
    @dt.setter
    def dt(self, dt: a_real_t):
        a_pid_set_dt(&self.ctx, dt)

    @property
    def kp(self) -> a_real_t:
        return a_pid_kp(&self.ctx)
    @kp.setter
    def kp(self, kp: a_real_t):
        a_pid_set_kp(&self.ctx, kp)

    @property
    def ki(self) -> a_real_t:
        return a_pid_ki(&self.ctx)
    @ki.setter
    def ki(self, ki: a_real_t):
        a_pid_set_ki(&self.ctx, ki)

    @property
    def kd(self) -> a_real_t:
        return a_pid_kd(&self.ctx)
    @kd.setter
    def kd(self, kd: a_real_t):
        a_pid_set_kd(&self.ctx, kd)

    @property
    def out(self) -> a_real_t:
        return self.ctx.out.f
    @property
    def fdb(self) -> a_real_t:
        return self.ctx.fdb.f
    @property
    def ec(self) -> a_real_t:
        return self.ctx.ec.f
    @property
    def e(self) -> a_real_t:
        return self.ctx.e.f
