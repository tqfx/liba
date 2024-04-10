#include "a/que.h"

static a_list *a_que_new_(a_que *ctx)
{
    a_list *node;
    if (ctx->cur_ == 0)
    {
        node = (a_list *)a_alloc(A_NULL, sizeof(a_list) + ctx->siz_);
        if (A_UNLIKELY(!node)) { return node; }
    }
    else
    {
        node = ctx->ptr_[--ctx->cur_];
    }
    ++ctx->num_;
    return node;
}

static int a_que_die_(a_que *ctx, a_list *node)
{
    if (A_UNLIKELY(!node)) { return A_INVALID; }
    if (ctx->mem_ <= ctx->cur_)
    {
        a_size const mem = ctx->mem_ + (ctx->mem_ >> 1) + 1;
        a_list **const ptr = (a_list **)a_alloc((void *)ctx->ptr_, sizeof(void *) * mem);
        if (A_UNLIKELY(!ptr)) { return A_FAILURE; }
        ctx->ptr_ = ptr;
        ctx->mem_ = mem;
    }
    ctx->ptr_[ctx->cur_++] = node;
    --ctx->num_;
    return A_SUCCESS;
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
    if (!size) { size = sizeof(void *); }
    a_list_ctor(&ctx->head_);
    ctx->ptr_ = A_NULL;
    ctx->siz_ = size;
    ctx->num_ = 0;
    ctx->cur_ = 0;
    ctx->mem_ = 0;
}

void a_que_dtor(a_que *ctx, void (*dtor)(void *))
{
    if (dtor)
    {
        for (a_list **node = ctx->ptr_; ctx->cur_; --ctx->cur_)
        {
            dtor(*node + 1);
            a_alloc(*node++, 0);
        }
        a_list_forsafe_next(node, next, &ctx->head_)
        {
            dtor(node + 1);
            a_alloc(node, 0);
        }
    }
    else
    {
        for (a_list **node = ctx->ptr_; ctx->cur_; --ctx->cur_)
        {
            a_alloc(*node++, 0);
        }
        a_list_forsafe_next(node, next, &ctx->head_)
        {
            a_alloc(node, 0);
        }
    }
    a_alloc((void *)ctx->ptr_, 0);
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
    a_imax cur = 0;
    if (idx >= 0)
    {
        a_list_foreach_next(it, &ctx->head_)
        {
            if (cur++ == idx) { return it + 1; }
        }
    }
    else
    {
        a_list_foreach_prev(it, &ctx->head_)
        {
            if (--cur == idx) { return it + 1; }
        }
    }
    return A_NULL;
}

int a_que_drop(a_que *ctx, void (*dtor)(void *))
{
    a_list *const head = &ctx->head_;
    for (a_list *node = head->next; node != head; node = head->next)
    {
        if (a_que_die_(ctx, node) == A_SUCCESS)
        {
            a_list_del_node(node);
            a_list_dtor(node);
        }
        else { return A_FAILURE; }
    }
    if (dtor)
    {
        a_size cur = ctx->cur_;
        a_list **node = ctx->ptr_;
        for (; cur; ++node, --cur)
        {
            dtor(*node + 1);
        }
    }
    return A_SUCCESS;
}

int a_que_edit(a_que *ctx, a_size size, void (*dtor)(void *))
{
    int ok = a_que_drop(ctx, dtor);
    if (ok == A_SUCCESS)
    {
        if (!size) { size = sizeof(void *); }
        if (size > ctx->siz_)
        {
            a_size cur = ctx->cur_;
            a_list **node = ctx->ptr_;
            for (; cur; ++node, --cur)
            {
                void *const ptr = a_alloc(*node, sizeof(a_list) + size);
                if (A_UNLIKELY(!ptr)) { return A_FAILURE; }
                *node = (a_list *)ptr;
            }
        }
        ctx->siz_ = size;
    }
    return ok;
}

int a_que_swap(a_que const *ctx, a_size lhs, a_size rhs)
{
    a_size cur = 0;
    int ok = A_FAILURE;
    a_list *at = A_NULL;
    a_size const num = ctx->num_ - 1;
    lhs = lhs < ctx->num_ ? lhs : num;
    rhs = rhs < ctx->num_ ? rhs : num;
    if (lhs == rhs) { return A_SUCCESS; }
    a_list_foreach_next(it, &ctx->head_)
    {
        if (cur == lhs || cur == rhs)
        {
            if (at)
            {
                a_list_swap_node(it, at);
                ok = A_SUCCESS;
                break;
            }
            else { at = it; }
        }
        ++cur;
    }
    return ok;
}

void a_que_sort_fore(a_que const *ctx, int (*cmp)(void const *, void const *))
{
    if (ctx->num_ > 1)
    {
        a_list *ok = A_NULL;
        a_list *const it = ctx->head_.next;
        for (a_list *at = it->next; at != &ctx->head_; at = at->next)
        {
            if (cmp(it + 1, at + 1) > 0) { ok = at; }
            else { break; }
        }
        if (ok)
        {
            /* a-it-b-at-a => a-b-at-it-a */
            a_list_link(it->prev, it->next); // a-b
            a_list_link(it, ok->next); // it-a
            a_list_link(ok, it); // at-it
        }
    }
}

void a_que_sort_back(a_que const *ctx, int (*cmp)(void const *, void const *))
{
    if (ctx->num_ > 1)
    {
        a_list *ok = A_NULL;
        a_list *const it = ctx->head_.prev;
        for (a_list *at = it->prev; at != &ctx->head_; at = at->prev)
        {
            if (cmp(at + 1, it + 1) > 0) { ok = at; }
            else { break; }
        }
        if (ok)
        {
            /* a-at-b-it-a => a-it-at-b-a */
            a_list_link(it->prev, it->next); // b-a
            a_list_link(ok->prev, it); // a-it
            a_list_link(it, ok); // it-at
        }
    }
}

void *a_que_push_fore(a_que *ctx)
{
    a_list *const node = a_que_new_(ctx);
    if (A_UNLIKELY(!node)) { return node; }
    a_list_add_next(&ctx->head_, node);
    return node + 1;
}

void *a_que_push_back(a_que *ctx)
{
    a_list *const node = a_que_new_(ctx);
    if (A_UNLIKELY(!node)) { return node; }
    a_list_add_prev(&ctx->head_, node);
    return node + 1;
}

void *a_que_pull_fore(a_que *ctx)
{
    if (ctx->head_.next != &ctx->head_)
    {
        a_list *const node = (a_list *)ctx->head_.next;
        if (a_que_die_(ctx, node) == A_SUCCESS)
        {
            a_list_del_node(node);
            a_list_dtor(node);
            return node + 1;
        }
    }
    return A_NULL;
}

void *a_que_pull_back(a_que *ctx)
{
    if (ctx->head_.prev != &ctx->head_)
    {
        a_list *const node = (a_list *)ctx->head_.prev;
        if (a_que_die_(ctx, node) == A_SUCCESS)
        {
            a_list_del_node(node);
            a_list_dtor(node);
            return node + 1;
        }
    }
    return A_NULL;
}

void *a_que_insert(a_que *ctx, a_size idx)
{
    if (idx < ctx->num_)
    {
        a_size cur = 0;
        a_list *const node = a_que_new_(ctx);
        if (node)
        {
            a_list_foreach_next(it, &ctx->head_)
            {
                if (cur++ == idx)
                {
                    a_list_add_prev(it, node);
                    break;
                }
            }
            return node + 1;
        }
        return A_NULL;
    }
    return a_que_push_back(ctx);
}

void *a_que_remove(a_que *ctx, a_size idx)
{
    if (idx < ctx->num_)
    {
        a_size cur = 0;
        a_list *node = A_NULL;
        a_list_foreach_next(it, &ctx->head_)
        {
            if (cur++ == idx)
            {
                node = it;
                break;
            }
        }
        if (a_que_die_(ctx, node) == A_SUCCESS)
        {
            a_list_del_node(node);
            a_list_dtor(node);
            return node + 1;
        }
        return A_NULL;
    }
    return a_que_pull_back(ctx);
}
