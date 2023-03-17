from a.math cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def f32_rsqrt(x):
    '''fast inverse square-root'''
    if iterable(x):
        y = reals(x)
        for i, it in enumerate(x):
            y[i] = a_f32_rsqrt(it)
        return y
    return a_f32_rsqrt(x)

@cython.wraparound(False)
@cython.boundscheck(False)
def f64_rsqrt(x):
    '''fast inverse square-root'''
    if iterable(x):
        y = reals(x)
        for i, it in enumerate(x):
            y[i] = a_f64_rsqrt(it)
        return y
    return a_f64_rsqrt(x)
