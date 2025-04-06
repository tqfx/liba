#include "a/vec.h"
#include <stdlib.h>

static A_INLINE void *a_vec_inc_(a_vec *ctx)
{
    return (a_byte *)ctx->ptr_ + ctx->siz_ * ctx->num_++;
}

static A_INLINE void *a_vec_dec_(a_vec *ctx)
{
    return (a_byte *)ctx->ptr_ + ctx->siz_ * --ctx->num_;
}

a_vec *a_vec_new(a_size size)
{
    a_vec *const ctx = (a_vec *)a_alloc(A_NULL, sizeof(a_vec));
    if (ctx) { a_vec_ctor(ctx, size); }
    return ctx;
}

void a_vec_die(a_vec *ctx, void (*dtor)(void *))
{
    if (ctx)
    {
        a_vec_dtor(ctx, dtor);
        a_alloc(ctx, 0);
    }
}

void a_vec_ctor(a_vec *ctx, a_size size)
{
    if (!size) { size = 1; }
    ctx->ptr_ = A_NULL;
    ctx->siz_ = size;
    ctx->num_ = 0;
    ctx->mem_ = 0;
}

void a_vec_dtor(a_vec *ctx, void (*dtor)(void *))
{
    a_vec_setn(ctx, 0, dtor);
    if (ctx->ptr_)
    {
        a_alloc(ctx->ptr_, 0);
        ctx->ptr_ = A_NULL;
    }
    ctx->siz_ = 0;
    ctx->mem_ = 0;
}

void a_vec_swap(a_vec *lhs, a_vec *rhs)
{
    a_vec swap;
    swap = *lhs;
    *lhs = *rhs;
    *rhs = swap;
}

int a_vec_setm(a_vec *ctx, a_size mem)
{
    int rc = A_SUCCESS;
    if (mem > ctx->mem_)
    {
        void *ptr;
        a_size m = ctx->mem_;
        do {
            m += (m >> 1) + 1;
        } while (m < mem);
        mem = a_size_up(sizeof(void *), m);
        ptr = a_alloc(ctx->ptr_, ctx->siz_ * mem);
        if (ptr)
        {
            ctx->ptr_ = ptr;
            ctx->mem_ = mem;
        }
        else
        {
            rc = A_OMEMORY;
        }
    }
    A_ASSUME(ctx->ptr_);
    return rc;
}

int a_vec_setn(a_vec *ctx, a_size num, void (*dtor)(void *))
{
    int rc = a_vec_setm(ctx, num);
    if (rc == 0)
    {
        if (dtor)
        {
            while (ctx->num_ > num)
            {
                dtor(a_vec_dec_(ctx));
            }
        }
        ctx->num_ = num;
    }
    return rc;
}

void a_vec_setz(a_vec *ctx, a_size siz, void (*dtor)(void *))
{
    a_vec_setn(ctx, 0, dtor);
    ctx->mem_ *= ctx->siz_;
    if (!siz) { siz = 1; }
    ctx->mem_ /= siz;
    ctx->siz_ = siz;
}

void a_vec_sort(a_vec const *ctx, int (*cmp)(void const *, void const *))
{
    qsort(ctx->ptr_, ctx->num_, ctx->siz_, cmp);
}

void a_vec_sort_fore(a_vec const *ctx, int (*cmp)(void const *, void const *))
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
                if (cmp(ptr, cur) > 0) { b = m + 1; }
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

void a_vec_sort_back(a_vec const *ctx, int (*cmp)(void const *, void const *))
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
                if (cmp(cur, ptr) > 0) { r = m; }
                else { i = m + 1; }
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

void *a_vec_push_sort(a_vec *ctx, void const *key, int (*cmp)(void const *, void const *))
{
    if (a_vec_setm(ctx, ctx->num_ + 1) == 0)
    {
        a_size const idx = ctx->num_;
        a_byte *ptr = (a_byte *)a_vec_inc_(ctx);
        a_size i = 0, r = idx;
        while (i < r)
        {
            a_size const m = i + ((r - i) >> 1);
            a_byte *const cur = (a_byte *)ctx->ptr_ + ctx->siz_ * m;
            if (cmp(cur, key) > 0) { r = m; }
            else { i = m + 1; }
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

void *a_vec_search(a_vec const *ctx, void const *obj, int (*cmp)(void const *, void const *))
{
    return bsearch(obj, ctx->ptr_, ctx->num_, ctx->siz_, cmp);
}

void *a_vec_insert(a_vec *ctx, a_size idx)
{
    if (a_vec_setm(ctx, ctx->num_ + 1) == 0)
    {
        if (idx < ctx->num_)
        {
            a_byte *const p = (a_byte *)ctx->ptr_ + ctx->siz_ * idx;
            a_move(p + ctx->siz_, p, (ctx->num_ - idx) * ctx->siz_);
            ++ctx->num_;
            return p;
        }
        return a_vec_inc_(ctx);
    }
    return A_NULL;
}

void *a_vec_push_fore(a_vec *ctx) { return a_vec_insert(ctx, 0); }

void *a_vec_push_back(a_vec *ctx)
{
    if (a_vec_setm(ctx, ctx->num_ + 1) == 0)
    {
        return a_vec_inc_(ctx);
    }
    return A_NULL;
}

void *a_vec_remove(a_vec *ctx, a_size idx)
{
    if (idx + 1 < ctx->num_)
    {
        a_byte *const p = (a_byte *)ctx->ptr_ + ctx->siz_ * idx;
        a_byte *const q = p + ctx->siz_;
        if (ctx->num_ < ctx->mem_)
        {
            a_byte *const ptr = (a_byte *)ctx->ptr_ + ctx->siz_ * ctx->num_--;
            a_copy(ptr, p, ctx->siz_);
            a_move(p, q, (a_size)(ptr - q));
            return ptr;
        }
        else
        {
            a_byte *const ptr = (a_byte *)ctx->ptr_ + ctx->siz_ * --ctx->num_;
            a_swap(p, q, (a_size)(ptr - p));
            return ptr;
        }
    }
    return ctx->num_ ? a_vec_dec_(ctx) : A_NULL;
}

void *a_vec_pull_fore(a_vec *ctx) { return a_vec_remove(ctx, 0); }

void *a_vec_pull_back(a_vec *ctx)
{
    return ctx->num_ ? a_vec_dec_(ctx) : A_NULL;
}

int a_vec_store(a_vec *ctx, a_size idx, void *ptr, a_size num, int (*copy)(void *, void const *))
{
    int rc = a_vec_setm(ctx, ctx->num_ + num);
    if (rc == 0 && num)
    {
        a_byte *p = (a_byte *)ctx->ptr_ + ctx->siz_ * ctx->num_;
        a_size n = ctx->siz_ * num;
        if (idx < ctx->num_)
        {
            a_byte *const q = p;
            p = (a_byte *)ctx->ptr_ + ctx->siz_ * idx;
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
    return rc;
}

int a_vec_erase(a_vec *ctx, a_size idx, a_size num, void (*dtor)(void *))
{
    int rc = A_SUCCESS;
    a_size const n = idx + num;
    if (dtor && ctx->num_)
    {
        a_size i = (n <= ctx->num_ ? n : ctx->num_);
        a_byte *p = (a_byte *)ctx->ptr_ + ctx->siz_ * idx;
        for (; i > idx; --i, p += ctx->siz_) { dtor(p); }
    }
    if (n < ctx->num_)
    {
        a_byte *const p = (a_byte *)ctx->ptr_ + ctx->siz_ * idx;
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
