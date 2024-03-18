#include "a/vec.h"
#include <stdlib.h>

#undef a_vec_at
#undef a_vec_at_
#undef a_vec_idx
#undef a_vec_ptr
#undef a_vec_end
#undef a_vec_top
#undef a_vec_end_
#undef a_vec_top_
#undef a_vec_push
#undef a_vec_pull
#undef a_vec_search
#undef a_vec_insert
#undef a_vec_remove
#undef a_vec_push_fore
#undef a_vec_push_back
#undef a_vec_pull_fore
#undef a_vec_pull_back

static A_INLINE void *a_vec_inc_(a_vec *ctx)
{
    return (a_byte *)ctx->ptr_ + ctx->siz_ * ctx->num_++;
}

static A_INLINE void *a_vec_dec_(a_vec *ctx)
{
    return (a_byte *)ctx->ptr_ + ctx->siz_ * --ctx->num_;
}

static void a_vec_drop_(a_vec *ctx, a_size bot, void (*dtor)(void *))
{
    if (dtor)
    {
        while (ctx->num_ > bot) { dtor(a_vec_dec_(ctx)); }
    }
    ctx->num_ = bot;
}

static int a_vec_alloc(a_vec *ctx, a_size num)
{
    if (ctx->mem_ <= num)
    {
        a_size mem = ctx->mem_;
        do {
            mem += (mem >> 1) + 1;
        } while (mem < num);
        a_size const siz = a_size_up(sizeof(void *), ctx->siz_ * mem);
        void *ptr = a_alloc(ctx->ptr_, siz);
        if (a_unlikely(!ptr)) { return A_FAILURE; }
        ctx->ptr_ = ptr;
        ctx->mem_ = mem;
    }
    return A_SUCCESS;
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
    ctx->siz_ = size ? size : sizeof(a_cast);
    ctx->ptr_ = A_NULL;
    ctx->num_ = 0;
    ctx->mem_ = 0;
}

void a_vec_dtor(a_vec *ctx, void (*dtor)(void *))
{
    if (ctx->ptr_)
    {
        a_vec_drop_(ctx, 0, dtor);
        ctx->ptr_ = a_alloc(ctx->ptr_, 0);
    }
    ctx->siz_ = 0;
    ctx->mem_ = 0;
}

int a_vec_copy(a_vec *ctx, a_vec const *obj, int (*dup)(void *, void const *))
{
    ctx->ptr_ = a_alloc(A_NULL, obj->mem_ * obj->siz_);
    if (a_unlikely(!ctx->ptr_)) { return A_FAILURE; }
    ctx->num_ = obj->num_;
    ctx->mem_ = obj->mem_;
    ctx->siz_ = obj->siz_;
    if (dup)
    {
        a_byte *dst = (a_byte *)ctx->ptr_;
        a_byte *src = (a_byte *)obj->ptr_;
        for (a_size num = obj->num_; num; --num)
        {
            dup(dst, src);
            dst += ctx->siz_;
            src += ctx->siz_;
        }
    }
    else
    {
        a_copy(ctx->ptr_, obj->ptr_, obj->num_ * obj->siz_);
    }
    return A_SUCCESS;
}

void a_vec_move(a_vec *ctx, a_vec *obj)
{
    a_copy(ctx, obj, sizeof(*obj));
    a_zero(obj, sizeof(*obj));
}

void a_vec_edit(a_vec *ctx, a_size size, void (*dtor)(void *))
{
    size = size ? size : sizeof(a_cast);
    a_vec_drop_(ctx, 0, dtor);
    ctx->mem_ = ctx->mem_ * ctx->siz_ / size;
    ctx->siz_ = size;
}

int a_vec_make(a_vec *ctx, a_size num, void (*dtor)(void *))
{
    if (a_unlikely(a_vec_alloc(ctx, num))) { return A_FAILURE; }
    a_vec_drop_(ctx, num, dtor);
    return A_SUCCESS;
}

void a_vec_drop(a_vec *ctx, void (*dtor)(void *))
{
    a_vec_drop_(ctx, 0, dtor);
}

void a_vec_swap(a_vec const *ctx, a_size lhs, a_size rhs)
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

void a_vec_sort(a_vec const *ctx, int (*cmp)(void const *, void const *))
{
    qsort(ctx->ptr_, ctx->num_, ctx->siz_, cmp);
}

void a_vec_sort_fore(a_vec const *ctx, int (*cmp)(void const *, void const *))
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

void a_vec_sort_back(a_vec const *ctx, int (*cmp)(void const *, void const *))
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

void *a_vec_search(a_vec const *ctx, void const *obj, int (*cmp)(void const *, void const *))
{
    return bsearch(obj, ctx->ptr_, ctx->num_, ctx->siz_, cmp);
}

void *a_vec_insert(a_vec *ctx, a_size idx)
{
    if (a_unlikely(a_vec_alloc(ctx, ctx->num_))) { return A_NULL; }
    if (idx < ctx->num_)
    {
        a_byte *const src = (a_byte *)ctx->ptr_ + ctx->siz_ * (idx + 0);
        a_byte *const dst = (a_byte *)ctx->ptr_ + ctx->siz_ * (idx + 1);
        a_move(dst, src, (ctx->num_ - idx) * ctx->siz_);
        ++ctx->num_;
        return src;
    }
    return a_vec_inc_(ctx);
}

void *a_vec_push_fore(a_vec *ctx) { return a_vec_insert(ctx, 0); }

void *a_vec_push_back(a_vec *ctx)
{
    if (a_unlikely(a_vec_alloc(ctx, ctx->num_))) { return A_NULL; }
    return a_vec_inc_(ctx);
}

void *a_vec_remove(a_vec *ctx, a_size idx)
{
    if (ctx->num_ && idx < ctx->num_ - 1)
    {
        if (a_unlikely(a_vec_alloc(ctx, ctx->num_))) { return A_NULL; }
        a_byte *const ptr = (a_byte *)ctx->ptr_ + ctx->siz_ * ctx->num_;
        a_byte *const dst = (a_byte *)ctx->ptr_ + ctx->siz_ * (idx + 0);
        a_byte *const src = (a_byte *)ctx->ptr_ + ctx->siz_ * (idx + 1);
        a_copy(ptr, dst, ctx->siz_);
        a_move(dst, src, (a_size)(ptr - src));
        --ctx->num_;
        return ptr;
    }
    return a_likely(ctx->num_) ? a_vec_dec_(ctx) : A_NULL;
}

void *a_vec_pull_fore(a_vec *ctx) { return a_vec_remove(ctx, 0); }

void *a_vec_pull_back(a_vec *ctx)
{
    return a_likely(ctx->num_) ? a_vec_dec_(ctx) : A_NULL;
}
