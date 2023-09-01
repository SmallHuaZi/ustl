/**
 * Go China! ! !
 * 
 * @author SmallHuaZi 
 * @date   2023.4.10
*/
#include <ustl/core/internal/container/base/con_rbtnode.hpp>

using namespace ustl;
using namespace core;
using namespace internal;
using namespace container;
using namespace base;

using RBTreeNodeColor::Red;
using RBTreeNodeColor::Black;

typedef TreeHeader          Header;
typedef RBTreeNodeBasic     Node;
typedef RBTreeNodeBasic *   Ptr;


USTL_ALWAYS_INLINE
static void
swap_node_color(Ptr x, Ptr y) USTL_NOEXCEPT
{
    RBTreeNodeColor tmp = x->_M_color;
    x->_M_color = y->_M_color;
    y->_M_color = tmp;
}


USTL_ALWAYS_INLINE
static void
rbt_rebalance_after_insertion(Ptr node, Ptr const root) USTL_NOEXCEPT
{
    if (node == root) {
        node->_M_color = Black;
        return;
    }
    node->_M_color = Red;

    while (Red == node->parent()->_M_color && root != node) {
        Ptr parent = node->parent();
        Ptr uncle = parent->_M_sibling<Node>();
        Ptr grandpa = parent->parent();

        if (Red == uncle->_M_color) {
            uncle->_M_color = Black;
            parent->_M_color = Black;
            grandpa->_M_color = Red;
            node = grandpa;
        }
        else {
            if (parent->_M_parent->_M_left == parent) {
                if (node->_M_parent->_M_left == node) {
                    node = node->parent();
                    parent->_M_rotate_left();
                    // __tree_rotate_left(parent, header);
                    parent = node->parent();
                    grandpa = parent->parent();
                }
                swap_node_color(grandpa, parent);
                grandpa->_M_rotate_right();
                // __tree_rotate_right(grandpa, header);
            }
            else  {
                if (node->_M_parent->_M_left == node) {
                    node = node->parent();
                    parent->_M_rotate_right();
                    // __tree_rotate_right(parent, header);
                    parent = node->parent();
                    grandpa = parent->parent();
                }
                swap_node_color(grandpa, parent);
                grandpa->_M_rotate_left();
                // __tree_rotate_left(grandpa, header);
            }
        }
    }

    root->_M_color = Black;
}


USTL_ALWAYS_INLINE
static void
rbt_rebalance_after_erasing(Ptr node, Ptr const root) USTL_NOEXCEPT
{
    while (root != node || Red == node->_M_color)
    {
        Ptr __parent  = node->parent();
        Ptr __sibling = node->_M_sibling<Node>();
        Ptr const __sib_right = __sibling->right();
        Ptr const __sib_left = __sibling->left();

        if (node == node->_M_parent->_M_left) {
            /// Sibling node is red
            if (Red == __sibling->_M_color) {
                __parent->_M_color = Red;
                __sibling->_M_color = Black;
                __parent->_M_rotate_left();
                // __tree_rotate_left(__parent, header);
                __sibling = __parent->right();
            }

            /// All child nodes are black
            if (Black == __sib_left->_M_color && Black == __sib_right->_M_color) {
                node = __parent;
                __sibling->_M_color = Red;
            }
            else {
                /// The left child is black
                if (Red == __sib_left->_M_color) {
                    __sibling->_M_color = Red;
                    __sib_left->_M_color = Black;
                    __sibling->_M_rotate_right();
                    // __tree_rotate_right(__sibling, header);
                    __sibling = __parent->right();
                }
                __sibling->_M_color = __parent->_M_color;
                __parent->_M_color = Black;
                __sib_right->_M_color == Black;
                __parent->_M_rotate_left();
                // __tree_rotate_left(__parent, header);
                break;
            }
        }
        else {
            /// Sibling node is red
            if (Red == __sibling->_M_color) {
                __parent->_M_color = Red;
                __sibling->_M_color = Black;
                __parent->_M_rotate_right();
                // __tree_rotate_right(__parent, header);
                __sibling = __parent->left();
            }

            /// All child nodes are black
            if (Black == __sib_left->_M_color && Black == __sib_right->_M_color) {
                node = __parent;
                __sibling->_M_color = Red;
            }
            else {
                /// The left child is black
                if (Red == __sib_right->_M_color) {
                    __sibling->_M_color = Red;
                    __sib_right->_M_color = Black;
                    __sibling->_M_rotate_right();
                    // __tree_rotate_right(__sibling, header);
                    __sibling = __parent->left();
                }
                __sibling->_M_color = __parent->_M_color;
                __parent->_M_color = Black;
                __sib_left->_M_color = Black;
                __parent->_M_rotate_right();
                // __tree_rotate_right(__parent, header);
                break;
            }
        }

    }

    root->_M_color = Black;
}


Ptr 
base::ustl_rbt_erase_and_rebalance(Ptr node, Header * const header) USTL_NOEXCEPT 
{
    if (node->_M_left) {
        node = Node::_S_decrement<Node>(node);
    }
    if (node->right()) {
        node = node->right();
    }

    if (node == header->_M_left) {
        header->_M_left = Node::_S_increment<Node>(node);
    }
    else if (node == header->_M_right) {
        header->_M_right = Node::_S_decrement<Node>(node);
    }

    ::rbt_rebalance_after_erasing(node, static_cast<Ptr>(header->_M_parent));

    if(Red == node->_M_color)  {
        node->_M_parent->_M_right = 0;
    }
    else if(node == node->_M_parent->_M_left) {
        node->_M_parent->_M_left = 0;
    }
    else {
        header->_M_reset();
    }

    return node;
}


void
base::ustl_rbt_rebalance_after_insertion(Ptr node, Header * const header) USTL_NOEXCEPT
{
    if (node == header->_M_parent) {
        header->_M_left = node;
        header->_M_right = node;
    }
    else if (node->_M_parent == header->_M_left && node == node->_M_parent->_M_left) {
        header->_M_left = node;
    }
    else if (node->_M_parent == header->_M_right && node == node->_M_parent->_M_right) {
        header->_M_right = node;
    }

    ::rbt_rebalance_after_insertion(node, static_cast<Ptr>(header->_M_parent));
}