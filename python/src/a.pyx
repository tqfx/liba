cimport cython
from a cimport *
from a.math cimport *
from cpython cimport *
from cpython.array cimport array

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class i8:
    cdef a_i8_t value
    property value:
        def __get__(self) -> a_i8_t:
            return self.value
        def __set__(self, value: a_i8_t):
            self.value = value
    def __init__(self, value: a_i8_t = 0):
        self.value = value
    def __repr__(self):
        return str(self.value)
    @staticmethod
    def array(object o = ()):
        return array('b', o)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class u8:
    cdef a_u8_t value
    property value:
        def __get__(self) -> a_u8_t:
            return self.value
        def __set__(self, value: a_u8_t):
            self.value = value
    def __init__(self, value: a_u8_t = 0):
        self.value = value
    def __repr__(self):
        return str(self.value)
    @staticmethod
    def array(object o = ()):
        return array('B', o)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class i16:
    cdef a_i16_t value
    property value:
        def __get__(self) -> a_i16_t:
            return self.value
        def __set__(self, value: a_i16_t):
            self.value = value
    def __init__(self, value: a_i16_t = 0):
        self.value = value
    def __repr__(self):
        return str(self.value)
    @staticmethod
    def array(object o = ()):
        return array('h', o)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class u16:
    cdef a_u16_t value
    property value:
        def __get__(self) -> a_u16_t:
            return self.value
        def __set__(self, value: a_u16_t):
            self.value = value
    def __init__(self, value: a_u16_t = 0):
        self.value = value
    def __repr__(self):
        return str(self.value)
    @staticmethod
    def array(object o = ()):
        return array('H', o)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class i32:
    cdef a_i32_t value
    property value:
        def __get__(self) -> a_i32_t:
            return self.value
        def __set__(self, value: a_i32_t):
            self.value = value
    def __init__(self, value: a_i32_t = 0):
        self.value = value
    def __repr__(self):
        return str(self.value)
    @staticmethod
    def array(object o = ()):
        if INT32_MAX == INT_MAX:
            return array('i', o)
        if INT32_MAX == LONG_MAX:
            return array('l', o)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class u32:
    cdef a_u32_t value
    property value:
        def __get__(self) -> a_u32_t:
            return self.value
        def __set__(self, value: a_u32_t):
            self.value = value
    def __init__(self, value: a_u32_t = 0):
        self.value = value
    def __repr__(self):
        return str(self.value)
    @staticmethod
    def array(object o = ()):
        if UINT32_MAX == UINT_MAX:
            return array('I', o)
        if UINT32_MAX == ULONG_MAX:
            return array('L', o)
    @staticmethod
    def sqrt(x):
        cdef a_u32_t o
        if iterable(x):
            y = u32.array(x)
            z = u32.array(x)
            for i, it in enumerate(x):
                y[i], z[i] = a_u32_sqrt(it, &o), o
            return y, z
        return a_u32_sqrt(x, &o), o

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class i64:
    cdef a_i64_t value
    property value:
        def __get__(self) -> a_i64_t:
            return self.value
        def __set__(self, value: a_i64_t):
            self.value = value
    def __init__(self, value: a_i64_t = 0):
        self.value = value
    def __repr__(self):
        return str(self.value)
    @staticmethod
    def array(object o = ()):
        if INT64_MAX == LONG_MAX:
            return array('l', o)
        if INT64_MAX == LLONG_MAX:
            return array('q', o)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class u64:
    cdef a_u64_t value
    property value:
        def __get__(self) -> a_u64_t:
            return self.value
        def __set__(self, value: a_u64_t):
            self.value = value
    def __init__(self, value: a_u64_t = 0):
        self.value = value
    def __repr__(self):
        return str(self.value)
    @staticmethod
    def array(object o = ()):
        if UINT64_MAX == ULONG_MAX:
            return array('L', o)
        if UINT64_MAX == ULLONG_MAX:
            return array('Q', o)
    @staticmethod
    def sqrt(x):
        cdef a_u64_t o
        if iterable(x):
            y = u64.array(x)
            z = u64.array(x)
            for i, it in enumerate(x):
                y[i], z[i] = a_u64_sqrt(it, &o), o
            return y, z
        return a_u64_sqrt(x, &o), o

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class f32:
    cdef a_f32_t value
    property value:
        def __get__(self) -> a_f32_t:
            return self.value
        def __set__(self, value: a_f32_t):
            self.value = value
    def __init__(self, value: a_f32_t = 0):
        self.value = value
    def __repr__(self):
        return str(self.value)
    @staticmethod
    def array(object o = ()):
        return array('f', o)
    @staticmethod
    def rsqrt(x):
        '''fast inverse square-root'''
        if iterable(x):
            y = array('f', x)
            for i, it in enumerate(x):
                y[i] = a_f32_rsqrt(it)
            return y
        return a_f32_rsqrt(x)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class f64:
    cdef a_f64_t value
    property value:
        def __get__(self) -> a_f64_t:
            return self.value
        def __set__(self, value: a_f64_t):
            self.value = value
    def __init__(self, value: a_f64_t = 0):
        self.value = value
    def __repr__(self):
        return str(self.value)
    @staticmethod
    def array(object o = ()):
        return array('d', o)
    @staticmethod
    def rsqrt(x):
        '''fast inverse square-root'''
        if iterable(x):
            y = array('d', x)
            for i, it in enumerate(x):
                y[i] = a_f64_rsqrt(it)
            return y
        return a_f64_rsqrt(x)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class float:
    cdef a_float_t value
    property value:
        def __get__(self) -> a_float_t:
            return self.value
        def __set__(self, value: a_float_t):
            self.value = value
    def __init__(self, value: a_float_t = 0):
        self.value = value
    def __repr__(self):
        return str(self.value)
    @staticmethod
    def array(object o = ()):
        if A_FLOAT_TYPE == A_FLOAT_DOUBLE:
            return array('d', o)
        if A_FLOAT_TYPE == A_FLOAT_SINGLE:
            return array('f', o)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef bint iterable(object o):
    return PyObject_HasAttrString(o, "__contains__")

include "a/crc.pxi"
include "a/mf.pxi"
include "a/pid.pxi"
include "a/poly.pxi"
include "a/polytrack.pxi"
include "a/tf.pxi"
include "a/version.pxi"

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class hash:
    @staticmethod
    def bkdr(str: bytes, val: a_umax_t) -> a_umax_t:
        return a_hash_bkdr(str, val)
