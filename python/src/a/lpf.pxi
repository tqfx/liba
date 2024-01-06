from a.lpf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class lpf:
    '''Low Pass Filter'''
    cdef a_lpf_s ctx
    def __init__(self, fc: a_float_t, ts: a_float_t):
        '''initialize for Low Pass Filter'''
        a_lpf_init(&self.ctx, a_lpf_gen(fc, ts))
    def gen(self, fc: a_float_t, ts: a_float_t):
        '''generate for Low Pass Filter'''
        a_lpf_init(&self.ctx, a_lpf_gen(fc, ts))
        return self
    def __call__(self, x: a_float_t) -> a_float_t:
        '''calculate for Low Pass Filter'''
        return a_lpf_iter(&self.ctx, x)
    def zero(self):
        '''zeroing for Low Pass Filter'''
        a_lpf_zero(&self.ctx)
        return self
    property alpha:
        def __get__(self) -> a_float_t:
            return self.ctx.alpha
        def __set__(self, alpha: a_float_t):
            self.ctx.alpha = alpha
    property output:
        def __get__(self) -> a_float_t:
            return self.ctx.output
