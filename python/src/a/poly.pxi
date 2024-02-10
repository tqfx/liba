from a.poly cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def poly_eval(x, *a):
    cdef array f, y
    cdef a_float *q
    cdef a_float *p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    cdef a_size b
    b = len(a)
    f = array_num(a)
    p = <a_float *>f.data.as_voidptr
    if iterable(x):
        n = len(x)
        y = array_num(x)
        q = <a_float *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            q[i] = a_poly_eval(p, b, q[i])
        return y
    return a_poly_eval(p, b, x)

@cython.wraparound(False)
@cython.boundscheck(False)
def poly_evar(x, *a):
    cdef array f, y
    cdef a_float *q
    cdef a_float *p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    cdef a_size b
    b = len(a)
    f = array_num(a)
    p = <a_float *>f.data.as_voidptr
    if iterable(x):
        n = len(x)
        y = array_num(x)
        q = <a_float *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            q[i] = a_poly_evar(p, b, q[i])
        return y
    return a_poly_evar(p, b, x)
