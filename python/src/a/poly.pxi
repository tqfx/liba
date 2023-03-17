from a.poly cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def poly_eval(x, *a):
    d, n = reals(a), len(a)
    cdef a_real_t *p = <a_real_t *>d.data.as_voidptr
    if iterable(x):
        y = reals(x)
        a_poly_evaln(p, n, <a_real_t *>y.data.as_voidptr, len(x), <a_real_t *>y.data.as_voidptr)
        return y
    return a_poly_eval(p, n, x)

@cython.wraparound(False)
@cython.boundscheck(False)
def poly_evar(x, *a):
    d, n = reals(a), len(a)
    cdef a_real_t *p = <a_real_t *>d.data.as_voidptr
    if iterable(x):
        y = reals(x)
        a_poly_evarn(p, n, <a_real_t *>y.data.as_voidptr, len(x), <a_real_t *>y.data.as_voidptr)
        return y
    return a_poly_evar(p, n, x)
