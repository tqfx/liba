#include "a/rbt.h"

/*
red-black trees properties: https://en.wikipedia.org/wiki/Rbtree

 1) A node is either red or black
 2) The root is black
 3) All leaves (null) are black
 4) Both children of every red node are black
 5) Every simple path from root to leaves contains the same number of black nodes.

 4 and 5 give the O(log n) guarantee, since 4 implies you cannot have two
 consecutive red nodes in a path and every red node is therefore followed by
 a black. So if B is the number of black nodes on every simple path (as per
 5), then the longest possible path due to 4 is 2B.

 We shall indicate color with case, where black nodes are uppercase and red
 nodes will be lowercase. Unknown color nodes shall be drawn as red within
 parentheses and have some accompanying text comment.
*/

/* Replaces the child of the specified red–black tree node. */
static A_INLINE void a_rbt_new_child(a_rbt *root, a_rbt_node *parent, a_rbt_node *node, a_rbt_node *newnode)
{
    if (parent)
    {
        if (parent->left == node)
        {
            parent->left = newnode;
        }
        else
        {
            parent->right = newnode;
        }
    }
    else
    {
        root->node = newnode;
    }
}

/* Sets the parent and color of the specified red–black tree node. */
static A_INLINE void a_rbt_set_parent_color(a_rbt_node *node, a_rbt_node *parent, unsigned int color)
{
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
    node->parent_ = (a_uptr)parent + color;
#else /* !A_SIZE_POINTER */
    node->parent = parent;
    node->color = color;
#endif /* A_SIZE_POINTER */
}

/* Sets the parent of the specified red–black tree node. */
static A_INLINE void a_rbt_set_parent(a_rbt_node *node, a_rbt_node *parent)
{
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
    node->parent_ = (a_uptr)parent + (node->parent_ & 1);
#else /* !A_SIZE_POINTER */
    node->parent = parent;
#endif /* A_SIZE_POINTER */
}

/* Returns the color of the specified red–black tree node. */
static A_INLINE unsigned int a_rbt_color(a_rbt_node const *node)
{
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
    return (unsigned int)(node->parent_ & 1);
#else /* !A_SIZE_POINTER */
    return node->color;
#endif /* A_SIZE_POINTER */
}

/* Sets the black color of the specified red–black tree node. */
static A_INLINE void a_rbt_set_black(a_rbt_node *node)
{
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
    node->parent_ |= 1;
#else /* !A_SIZE_POINTER */
    node->color = 1;
#endif /* A_SIZE_POINTER */
}

/*
Helper function for rotations:
 - node's parent and color get assigned to new
 - node gets assigned new as a parent and 'color' as a color.
*/
static A_INLINE void a_rbt_set_parents(a_rbt *root, a_rbt_node *node, a_rbt_node *newnode, unsigned int color)
{
    a_rbt_node *const parent = a_rbt_parent(node);
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
    newnode->parent_ = node->parent_;
#else /* !A_SIZE_POINTER */
    newnode->parent = node->parent;
    newnode->color = node->color;
#endif /* A_SIZE_POINTER */
    a_rbt_set_parent_color(node, newnode, color);
    a_rbt_new_child(root, parent, node, newnode);
}

#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
#define A_RBT_PARENT(node) a_cast_r(a_rbt_node *, (node)->parent_)
#else /* !A_SIZE_POINTER */
#define A_RBT_PARENT(node) (node)->parent
#endif /* A_SIZE_POINTER */

void a_rbt_insert_adjust(a_rbt *root, a_rbt_node *node)
{
    for (a_rbt_node *parent = A_RBT_PARENT(node), *gparent, *tmp;;)
    {
        /* Loop invariant: node is red. */
        if (A_UNLIKELY(!parent))
        {
            /*
            The inserted node is root. Either this is the first node,
            or we recursed at Case 1 below and are no longer violating 4).
            */
            a_rbt_set_parent_color(node, A_NULL, 1);
            break;
        }
        /*
        If there is a black parent, we are done. Otherwise, take some corrective action as, per 4),
        we don't want a red root or two consecutive red nodes.
        */
        if (a_rbt_color(parent)) { break; }
        gparent = A_RBT_PARENT(parent);
        tmp = gparent->right;
        if (parent != tmp) /* parent == gparent->left */
        {
            if (tmp && a_rbt_color(tmp) == 0)
            {
                /*
                Case 1 - node's uncle is red (color flips).

                        G            g
                       / \          / \
                      p   u  -->   P   U
                     /            /
                    n            n

                However, since g's parent might be red, and 4) does not allow this, we need to recurse at g.
                */
                a_rbt_set_parent_color(tmp, gparent, 1);
                a_rbt_set_parent_color(parent, gparent, 1);
                node = gparent;
                parent = a_rbt_parent(node);
                a_rbt_set_parent_color(node, parent, 0);
                continue;
            }
            tmp = parent->right;
            if (node == tmp)
            {
                /*
                Case 2 - node's uncle is black and node is the parent's right child (left rotate at parent).

                      G             G
                     / \           / \
                    p   U  -->    n   U
                     \           /
                      n         p

                This still leaves us in violation of 4), the continuation into Case 3 will fix that.
                */
                tmp = node->left;
                parent->right = tmp;
                node->left = parent;
                if (tmp) { a_rbt_set_parent_color(tmp, parent, 1); }
                a_rbt_set_parent_color(parent, node, 0);
                parent = node;
                tmp = node->right;
            }
            /*
            Case 3 - node's uncle is black and node is
            the parent's left child (right rotate at gparent).

                    G           P
                   / \         / \
                  p   U  -->  n   g
                 /                 \
                n                   U
            */
            gparent->left = tmp; /* == parent->right */
            parent->right = gparent;
            if (tmp) { a_rbt_set_parent_color(tmp, gparent, 1); }
            a_rbt_set_parents(root, gparent, parent, 0);
            break;
        }
        else
        {
            tmp = gparent->left;
            if (tmp && a_rbt_color(tmp) == 0)
            {
                /* Case 1 - color flips */
                a_rbt_set_parent_color(tmp, gparent, 1);
                a_rbt_set_parent_color(parent, gparent, 1);
                node = gparent;
                parent = a_rbt_parent(node);
                a_rbt_set_parent_color(node, parent, 0);
                continue;
            }
            tmp = parent->left;
            if (node == tmp)
            {
                /* Case 2 - right rotate at parent */
                tmp = node->right;
                parent->left = tmp;
                node->right = parent;
                if (tmp) { a_rbt_set_parent_color(tmp, parent, 1); }
                a_rbt_set_parent_color(parent, node, 0);
                parent = node;
                tmp = node->left;
            }
            /* Case 3 - left rotate at gparent */
            gparent->right = tmp; /* == parent->left */
            parent->left = gparent;
            if (tmp) { a_rbt_set_parent_color(tmp, gparent, 1); }
            a_rbt_set_parents(root, gparent, parent, 0);
            break;
        }
    }
}

static A_INLINE void a_rbt_remove_adjust(a_rbt *root, a_rbt_node *parent)
{
    for (a_rbt_node *node = A_NULL, *sibling, *tmp1, *tmp2;;)
    {
        /*
        Loop invariants:
         - node is black (or null on first iteration)
         - node is not the root (parent is not null)
         - All leaf paths going through parent and node have a
           black node count that is 1 lower than other leaf paths.
        */
        if (node != parent->right) /* node == parent->left */
        {
            sibling = parent->right;
            if (a_rbt_color(sibling) == 0)
            {
                /*
                Case 1 - left rotate at parent

                      P               S
                     / \             / \
                    N   s    -->    p   Sr
                       / \         / \
                      Sl  Sr      N   Sl
                */
                tmp1 = sibling->left;
                parent->right = tmp1;
                sibling->left = parent;
                a_rbt_set_parent_color(tmp1, parent, 1);
                a_rbt_set_parents(root, parent, sibling, 0);
                sibling = tmp1;
                A_ASSUME(tmp1);
            }
            tmp1 = sibling->right;
            if (!tmp1 || a_rbt_color(tmp1))
            {
                tmp2 = sibling->left;
                if (!tmp2 || a_rbt_color(tmp2))
                {
                    /*
                    Case 2 - sibling color flip (p could be either color here)

                         (p)           (p)
                         / \           / \
                        N   S    -->  N   s
                           / \           / \
                          Sl  Sr        Sl  Sr

                    This leaves us violating 5) which can be fixed by flipping p to black if it was red,
                    or by recursing at p. p is red when coming from Case 1.
                    */
                    a_rbt_set_parent_color(sibling, parent, 0);
                    if (a_rbt_color(parent) == 0)
                    {
                        a_rbt_set_black(parent);
                    }
                    else
                    {
                        node = parent;
                        parent = a_rbt_parent(node);
                        if (parent) { continue; }
                    }
                    break;
                }
                /*
                Case 3 - right rotate at sibling (p could be either color here)

                     (p)           (p)
                     / \           / \
                    N   S    -->  N   sl
                       / \             \
                      sl  Sr            S
                                         \
                                          Sr

                Note: p might be red, and then both p and sl are red after rotation(which breaks property 4).
                This is fixed in Case 4 (in a_rbt_set_parents() which set sl the color of p and set black)

                     (p)            (sl)
                     / \            /  \
                    N   sl   -->   P    S
                         \        /      \
                          S      N        Sr
                           \
                            Sr
                */
                tmp1 = tmp2->right;
                sibling->left = tmp1;
                tmp2->right = sibling;
                parent->right = tmp2;
                if (tmp1) { a_rbt_set_parent_color(tmp1, sibling, 1); }
                tmp1 = sibling;
                sibling = tmp2;
            }
            /*
            Case 4 - left rotate at parent + color flips (p and sl could be either color here.
            After rotation, p becomes black, s acquires p's color, and sl keeps its color)

                 (p)             (s)
                 / \             / \
                N   S     -->   P   Sr
                   / \         / \
                 (sl) sr      N  (sl)
            */
            tmp2 = sibling->left;
            parent->right = tmp2;
            sibling->left = parent;
            a_rbt_set_parent_color(tmp1, sibling, 1);
            if (tmp2) { a_rbt_set_parent(tmp2, parent); }
            a_rbt_set_parents(root, parent, sibling, 1);
            break;
        }
        else
        {
            A_ASSUME(parent->left);
            sibling = parent->left;
            if (a_rbt_color(sibling) == 0)
            {
                /* Case 1 - right rotate at parent */
                tmp1 = sibling->right;
                parent->left = tmp1;
                sibling->right = parent;
                a_rbt_set_parent_color(tmp1, parent, 1);
                a_rbt_set_parents(root, parent, sibling, 0);
                sibling = tmp1;
                A_ASSUME(tmp1);
            }
            tmp1 = sibling->left;
            if (!tmp1 || a_rbt_color(tmp1))
            {
                tmp2 = sibling->right;
                if (!tmp2 || a_rbt_color(tmp2))
                {
                    /* Case 2 - sibling color flip */
                    a_rbt_set_parent_color(sibling, parent, 0);
                    if (a_rbt_color(parent) == 0)
                    {
                        a_rbt_set_black(parent);
                    }
                    else
                    {
                        node = parent;
                        parent = a_rbt_parent(node);
                        if (parent) { continue; }
                    }
                    break;
                }
                /* Case 3 - left rotate at sibling */
                tmp1 = tmp2->left;
                sibling->right = tmp1;
                tmp2->left = sibling;
                parent->left = tmp2;
                if (tmp1) { a_rbt_set_parent_color(tmp1, sibling, 1); }
                tmp1 = sibling;
                sibling = tmp2;
            }
            /* Case 4 - right rotate at parent + color flips */
            tmp2 = sibling->right;
            parent->left = tmp2;
            sibling->right = parent;
            a_rbt_set_parent_color(tmp1, sibling, 1);
            if (tmp2) { a_rbt_set_parent(tmp2, parent); }
            a_rbt_set_parents(root, parent, sibling, 1);
            break;
        }
    }
}

void a_rbt_remove(a_rbt *root, a_rbt_node *node)
{
    a_rbt_node *child = node->right;
    a_rbt_node *tmp = node->left;
    a_rbt_node *parent, *adjust;
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
    a_uptr parent_;
#else /* !A_SIZE_POINTER */
    unsigned int color;
#endif /* A_SIZE_POINTER */

    if (!tmp)
    {
        /*
        Case 1: node to erase has no more than 1 child (easy!)
        Note that if there is one child it must be red due to 5) and node must be black due to 4).
        We adjust colors locally so as to bypass a_rbt_remove_adjust() later on.
        */
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
        parent_ = node->parent_;
#else /* !A_SIZE_POINTER */
        color = node->color;
#endif /* A_SIZE_POINTER */
        parent = a_rbt_parent(node);
        a_rbt_new_child(root, parent, node, child);
        if (child)
        {
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
            child->parent_ = parent_;
#else /* !A_SIZE_POINTER */
            child->parent = parent;
            child->color = color;
#endif /* A_SIZE_POINTER */
            adjust = A_NULL;
        }
        else
        {
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
            adjust = (parent_ & 1) ? parent : A_NULL;
#else /* !A_SIZE_POINTER */
            adjust = color ? parent : A_NULL;
#endif /* A_SIZE_POINTER */
        }
    }
    else if (!child)
    {
        /* Still case 1, but this time the child is node->left */
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
        tmp->parent_ = node->parent_;
#else /* !A_SIZE_POINTER */
        tmp->parent = node->parent;
        tmp->color = node->color;
#endif /* A_SIZE_POINTER */
        parent = a_rbt_parent(node);
        a_rbt_new_child(root, parent, node, tmp);
        adjust = A_NULL;
    }
    else
    {
        a_rbt_node *successor = child, *child2;

        tmp = child->left;
        if (!tmp)
        {
            /*
            Case 2: node's successor is its right child

                  (n)          (s)
                  / \          / \
                (x) (s)  ->  (x) (c)
                      \
                     (c)
            */
            parent = successor;
            child2 = successor->right;
        }
        else
        {
            /*
            Case 3: node's successor is leftmost under node's right child subtree

                  (n)          (s)
                  / \          / \
                (x) (y)  ->  (x) (y)
                    /            /
                  (p)          (p)
                  /            /
                (s)          (c)
                  \
                  (c)
            */
            do {
                parent = successor;
                successor = tmp;
                tmp = tmp->left;
            } while (tmp);
            child2 = successor->right;
            parent->left = child2;
            successor->right = child;
            a_rbt_set_parent(child, successor);
        }

        tmp = node->left;
        successor->left = tmp;
        a_rbt_set_parent(tmp, successor);

#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
        parent_ = node->parent_;
#else /* !A_SIZE_POINTER */
        color = node->color;
#endif /* A_SIZE_POINTER */
        tmp = a_rbt_parent(node);
        a_rbt_new_child(root, tmp, node, successor);

        if (child2)
        {
            a_rbt_set_parent_color(child2, parent, 1);
            adjust = A_NULL;
        }
        else
        {
            adjust = a_rbt_color(successor) ? parent : A_NULL;
        }
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
        successor->parent_ = parent_;
#else /* !A_SIZE_POINTER */
        successor->parent = tmp;
        successor->color = color;
#endif /* A_SIZE_POINTER */
    }

    if (adjust) { a_rbt_remove_adjust(root, adjust); }
}

a_rbt_node *a_rbt_insert(a_rbt *root, a_rbt_node *node, int (*cmp)(void const *, void const *))
{
    a_rbt_node *parent = root->node;
    a_rbt_node **link = &root->node;
    while (*link)
    {
        parent = *link;
        int const res = cmp(node, parent);
        if (res < 0)
        {
            link = &parent->left;
        }
        else if (res > 0)
        {
            link = &parent->right;
        }
        else { return parent; }
    }
    *link = a_rbt_init(node, parent);
    a_rbt_insert_adjust(root, node);
    return A_NULL;
}

a_rbt_node *a_rbt_search(a_rbt const *root, void const *ctx, int (*cmp)(void const *, void const *))
{
    for (a_rbt_node *cur = root->node; cur;)
    {
        int const res = cmp(ctx, cur);
        if (res < 0)
        {
            cur = cur->left;
        }
        else if (res > 0)
        {
            cur = cur->right;
        }
        else { return cur; }
    }
    return A_NULL;
}

a_rbt_node *a_rbt_head(a_rbt const *root)
{
    a_rbt_node *node = root->node;
    if (node)
    {
        while (node->left) { node = node->left; }
    }
    return node;
}

a_rbt_node *a_rbt_tail(a_rbt const *root)
{
    a_rbt_node *node = root->node;
    if (node)
    {
        while (node->right) { node = node->right; }
    }
    return node;
}

a_rbt_node *a_rbt_next(a_rbt_node *node)
{
    /*
         D
       /   \
      B     F
     / \   / \
    A   C E   G
    */
    if (node->right) /* D -> F -> E */
    {
        node = node->right;
        while (node->left) { node = node->left; }
    }
    else /* C -> B -> D */
    {
        a_rbt_node *leaf;
        do {
            leaf = node;
            node = a_rbt_parent(node);
        } while (node && node->left != leaf);
    }
    return node;
}

a_rbt_node *a_rbt_prev(a_rbt_node *node)
{
    if (node->left)
    {
        node = node->left;
        while (node->right) { node = node->right; }
    }
    else
    {
        a_rbt_node *leaf;
        do {
            leaf = node;
            node = a_rbt_parent(node);
        } while (node && node->right != leaf);
    }
    return node;
}

a_rbt_node *a_rbt_pre_next(a_rbt_node *node)
{
    /*
         D
       /   \
      B     F
     / \   / \
    A   C E   G
    */
    a_rbt_node *leaf;
    if (node->left) { return node->left; }
    if (node->right) { return node->right; }
    for (leaf = node, node = a_rbt_parent(node); node;
         leaf = node, node = a_rbt_parent(node))
    {
        if (node->right && node->right != leaf)
        {
            node = node->right;
            break; /* A -> B -> C */
        } /* C -> B -> D -> F */
    }
    return node;
}

a_rbt_node *a_rbt_pre_prev(a_rbt_node *node)
{
    a_rbt_node *leaf;
    if (node->right) { return node->right; }
    if (node->left) { return node->left; }
    for (leaf = node, node = a_rbt_parent(node); node;
         leaf = node, node = a_rbt_parent(node))
    {
        if (node->left && node->left != leaf)
        {
            node = node->left;
            break;
        }
    }
    return node;
}

#define A_RBT_POST(head, tail) \
    for (;;)                   \
    {                          \
        if (node->head)        \
        {                      \
            node = node->head; \
        }                      \
        else if (node->tail)   \
        {                      \
            node = node->tail; \
        }                      \
        else { break; }        \
    }                          \
    (void)0

a_rbt_node *a_rbt_post_head(a_rbt const *root)
{
    a_rbt_node *node = root->node;
    if (node) { A_RBT_POST(left, right); }
    return node;
}

a_rbt_node *a_rbt_post_tail(a_rbt const *root)
{
    a_rbt_node *node = root->node;
    if (node) { A_RBT_POST(right, left); }
    return node;
}

a_rbt_node *a_rbt_post_next(a_rbt_node *node)
{
    /*
         D
       /   \
      B     F
     / \   / \
    A   C E   G
    */
    a_rbt_node *leaf = node;
    node = a_rbt_parent(node);
    if (node && node->right && node->right != leaf)
    {
        node = node->right; /* B -> D -> F -> E */
        A_RBT_POST(left, right); /* A -> B -> C */
    } /* C -> B */
    return node;
}

a_rbt_node *a_rbt_post_prev(a_rbt_node *node)
{
    a_rbt_node *leaf = node;
    node = a_rbt_parent(node);
    if (node && node->left && node->left != leaf)
    {
        node = node->left;
        A_RBT_POST(right, left);
    }
    return node;
}

a_rbt_node *a_rbt_tear(a_rbt *root, a_rbt_node **next)
{
    a_rbt_node *node = *next;
    if (!node)
    {
        node = root->node;
        if (!node) { return node; }
    }
    A_RBT_POST(left, right);
    *next = a_rbt_parent(node);
    a_rbt_new_child(root, *next, node, A_NULL);
    return node;
}
