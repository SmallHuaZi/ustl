#ifndef __tree_basic_h
#define __tree_basic_h

#include "include/config.h"

#define __TREE_BASIC_DEFINED

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

        _Node_basic_pointer
        _M_Max_node() ustl_cpp_noexcept;

        _Node_basic_pointer
        _M_Min_node() ustl_cpp_noexcept;


        _Node_basic_pointer     _M_parent;
        _Node_basic_pointer     _M_left;
        _Node_basic_pointer     _M_right;
    };



    inline tree_node_basic * 
    tree_node_basic::
        _M_Max_node() ustl_cpp_noexcept
    {
        tree_node_basic *__tmp = this;
        while(__tmp->_M_right)
            __tmp = __tmp->_M_right;
        return  __tmp;
    }


    inline tree_node_basic * 
    tree_node_basic::
        _M_Min_node() ustl_cpp_noexcept
    {
        tree_node_basic *__tmp = this;
        while(__tmp->_M_left)
            __tmp = __tmp->_M_left;
        return  __tmp;
    }



    static inline bool
    _tree_is_lchild(tree_node_basic *__node) ustl_cpp_noexcept
    { return    __node == __node->_M_parent->_M_left; }



    static inline bool
    _tree_is_rchild(tree_node_basic *__node) ustl_cpp_noexcept
    { return    __node == __node->_M_parent->_M_right; }



    static inline tree_node_basic *
    _tree_node_bro(tree_node_basic *__node) ustl_cpp_noexcept
    {
        return  __node == __node->_M_parent->_M_left 
                        ? __node->_M_parent->_M_right 
                        : __node->_M_parent->_M_left;
    }



    // common methods are not defined as class methods
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
    _tree_insert(bool __left, 
                 tree_node_basic *__new, 
                 tree_node_basic *__pos, 
                 tree_node_basic *__header) ustl_cpp_noexcept;
    
    void
    _tree_erase(tree_node_basic *__del, 
                tree_node_basic *__header) ustl_cpp_noexcept;

    size_t
    _tree_node_height(tree_node_basic *__root) ustl_cpp_noexcept;

} // namespace ustl


#endif