from a.tf cimport *

cdef class tf:
    cdef a_tf ctx
    def __init__(self, num, den):
        tf.num.__set__(self, num)
        tf.den.__set__(self, den)
    def __call__(self, a_float x):
        return a_tf_iter(&self.ctx, x)
    def zero(self):
        a_tf_zero(&self.ctx)
        return self
    cdef array _num
    cdef readonly array input
    property num:
        def __get__(self):
            return self._num
        def __set__(self, num):
            self._num = array_num(num)
            self.input = array_num(num)
            a_tf_set_num(&self.ctx, <unsigned int>len(num), <a_float *>self._num.data.as_voidptr, <a_float *>self.input.data.as_voidptr)
    cdef array _den
    cdef readonly array output
    property den:
        def __get__(self):
            return self._den
        def __set__(self, den):
            self._den = array_num(den)
            self.output = array_num(den)
            a_tf_set_den(&self.ctx, <unsigned int>len(den), <a_float *>self._den.data.as_voidptr, <a_float *>self.output.data.as_voidptr)
