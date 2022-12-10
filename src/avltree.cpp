#include "container/avltree_fwd.h"

namespace ustl
{


    size_t
    avl_node_basic::
        update_height() const ustl_cpp_noexcept
    {

    }


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
