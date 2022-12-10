#include "container/avltree_fwd.h"

namespace ustl
{
    avl_node_basic::
        avl_node_basic()
            : tree_node_basic(0, 0, 0),
              _M_height(1) 
    {}

    avl_node_basic *
    avl_node_basic::
        left() ustl_cpp_noexcept
    { return    static_cast<node_basic_pointer>(_M_left); }

    avl_node_basic *
    avl_node_basic::    
        right() ustl_cpp_noexcept
    { return    static_cast<node_basic_pointer>(_M_right); }

    avl_node_basic *
    avl_node_basic::
        parent() ustl_cpp_noexcept
    { return    static_cast<node_basic_pointer>(_M_parent); }

    avl_node_basic const *
    avl_node_basic::
        left() const ustl_cpp_noexcept
    { return    static_cast<const_node_basic_pointer>(_M_left); }

    avl_node_basic const *
    avl_node_basic::
        right() const ustl_cpp_noexcept
    { return    static_cast<const_node_basic_pointer>(_M_right); }

    avl_node_basic const *
    avl_node_basic::
        parent() const ustl_cpp_noexcept
    { return    static_cast<const_node_basic_pointer>(_M_parent); }

    size_t
    avl_node_basic::
        update_height() ustl_cpp_noexcept
    {
        avl_node_basic const *__cv = this;
        __cv->update_height();
    }

    size_t
    avl_node_basic::
        update_height() const ustl_cpp_noexcept
    {

    }

    avl_header::
        avl_header()
            : avl_node_basic(),
              _M_size(0)
    {}

    avl_node_basic *
    avl_header::
        _M_Min_node() ustl_cpp_noexcept
    { return    left(); }

    avl_node_basic *
    avl_header::
        _M_Max_node() ustl_cpp_noexcept
    { return    right(); }

    avl_node_basic *
    avl_header::
        _M_root() ustl_cpp_noexcept
    { return    parent(); }

    avl_node_basic const *
    avl_header::
        _M_Min_node() const ustl_cpp_noexcept
    { return    left(); }

    avl_node_basic const *
    avl_header::
        _M_Max_node() const ustl_cpp_noexcept
    { return    right(); }

    avl_node_basic const *
    avl_header::
        _M_root() const ustl_cpp_noexcept
    { return    parent(); }




    void
    _avlt_insert_balance(avl_node_basic *__pos, avl_node_basic *__header) ustl_cpp_noexcept
    {
        _Rotate_Mode __mode = _Rotate_Mode::__NON;
        avl_node_basic  *__grand_parent = __pos->parent();


        switch (__mode)
        {
        case _Rotate_Mode::__LR :
            _avlt_rotate_left(__pos, __header);
        case _Rotate_Mode::__LL : 
            _avlt_rotate_right(__grand_parent, __header);
            break;
        
        case _Rotate_Mode::__RL :
            _avlt_rotate_right(__pos, __header);
        case _Rotate_Mode::__RR :
            _avlt_rotate_left(__grand_parent, __header);
            break;
        }
    }

    void
    _avlt_erase_balance(avl_node_basic *__del, avl_node_basic *__header) ustl_cpp_noexcept
    {}

    void
    _avlt_update_factor(avl_node_basic  *__node) ustl_cpp_noexcept
    {

    }
} // namespace ustl
