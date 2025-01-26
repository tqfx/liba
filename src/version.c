#if !defined _GNU_SOURCE && defined(__linux__)
#define _GNU_SOURCE /* NOLINT */
#endif /* _GNU_SOURCE */
#include "a/version.h"

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
    if (lhs->major < rhs->major) { return 1; }
    if (lhs->major > rhs->major) { return 0; }
    if (lhs->minor < rhs->minor) { return 1; }
    if (lhs->minor > rhs->minor) { return 0; }
    if (lhs->third < rhs->third) { return 1; }
    if (lhs->third > rhs->third) { return 0; }
    return 0;
}

a_bool a_version_gt(a_version const *lhs, a_version const *rhs)
{
    if (lhs->major > rhs->major) { return 1; }
    if (lhs->major < rhs->major) { return 0; }
    if (lhs->minor > rhs->minor) { return 1; }
    if (lhs->minor < rhs->minor) { return 0; }
    if (lhs->third > rhs->third) { return 1; }
    if (lhs->third < rhs->third) { return 0; }
    return 0;
}

a_bool a_version_le(a_version const *lhs, a_version const *rhs)
{
    if (lhs->major < rhs->major) { return 1; }
    if (lhs->major > rhs->major) { return 0; }
    if (lhs->minor < rhs->minor) { return 1; }
    if (lhs->minor > rhs->minor) { return 0; }
    if (lhs->third < rhs->third) { return 1; }
    if (lhs->third > rhs->third) { return 0; }
    return 1;
}

a_bool a_version_ge(a_version const *lhs, a_version const *rhs)
{
    if (lhs->major > rhs->major) { return 1; }
    if (lhs->major < rhs->major) { return 0; }
    if (lhs->minor > rhs->minor) { return 1; }
    if (lhs->minor < rhs->minor) { return 0; }
    if (lhs->third > rhs->third) { return 1; }
    if (lhs->third < rhs->third) { return 0; }
    return 1;
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
#if __has_warning("-Wdisabled-macro-expansion")
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
#endif /* -Wdisabled-macro-expansion */

static A_INLINE char const *a_version_set_alpha_(a_version *ctx, char const *alpha)
{
    unsigned int c = 1;
    ctx->alpha_[0] = *alpha;
    for (++alpha; isalpha((a_byte)*alpha); ++alpha)
    {
        if (c < sizeof(ctx->alpha_)) { ctx->alpha_[c++] = *alpha; }
    }
    if (*alpha == '.')
    {
        if (c < sizeof(ctx->alpha_)) { ctx->alpha_[c++] = *alpha; }
        else { ctx->alpha_[c - 1] = *alpha; }
        ++alpha;
    }
    while (c < sizeof(ctx->alpha_)) { ctx->alpha_[c++] = 0; }
    return alpha;
}

void a_version_set_alpha(a_version *ctx, char const *alpha)
{
    if ((*alpha == '.' || *alpha == '-' || *alpha == '+' || isalpha((a_byte)*alpha)) &&
        (isalpha((a_byte)alpha[1]) || !alpha[1])) { a_version_set_alpha_(ctx, alpha); }
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
    if (!isdigit((a_byte)*ver)) { return 0; }
    ctx->minor = ctx->third = ctx->extra = 0;
    ctx->major = (unsigned int)strtoul(u.s, &u.p, 10);
    if (u.s[0] == '.' && u.s[1] >= '0' && u.s[1] <= '9') { ++u.s; }
    else { goto ext; }
    ctx->minor = (unsigned int)strtoul(u.s, &u.p, 10);
    if (u.s[0] == '.' && u.s[1] >= '0' && u.s[1] <= '9') { ++u.s; }
    else { goto ext; }
    ctx->third = (unsigned int)strtoul(u.s, &u.p, 10);
ext:
    if ((u.s[0] == '.' || u.s[0] == '-' || u.s[0] == '+' || isalpha((a_byte)u.s[0])) &&
        (isalnum((a_byte)u.s[1]) || !u.s[1]))
    {
        u.s = a_version_set_alpha_(ctx, u.s);
        if (isdigit((a_byte)u.s[0]))
        {
            ctx->extra = (unsigned int)strtoul(u.s, &u.p, 10);
        }
    }
    return (unsigned int)(u.s - ver);
}

#include <stdio.h>
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define snprintf sprintf_s
#endif /* _MSC_VER */

void a_version_alpha(a_version const *ctx, char alpha[5])
{
    unsigned int c;
    for (c = 0; c < sizeof(ctx->alpha_) && ctx->alpha_[c]; ++c)
    {
        alpha[c] = ctx->alpha_[c];
    }
    alpha[c] = 0;
}

unsigned int a_version_tostr(a_version const *ctx, void *pdata, a_size nbyte)
{
    int n;
    char *p = (char *)pdata;
    char alpha[sizeof(ctx->alpha_) + 1];
    if (ctx->extra || isalpha((a_byte)ctx->alpha_[0]) || isalpha((a_byte)ctx->alpha_[1]))
    {
        a_version_alpha(ctx, alpha);
        n = snprintf(p, nbyte, "%u.%u.%u%s%u",
                     ctx->major, ctx->minor, ctx->third, alpha, ctx->extra);
    }
    else
    {
        n = snprintf(p, nbyte, "%u.%u.%u",
                     ctx->major, ctx->minor, ctx->third);
    }
    return n > 0 ? (unsigned int)n : 0;
}
