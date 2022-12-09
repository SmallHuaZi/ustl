#include "container/avltree_fwd.h"

namespace ustl
{
    avl_node_basic::
        avl_node_basic()
            : tree_node_basic(0, 0, 0),
              _M_balance_factor(_Balance_Foctor::__BALANCE)
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
    _avlt_rotate_left(avl_node_basic *__node, avl_node_basic *__header)
    {
        _tree_rotate_left(__node, __header);
    }

    void
    _avlt_rotate_right(avl_node_basic *__node, avl_node_basic *__header)
    {   
        _tree_rotate_right(__node, __header);
    }

    void
    _avlt_insert(bool __right, 
                 avl_node_basic *__new, 
                 avl_node_basic *__pos, 
                 avl_node_basic *__header)
    {
        _tree_insert(__right, __new, __pos, __header);
        _avlt_insert_balance(__pos, __header);
    }

    void
    _avlt_erase(avl_node_basic *__del, avl_node_basic *__header)
    {
        _tree_erase(__del, __header);
        _avlt_erase_balance(__del, __header);
    }

    void
    _avlt_insert_balance(avl_node_basic *__pos, avl_node_basic *__header)
    {
        _Rotate_Mode __mode = _Rotate_Mode::__NON;
        avl_node_basic  *__grand_parent = __pos->parent();

        if(__pos == __grand_parent->_M_left && 
           _Balance_Foctor::__LEFT_BANK == __grand_parent->_M_balance_factor) {
            __mode = _is_rchild(__pos) ? _Rotate_Mode::__LR : _Rotate_Mode::__LL;
        }
        else if(_Balance_Foctor::__RIGHT_BANK == __grand_parent->_M_balance_factor) {
            __mode = _is_rchild(__pos) ? _Rotate_Mode::__RR : _Rotate_Mode::__RL;
        }

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
    _avlt_erase_balance(avl_node_basic *__del, avl_node_basic *__header)
    {}

    void
    _avlt_update_factor(avl_node_basic  *__start)
    {

    }
} // namespace ustl
