from a.poly cimport *

def poly_eval(x, *a):
    cdef array y
    cdef array a_
    cdef a_float *p
    cdef a_float *a_p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    cdef a_size a_n = len(a)
    a_ = array_num(a)
    a_p = <a_float *>a_.data.as_voidptr
    if PyObject_HasAttrString(x, "__contains__"):
        n = len(x)
        y = array_num(x)
        p = <a_float *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_poly_eval(a_p, a_n, p[i])
        return y
    return a_poly_eval(a_p, a_n, x)

def poly_evar(x, *a):
    cdef array y
    cdef array a_
    cdef a_float *p
    cdef a_float *a_p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    cdef a_size a_n = len(a)
    a_ = array_num(a)
    a_p = <a_float *>a_.data.as_voidptr
    if PyObject_HasAttrString(x, "__contains__"):
        n = len(x)
        y = array_num(x)
        p = <a_float *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_poly_evar(a_p, a_n, p[i])
        return y
    return a_poly_evar(a_p, a_n, x)
