#include "container/avltree_fwd.h"

namespace ustl
{
    avl_node_basic::
        avl_node_basic()
            : _M_left(0), 
              _M_right(0),
              _M_parent(0),
              _M_balance_factor(_Balance_Foctor::__BALANCE)
    {}

    avl_header::
        avl_header()
            : avl_node_basic(),
              _M_size(0)
    {}

    avl_node_basic *
    avl_header::
        _M_Min_node()
    { return    _M_left; }

    avl_node_basic *
    avl_header::
        _M_Max_node()
    { return    _M_right; }

    avl_node_basic *
    avl_header::
        _M_root()
    { return    _M_parent; }


    void
    _avlt_insert(avl_node_basic *__new, avl_node_basic *__pos, bool __right)
    {
        avl_node_basic  *__grand_parent = __pos->_M_parent;
        _Rotate_Mode     __balance_mode = _Rotate_Mode::__NON;
    
        if(__right) 
            __pos->_M_right = __new;
        else        
            __pos->_M_left  = __new;

        if(__pos == __grand_parent->_M_left && 
           _Balance_Foctor::__LEFT_BANK == __grand_parent->_M_balance_factor) {
            __balance_mode = __right ? _Rotate_Mode::__LR : _Rotate_Mode::__LL;
        }
        else if(_Balance_Foctor::__RIGHT_BANK == __grand_parent->_M_balance_factor) {
            __balance_mode = __right ? _Rotate_Mode::__RR : _Rotate_Mode::__RL;
        }

        _avlt_insert_balance(__pos, __balance_mode);
    }

    void
    _avlt_insert_balance(avl_node_basic *__pos, _Rotate_Mode __mode)
    {
        if(_Rotate_Mode::__NON == __mode)
            return;

        avl_node_basic  *__grand_parent = __pos->_M_parent;
        switch (__mode)
        {
        case _Rotate_Mode::__LR :
            _avlt_left_rotate(__pos);
        case _Rotate_Mode::__LL : 
            _avlt_right_rotate(__grand_parent);
            break;
        
        case _Rotate_Mode::__RL :
            _avlt_right_rotate(__pos);
        case _Rotate_Mode::__RR :
            _avlt_left_rotate(__grand_parent);
            break;
        }
    }

    void
    _avlt_left_rotate(avl_node_basic    *__node)
    {
        avl_node_basic  *__parent = __node->_M_parent;
        avl_node_basic  *__grand_parent = __parent->_M_parent;


        
    }

    void
    _avlt_right_rotate(avl_node_basic   *__node)
    {

    }
} // namespace ustl
