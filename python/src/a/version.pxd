from a cimport *

cdef extern from "a/version.h":
    """#undef a_version_check"""
    const unsigned int A_VERSION_MAJOR
    const unsigned int A_VERSION_MINOR
    const unsigned int A_VERSION_PATCH
    const a_u32 A_VERSION_TWEAK
    const char *const A_VERSION
    ctypedef struct a_version:
        unsigned int major
        unsigned int minor
        unsigned int third
        unsigned int extra
        char alpha[4]
    int a_version_check(unsigned int major, unsigned int minor, unsigned int patch)
    int a_version_tostr(const a_version *ctx, void *pdata, a_size nbyte)
    unsigned int a_version_parse(a_version *ctx, const char *ver)
    int a_version_cmp(const a_version *lhs, const a_version *rhs)
    bint a_version_lt(const a_version *lhs, const a_version *rhs)
    bint a_version_gt(const a_version *lhs, const a_version *rhs)
    bint a_version_le(const a_version *lhs, const a_version *rhs)
    bint a_version_ge(const a_version *lhs, const a_version *rhs)
    bint a_version_eq(const a_version *lhs, const a_version *rhs)
    bint a_version_ne(const a_version *lhs, const a_version *rhs)
    void a_version_set_alpha(a_version *ctx, const char *alpha)
    void a_version_alpha(const a_version *ctx, char alpha[5])
