#include "a/buf.h"
#include <stdlib.h>

static A_INLINE void *a_buf_inc_(a_buf *ctx)
{
    return (a_byte *)ctx->ptr_ + ctx->siz_ * ctx->num_++;
}

static A_INLINE void *a_buf_dec_(a_buf *ctx)
{
    return (a_byte *)ctx->ptr_ + ctx->siz_ * --ctx->num_;
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
    a_buf_setn(ctx, 0, dtor);
}

void a_buf_move(a_buf *ctx, a_buf *obj)
{
    a_copy(ctx, obj, sizeof(*obj));
    a_zero(obj, sizeof(*obj));
}

void a_buf_setn(a_buf *ctx, a_size num, void (*dtor)(void *))
{
    if (dtor)
    {
        while (ctx->num_ > num)
        {
            dtor(a_buf_dec_(ctx));
        }
    }
    if (num > ctx->mem_)
    {
        num = ctx->mem_;
    }
    ctx->num_ = num;
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
        a_byte *const end = (a_byte *)ctx->ptr_ + ctx->siz_ * ctx->num_;
        a_byte *ptr = (a_byte *)ctx->ptr_;
        if (ctx->num_ < ctx->mem_)
        {
            a_size b = 1, i = ctx->num_ - 1;
            while (b <= i)
            {
                a_size const m = b + ((i - b) >> 1);
                a_byte *const cur = (a_byte *)ctx->ptr_ + ctx->siz_ * m;
                if (cmp(cur, ptr) <= 0) { b = m + 1; }
                else { i = m - 1; }
            }
            if (i > 0)
            {
                a_byte *const cur = (a_byte *)ctx->ptr_ + ctx->siz_ * i;
                a_copy(end, ptr, ctx->siz_);
                a_move(ptr, ptr + ctx->siz_, (a_size)(cur - ptr));
                a_copy(cur, end, ctx->siz_);
            }
        }
        else
        {
            a_byte *cur = ptr + ctx->siz_;
            for (; cur != end; cur += ctx->siz_)
            {
                if (cmp(ptr, cur) > 0)
                {
                    a_swap(cur, ptr, ctx->siz_);
                }
                else { break; }
                ptr = cur;
            }
        }
    }
}

void a_buf_sort_back(a_buf const *ctx, int (*cmp)(void const *, void const *))
{
    if (ctx->num_ > 1)
    {
        a_byte *const end = (a_byte *)ctx->ptr_ + ctx->siz_ * ctx->num_;
        a_byte *ptr = end - ctx->siz_;
        if (ctx->num_ < ctx->mem_)
        {
            a_size const idx = ctx->num_ - 1;
            a_size i = 0, r = idx;
            while (i < r)
            {
                a_size const m = i + ((r - i) >> 1);
                a_byte *const cur = (a_byte *)ctx->ptr_ + ctx->siz_ * m;
                if (cmp(cur, ptr) <= 0) { i = m + 1; }
                else { r = m; }
            }
            if (i < idx)
            {
                a_byte *const cur = (a_byte *)ctx->ptr_ + ctx->siz_ * i;
                a_copy(end, ptr, ctx->siz_);
                a_move(cur + ctx->siz_, cur, (a_size)(ptr - cur));
                a_copy(cur, end, ctx->siz_);
            }
        }
        else
        {
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
}

void *a_buf_push_sort(a_buf *ctx, void const *key, int (*cmp)(void const *, void const *))
{
    if (ctx->num_ < ctx->mem_)
    {
        a_size const idx = ctx->num_;
        a_byte *ptr = (a_byte *)a_buf_inc_(ctx);
        a_size i = 0, r = idx;
        while (i < r)
        {
            a_size const m = i + ((r - i) >> 1);
            a_byte *const cur = (a_byte *)ctx->ptr_ + ctx->siz_ * m;
            if (cmp(cur, key) <= 0) { i = m + 1; }
            else { r = m; }
        }
        if (i < idx)
        {
            a_byte *const cur = (a_byte *)ctx->ptr_ + ctx->siz_ * i;
            a_move(cur + ctx->siz_, cur, (a_size)(ptr - cur));
            ptr = cur;
        }
        return ptr;
    }
    return A_NULL;
}

void *a_buf_search(a_buf const *ctx, void const *obj, int (*cmp)(void const *, void const *))
{
    return bsearch(obj, ctx->ptr_, ctx->num_, ctx->siz_, cmp);
}

void *a_buf_insert(a_buf *ctx, a_size idx)
{
    if (ctx->num_ < ctx->mem_)
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
    return ctx->num_ < ctx->mem_ ? a_buf_inc_(ctx) : A_NULL;
}

void *a_buf_remove(a_buf *ctx, a_size idx)
{
    if (idx + 1 < ctx->num_)
    {
        if (ctx->num_ < ctx->mem_)
        {
            a_byte *const ptr = (a_byte *)ctx->ptr_ + ctx->siz_ * ctx->num_--;
            a_byte *const dst = (a_byte *)ctx->ptr_ + ctx->siz_ * (idx + 0);
            a_byte *const src = (a_byte *)ctx->ptr_ + ctx->siz_ * (idx + 1);
            a_size const siz = (a_size)(ptr - src);
            a_copy(ptr, dst, ctx->siz_);
            a_move(dst, src, siz);
            return ptr;
        }
        else
        {
            a_byte *const ptr = (a_byte *)ctx->ptr_ + ctx->siz_ * --ctx->num_;
            a_byte *const dst = (a_byte *)ctx->ptr_ + ctx->siz_ * (idx + 0);
            a_byte *const src = (a_byte *)ctx->ptr_ + ctx->siz_ * (idx + 1);
            a_swap(dst, src, (a_size)(ptr - dst));
            return ptr;
        }
    }
    return ctx->num_ ? a_buf_dec_(ctx) : A_NULL;
}

void *a_buf_pull_fore(a_buf *ctx) { return a_buf_remove(ctx, 0); }

void *a_buf_pull_back(a_buf *ctx)
{
    return ctx->num_ ? a_buf_dec_(ctx) : A_NULL;
}
