from a cimport *

cdef extern from "a/version.h":
    """#undef a_version_check"""
    const unsigned int A_VERSION_MAJOR
    const unsigned int A_VERSION_MINOR
    const unsigned int A_VERSION_PATCH
    const a_u64_t A_VERSION_TWEAK
    const char *A_VERSION
    ctypedef struct a_version_s:
        unsigned int major
        unsigned int minor
        unsigned int patch
    unsigned int a_version_parse(a_version_s *ctx, const char *ver)
    int a_version_check(unsigned int major, unsigned int minor, unsigned int patch)
    bint a_version_lt(const a_version_s *lhs, const a_version_s *rhs)
    bint a_version_gt(const a_version_s *lhs, const a_version_s *rhs)
    bint a_version_le(const a_version_s *lhs, const a_version_s *rhs)
    bint a_version_ge(const a_version_s *lhs, const a_version_s *rhs)
    bint a_version_eq(const a_version_s *lhs, const a_version_s *rhs)
    bint a_version_ne(const a_version_s *lhs, const a_version_s *rhs)
