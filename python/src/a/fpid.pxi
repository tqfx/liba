from a cimport *
from a.fpid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class fpid:
    '''fuzzy proportional integral derivative controller'''
    cdef a_fpid_s ctx
    cdef void *ptr
    cdef array me
    cdef array mec
    cdef array mkp
    cdef array mki
    cdef array mkd
    def __cinit__(self, unsigned int num, a_float_t dt, me, mec, mkp, mki, mkd, a_float_t min, a_float_t max, a_float_t sum = 0):
        self.me = floats((i for j in me for i in j))
        self.mec = floats((i for j in mec for i in j))
        self.mkp = floats((i for j in mkp for i in j))
        self.mki = floats((i for j in mki for i in j))
        self.mkd = floats((i for j in mkd for i in j))
        cdef a_float_t *e = <a_float_t *>self.me.data.as_voidptr
        cdef a_float_t *ec = <a_float_t *>self.mec.data.as_voidptr
        cdef a_float_t *kp = <a_float_t *>self.mkp.data.as_voidptr
        cdef a_float_t *ki = <a_float_t *>self.mki.data.as_voidptr
        cdef a_float_t *kd = <a_float_t *>self.mkd.data.as_voidptr
        a_fpid_init(&self.ctx, dt, <unsigned int>len(mkp), e, ec, kp, ki, kd, min, max)
        if sum:
            a_fpid_pos(&self.ctx, sum)
        else:
            a_fpid_inc(&self.ctx)
        self.buf = num
    def __call__(self, set: a_float_t, fdb: a_float_t) -> a_float_t:
        '''calculate function for fuzzy PID controller'''
        return a_fpid_outf(&self.ctx, set, fdb)
    def __dealloc__(self):
        '''terminate function for fuzzy PID controller'''
        a_fpid_exit(&self.ctx)
        PyMem_Free(self.ptr)
    def zero(self):
        '''zero function for fuzzy PID controller'''
        a_fpid_zero(&self.ctx)
        return self
    def base(self, me, mec, mkp, mki, mkd):
        '''set rule base for fuzzy PID controller'''
        self.me = floats((i for j in me for i in j))
        self.mec = floats((i for j in mec for i in j))
        self.mkp = floats((i for j in mkp for i in j))
        self.mki = floats((i for j in mki for i in j))
        self.mkd = floats((i for j in mkd for i in j))
        cdef a_float_t *e = <a_float_t *>self.me.data.as_voidptr
        cdef a_float_t *ec = <a_float_t *>self.mec.data.as_voidptr
        cdef a_float_t *kp = <a_float_t *>self.mkp.data.as_voidptr
        cdef a_float_t *ki = <a_float_t *>self.mki.data.as_voidptr
        cdef a_float_t *kd = <a_float_t *>self.mkd.data.as_voidptr
        a_fpid_base(&self.ctx, <unsigned int>len(mkp), e, ec, kp, ki, kd)
        return self
    def kpid(self, kp: a_float_t, ki: a_float_t, kd: a_float_t):
        '''set proportional integral derivative constant for fuzzy PID controller'''
        a_fpid_kpid(&self.ctx, kp, ki, kd)
        return self
    def pos(self, max: a_float_t):
        '''positional fuzzy PID controller'''
        a_fpid_pos(&self.ctx, max)
        return self
    def inc(self):
        '''incremental fuzzy PID controller'''
        a_fpid_inc(&self.ctx)
        return self
    def off(self):
        '''turn off fuzzy PID controller'''
        a_fpid_off(&self.ctx)
        return self

    @property
    def outmin(self) -> a_float_t:
        return self.ctx.pid.outmin
    @outmin.setter
    def outmin(self, outmin: a_float_t):
        self.ctx.pid.outmin = outmin

    @property
    def outmax(self) -> a_float_t:
        return self.ctx.pid.outmax
    @outmax.setter
    def outmax(self, outmax: a_float_t):
        self.ctx.pid.outmax = outmax

    @property
    def summax(self) -> a_float_t:
        return self.ctx.pid.summax
    @summax.setter
    def summax(self, summax: a_float_t):
        self.ctx.pid.summax = summax

    @property
    def mode(self) -> int:
        return a_pid_mode(&self.ctx.pid)
    @mode.setter
    def mode(self, mode: int):
        a_pid_set_mode(&self.ctx.pid, mode)

    @property
    def dt(self) -> a_float_t:
        return a_pid_dt(&self.ctx.pid)
    @dt.setter
    def dt(self, dt: a_float_t):
        a_pid_set_dt(&self.ctx.pid, dt)

    @property
    def kp(self) -> a_float_t:
        return self.ctx.kp
    @kp.setter
    def kp(self, kp: a_float_t):
        self.ctx.kp = kp

    @property
    def ki(self) -> a_float_t:
        return self.ctx.ki
    @ki.setter
    def ki(self, ki: a_float_t):
        self.ctx.ki = ki

    @property
    def kd(self) -> a_float_t:
        return self.ctx.kd
    @kd.setter
    def kd(self, kd: a_float_t):
        self.ctx.kd = kd

    @property
    def buf(self) -> int:
        return a_fpid_bufnum(&self.ctx)
    @buf.setter
    def buf(self, max: int):
        self.ptr = PyMem_Realloc(self.ptr, A_FPID_BUF1(max))
        a_fpid_buf1(&self.ctx, self.ptr, max)

    @property
    def col(self) -> int:
        return a_fpid_col(&self.ctx)
    @property
    def out(self) -> a_float_t:
        return self.ctx.pid.out.f
    @property
    def fdb(self) -> a_float_t:
        return self.ctx.pid.fdb.f
    @property
    def ec(self) -> a_float_t:
        return self.ctx.pid.ec.f
    @property
    def e(self) -> a_float_t:
        return self.ctx.pid.e.f
