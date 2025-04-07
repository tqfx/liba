#include "a/buf.h"
#include <stdlib.h>

static A_INLINE void *a_buf_inc_(void *ctx_)
{
    a_buf *const ctx = (a_buf *)ctx_;
    return (a_byte *)(ctx + 1) + ctx->siz_ * ctx->num_++;
}

static A_INLINE void *a_buf_dec_(void *ctx_)
{
    a_buf *const ctx = (a_buf *)ctx_;
    return (a_byte *)(ctx + 1) + ctx->siz_ * --ctx->num_;
}

a_buf *a_buf_new(a_size siz, a_size num)
{
    a_buf *const ctx = (a_buf *)a_alloc(A_NULL, sizeof(a_buf) + siz * num);
    if (ctx) { a_buf_ctor(ctx, siz, num); }
    return ctx;
}

void a_buf_die(a_buf *ctx, void (*dtor)(void *))
{
    if (ctx)
    {
        a_buf_dtor(ctx, dtor);
        a_alloc(ctx, 0);
    }
}

void a_buf_ctor(void *ctx_, a_size siz, a_size num)
{
    a_buf *const ctx = (a_buf *)ctx_;
    if (!siz) { siz = 1; }
    ctx->num_ = 0;
    ctx->mem_ = num;
    ctx->siz_ = siz;
}

void a_buf_dtor(void *ctx, void (*dtor)(void *))
{
    a_buf_setn(ctx, 0, dtor);
}

a_buf *a_buf_setm(a_buf *ctx, a_size mem)
{
    ctx = (a_buf *)a_alloc(ctx, sizeof(a_buf) + ctx->siz_ * mem);
    if (ctx) { ctx->mem_ = mem; }
    return ctx;
}

void a_buf_setn(void *ctx_, a_size num, void (*dtor)(void *))
{
    a_buf *const ctx = (a_buf *)ctx_;
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

void a_buf_setz(void *ctx_, a_size siz, void (*dtor)(void *))
{
    a_buf *const ctx = (a_buf *)ctx_;
    a_buf_setn(ctx, 0, dtor);
    ctx->mem_ *= ctx->siz_;
    if (!siz) { siz = 1; }
    ctx->mem_ /= siz;
    ctx->siz_ = siz;
}

void a_buf_sort(void const *ctx_, int (*cmp)(void const *, void const *))
{
    a_buf const *const ctx = (a_buf const *)ctx_;
    qsort(a_buf_ptr(ctx), ctx->num_, ctx->siz_, cmp);
}

void a_buf_sort_fore(void const *ctx_, int (*cmp)(void const *, void const *))
{
    a_buf const *const ctx = (a_buf const *)ctx_;
    if (ctx->num_ > 1)
    {
        a_byte *ptr = (a_byte *)a_buf_ptr(ctx);
        a_byte *const end = ptr + ctx->siz_ * ctx->num_;
        if (ctx->num_ < ctx->mem_)
        {
            a_size b = 1, i = ctx->num_ - 1;
            while (b <= i)
            {
                a_size const m = b + ((i - b) >> 1);
                a_byte *const cur = ptr + ctx->siz_ * m;
                if (cmp(ptr, cur) > 0) { b = m + 1; }
                else { i = m - 1; }
            }
            if (i > 0)
            {
                a_byte *const cur = ptr + ctx->siz_ * i;
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

void a_buf_sort_back(void const *ctx_, int (*cmp)(void const *, void const *))
{
    a_buf const *const ctx = (a_buf const *)ctx_;
    if (ctx->num_ > 1)
    {
        a_byte *const buf = (a_byte *)a_buf_ptr(ctx);
        a_byte *const end = buf + ctx->siz_ * ctx->num_;
        a_byte *ptr = end - ctx->siz_;
        if (ctx->num_ < ctx->mem_)
        {
            a_size const idx = ctx->num_ - 1;
            a_size i = 0, r = idx;
            while (i < r)
            {
                a_size const m = i + ((r - i) >> 1);
                a_byte *const cur = buf + ctx->siz_ * m;
                if (cmp(cur, ptr) > 0) { r = m; }
                else { i = m + 1; }
            }
            if (i < idx)
            {
                a_byte *const cur = buf + ctx->siz_ * i;
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
            } while (ptr != buf);
        }
    }
}

void *a_buf_push_sort(void *ctx_, void const *key, int (*cmp)(void const *, void const *))
{
    a_buf *const ctx = (a_buf *)ctx_;
    if (ctx->num_ < ctx->mem_)
    {
        a_size const idx = ctx->num_;
        a_byte *const buf = (a_byte *)(ctx + 1);
        a_byte *ptr = (a_byte *)a_buf_inc_(ctx);
        a_size i = 0, r = idx;
        while (i < r)
        {
            a_size const m = i + ((r - i) >> 1);
            a_byte *const cur = buf + ctx->siz_ * m;
            if (cmp(cur, key) > 0) { r = m; }
            else { i = m + 1; }
        }
        if (i < idx)
        {
            a_byte *const cur = buf + ctx->siz_ * i;
            a_move(cur + ctx->siz_, cur, (a_size)(ptr - cur));
            ptr = cur;
        }
        return ptr;
    }
    return A_NULL;
}

void *a_buf_search(void const *ctx_, void const *obj, int (*cmp)(void const *, void const *))
{
    a_buf const *const ctx = (a_buf const *)ctx_;
    return bsearch(obj, (ctx + 1), ctx->num_, ctx->siz_, cmp);
}

void *a_buf_insert(void *ctx_, a_size idx)
{
    a_buf *const ctx = (a_buf *)ctx_;
    if (ctx->num_ < ctx->mem_)
    {
        if (idx < ctx->num_)
        {
            a_byte *const p = (a_byte *)(ctx + 1) + ctx->siz_ * idx;
            a_move(p + ctx->siz_, p, (ctx->num_ - idx) * ctx->siz_);
            ++ctx->num_;
            return p;
        }
        return a_buf_inc_(ctx);
    }
    return A_NULL;
}

void *a_buf_push_fore(void *ctx) { return a_buf_insert(ctx, 0); }

void *a_buf_push_back(void *ctx_)
{
    a_buf *const ctx = (a_buf *)ctx_;
    return ctx->num_ < ctx->mem_ ? a_buf_inc_(ctx) : A_NULL;
}

void *a_buf_remove(void *ctx_, a_size idx)
{
    a_buf *const ctx = (a_buf *)ctx_;
    if (idx + 1 < ctx->num_)
    {
        a_byte *const buf = (a_byte *)(ctx + 1);
        a_byte *const p = buf + ctx->siz_ * idx;
        a_byte *const q = p + ctx->siz_;
        if (ctx->num_ < ctx->mem_)
        {
            a_byte *const ptr = buf + ctx->siz_ * ctx->num_--;
            a_copy(ptr, p, ctx->siz_);
            a_move(p, q, (a_size)(ptr - q));
            return ptr;
        }
        else
        {
            a_byte *const ptr = buf + ctx->siz_ * --ctx->num_;
            a_swap(p, q, (a_size)(ptr - p));
            return ptr;
        }
    }
    return ctx->num_ ? a_buf_dec_(ctx) : A_NULL;
}

void *a_buf_pull_fore(void *ctx) { return a_buf_remove(ctx, 0); }

void *a_buf_pull_back(void *ctx_)
{
    a_buf *const ctx = (a_buf *)ctx_;
    return ctx->num_ ? a_buf_dec_(ctx) : A_NULL;
}

int a_buf_store(void *ctx_, a_size idx, void *ptr, a_size num, int (*copy)(void *, void const *))
{
    int rc = A_SUCCESS;
    a_buf *const ctx = (a_buf *)ctx_;
    if (ctx->num_ + num <= ctx->mem_)
    {
        a_byte *const buf = (a_byte *)(ctx + 1);
        a_byte *p = buf + ctx->siz_ * ctx->num_;
        a_size n = ctx->siz_ * num;
        if (!num) { return rc; }
        if (idx < ctx->num_)
        {
            a_byte *const q = p;
            p = buf + ctx->siz_ * idx;
            a_move(p + n, p, (a_size)(q - p));
        }
        if (!copy) { a_copy(p, ptr, n); }
        else
        {
            a_byte *q = (a_byte *)ptr;
            for (n = num; n; --n)
            {
                rc = copy(p, q);
                p += ctx->siz_;
                q += ctx->siz_;
            }
        }
        ctx->num_ += num;
    }
    else { rc = A_OBOUNDS; }
    return rc;
}

int a_buf_erase(void *ctx_, a_size idx, a_size num, void (*dtor)(void *))
{
    int rc = A_SUCCESS;
    a_size const n = idx + num;
    a_buf *const ctx = (a_buf *)ctx_;
    a_byte *const buf = (a_byte *)(ctx + 1);
    if (dtor)
    {
        a_byte *p = buf + ctx->siz_ * idx;
        a_size i = (n <= ctx->num_ ? n : ctx->num_);
        for (; i > idx; --i, p += ctx->siz_) { dtor(p); }
    }
    if (n < ctx->num_)
    {
        a_byte *const p = buf + ctx->siz_ * idx;
        a_move(p, p + ctx->siz_ * num, (ctx->num_ - n) * ctx->siz_);
        ctx->num_ -= num;
    }
    else if (idx < ctx->num_)
    {
        ctx->num_ = idx;
    }
    else { rc = A_OBOUNDS; }
    return rc;
}
