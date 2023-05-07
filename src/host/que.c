#include "a/host/que.h"

#undef a_que_at
#undef a_que_fore
#undef a_que_back
#undef a_que_fore_
#undef a_que_back_
#undef a_que_insert
#undef a_que_remove
#undef a_que_push_fore
#undef a_que_push_back
#undef a_que_pull_fore
#undef a_que_pull_back

static a_que_node_s *a_que_node_new(a_que_s *const ctx)
{
    a_que_node_s *node = A_NULL;
    if (ctx->_cur)
    {
        node = ctx->_ptr[--ctx->_cur];
    }
    else
    {
        node = (a_que_node_s *)a_alloc(A_NULL, sizeof(a_que_node_s));
        if (a_unlikely(node == A_NULL))
        {
            return node;
        }
        node->_data = A_NULL;
    }
    if (node->_data == A_NULL)
    {
        node->_data = a_alloc(A_NULL, ctx->_size);
        if (a_unlikely(node->_data == A_NULL))
        {
            a_alloc(node, 0);
            return A_NULL;
        }
    }
    ++ctx->_num;
    return node;
}

static int a_que_node_die(a_que_s *const ctx, a_que_node_s *const obj)
{
    if (obj == A_NULL)
    {
        return A_INVALID;
    }
    if (ctx->_mem <= ctx->_cur)
    {
        a_size_t const mem = ctx->_mem + (ctx->_mem >> 1) + 1;
        a_que_node_s **const ptr = (a_que_node_s **)a_alloc(ctx->_ptr, sizeof(a_vptr_t) * mem);
        if (a_unlikely(ptr == A_NULL))
        {
            return A_FAILURE;
        }
        ctx->_ptr = ptr;
        ctx->_mem = mem;
    }
    ctx->_ptr[ctx->_cur++] = obj;
    --ctx->_num;
    return A_SUCCESS;
}

static a_void_t a_que_drop_(a_que_s *const ctx)
{
    while (a_list_used(&ctx->_head))
    {
        a_que_node_s *const node = a_que_from(ctx->_head.prev);
        if (a_unlikely(a_que_node_die(ctx, node)))
        {
            break;
        }
        a_list_del_node(&node->_node);
        a_list_dtor(&node->_node);
    }
}

static A_INLINE a_void_t a_que_dtor_nop(a_vptr_t const vptr) { (void)(vptr); }

a_que_s *a_que_new(a_size_t const size)
{
    a_que_s *const ctx = (a_que_s *)a_alloc(A_NULL, sizeof(a_que_s));
    if (ctx)
    {
        a_que_ctor(ctx, size);
    }
    return ctx;
}

a_void_t a_que_die(a_que_s *const ctx, a_void_t (*const dtor)(a_vptr_t))
{
    if (ctx)
    {
        a_que_dtor(ctx, dtor);
        a_alloc(ctx, 0);
    }
}

a_void_t a_que_ctor(a_que_s *const ctx, a_size_t const size)
{
    a_list_ctor(&ctx->_head);
    ctx->_size = size ? size : sizeof(a_cast_u);
    ctx->_ptr = A_NULL;
    ctx->_num = 0;
    ctx->_cur = 0;
    ctx->_mem = 0;
}

a_void_t a_que_dtor(a_que_s *const ctx, a_void_t (*dtor)(a_vptr_t))
{
    a_que_drop_(ctx);
    dtor = dtor ? dtor : a_que_dtor_nop;
    while (ctx->_cur)
    {
        --ctx->_cur;
        dtor(ctx->_ptr[ctx->_cur]->_data);
        a_alloc(ctx->_ptr[ctx->_cur]->_data, 0);
        a_alloc(ctx->_ptr[ctx->_cur], 0);
    }
    a_alloc(ctx->_ptr, 0);
    ctx->_ptr = A_NULL;
    ctx->_size = 0;
    ctx->_mem = 0;
}

a_que_s *a_que_move(a_que_s *const ctx, a_que_s *const obj)
{
    a_copy(ctx, obj, sizeof(*obj));
    a_zero(obj, sizeof(*obj));
    return ctx;
}

a_vptr_t a_que_at(a_que_s const *const ctx, a_imax_t const idx)
{
    a_imax_t cur = 0;
    a_vptr_t vptr = A_NULL;
    if (idx < 0)
    {
        a_list_foreach_prev(it, &ctx->_head)
        {
            if (--cur == idx)
            {
                vptr = a_que_from(it)->_data;
                break;
            }
        }
    }
    else
    {
        a_list_foreach_next(it, &ctx->_head)
        {
            if (cur++ == idx)
            {
                vptr = a_que_from(it)->_data;
                break;
            }
        }
    }
    return vptr;
}

a_void_t a_que_set(a_que_s *const ctx, a_size_t size, a_void_t (*const dtor)(a_vptr_t))
{
    size = size ? size : sizeof(a_cast_u);
    a_que_drop(ctx, dtor);
    ctx->_size = size;
}

a_void_t a_que_drop(a_que_s *const ctx, a_void_t (*dtor)(a_vptr_t))
{
    a_que_drop_(ctx);
    dtor = dtor ? dtor : a_que_dtor_nop;
    for (a_size_t cur = ctx->_cur; cur--; ctx->_ptr[cur]->_data = A_NULL)
    {
        dtor(ctx->_ptr[cur]->_data);
        a_alloc(ctx->_ptr[cur]->_data, 0);
    }
}

a_int_t a_que_swap_(a_que_s const *const ctx, a_vptr_t const lhs, a_vptr_t const rhs)
{
    if (lhs == rhs)
    {
        return A_SUCCESS;
    }
    int ok = A_FAILURE;
    a_que_node_s *l = A_NULL;
    a_que_node_s *r = A_NULL;
    a_list_foreach_next(it, &ctx->_head)
    {
        a_que_node_s *const node = a_que_from(it);
        if (node->_data == lhs)
        {
            l = node;
        }
        else if (node->_data == rhs)
        {
            r = node;
        }
        if (l && r)
        {
            a_list_swap_node(&l->_node, &r->_node);
            ok = A_SUCCESS;
            break;
        }
    }
    return ok;
}

a_void_t a_que_swap(a_que_s const *const ctx, a_size_t lhs, a_size_t rhs)
{
    a_size_t cur = 0;
    a_size_t const num = ctx->_num - 1;
    lhs = lhs < ctx->_num ? lhs : num;
    rhs = rhs < ctx->_num ? rhs : num;
    if (lhs != rhs)
    {
        a_que_node_s *l = A_NULL;
        a_que_node_s *r = A_NULL;
        a_list_foreach_next(it, &ctx->_head)
        {
            if (cur == lhs)
            {
                // because lhs less than num
                // it's never a null pointer
                l = a_que_from(it);
            }
            else if (cur == rhs)
            {
                // because rhs less than num
                // it's never a null pointer
                r = a_que_from(it);
            }
            if (l && r)
            {
                a_list_swap_node(&l->_node, &r->_node);
                break;
            }
            ++cur;
        }
    }
}

a_void_t a_que_sort_fore(a_que_s const *const ctx, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    if (ctx->_num > 1)
    {
        a_list_s *pt = A_NULL;
        a_list_s *const it = ctx->_head.next;
        for (a_list_s *at = it->next; at != &ctx->_head; at = at->next)
        {
            a_vptr_t const lhs = a_que_from(it)->_data;
            a_vptr_t const rhs = a_que_from(at)->_data;
            if (cmp(lhs, rhs) > 0)
            {
                pt = at;
            }
            else
            {
                break;
            }
        }
        if (pt)
        {
            a_list_del_(it, it);
            a_list_add_(pt->next, pt, it, it);
        }
    }
}

a_void_t a_que_sort_back(a_que_s const *const ctx, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    if (ctx->_num > 1)
    {
        a_list_s *pt = A_NULL;
        a_list_s *const it = ctx->_head.prev;
        for (a_list_s *at = it->prev; at != &ctx->_head; at = at->prev)
        {
            a_vptr_t const lhs = a_que_from(at)->_data;
            a_vptr_t const rhs = a_que_from(it)->_data;
            if (cmp(lhs, rhs) > 0)
            {
                pt = at;
            }
            else
            {
                break;
            }
        }
        if (pt)
        {
            a_list_del_(it, it);
            a_list_add_(pt, pt->prev, it, it);
        }
    }
}

a_vptr_t a_que_push_fore(a_que_s *const ctx)
{
    a_que_node_s *const node = a_que_node_new(ctx);
    if (a_unlikely(node == A_NULL))
    {
        return node;
    }
    a_list_add_next(&ctx->_head, &node->_node);
    return node->_data;
}

a_vptr_t a_que_push_back(a_que_s *const ctx)
{
    a_que_node_s *const node = a_que_node_new(ctx);
    if (a_unlikely(node == A_NULL))
    {
        return node;
    }
    a_list_add_prev(&ctx->_head, &node->_node);
    return node->_data;
}

a_vptr_t a_que_pull_fore(a_que_s *const ctx)
{
    a_vptr_t data = A_NULL;
    if (a_list_used(&ctx->_head))
    {
        a_que_node_s *const node = a_que_from(ctx->_head.next);
        if (a_unlikely(a_que_node_die(ctx, node)))
        {
            return data;
        }
        a_list_del_node(&node->_node);
        a_list_dtor(&node->_node);
        data = node->_data;
    }
    return data;
}

a_vptr_t a_que_pull_back(a_que_s *const ctx)
{
    a_vptr_t data = A_NULL;
    if (a_list_used(&ctx->_head))
    {
        a_que_node_s *const node = a_que_from(ctx->_head.prev);
        if (a_unlikely(a_que_node_die(ctx, node)))
        {
            return data;
        }
        a_list_del_node(&node->_node);
        a_list_dtor(&node->_node);
        data = node->_data;
    }
    return data;
}

a_vptr_t a_que_insert(a_que_s *const ctx, a_size_t const idx)
{
    if (idx < ctx->_num)
    {
        a_size_t cur = 0;
        a_que_node_s *const node = a_que_node_new(ctx);
        if (a_unlikely(node == A_NULL))
        {
            return node;
        }
        a_list_foreach_next(it, &ctx->_head)
        {
            if (cur++ == idx)
            {
                a_list_add_prev(it, &node->_node);
                break;
            }
        }
        return node->_data;
    }
    return a_que_push_back(ctx);
}

a_vptr_t a_que_remove(a_que_s *const ctx, a_size_t const idx)
{
    if (idx < ctx->_num)
    {
        a_size_t cur = 0;
        a_que_node_s *node = A_NULL;
        a_list_foreach_next(it, &ctx->_head)
        {
            if (cur++ == idx)
            {
                // because idx less than num
                // it's never a null pointer
                node = a_que_from(it);
                break;
            }
        }
        if (a_unlikely(a_que_node_die(ctx, node)))
        {
            return A_NULL;
        }
        a_list_del_node(&node->_node);
        a_list_dtor(&node->_node);
        return node->_data;
    }
    return a_que_pull_back(ctx);
}
