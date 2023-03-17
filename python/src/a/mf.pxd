from a cimport *

cdef extern from "a/mf.h":
    ctypedef enum a_mf_e:
        A_MF_NUL
        A_MF_GAUSS
        A_MF_GBELL
        A_MF_SIG
        A_MF_TRAP
        A_MF_TRI
        A_MF_Z
    a_real_t a_mf_gauss(a_real_t x, a_real_t sigma, a_real_t c)
    a_real_t a_mf_gbell(a_real_t x, a_real_t a, a_real_t b, a_real_t c)
    a_real_t a_mf_sig(a_real_t x, a_real_t a, a_real_t c)
    a_real_t a_mf_trap(a_real_t x, a_real_t a, a_real_t b, a_real_t c, a_real_t d)
    a_real_t a_mf_tri(a_real_t x, a_real_t a, a_real_t b, a_real_t c)
    a_real_t a_mf_z(a_real_t x, a_real_t a, a_real_t b)
    a_real_t a_mf(a_uint_t t, a_real_t x, a_real_t *a)
