#include <ustl/core/internal/container/base/con_treenode.hpp>

using namespace ustl;
using namespace core;
using namespace internal;
using namespace container;
using namespace base; 


typedef TreeNodeBasic      Node;
typedef TreeNodeBasic *    NodePtr;


template <>
auto
Node::_S_maxnode<Node>(ConstPtr root) USTL_NOEXCEPT -> ConstPtr
{
    while(root->_M_right) {
        root = root->_M_right;
    }

    return root;
}


template <>
auto
Node::_S_minnode<Node>(ConstPtr root) USTL_NOEXCEPT -> ConstPtr
{
    while(root->_M_left) {
        root = root->_M_left;
    }

    return root;
}


template <>
auto
Node::_S_increment<Node>(ConstPtr node) USTL_NOEXCEPT -> ConstPtr
{
    NodePtr tmp;
    if(node->_M_right) {
        tmp = node->_M_right;
        while(tmp->_M_left) {
            tmp = tmp->_M_left;
        }
    }
    else {
        tmp = node->_M_parent;
        if(node == tmp->_M_parent) {
            return tmp;
        }

        while(node == tmp->_M_right) {
            node = tmp;
            tmp  = tmp->_M_parent;
        }
    }
    return tmp;
}


template <>
auto
Node::_S_decrement<Node>(ConstPtr node) USTL_NOEXCEPT -> ConstPtr
{
    NodePtr tmp; 
    if(node->_M_left) {
        tmp = node->_M_left;
        while(tmp->_M_right) {
            tmp = tmp->_M_right;
        }
    }
    else {
        tmp = node->_M_parent;
        if(node == tmp->_M_parent) {
            return tmp;
        }

        while(node == tmp->_M_left) {
            node = tmp;
            tmp  = tmp->_M_parent;
        }
    }
    return tmp;
}


void
Node::_M_rotate_left() USTL_NOEXCEPT
{
    Self *parent = _M_parent;
    Self *freshly = _M_right;

    this->_M_parent = freshly;
    freshly->_M_parent = parent;

    if (parent == parent->_M_parent->_M_parent) {
        parent->_M_parent = freshly;
    }
    else if (this == parent->_M_left) {
        parent->_M_left = freshly;
    }
    else {
        parent->_M_right = freshly;
    }

    freshly->_M_left = this;
    this->_M_right = freshly->_M_left;

    if (this->_M_right) {
        this->_M_right->_M_parent = this;
    }
}


void
Node::_M_rotate_right() USTL_NOEXCEPT
{
    Self *parent =  _M_parent;
    Self *freshly =  _M_left;

    this->_M_parent = freshly;
    freshly->_M_parent = parent;

    if (parent == parent->_M_parent->_M_parent) {
        parent->_M_parent = freshly;
    }
    else if(this == parent->_M_left) {
        parent->_M_left = freshly;
    }
    else {
        parent->_M_right = freshly;
    }
    
    freshly->_M_right = this;
    this->_M_left = freshly->_M_right;

    if(this->_M_left) {
        this->_M_left->_M_parent = this;
    }
}


usize
Node::_M_height() const USTL_NOEXCEPT
{
    return 0;
}


// usize
// internal::__tree_node_height(NodePtr const __root) USTL_NOEXCEPT
// {
//     if(0 == __root)
//         return 0;

//     bool recall = false;
//     bool from_lchild = false;
//     usize height =   1;
//     usize tmp_height=   1;
//     NodePtr first = __root;
//     NodePtr last  = __root->_M_max_node();

//     do
//     {
//         if(recall)
//         {
//            from_lchild = __tree_is_lchild(__first);
//            first = __first->parent();

//             if(__from_lchild && __first->right())
//             {
//                 __first = __first->right();
//                 __recall = false;
//             }
//             else
//                 --__tmp_height;
//         }
//         else
//         {
//             if(__first->_M_left))
//             {
//                 __first = __first->_M_left);
//                 ++__tmp_height;
//             }
//             else if(__first->right())
//             {
//                 __first = __first->right(); 
//                 ++__tmp_height;
//             }
//             else
//             {
//                 __recall = true;
//                 __height = __height > __tmp_height ? __height : __tmp_height;
//             }
//         }
//     } while(__first != __last);

//     return __height  > __tmp_height ? __height : __tmp_height;
// }