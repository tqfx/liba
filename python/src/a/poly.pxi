from a.poly cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def poly_eval(x, *a):
    cdef array y
    cdef array f = float.array(a)
    cdef a_float_t *p = <a_float_t *>f.data.as_voidptr
    if iterable(x):
        y = float.array(x)
        a_poly_evaln(p, len(a), <a_float_t *>y.data.as_voidptr, len(x), <a_float_t *>y.data.as_voidptr)
        return y
    return a_poly_eval(p, len(a), x)

@cython.wraparound(False)
@cython.boundscheck(False)
def poly_evar(x, *a):
    cdef array y
    cdef array f = float.array(a)
    cdef a_float_t *p = <a_float_t *>f.data.as_voidptr
    if iterable(x):
        y = float.array(x)
        a_poly_evarn(p, len(a), <a_float_t *>y.data.as_voidptr, len(x), <a_float_t *>y.data.as_voidptr)
        return y
    return a_poly_evar(p, len(a), x)
