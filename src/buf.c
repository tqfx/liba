#include "a/buf.h"
#include <stdlib.h>

#undef a_buf_at
#undef a_buf_at_
#undef a_buf_idx
#undef a_buf_ptr
#undef a_buf_end
#undef a_buf_top
#undef a_buf_top_
#undef a_buf_push
#undef a_buf_pull
#undef a_buf_search
#undef a_buf_insert
#undef a_buf_remove
#undef a_buf_push_fore
#undef a_buf_push_back
#undef a_buf_pull_fore
#undef a_buf_pull_back

static A_INLINE void *a_buf_inc_(a_buf *ctx)
{
    return (a_byte *)ctx->_ptr + ctx->_siz * ctx->_num++;
}

static A_INLINE void *a_buf_dec_(a_buf *ctx)
{
    return (a_byte *)ctx->_ptr + ctx->_siz * --ctx->_num;
}

static void a_buf_drop_(a_buf *ctx, a_size bot, void (*dtor)(void *))
{
    if (dtor)
    {
        while (ctx->_num > bot) { dtor(a_buf_dec_(ctx)); }
    }
    ctx->_num = bot;
}

void a_buf_ctor(a_buf *ctx, void *ptr, a_size siz, a_size num)
{
    ctx->_ptr = ptr;
    ctx->_siz = siz;
    ctx->_mem = num;
    ctx->_num = 0;
}

void a_buf_dtor(a_buf *ctx, void (*dtor)(void *))
{
    if (ctx->_ptr)
    {
        a_buf_drop_(ctx, 0, dtor);
        ctx->_ptr = A_NULL;
    }
    ctx->_mem = 0;
    ctx->_siz = 0;
}

void a_buf_move(a_buf *ctx, a_buf *obj)
{
    a_copy(ctx, obj, sizeof(*obj));
    a_zero(obj, sizeof(*obj));
}

void a_buf_drop(a_buf *ctx, void (*dtor)(void *))
{
    a_buf_drop_(ctx, 0, dtor);
}

void a_buf_swap(a_buf const *ctx, a_size lhs, a_size rhs)
{
    a_size const num = ctx->_num - 1;
    lhs = lhs < ctx->_num ? lhs : num;
    rhs = rhs < ctx->_num ? rhs : num;
    if (lhs != rhs)
    {
        a_swap((a_byte *)ctx->_ptr + lhs * ctx->_siz,
               (a_byte *)ctx->_ptr + rhs * ctx->_siz,
               ctx->_siz);
    }
}

void a_buf_sort(a_buf const *ctx, int (*cmp)(void const *, void const *))
{
    qsort(ctx->_ptr, ctx->_num, ctx->_siz, cmp);
}

void a_buf_sort_fore(a_buf const *ctx, int (*cmp)(void const *, void const *))
{
    if (ctx->_num > 1)
    {
        a_byte *ptr = (a_byte *)ctx->_ptr;
        a_byte *const end = (a_byte *)ctx->_ptr + ctx->_siz * ctx->_num - ctx->_siz;
        do {
            a_byte *const cur = ptr + ctx->_siz;
            if (cmp(ptr, cur) > 0)
            {
                a_swap(cur, ptr, ctx->_siz);
            }
            else { break; }
            ptr = cur;
        } while (ptr != end);
    }
}

void a_buf_sort_back(a_buf const *ctx, int (*cmp)(void const *, void const *))
{
    if (ctx->_num > 1)
    {
        a_byte *ptr = (a_byte *)ctx->_ptr + ctx->_siz * ctx->_num - ctx->_siz;
        do {
            a_byte *const cur = ptr - ctx->_siz;
            if (cmp(cur, ptr) > 0)
            {
                a_swap(cur, ptr, ctx->_siz);
            }
            else { break; }
            ptr = cur;
        } while (ptr != ctx->_ptr);
    }
}

void *a_buf_search(a_buf const *ctx, void const *obj, int (*cmp)(void const *, void const *))
{
    return bsearch(obj, ctx->_ptr, ctx->_num, ctx->_siz, cmp);
}

void *a_buf_insert(a_buf *ctx, a_size idx)
{
    if (a_likely(ctx->_num < ctx->_mem))
    {
        if (idx < ctx->_num)
        {
            a_byte *const src = (a_byte *)ctx->_ptr + ctx->_siz * (idx + 0);
            a_byte *const dst = (a_byte *)ctx->_ptr + ctx->_siz * (idx + 1);
            a_move(dst, src, (ctx->_num - idx) * ctx->_siz);
            ++ctx->_num;
            return src;
        }
        return a_buf_inc_(ctx);
    }
    return A_NULL;
}

void *a_buf_push_fore(a_buf *ctx) { return a_buf_insert(ctx, 0); }

void *a_buf_push_back(a_buf *ctx)
{
    return a_likely(ctx->_num < ctx->_mem) ? a_buf_inc_(ctx) : A_NULL;
}

void *a_buf_remove(a_buf *ctx, a_size idx)
{
    a_size const num = ctx->_num - 1;
    if (ctx->_num && idx < num)
    {
        a_byte *const ptr = (a_byte *)ctx->_ptr + ctx->_siz * num;
        a_byte *const dst = (a_byte *)ctx->_ptr + ctx->_siz * (idx + 0);
        a_byte *const src = (a_byte *)ctx->_ptr + ctx->_siz * (idx + 1);
        a_swap(dst, src, (a_size)(ptr - dst));
        --ctx->_num;
        return ptr;
    }
    return a_likely(ctx->_num) ? a_buf_dec_(ctx) : A_NULL;
}

void *a_buf_pull_fore(a_buf *ctx) { return a_buf_remove(ctx, 0); }

void *a_buf_pull_back(a_buf *ctx)
{
    return a_likely(ctx->_num) ? a_buf_dec_(ctx) : A_NULL;
}
