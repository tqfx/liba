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
    property input:
        def __get__(self):
            return self.input
    cdef array _num
    property num:
        def __get__(self):
            return self._num
        def __set__(self, num):
            self._num = float.array(num)
            self.input = float.array(num)
            a_tf_set_num(&self.ctx, <unsigned int>len(num), <a_float_t *>self._num.data.as_voidptr, <a_float_t *>self.input.data.as_voidptr)
    cdef array output
    property output:
        def __get__(self):
            return self.output
    cdef array _den
    property den:
        def __get__(self):
            return self._den
        def __set__(self, den):
            self._den = float.array(den)
            self.output = float.array(den)
            a_tf_set_den(&self.ctx, <unsigned int>len(den), <a_float_t *>self._den.data.as_voidptr, <a_float_t *>self.output.data.as_voidptr)
    def __init__(self, num, den):
        tf.num.__set__(self, num)
        tf.den.__set__(self, den)
