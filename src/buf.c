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
    return (a_byte *)ctx->ptr_ + ctx->siz_ * ctx->num_++;
}

static A_INLINE void *a_buf_dec_(a_buf *ctx)
{
    return (a_byte *)ctx->ptr_ + ctx->siz_ * --ctx->num_;
}

static void a_buf_drop_(a_buf *ctx, a_size bot, void (*dtor)(void *))
{
    if (dtor)
    {
        while (ctx->num_ > bot) { dtor(a_buf_dec_(ctx)); }
    }
    ctx->num_ = bot;
}

void a_buf_ctor(a_buf *ctx, void *ptr, a_size siz, a_size num)
{
    ctx->ptr_ = ptr;
    ctx->siz_ = siz;
    ctx->mem_ = num;
    ctx->num_ = 0;
}

void a_buf_dtor(a_buf *ctx, void (*dtor)(void *))
{
    if (ctx->ptr_)
    {
        a_buf_drop_(ctx, 0, dtor);
        ctx->ptr_ = A_NULL;
    }
    ctx->siz_ = 0;
    ctx->mem_ = 0;
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
    a_size const num = ctx->num_ - 1;
    lhs = lhs < ctx->num_ ? lhs : num;
    rhs = rhs < ctx->num_ ? rhs : num;
    if (lhs != rhs)
    {
        a_swap((a_byte *)ctx->ptr_ + lhs * ctx->siz_,
               (a_byte *)ctx->ptr_ + rhs * ctx->siz_,
               ctx->siz_);
    }
}

void a_buf_sort(a_buf const *ctx, int (*cmp)(void const *, void const *))
{
    qsort(ctx->ptr_, ctx->num_, ctx->siz_, cmp);
}

void a_buf_sort_fore(a_buf const *ctx, int (*cmp)(void const *, void const *))
{
    if (ctx->num_ > 1)
    {
        a_byte *ptr = (a_byte *)ctx->ptr_;
        a_byte *const end = (a_byte *)ctx->ptr_ + ctx->siz_ * ctx->num_ - ctx->siz_;
        do {
            a_byte *const cur = ptr + ctx->siz_;
            if (cmp(ptr, cur) > 0)
            {
                a_swap(cur, ptr, ctx->siz_);
            }
            else { break; }
            ptr = cur;
        } while (ptr != end);
    }
}

void a_buf_sort_back(a_buf const *ctx, int (*cmp)(void const *, void const *))
{
    if (ctx->num_ > 1)
    {
        a_byte *ptr = (a_byte *)ctx->ptr_ + ctx->siz_ * ctx->num_ - ctx->siz_;
        do {
            a_byte *const cur = ptr - ctx->siz_;
            if (cmp(cur, ptr) > 0)
            {
                a_swap(cur, ptr, ctx->siz_);
            }
            else { break; }
            ptr = cur;
        } while (ptr != ctx->ptr_);
    }
}

void *a_buf_search(a_buf const *ctx, void const *obj, int (*cmp)(void const *, void const *))
{
    return bsearch(obj, ctx->ptr_, ctx->num_, ctx->siz_, cmp);
}

void *a_buf_insert(a_buf *ctx, a_size idx)
{
    if (a_likely(ctx->num_ < ctx->mem_))
    {
        if (idx < ctx->num_)
        {
            a_byte *const src = (a_byte *)ctx->ptr_ + ctx->siz_ * (idx + 0);
            a_byte *const dst = (a_byte *)ctx->ptr_ + ctx->siz_ * (idx + 1);
            a_move(dst, src, (ctx->num_ - idx) * ctx->siz_);
            ++ctx->num_;
            return src;
        }
        return a_buf_inc_(ctx);
    }
    return A_NULL;
}

void *a_buf_push_fore(a_buf *ctx) { return a_buf_insert(ctx, 0); }

void *a_buf_push_back(a_buf *ctx)
{
    return a_likely(ctx->num_ < ctx->mem_) ? a_buf_inc_(ctx) : A_NULL;
}

void *a_buf_remove(a_buf *ctx, a_size idx)
{
    a_size const num = ctx->num_ - 1;
    if (ctx->num_ && idx < num)
    {
        a_byte *const ptr = (a_byte *)ctx->ptr_ + ctx->siz_ * num;
        a_byte *const dst = (a_byte *)ctx->ptr_ + ctx->siz_ * (idx + 0);
        a_byte *const src = (a_byte *)ctx->ptr_ + ctx->siz_ * (idx + 1);
        a_swap(dst, src, (a_size)(ptr - dst));
        --ctx->num_;
        return ptr;
    }
    return a_likely(ctx->num_) ? a_buf_dec_(ctx) : A_NULL;
}

void *a_buf_pull_fore(a_buf *ctx) { return a_buf_remove(ctx, 0); }

void *a_buf_pull_back(a_buf *ctx)
{
    return a_likely(ctx->num_) ? a_buf_dec_(ctx) : A_NULL;
}
