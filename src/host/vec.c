#include "a/host/vec.h"

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

static A_INLINE void *a_vec_inc_(a_vec_s *const ctx)
{
    return (a_byte_t *)ctx->_ptr + ctx->_siz * ctx->_num++;
}

static A_INLINE void *a_vec_dec_(a_vec_s *const ctx)
{
    return (a_byte_t *)ctx->_ptr + ctx->_siz * --ctx->_num;
}

static void a_vec_drop_(a_vec_s *const ctx, a_size_t const bot, void (*const dtor)(void *))
{
    if (dtor)
    {
        while (ctx->_num > bot)
        {
            dtor(a_vec_dec_(ctx));
        }
    }
    ctx->_num = bot;
}

static int a_vec_alloc(a_vec_s *const ctx, a_size_t const num)
{
    if (ctx->_mem <= num)
    {
        a_size_t mem = ctx->_mem;
        do
        {
            mem += (mem >> 1) + 1;
        } while (mem < num);
        a_size_t const siz = a_size_up(sizeof(void *), ctx->_siz * mem);
        void *ptr = a_alloc(ctx->_ptr, siz);
        if (a_unlikely(ptr == A_NULL))
        {
            return A_FAILURE;
        }
        ctx->_mem = mem;
        ctx->_ptr = ptr;
    }
    return A_SUCCESS;
}

a_vec_s *a_vec_new(a_size_t const size)
{
    a_vec_s *const ctx = (a_vec_s *)a_alloc(A_NULL, sizeof(a_vec_s));
    if (ctx)
    {
        a_vec_ctor(ctx, size);
    }
    return ctx;
}

void a_vec_die(a_vec_s *const ctx, void (*const dtor)(void *))
{
    if (ctx)
    {
        a_vec_dtor(ctx, dtor);
        a_alloc(ctx, 0);
    }
}

void a_vec_ctor(a_vec_s *const ctx, a_size_t const size)
{
    ctx->_siz = size ? size : sizeof(a_cast_u);
    ctx->_ptr = A_NULL;
    ctx->_mem = 0;
    ctx->_num = 0;
}

void a_vec_dtor(a_vec_s *const ctx, void (*const dtor)(void *))
{
    if (ctx->_ptr)
    {
        a_vec_drop_(ctx, 0, dtor);
        ctx->_ptr = a_alloc(ctx->_ptr, 0);
    }
    ctx->_mem = 0;
    ctx->_siz = 0;
}

int a_vec_copy(a_vec_s *const ctx, a_vec_s const *const obj, int (*const dup)(void *, void const *))
{
    ctx->_ptr = a_alloc(A_NULL, obj->_mem * obj->_siz);
    if (a_unlikely(ctx->_ptr == A_NULL))
    {
        return A_FAILURE;
    }
    ctx->_siz = obj->_siz;
    ctx->_num = obj->_num;
    ctx->_mem = obj->_mem;
    a_size_t const size = obj->_num * obj->_siz;
    if (dup)
    {
        a_byte_t *dst = (a_byte_t *)ctx->_ptr;
        a_byte_t *src = (a_byte_t *)obj->_ptr;
        for (a_byte_t *const end = src + size; src != end;)
        {
            dup(dst, src);
            dst += ctx->_siz;
            src += ctx->_siz;
        }
    }
    else
    {
        a_copy(ctx->_ptr, obj->_ptr, size);
    }
    return A_SUCCESS;
}

a_vec_s *a_vec_move(a_vec_s *const ctx, a_vec_s *const obj)
{
    a_copy(ctx, obj, sizeof(*obj));
    a_zero(obj, sizeof(*obj));
    return ctx;
}

void a_vec_set(a_vec_s *const ctx, a_size_t size, void (*const dtor)(void *))
{
    size = size ? size : sizeof(a_cast_u);
    a_vec_drop_(ctx, 0, dtor);
    ctx->_mem = ctx->_mem * ctx->_siz / size;
    ctx->_siz = size;
}

int a_vec_make(a_vec_s *const ctx, a_size_t const num, void (*const dtor)(void *))
{
    if (a_unlikely(a_vec_alloc(ctx, num)))
    {
        return A_FAILURE;
    }
    a_vec_drop_(ctx, num, dtor);
    return A_SUCCESS;
}

void a_vec_drop(a_vec_s *const ctx, void (*const dtor)(void *))
{
    a_vec_drop_(ctx, 0, dtor);
}

void a_vec_swap(a_vec_s const *const ctx, a_size_t lhs, a_size_t rhs)
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

void a_vec_sort(a_vec_s const *const ctx, int (*const cmp)(void const *, void const *))
{
    qsort(ctx->_ptr, ctx->_num, ctx->_siz, cmp);
}

void a_vec_sort_fore(a_vec_s const *const ctx, int (*const cmp)(void const *, void const *))
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

void a_vec_sort_back(a_vec_s const *const ctx, int (*const cmp)(void const *, void const *))
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

void *a_vec_search(a_vec_s const *const ctx, void const *const obj, int (*const cmp)(void const *, void const *))
{
    return bsearch(obj, ctx->_ptr, ctx->_num, ctx->_siz, cmp);
}

void *a_vec_insert(a_vec_s *const ctx, a_size_t const idx)
{
    if (a_unlikely(a_vec_alloc(ctx, ctx->_num)))
    {
        return A_NULL;
    }
    if (idx < ctx->_num)
    {
        a_byte_t *const src = (a_byte_t *)ctx->_ptr + ctx->_siz * (idx + 0);
        a_byte_t *const dst = (a_byte_t *)ctx->_ptr + ctx->_siz * (idx + 1);
        a_move(dst, src, (ctx->_num - idx) * ctx->_siz);
        ++ctx->_num;
        return src;
    }
    return a_vec_inc_(ctx);
}

void *a_vec_push_fore(a_vec_s *const ctx) { return a_vec_insert(ctx, 0); }

void *a_vec_push_back(a_vec_s *const ctx)
{
    if (a_unlikely(a_vec_alloc(ctx, ctx->_num)))
    {
        return A_NULL;
    }
    return a_vec_inc_(ctx);
}

void *a_vec_remove(a_vec_s *const ctx, a_size_t const idx)
{
    if (ctx->_num && idx < ctx->_num - 1)
    {
        if (a_unlikely(a_vec_alloc(ctx, ctx->_num)))
        {
            return A_NULL;
        }
        a_byte_t *const ptr = (a_byte_t *)ctx->_ptr + ctx->_siz * ctx->_num;
        a_byte_t *const dst = (a_byte_t *)ctx->_ptr + ctx->_siz * (idx + 0);
        a_byte_t *const src = (a_byte_t *)ctx->_ptr + ctx->_siz * (idx + 1);
        a_copy(ptr, dst, ctx->_siz);
        a_move(dst, src, (a_size_t)(ptr - src));
        --ctx->_num;
        return ptr;
    }
    return a_likely(ctx->_num) ? a_vec_dec_(ctx) : A_NULL;
}

void *a_vec_pull_fore(a_vec_s *const ctx) { return a_vec_remove(ctx, 0); }

void *a_vec_pull_back(a_vec_s *const ctx)
{
    return a_likely(ctx->_num) ? a_vec_dec_(ctx) : A_NULL;
}
