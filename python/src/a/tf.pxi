from a.tf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class tf:
    '''transfer function'''
    cdef a_tf_s ctx
    cdef array _num
    cdef array _u
    cdef array _den
    cdef array _v
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
        cdef unsigned int m = <unsigned int>len(num)
        self._num = floats(num)
        self._u = floats(num)
        a_tf_set_num(&self.ctx, m, <a_float_t *>self._num.data.as_voidptr, <a_float_t *>self._u.data.as_voidptr)
    @property
    def den(self):
        return self._den
    @den.setter
    def den(self, den):
        cdef unsigned int n = <unsigned int>len(den)
        self._den = floats(den)
        self._v = floats(den)
        a_tf_set_den(&self.ctx, n, <a_float_t *>self._den.data.as_voidptr, <a_float_t *>self._v.data.as_voidptr)
