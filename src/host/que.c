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
        if (a_unlikely(!node))
        {
            return node;
        }
        node->_data = A_NULL;
    }
    if (!node->_data)
    {
        node->_data = a_alloc(A_NULL, ctx->_siz);
        if (a_unlikely(!node->_data))
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
    if (!obj)
    {
        return A_INVALID;
    }
    if (ctx->_mem <= ctx->_cur)
    {
        a_size_t const mem = ctx->_mem + (ctx->_mem >> 1) + 1;
        a_que_node_s **const ptr = (a_que_node_s **)a_alloc(ctx->_ptr, sizeof(void *) * mem);
        if (a_unlikely(!ptr))
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

static void a_que_drop_(a_que_s *const ctx)
{
    while (ctx->_head.next != &ctx->_head)
    {
        a_que_node_s *const node = (a_que_node_s *)ctx->_head.next;
        if (a_unlikely(a_que_node_die(ctx, node)))
        {
            break;
        }
        a_list_del_node(&node->_node);
        a_list_dtor(&node->_node);
    }
}

a_que_s *a_que_new(a_size_t const size)
{
    a_que_s *const ctx = (a_que_s *)a_alloc(A_NULL, sizeof(a_que_s));
    if (ctx)
    {
        a_que_ctor(ctx, size);
    }
    return ctx;
}

void a_que_die(a_que_s *const ctx, void (*const dtor)(void *))
{
    if (ctx)
    {
        a_que_dtor(ctx, dtor);
        a_alloc(ctx, 0);
    }
}

void a_que_ctor(a_que_s *const ctx, a_size_t const size)
{
    a_list_ctor(&ctx->_head);
    ctx->_siz = size ? size : sizeof(a_cast_u);
    ctx->_ptr = A_NULL;
    ctx->_num = 0;
    ctx->_cur = 0;
    ctx->_mem = 0;
}

void a_que_dtor(a_que_s *const ctx, void (*const dtor)(void *))
{
    a_que_drop_(ctx);
    a_que_node_s **node = ctx->_ptr;
    if (dtor)
    {
        for (; ctx->_cur; ++node, --ctx->_cur)
        {
            dtor((**node)._data);
            a_alloc((**node)._data, 0);
            a_alloc(*node, 0);
        }
    }
    else
    {
        for (; ctx->_cur; ++node, --ctx->_cur)
        {
            a_alloc((**node)._data, 0);
            a_alloc(*node, 0);
        }
    }
    a_alloc(ctx->_ptr, 0);
    ctx->_ptr = A_NULL;
    ctx->_siz = 0;
    ctx->_mem = 0;
}

void a_que_move(a_que_s *const ctx, a_que_s *const obj)
{
    a_copy(ctx, obj, sizeof(*obj));
    a_zero(obj, sizeof(*obj));
}

void *a_que_at(a_que_s const *const ctx, a_imax_t const idx)
{
    a_imax_t cur = 0;
    void *ptr = A_NULL;
    if (idx < 0)
    {
        a_list_foreach_prev(it, &ctx->_head)
        {
            if (--cur == idx)
            {
                ptr = ((a_que_node_s *)it)->_data;
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
                ptr = ((a_que_node_s *)it)->_data;
                break;
            }
        }
    }
    return ptr;
}

void a_que_drop(a_que_s *const ctx, void (*const dtor)(void *))
{
    a_que_drop_(ctx);
    a_que_node_s **node = ctx->_ptr;
    if (dtor)
    {
        for (a_size_t cur = ctx->_cur; cur; ++node, --cur)
        {
            dtor((**node)._data);
            a_alloc((**node)._data, 0);
            (**node)._data = A_NULL;
        }
    }
    else
    {
        for (a_size_t cur = ctx->_cur; cur; ++node, --cur)
        {
            a_alloc((**node)._data, 0);
            (**node)._data = A_NULL;
        }
    }
}

void a_que_edit(a_que_s *const ctx, a_size_t size, void (*const dtor)(void *))
{
    size = size ? size : sizeof(a_cast_u);
    a_que_drop(ctx, dtor);
    ctx->_siz = size;
}

int a_que_swap_(a_que_s const *const ctx, void *const lhs, void *const rhs)
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
        a_que_node_s *const node = (a_que_node_s *)it;
        if (node->_data == lhs || node->_data == rhs)
        {
            if (!l)
            {
                l = node;
            }
            else
            {
                r = node;
            }
        }
        if (r)
        {
            a_list_swap_node(&l->_node, &r->_node);
            ok = A_SUCCESS;
            break;
        }
    }
    return ok;
}

void a_que_swap(a_que_s const *const ctx, a_size_t lhs, a_size_t rhs)
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
            if (cur == lhs || cur == rhs)
            {
                // because lhs less than num
                // it's never a null pointer
                if (!l)
                {
                    l = (a_que_node_s *)it;
                }
                else
                {
                    r = (a_que_node_s *)it;
                }
                if (!it)
                {
                    break;
                }
            }
            if (r)
            {
                a_list_swap_node(&l->_node, &r->_node);
                break;
            }
            ++cur;
        }
    }
}

void a_que_sort_fore(a_que_s const *const ctx, int (*const cmp)(void const *, void const *))
{
    if (ctx->_num > 1)
    {
        a_list_s *pt = A_NULL;
        a_list_s *const it = ctx->_head.next;
        for (a_list_s *at = it->next; at != &ctx->_head; at = at->next)
        {
            void *const lhs = ((a_que_node_s *)it)->_data;
            void *const rhs = ((a_que_node_s *)at)->_data;
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
            /* a<->it<->b<->pt<->a */
            a_list_link(it->prev, it->next); // a<->b
            a_list_link(it, pt->next); // it<->a
            a_list_link(pt, it); // pt<->it
            /* a<->b<->pt<->it<->a */
        }
    }
}

void a_que_sort_back(a_que_s const *const ctx, int (*const cmp)(void const *, void const *))
{
    if (ctx->_num > 1)
    {
        a_list_s *pt = A_NULL;
        a_list_s *const it = ctx->_head.prev;
        for (a_list_s *at = it->prev; at != &ctx->_head; at = at->prev)
        {
            void *const lhs = ((a_que_node_s *)at)->_data;
            void *const rhs = ((a_que_node_s *)it)->_data;
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
            /* a<->pt<->b<->it<->a */
            a_list_link(it->prev, it->next); // b<->a
            a_list_link(pt->prev, it); // a<->it
            a_list_link(it, pt); // it<->pt
            /* a<->it<->pt<->b<->a */
        }
    }
}

void *a_que_push_fore(a_que_s *const ctx)
{
    a_que_node_s *const node = a_que_node_new(ctx);
    if (a_unlikely(!node))
    {
        return node;
    }
    a_list_add_next(&ctx->_head, &node->_node);
    return node->_data;
}

void *a_que_push_back(a_que_s *const ctx)
{
    a_que_node_s *const node = a_que_node_new(ctx);
    if (a_unlikely(!node))
    {
        return node;
    }
    a_list_add_prev(&ctx->_head, &node->_node);
    return node->_data;
}

void *a_que_pull_fore(a_que_s *const ctx)
{
    void *data = A_NULL;
    while (ctx->_head.next != &ctx->_head)
    {
        a_que_node_s *const node = (a_que_node_s *)ctx->_head.next;
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

void *a_que_pull_back(a_que_s *const ctx)
{
    void *data = A_NULL;
    while (ctx->_head.prev != &ctx->_head)
    {
        a_que_node_s *const node = (a_que_node_s *)ctx->_head.prev;
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

void *a_que_insert(a_que_s *const ctx, a_size_t const idx)
{
    if (idx < ctx->_num)
    {
        a_size_t cur = 0;
        a_que_node_s *const node = a_que_node_new(ctx);
        if (a_unlikely(!node))
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

void *a_que_remove(a_que_s *const ctx, a_size_t const idx)
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
                node = (a_que_node_s *)it;
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
