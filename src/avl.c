#include "a/avl.h"

/* Sets the parent and balance factor of the specified AVL tree node. */
static A_INLINE void a_avl_set_parent_factor(a_avl_s *const node, a_avl_s *const parent, int const factor)
{
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 3)
    node->_parent = (a_uptr_t)parent | (a_uptr_t)(factor + 1);
#else /* !A_SIZE_POINTER */
    node->parent = parent;
    node->factor = factor;
#endif /* A_SIZE_POINTER */
}

/* Sets the parent of the specified AVL tree node. */
static A_INLINE void a_avl_set_parent(a_avl_s *const node, a_avl_s *const parent)
{
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 3)
    node->_parent = (a_uptr_t)parent | (node->_parent & 3);
#else /* !A_SIZE_POINTER */
    node->parent = parent;
#endif /* A_SIZE_POINTER */
}

/*
Returns the balance factor of the specified AVL tree node --- that is,
the height of its right subtree minus the height of its left subtree.
*/
static A_INLINE int a_avl_factor(a_avl_s const *const node)
{
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 3)
    return (int)(node->_parent & 3) - 1;
#else /* !A_SIZE_POINTER */
    return node->factor;
#endif /* A_SIZE_POINTER */
}

/*
Adds %amount to the balance factor of the specified AVL tree node.
The caller must ensure this still results in a valid balance factor (-1, 0, or 1).
*/
static A_INLINE void a_avl_set_factor(a_avl_s *const node, int const amount)
{
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 3)
    node->_parent += (a_uptr_t)amount;
#else /* !A_SIZE_POINTER */
    node->factor += amount;
#endif /* A_SIZE_POINTER */
}

static A_INLINE a_avl_s *a_avl_child(a_avl_s const *const node, int const sign)
{
    if (sign < 0)
    {
        return node->left;
    }
    return node->right;
}

static A_INLINE void a_avl_set_child(a_avl_s *const node, a_avl_s *const child, int const sign)
{
    if (sign < 0)
    {
        node->left = child;
    }
    else
    {
        node->right = child;
    }
}

static A_INLINE void a_avl_mod_child(a_avl_u *const root, a_avl_s *const parent, a_avl_s *const oldnode, a_avl_s *const newnode)
{
    if (parent)
    {
        if (parent->left == oldnode)
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

/*
Template for performing a single rotation (nodes marked with ? may not exist)

sign > 0: Rotate clockwise (right) rooted at A:

        P?            P?
        |             |
        A             B
       / \           / \
      B   C?  =>    D?  A
     / \               / \
    D?  E?            E?  C?

sign < 0: Rotate counterclockwise (left) rooted at A:

        P?            P?
        |             |
        A             B
       / \           / \
      C?  B   =>    A   D?
         / \       / \
        E?  D?    C?  E?

This updates pointers but not balance factors!
*/
static void a_avl_rotate(a_avl_u *const root, a_avl_s *const A, int const sign)
{
    a_avl_s *const P = a_avl_parent(A);
    a_avl_s *const B = a_avl_child(A, -sign);
    a_avl_s *const E = a_avl_child(B, +sign);

    a_avl_set_child(A, E, -sign);
    a_avl_set_parent(A, B);

    a_avl_set_child(B, A, +sign);
    a_avl_set_parent(B, P);

    if (E)
    {
        a_avl_set_parent(E, A);
    }

    a_avl_mod_child(root, P, A, B);
}

/*
Template for performing a double rotation (nodes marked with ? may not exist)

sign > 0: Rotate counterclockwise (left) rooted at B, then clockwise (right) rooted at A:

        P?            P?          P?
        |             |           |
        A             A           E
       / \           / \        /   \
      B   C?  =>    E   C? =>  B     A
     / \           / \        / \   / \
    D?  E         B   G?     D?  F?G?  C?
       / \       / \
      F?  G?    D?  F?

sign < 0: Rotate clockwise (right) rooted at B, then counterclockwise (left) rooted at A:

         P?          P?              P?
         |           |               |
         A           A               E
        / \         / \            /   \
       C?  B   =>  C?  E    =>    A     B
          / \         / \        / \   / \
         E   D?      G?  B      C?  G?F?  D?
        / \             / \
       G?  F?          F?  D?

Returns a pointer to E and updates balance factors. Except for those two things, this function is equivalent to:

    a_avl_rotate(root, B, -sign);
    a_avl_rotate(root, A, +sign);
*/
static a_avl_s *a_avl_rotate2(a_avl_u *const root, a_avl_s *const B, a_avl_s *const A, int const sign)
{
    a_avl_s *const P = a_avl_parent(A);
    a_avl_s *const E = a_avl_child(B, +sign);
    a_avl_s *const F = a_avl_child(E, -sign);
    a_avl_s *const G = a_avl_child(E, +sign);
    int const e = a_avl_factor(E);

    a_avl_set_child(A, G, -sign);
    a_avl_set_parent_factor(A, E, (sign * e >= 0) ? 0 : -e);

    a_avl_set_child(B, F, +sign);
    a_avl_set_parent_factor(B, E, (sign * e <= 0) ? 0 : -e);

    a_avl_set_child(E, A, +sign);
    a_avl_set_child(E, B, -sign);
    a_avl_set_parent_factor(E, P, 0);

    if (F)
    {
        a_avl_set_parent(F, B);
    }
    if (G)
    {
        a_avl_set_parent(G, A);
    }

    a_avl_mod_child(root, P, A, E);

    return E;
}

/*
This function handles the growth of a subtree due to an insertion.

root
    Location of the tree's root pointer.

node
    A subtree that has increased in height by 1 due to an insertion.

parent
    Parent of node; must not be NULL.

sign
    -1 if node is the left child of parent;
    +1 if node is the right child of parent.

This function will adjust parent's balance factor, then do a (single or double) rotation if necessary.
The return value will be %true if the full AVL tree is now adequately balanced,
or %false if the subtree rooted at parent is now adequately balanced but has increased in height by 1,
so the caller should continue up the tree.

Note that if %false is returned, no rotation will have been done.
Indeed, a single node insertion cannot require that more than one (single or double) rotation be done.
*/
static a_bool_t a_avl_handle_growth(a_avl_u *const root, a_avl_s *const parent, a_avl_s *const node, int const sign)
{
    int const old_factor = a_avl_factor(parent);
    if (old_factor == 0)
    {
        /* %parent is still sufficiently balanced (-1 or +1 balance factor), but must have increased in height. Continue up the tree. */
        a_avl_set_factor(parent, sign);
        return A_FALSE;
    }

    int const new_factor = old_factor + sign;
    if (new_factor == 0)
    {
        /* %parent is now perfectly balanced (0 balance factor). It cannot have increased in height, so there is nothing more to do. */
        a_avl_set_factor(parent, sign);
        return A_TRUE;
    }

    /* %parent is too left-heavy (new_balance_factor == -2) or too right-heavy (new_balance_factor == +2). */

    /*
    Test whether %node is left-heavy (-1 balance factor) or right-heavy (+1 balance factor).
    Note that it cannot be perfectly balanced (0 balance factor) because here we are under the invariant that
    %node has increased in height due to the insertion.
    */
    if (sign * a_avl_factor(node) > 0)
    {
        /*
        %node (B below) is heavy in the same direction %parent (A below) is heavy.
        The comment, diagram, and equations below assume sign < 0. The other case is symmetric!
        Do a clockwise rotation rooted at %parent (A below):

                  A              B
                 / \           /   \
                B   C?  =>    D     A
               / \           / \   / \
              D   E?        F?  G?E?  C?
             / \
            F?  G?

        Before the rotation:
            balance(A) = -2
            balance(B) = -1
        Let x = height(C). Then:
            height(B) = x + 2
            height(D) = x + 1
            height(E) = x
            max(height(F), height(G)) = x.

        After the rotation:
            height(D) = max(height(F), height(G)) + 1
                    = x + 1
            height(A) = max(height(E), height(C)) + 1
                    = max(x, x) + 1 = x + 1
            balance(B) = 0
            balance(A) = 0
        */
        a_avl_rotate(root, parent, -sign);

        /* Equivalent to setting %parent's balance factor to 0. */
        a_avl_set_factor(parent, -sign); // A

        /* Equivalent to setting %node's balance factor to 0. */
        a_avl_set_factor(node, -sign); // B
    }
    else
    {
        /*
        %node (B below) is heavy in the direction opposite from the direction %parent (A below) is heavy.
        The comment, diagram, and equations below assume sign < 0. The other case is symmetric!
        Do a counterblockwise rotation rooted at %node (B below), then a clockwise rotation rooted at %parent (A below):

                A             A           E
               / \           / \        /   \
              B   C?  =>    E   C? =>  B     A
             / \           / \        / \   / \
            D?  E         B   G?     D?  F?G?  C?
               / \       / \
              F?  G?    D?  F?

         Before the rotation:
            balance(A) = -2
            balance(B) = +1
         Let x = height(C). Then:
            height(B) = x + 2
            height(E) = x + 1
            height(D) = x
            max(height(F), height(G)) = x

         After both rotations:
            height(A) = max(height(G), height(C)) + 1
                      = x + 1
            balance(A) = balance(E{orig}) >= 0 ? 0 : -balance(E{orig})
            height(B) = max(height(D), height(F)) + 1
                      = x + 1
            balance(B) = balance(E{orig} <= 0) ? 0 : -balance(E{orig})

            height(E) = x + 2
            balance(E) = 0
        */
        a_avl_rotate2(root, node, parent, -sign);
    }

    /* Height after rotation is unchanged; nothing more to do. */
    return A_TRUE;
}

void a_avl_insert_adjust(a_avl_u *const root, a_avl_s *node)
{
    /* Adjust balance factor of new node's parent. No rotation will need to be done at this level. */

    a_avl_s *parent = a_avl_parent(node);
    if (!parent)
    {
        return;
    }

    if (parent->left == node)
    {
        a_avl_set_factor(parent, -1);
    }
    else
    {
        a_avl_set_factor(parent, +1);
    }

    if (a_avl_factor(parent) == 0)
    {
        /* %parent did not change in height. Nothing more to do. */
        return;
    }

    /* The subtree rooted at parent increased in height by 1. */

    a_bool_t done;
    do
    {
        node = parent;
        parent = a_avl_parent(node);
        if (!parent)
        {
            return;
        }
        if (parent->left == node)
        {
            done = a_avl_handle_growth(root, parent, node, -1);
        }
        else
        {
            done = a_avl_handle_growth(root, parent, node, +1);
        }
    } while (!done);
}

/*
This function handles the shrinkage of a subtree due to a deletion.

root
    Location of the tree's root pointer.

parent
    A node in the tree, exactly one of whose subtrees has decreased in height by 1 due to a deletion.
    (This includes the case where one of the child pointers has become NULL,
    since we can consider the "NULL" subtree to have a height of 0.)

sign
    +1 if the left subtree of parent has decreased in height by 1;
    -1 if the right subtree of parent has decreased in height by 1.

left
    If the return value is not NULL, this will be set to
    %true if the left subtree of the returned node has decreased in height by 1,
    %false if the right subtree of the returned node has decreased in height by 1.

This function will adjust parent's balance factor, then do a (single or double) rotation if necessary.
The return value will be NULL if the full AVL tree is now adequately balanced,
or a pointer to the parent of parent if parent is now adequately balanced but has decreased in height by 1.
Also in the latter case, *left will be set.
*/
static a_avl_s *a_avl_handle_shrink(a_avl_u *const root, a_avl_s *parent, int const sign, a_bool_t *const left)
{
    int const old_factor = a_avl_factor(parent);
    if (old_factor == 0)
    {
        /*
        Prior to the deletion, the subtree rooted at %parent was perfectly balanced.
        It's now unbalanced by 1, but that's okay and its height hasn't changed. Nothing more to do.
        */
        a_avl_set_factor(parent, sign);
        return A_NULL;
    }

    a_avl_s *node;
    int const new_factor = old_factor + sign;
    if (new_factor == 0)
    {
        /*
        The subtree rooted at %parent is now perfectly balanced, whereas before the deletion it was unbalanced by 1.
        Its height must have decreased by 1. No rotation is needed at this location, but continue up the tree.
        */
        a_avl_set_factor(parent, sign);
        node = parent;
    }
    else
    {
        /* %parent is too left-heavy (new_factor == -2) or too right-heavy (new_factor == +2). */
        node = a_avl_child(parent, sign);

        /*
        The rotations below are similar to those done during insertion, so full comments are not provided.
        The only new case is the one where %node has a balance factor of 0, and that is commented.
        */
        if (sign * a_avl_factor(node) >= 0)
        {
            a_avl_rotate(root, parent, -sign);
            if (a_avl_factor(node) == 0)
            {
                /*
                %node (B below) is perfectly balanced.
                The comment, diagram, and equations below assume sign < 0. The other case is symmetric!
                Do a clockwise rotation rooted at %parent (A below):

                          A              B
                         / \           /   \
                        B   C?  =>    D     A
                       / \           / \   / \
                      D   E         F?  G?E   C?
                     / \
                    F?  G?

                Before the rotation:
                    balance(A) = -2
                    balance(B) =  0
                Let x = height(C). Then:
                    height(B) = x + 2
                    height(D) = x + 1
                    height(E) = x + 1
                    max(height(F), height(G)) = x.

                After the rotation:
                    height(D) = max(height(F), height(G)) + 1
                              = x + 1
                    height(A) = max(height(E), height(C)) + 1
                              = max(x + 1, x) + 1 = x + 2
                    balance(A) = -1
                    balance(B) = +1

                A: -2 => -1 (sign < 0) or +2 => +1 (sign > 0)
                No change needed --- that's the same as old_factor.

                B: 0 => +1 (sign < 0) or 0 => -1 (sign > 0)
                */
                a_avl_set_factor(node, -sign);

                /* Height is unchanged; nothing more to do. */
                return A_NULL;
            }
            else
            {
                a_avl_set_factor(parent, -sign);
                a_avl_set_factor(node, -sign);
            }
        }
        else
        {
            node = a_avl_rotate2(root, node, parent, -sign);
        }
    }
    parent = a_avl_parent(node);
    if (parent)
    {
        *left = (parent->left == node);
    }
    return parent;
}

/*
Swaps node X, which must have 2 children, with its in-order successor, then unlinks node X.
Returns the parent of X just before unlinking, without its balance factor having been updated to account for the unlink.
*/
static A_INLINE a_avl_s *a_avl_handle_remove(a_avl_u *const root, a_avl_s *const X, a_bool_t *const left)
{
    a_avl_s *node;

    a_avl_s *Y = X->right;
    if (!Y->left)
    {
        /*
          P?           P?           P?
          |            |            |
          X            Y            Y
         / \          / \          / \
        A   Y    =>  A   X    =>  A   B?
           / \          / \
         (0)  B?      (0)  B?

        [ X unlinked, Y returned ]
        */
        *left = A_FALSE;
        node = Y;
    }
    else
    {
        a_avl_s *Q;
        do
        {
            Q = Y;
            Y = Y->left;
        } while (Y->left);
        /*
           P?           P?           P?
           |            |            |
           X            Y            Y
          / \          / \          / \
         A   ... =>  A  ... =>  A  ...
             |            |            |
             Q            Q            Q
            /            /            /
           Y            X            B?
          / \          / \
        (0)  B?      (0)  B?

        [ X unlinked, Q returned ]
        */
        Q->left = Y->right;
        if (Y->right)
        {
            a_avl_set_parent(Y->right, Q);
        }
        Y->right = X->right;
        a_avl_set_parent(X->right, Y);
        *left = A_TRUE;
        node = Q;
    }

    Y->left = X->left;
    a_avl_set_parent(X->left, Y);

#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 3)
    Y->_parent = X->_parent;
#else /* !A_SIZE_POINTER */
    Y->parent = X->parent;
    Y->factor = X->factor;
#endif /* A_SIZE_POINTER */
    a_avl_mod_child(root, a_avl_parent(X), X, Y);

    return node;
}

void a_avl_remove(a_avl_u *const root, a_avl_s *const node)
{
    a_avl_s *parent;
    a_bool_t left = A_FALSE;
    if (node->left && node->right)
    {
        /*
        %node is fully internal, with two children. Swap it with its in-order successor
        (which must exist in the right subtree of %node and can have, at most, a right child),
        then unlink %node.
        */
        parent = a_avl_handle_remove(root, node, &left);
        /*
        %parent is now the parent of what was %node's in-order successor.
        It cannot be NULL, since %node itself was an ancestor of its in-order successor.
        %left has been set to %true if %node's in-order successor was the left child of %parent, otherwise %false.
        */
    }
    else
    {
        a_avl_s *const child = node->left ? node->left : node->right;
        /*
        %node is missing at least one child. Unlink it. Set %parent to %node's parent,
        and set %left to reflect which child of %parent %node was.
        Or, if %node was the root node, simply update the root node and return.
        */
        parent = a_avl_parent(node);
        if (parent)
        {
            if (parent->left == node)
            {
                parent->left = child;
                left = A_TRUE;
            }
            else
            {
                parent->right = child;
                left = A_FALSE;
            }
            if (child)
            {
                a_avl_set_parent(child, parent);
            }
        }
        else
        {
            if (child)
            {
                a_avl_set_parent(child, parent);
            }
            root->node = child;
            return;
        }
    }
    /* Rebalance the tree. */
    do
    {
        if (left)
        {
            parent = a_avl_handle_shrink(root, parent, +1, &left);
        }
        else
        {
            parent = a_avl_handle_shrink(root, parent, -1, &left);
        }
    } while (parent);
}

a_avl_s *a_avl_insert(a_avl_u *const root, a_avl_s *const node, int (*const cmp)(void const *, void const *))
{
    a_avl_s *parent = root->node;
    a_avl_s **link = &root->node;
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
        else
        {
            return parent;
        }
    }
    *link = a_avl_init(node, parent);
    a_avl_insert_adjust(root, node);
    return A_NULL;
}

a_avl_s *a_avl_search(a_avl_u const *const root, void const *const ctx, int (*const cmp)(void const *, void const *))
{
    for (a_avl_s *cur = root->node; cur;)
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
        else
        {
            return cur;
        }
    }
    return A_NULL;
}

a_avl_s *a_avl_head(a_avl_u const *const root)
{
    a_avl_s *node = root->node;
    if (node)
    {
        while (node->left)
        {
            node = node->left;
        }
    }
    return node;
}

a_avl_s *a_avl_tail(a_avl_u const *const root)
{
    a_avl_s *node = root->node;
    if (node)
    {
        while (node->right)
        {
            node = node->right;
        }
    }
    return node;
}

a_avl_s *a_avl_next(a_avl_s *node)
{
    /*
         D
       /   \
      B     F
     / \   / \
    A   C E   G
    */
    if (!node)
    {
        return node;
    }
    if (node->right) /* D -> F -> E */
    {
        for (node = node->right; node->left; node = node->left)
        {
        }
    }
    else /* C -> B -> D */
    {
        a_avl_s *last = node;
        for (node = a_avl_parent(node); node && node->left != last;)
        {
            last = node;
            node = a_avl_parent(node);
        }
    }
    return node;
}

a_avl_s *a_avl_prev(a_avl_s *node)
{
    if (!node)
    {
        return node;
    }
    if (node->left)
    {
        for (node = node->left; node->right; node = node->right)
        {
        }
    }
    else
    {
        a_avl_s *last = node;
        for (node = a_avl_parent(node); node && node->right != last;)
        {
            last = node;
            node = a_avl_parent(node);
        }
    }
    return node;
}

a_avl_s *a_avl_pre_next(a_avl_s *node)
{
    /*
         D
       /   \
      B     F
     / \   / \
    A   C E   G
    */
    if (!node)
    {
        return node;
    }
    if (node->left)
    {
        return node->left;
    }
    if (node->right)
    {
        return node->right;
    }
    a_avl_s *last = node;
    for (node = a_avl_parent(node); node; node = a_avl_parent(node))
    {
        if (node->right && node->right != last)
        {
            node = node->right; /* A -> B -> C */
            break;
        }
        last = node; /* C -> B -> D -> F */
    }
    return node;
}

a_avl_s *a_avl_pre_prev(a_avl_s *node)
{
    if (!node)
    {
        return node;
    }
    if (node->right)
    {
        return node->right;
    }
    if (node->left)
    {
        return node->left;
    }
    a_avl_s *last = node;
    for (node = a_avl_parent(node); node; node = a_avl_parent(node))
    {
        if (node->left && node->left != last)
        {
            node = node->left;
            break;
        }
        last = node;
    }
    return node;
}

a_avl_s *a_avl_post_head(a_avl_u const *const root)
{
#define A_AVL_POST_NEXT(node)       \
    do                              \
    {                               \
        if ((node)->left)           \
        {                           \
            (node) = (node)->left;  \
        }                           \
        else if ((node)->right)     \
        {                           \
            (node) = (node)->right; \
        }                           \
        else                        \
        {                           \
            break;                  \
        }                           \
    } while (!0)
    a_avl_s *node = root->node;
    if (node)
    {
        A_AVL_POST_NEXT(node);
    }
    return node;
}

a_avl_s *a_avl_post_tail(a_avl_u const *const root)
{
#define A_AVL_POST_PREV(node)       \
    do                              \
    {                               \
        if ((node)->right)          \
        {                           \
            (node) = (node)->right; \
        }                           \
        else if ((node)->left)      \
        {                           \
            (node) = (node)->left;  \
        }                           \
        else                        \
        {                           \
            break;                  \
        }                           \
    } while (!0)
    a_avl_s *node = root->node;
    if (node)
    {
        A_AVL_POST_PREV(node);
    }
    return node;
}

a_avl_s *a_avl_post_next(a_avl_s *node)
{
    /*
         D
       /   \
      B     F
     / \   / \
    A   C E   G
    */
    if (!node)
    {
        return node;
    }
    a_avl_s *last = node;
    node = a_avl_parent(node);
    if (node && node->right && node->right != last)
    {
        node = node->right; /* B -> D -> F -> E */
        A_AVL_POST_NEXT(node); /* A -> B -> C */
    } /* C -> B */
    return node;
}

a_avl_s *a_avl_post_prev(a_avl_s *node)
{
    if (!node)
    {
        return node;
    }
    a_avl_s *last = node;
    node = a_avl_parent(node);
    if (node && node->left && node->left != last)
    {
        node = node->left;
        A_AVL_POST_PREV(node);
    }
    return node;
}

a_avl_s *a_avl_tear(a_avl_u *const root, a_avl_s **const next)
{
    a_avl_s *node = *next;
    if (!node)
    {
        node = root->node;
        if (!node)
        {
            return node;
        }
    }
    A_AVL_POST_NEXT(node);
    a_avl_s *const parent = a_avl_parent(node);
    if (parent)
    {
        if (parent->left == node)
        {
            parent->left = A_NULL;
        }
        else
        {
            parent->right = A_NULL;
        }
    }
    else
    {
        root->node = A_NULL;
    }
    *next = parent;
    return node;
}
