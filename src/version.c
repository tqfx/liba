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
    outer.major = major;
    outer.minor = minor;
    outer.third = patch;
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

#include <ctype.h>

static A_INLINE char const *a_version_set_alpha_(a_version *ctx, char const *alpha)
{
    unsigned int c = 1;
    ctx->alpha[0] = *alpha;
    for (++alpha; isalpha(*alpha); ++alpha)
    {
        if (c < sizeof(ctx->alpha)) { ctx->alpha[c++] = *alpha; }
    }
    if (*alpha == '.')
    {
        if (c < sizeof(ctx->alpha)) { ctx->alpha[c++] = *alpha; }
        else { ctx->alpha[c - 1] = *alpha; }
        ++alpha;
    }
    while (c < sizeof(ctx->alpha)) { ctx->alpha[c++] = 0; }
    return alpha;
}

#include <stdlib.h>

void a_version_set_alpha(a_version *ctx, char const *alpha)
{
    if ((*alpha == '.' || *alpha == '-' || *alpha == '+' || isalpha(*alpha)) &&
        (isalpha(alpha[1]) || !alpha[1])) { a_version_set_alpha_(ctx, alpha); }
}

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
    if ((u.s[0] == '.' || u.s[0] == '-' || u.s[0] == '+' || isalpha(u.s[0])) &&
        (isalnum(u.s[1]) || !u.s[1])) { u.s = a_version_set_alpha_(ctx, u.s); }
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

#include <stdio.h>
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define snprintf sprintf_s
#endif /* _MSC_VER */

void a_version_alpha(a_version const *ctx, char alpha[5])
{
    unsigned int c;
    for (c = 0; ctx->alpha[c] && c < sizeof(ctx->alpha); ++c)
    {
        alpha[c] = ctx->alpha[c];
    }
    alpha[c] = 0;
}

int a_version_tostr(a_version const *ctx, void *pdata, a_size nbyte)
{
    char *p = (char *)pdata;
    char alpha[sizeof(ctx->alpha) + 1];
    if (ctx->extra || isalpha(ctx->alpha[0]) || isalpha(ctx->alpha[1]))
    {
        a_version_alpha(ctx, alpha);
        return snprintf(p, nbyte, "%u.%u.%u%s%u",
                        ctx->major, ctx->minor, ctx->third, alpha, ctx->extra);
    }
    return snprintf(p, nbyte, "%u.%u.%u", ctx->major, ctx->minor, ctx->third);
}
