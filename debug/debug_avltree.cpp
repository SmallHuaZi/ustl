#include "container/avltree_fwd.h"

struct avltree_node
    :  ustl::avl_node_basic
{
    avltree_node() = default;

    avltree_node(int data)
        : _M_val(data)
    {}

    avltree_node *
    left()
    { return    static_cast<avltree_node *>(_M_left); }

    avltree_node *
    right()
    { return    static_cast<avltree_node *>(_M_right); }

    int     _M_val;
};

struct avltree
{

    void
    _M_insert(int __data)
    {
        avltree_node *__new = new avltree_node(__data);
        avltree_node *__pos = _M_get_insert_pos(__data);
        bool __is_l = __new->_M_val < __pos->_M_val ? true : false;
        ustl::_avlt_insert(__is_l, __new, __pos, &_M_header);
    }

    avltree_node *
    _M_get_insert_pos(int __data)
    {
        avltree_node    *__pos{0};
        avltree_node    *__r = static_cast<avltree_node *>(_M_header._M_root());
        while (__r)
        {
            __pos = __r;
            if (__data < __r->_M_val)
                __r = __r->left();
            else
                __r = __r->right();
        }
        return __pos;
    }

    ustl::avl_header    _M_header;
};

#include <iostream>
int 
main()
{
    avltree __tree;

    for(int __i = 0; __i < 20; ++__i)
        __tree._M_insert(__i);
    avltree_node *__min = static_cast<avltree_node *>(__tree._M_header._M_left);
    for(int __i = 0; __i< 20; ++__i)
    {
        std::cout << __min->_M_val << std::endl;
        __min = static_cast<avltree_node *>(ustl::_tree_increment(__min));
    }
    return  0;
}