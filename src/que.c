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
        a_list **ptr;
        a_size mem = ctx->mem_;
        mem += (ctx->mem_ >> 1) + 1;
        mem = a_size_up(sizeof(void *), mem);
        ptr = (a_list **)a_alloc((void *)ctx->ptr_, sizeof(void *) * mem);
        if (A_UNLIKELY(!ptr)) { return A_OMEMORY; }
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
    a_list_ctor(&ctx->head_);
    if (!size) { size = 1; }
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
        a_list **ptr, *node, *next;
        for (ptr = ctx->ptr_; ctx->cur_; --ctx->cur_)
        {
            dtor(*ptr + 1);
            a_alloc(*ptr++, 0);
        }
        A_LIST_FORSAFE_NEXT(node, next, &ctx->head_)
        {
            dtor(node + 1);
            a_alloc(node, 0);
        }
    }
    else
    {
        a_list **ptr, *node, *next;
        for (ptr = ctx->ptr_; ctx->cur_; --ctx->cur_)
        {
            a_alloc(*ptr++, 0);
        }
        A_LIST_FORSAFE_NEXT(node, next, &ctx->head_)
        {
            a_alloc(node, 0);
        }
    }
    a_alloc((void *)ctx->ptr_, 0);
    ctx->ptr_ = A_NULL;
    ctx->siz_ = 0;
    ctx->mem_ = 0;
}

void a_que_swap(a_que *lhs, a_que *rhs)
{
    a_que swap;
    swap = *lhs;
    *lhs = *rhs;
    *rhs = swap;
}

int a_que_drop(a_que *ctx, void (*dtor)(void *))
{
    a_list *const head = &ctx->head_, *node;
    for (node = head->next; node != head; node = head->next)
    {
        int rc = a_que_die_(ctx, node);
        if (rc == 0)
        {
            a_list_del_node(node);
            a_list_dtor(node);
        }
        else { return rc; }
    }
    if (dtor)
    {
        a_size cur = ctx->cur_;
        a_list **ptr = ctx->ptr_;
        for (; cur; ++ptr, --cur)
        {
            dtor(*ptr + 1);
        }
    }
    return A_SUCCESS;
}

int a_que_setz(a_que *ctx, a_size siz, void (*dtor)(void *))
{
    int rc = a_que_drop(ctx, dtor);
    if (rc == 0)
    {
        if (!siz) { siz = 1; }
        if (siz > ctx->siz_)
        {
            a_size cur = ctx->cur_;
            a_list **ptr = ctx->ptr_;
            for (; cur; ++ptr, --cur)
            {
                void *const p = a_alloc(*ptr, sizeof(a_list) + siz);
                if (A_UNLIKELY(!p)) { return A_OMEMORY; }
                *ptr = (a_list *)p;
            }
        }
        ctx->siz_ = siz;
    }
    return rc;
}

void *a_que_at(a_que const *ctx, a_diff idx)
{
    a_diff cur = 0;
    if (idx >= 0)
    {
        a_list *it;
        A_LIST_FOREACH_NEXT(it, &ctx->head_)
        {
            if (cur++ == idx) { return it + 1; }
        }
    }
    else
    {
        a_list *it;
        A_LIST_FOREACH_PREV(it, &ctx->head_)
        {
            if (--cur == idx) { return it + 1; }
        }
    }
    return A_NULL;
}

void a_que_sort_fore(a_que const *ctx, int (*cmp)(void const *, void const *))
{
    if (ctx->num_ > 1)
    {
        a_list *const it = ctx->head_.next;
        a_list *at = it->next;
        do {
            if (cmp(it + 1, at + 1) <= 0) { break; }
            at = at->next;
        } while (at != &ctx->head_);
        if (at != it->next)
        {
            at = at->prev; /* a-it-b-at-a => a-b-at-it-a */
            a_list_link(it->prev, it->next); /* a-b */
            a_list_link(it, at->next); /* it-a */
            a_list_link(at, it); /* at-it */
        }
    }
}

void a_que_sort_back(a_que const *ctx, int (*cmp)(void const *, void const *))
{
    if (ctx->num_ > 1)
    {
        a_list *const it = ctx->head_.prev;
        a_list *at = it->prev;
        do {
            if (cmp(at + 1, it + 1) <= 0) { break; }
            at = at->prev;
        } while (at != &ctx->head_);
        if (at != it->prev)
        {
            at = at->next; /* a-at-b-it-a => a-it-at-b-a */
            a_list_link(it->prev, it->next); /* b-a */
            a_list_link(at->prev, it); /* a-it */
            a_list_link(it, at); /* it-at */
        }
    }
}

void *a_que_push_sort(a_que *ctx, void const *key, int (*cmp)(void const *, void const *))
{
    a_list *it = ctx->head_.prev;
    a_list *const node = a_que_new_(ctx);
    if (A_UNLIKELY(!node)) { return node; }
    if (ctx->num_ > 1)
    {
        do {
            if (cmp(it + 1, key) <= 0) { break; }
            it = it->prev;
        } while (it != &ctx->head_);
    }
    a_list_link(node, it->next);
    a_list_link(it, node);
    return node + 1;
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
        if (a_que_die_(ctx, node) == 0)
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
        if (a_que_die_(ctx, node) == 0)
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
            a_list *it;
            A_LIST_FOREACH_NEXT(it, &ctx->head_)
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
        a_list *it, *node = A_NULL;
        A_LIST_FOREACH_NEXT(it, &ctx->head_)
        {
            if (cur++ == idx)
            {
                node = it;
                break;
            }
        }
        if (a_que_die_(ctx, node) == 0)
        {
            a_list_del_node(node);
            a_list_dtor(node);
            return node + 1;
        }
        return A_NULL;
    }
    return a_que_pull_back(ctx);
}
