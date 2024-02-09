from a cimport *

cdef extern from "a/mf.h":
    enum:
        A_MF_NUL
        A_MF_GAUSS
        A_MF_GAUSS2
        A_MF_GBELL
        A_MF_SIG
        A_MF_DSIG
        A_MF_PSIG
        A_MF_TRAP
        A_MF_TRI
        A_MF_LINS
        A_MF_LINZ
        A_MF_S
        A_MF_Z
        A_MF_PI
    a_float a_mf_gauss(a_float x, a_float sigma, a_float c) nogil
    a_float a_mf_gauss2(a_float x, a_float sigma1, a_float c1, a_float sigma2, a_float c2) nogil
    a_float a_mf_gbell(a_float x, a_float a, a_float b, a_float c) nogil
    a_float a_mf_sig(a_float x, a_float a, a_float c) nogil
    a_float a_mf_dsig(a_float x, a_float a1, a_float c1, a_float a2, a_float c2) nogil
    a_float a_mf_psig(a_float x, a_float a1, a_float c1, a_float a2, a_float c2) nogil
    a_float a_mf_trap(a_float x, a_float a, a_float b, a_float c, a_float d) nogil
    a_float a_mf_tri(a_float x, a_float a, a_float b, a_float c) nogil
    a_float a_mf_lins(a_float x, a_float a, a_float b) nogil
    a_float a_mf_linz(a_float x, a_float a, a_float b) nogil
    a_float a_mf_s(a_float x, a_float a, a_float b) nogil
    a_float a_mf_z(a_float x, a_float a, a_float b) nogil
    a_float a_mf_pi(a_float x, a_float a, a_float b, a_float c, a_float d) nogil
    a_float a_mf(unsigned int t, a_float x, a_float *a) nogil
