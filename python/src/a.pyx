cimport cython
from a cimport *
from cpython cimport *
from cpython.array cimport array

cdef bint iterable(object o):
    return PyObject_HasAttrString(o, "__contains__")

cdef array u8s(object o = ()):
    return array('B', o)

cdef array u16s(object o = ()):
    return array('H', o)

cdef array u32s(object o = ()):
    if UINT32_MAX == UINT_MAX:
        return array('I', o)
    if UINT32_MAX == ULONG_MAX:
        return array('L', o)

cdef array u64s(object o = ()):
    if UINT64_MAX == ULONG_MAX:
        return array('L', o)
    if UINT64_MAX == ULLONG_MAX:
        return array('Q', o)

cdef array floats(object o = ()):
    if A_FLOAT_TYPE == A_FLOAT_DOUBLE:
        return array('d', o)
    if A_FLOAT_TYPE == A_FLOAT_SINGLE:
        return array('f', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def hash_bkdr(str: bytes, val: a_umax_t) -> a_umax_t:
    return a_hash_bkdr(str, val)

include "a/crc.pxi"
include "a/math.pxi"
include "a/mf.pxi"
include "a/pid.pxi"
include "a/pid_fuzzy.pxi"
include "a/poly.pxi"
include "a/polytrack.pxi"
include "a/tf.pxi"
include "a/version.pxi"
