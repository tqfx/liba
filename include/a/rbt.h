/*!
 @file rbt.h
 @brief red–black self-balancing binary search tree
*/

#ifndef LIBA_RBT_H
#define LIBA_RBT_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_RBT red–black binary search tree
 @{
*/

// clang-format off
#define A_RBT_ROOT {A_NULL}
// clang-format on

#define A_RBT_R 0 //!< red
#define A_RBT_B 1 //!< black

/*!
 @brief instance structure for red–black binary search tree node
*/
typedef struct a_rbt_node
{
    struct a_rbt_node *left; /*!< pointer to left child or null */
    struct a_rbt_node *right; /*!< pointer to right child or null */
    /*! pointer to parent combined with the color. The mapping is: 0 => red, 1 => black.
     The rest of the bits are the pointer to the parent node. It must be 2-byte aligned,
     and it will be null if this is the root node and therefore has no parent.
    */
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
    a_uptr _parent;
#else /* !A_SIZE_POINTER */
    struct a_rbt_node *parent;
    unsigned int color;
#endif /* A_SIZE_POINTER */
} a_rbt_node;

/*!
 @brief access parent of red–black binary search tree node
 @param[in] node points to red–black binary search tree node
 @return a pointer to the parent of the specified red–black tree node,
 or null if it is already the root of the tree.
*/
A_INTERN a_rbt_node *a_rbt_parent(a_rbt_node const *node)
{
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
    return a_cast_r(a_rbt_node *, node->_parent & ~a_uptr_c(1));
#else /* !A_SIZE_POINTER */
    return node->parent;
#endif /* A_SIZE_POINTER */
}

/*!
 @brief initialize for red–black binary search tree node
 @param[in] node node to be initialized
 @param[in] parent node parent
 @return initialized node
*/
A_INTERN a_rbt_node *a_rbt_init(a_rbt_node *node, a_rbt_node *parent)
{
#if defined(A_SIZE_POINTER) && (A_SIZE_POINTER + 0 > 1)
    node->_parent = a_cast_r(a_uptr, parent);
#else /* !A_SIZE_POINTER */
    node->parent = parent;
    node->color = A_RBT_R;
#endif /* A_SIZE_POINTER */
    node->right = A_NULL;
    node->left = A_NULL;
    return node;
}

/*!
 @brief instance structure for red–black binary search tree root
*/
typedef union a_rbt
{
    struct a_rbt_node *node; //!< root node
} a_rbt;

/*!
 @brief initialize for red–black binary search tree root
 @param[in,out] root red–black binary search tree root
*/
A_INTERN void a_rbt_root(a_rbt *root) { root->node = A_NULL; }

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief access head node of red–black binary search tree in-order
 @param[in] root red–black binary search tree root
 @return head node or null
*/
A_EXTERN a_rbt_node *a_rbt_head(a_rbt const *root);

/*!
 @brief access tail node of red–black binary search tree in-order
 @param[in] root red–black binary search tree root
 @return tail node or null
*/
A_EXTERN a_rbt_node *a_rbt_tail(a_rbt const *root);

/*!
 @brief access next node of red–black binary search tree node in-order
 @param[in] node red–black binary search tree node
 @return next node or null
*/
A_EXTERN a_rbt_node *a_rbt_next(a_rbt_node *node);

/*!
 @brief access prev node of red–black binary search tree node in-order
 @param[in] node red–black binary search tree node
 @return prev node or null
*/
A_EXTERN a_rbt_node *a_rbt_prev(a_rbt_node *node);

/*!
 @brief access next node of red–black binary search tree node preorder
 @param[in] node red–black binary search tree node
 @return next node or null
*/
A_EXTERN a_rbt_node *a_rbt_pre_next(a_rbt_node *node);

/*!
 @brief access prev node of red–black binary search tree node preorder
 @param[in] node red–black binary search tree node
 @return prev node or null
*/
A_EXTERN a_rbt_node *a_rbt_pre_prev(a_rbt_node *node);

/*!
 @brief access head node of red–black binary search tree postorder
 @param[in] root red–black binary search tree root
 @return head node or null
*/
A_EXTERN a_rbt_node *a_rbt_post_head(a_rbt const *root);

/*!
 @brief access tail node of red–black binary search tree postorder
 @param[in] root red–black binary search tree root
 @return tail node or null
*/
A_EXTERN a_rbt_node *a_rbt_post_tail(a_rbt const *root);

/*!
 @brief access next node of red–black binary search tree node postorder
 @param[in] node red–black binary search tree node
 @return next node or null
*/
A_EXTERN a_rbt_node *a_rbt_post_next(a_rbt_node *node);

/*!
 @brief access prev node of red–black binary search tree node postorder
 @param[in] node red–black binary search tree node
 @return prev node or null
*/
A_EXTERN a_rbt_node *a_rbt_post_prev(a_rbt_node *node);

/*!
 @brief tear a node from red–black binary search tree
 @param[in] root red–black binary search tree root
 @param[in,out] next input starting node or,
 if null, root node. output next node or null.
 @return teared node or null
*/
A_EXTERN a_rbt_node *a_rbt_tear(a_rbt *root, a_rbt_node **next);

/*!
 @brief search specified content from red–black binary search tree
 @param[in] root red–black binary search tree root
 @param[in] ctx specified content
 @param[in] cmp a function that compares two nodes
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
 @return specified node or null
*/
A_EXTERN a_rbt_node *a_rbt_search(a_rbt const *root, void const *ctx, int (*cmp)(void const *, void const *));

/*!
 @brief insert specified node into red–black binary search tree
 @param[in] root red–black binary search tree root
 @param[in] node specified tree node
 @param[in] cmp a function that compares two nodes
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
 @return null or duplicate node
*/
A_EXTERN a_rbt_node *a_rbt_insert(a_rbt *root, a_rbt_node *node, int (*cmp)(void const *, void const *));

/*!
 @brief rebalance the tree after insertion of the specified node
 @param[in] root red–black binary search tree root
 @param[in] node insert tree node
*/
A_EXTERN void a_rbt_insert_adjust(a_rbt *root, a_rbt_node *node);

/*!
 @brief remove specified node from red–black binary search tree
 @param[in] root red–black binary search tree root
 @param[in] node specified tree node
*/
A_EXTERN void a_rbt_remove(a_rbt *root, a_rbt_node *node);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief access the struct for this entry
 @param ptr the &a_rbt_node pointer
 @param type the type of the struct this is embedded in
 @param member the name of the a_rbt_node within the struct
*/
#define a_rbt_entry(ptr, type, member) a_container_of(ptr, type, member)

/*!
 @brief iterate over a red–black binary search tree in-order
 @code{.c}
 typedef struct
 {
     a_rbt_node node;
 } T;
 a_rbt root = A_RBT_ROOT;
 a_rbt_foreach(cur, &root)
 {
     T *it = a_rbt_entry(cur, T, node);
 }
 @endcode
 @param cur the &a_rbt_node to use as a loop counter
 @param root red–black binary search tree root
*/
#define a_rbt_foreach(cur, root) \
    for (a_rbt_node *cur = a_rbt_head(root); cur; cur = a_rbt_next(cur))

/*!
 @brief iterate over a red–black binary search tree in-order reverse
 @code{.c}
 typedef struct
 {
     a_rbt_node node;
 } T;
 a_rbt root = A_RBT_ROOT;
 a_rbt_foreach_reverse(cur, &root)
 {
     T *it = a_rbt_entry(cur, T, node);
 }
 @endcode
 @param cur the &a_rbt_node to use as a loop counter
 @param root red–black binary search tree root
*/
#define a_rbt_foreach_reverse(cur, root) \
    for (a_rbt_node *cur = a_rbt_tail(root); cur; cur = a_rbt_prev(cur))

/*!
 @brief iterate over a red–black binary search tree preorder
 @code{.c}
 typedef struct
 {
     a_rbt_node node;
 } T;
 a_rbt root = A_RBT_ROOT;
 a_rbt_pre_foreach(cur, &root)
 {
     T *it = a_rbt_entry(cur, T, node);
 }
 @endcode
 @param cur the &a_rbt_node to use as a loop counter
 @param root red–black binary search tree root
*/
#define a_rbt_pre_foreach(cur, root) \
    for (a_rbt_node *cur = (root)->node; cur; cur = a_rbt_pre_next(cur))

/*!
 @brief iterate over a red–black binary search tree preorder reverse
 @code{.c}
 typedef struct
 {
     a_rbt_node node;
 } T;
 a_rbt root = A_RBT_ROOT;
 a_rbt_pre_foreach_reverse(cur, &root)
 {
     T *it = a_rbt_entry(cur, T, node);
 }
 @endcode
 @param cur the &a_rbt_node to use as a loop counter
 @param root red–black binary search tree root
*/
#define a_rbt_pre_foreach_reverse(cur, root) \
    for (a_rbt_node *cur = (root)->node; cur; cur = a_rbt_pre_prev(cur))

/*!
 @brief iterate over a red–black binary search tree postorder
 @code{.c}
 typedef struct
 {
     a_rbt_node node;
 } T;
 a_rbt root = A_RBT_ROOT;
 a_rbt_post_foreach(cur, &root)
 {
     T *it = a_rbt_entry(cur, T, node);
 }
 @endcode
 @param cur the &a_rbt_node to use as a loop counter
 @param root red–black binary search tree root
*/
#define a_rbt_post_foreach(cur, root) \
    for (a_rbt_node *cur = a_rbt_post_head(root); cur; cur = a_rbt_post_next(cur))

/*!
 @brief iterate over a red–black binary search tree postorder reverse
 @code{.c}
 typedef struct
 {
     a_rbt_node node;
 } T;
 a_rbt root = A_RBT_ROOT;
 a_rbt_post_foreach_reverse(cur, &root)
 {
     T *it = a_rbt_entry(cur, T, node);
 }
 @endcode
 @param cur the &a_rbt_node to use as a loop counter
 @param root red–black binary search tree root
*/
#define a_rbt_post_foreach_reverse(cur, root) \
    for (a_rbt_node *cur = a_rbt_post_tail(root); cur; cur = a_rbt_post_prev(cur))

/*!
 @brief tear a red–black binary search tree using postorder traversal
 @code{.c}
 typedef struct
 {
     a_rbt_node node;
 } T;
 a_rbt root = A_AVL_ROOT;
 a_rbt_fortear(cur, next, &root)
 {
     T *it = a_rbt_entry(cur, T, node);
 }
 @endcode
 @param cur the &a_rbt_node to use as a loop counter
 @param next the &a_rbt_node to use as next node
 @param root red–black binary search tree root
*/
#define a_rbt_fortear(cur, next, root) \
    for (a_rbt_node *next = A_NULL, *cur = a_rbt_tear(root, &next); cur; cur = a_rbt_tear(root, &next))

/*! @} A_RBT */

#endif /* a/rbt.h */
