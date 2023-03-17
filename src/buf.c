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

static A_INLINE a_vptr_t a_buf_inc_(a_buf_s *const ctx)
{
    return a_byte_p(ctx->_ptr) + ctx->_siz * ctx->_num++;
}

static A_INLINE a_vptr_t a_buf_dec_(a_buf_s *const ctx)
{
    return a_byte_p(ctx->_ptr) + ctx->_siz * --ctx->_num;
}

static a_void_t a_buf_drop_(a_buf_s *const ctx, a_size_t const bot, a_void_t (*const dtor)(a_vptr_t))
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

a_void_t a_buf_ctor(a_buf_s *const ctx, a_vptr_t const ptr, a_size_t const siz, a_size_t const num)
{
    ctx->_ptr = ptr;
    ctx->_siz = siz;
    ctx->_mem = num;
    ctx->_num = 0;
}

a_void_t a_buf_dtor(a_buf_s *const ctx, a_void_t (*const dtor)(a_vptr_t))
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

a_void_t a_buf_drop(a_buf_s *const ctx, a_void_t (*const dtor)(a_vptr_t))
{
    a_buf_drop_(ctx, 0, dtor);
}

a_void_t a_buf_swap(a_buf_s const *const ctx, a_size_t lhs, a_size_t rhs)
{
    a_size_t const num = ctx->_num - 1;
    lhs = lhs < ctx->_num ? lhs : num;
    rhs = rhs < ctx->_num ? rhs : num;
    if (lhs != rhs)
    {
        a_vptr_t const lobj = a_byte_p(ctx->_ptr) + lhs * ctx->_siz;
        a_vptr_t const robj = a_byte_p(ctx->_ptr) + rhs * ctx->_siz;
        a_swap(lobj, robj, ctx->_siz);
    }
}

a_void_t a_buf_sort(a_buf_s const *const ctx, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    qsort(ctx->_ptr, ctx->_num, ctx->_siz, cmp);
}

a_void_t a_buf_sort_fore(a_buf_s const *const ctx, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    if (ctx->_num > 1)
    {
        a_byte_t *ptr = a_byte_p(ctx->_ptr);
        a_byte_t *const end = a_byte_p(ctx->_ptr) + ctx->_siz * ctx->_num - ctx->_siz;
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

a_void_t a_buf_sort_back(a_buf_s const *const ctx, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    if (ctx->_num > 1)
    {
        a_byte_t *ptr = a_byte_p(ctx->_ptr) + ctx->_siz * ctx->_num - ctx->_siz;
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

a_vptr_t a_buf_search(a_buf_s const *const ctx, a_cptr_t const obj, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    return bsearch(obj, ctx->_ptr, ctx->_num, ctx->_siz, cmp);
}

a_vptr_t a_buf_insert(a_buf_s *const ctx, a_size_t const idx)
{
    if (a_likely(ctx->_num < ctx->_mem))
    {
        if (idx < ctx->_num)
        {
            a_byte_t *const src = a_byte_p(ctx->_ptr) + ctx->_siz * (idx + 0);
            a_byte_t *const dst = a_byte_p(ctx->_ptr) + ctx->_siz * (idx + 1);
            a_move(dst, src, (ctx->_num - idx) * ctx->_siz);
            ++ctx->_num;
            return src;
        }
        return a_buf_inc_(ctx);
    }
    return A_NULL;
}

a_vptr_t a_buf_push_fore(a_buf_s *const ctx) { return a_buf_insert(ctx, 0); }

a_vptr_t a_buf_push_back(a_buf_s *const ctx)
{
    return a_likely(ctx->_num < ctx->_mem) ? a_buf_inc_(ctx) : A_NULL;
}

a_vptr_t a_buf_remove(a_buf_s *const ctx, a_size_t const idx)
{
    a_size_t const num = ctx->_num - 1;
    if (ctx->_num && idx < num)
    {
        a_byte_t *const ptr = a_byte_p(ctx->_ptr) + ctx->_siz * num;
        a_byte_t *const dst = a_byte_p(ctx->_ptr) + ctx->_siz * (idx + 0);
        a_byte_t *const src = a_byte_p(ctx->_ptr) + ctx->_siz * (idx + 1);
        a_swap(dst, src, a_size_c(ptr - dst));
        --ctx->_num;
        return ptr;
    }
    return a_likely(ctx->_num) ? a_buf_dec_(ctx) : A_NULL;
}

a_vptr_t a_buf_pull_fore(a_buf_s *const ctx) { return a_buf_remove(ctx, 0); }

a_vptr_t a_buf_pull_back(a_buf_s *const ctx)
{
    return a_likely(ctx->_num) ? a_buf_dec_(ctx) : A_NULL;
}
