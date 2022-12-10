#include "container/avltree_fwd.h"

namespace ustl
{

    avl_node_basic *
    _avlt_erase(avl_node_basic *__del, avl_node_basic *__header) ustl_cpp_noexcept
    {
        if(__del->_M_left)
            __del = _avlt_decrement(__del);
        if(__del->_M_right)
            __del = __del->right();
        
        if(__del == __header->left())
            __header->_M_left = _avlt_increment(__del);
        else if(__del == __header->right())
            __header->_M_right = _avlt_decrement(__del);
        
        // swap value

        if(_tree_is_rchild(__del))
        {
            __del->_M_parent->_M_right = __del->_M_left;
            if(__del->_M_left)
                __del->_M_left->_M_parent = __del->_M_parent;
        } 
        else if(_tree_is_lchild(__del))
        {
            __del->_M_parent->_M_left = __del->_M_left;
            if(__del->_M_left)
                __del->_M_left->_M_parent = __del->_M_parent;
        }
        else 
            __header->_M_reset();

         _avlt_erase_balance(__del->parent(), __header);
        return  __del;
    }


    void
    _avlt_insert_balance(bool __right, avl_node_basic *__pos, avl_node_basic *__header) ustl_cpp_noexcept
    {
        avl_node_basic  *__parent = __pos->parent();
        __pos->update_height();        


        // 使用 bool variable 减少inline 带来的代码膨胀
        if(2 == __parent->balance_factor())
        {
            if(__right) 
                _avlt_rotate_left(__pos, __header);
            _avlt_rotate_right(__parent, __header);
        }
        else if(-2 == __parent->balance_factor())
        {
            if(!__right) 
                _avlt_rotate_right(__pos, __header);
            _avlt_rotate_left(__parent, __header);
        }
        else
        {
            if(__parent == __header)
                return;
            bool __frchild = _tree_is_rchild(__parent);
            _avlt_insert_balance(__frchild, __parent, __header);
        }
    }



    void
    _avlt_erase_balance(avl_node_basic *__del, avl_node_basic *__header) ustl_cpp_noexcept
    {
        if(__del == __header->parent())
            return;

        avl_node_basic  *__parent = __del->parent();        
        __parent->update_height();

        if(0 == __parent->balance_factor())
            _avlt_erase_balance(__parent, __header);
        else if(2 == __parent->balance_factor()) // left height > right height
        {
            avl_node_basic  *__lchild = __parent->left();
            if(-1 == __lchild->balance_factor()) //lr
                _avlt_rotate_left(__lchild, __header);
            if(1 == __lchild->balance_factor() || 0 == __lchild->balance_factor()) // ll
                _avlt_rotate_right(__parent, __header);
            _avlt_erase_balance(__parent, __header);
        }
        else if(-2 == __parent->balance_factor()) // right height > left height
        {
            avl_node_basic  *__rchild = __parent->right();
            if(1 == __rchild->balance_factor()) // rl
                _avlt_rotate_right(__rchild, __header);
            if(-1 == __rchild->balance_factor() || 0 == __rchild->balance_factor()) // rr
                _avlt_rotate_left(__parent, __header);
            _avlt_erase_balance(__parent, __header);
        }
    }

} // namespace ustl
