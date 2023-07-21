from a.mf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class mf:
    '''membership function'''
    NUL   = A_MF_NUL
    GAUSS = A_MF_GAUSS
    GBELL = A_MF_GBELL
    SIG   = A_MF_SIG
    TRAP  = A_MF_TRAP
    TRI   = A_MF_TRI
    Z     = A_MF_Z
    @staticmethod
    def __call__(e: a_mf_e, x, a):
        cdef array f = float.array(a)
        cdef a_float_t *v = <a_float_t *>f.data.as_voidptr
        if iterable(x):
            y = float.array(x)
            for i, it in enumerate(x):
                y[i] = a_mf(e, it, v)
            return y
        return a_mf(e, x, v)
    @staticmethod
    def gauss(x, sigma: a_float_t, c: a_float_t):
        '''Gaussian membership function'''
        if iterable(x):
            y = float.array(x)
            for i, it in enumerate(x):
                y[i] = a_mf_gauss(it, sigma, c)
            return y
        return a_mf_gauss(x, sigma, c)
    @staticmethod
    def gbell(x, a: a_float_t, b: a_float_t, c: a_float_t):
        '''Generalized bell-shaped membership function'''
        if iterable(x):
            y = float.array(x)
            for i, it in enumerate(x):
                y[i] = a_mf_gbell(it, a, b, c)
            return y
        return a_mf_gbell(x, a, b, c)
    @staticmethod
    def sig(x, a: a_float_t, c: a_float_t):
        '''Sigmoidal membership function'''
        if iterable(x):
            y = float.array(x)
            for i, it in enumerate(x):
                y[i] = a_mf_sig(it, a, c)
            return y
        return a_mf_sig(x, a, c)
    @staticmethod
    def trap(x, a: a_float_t, b: a_float_t, c: a_float_t, d: a_float_t):
        '''Trapezoidal membership function'''
        if iterable(x):
            y = float.array(x)
            for i, it in enumerate(x):
                y[i] = a_mf_trap(it, a, b, c, d)
            return y
        return a_mf_trap(x, a, b, c, d)
    @staticmethod
    def tri(x, a: a_float_t, b: a_float_t, c: a_float_t):
        '''Triangular membership function'''
        if iterable(x):
            y = float.array(x)
            for i, it in enumerate(x):
                y[i] = a_mf_tri(it, a, b, c)
            return y
        return a_mf_tri(x, a, b, c)
    @staticmethod
    def z(x, a: a_float_t, b: a_float_t):
        '''Z-shaped membership function'''
        if iterable(x):
            y = float.array(x)
            for i, it in enumerate(x):
                y[i] = a_mf_z(it, a, b)
            return y
        return a_mf_z(x, a, b)
