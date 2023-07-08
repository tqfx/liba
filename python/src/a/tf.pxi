from a.tf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class tf:
    '''transfer function'''
    cdef a_tf_s ctx
    cdef array _num
    cdef array _den
    cdef array _input
    cdef array _output
    def __cinit__(self, num, den):
        self.num = num
        self.den = den
    def __call__(self, x: a_float_t) -> a_float_t:
        '''calculate function for transfer function'''
        return a_tf_iter(&self.ctx, x)
    def zero(self):
        '''zero clear function for transfer function'''
        a_tf_zero(&self.ctx)
        return self
    @property
    def num(self):
        return self._num
    @num.setter
    def num(self, num):
        self._num = floats(num)
        self._input = floats(num)
        cdef unsigned int n = <unsigned int>len(num)
        a_tf_set_num(&self.ctx, n, <a_float_t *>self._num.data.as_voidptr, <a_float_t *>self._input.data.as_voidptr)
    @property
    def input(self):
        return self._input
    @property
    def den(self):
        return self._den
    @den.setter
    def den(self, den):
        self._den = floats(den)
        self._output = floats(den)
        cdef unsigned int n = <unsigned int>len(den)
        a_tf_set_den(&self.ctx, n, <a_float_t *>self._den.data.as_voidptr, <a_float_t *>self._output.data.as_voidptr)
    @property
    def output(self):
        return self._output
