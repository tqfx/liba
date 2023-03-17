from a cimport *

cdef extern from "a/version.h":
    a_cstr_t a_version()
    a_uint_t a_version_major()
    a_uint_t a_version_minor()
    a_uint_t a_version_patch()
