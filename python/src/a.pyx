include "a/__init__.pxi"

from cpython cimport *
cdef bint iterable(object o):
    return PyObject_HasAttrString(o, "__contains__")

from cpython.array cimport array
cdef array floats(object o = ()):
    IF A_SIZE_FLOAT == 8:
        return array('d', o)
    IF A_SIZE_FLOAT == 4:
        return array('f', o)

cimport cython
include "a/version.pxi"
include "a/math.pxi"
include "a/mf.pxi"
include "a/tf.pxi"
include "a/pid.pxi"
include "a/fpid.pxi"
include "a/poly.pxi"
include "a/polytrack.pxi"
