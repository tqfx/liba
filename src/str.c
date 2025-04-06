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
    A_ASSUME(ctx->ptr_);
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

#include "a/utf.h"

a_size a_str_utflen(a_str const *ctx)
{
    a_size length = 0;
    if (ctx->num_)
    {
        char const *head = ctx->ptr_;
        char const *const tail = head + ctx->num_;
        unsigned int offset = a_utf_decode(head, A_NULL);
        for (; offset; offset = a_utf_decode(head, A_NULL))
        {
            ++length;
            head += offset;
            if (head >= tail) { break; }
        }
    }
    return length;
}
