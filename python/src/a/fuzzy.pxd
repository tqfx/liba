from a cimport *

cdef extern from "a/fuzzy.h":
    a_float a_fuzzy_not(a_float x)
    a_float a_fuzzy_cap(a_float a, a_float b)
    a_float a_fuzzy_cap_algebra(a_float a, a_float b)
    a_float a_fuzzy_cap_bounded(a_float a, a_float b)
    a_float a_fuzzy_cup(a_float a, a_float b)
    a_float a_fuzzy_cup_algebra(a_float a, a_float b)
    a_float a_fuzzy_cup_bounded(a_float a, a_float b)
    a_float a_fuzzy_equ(a_float a, a_float b)
    a_float a_fuzzy_equ_(a_float gamma, a_float a, a_float b)
