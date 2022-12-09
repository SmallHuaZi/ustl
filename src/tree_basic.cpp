#include "container/tree_basic.h"

namespace ustl
{
    tree_node_basic::
        tree_node_basic()
            : _M_left(0), 
              _M_right(0), 
              _M_parent(0) 
    {}    

    tree_node_basic::
        tree_node_basic(_Node_basic_pointer __p)
            : _M_left(0), 
              _M_right(0), 
              _M_parent(__p)
    {}

    tree_node_basic::
        tree_node_basic(_Node_basic_pointer __l,
                        _Node_basic_pointer __r,
                        _Node_basic_pointer __p)
            : _M_left(__l), _M_right(__r), _M_parent(__p)
    {}

    tree_node_basic *
    _tree_decrement(tree_node_basic *__node)
    {
        tree_node_basic *__tmp; 
        if(__node->_M_left)
        {
            __tmp = __node->_M_left;
            while(__tmp->_M_right)
                __tmp = __tmp->_M_right;
        }
        else
        {
            __tmp = __node->_M_parent;
            while(__node == __tmp->_M_left)
            {
                __node = __tmp;
                __tmp  = __tmp->_M_right;
            }
        }
        return  __tmp;
    }

    tree_node_basic *
    _tree_increment(tree_node_basic *__node)
    {
        tree_node_basic *__tmp;
        if(__node->_M_right)
        {
            __tmp = __node->_M_right;
            while(__tmp->_M_left)
                __tmp = __tmp->_M_left;
        }
        else
        {
            __tmp = __node->_M_parent;
            while(__node == __tmp->_M_left)
            {
                __node = __tmp;
                __tmp = __tmp->_M_parent;
            }
        }
        return  __tmp;
    }

    void
    _tree_left_rotate(tree_node_basic *__node)
    {}

    void
    _tree_right_rotate(tree_node_basic *__node)
    {}

} // namespace ustl
