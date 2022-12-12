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
    tree_node_pool::
        operator()(tree_recycle) 
    {
        tree_node_basic *__ret = 0;
        tree_node_basic *__left_most = _M_header._M_left;
        if(0 != __left_most)
        {
            __ret = __left_most;
            __left_most = __left_most->_M_parent;
            if(&_M_header != __left_most)
            {
                if(_tree_is_lchild(__ret)) 
                {
                    __left_most->_M_left = 0;
                    while(__left_most->_M_right)
                        __left_most = __left_most->_M_right;
                    while(__left_most->_M_left)
                        __left_most = __left_most->_M_left;
                    if(__left_most->_M_right)
                        __left_most = __left_most->_M_right;
                    _M_header._M_left = __left_most;

                }
                else
                    __left_most->_M_right = 0;
            }
            else
                _M_header._M_reset();
        }
        return 0 == __ret ? (*this)(tree_extract()) : 0;
    }


    tree_node_basic *
    tree_node_pool::
        operator()(tree_extract) 
    {
        tree_node_basic *__ret = 0;
        if(_M_list_size > 0)
        {
            __ret = _M_list_last;
            _M_list_last = __ret->_M_left;
            --_M_list_size;
        }
        return  __ret;
    }


    bool 
    tree_node_pool::
        operator()(tree_node_basic *__node) 
    {
        if(size_t(__MAX_NODE_COUNT) > _M_list_size) 
        {
            if(0 == _M_list_first)
            {
                _M_list_first = __node;
                _M_list_last  = __node;
            }
            else
            {
                _M_list_last->_M_right = __node;
                __node->_M_left = _M_list_last;
                _M_list_last = __node;
            } 
            __node->_M_right = 0;
            ++_M_list_size;
            return true;
        }
        return false;
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
            if(__node == __tmp->_M_parent)
                return  __tmp;

            while(__node == __tmp->_M_left)
            {
                __node = __tmp;
                __tmp  = __tmp->_M_parent;
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
            if(__node == __tmp->_M_parent)
                return  __tmp;

            while(__node == __tmp->_M_right)
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
    _tree_insert(bool __left, 
                 tree_node_basic *__new, 
                 tree_node_basic *__pos, 
                 tree_node_basic *__header) ustl_cpp_noexcept
    {
        if(__left)
        {
            if(__header->_M_parent)
            {
                if(__pos == __header->_M_left)
                    __header->_M_left = __new;
                __pos->_M_left = __new;
            }
            else
            {
                __header->_M_left = __new;
                __header->_M_right = __new;
                __header->_M_parent = __new;
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


    size_t
    _tree_node_height(tree_node_basic * const __root) ustl_cpp_noexcept
    {
        if(0 == __root)
            return 0;

        size_t  __height = 1;
        size_t  __tmp_height = 1;
        bool    __recall = false;
        bool    __from_lchild = false;
        tree_node_basic *__first = __root;
        tree_node_basic const *__last  = __root->_M_Max_node();

        do
        {
            if(__recall)
            {
                __from_lchild = _tree_is_lchild(__first);
                __first = __first->_M_parent;

                if(__from_lchild && __first->_M_right)
                {
                    __first = __first->_M_right;
                    __recall = false;
                }
                else
                    --__tmp_height;
            }
            else
            {
                if(__first->_M_left)
                {
                    __first = __first->_M_left;
                    ++__tmp_height;
                }
                else if(__first->_M_right)
                {
                    __first = __first->_M_right; 
                    ++__tmp_height;
                }
                else
                {
                    __recall = true;
                    __height = __height > __tmp_height ? __height : __tmp_height;
                }
            }
        } while(__first != __last);

        return __height  > __tmp_height ? __height : __tmp_height;
    }

} // namespace ustl
