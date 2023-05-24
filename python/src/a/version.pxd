from a cimport *

cdef extern from "a/version.h":
    const char *a_version()
    unsigned int a_version_major()
    unsigned int a_version_minor()
    unsigned int a_version_patch()
