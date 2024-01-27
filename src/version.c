#include "a/version.h"
#undef a_version_check

unsigned int const a_version_major = A_VERSION_MAJOR;
unsigned int const a_version_minor = A_VERSION_MINOR;
unsigned int const a_version_patch = A_VERSION_PATCH;
a_u32 const a_version_tweak = A_VERSION_TWEAK;

int a_version_check(unsigned int major, unsigned int minor, unsigned int patch)
{
    a_version inner, outer;
    inner.major = a_version_major;
    inner.minor = a_version_minor;
    inner.third = a_version_patch;
    inner.extra = 0;
    outer.major = major;
    outer.minor = minor;
    outer.third = patch;
    outer.extra = 0;
    return a_version_cmp(&inner, &outer);
}

int a_version_cmp(a_version const *lhs, a_version const *rhs)
{
    if (lhs->major < rhs->major) { return -3; }
    if (lhs->major > rhs->major) { return +3; }
    if (lhs->minor < rhs->minor) { return -2; }
    if (lhs->minor > rhs->minor) { return +2; }
    if (lhs->third < rhs->third) { return -1; }
    if (lhs->third > rhs->third) { return +1; }
    return 0;
}

a_bool a_version_lt(a_version const *lhs, a_version const *rhs)
{
    if (lhs->major < rhs->major) { return A_TRUE; }
    if (lhs->major > rhs->major) { return A_FALSE; }
    if (lhs->minor < rhs->minor) { return A_TRUE; }
    if (lhs->minor > rhs->minor) { return A_FALSE; }
    if (lhs->third < rhs->third) { return A_TRUE; }
    if (lhs->third > rhs->third) { return A_FALSE; }
    return A_FALSE;
}

a_bool a_version_gt(a_version const *lhs, a_version const *rhs)
{
    if (lhs->major > rhs->major) { return A_TRUE; }
    if (lhs->major < rhs->major) { return A_FALSE; }
    if (lhs->minor > rhs->minor) { return A_TRUE; }
    if (lhs->minor < rhs->minor) { return A_FALSE; }
    if (lhs->third > rhs->third) { return A_TRUE; }
    if (lhs->third < rhs->third) { return A_FALSE; }
    return A_FALSE;
}

a_bool a_version_le(a_version const *lhs, a_version const *rhs)
{
    if (lhs->major < rhs->major) { return A_TRUE; }
    if (lhs->major > rhs->major) { return A_FALSE; }
    if (lhs->minor < rhs->minor) { return A_TRUE; }
    if (lhs->minor > rhs->minor) { return A_FALSE; }
    if (lhs->third < rhs->third) { return A_TRUE; }
    if (lhs->third > rhs->third) { return A_FALSE; }
    return A_TRUE;
}

a_bool a_version_ge(a_version const *lhs, a_version const *rhs)
{
    if (lhs->major > rhs->major) { return A_TRUE; }
    if (lhs->major < rhs->major) { return A_FALSE; }
    if (lhs->minor > rhs->minor) { return A_TRUE; }
    if (lhs->minor < rhs->minor) { return A_FALSE; }
    if (lhs->third > rhs->third) { return A_TRUE; }
    if (lhs->third < rhs->third) { return A_FALSE; }
    return A_TRUE;
}

a_bool a_version_eq(a_version const *lhs, a_version const *rhs)
{
    return (lhs->major == rhs->major) && (lhs->minor == rhs->minor) && (lhs->third == rhs->third);
}

a_bool a_version_ne(a_version const *lhs, a_version const *rhs)
{
    return (lhs->major != rhs->major) || (lhs->minor != rhs->minor) || (lhs->third != rhs->third);
}

#include <stdlib.h>

unsigned int a_version_parse(a_version *ctx, char const *ver)
{
    union
    {
        char const *s;
        char *p;
    } u;
    u.s = ver;
    if (!ver) { return 0; }
    ctx->major = (unsigned int)strtoul(u.s, &u.p, 0);
    if (u.s[0] == '.' && u.s[1] >= '0' && u.s[1] <= '9') { ++u.s; }
    else { goto major; }
    ctx->minor = (unsigned int)strtoul(u.s, &u.p, 0);
    if (u.s[0] == '.' && u.s[1] >= '0' && u.s[1] <= '9') { ++u.s; }
    else { goto minor; }
    ctx->third = (unsigned int)strtoul(u.s, &u.p, 0);
    if (u.s[0] == '.' && u.s[1] >= '0' && u.s[1] <= '9') { ++u.s; }
    else { goto third; }
    ctx->extra = (unsigned int)strtoul(u.s, &u.p, 0);
    goto extra;
major:
    ctx->minor = 0;
minor:
    ctx->third = 0;
third:
    ctx->extra = 0;
extra:
    return (unsigned int)(u.s - ver);
}
