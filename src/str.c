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
    ctx->_ptr = A_NULL;
    ctx->_num = 0;
    ctx->_mem = 0;
}

void a_str_dtor(a_str *ctx)
{
    if (ctx->_ptr)
    {
        a_alloc(ctx->_ptr, 0);
        ctx->_ptr = A_NULL;
    }
    ctx->_num = 0;
    ctx->_mem = 0;
}

int a_str_init(a_str *ctx, void const *pdata, a_size nbyte)
{
    ctx->_num = nbyte;
    ctx->_mem = ctx->_num + 1;
    ctx->_mem = a_size_up(sizeof(void *), ctx->_mem);
    ctx->_ptr = (char *)a_alloc(A_NULL, ctx->_mem);
    if (a_unlikely(!ctx->_ptr)) { return A_FAILURE; }
    if (pdata && nbyte)
    {
        a_copy(ctx->_ptr, pdata, nbyte);
    }
    ctx->_ptr[ctx->_num] = 0;
    return A_SUCCESS;
}

int a_str_copy(a_str *ctx, a_str const *obj)
{
    return a_str_init(ctx, obj->_ptr, obj->_num);
}

void a_str_move(a_str *ctx, a_str *obj)
{
    a_copy(ctx, obj, sizeof(*obj));
    a_zero(obj, sizeof(*obj));
}

char *a_str_exit(a_str *ctx)
{
    char *const str = ctx->_ptr;
    if (ctx->_ptr)
    {
        ctx->_ptr[ctx->_num] = 0;
        ctx->_ptr = A_NULL;
    }
    ctx->_num = 0;
    ctx->_mem = 0;
    return str;
}

int a_str_cmp(a_str const *lhs, a_str const *rhs)
{
    int ok = 0;
    if (lhs->_ptr && rhs->_ptr)
    {
        ok = memcmp(lhs->_ptr, rhs->_ptr, A_MIN(lhs->_num, rhs->_num));
        if (ok) { return ok; }
    }
    if (lhs->_num == rhs->_num) { return 0; }
    return lhs->_num < rhs->_num ? -1 : +1;
}

int a_str_alloc_(a_str *ctx, a_size mem)
{
    char *ptr;
    mem = a_size_up(sizeof(void *), mem);
    ptr = (char *)a_alloc(ctx->_ptr, mem);
    if (a_unlikely(!ptr && mem)) { return A_FAILURE; }
    ctx->_ptr = ptr;
    ctx->_mem = mem;
    return A_SUCCESS;
}

int a_str_alloc(a_str *ctx, a_size mem)
{
    return ctx->_mem < mem ? a_str_alloc_(ctx, mem) : A_SUCCESS;
}

int a_str_getc_(a_str *ctx)
{
    int c = ~0;
    if (ctx->_num)
    {
        c = (int)ctx->_ptr[--ctx->_num];
    }
    return c;
}

int a_str_getc(a_str *ctx)
{
    int c = ~0;
    if (ctx->_num)
    {
        c = (int)ctx->_ptr[--ctx->_num];
        ctx->_ptr[ctx->_num] = 0;
    }
    return c;
}

int a_str_putc_(a_str *ctx, int c)
{
    if (a_unlikely(a_str_alloc(ctx, ctx->_num + 1))) { return ~0; }
    ctx->_ptr[ctx->_num++] = (char)c;
    return c;
}

int a_str_putc(a_str *ctx, int c)
{
    if (a_unlikely(a_str_alloc(ctx, ctx->_num + 2))) { return ~0; }
    ctx->_ptr[ctx->_num++] = (char)c;
    ctx->_ptr[ctx->_num] = 0;
    return c;
}

a_size a_str_getn_(a_str *ctx, void *pdata, a_size nbyte)
{
    if (nbyte > ctx->_num) { nbyte = ctx->_num; }
    if (pdata && nbyte)
    {
        ctx->_num -= nbyte;
        a_copy(pdata, ctx->_ptr + ctx->_num, nbyte);
    }
    return nbyte;
}

a_size a_str_getn(a_str *ctx, void *pdata, a_size nbyte)
{
    if (nbyte > ctx->_num) { nbyte = ctx->_num; }
    if (pdata && nbyte)
    {
        ctx->_num -= nbyte;
        a_copy(pdata, ctx->_ptr + ctx->_num, nbyte);
        ctx->_ptr[ctx->_num] = 0;
    }
    return nbyte;
}

int a_str_putn_(a_str *ctx, void const *pdata, a_size nbyte)
{
    if (pdata && nbyte)
    {
        if (a_unlikely(a_str_alloc(ctx, ctx->_num + nbyte))) { return A_FAILURE; }
        a_copy(ctx->_ptr + ctx->_num, pdata, nbyte);
        ctx->_num += nbyte;
    }
    return A_SUCCESS;
}

int a_str_putn(a_str *ctx, void const *pdata, a_size nbyte)
{
    if (pdata && nbyte)
    {
        if (a_unlikely(a_str_alloc(ctx, ctx->_num + nbyte + 1))) { return A_FAILURE; }
        a_copy(ctx->_ptr + ctx->_num, pdata, nbyte);
        ctx->_num += nbyte;
        ctx->_ptr[ctx->_num] = 0;
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
    return a_str_putn_(ctx, obj->_ptr, obj->_num);
}

int a_str_cat(a_str *ctx, a_str const *obj)
{
    return a_str_putn(ctx, obj->_ptr, obj->_num);
}

#include <stdio.h>

int a_str_putf_(a_str *ctx, char const *fmt, va_list va)
{
    int res;
    va_list ap;
    a_size mem;
    char *ptr = ctx->_ptr ? ctx->_ptr + ctx->_num : ctx->_ptr;
    va_copy(ap, va);
    mem = ctx->_mem - ctx->_num;
    res = vsnprintf(ptr, mem, fmt, ap);
    mem = ctx->_num + (size_t)(res + 1);
    va_end(ap);
    if (mem > ctx->_mem)
    {
        if (a_unlikely(a_str_alloc_(ctx, mem))) { return 0; }
        va_copy(ap, va);
        ptr = ctx->_ptr + ctx->_num;
        mem = ctx->_mem - ctx->_num;
        res = vsnprintf(ptr, mem, fmt, ap);
        va_end(ap);
    }
    if (res > 0) { ctx->_num += (size_t)res; }
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
    if (ctx->_num)
    {
        char const *head = ctx->_ptr;
        char const *const tail = head + ctx->_num;
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
