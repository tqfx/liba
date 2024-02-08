from a.lpf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
@cython.auto_pickle(False)
cdef class lpf:
    cdef a_lpf ctx
    def __init__(self, fc: a_float, ts: a_float):
        a_lpf_init(&self.ctx, a_lpf_gen(fc, ts))
    def gen(self, fc: a_float, ts: a_float):
        a_lpf_init(&self.ctx, a_lpf_gen(fc, ts))
        return self
    def __call__(self, x: a_float) -> a_float:
        return a_lpf_iter(&self.ctx, x)
    def zero(self):
        a_lpf_zero(&self.ctx)
        return self
    property alpha:
        def __get__(self) -> a_float:
            return self.ctx.alpha
        def __set__(self, alpha: a_float):
            self.ctx.alpha = alpha
    property output:
        def __get__(self) -> a_float:
            return self.ctx.output
