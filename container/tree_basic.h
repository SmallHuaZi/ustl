#ifndef __tree_basic_h
#define __tree_basic_h

#include "include/config.h"

#define __TREE_BASIC_DEFINED

#define _is_rchild(__ptr) \
    (__ptr == __ptr->_M_parent->_M_right)

#define _is_lchild(__ptr) \
    (__ptr == __ptr->_M_parent->_M_left)

namespace ustl
{

    struct tree_node_basic
    {
        typedef     tree_node_basic     _Node_basic;
        typedef     tree_node_basic *   _Node_basic_pointer;


        tree_node_basic();

        tree_node_basic(_Node_basic_pointer __p);

        tree_node_basic(_Node_basic_pointer __l, _Node_basic_pointer __r, _Node_basic_pointer __p);

        void
        _M_reset();

        _Node_basic_pointer     _M_parent;
        _Node_basic_pointer     _M_left;
        _Node_basic_pointer     _M_right;
    };

    tree_node_basic *
    _tree_decrement(tree_node_basic *__node) ustl_cpp_noexcept;

    tree_node_basic *
    _tree_increment(tree_node_basic *__node) ustl_cpp_noexcept;

    void
    _tree_rotate_left(tree_node_basic *__node, 
                      tree_node_basic *__header) ustl_cpp_noexcept;

    void
    _tree_rotate_right(tree_node_basic *__node, 
                       tree_node_basic *__header) ustl_cpp_noexcept;

    void
    _tree_insert(bool __right, 
                 tree_node_basic *__new, 
                 tree_node_basic *__pos, 
                 tree_node_basic *__header) ustl_cpp_noexcept;
    
    void
    _tree_erase(tree_node_basic *__del, 
                tree_node_basic *__header) ustl_cpp_noexcept;

} // namespace ustl


#endif