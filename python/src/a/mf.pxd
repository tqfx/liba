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
    a_float_t a_mf_gauss(a_float_t x, a_float_t sigma, a_float_t c)
    a_float_t a_mf_gbell(a_float_t x, a_float_t a, a_float_t b, a_float_t c)
    a_float_t a_mf_sig(a_float_t x, a_float_t a, a_float_t c)
    a_float_t a_mf_trap(a_float_t x, a_float_t a, a_float_t b, a_float_t c, a_float_t d)
    a_float_t a_mf_tri(a_float_t x, a_float_t a, a_float_t b, a_float_t c)
    a_float_t a_mf_z(a_float_t x, a_float_t a, a_float_t b)
    a_float_t a_mf(unsigned int t, a_float_t x, a_float_t *a)
