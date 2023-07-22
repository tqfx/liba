#if defined(_MSC_VER)
#if !defined _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // NOLINT
#endif /* _CRT_SECURE_NO_WARNINGS */
#endif /* _MSC_VER */
#include "a/host/str.h"

a_str_s *a_str_new(void)
{
    a_str_s *const ctx = (a_str_s *)a_alloc(A_NULL, sizeof(a_str_s));
    if (ctx)
    {
        a_str_ctor(ctx);
    }
    return ctx;
}

void a_str_die(a_str_s *const ctx)
{
    if (ctx)
    {
        a_str_dtor(ctx);
        a_alloc(ctx, 0);
    }
}

void a_str_ctor(a_str_s *const ctx)
{
    ctx->_ptr = A_NULL;
    ctx->_num = 0;
    ctx->_mem = 0;
}

void a_str_dtor(a_str_s *const ctx)
{
    if (ctx->_ptr)
    {
        a_alloc(ctx->_ptr, 0);
        ctx->_ptr = NULL;
    }
    ctx->_num = 0;
    ctx->_mem = 0;
}

int a_str_init(a_str_s *const ctx, void const *const pdata, a_size_t const nbyte)
{
    ctx->_num = nbyte;
    ctx->_mem = nbyte + 1;
    ctx->_mem = a_size_up(sizeof(void *), ctx->_mem);
    ctx->_ptr = (char *)a_alloc(A_NULL, ctx->_mem);
    if (a_unlikely(ctx->_ptr == A_NULL))
    {
        return A_FAILURE;
    }
    if (pdata && nbyte)
    {
        a_copy(ctx->_ptr, pdata, nbyte);
    }
    ctx->_ptr[ctx->_num] = 0;
    return A_SUCCESS;
}

int a_str_copy(a_str_s *const ctx, a_str_s const *const obj)
{
    return a_str_init(ctx, obj->_ptr, obj->_num);
}

a_str_s *a_str_move(a_str_s *const ctx, a_str_s *const obj)
{
    a_copy(ctx, obj, sizeof(*obj));
    a_zero(obj, sizeof(*obj));
    return ctx;
}

char *a_str_exit(a_str_s *const ctx)
{
    char *const str = ctx->_ptr;
    if (ctx->_ptr)
    {
        ctx->_ptr[ctx->_num] = 0;
        ctx->_ptr = A_NULL;
    }
    ctx->_mem = 0;
    ctx->_num = 0;
    return str;
}

int a_str_cmp(a_str_s const *const lhs, a_str_s const *const rhs)
{
    int ok = 0;
    if (lhs->_ptr && rhs->_ptr)
    {
        ok = memcmp(lhs->_ptr, rhs->_ptr, A_MIN(lhs->_num, rhs->_num));
    }
    if (ok)
    {
        return ok;
    }
    if (lhs->_num == rhs->_num)
    {
        return 0;
    }
    return lhs->_num < rhs->_num ? -1 : +1;
}

int a_str_alloc_(a_str_s *const ctx, a_size_t mem)
{
    char *str;
    mem = a_size_up(sizeof(void *), mem);
    str = (char *)a_alloc(ctx->_ptr, mem);
    if (a_unlikely(!str && mem))
    {
        return A_FAILURE;
    }
    ctx->_ptr = str;
    ctx->_mem = mem;
    return A_SUCCESS;
}

int a_str_alloc(a_str_s *const ctx, a_size_t const mem)
{
    return ctx->_mem < mem ? a_str_alloc_(ctx, mem) : A_SUCCESS;
}

#include <stdio.h>

int a_str_getc_(a_str_s *const ctx)
{
    int c = EOF;
    if (ctx->_num)
    {
        c = (int)ctx->_ptr[--ctx->_num];
    }
    return c;
}

int a_str_getc(a_str_s *const ctx)
{
    int c = EOF;
    if (ctx->_num)
    {
        c = (int)ctx->_ptr[--ctx->_num];
        ctx->_ptr[ctx->_num] = 0;
    }
    return c;
}

int a_str_putc_(a_str_s *const ctx, int const c)
{
    if (a_unlikely(a_str_alloc(ctx, ctx->_num + 1)))
    {
        return EOF;
    }
    ctx->_ptr[ctx->_num++] = (char)c;
    return c;
}

int a_str_putc(a_str_s *const ctx, int const c)
{
    if (a_unlikely(a_str_alloc(ctx, ctx->_num + 2)))
    {
        return EOF;
    }
    ctx->_ptr[ctx->_num++] = (char)c;
    ctx->_ptr[ctx->_num] = 0;
    return c;
}

int a_str_putn_(a_str_s *const ctx, void const *const pdata, a_size_t const nbyte)
{
    if (pdata && nbyte)
    {
        if (a_unlikely(a_str_alloc(ctx, ctx->_num + nbyte)))
        {
            return A_FAILURE;
        }
        a_copy(ctx->_ptr + ctx->_num, pdata, nbyte);
        ctx->_num += nbyte;
    }
    return A_SUCCESS;
}

int a_str_putn(a_str_s *const ctx, void const *const pdata, a_size_t const nbyte)
{
    if (pdata)
    {
        if (a_unlikely(a_str_alloc(ctx, ctx->_num + nbyte + 1)))
        {
            return A_FAILURE;
        }
        if (nbyte)
        {
            a_copy(ctx->_ptr + ctx->_num, pdata, nbyte);
            ctx->_num += nbyte;
        }
        ctx->_ptr[ctx->_num] = 0;
    }
    return A_SUCCESS;
}

int a_str_puts(a_str_s *const ctx, void const *const str)
{
    return a_str_putn(ctx, str, strlen((char const *)str));
}

int a_str_cat(a_str_s *const ctx, a_str_s const *const obj)
{
    return a_str_putn(ctx, obj->_ptr, obj->_num);
}

int a_str_vprintf(a_str_s *const ctx, char const *const fmt, va_list va)
{
    a_size_t siz;
    a_size_t mem;
    char *str;
    int num;
    va_list ap;
    va_copy(ap, va);
    mem = ctx->_mem - ctx->_num;
    str = ctx->_ptr ? ctx->_ptr + ctx->_num : A_NULL;
    num = vsnprintf(str, mem, fmt, ap);
    va_end(ap);
    siz = (a_size_t)num + 1;
    if (siz > mem)
    {
        if (a_unlikely(a_str_alloc_(ctx, ctx->_num + siz)))
        {
            return EOF;
        }
        va_copy(ap, va);
        mem = ctx->_mem - ctx->_num;
        str = ctx->_ptr + ctx->_num;
        num = vsnprintf(str, mem, fmt, ap);
        va_end(ap);
    }
    ctx->_num += (a_size_t)num;
    return num;
}

int a_str_printf(a_str_s *const ctx, char const *const fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    int num = a_str_vprintf(ctx, fmt, va);
    va_end(va);
    return num;
}

#include "a/utf.h"

a_size_t a_str_utflen(a_str_s const *const ctx)
{
    a_size_t length = 0;
    if (ctx->_num)
    {
        unsigned int offset;
        char const *head = ctx->_ptr;
        char const *const tail = head + ctx->_num;
        while ((void)(offset = a_utf_decode(head, A_NULL)), offset)
        {
            ++length;
            head += offset;
            if (head >= tail)
            {
                break;
            }
        }
    }
    return length;
}
