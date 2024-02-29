#cython: autotestdict=False
#cython: auto_pickle=False
#cython: boundscheck=False
#cython: wraparound=False
from a cimport *
from cpython cimport *
from cpython.array cimport array
from cython.parallel import prange

cdef inline array_i8(object o):
    return array('b', o)

cdef inline array_u8(object o):
    return array('B', o)

cdef inline array_i16(object o):
    return array('h', o)

cdef inline array_u16(object o):
    return array('H', o)

cdef inline array_i32(object o):
    if INT32_MAX == INT_MAX:
        return array('i', o)
    return array('l', o)

cdef inline array_u32(object o):
    if UINT32_MAX == UINT_MAX:
        return array('I', o)
    return array('L', o)

cdef inline array_i64(object o):
    if INT64_MAX == LONG_MAX:
        return array('l', o)
    return array('q', o)

cdef inline array_u64(object o):
    if UINT64_MAX == ULONG_MAX:
        return array('L', o)
    return array('Q', o)

cdef inline array_f32(object o):
    return array('f', o)

cdef inline array_f64(object o):
    return array('d', o)

cdef inline array_num(object o):
    if A_FLOAT_TYPE == A_FLOAT_SINGLE:
        return array('f', o)
    return array('d', o)

def hash_bkdr(bytes str, a_u32 val = 0) -> a_u32:
    return a_hash_bkdr(str, val)

def hash_sdbm(bytes str, a_u32 val = 0) -> a_u32:
    return a_hash_sdbm(str, val)

include "a/crc.pxi"
include "a/hpf.pxi"
include "a/lpf.pxi"
include "a/math.pxi"
include "a/mf.pxi"
include "a/pid.pxi"
include "a/pid_fuzzy.pxi"
include "a/pid_neuro.pxi"
include "a/poly.pxi"
include "a/tf.pxi"
include "a/trajbell.pxi"
include "a/trajpoly3.pxi"
include "a/trajpoly5.pxi"
include "a/trajpoly7.pxi"
include "a/trajtrap.pxi"
include "a/version.pxi"
