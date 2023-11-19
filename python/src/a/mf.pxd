from a cimport *

cdef extern from "a/mf.h":
    ctypedef enum a_mf_e:
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
    a_float_t a_mf_gauss(a_float_t x, a_float_t sigma, a_float_t c)
    a_float_t a_mf_gauss2(a_float_t x, a_float_t sigma1, a_float_t c1, a_float_t sigma2, a_float_t c2)
    a_float_t a_mf_gbell(a_float_t x, a_float_t a, a_float_t b, a_float_t c)
    a_float_t a_mf_sig(a_float_t x, a_float_t a, a_float_t c)
    a_float_t a_mf_dsig(a_float_t x, a_float_t a1, a_float_t c1, a_float_t a2, a_float_t c2)
    a_float_t a_mf_psig(a_float_t x, a_float_t a1, a_float_t c1, a_float_t a2, a_float_t c2)
    a_float_t a_mf_trap(a_float_t x, a_float_t a, a_float_t b, a_float_t c, a_float_t d)
    a_float_t a_mf_tri(a_float_t x, a_float_t a, a_float_t b, a_float_t c)
    a_float_t a_mf_lins(a_float_t x, a_float_t a, a_float_t b)
    a_float_t a_mf_linz(a_float_t x, a_float_t a, a_float_t b)
    a_float_t a_mf_s(a_float_t x, a_float_t a, a_float_t b)
    a_float_t a_mf_z(a_float_t x, a_float_t a, a_float_t b)
    a_float_t a_mf_pi(a_float_t x, a_float_t a, a_float_t b, a_float_t c, a_float_t d)
    a_float_t a_mf(unsigned int t, a_float_t x, a_float_t *a)
