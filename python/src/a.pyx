cimport cython
from a cimport *
from cpython cimport *
cdef bint iterable(object o):
    return PyObject_HasAttrString(o, "__contains__")

from cpython.array cimport array
cdef array floats(object o = ()):
    if A_FLOAT_TYPE == A_FLOAT_DOUBLE:
        return array('d', o)
    if A_FLOAT_TYPE == A_FLOAT_SINGLE:
        return array('f', o)

@cython.wraparound(False)
@cython.boundscheck(False)
def hash_bkdr(str: bytes, val: a_umax_t) -> a_umax_t:
    return a_hash_bkdr(str, val)

include "a/math.pxi"
include "a/mf.pxi"
include "a/pid.pxi"
include "a/pid_fuzzy.pxi"
include "a/poly.pxi"
include "a/polytrack.pxi"
include "a/tf.pxi"
include "a/version.pxi"
