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
    a_real a_mf_gauss(a_real x, a_real sigma, a_real c) nogil
    a_real a_mf_gauss2(a_real x, a_real sigma1, a_real c1, a_real sigma2, a_real c2) nogil
    a_real a_mf_gbell(a_real x, a_real a, a_real b, a_real c) nogil
    a_real a_mf_sig(a_real x, a_real a, a_real c) nogil
    a_real a_mf_dsig(a_real x, a_real a1, a_real c1, a_real a2, a_real c2) nogil
    a_real a_mf_psig(a_real x, a_real a1, a_real c1, a_real a2, a_real c2) nogil
    a_real a_mf_trap(a_real x, a_real a, a_real b, a_real c, a_real d) nogil
    a_real a_mf_tri(a_real x, a_real a, a_real b, a_real c) nogil
    a_real a_mf_lins(a_real x, a_real a, a_real b) nogil
    a_real a_mf_linz(a_real x, a_real a, a_real b) nogil
    a_real a_mf_s(a_real x, a_real a, a_real b) nogil
    a_real a_mf_z(a_real x, a_real a, a_real b) nogil
    a_real a_mf_pi(a_real x, a_real a, a_real b, a_real c, a_real d) nogil
    a_real a_mf(unsigned int t, a_real x, a_real *a) nogil
