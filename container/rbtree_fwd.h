#ifndef __USTL_RBTREE_FWD_H
#define __USTL_RBTREE_FWD_H

#include "include/config.h"
#include "container/tree_basic.h"

namespace ustl
{    

    struct _rbt_node_basic;

    _rbt_node_basic * 
    _rbt_erase(_rbt_node_basic *__del,
               _rbt_node_basic *__h) ustl_cpp_noexcept;

    void
    _rbt_recolor(_rbt_node_basic *__n,
                 _rbt_node_basic *__h) ustl_cpp_noexcept;

    void
    _rbt_rebalance_insert(_rbt_node_basic *__n,
                          _rbt_node_basic *__h) ustl_cpp_noexcept;

    void
    _rbt_rebalance_erase(_rbt_node_basic *__n,
                         _rbt_node_basic *__h) ustl_cpp_noexcept;



    enum _color : unsigned long {
        _Black,
        _Red
    };



    struct _rbt_node_basic
        : tree_node_basic
    {
        typedef     _color                   _Node_color;
        typedef     _rbt_node_basic  *       _Node_base_pointer;
        typedef     _rbt_node_basic const *  _CNode_base_pointer;


        _Node_color _M_color;

#ifdef __debug_ustl
        int _M_value_field;
#endif

        _rbt_node_basic();

        _rbt_node_basic(_Node_base_pointer);

        _rbt_node_basic(_Node_base_pointer, _Node_base_pointer, _Node_base_pointer);


        static  _color
        _S_color(_rbt_node_basic *__p) ustl_cpp_noexcept;


         void
        _M_setcolor(_color __c) ustl_cpp_noexcept;


        static  _Node_base_pointer
        maxnode(_Node_base_pointer __r) ustl_cpp_noexcept;


        static  _CNode_base_pointer
        maxnode(_CNode_base_pointer __r) ustl_cpp_noexcept;


        static  _Node_base_pointer
        minnode(_Node_base_pointer __r) ustl_cpp_noexcept;


        static  _CNode_base_pointer
        minnode(_CNode_base_pointer __r) ustl_cpp_noexcept;

         _Node_base_pointer
        right() ustl_cpp_noexcept;

         _Node_base_pointer
        left() ustl_cpp_noexcept;

         _Node_base_pointer
        parent() ustl_cpp_noexcept;

         _CNode_base_pointer
        right() const ustl_cpp_noexcept;

         _CNode_base_pointer
        left() const ustl_cpp_noexcept;

         _CNode_base_pointer
        parent() const ustl_cpp_noexcept;

    };

    inline
    _rbt_node_basic::
        _rbt_node_basic()
        : _M_color(_Red),
          tree_node_basic()  
    {}   


    inline
    _rbt_node_basic::
        _rbt_node_basic(_Node_base_pointer __p)
            : _M_color(_Red),
              tree_node_basic(__p)
    {}


    inline 
    _rbt_node_basic::
        _rbt_node_basic(_Node_base_pointer __l,
                       _Node_base_pointer __r, _Node_base_pointer __p)
            : _M_color(_Red), 
              tree_node_basic(__l, __r, __p)
    {}       


    inline _rbt_node_basic *
    _rbt_node_basic::
        left() ustl_cpp_noexcept
    { return    static_cast<_Node_base_pointer>(_M_left); }



    inline _rbt_node_basic *
    _rbt_node_basic::
        right() ustl_cpp_noexcept
    { return    static_cast<_Node_base_pointer>(_M_right); }



    inline _rbt_node_basic *
    _rbt_node_basic::
        parent() ustl_cpp_noexcept
    { return    static_cast<_Node_base_pointer>(_M_parent); }



    inline _rbt_node_basic const *
    _rbt_node_basic::
        left() const ustl_cpp_noexcept
    { return    static_cast<_Node_base_pointer>(_M_left); }



    inline _rbt_node_basic const *
    _rbt_node_basic::
        right() const ustl_cpp_noexcept
    { return    static_cast<_Node_base_pointer>(_M_right); }



    inline _rbt_node_basic const *
    _rbt_node_basic::
        parent() const ustl_cpp_noexcept
    { return    static_cast<_Node_base_pointer>(_M_parent); }



    inline auto
    _rbt_node_basic::
        _S_color(_rbt_node_basic *__p) ustl_cpp_noexcept -> _color
    { return    __p ? __p->_M_color : _Black; }   



    inline void
    _rbt_node_basic::
        _M_setcolor(_color __c) ustl_cpp_noexcept
    { if (this)  this->_M_color = __c; }



    inline auto
    _rbt_node_basic::
        maxnode(_Node_base_pointer __r) ustl_cpp_noexcept -> _Node_base_pointer
    {
        while (__r->_M_right)
            __r = __r->right();
        return __r;
    }       

    

    inline auto
    _rbt_node_basic::
        maxnode(_CNode_base_pointer __r) ustl_cpp_noexcept -> _CNode_base_pointer
    {
        while (__r->_M_right)
            __r = __r->right();
        return __r;
    }    



    inline auto
    _rbt_node_basic::
        minnode(_Node_base_pointer __r) ustl_cpp_noexcept -> _Node_base_pointer
    {
        while (__r->_M_left)
            __r = __r->left();
        return __r;
    }  



    inline auto
    _rbt_node_basic::
        minnode(_CNode_base_pointer __r) ustl_cpp_noexcept -> _CNode_base_pointer
    {
        while (__r->_M_left)
            __r = __r->right();
        return __r;
    }



    struct _Rbt_header
        : _rbt_node_basic
    {
        size_t _M_count;

        _Rbt_header();

        _Rbt_header(_Node_base_pointer, _Node_base_pointer, _Node_base_pointer, size_t);


        void 
        _M_reset() ustl_cpp_noexcept;

        _Node_base_pointer
        _S_Min_node() ustl_cpp_noexcept;

        _Node_base_pointer
        _S_Max_node() ustl_cpp_noexcept;

        _CNode_base_pointer
        _S_Min_node() const ustl_cpp_noexcept;

        _CNode_base_pointer
        _S_Max_node() const ustl_cpp_noexcept;
    };


    inline
    _Rbt_header::
        _Rbt_header()
            : _M_count(0),
              _rbt_node_basic(this, this, 0) 
    {}   



    inline
    _Rbt_header::
        _Rbt_header(_Node_base_pointer __l, _Node_base_pointer __r, 
                    _Node_base_pointer __p, size_t __n)
            : _M_count(__n), 
              _rbt_node_basic(__l, __r, __p) 
    {}    
 


    inline auto
    _Rbt_header::
        _S_Min_node() ustl_cpp_noexcept -> _Node_base_pointer
    { return    this->right(); }



    inline auto
    _Rbt_header::
        _S_Max_node() ustl_cpp_noexcept -> _Node_base_pointer
    { return    this->right(); }



    inline auto
    _Rbt_header::
        _S_Min_node() const ustl_cpp_noexcept -> _CNode_base_pointer
    { return    this->right(); }



    inline auto
    _Rbt_header::
        _S_Max_node() const ustl_cpp_noexcept -> _CNode_base_pointer
    { return    this->right(); }
   


    inline void
    _Rbt_header::
        _M_reset() ustl_cpp_noexcept
    {
        _M_count = 0;
        _M_parent = 0;
        _M_left = _M_right = this;
    }


    static inline _rbt_node_basic *
    _rbt_decrement(_rbt_node_basic *__p) ustl_cpp_noexcept
    { return    static_cast<_rbt_node_basic *>(_tree_decrement(__p)); }



    static inline _rbt_node_basic *
    _rbt_increment(_rbt_node_basic *__p) ustl_cpp_noexcept
    { return    static_cast<_rbt_node_basic *>(_tree_increment(__p)); }



    static inline bool
    _rbt_rchild_is_red(_rbt_node_basic *__node)
    { return    0 != __node && _rbt_node_basic::_S_color(__node->right()); }



    static inline bool
    _rbt_lchild_is_red(_rbt_node_basic *__node)
    { return    0 != __node && _rbt_node_basic::_S_color(__node->left()); }



    static inline _rbt_node_basic *
    _rbt_node_bro(_rbt_node_basic *__node)
    { return    static_cast<_rbt_node_basic *>(_tree_node_bro(__node)); }




    static inline void
    _rbt_insert(bool __is_l, _rbt_node_basic *__new,
                _rbt_node_basic *__pos, _rbt_node_basic *__header) ustl_cpp_noexcept
    {
        _tree_insert(__is_l, __new, __pos, __header);
        _rbt_recolor(__new, __header);
    }



    static inline void
    _rbt_rotate_left(_rbt_node_basic *__n,
                     _rbt_node_basic *__h) ustl_cpp_noexcept
    {
        _rbt_node_basic *__new = __n->right();
        __new->right()->_M_setcolor(__new->_M_color);
        __new->_M_setcolor(__n->_M_color);

        _tree_rotate_left(__n, __h);
    }



    static inline void
    _rbt_rotate_right(_rbt_node_basic *__n,
                      _rbt_node_basic *__h) ustl_cpp_noexcept
    {
        _rbt_node_basic *__new = __n->left();
        __new->left()->_M_setcolor(__new->_M_color);
        __new->_M_setcolor(__n->_M_color);

        _tree_rotate_right(__n, __h);
    }


}

#endif