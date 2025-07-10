#if !defined _CRT_SECURE_NO_WARNINGS && defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS /* NOLINT */
#endif /* _CRT_SECURE_NO_WARNINGS */
#if !defined _GNU_SOURCE && defined(__linux__)
#define _GNU_SOURCE /* NOLINT */
#endif /* _GNU_SOURCE */
#include "a/str.h"

a_str *a_str_new(void)
{
    a_str *const ctx = (a_str *)a_alloc(A_NULL, sizeof(a_str));
    if (ctx) { a_str_ctor(ctx); }
    return ctx;
}

void a_str_die(a_str *ctx)
{
    if (ctx)
    {
        a_str_dtor(ctx);
        a_alloc(ctx, 0);
    }
}

void a_str_ctor(a_str *ctx)
{
    ctx->ptr_ = A_NULL;
    ctx->num_ = 0;
    ctx->mem_ = 0;
}

void a_str_dtor(a_str *ctx)
{
    if (ctx->ptr_)
    {
        a_alloc(ctx->ptr_, 0);
        ctx->ptr_ = A_NULL;
    }
    ctx->num_ = 0;
    ctx->mem_ = 0;
}

void a_str_swap(a_str *lhs, a_str *rhs)
{
    a_str swap;
    swap = *lhs;
    *lhs = *rhs;
    *rhs = swap;
}

char *a_str_exit(a_str *ctx)
{
    char *const str = ctx->ptr_;
    if (ctx->ptr_)
    {
        ctx->ptr_[ctx->num_] = 0;
        ctx->ptr_ = A_NULL;
    }
    ctx->num_ = 0;
    ctx->mem_ = 0;
    return str;
}

int a_str_setm_(a_str *ctx, a_size mem)
{
    char *ptr;
    mem = a_size_up(sizeof(void *), mem);
    ptr = (char *)a_alloc(ctx->ptr_, mem);
    if (ptr || mem == 0)
    {
        ctx->ptr_ = ptr;
        ctx->mem_ = mem;
        return A_SUCCESS;
    }
    return A_OMEMORY;
}

int a_str_setm(a_str *ctx, a_size mem)
{
    if (mem > ctx->mem_)
    {
        return a_str_setm_(ctx, mem);
    }
    return A_SUCCESS;
}

int a_str_cmp_(void const *p0, a_size n0, void const *p1, a_size n1)
{
    if (p0 && p1)
    {
        int rc = memcmp(p0, p1, A_MIN(n0, n1));
        if (rc) { return rc; }
    }
    return (n0 > n1) - (n0 < n1);
}

int a_str_cmp(a_str const *ctx, a_str const *str)
{
    return a_str_cmp_(ctx->ptr_, ctx->num_, str->ptr_, str->num_);
}

int a_str_cmpn(a_str const *ctx, void const *pdata, a_size nbyte)
{
    return a_str_cmp_(ctx->ptr_, ctx->num_, pdata, nbyte);
}

int a_str_cmps(a_str const *ctx, void const *str)
{
    return a_str_cmp_(ctx->ptr_, ctx->num_, str, strlen((char const *)str));
}

int a_str_getc_(a_str *ctx)
{
    int c = ~0;
    if (ctx->num_)
    {
        c = (int)ctx->ptr_[--ctx->num_];
    }
    return c;
}

int a_str_getc(a_str *ctx)
{
    int c = ~0;
    if (ctx->num_)
    {
        c = (int)ctx->ptr_[--ctx->num_];
        ctx->ptr_[ctx->num_] = 0;
    }
    return c;
}

int a_str_catc_(a_str *ctx, int c)
{
    if (a_str_setm(ctx, ctx->num_ + 1) == 0)
    {
        ctx->ptr_[ctx->num_++] = (char)c;
        return c;
    }
    return ~0;
}

int a_str_catc(a_str *ctx, int c)
{
    if (a_str_setm(ctx, ctx->num_ + 2) == 0)
    {
        ctx->ptr_[ctx->num_++] = (char)c;
        ctx->ptr_[ctx->num_] = 0;
        return c;
    }
    return ~0;
}

a_size a_str_getn_(a_str *ctx, void *pdata, a_size nbyte)
{
    if (nbyte > ctx->num_) { nbyte = ctx->num_; }
    if (nbyte)
    {
        ctx->num_ -= nbyte;
        if (pdata) { a_copy(pdata, ctx->ptr_ + ctx->num_, nbyte); }
    }
    return nbyte;
}

a_size a_str_getn(a_str *ctx, void *pdata, a_size nbyte)
{
    if (nbyte > ctx->num_) { nbyte = ctx->num_; }
    if (nbyte)
    {
        ctx->num_ -= nbyte;
        if (pdata) { a_copy(pdata, ctx->ptr_ + ctx->num_, nbyte); }
        ctx->ptr_[ctx->num_] = 0;
    }
    return nbyte;
}

int a_str_catn_(a_str *ctx, void const *pdata, a_size nbyte)
{
    int rc = a_str_setm(ctx, ctx->num_ + nbyte);
    if (rc == 0 && nbyte)
    {
        a_copy(ctx->ptr_ + ctx->num_, pdata, nbyte);
        ctx->num_ += nbyte;
    }
    return rc;
}

int a_str_catn(a_str *ctx, void const *pdata, a_size nbyte)
{
    int rc = a_str_setm(ctx, ctx->num_ + nbyte + 1);
    if (rc == 0)
    {
        if (nbyte)
        {
            a_copy(ctx->ptr_ + ctx->num_, pdata, nbyte);
            ctx->num_ += nbyte;
        }
        ctx->ptr_[ctx->num_] = 0;
    }
    return rc;
}

int a_str_cats_(a_str *ctx, void const *str)
{
    return a_str_catn_(ctx, str, strlen((char const *)str));
}
int a_str_cats(a_str *ctx, void const *str)
{
    return a_str_catn(ctx, str, strlen((char const *)str));
}

int a_str_cat_(a_str *ctx, a_str const *obj)
{
    return a_str_catn_(ctx, obj->ptr_, obj->num_);
}
int a_str_cat(a_str *ctx, a_str const *obj)
{
    return a_str_catn(ctx, obj->ptr_, obj->num_);
}

#if !defined va_copy && \
    (A_PREREQ_GNUC(3, 0) || __has_builtin(__builtin_va_copy))
#define va_copy(d, s) __builtin_va_copy(d, s)
#elif !defined va_copy
#define va_copy(d, s) ((d) = (s))
#endif /* va_copy */
#include <stdio.h>

int a_str_catv(a_str *ctx, char const *fmt, va_list va)
{
    int res;
    va_list ap;
    a_size mem;
    char *ptr = ctx->ptr_;
    if (ptr) { ptr += ctx->num_; }
    mem = ctx->mem_ - ctx->num_;
    va_copy(ap, va);
    res = vsnprintf(ptr, mem, fmt, ap);
    va_end(ap);
    mem = ctx->num_ + (a_size)(res + 1);
    if (mem > ctx->mem_)
    {
        if (A_UNLIKELY(a_str_setm_(ctx, mem))) { return 0; }
        ptr = ctx->ptr_ + ctx->num_;
        mem = ctx->mem_ - ctx->num_;
        res = vsnprintf(ptr, mem, fmt, va);
    }
    if (res > 0) { ctx->num_ += (a_size)res; }
    return res;
}

int a_str_catf(a_str *ctx, char const *fmt, ...)
{
    int res;
    va_list va;
    va_start(va, fmt);
    res = a_str_catv(ctx, fmt, va);
    va_end(va);
    return res;
}

#include <ctype.h>

void a_str_rtrim_(a_str *ctx, char const *s, a_size n)
{
    char const *const p = ctx->ptr_;
    a_size i = ctx->num_ - 1;
    if (n)
    {
        while (ctx->num_ && memchr(s, p[i], n))
        {
            ctx->num_ = i--;
        }
    }
    else
    {
        while (ctx->num_ && isspace(p[i]))
        {
            ctx->num_ = i--;
        }
    }
}
void a_str_rtrim(a_str *ctx, char const *s, a_size n)
{
    a_size const num = ctx->num_;
    a_str_rtrim_(ctx, s, n);
    if (ctx->num_ < num)
    {
        ctx->ptr_[ctx->num_] = 0;
    }
}

void a_str_ltrim_(a_str *ctx, char const *s, a_size n)
{
    char const *p = ctx->ptr_;
    a_size i = 0;
    if (n)
    {
        for (; i < ctx->num_ && memchr(s, *p, n); ++i) { ++p; }
    }
    else
    {
        for (; i < ctx->num_ && isspace(*p); ++i) { ++p; }
    }
    if (i)
    {
        a_size const num = ctx->num_ - i;
        a_move(ctx->ptr_, p, num);
        ctx->num_ = num;
    }
}
void a_str_ltrim(a_str *ctx, char const *s, a_size n)
{
    a_size const num = ctx->num_;
    a_str_ltrim_(ctx, s, n);
    if (ctx->num_ < num)
    {
        ctx->ptr_[ctx->num_] = 0;
    }
}

void a_str_trim_(a_str *ctx, char const *s, a_size n)
{
    a_str_rtrim_(ctx, s, n);
    a_str_ltrim_(ctx, s, n);
}
void a_str_trim(a_str *ctx, char const *s, a_size n)
{
    a_size const num = ctx->num_;
    a_str_trim_(ctx, s, n);
    if (ctx->num_ < num)
    {
        ctx->ptr_[ctx->num_] = 0;
    }
}

#include "a/utf.h"

a_size a_utf_len(a_str const *ctx, a_size *stop)
{
    return a_utf_length(ctx->ptr_, ctx->num_, stop);
}

int a_utf_catc(a_str *ctx, a_u32 c)
{
    int rc = a_str_setm(ctx, ctx->num_ + 7);
    if (rc == 0)
    {
        char *const p = ctx->ptr_ + ctx->num_;
        a_size const n = a_utf_encode(c, p);
        ctx->num_ += n;
        p[n] = 0;
    }
    return rc;
}
