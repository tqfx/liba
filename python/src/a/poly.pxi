from a.poly cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def poly_eval(x, *a):
    cdef array f, y
    cdef a_float *q
    cdef a_float *p
    f = array_num(a)
    p = <a_float *>f.data.as_voidptr
    if iterable(x):
        y = array_num(x)
        q = <a_float *>y.data.as_voidptr
        a_poly_evaln(p, len(a), q, len(x), q)
        return y
    return a_poly_eval(p, len(a), x)

@cython.wraparound(False)
@cython.boundscheck(False)
def poly_evar(x, *a):
    cdef array f, y
    cdef a_float *q
    cdef a_float *p
    f = array_num(a)
    f = array_num(a)
    p = <a_float *>f.data.as_voidptr
    if iterable(x):
        y = array_num(x)
        q = <a_float *>y.data.as_voidptr
        a_poly_evarn(p, len(a), q, len(x), q)
        return y
    return a_poly_evar(p, len(a), x)
