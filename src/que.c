#include "a/que.h"

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

static a_que_node *a_que_node_new(a_que *ctx)
{
    a_que_node *node = A_NULL;
    if (ctx->cur_)
    {
        node = ctx->ptr_[--ctx->cur_];
    }
    else
    {
        node = (a_que_node *)a_alloc(A_NULL, sizeof(a_que_node));
        if (a_unlikely(!node)) { return node; }
        node->data_ = A_NULL;
    }
    if (!node->data_)
    {
        node->data_ = a_alloc(A_NULL, ctx->siz_);
        if (a_unlikely(!node->data_))
        {
            a_alloc(node, 0);
            return A_NULL;
        }
    }
    ++ctx->num_;
    return node;
}

static int a_que_node_die(a_que *ctx, a_que_node *node)
{
    if (!node) { return A_INVALID; }
    if (ctx->mem_ <= ctx->cur_)
    {
        a_size const mem = ctx->mem_ + (ctx->mem_ >> 1) + 1;
        a_que_node **const ptr = (a_que_node **)a_alloc(ctx->ptr_, sizeof(void *) * mem);
        if (a_unlikely(!ptr)) { return A_FAILURE; }
        ctx->ptr_ = ptr;
        ctx->mem_ = mem;
    }
    ctx->ptr_[ctx->cur_++] = node;
    --ctx->num_;
    return A_SUCCESS;
}

static void a_que_drop_(a_que *ctx)
{
    while (ctx->head_.next != &ctx->head_)
    {
        a_que_node *const node = (a_que_node *)ctx->head_.next;
        if (a_unlikely(a_que_node_die(ctx, node))) { break; }
        a_list_del_node(&node->node_);
        a_list_dtor(&node->node_);
    }
}

a_que *a_que_new(a_size size)
{
    a_que *const ctx = (a_que *)a_alloc(A_NULL, sizeof(a_que));
    if (ctx) { a_que_ctor(ctx, size); }
    return ctx;
}

void a_que_die(a_que *ctx, void (*dtor)(void *))
{
    if (ctx)
    {
        a_que_dtor(ctx, dtor);
        a_alloc(ctx, 0);
    }
}

void a_que_ctor(a_que *ctx, a_size size)
{
    a_list_ctor(&ctx->head_);
    ctx->siz_ = size ? size : sizeof(a_cast);
    ctx->ptr_ = A_NULL;
    ctx->num_ = 0;
    ctx->cur_ = 0;
    ctx->mem_ = 0;
}

void a_que_dtor(a_que *ctx, void (*dtor)(void *))
{
    a_que_node **node;
    a_que_drop_(ctx);
    node = ctx->ptr_;
    if (dtor)
    {
        for (; ctx->cur_; --ctx->cur_)
        {
            dtor((**node).data_);
            a_alloc((**node).data_, 0);
            a_alloc(*node++, 0);
        }
    }
    else
    {
        for (; ctx->cur_; --ctx->cur_)
        {
            a_alloc((**node).data_, 0);
            a_alloc(*node++, 0);
        }
    }
    a_alloc(ctx->ptr_, 0);
    ctx->ptr_ = A_NULL;
    ctx->siz_ = 0;
    ctx->mem_ = 0;
}

void a_que_move(a_que *ctx, a_que *obj)
{
    a_copy(ctx, obj, sizeof(*obj));
    a_zero(obj, sizeof(*obj));
}

void *a_que_at(a_que const *ctx, a_imax idx)
{
    void *ptr = A_NULL;
    a_imax cur = 0;
    if (idx >= 0)
    {
        a_list_foreach_next(it, &ctx->head_)
        {
            if (cur++ == idx)
            {
                ptr = ((a_que_node *)it)->data_;
                break;
            }
        }
    }
    else
    {
        a_list_foreach_prev(it, &ctx->head_)
        {
            if (--cur == idx)
            {
                ptr = ((a_que_node *)it)->data_;
                break;
            }
        }
    }
    return ptr;
}

void a_que_drop(a_que *ctx, void (*dtor)(void *))
{
    a_que_node **node;
    a_que_drop_(ctx);
    node = ctx->ptr_;
    if (dtor)
    {
        for (a_size cur = ctx->cur_; cur; ++node, --cur)
        {
            dtor((**node).data_);
            a_alloc((**node).data_, 0);
            (**node).data_ = A_NULL;
        }
    }
    else
    {
        for (a_size cur = ctx->cur_; cur; ++node, --cur)
        {
            a_alloc((**node).data_, 0);
            (**node).data_ = A_NULL;
        }
    }
}

void a_que_edit(a_que *ctx, a_size size, void (*dtor)(void *))
{
    size = size ? size : sizeof(a_cast);
    a_que_drop(ctx, dtor);
    ctx->siz_ = size;
}

int a_que_swap_(a_que const *ctx, void *lhs, void *rhs)
{
    int ok = A_FAILURE;
    a_que_node *l = A_NULL;
    a_que_node *r = A_NULL;
    if (lhs == rhs) { return A_SUCCESS; }
    a_list_foreach_next(it, &ctx->head_)
    {
        a_que_node *const node = (a_que_node *)it;
        if (node->data_ == lhs || node->data_ == rhs)
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
            a_list_swap_node(&l->node_, &r->node_);
            ok = A_SUCCESS;
            break;
        }
    }
    return ok;
}

void a_que_swap(a_que const *ctx, a_size lhs, a_size rhs)
{
    a_size cur = 0;
    a_size const num = ctx->num_ - 1;
    lhs = lhs < ctx->num_ ? lhs : num;
    rhs = rhs < ctx->num_ ? rhs : num;
    if (lhs != rhs)
    {
        a_que_node *l = A_NULL;
        a_que_node *r = A_NULL;
        a_list_foreach_next(it, &ctx->head_)
        {
            if (cur == lhs || cur == rhs)
            {
                // because lhs less than num
                // it's never a null pointer
                if (!l)
                {
                    l = (a_que_node *)it;
                }
                else
                {
                    r = (a_que_node *)it;
                }
                if (!it) { break; }
            }
            if (r)
            {
                a_list_swap_node(&l->node_, &r->node_);
                break;
            }
            ++cur;
        }
    }
}

void a_que_sort_fore(a_que const *ctx, int (*cmp)(void const *, void const *))
{
    if (ctx->num_ > 1)
    {
        a_list *pt = A_NULL;
        a_list *const it = ctx->head_.next;
        for (a_list *at = it->next; at != &ctx->head_; at = at->next)
        {
            void *const lhs = ((a_que_node *)it)->data_;
            void *const rhs = ((a_que_node *)at)->data_;
            if (cmp(lhs, rhs) > 0) { pt = at; }
            else { break; }
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

void a_que_sort_back(a_que const *ctx, int (*cmp)(void const *, void const *))
{
    if (ctx->num_ > 1)
    {
        a_list *pt = A_NULL;
        a_list *const it = ctx->head_.prev;
        for (a_list *at = it->prev; at != &ctx->head_; at = at->prev)
        {
            void *const lhs = ((a_que_node *)at)->data_;
            void *const rhs = ((a_que_node *)it)->data_;
            if (cmp(lhs, rhs) > 0) { pt = at; }
            else { break; }
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

void *a_que_push_fore(a_que *ctx)
{
    a_que_node *const node = a_que_node_new(ctx);
    if (a_unlikely(!node)) { return node; }
    a_list_add_next(&ctx->head_, &node->node_);
    return node->data_;
}

void *a_que_push_back(a_que *ctx)
{
    a_que_node *const node = a_que_node_new(ctx);
    if (a_unlikely(!node)) { return node; }
    a_list_add_prev(&ctx->head_, &node->node_);
    return node->data_;
}

void *a_que_pull_fore(a_que *ctx)
{
    void *data = A_NULL;
    if (ctx->head_.next != &ctx->head_)
    {
        a_que_node *const node = (a_que_node *)ctx->head_.next;
        if (a_unlikely(a_que_node_die(ctx, node))) { goto fail; }
        a_list_del_node(&node->node_);
        a_list_dtor(&node->node_);
        data = node->data_;
    }
fail:
    return data;
}

void *a_que_pull_back(a_que *ctx)
{
    void *data = A_NULL;
    if (ctx->head_.prev != &ctx->head_)
    {
        a_que_node *const node = (a_que_node *)ctx->head_.prev;
        if (a_unlikely(a_que_node_die(ctx, node))) { goto fail; }
        a_list_del_node(&node->node_);
        a_list_dtor(&node->node_);
        data = node->data_;
    }
fail:
    return data;
}

void *a_que_insert(a_que *ctx, a_size idx)
{
    if (idx < ctx->num_)
    {
        a_size cur = 0;
        a_que_node *const node = a_que_node_new(ctx);
        if (a_unlikely(!node)) { return node; }
        a_list_foreach_next(it, &ctx->head_)
        {
            if (cur++ == idx)
            {
                a_list_add_prev(it, &node->node_);
                break;
            }
        }
        return node->data_;
    }
    return a_que_push_back(ctx);
}

void *a_que_remove(a_que *ctx, a_size idx)
{
    if (idx < ctx->num_)
    {
        a_size cur = 0;
        a_que_node *node = A_NULL;
        a_list_foreach_next(it, &ctx->head_)
        {
            if (cur++ == idx)
            {
                // because idx less than num
                // it's never a null pointer
                node = (a_que_node *)it;
                break;
            }
        }
        if (a_unlikely(a_que_node_die(ctx, node))) { return A_NULL; }
        a_list_del_node(&node->node_);
        a_list_dtor(&node->node_);
        return node->data_;
    }
    return a_que_pull_back(ctx);
}
