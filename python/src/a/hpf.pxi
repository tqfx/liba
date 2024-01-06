from a.hpf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class hpf:
    '''High Pass Filter'''
    cdef a_hpf_s ctx
    def __init__(self, fc: a_float_t, ts: a_float_t):
        '''initialize for High Pass Filter'''
        a_hpf_init(&self.ctx, a_hpf_gen(fc, ts))
    def gen(self, fc: a_float_t, ts: a_float_t):
        '''generate for High Pass Filter'''
        a_hpf_init(&self.ctx, a_hpf_gen(fc, ts))
        return self
    def __call__(self, x: a_float_t) -> a_float_t:
        '''calculate for High Pass Filter'''
        return a_hpf_iter(&self.ctx, x)
    def zero(self):
        '''zeroing for High Pass Filter'''
        a_hpf_zero(&self.ctx)
        return self
    property alpha:
        def __get__(self) -> a_float_t:
            return self.ctx.alpha
        def __set__(self, alpha: a_float_t):
            self.ctx.alpha = alpha
    property output:
        def __get__(self) -> a_float_t:
            return self.ctx.output
    property input:
        def __get__(self) -> a_float_t:
            return self.ctx.input
