#include "container/rbtree_fwd.h"

namespace ustl
{

    _rbt_node_basic *
    _rbt_erase(_rbt_node_basic *__del,
               _rbt_node_basic *__h) ustl_cpp_noexcept
    {
        if (__del->_M_left)
            __del = _rbt_decrement(__del);
        if (__del->_M_right)
            __del = __del->right();

        if (__del == __h->_M_left)
            __h->_M_left = _rbt_increment(__del);
        else if (__del == __h->_M_right)
            __h->_M_right = _rbt_decrement(__del);

        _rbt_rebalance_erase(__del, __h);

        if(_tree_is_rchild(__del)) 
            __del->_M_parent->_M_right = 0;
        else if(_tree_is_lchild(__del))
            __del->_M_parent->_M_left = 0;
        else 
            __h->_M_reset();

        return __del;
    }



    void
    _rbt_rebalance_insert(_rbt_node_basic *__n,
                          _rbt_node_basic *__h) ustl_cpp_noexcept
    {
        typedef _rbt_node_basic *_Node_ptr;
        _Node_ptr __parent = __n->parent();
        _Node_ptr __gparnet = __parent->parent();

        if (__parent == __gparnet->_M_right)
        {
            if (__n != __parent->_M_right) // rl
                _rbt_rotate_right(__parent, __h);
            _rbt_rotate_left(__gparnet, __h);
        }
        else
        {
            if (__n == __parent->_M_right) // lr
                _rbt_rotate_left(__parent, __h);
            _rbt_rotate_right(__gparnet, __h);
        }
        __gparnet->_M_setcolor(_Red);
    }



    void
    _rbt_rebalance_erase(_rbt_node_basic *__del,
                         _rbt_node_basic *__header) ustl_cpp_noexcept
    {
        /// @if color(__del) = red
        ///     don`t need rebalance operating
        if (__del == __header->_M_parent || _Red == _rbt_node_basic::_S_color(__del))
            return;

        _rbt_node_basic *__bro = _rbt_node_bro(__del);
        _rbt_node_basic *__parent = __del->parent();
        bool    __right = _tree_is_rchild(__del);

        if (_Black == _rbt_node_basic::_S_color(__bro))
        {
            if (!_rbt_rchild_is_red(__bro) && !_rbt_lchild_is_red(__bro))
            {
                // using recursion, from low to height, tell tree (height - 1)
                // let tree take it
                __bro->_M_setcolor(_Red);
                if (_Red != __parent->_M_color)
                    _rbt_rebalance_erase(__parent, __header);
                else
                    __parent->_M_setcolor(_Black);
            }
            else if (__right)
            {
                if (_rbt_rchild_is_red(__bro) && !_rbt_lchild_is_red(__bro)) // lr
                {
                    _rbt_rotate_left(__bro, __header);
                    __bro->_M_setcolor(_Red);
                    __bro = __bro->parent();
                }
                if (__bro && _Red == _rbt_node_basic::_S_color(__bro->left())) // ll
                {
                    _rbt_rotate_right(__parent, __header);
                    __parent->_M_setcolor(_Black);
                }
            }
            else
            {
                if (_rbt_lchild_is_red(__bro) && !_rbt_rchild_is_red(__bro)) // rl
                {
                    _rbt_rotate_right(__bro, __header);
                    __bro->_M_setcolor(_Red);
                    __bro = __bro->parent();
                }
                if (_rbt_rchild_is_red(__bro)) // rr
                {
                    _rbt_rotate_left(__parent, __header);
                    __parent->_M_setcolor(_Black);
                }
            }
        }
        else // color(__bro) = red, so childs of a sibling is all black
        {
            if (__right)
            {
                _rbt_rotate_right(__parent, __header);
                __bro->left()->_M_setcolor(_Black);
            }
            else
            {
                _rbt_rotate_left(__parent, __header);
                __bro->right()->_M_setcolor(_Black);
            }
            __parent->_M_setcolor(_Red);
            _rbt_rebalance_erase(__del, __header);
        }
    }



    void
    _rbt_recolor(_rbt_node_basic *__n,
                 _rbt_node_basic *__h) ustl_cpp_noexcept
    {
        typedef _rbt_node_basic _Node;
        typedef _rbt_node_basic *_Node_ptr;

        if (__n == __h->_M_parent)
        {
            __n->_M_setcolor(_Black);
            return;
        }

        __n->_M_setcolor(_Red);
        _Node_ptr __p = __n->parent();
        if (_Black == _Node::_S_color(__p))
            return;

        _Node_ptr __uncle = _rbt_node_bro(__p);
        if (_Red == _Node::_S_color(__uncle))
        {
            __uncle->_M_setcolor(_Black);
            __p->_M_setcolor(_Black);
            _rbt_recolor(__p->parent(), __h);
        }
        else
            _rbt_rebalance_insert(__n, __h);
    }
}