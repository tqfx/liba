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

static A_INLINE void *a_buf_inc_(a_buf_s *const ctx)
{
    return (a_byte_t *)ctx->_ptr + ctx->_siz * ctx->_num++;
}

static A_INLINE void *a_buf_dec_(a_buf_s *const ctx)
{
    return (a_byte_t *)ctx->_ptr + ctx->_siz * --ctx->_num;
}

static void a_buf_drop_(a_buf_s *const ctx, a_size_t const bot, void (*const dtor)(void *))
{
    if (dtor)
    {
        while (ctx->_num > bot)
        {
            dtor(a_buf_dec_(ctx));
        }
    }
    ctx->_num = bot;
}

void a_buf_ctor(a_buf_s *const ctx, void *const ptr, a_size_t const siz, a_size_t const num)
{
    ctx->_ptr = ptr;
    ctx->_siz = siz;
    ctx->_mem = num;
    ctx->_num = 0;
}

void a_buf_dtor(a_buf_s *const ctx, void (*const dtor)(void *))
{
    if (ctx->_ptr)
    {
        a_buf_drop_(ctx, 0, dtor);
        ctx->_ptr = A_NULL;
    }
    ctx->_mem = 0;
    ctx->_siz = 0;
}

a_buf_s *a_buf_move(a_buf_s *const ctx, a_buf_s *const obj)
{
    a_copy(ctx, obj, sizeof(*obj));
    a_zero(obj, sizeof(*obj));
    return ctx;
}

void a_buf_drop(a_buf_s *const ctx, void (*const dtor)(void *))
{
    a_buf_drop_(ctx, 0, dtor);
}

void a_buf_swap(a_buf_s const *const ctx, a_size_t lhs, a_size_t rhs)
{
    a_size_t const num = ctx->_num - 1;
    lhs = lhs < ctx->_num ? lhs : num;
    rhs = rhs < ctx->_num ? rhs : num;
    if (lhs != rhs)
    {
        void *const lobj = (a_byte_t *)ctx->_ptr + lhs * ctx->_siz;
        void *const robj = (a_byte_t *)ctx->_ptr + rhs * ctx->_siz;
        a_swap(lobj, robj, ctx->_siz);
    }
}

void a_buf_sort(a_buf_s const *const ctx, int (*const cmp)(void const *, void const *))
{
    qsort(ctx->_ptr, ctx->_num, ctx->_siz, cmp);
}

void a_buf_sort_fore(a_buf_s const *const ctx, int (*const cmp)(void const *, void const *))
{
    if (ctx->_num > 1)
    {
        a_byte_t *ptr = (a_byte_t *)ctx->_ptr;
        a_byte_t *const end = (a_byte_t *)ctx->_ptr + ctx->_siz * ctx->_num - ctx->_siz;
        do
        {
            a_byte_t *const cur = ptr + ctx->_siz;
            if (cmp(ptr, cur) > 0)
            {
                a_swap(cur, ptr, ctx->_siz);
            }
            else
            {
                break;
            }
            ptr = cur;
        } while (ptr != end);
    }
}

void a_buf_sort_back(a_buf_s const *const ctx, int (*const cmp)(void const *, void const *))
{
    if (ctx->_num > 1)
    {
        a_byte_t *ptr = (a_byte_t *)ctx->_ptr + ctx->_siz * ctx->_num - ctx->_siz;
        do
        {
            a_byte_t *const cur = ptr - ctx->_siz;
            if (cmp(cur, ptr) > 0)
            {
                a_swap(cur, ptr, ctx->_siz);
            }
            else
            {
                break;
            }
            ptr = cur;
        } while (ptr != ctx->_ptr);
    }
}

void *a_buf_search(a_buf_s const *const ctx, void const *const obj, int (*const cmp)(void const *, void const *))
{
    return bsearch(obj, ctx->_ptr, ctx->_num, ctx->_siz, cmp);
}

void *a_buf_insert(a_buf_s *const ctx, a_size_t const idx)
{
    if (a_likely(ctx->_num < ctx->_mem))
    {
        if (idx < ctx->_num)
        {
            a_byte_t *const src = (a_byte_t *)ctx->_ptr + ctx->_siz * (idx + 0);
            a_byte_t *const dst = (a_byte_t *)ctx->_ptr + ctx->_siz * (idx + 1);
            a_move(dst, src, (ctx->_num - idx) * ctx->_siz);
            ++ctx->_num;
            return src;
        }
        return a_buf_inc_(ctx);
    }
    return A_NULL;
}

void *a_buf_push_fore(a_buf_s *const ctx) { return a_buf_insert(ctx, 0); }

void *a_buf_push_back(a_buf_s *const ctx)
{
    return a_likely(ctx->_num < ctx->_mem) ? a_buf_inc_(ctx) : A_NULL;
}

void *a_buf_remove(a_buf_s *const ctx, a_size_t const idx)
{
    a_size_t const num = ctx->_num - 1;
    if (ctx->_num && idx < num)
    {
        a_byte_t *const ptr = (a_byte_t *)ctx->_ptr + ctx->_siz * num;
        a_byte_t *const dst = (a_byte_t *)ctx->_ptr + ctx->_siz * (idx + 0);
        a_byte_t *const src = (a_byte_t *)ctx->_ptr + ctx->_siz * (idx + 1);
        a_swap(dst, src, (a_size_t)(ptr - dst));
        --ctx->_num;
        return ptr;
    }
    return a_likely(ctx->_num) ? a_buf_dec_(ctx) : A_NULL;
}

void *a_buf_pull_fore(a_buf_s *const ctx) { return a_buf_remove(ctx, 0); }

void *a_buf_pull_back(a_buf_s *const ctx)
{
    return a_likely(ctx->_num) ? a_buf_dec_(ctx) : A_NULL;
}
