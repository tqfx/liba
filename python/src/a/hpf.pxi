from a.hpf cimport *

cdef class hpf:
    cdef a_hpf ctx
    def __init__(self, a_float fc, a_float ts):
        a_hpf_init(&self.ctx, a_hpf_gen(fc, ts))
    def gen(self, a_float fc, a_float ts):
        a_hpf_init(&self.ctx, a_hpf_gen(fc, ts))
        return self
    def __call__(self, a_float x):
        return a_hpf_iter(&self.ctx, x)
    def zero(self):
        a_hpf_zero(&self.ctx)
        return self
    property alpha:
        def __get__(self):
            return self.ctx.alpha
        def __set__(self, a_float alpha):
            self.ctx.alpha = alpha
    property output:
        def __get__(self):
            return self.ctx.output
    property input:
        def __get__(self):
            return self.ctx.input
