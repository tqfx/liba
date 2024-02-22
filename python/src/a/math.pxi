from a.math cimport *

def isqrt(x: int):
    if x <= 1:
        return x
    x0 = 1 << ((x.bit_length() + 1) >> 1)
    x1 = (x0 + x // x0) >> 1
    while x0 > x1:
        x0 = x1
        x1 = (x0 + x // x0) >> 1
    return x0

def sqrt_u32(x):
    cdef array y
    cdef a_u32 *p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    if PyObject_HasAttrString(x, "__contains__"):
        n = len(x)
        y = array_u32(x)
        p = <a_u32 *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_u32_sqrt(p[i])
        return array_u16(y)
    return a_u32_sqrt(x)

def sqrt_u64(x):
    cdef array y
    cdef a_u64 *p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    if PyObject_HasAttrString(x, "__contains__"):
        n = len(x)
        y = array_u64(x)
        p = <a_u64 *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_u64_sqrt(p[i])
        return array_u32(y)
    return a_u64_sqrt(x)

def rsqrt_f32(x):
    cdef array y
    cdef a_f32 *p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    if PyObject_HasAttrString(x, "__contains__"):
        n = len(x)
        y = array_f32(x)
        p = <a_f32 *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_f32_rsqrt(p[i])
        return y
    return a_f32_rsqrt(x)

def rsqrt_f64(x):
    cdef array y
    cdef a_f64 *p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    if PyObject_HasAttrString(x, "__contains__"):
        n = len(x)
        y = array_f64(x)
        p = <a_f64 *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_f64_rsqrt(p[i])
        return y
    return a_f64_rsqrt(x)
