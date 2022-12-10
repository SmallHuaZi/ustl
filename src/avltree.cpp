#include "container/avltree_fwd.h"

namespace ustl
{


    void
    _avlt_insert_balance(avl_node_basic *__new, avl_node_basic *__header) ustl_cpp_noexcept
    {
        _Rotate_Mode __mode = _Rotate_Mode::__NON;
        avl_node_basic  *__parent = __new->parent();
        avl_node_basic  *__grande_parent = __parent->parent();

        // 使用 bool variable 减少inline 带来的代码膨胀
        bool __right = _tree_is_rchild(__new);
        if(_Balance_Factor::__RIGHT_BANK == __grande_parent->_M_height)
            __mode = !__right ? _Rotate_Mode::__RL : _Rotate_Mode::__RR;
        else if(_Balance_Factor::__LEFT_BANK == __grande_parent->_M_height)
            __mode = __right ? _Rotate_Mode::__LR : _Rotate_Mode::__LL;
        else
        {
            if(__right)
            {
                if(_Balance_Factor::__LEFT_BANK == __parent->_M_height)
                    __parent->_M_height = _Balance_Factor::__BALANCE;
                else if(_Balance_Factor::__BALANCE == __parent->_M_height)
                    __parent->_M_height = _Balance_Factor::__RIGHT_BANK;
            }
            else
            {
                if(_Balance_Factor::__RIGHT_BANK == __parent->_M_height)
                    __parent->_M_height = _Balance_Factor::__BALANCE;
                else if(_Balance_Factor::__BALANCE == __parent->_M_height)
                    __parent->_M_height = _Balance_Factor::__LEFT_BANK;
            }
        } 

        switch (__mode)
        {
        case _Rotate_Mode::__NON:
            break;

        case _Rotate_Mode::__LR :
            {
                avl_node_basic *__rchild = __parent->right();
                _avlt_rotate_left(__parent, __header);
                __rchild->update_height();
                __parent->update_height();
            }            
        case _Rotate_Mode::__LL : 
            {
                avl_node_basic *__lchild = __parent->left();
                _avlt_rotate_right(__grande_parent, __header);
                __lchild->update_height();
                __grande_parent->update_height();
            }
            break;
        
        case _Rotate_Mode::__RL :
            {
                avl_node_basic *__lchild = __parent->left();
                _avlt_rotate_right(__parent, __header);
                __lchild->update_height();
                __parent->update_height();
            }
        case _Rotate_Mode::__RR :
            {
                avl_node_basic *__rchild = __parent->right();
                _avlt_rotate_left(__grande_parent, __header);
                __rchild->update_height();
                __grande_parent->update_height();
            }
            break;
        }
    }

    void
    _avlt_erase_balance(avl_node_basic *__del, avl_node_basic *__header) ustl_cpp_noexcept
    {

    }

    void
    _avlt_update_factor(avl_node_basic  *__node) ustl_cpp_noexcept
    {

    }
} // namespace ustl
