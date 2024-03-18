#if defined(_MSC_VER)
#if !defined _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS /* NOLINT */
#endif /* _CRT_SECURE_NO_WARNINGS */
#endif /* _MSC_VER */
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

int a_str_init(a_str *ctx, void const *pdata, a_size nbyte)
{
    ctx->num_ = nbyte;
    ctx->mem_ = ctx->num_ + 1;
    ctx->mem_ = a_size_up(sizeof(void *), ctx->mem_);
    ctx->ptr_ = (char *)a_alloc(A_NULL, ctx->mem_);
    if (a_unlikely(!ctx->ptr_)) { return A_FAILURE; }
    if (pdata && nbyte)
    {
        a_copy(ctx->ptr_, pdata, nbyte);
    }
    ctx->ptr_[ctx->num_] = 0;
    return A_SUCCESS;
}

int a_str_copy(a_str *ctx, a_str const *obj)
{
    return a_str_init(ctx, obj->ptr_, obj->num_);
}

void a_str_move(a_str *ctx, a_str *obj)
{
    a_copy(ctx, obj, sizeof(*obj));
    a_zero(obj, sizeof(*obj));
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

int a_str_cmp(a_str const *lhs, a_str const *rhs)
{
    int ok = 0;
    if (lhs->ptr_ && rhs->ptr_)
    {
        ok = memcmp(lhs->ptr_, rhs->ptr_, A_MIN(lhs->num_, rhs->num_));
        if (ok) { return ok; }
    }
    if (lhs->num_ == rhs->num_) { return 0; }
    return lhs->num_ < rhs->num_ ? -1 : +1;
}

int a_str_alloc_(a_str *ctx, a_size mem)
{
    char *ptr;
    mem = a_size_up(sizeof(void *), mem);
    ptr = (char *)a_alloc(ctx->ptr_, mem);
    if (a_unlikely(!ptr && mem)) { return A_FAILURE; }
    ctx->ptr_ = ptr;
    ctx->mem_ = mem;
    return A_SUCCESS;
}

int a_str_alloc(a_str *ctx, a_size mem)
{
    return ctx->mem_ < mem ? a_str_alloc_(ctx, mem) : A_SUCCESS;
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

int a_str_putc_(a_str *ctx, int c)
{
    if (a_unlikely(a_str_alloc(ctx, ctx->num_ + 1))) { return ~0; }
    ctx->ptr_[ctx->num_++] = (char)c;
    return c;
}

int a_str_putc(a_str *ctx, int c)
{
    if (a_unlikely(a_str_alloc(ctx, ctx->num_ + 2))) { return ~0; }
    ctx->ptr_[ctx->num_++] = (char)c;
    ctx->ptr_[ctx->num_] = 0;
    return c;
}

a_size a_str_getn_(a_str *ctx, void *pdata, a_size nbyte)
{
    if (nbyte > ctx->num_) { nbyte = ctx->num_; }
    if (pdata && nbyte)
    {
        ctx->num_ -= nbyte;
        a_copy(pdata, ctx->ptr_ + ctx->num_, nbyte);
    }
    return nbyte;
}

a_size a_str_getn(a_str *ctx, void *pdata, a_size nbyte)
{
    if (nbyte > ctx->num_) { nbyte = ctx->num_; }
    if (pdata && nbyte)
    {
        ctx->num_ -= nbyte;
        a_copy(pdata, ctx->ptr_ + ctx->num_, nbyte);
        ctx->ptr_[ctx->num_] = 0;
    }
    return nbyte;
}

int a_str_putn_(a_str *ctx, void const *pdata, a_size nbyte)
{
    if (pdata && nbyte)
    {
        if (a_unlikely(a_str_alloc(ctx, ctx->num_ + nbyte))) { return A_FAILURE; }
        a_copy(ctx->ptr_ + ctx->num_, pdata, nbyte);
        ctx->num_ += nbyte;
    }
    return A_SUCCESS;
}

int a_str_putn(a_str *ctx, void const *pdata, a_size nbyte)
{
    if (pdata && nbyte)
    {
        if (a_unlikely(a_str_alloc(ctx, ctx->num_ + nbyte + 1))) { return A_FAILURE; }
        a_copy(ctx->ptr_ + ctx->num_, pdata, nbyte);
        ctx->num_ += nbyte;
        ctx->ptr_[ctx->num_] = 0;
    }
    return A_SUCCESS;
}

int a_str_puts_(a_str *ctx, void const *str)
{
    return a_str_putn_(ctx, str, strlen((char const *)str));
}

int a_str_puts(a_str *ctx, void const *str)
{
    return a_str_putn(ctx, str, strlen((char const *)str));
}

int a_str_cat_(a_str *ctx, a_str const *obj)
{
    return a_str_putn_(ctx, obj->ptr_, obj->num_);
}

int a_str_cat(a_str *ctx, a_str const *obj)
{
    return a_str_putn(ctx, obj->ptr_, obj->num_);
}

#include <stdio.h>

int a_str_putf_(a_str *ctx, char const *fmt, va_list va)
{
    int res;
    va_list ap;
    a_size mem;
    char *ptr = ctx->ptr_ ? ctx->ptr_ + ctx->num_ : ctx->ptr_;
    va_copy(ap, va);
    mem = ctx->mem_ - ctx->num_;
    res = vsnprintf(ptr, mem, fmt, ap);
    mem = ctx->num_ + (size_t)(res + 1);
    va_end(ap);
    if (mem > ctx->mem_)
    {
        if (a_unlikely(a_str_alloc_(ctx, mem))) { return 0; }
        va_copy(ap, va);
        ptr = ctx->ptr_ + ctx->num_;
        mem = ctx->mem_ - ctx->num_;
        res = vsnprintf(ptr, mem, fmt, ap);
        va_end(ap);
    }
    if (res > 0) { ctx->num_ += (size_t)res; }
    return res;
}

int a_str_putf(a_str *ctx, char const *fmt, ...)
{
    int res;
    va_list va;
    va_start(va, fmt);
    res = a_str_putf_(ctx, fmt, va);
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
