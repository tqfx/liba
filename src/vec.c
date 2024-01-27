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
    return (a_byte *)ctx->_ptr + ctx->_siz * ctx->_num++;
}

static A_INLINE void *a_vec_dec_(a_vec *ctx)
{
    return (a_byte *)ctx->_ptr + ctx->_siz * --ctx->_num;
}

static void a_vec_drop_(a_vec *ctx, a_size bot, void (*dtor)(void *))
{
    if (dtor)
    {
        while (ctx->_num > bot) { dtor(a_vec_dec_(ctx)); }
    }
    ctx->_num = bot;
}

static int a_vec_alloc(a_vec *ctx, a_size num)
{
    if (ctx->_mem <= num)
    {
        a_size mem = ctx->_mem;
        do {
            mem += (mem >> 1) + 1;
        } while (mem < num);
        a_size const siz = a_size_up(sizeof(void *), ctx->_siz * mem);
        void *ptr = a_alloc(ctx->_ptr, siz);
        if (a_unlikely(!ptr)) { return A_FAILURE; }
        ctx->_ptr = ptr;
        ctx->_mem = mem;
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
    ctx->_siz = size ? size : sizeof(a_cast);
    ctx->_ptr = A_NULL;
    ctx->_num = 0;
    ctx->_mem = 0;
}

void a_vec_dtor(a_vec *ctx, void (*dtor)(void *))
{
    if (ctx->_ptr)
    {
        a_vec_drop_(ctx, 0, dtor);
        ctx->_ptr = a_alloc(ctx->_ptr, 0);
    }
    ctx->_mem = 0;
    ctx->_siz = 0;
}

int a_vec_copy(a_vec *ctx, a_vec const *obj, int (*dup)(void *, void const *))
{
    ctx->_ptr = a_alloc(A_NULL, obj->_mem * obj->_siz);
    if (a_unlikely(!ctx->_ptr)) { return A_FAILURE; }
    ctx->_num = obj->_num;
    ctx->_mem = obj->_mem;
    ctx->_siz = obj->_siz;
    if (dup)
    {
        a_byte *dst = (a_byte *)ctx->_ptr;
        a_byte *src = (a_byte *)obj->_ptr;
        for (a_size num = obj->_num; num; --num)
        {
            dup(dst, src);
            dst += ctx->_siz;
            src += ctx->_siz;
        }
    }
    else
    {
        a_copy(ctx->_ptr, obj->_ptr, obj->_num * obj->_siz);
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
    ctx->_mem = ctx->_mem * ctx->_siz / size;
    ctx->_siz = size;
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

void a_vec_sort(a_vec const *ctx, int (*cmp)(void const *, void const *))
{
    qsort(ctx->_ptr, ctx->_num, ctx->_siz, cmp);
}

void a_vec_sort_fore(a_vec const *ctx, int (*cmp)(void const *, void const *))
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

void a_vec_sort_back(a_vec const *ctx, int (*cmp)(void const *, void const *))
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

void *a_vec_search(a_vec const *ctx, void const *obj, int (*cmp)(void const *, void const *))
{
    return bsearch(obj, ctx->_ptr, ctx->_num, ctx->_siz, cmp);
}

void *a_vec_insert(a_vec *ctx, a_size idx)
{
    if (a_unlikely(a_vec_alloc(ctx, ctx->_num))) { return A_NULL; }
    if (idx < ctx->_num)
    {
        a_byte *const src = (a_byte *)ctx->_ptr + ctx->_siz * (idx + 0);
        a_byte *const dst = (a_byte *)ctx->_ptr + ctx->_siz * (idx + 1);
        a_move(dst, src, (ctx->_num - idx) * ctx->_siz);
        ++ctx->_num;
        return src;
    }
    return a_vec_inc_(ctx);
}

void *a_vec_push_fore(a_vec *ctx) { return a_vec_insert(ctx, 0); }

void *a_vec_push_back(a_vec *ctx)
{
    if (a_unlikely(a_vec_alloc(ctx, ctx->_num))) { return A_NULL; }
    return a_vec_inc_(ctx);
}

void *a_vec_remove(a_vec *ctx, a_size idx)
{
    if (ctx->_num && idx < ctx->_num - 1)
    {
        if (a_unlikely(a_vec_alloc(ctx, ctx->_num))) { return A_NULL; }
        a_byte *const ptr = (a_byte *)ctx->_ptr + ctx->_siz * ctx->_num;
        a_byte *const dst = (a_byte *)ctx->_ptr + ctx->_siz * (idx + 0);
        a_byte *const src = (a_byte *)ctx->_ptr + ctx->_siz * (idx + 1);
        a_copy(ptr, dst, ctx->_siz);
        a_move(dst, src, (a_size)(ptr - src));
        --ctx->_num;
        return ptr;
    }
    return a_likely(ctx->_num) ? a_vec_dec_(ctx) : A_NULL;
}

void *a_vec_pull_fore(a_vec *ctx) { return a_vec_remove(ctx, 0); }

void *a_vec_pull_back(a_vec *ctx)
{
    return a_likely(ctx->_num) ? a_vec_dec_(ctx) : A_NULL;
}
