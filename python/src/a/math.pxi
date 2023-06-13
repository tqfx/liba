from a.math cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def f32_rsqrt(x):
    '''fast inverse square-root'''
    if iterable(x):
        y = floats(x)
        for i, it in enumerate(x):
            y[i] = a_f32_rsqrt(it)
        return y
    return a_f32_rsqrt(x)

@cython.wraparound(False)
@cython.boundscheck(False)
def f64_rsqrt(x):
    '''fast inverse square-root'''
    if iterable(x):
        y = floats(x)
        for i, it in enumerate(x):
            y[i] = a_f64_rsqrt(it)
        return y
    return a_f64_rsqrt(x)

@cython.wraparound(False)
@cython.boundscheck(False)
def u32_sqrt(x):
    cdef a_u32_t o
    if iterable(x):
        y = u32s(x)
        z = u32s(x)
        for i, it in enumerate(x):
            y[i], z[i] = a_u32_sqrt(it, &o), o
        return y, z
    return a_u32_sqrt(x, &o), o

@cython.wraparound(False)
@cython.boundscheck(False)
def u64_sqrt(x):
    cdef a_u64_t o
    if iterable(x):
        y = u64s(x)
        z = u64s(x)
        for i, it in enumerate(x):
            y[i], z[i] = a_u64_sqrt(it, &o), o
        return y, z
    return a_u64_sqrt(x, &o), o
