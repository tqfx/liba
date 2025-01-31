from a cimport *

cdef extern from "a/fuzzy.h":
    a_real a_fuzzy_not(a_real x) nogil
    a_real a_fuzzy_cap(a_real a, a_real b) nogil
    a_real a_fuzzy_cap_algebra(a_real a, a_real b) nogil
    a_real a_fuzzy_cap_bounded(a_real a, a_real b) nogil
    a_real a_fuzzy_cup(a_real a, a_real b) nogil
    a_real a_fuzzy_cup_algebra(a_real a, a_real b) nogil
    a_real a_fuzzy_cup_bounded(a_real a, a_real b) nogil
    a_real a_fuzzy_equ(a_real a, a_real b) nogil
    a_real a_fuzzy_equ_(a_real gamma, a_real a, a_real b) nogil
