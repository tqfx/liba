#include "a/version.h"
#undef a_version_check

char const *const a_version = A_VERSION;
unsigned int const a_version_major = A_VERSION_MAJOR;
unsigned int const a_version_minor = A_VERSION_MINOR;
unsigned int const a_version_patch = A_VERSION_PATCH;
a_u32_t const a_version_tweak = A_VERSION_TWEAK;

int a_version_check(unsigned int const major, unsigned int const minor, unsigned int const patch)
{
    a_version_s inner = A_VERSION_C(a_version_major, a_version_minor, a_version_patch);
    a_version_s outer = A_VERSION_C(major, minor, patch);
    return a_version_cmp(&inner, &outer);
}

int a_version_cmp(a_version_s const *const lhs, a_version_s const *const rhs)
{
    if (lhs->major < rhs->major) { return -3; }
    if (lhs->major > rhs->major) { return +3; }
    if (lhs->minor < rhs->minor) { return -2; }
    if (lhs->minor > rhs->minor) { return +2; }
    if (lhs->patch < rhs->patch) { return -1; }
    if (lhs->patch > rhs->patch) { return +1; }
    return 0;
}

a_bool_t a_version_lt(a_version_s const *const lhs, a_version_s const *const rhs)
{
    if (lhs->major < rhs->major) { return A_TRUE; }
    if (lhs->major > rhs->major) { return A_FALSE; }
    if (lhs->minor < rhs->minor) { return A_TRUE; }
    if (lhs->minor > rhs->minor) { return A_FALSE; }
    if (lhs->patch < rhs->patch) { return A_TRUE; }
    if (lhs->patch > rhs->patch) { return A_FALSE; }
    return A_FALSE;
}

a_bool_t a_version_gt(a_version_s const *const lhs, a_version_s const *const rhs)
{
    if (lhs->major > rhs->major) { return A_TRUE; }
    if (lhs->major < rhs->major) { return A_FALSE; }
    if (lhs->minor > rhs->minor) { return A_TRUE; }
    if (lhs->minor < rhs->minor) { return A_FALSE; }
    if (lhs->patch > rhs->patch) { return A_TRUE; }
    if (lhs->patch < rhs->patch) { return A_FALSE; }
    return A_FALSE;
}

a_bool_t a_version_le(a_version_s const *const lhs, a_version_s const *const rhs)
{
    if (lhs->major < rhs->major) { return A_TRUE; }
    if (lhs->major > rhs->major) { return A_FALSE; }
    if (lhs->minor < rhs->minor) { return A_TRUE; }
    if (lhs->minor > rhs->minor) { return A_FALSE; }
    if (lhs->patch < rhs->patch) { return A_TRUE; }
    if (lhs->patch > rhs->patch) { return A_FALSE; }
    return A_TRUE;
}

a_bool_t a_version_ge(a_version_s const *const lhs, a_version_s const *const rhs)
{
    if (lhs->major > rhs->major) { return A_TRUE; }
    if (lhs->major < rhs->major) { return A_FALSE; }
    if (lhs->minor > rhs->minor) { return A_TRUE; }
    if (lhs->minor < rhs->minor) { return A_FALSE; }
    if (lhs->patch > rhs->patch) { return A_TRUE; }
    if (lhs->patch < rhs->patch) { return A_FALSE; }
    return A_TRUE;
}

a_bool_t a_version_eq(a_version_s const *const lhs, a_version_s const *const rhs)
{
    return (lhs->major == rhs->major) && (lhs->minor == rhs->minor) && (lhs->patch == rhs->patch);
}

a_bool_t a_version_ne(a_version_s const *const lhs, a_version_s const *const rhs)
{
    return (lhs->major != rhs->major) || (lhs->minor != rhs->minor) || (lhs->patch != rhs->patch);
}

unsigned int a_version_parse(a_version_s *const ctx, char const *const ver)
{
    union
    {
        char const *s;
        char *p;
    } u = {ver};
    if (!ver) { return 0; }
    ctx->major = (unsigned int)strtoul(u.s, &u.p, 0);
    if (u.s[0] == '.' && u.s[1] >= '0' && u.s[1] <= '9') { ++u.s; }
    else { goto done; }
    ctx->minor = (unsigned int)strtoul(u.s, &u.p, 0);
    if (u.s[0] == '.' && u.s[1] >= '0' && u.s[1] <= '9') { ++u.s; }
    else { goto done; }
    ctx->patch = (unsigned int)strtoul(u.s, &u.p, 0);
    if (u.s[0] == '.' && u.s[1] >= '0' && u.s[1] <= '9') { ++u.s; }
    else { goto done; }
    ctx->extra = (unsigned int)strtoul(u.s, &u.p, 0);
done:
    return (unsigned int)(u.s - ver);
}
