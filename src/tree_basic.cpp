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

    void
    tree_node_basic::
        _M_reset()
    {
        _M_left = 0;
        _M_right = 0;
        _M_parent = 0;
    }

    tree_node_basic *
    _tree_decrement(tree_node_basic *__node) ustl_cpp_noexcept 
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
    _tree_increment(tree_node_basic *__node) ustl_cpp_noexcept
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
    _tree_rotate_left(tree_node_basic *__node, tree_node_basic *__header)
        ustl_cpp_noexcept
    {
        tree_node_basic *__parent = __node->_M_parent;
        tree_node_basic *__new = __node->_M_right;

        __node->_M_parent = __new;
        __new->_M_parent = __parent;

        if(__new->_M_left)
            __new->_M_left->_M_parent = __node;
        
        if(__parent == __header)
            __header->_M_parent = __new;
        else if(__node == __parent->_M_left)
            __parent->_M_left = __new;
        else
            __parent->_M_right = __new;

        __node->_M_right = __new->_M_left;
        __new->_M_left   = __node;
        
    }

    void
    _tree_rotate_right(tree_node_basic *__node, tree_node_basic *__header)
        ustl_cpp_noexcept
    {
        tree_node_basic *__parent = __node->_M_parent;
        tree_node_basic *__new = __node->_M_left;

        __node->_M_parent = __new;
        __new->_M_parent =__parent;

        if(__new->_M_right)
            __new->_M_right->_M_parent = __node;

        if(__parent == __header)
            __header->_M_parent = __new;
        else if(__node == __parent->_M_left)
            __parent->_M_left = __new;
        else
            __parent->_M_right = __new;
        
        __node->_M_left = __new->_M_right;
        __new->_M_right = __node;
    }

    void
    _tree_insert(bool __right, 
                 tree_node_basic *__new, 
                 tree_node_basic *__pos, 
                 tree_node_basic *__header) ustl_cpp_noexcept
    {
        if(__right)
        {
            if(__header->_M_parent)
            {
                if(__pos == __header->_M_left)
                    __header->_M_left = __pos;
                __pos->_M_left = __new;
            }
            else
            {
                __pos->_M_parent = __new;
                __pos->_M_right = __pos->_M_left = __new;
            }
        }
        else
        {
            if(__pos == __header->_M_right)
                __header->_M_right = __new;
            __pos->_M_right = __new;
        }
        __new->_M_parent = __pos;
    }

    void 
    _tree_erase(tree_node_basic *__del, tree_node_basic *__header) ustl_cpp_noexcept
    {
        if(__del->_M_left)
            __del = _tree_decrement(__del);
        if(__del->_M_right)
            __del = __del->_M_right;
        
        if(__del == __header->_M_left)
            __header->_M_left = _tree_increment(__del);
        else if(__del == __header->_M_right)
            __header->_M_right = _tree_decrement(__del);

        if(_is_rchild(__del)) 
            __del->_M_parent->_M_right = 0;
        else if(_is_lchild(__del))
            __del->_M_parent->_M_left = 0;
        else if(__del == __header->_M_parent)
            __header->_M_reset();

    }

    size_t
    _tree_node_height(tree_node_basic *__root) ustl_cpp_noexcept
    {
        if(__root)
        {
            size_t  __height = 1;
            bool    __recall = false;
            bool    __from_lchild = false;
            size_t  __tmp_height = 0;
            tree_node_basic *__tmp = __root;
            do
            {
                if(__recall)
                {
                    __from_lchild = _is_lchild(__tmp);
                    __tmp = __tmp->_M_parent;
                    if(__from_lchild && __tmp->_M_right)
                    {
                        __tmp = __tmp->_M_right;
                        __recall = false;
                    }
                    else
                        --__tmp_height;
                }
                else
                {
                    if(__tmp->_M_left)
                    {
                        __tmp = __tmp->_M_left;
                        ++__tmp_height;
                    }
                    else if(__tmp->_M_right)
                    {
                       __tmp = __tmp->_M_right; 
                       ++__tmp_height;
                    }
                    else
                    {
                        __recall = true;
                        __height = __height > __tmp_height ? __height : __tmp_height;
                    }
                }
            } while(!__from_lchild && __tmp == __root);

            return __height;
        }
        return 0;
    }

} // namespace ustl
