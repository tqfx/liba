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

int a_str_copy(a_str *ctx, a_str const *obj)
{
    int ok;
    a_str_ctor(ctx);
    ok = a_str_alloc_(ctx, obj->num_ + 1);
    if (ok == A_SUCCESS)
    {
        if (obj->num_) { a_copy(ctx->ptr_, obj->ptr_, obj->num_); }
        ctx->ptr_[obj->num_] = 0;
        ctx->num_ = obj->num_;
    }
    return ok;
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

int a_str_alloc_(a_str *ctx, a_size mem)
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
    return A_FAILURE;
}

int a_str_alloc(a_str *ctx, a_size mem)
{
    if (mem > ctx->mem_)
    {
        return a_str_alloc_(ctx, mem);
    }
    return A_SUCCESS;
}

int a_str_cmpn(a_str const *ctx, void const *pdata, a_size nbyte)
{
    int ok;
    if (ctx->ptr_ && pdata)
    {
        ok = memcmp(ctx->ptr_, pdata, A_MIN(ctx->num_, nbyte));
        if (ok) { return ok; }
    }
    if (ctx->num_ == nbyte) { return 0; }
    return ctx->num_ < nbyte ? -1 : +1;
}

int a_str_cmps(a_str const *ctx, void const *str)
{
    return a_str_cmpn(ctx, str, strlen((char const *)str));
}

int a_str_cmp(a_str const *ctx, a_str const *str)
{
    return a_str_cmpn(ctx, str->ptr_, str->num_);
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
    if (a_str_alloc(ctx, ctx->num_ + 1) == A_SUCCESS)
    {
        ctx->ptr_[ctx->num_++] = (char)c;
        return c;
    }
    return ~0;
}

int a_str_putc(a_str *ctx, int c)
{
    if (a_str_alloc(ctx, ctx->num_ + 2) == A_SUCCESS)
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

int a_str_setn_(a_str *ctx, void const *pdata, a_size nbyte)
{
    int ok = a_str_alloc(ctx, nbyte);
    if (ok == A_SUCCESS && nbyte)
    {
        a_copy(ctx->ptr_, pdata, nbyte);
        ctx->num_ = nbyte;
    }
    return ok;
}

int a_str_putn_(a_str *ctx, void const *pdata, a_size nbyte)
{
    int ok = a_str_alloc(ctx, ctx->num_ + nbyte);
    if (ok == A_SUCCESS && nbyte)
    {
        a_copy(ctx->ptr_ + ctx->num_, pdata, nbyte);
        ctx->num_ += nbyte;
    }
    return ok;
}

int a_str_setn(a_str *ctx, void const *pdata, a_size nbyte)
{
    int ok = a_str_alloc(ctx, nbyte + 1);
    if (ok == A_SUCCESS)
    {
        if (nbyte) { a_copy(ctx->ptr_, pdata, nbyte); }
        ctx->ptr_[nbyte] = 0;
        ctx->num_ = nbyte;
    }
    return ok;
}

int a_str_putn(a_str *ctx, void const *pdata, a_size nbyte)
{
    int ok = a_str_alloc(ctx, ctx->num_ + nbyte + 1);
    if (ok == A_SUCCESS)
    {
        if (nbyte)
        {
            a_copy(ctx->ptr_ + ctx->num_, pdata, nbyte);
            ctx->num_ += nbyte;
        }
        ctx->ptr_[ctx->num_] = 0;
    }
    return ok;
}

int a_str_sets_(a_str *ctx, void const *str)
{
    return a_str_setn_(ctx, str, strlen((char const *)str));
}
int a_str_sets(a_str *ctx, void const *str)
{
    return a_str_setn(ctx, str, strlen((char const *)str));
}

int a_str_puts_(a_str *ctx, void const *str)
{
    return a_str_putn_(ctx, str, strlen((char const *)str));
}
int a_str_puts(a_str *ctx, void const *str)
{
    return a_str_putn(ctx, str, strlen((char const *)str));
}

int a_str_set_(a_str *ctx, a_str const *obj)
{
    return a_str_setn_(ctx, obj->ptr_, obj->num_);
}
int a_str_set(a_str *ctx, a_str const *obj)
{
    return a_str_setn(ctx, obj->ptr_, obj->num_);
}

int a_str_put_(a_str *ctx, a_str const *obj)
{
    return a_str_putn_(ctx, obj->ptr_, obj->num_);
}
int a_str_put(a_str *ctx, a_str const *obj)
{
    return a_str_putn(ctx, obj->ptr_, obj->num_);
}

#include <stdio.h>

int a_str_setv(a_str *ctx, char const *fmt, va_list va)
{
    int res;
    va_list ap;
    va_copy(ap, va);
    res = vsnprintf(ctx->ptr_, ctx->mem_, fmt, ap);
    va_end(ap);
    if ((a_size)res + 1 > ctx->mem_)
    {
        if (A_UNLIKELY(a_str_alloc_(ctx, (a_size)res + 1))) { return 0; }
        va_copy(ap, va);
        res = vsnprintf(ctx->ptr_, ctx->mem_, fmt, ap);
        va_end(ap);
    }
    if (res >= 0) { ctx->num_ = (a_size)res; }
    return res;
}

int a_str_putv(a_str *ctx, char const *fmt, va_list va)
{
    int res;
    va_list ap;
    a_size mem;
    char *ptr = ctx->ptr_ ? ctx->ptr_ + ctx->num_ : ctx->ptr_;
    va_copy(ap, va);
    mem = ctx->mem_ - ctx->num_;
    res = vsnprintf(ptr, mem, fmt, ap);
    mem = ctx->num_ + (a_size)(res + 1);
    va_end(ap);
    if (mem > ctx->mem_)
    {
        if (A_UNLIKELY(a_str_alloc_(ctx, mem))) { return 0; }
        va_copy(ap, va);
        ptr = ctx->ptr_ + ctx->num_;
        mem = ctx->mem_ - ctx->num_;
        res = vsnprintf(ptr, mem, fmt, ap);
        va_end(ap);
    }
    if (res > 0) { ctx->num_ += (a_size)res; }
    return res;
}

int a_str_setf(a_str *ctx, char const *fmt, ...)
{
    int res;
    va_list va;
    va_start(va, fmt);
    res = a_str_setv(ctx, fmt, va);
    va_end(va);
    return res;
}

int a_str_putf(a_str *ctx, char const *fmt, ...)
{
    int res;
    va_list va;
    va_start(va, fmt);
    res = a_str_putv(ctx, fmt, va);
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
