from a.tf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class tf:
    '''transfer function'''
    cdef a_tf ctx
    def __call__(self, x: a_float) -> a_float:
        '''calculate for transfer function'''
        return a_tf_iter(&self.ctx, x)
    def zero(self):
        '''zeroing for transfer function'''
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
            self._num = array_num(num)
            self.input = array_num(num)
            a_tf_set_num(&self.ctx, <unsigned int>len(num), <a_float *>self._num.data.as_voidptr, <a_float *>self.input.data.as_voidptr)
    cdef array output
    property output:
        def __get__(self):
            return self.output
    cdef array _den
    property den:
        def __get__(self):
            return self._den
        def __set__(self, den):
            self._den = array_num(den)
            self.output = array_num(den)
            a_tf_set_den(&self.ctx, <unsigned int>len(den), <a_float *>self._den.data.as_voidptr, <a_float *>self.output.data.as_voidptr)
    def __init__(self, num, den):
        tf.num.__set__(self, num)
        tf.den.__set__(self, den)
