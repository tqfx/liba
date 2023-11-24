#define LIBA_VERSION_C
#include "a/version.h"

char const *const a_version = A_VERSION;
unsigned int const a_version_major = A_VERSION_MAJOR;
unsigned int const a_version_minor = A_VERSION_MINOR;
unsigned int const a_version_patch = A_VERSION_PATCH;
a_u32_t const a_version_tweak = A_VERSION_TWEAK;

#undef a_version_check
int a_version_check(unsigned int const major, unsigned int const minor, unsigned int const patch)
{
    a_version_s inner = A_VERSION_C(a_version_major, a_version_minor, a_version_patch);
    a_version_s outer = A_VERSION_C(major, minor, patch);
    return a_version_cmp(&inner, &outer);
}

int a_version_cmp(a_version_s const *const lhs, a_version_s const *const rhs)
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

#include <stdlib.h>

unsigned int a_version_parse(a_version_s *const ctx, char const *const ver)
{
    union
    {
        char const *p;
        char *s;
    } u = {ver};
    ctx->major = 0;
    ctx->minor = 0;
    ctx->patch = 0;
    if (ver)
    {
        ctx->major = (unsigned int)strtoul(u.p, &u.s, 0);
        if (u.p[0] == '.' && u.p[1] >= '0' && u.p[1] <= '9')
        {
            ++u.p;
        }
        else
        {
            goto done;
        }
        ctx->minor = (unsigned int)strtoul(u.p, &u.s, 0);
        if (u.p[0] == '.' && u.p[1] >= '0' && u.p[1] <= '9')
        {
            ++u.p;
        }
        else
        {
            goto done;
        }
        ctx->patch = (unsigned int)strtoul(u.p, &u.s, 0);
    done:
        return (unsigned int)(u.p - ver);
    }
    return 0;
}
