#define LIBA_VERSION_C
#include "a/version.h"

a_cstr_t a_version(void)
{
    return A_VERSION;
}

a_uint_t a_version_major(void)
{
    return A_VERSION_MAJOR;
}

a_uint_t a_version_minor(void)
{
    return A_VERSION_MINOR;
}

a_uint_t a_version_patch(void)
{
    return A_VERSION_PATCH;
}

a_int_t a_version_cmp(a_version_s const *const lhs, a_version_s const *const rhs)
{
    if (lhs->major < rhs->major)
    {
        return -3;
    }
    if (lhs->major > rhs->major)
    {
        return +3;
    }
    if (lhs->minor < rhs->minor)
    {
        return -2;
    }
    if (lhs->minor > rhs->minor)
    {
        return +2;
    }
    if (lhs->patch < rhs->patch)
    {
        return -1;
    }
    if (lhs->patch > rhs->patch)
    {
        return +1;
    }
    return 0;
}

#undef a_version_check
a_int_t a_version_check(a_uint_t const major, a_uint_t const minor, a_uint_t const patch)
{
    a_version_s inner = A_VERSION_C(0, 0, 0);
    a_version_s outer = A_VERSION_C(0, 0, 0);
    inner.major = a_version_major();
    inner.minor = a_version_minor();
    inner.patch = a_version_patch();
    outer.major = major;
    outer.minor = minor;
    outer.patch = patch;
    return a_version_cmp(&inner, &outer);
}
