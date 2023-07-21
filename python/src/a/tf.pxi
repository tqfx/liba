from a.tf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class tf:
    '''transfer function'''
    cdef a_tf_s ctx
    def __call__(self, x: a_float_t) -> a_float_t:
        '''calculate function for transfer function'''
        return a_tf_iter(&self.ctx, x)
    def zero(self):
        '''zero clear function for transfer function'''
        a_tf_zero(&self.ctx)
        return self
    cdef array input
    @property
    def input(self):
        return self.input
    cdef array _num
    @property
    def num(self):
        return self._num
    @num.setter
    def num(self, num):
        self._num = float.array(num)
        self.input = float.array(num)
        a_tf_set_num(&self.ctx, <unsigned int>len(num), <a_float_t *>self._num.data.as_voidptr, <a_float_t *>self.input.data.as_voidptr)
    cdef array output
    @property
    def output(self):
        return self.output
    cdef array _den
    @property
    def den(self):
        return self._den
    @den.setter
    def den(self, den):
        self._den = float.array(den)
        self.output = float.array(den)
        a_tf_set_den(&self.ctx, <unsigned int>len(den), <a_float_t *>self._den.data.as_voidptr, <a_float_t *>self.output.data.as_voidptr)
    def __cinit__(self, num, den):
        self.num = num
        self.den = den
