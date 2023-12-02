cimport cython
from a cimport *
from a.math cimport *
from cpython cimport *
from cpython.array cimport array

@cython.wraparound(False)
@cython.boundscheck(False)
def array_i8(object o):
    return array('b', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def array_u8(object o):
    return array('B', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def array_i16(object o):
    return array('h', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def array_u16(object o):
    return array('H', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def array_i32(object o):
    if INT32_MAX == INT_MAX:
        return array('i', o)
    if INT32_MAX == LONG_MAX:
        return array('l', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def array_u32(object o):
    if UINT32_MAX == UINT_MAX:
        return array('I', o)
    if UINT32_MAX == ULONG_MAX:
        return array('L', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def array_i64(object o):
    if INT64_MAX == LONG_MAX:
        return array('l', o)
    if INT64_MAX == LLONG_MAX:
        return array('q', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def array_u64(object o):
    if UINT64_MAX == ULONG_MAX:
        return array('L', o)
    if UINT64_MAX == ULLONG_MAX:
        return array('Q', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def array_f32(object o):
    return array('f', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def array_f64(object o):
    return array('d', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def array_num(object o):
    if A_FLOAT_TYPE == A_FLOAT_DOUBLE:
        return array('d', o)
    if A_FLOAT_TYPE == A_FLOAT_SINGLE:
        return array('f', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def sqrt_u32(x):
    cdef a_u32_t o
    if iterable(x):
        y = array_u32(x)
        z = array_u32(x)
        for i, it in enumerate(x):
            y[i], z[i] = a_u32_sqrt(it, &o), o
        return y, z
    return a_u32_sqrt(x, &o), o

@cython.wraparound(False)
@cython.boundscheck(False)
def sqrt_u64(x):
    cdef a_u64_t o
    if iterable(x):
        y = array_u64(x)
        z = array_u64(x)
        for i, it in enumerate(x):
            y[i], z[i] = a_u64_sqrt(it, &o), o
        return y, z
    return a_u64_sqrt(x, &o), o

@cython.wraparound(False)
@cython.boundscheck(False)
def rsqrt_f32(x):
    '''fast inverse square-root'''
    if iterable(x):
        y = array('f', x)
        for i, it in enumerate(x):
            y[i] = a_f32_rsqrt(it)
        return y
    return a_f32_rsqrt(x)

@cython.wraparound(False)
@cython.boundscheck(False)
def rsqrt_f64(x):
    '''fast inverse square-root'''
    if iterable(x):
        y = array('d', x)
        for i, it in enumerate(x):
            y[i] = a_f64_rsqrt(it)
        return y
    return a_f64_rsqrt(x)

@cython.wraparound(False)
@cython.boundscheck(False)
def hash_bkdr(str: bytes, val: a_umax_t) -> a_umax_t:
    return a_hash_bkdr(str, val)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef bint iterable(object o):
    return PyObject_HasAttrString(o, "__contains__")

include "a/crc.pxi"
include "a/mf.pxi"
include "a/pid.pxi"
include "a/pid_fuzzy.pxi"
include "a/pid_neuron.pxi"
include "a/poly.pxi"
include "a/polytraj.pxi"
include "a/tf.pxi"
include "a/version.pxi"
