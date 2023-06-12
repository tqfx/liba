from a cimport *

cdef extern from "a/version.h":
    const char *A_VERSION
    const char *a_version()
    unsigned int A_VERSION_MAJOR
    unsigned int a_version_major()
    unsigned int A_VERSION_MINOR
    unsigned int a_version_minor()
    unsigned int A_VERSION_PATCH
    unsigned int a_version_patch()
