from a.lpf cimport *

cdef class lpf:
    cdef a_lpf ctx
    def __init__(self, a_float fc, a_float ts):
        a_lpf_init(&self.ctx, a_lpf_gen(fc, ts))
    def gen(self, a_float fc, a_float ts):
        a_lpf_init(&self.ctx, a_lpf_gen(fc, ts))
        return self
    def __call__(self, a_float x):
        return a_lpf_iter(&self.ctx, x)
    def zero(self):
        a_lpf_zero(&self.ctx)
        return self
    property alpha:
        def __get__(self):
            return self.ctx.alpha
        def __set__(self, a_float alpha):
            self.ctx.alpha = alpha
    property output:
        def __get__(self):
            return self.ctx.output
