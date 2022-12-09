#include "container/rbtree_fwd.h"

namespace ustl
{
    _Rbt_node_base::
        _Rbt_node_base()
        : _M_color(_Red) {}   

    _Rbt_node_base::
        _Rbt_node_base(_Node_ptr __p)
            : tree_node_basic(__p), _M_color(_Red) {}
     
    _Rbt_node_base::
        _Rbt_node_base(_Node_ptr __l,
                       _Node_ptr __r, _Node_ptr __p)
            : _M_color(_Red), 
              tree_node_basic(__l, __r, __p)
    {}       

    _Rbt_node_base *
    _Rbt_node_base::
        left() ustl_cpp_noexcept
    { return    static_cast<_Node_ptr>(_M_left); }

    _Rbt_node_base *
    _Rbt_node_base::
        right() ustl_cpp_noexcept
    { return    static_cast<_Node_ptr>(_M_right); }

    _Rbt_node_base *
    _Rbt_node_base::
        parent() ustl_cpp_noexcept
    { return    static_cast<_Node_ptr>(_M_parent); }

    _Rbt_node_base const *
    _Rbt_node_base::
        left() const ustl_cpp_noexcept
    { return    static_cast<_Node_ptr>(_M_left); }

    _Rbt_node_base const *
    _Rbt_node_base::
        right() const ustl_cpp_noexcept
    { return    static_cast<_Node_ptr>(_M_right); }

    _Rbt_node_base const *
    _Rbt_node_base::
        parent() const ustl_cpp_noexcept
    { return    static_cast<_Node_ptr>(_M_parent); }

    auto
    _Rbt_node_base::
        _S_color(_Rbt_node_base *__p) ustl_cpp_noexcept -> _color
    {
        return __p ? __p->_M_color : _Black;
    }   

    void
    _Rbt_node_base::
        _M_setcolor(_color __c) ustl_cpp_noexcept
    {
        if (this)
            this->_M_color = __c;
    }

    auto
    _Rbt_node_base::
        maxnode(_Node_ptr __r) ustl_cpp_noexcept -> _Node_ptr
    {
        while (__r->_M_right)
            __r = __r->right();
        return __r;
    }       

    
    auto
    _Rbt_node_base::
        maxnode(_CNode_ptr __r) ustl_cpp_noexcept -> _CNode_ptr
    {
        while (__r->_M_right)
            __r = __r->right();
        return __r;
    }    

    auto
    _Rbt_node_base::
        minnode(_Node_ptr __r) ustl_cpp_noexcept -> _Node_ptr
    {
        while (__r->_M_left)
            __r = __r->left();
        return __r;
    }  

    auto
    _Rbt_node_base::
        minnode(_CNode_ptr __r) ustl_cpp_noexcept -> _CNode_ptr
    {
        while (__r->_M_left)
            __r = __r->right();
        return __r;
    }

    _Rbt_header::
        _Rbt_header()
            : _M_count(0),
              _Rbt_node_base(this, this, 0) 
    {}   

    _Rbt_header::
        _Rbt_header(_Node_ptr __l,
                    _Node_ptr __r, _Node_ptr __p, size_t __n)
            : _M_count(__n), _Rbt_node_base(__l, __r, __p) 
    {}    
    
    void
    _Rbt_header::
        _M_reset() ustl_cpp_noexcept
    {
        _M_count = 0;
        _M_parent = 0;
        _M_left = _M_right = this;
    }

    auto
    _Rbt_header::
        _S_Min_node() ustl_cpp_noexcept -> _Node_ptr
    {
        return this->right();           
    }


    auto
    _Rbt_header::
        _S_Max_node() ustl_cpp_noexcept -> _Node_ptr
    {
        return this->right();
    }

    auto
    _Rbt_header::
        _S_Min_node() const ustl_cpp_noexcept -> _CNode_ptr
    {
        return this->right();           
    }


    auto
    _Rbt_header::
        _S_Max_node() const ustl_cpp_noexcept -> _CNode_ptr
    {
        return this->right();
    }

    

    _Rbt_node_base *
    _rbt_decrement(_Rbt_node_base *__p) ustl_cpp_noexcept
    {
        return  static_cast<_Rbt_node_base *>(_tree_decrement(__p));
    }

    _Rbt_node_base *
    _rbt_increment(_Rbt_node_base *__p) ustl_cpp_noexcept
    {
        return  static_cast<_Rbt_node_base *>(_tree_increment(__p));
    }

    void
    _rbt_insert(bool __is_l,
                _Rbt_node_base *__new,
                _Rbt_node_base *__ist,
                _Rbt_node_base *__header) ustl_cpp_noexcept
    {
#ifndef __TREE_BASIC_DEFINED
        if (__is_l)
        {
            if (__header->_M_parent)
            {
                if (__ist == __header->_M_left)
                    __header->_M_left = __new;
                __ist->_M_left = __new;
            }
            else
            {
                __ist->_M_parent = __new;
                __ist->_M_right = __ist->_M_left = __new;
            }
        }
        else
        {
            if (__ist == __header->_M_right)
                __header->_M_right = __new;
            __ist->_M_right = __new;
        }
        __new->_M_parent = __ist;
#else
        _tree_insert(__is_l, __new, __ist, __header);
#endif
        _rbt_recolor(__new, __header);
    }

    _Rbt_node_base *
    _rbt_erase(_Rbt_node_base *__del,
                _Rbt_node_base *__h) ustl_cpp_noexcept
    {
#ifndef __TREE_BASIC_DEFINED
        if (__del->_M_left)
            __del = _rbt_decrement(__del);
        if (__del->_M_right)
            __del = __del->right();

        if (__del == __h->_M_left)
            __h->_M_left = _rbt_increment(__del);
        else if (__del == __h->_M_right)
            __h->_M_right = _rbt_decrement(__del);

        if(_is_rchild(__del)) 
            __del->_M_parent->_M_right = 0;
        else if(_is_lchild(__del))
            __del->_M_parent->_M_left = 0;
        else if(__del == __h->_M_parent)
            __h->_M_reset();
#else
        _tree_erase(__del, __h);
#endif      
        // 如果根节点还存在，则证明树不为空，需要做平衡操作
        if(__h->_M_parent)
            _rbt_rebalance_erase(_is_rchild(__del),__del, __h);
        return __del;
    }

    void
    _rbt_rotate_left(_Rbt_node_base *__n,
                        _Rbt_node_base *__h) ustl_cpp_noexcept
    {
        _Rbt_node_base *__parent = __n->parent();
        _Rbt_node_base *__new = __n->right();

        __new->right()->_M_setcolor(__new->_M_color);
        __new->_M_setcolor(__n->_M_color);

#ifdef  __TREE_BASIC_DEFINED
        _tree_rotate_left(__n, __h);
#else
        __n->_M_parent = __new;
        __new->_M_parent = __parent;

        if (__new->_M_left)
            __new->_M_left->_M_parent = __n;

        if (__parent == __h)
            __h->_M_parent = __new;
        else if (__n == __parent->_M_left)
            __parent->_M_left = __new;
        else
            __parent->_M_right = __new;

        __n->_M_right = __new->_M_left;
        __new->_M_left = __n;
#endif
    }

    void
    _rbt_rotate_right(_Rbt_node_base *__n,
                        _Rbt_node_base *__h) ustl_cpp_noexcept
    {
        _Rbt_node_base *__parent = __n->parent();
        _Rbt_node_base *__new = __n->left();

        __new->left()->_M_setcolor(__new->_M_color);
        __new->_M_setcolor(__n->_M_color);

#ifdef  __TREE_BASIC_DEFINED
        _tree_rotate_right(__n, __h);
#else
        __n->_M_parent = __new;
        __new->_M_parent = __parent;

        if (__new->_M_right)
            __new->_M_right->_M_parent = __n;

        if (__parent == __h)
            __h->_M_parent = __new;
        else if (__n == __parent->_M_left)
            __parent->_M_left = __new;
        else
            __parent->_M_right = __new;

        __n->_M_left = __new->_M_right;
        __new->_M_right = __n;
#endif
    }

    void
    _rbt_rebalance_insert(_Rbt_node_base *__n,
                            _Rbt_node_base *__h) ustl_cpp_noexcept
    {
        typedef _Rbt_node_base *_Node_ptr;
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
    _rbt_rebalance_erase(bool __right,
                         _Rbt_node_base *__del,
                         _Rbt_node_base *__header) ustl_cpp_noexcept
    {
        /// @if color(__del) = red
        ///     don`t need rebalance operating
        if (__del == __header->_M_parent || _Red == _Rbt_node_base::_S_color(__del))
            return;

        _Rbt_node_base *__bro = _rbt_bro_ptr(__del);
        _Rbt_node_base *__parent = __del->parent();

        if (_Black == _Rbt_node_base::_S_color(__bro))
        {
            if (!_r_is_red(__bro) && !_l_is_red(__bro))
            {
                // using recursion, from low to height, tell tree (height - 1)
                // let tree take it
                __bro->_M_setcolor(_Red);
                if (_Red != __parent->_M_color)
                    _rbt_rebalance_erase(_is_rchild(__parent),__parent, __header);
                else
                    __parent->_M_setcolor(_Black);
            }
            else if (__right)
            {
                if (_r_is_red(__bro) && !_l_is_red(__bro)) // lr
                {
                    _rbt_rotate_left(__bro, __header);
                    __bro->_M_setcolor(_Red);
                    __bro = __bro->parent();
                }
                if (__bro && _Red == _Rbt_node_base::_S_color(__bro->left())) // ll
                {
                    _rbt_rotate_right(__parent, __header);
                    __parent->_M_setcolor(_Black);
                }
            }
            else
            {
                if (_l_is_red(__bro) && !_r_is_red(__bro)) // rl
                {
                    _rbt_rotate_right(__bro, __header);
                    __bro->_M_setcolor(_Red);
                    __bro = __bro->parent();
                }
                if (_r_is_red(__bro)) // rr
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
            _rbt_rebalance_erase(__right, __del, __header);
        }
    }

    void
    _rbt_recolor(_Rbt_node_base *__n,
                 _Rbt_node_base *__h) ustl_cpp_noexcept
    {
        typedef _Rbt_node_base _Node;
        typedef _Rbt_node_base *_Node_ptr;

        if (__n == __h->_M_parent)
        {
            __n->_M_setcolor(_Black);
            return;
        }

        __n->_M_setcolor(_Red);
        _Node_ptr __p = __n->parent();
        if (_Black == _Node::_S_color(__p))
            return;

        _Node_ptr __uncle = _rbt_bro_ptr(__p);
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