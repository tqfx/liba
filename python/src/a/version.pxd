from a cimport *

cdef extern from "a/version.h":
    """#undef a_version_check"""
    const char *A_VERSION
    unsigned int A_VERSION_MAJOR
    unsigned int A_VERSION_MINOR
    unsigned int A_VERSION_PATCH
    ctypedef struct a_version_s:
        unsigned int major
        unsigned int minor
        unsigned int patch
    int a_version_check(unsigned int major, unsigned int minor, unsigned int patch)
    bint a_version_lt(const a_version_s *lhs, const a_version_s *rhs)
    bint a_version_gt(const a_version_s *lhs, const a_version_s *rhs)
    bint a_version_le(const a_version_s *lhs, const a_version_s *rhs)
    bint a_version_ge(const a_version_s *lhs, const a_version_s *rhs)
    bint a_version_eq(const a_version_s *lhs, const a_version_s *rhs)
    bint a_version_ne(const a_version_s *lhs, const a_version_s *rhs)
