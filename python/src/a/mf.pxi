from a.mf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class mf:
    '''membership function'''
    NUL    = A_MF_NUL
    GAUSS  = A_MF_GAUSS
    GAUSS2 = A_MF_GAUSS2
    GBELL  = A_MF_GBELL
    SIG    = A_MF_SIG
    DSIG   = A_MF_DSIG
    PSIG   = A_MF_PSIG
    TRAP   = A_MF_TRAP
    TRI    = A_MF_TRI
    LINS   = A_MF_LINS
    LINZ   = A_MF_LINZ
    S      = A_MF_S
    Z      = A_MF_Z
    PI     = A_MF_PI
    @staticmethod
    def __call__(e: int, x, a):
        cdef array f = array_num(a)
        cdef a_float *v = <a_float *>f.data.as_voidptr
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf(e, it, v)
            return y
        return a_mf(e, x, v)
    @staticmethod
    def gauss(x, sigma: a_float, c: a_float):
        '''Gaussian membership function'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_gauss(it, sigma, c)
            return y
        return a_mf_gauss(x, sigma, c)
    @staticmethod
    def gauss2(x, sigma1: a_float, c1: a_float, sigma2: a_float, c2: a_float):
        '''Gaussian combination membership function'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_gauss2(it, sigma1, c1, sigma2, c2)
            return y
        return a_mf_gauss2(x, sigma1, c1, sigma2, c2)
    @staticmethod
    def gbell(x, a: a_float, b: a_float, c: a_float):
        '''Generalized bell-shaped membership function'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_gbell(it, a, b, c)
            return y
        return a_mf_gbell(x, a, b, c)
    @staticmethod
    def sig(x, a: a_float, c: a_float):
        '''Sigmoidal membership function'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_sig(it, a, c)
            return y
        return a_mf_sig(x, a, c)
    @staticmethod
    def dsig(x, a1: a_float, c1: a_float, a2: a_float, c2: a_float):
        '''Difference between two sigmoidal membership functions'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_dsig(it, a1, c1, a2, c2)
            return y
        return a_mf_dsig(x, a1, c1, a2, c2)
    @staticmethod
    def psig(x, a1: a_float, c1: a_float, a2: a_float, c2: a_float):
        '''Product of two sigmoidal membership functions'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_psig(it, a1, c1, a2, c2)
            return y
        return a_mf_psig(x, a1, c1, a2, c2)
    @staticmethod
    def trap(x, a: a_float, b: a_float, c: a_float, d: a_float):
        '''Trapezoidal membership function'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_trap(it, a, b, c, d)
            return y
        return a_mf_trap(x, a, b, c, d)
    @staticmethod
    def tri(x, a: a_float, b: a_float, c: a_float):
        '''Triangular membership function'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_tri(it, a, b, c)
            return y
        return a_mf_tri(x, a, b, c)
    @staticmethod
    def lins(x, a: a_float, b: a_float):
        '''Linear s-shaped saturation membership function'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_lins(it, a, b)
            return y
        return a_mf_lins(x, a, b)
    def linz(x, a: a_float, b: a_float):
        '''Linear z-shaped saturation membership function'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_linz(it, a, b)
            return y
        return a_mf_linz(x, a, b)
    @staticmethod
    def s(x, a: a_float, b: a_float):
        '''S-shaped membership function'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_s(it, a, b)
            return y
        return a_mf_s(x, a, b)
    def z(x, a: a_float, b: a_float):
        '''Z-shaped membership function'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_z(it, a, b)
            return y
        return a_mf_z(x, a, b)
    @staticmethod
    def pi(x, a: a_float, b: a_float, c: a_float, d: a_float):
        '''Pi-shaped membership function'''
        if iterable(x):
            y = array_num(x)
            for i, it in enumerate(x):
                y[i] = a_mf_pi(it, a, b, c, d)
            return y
        return a_mf_pi(x, a, b, c, d)
