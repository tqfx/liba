#include "a/host/vector.h"

#undef a_vector_at
#undef a_vector_at_
#undef a_vector_idx
#undef a_vector_ptr
#undef a_vector_end
#undef a_vector_top
#undef a_vector_top_
#undef a_vector_push
#undef a_vector_pull
#undef a_vector_search
#undef a_vector_insert
#undef a_vector_remove
#undef a_vector_push_fore
#undef a_vector_push_back
#undef a_vector_pull_fore
#undef a_vector_pull_back

static A_INLINE a_vptr_t a_vector_inc_(a_vector_s *const ctx)
{
    a_vptr_t const last = ctx->_tail;
    ctx->_tail = a_byte_p(ctx->_tail) + ctx->_size;
    return (void)(++ctx->_num), last;
}

static A_INLINE a_vptr_t a_vector_dec_(a_vector_s *const ctx)
{
    ctx->_tail = a_byte_p(ctx->_tail) - ctx->_size;
    return (void)(--ctx->_num), ctx->_tail;
}

static a_void_t a_vector_drop_(a_vector_s *const ctx, a_size_t const bot)
{
    if (ctx->dtor)
    {
        while (ctx->_num > bot)
        {
            ctx->dtor(a_vector_dec_(ctx));
        }
    }
    ctx->_tail = a_byte_p(ctx->_head) + ctx->_size * bot;
    ctx->_num = bot;
}

static a_int_t a_vector_alloc(a_vector_s *const ctx, a_size_t const num)
{
    if (ctx->_mem <= num)
    {
        a_size_t mem = ctx->_mem;
        do
        {
            mem += (mem >> 1) + 1;
        } while (mem < num);
        a_size_t const mem_ = mem * ctx->_size;
        a_size_t const num_ = ctx->_num * ctx->_size;
        a_size_t const size = a_align(sizeof(a_vptr_t), mem_);
        a_vptr_t const head = a_alloc(ctx->_head, size);
        if (a_unlikely(head == A_NULL))
        {
            return A_FAILURE;
        }
        ctx->_mem = mem;
        ctx->_head = head;
        ctx->_tail = a_byte_p(head) + num_;
        ctx->_last = a_byte_p(head) + mem_;
    }
    return A_SUCCESS;
}

a_vector_s *a_vector_new(a_size_t const size,
                         a_void_t (*const ctor)(a_vptr_t),
                         a_void_t (*const dtor)(a_vptr_t))
{
    a_vector_s *const ctx = (a_vector_s *)a_alloc(A_NULL, sizeof(a_vector_s));
    if (ctx)
    {
        a_vector_ctor(ctx, size, ctor, dtor);
    }
    return ctx;
}

a_void_t a_vector_die(a_vector_s *const ctx)
{
    if (ctx)
    {
        a_vector_dtor(ctx);
        a_alloc(ctx, 0);
    }
}

a_void_t a_vector_ctor(a_vector_s *const ctx, a_size_t const size,
                       a_void_t (*const ctor)(a_vptr_t),
                       a_void_t (*const dtor)(a_vptr_t))
{
    ctx->_size = size ? size : sizeof(a_cast_u);
    ctx->ctor = ctor;
    ctx->dtor = dtor;
    ctx->_last = A_NULL;
    ctx->_tail = A_NULL;
    ctx->_head = A_NULL;
    ctx->_num = 0;
    ctx->_mem = 0;
}

a_void_t a_vector_dtor(a_vector_s *const ctx)
{
    if (ctx->_head)
    {
        a_vector_drop_(ctx, 0);
        ctx->_head = a_alloc(ctx->_head, 0);
    }
    ctx->_tail = A_NULL;
    ctx->_last = A_NULL;
    ctx->_size = 0;
    ctx->_mem = 0;
}

a_int_t a_vector_copy(a_vector_s *const ctx, a_vector_s const *const obj, a_int_t (*const dup)(a_vptr_t, a_cptr_t))
{
    a_size_t const num_ = obj->_num * obj->_size;
    a_size_t const mem_ = obj->_mem * obj->_size;
    ctx->_head = a_alloc(A_NULL, mem_);
    if (a_unlikely(ctx->_head == A_NULL))
    {
        return A_FAILURE;
    }
    ctx->ctor = obj->ctor;
    ctx->dtor = obj->dtor;
    ctx->_num = obj->_num;
    ctx->_mem = obj->_mem;
    ctx->_size = obj->_size;
    ctx->_tail = a_byte_p(ctx->_head) + num_;
    ctx->_last = a_byte_p(ctx->_head) + mem_;
    if (dup)
    {
        a_byte_t *dst = a_byte_p(ctx->_head);
        a_byte_t *src = a_byte_p(obj->_head);
        while (src != obj->_tail)
        {
            dup(dst, src);
            dst += obj->_size;
            src += obj->_size;
        }
    }
    else
    {
        a_copy(ctx->_head, obj->_head, num_);
    }
    return A_SUCCESS;
}

a_vector_s *a_vector_move(a_vector_s *const ctx, a_vector_s *const obj)
{
    a_copy(ctx, obj, sizeof(*obj));
    a_zero(obj, sizeof(*obj));
    return ctx;
}

a_void_t a_vector_set(a_vector_s *const ctx, a_size_t size,
                      a_void_t (*const ctor)(a_vptr_t),
                      a_void_t (*const dtor)(a_vptr_t))
{
    size = size ? size : sizeof(a_cast_u);
    a_vector_drop_(ctx, 0);
    ctx->_mem = ctx->_mem * ctx->_size / size;
    ctx->_size = size;
    ctx->ctor = ctor;
    ctx->dtor = dtor;
}

a_int_t a_vector_make(a_vector_s *const ctx, a_size_t const num)
{
    if (a_unlikely(a_vector_alloc(ctx, num)))
    {
        return A_FAILURE;
    }
    a_vector_drop_(ctx, num);
    return A_SUCCESS;
}

a_void_t a_vector_drop(a_vector_s *const ctx)
{
    a_vector_drop_(ctx, 0);
}

a_void_t a_vector_swap(a_vector_s const *const ctx, a_size_t lhs, a_size_t rhs)
{
    a_size_t const num = ctx->_num - 1;
    lhs = lhs < ctx->_num ? lhs : num;
    rhs = rhs < ctx->_num ? rhs : num;
    if (lhs != rhs)
    {
        a_vptr_t const lobj = a_byte_p(ctx->_head) + lhs * ctx->_size;
        a_vptr_t const robj = a_byte_p(ctx->_head) + rhs * ctx->_size;
        a_swap(lobj, robj, ctx->_size);
    }
}

a_void_t a_vector_sort(a_vector_s const *const ctx, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    qsort(ctx->_head, ctx->_num, ctx->_size, cmp);
}

a_void_t a_vector_sort_fore(a_vector_s const *const ctx, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    if (ctx->_num > 1)
    {
        a_byte_t *ptr = a_byte_p(ctx->_head);
        a_byte_t *const end = a_byte_p(ctx->_tail) - ctx->_size;
        do
        {
            a_byte_t *const cur = ptr + ctx->_size;
            if (cmp(ptr, cur) > 0)
            {
                a_swap(cur, ptr, ctx->_size);
            }
            else
            {
                break;
            }
            ptr = cur;
        } while (ptr != end);
    }
}

a_void_t a_vector_sort_back(a_vector_s const *const ctx, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    if (ctx->_num > 1)
    {
        a_byte_t *ptr = a_byte_p(ctx->_tail) - ctx->_size;
        do
        {
            a_byte_t *const cur = ptr - ctx->_size;
            if (cmp(cur, ptr) > 0)
            {
                a_swap(cur, ptr, ctx->_size);
            }
            else
            {
                break;
            }
            ptr = cur;
        } while (ptr != ctx->_head);
    }
}

a_vptr_t a_vector_search(a_vector_s const *const ctx, a_cptr_t const obj, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    return bsearch(obj, ctx->_head, ctx->_num, ctx->_size, cmp);
}

a_vptr_t a_vector_insert(a_vector_s *const ctx, a_size_t const idx)
{
    if (a_unlikely(a_vector_alloc(ctx, ctx->_num)))
    {
        return A_NULL;
    }
    if (idx < ctx->_num)
    {
        a_byte_t *const ptr = a_byte_p(ctx->_tail);
        a_byte_t *const src = a_byte_p(ctx->_head) + ctx->_size * (idx + 0);
        a_byte_t *const dst = a_byte_p(ctx->_head) + ctx->_size * (idx + 1);
        a_move(dst, src, a_size_c(ptr - src));
        a_vector_inc_(ctx);
        if (ctx->ctor)
        {
            ctx->ctor(src);
        }
        return src;
    }
    a_vptr_t const obj = a_vector_inc_(ctx);
    if (ctx->ctor)
    {
        ctx->ctor(obj);
    }
    return obj;
}

a_vptr_t a_vector_push_fore(a_vector_s *const ctx) { return a_vector_insert(ctx, 0); }

a_vptr_t a_vector_push_back(a_vector_s *const ctx)
{
    if (a_unlikely(a_vector_alloc(ctx, ctx->_num)))
    {
        return A_NULL;
    }
    a_vptr_t const obj = a_vector_inc_(ctx);
    if (ctx->ctor)
    {
        ctx->ctor(obj);
    }
    return obj;
}

a_vptr_t a_vector_remove(a_vector_s *const ctx, a_size_t const idx)
{
    if (ctx->_num && idx < ctx->_num - 1)
    {
        if (a_unlikely(a_vector_alloc(ctx, ctx->_num)))
        {
            return A_NULL;
        }
        a_byte_t *const ptr = a_byte_p(ctx->_tail);
        a_byte_t *const dst = a_byte_p(ctx->_head) + ctx->_size * (idx + 0);
        a_byte_t *const src = a_byte_p(ctx->_head) + ctx->_size * (idx + 1);
        a_copy(ptr, dst, ctx->_size);
        a_move(dst, src, a_size_c(ptr - src));
        a_vector_dec_(ctx);
        return ptr;
    }
    return a_likely(ctx->_head != ctx->_tail) ? a_vector_dec_(ctx) : A_NULL;
}

a_vptr_t a_vector_pull_fore(a_vector_s *const ctx) { return a_vector_remove(ctx, 0); }

a_vptr_t a_vector_pull_back(a_vector_s *const ctx)
{
    return a_likely(ctx->_head != ctx->_tail) ? a_vector_dec_(ctx) : A_NULL;
}
