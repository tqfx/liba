from a.math cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def isqrt(x: int):
    if x <= 1:
        return x
    x0 = 1 << ((x.bit_length() + 1) >> 1)
    x1 = (x0 + x // x0) >> 1
    while x0 > x1:
        x0 = x1
        x1 = (x0 + x // x0) >> 1
    return x0

@cython.wraparound(False)
@cython.boundscheck(False)
def sqrt_u32(x):
    if iterable(x):
        y = array_u16(x)
        for i, it in enumerate(x):
            y[i] = a_u32_sqrt(it)
        return y
    return a_u32_sqrt(x)

@cython.wraparound(False)
@cython.boundscheck(False)
def sqrt_u64(x):
    if iterable(x):
        y = array_u32(x)
        for i, it in enumerate(x):
            y[i] = a_u64_sqrt(it)
        return y
    return a_u64_sqrt(x)

@cython.wraparound(False)
@cython.boundscheck(False)
def rsqrt_f32(x):
    '''reciprocal of square-root'''
    if iterable(x):
        y = array_f32(x)
        for i, it in enumerate(x):
            y[i] = a_f32_rsqrt(it)
        return y
    return a_f32_rsqrt(x)

@cython.wraparound(False)
@cython.boundscheck(False)
def rsqrt_f64(x):
    '''reciprocal of square-root'''
    if iterable(x):
        y = array_f64(x)
        for i, it in enumerate(x):
            y[i] = a_f64_rsqrt(it)
        return y
    return a_f64_rsqrt(x)
