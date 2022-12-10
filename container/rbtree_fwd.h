#ifndef __rbt_fwd_h
#define __rbt_fwd_h

#include "include/config.h"
#include "container/tree_basic.h"

namespace ustl
{    

    struct _Rbt_node_base;

    void
    _rbt_recolor(_Rbt_node_base *__n,
                 _Rbt_node_base *__h) ustl_cpp_noexcept;

    void
    _rbt_rebalance_insert(_Rbt_node_base *__n,
                          _Rbt_node_base *__h) ustl_cpp_noexcept;

    void
    _rbt_rebalance_erase(bool __right,
                         _Rbt_node_base *__n,
                         _Rbt_node_base *__h) ustl_cpp_noexcept;



    enum _color : unsigned long {
        _Black,
        _Red
    };

    struct _Rbt_node_base
        : tree_node_basic
    {
        using _Node_color = _color;
        using _Node_ptr = _Rbt_node_base *;
        using _CNode_ptr = const _Rbt_node_base *;
        /**
         * take typedef or using to cover function overload
         */

        _Node_color _M_color;

#ifdef __debug_ustl
        int _M_value;
#endif

        _Rbt_node_base();

        _Rbt_node_base(_Node_ptr);

        _Rbt_node_base(_Node_ptr, _Node_ptr, _Node_ptr);


        static  _color
        _S_color(_Rbt_node_base *__p) ustl_cpp_noexcept;


         void
        _M_setcolor(_color __c) ustl_cpp_noexcept;


        static  _Node_ptr
        maxnode(_Node_ptr __r) ustl_cpp_noexcept;


        static  _CNode_ptr
        maxnode(_CNode_ptr __r) ustl_cpp_noexcept;


        static  _Node_ptr
        minnode(_Node_ptr __r) ustl_cpp_noexcept;


        static  _CNode_ptr
        minnode(_CNode_ptr __r) ustl_cpp_noexcept;

         _Node_ptr
        right() ustl_cpp_noexcept;

         _Node_ptr
        left() ustl_cpp_noexcept;

         _Node_ptr
        parent() ustl_cpp_noexcept;

         _CNode_ptr
        right() const ustl_cpp_noexcept;

         _CNode_ptr
        left() const ustl_cpp_noexcept;

         _CNode_ptr
        parent() const ustl_cpp_noexcept;

    };

    inline
    _Rbt_node_base::
        _Rbt_node_base()
        : _M_color(_Red),
          tree_node_basic()  
    {}   


    inline
    _Rbt_node_base::
        _Rbt_node_base(_Node_ptr __p)
            : _M_color(_Red),
              tree_node_basic(__p)
    {}


    inline 
    _Rbt_node_base::
        _Rbt_node_base(_Node_ptr __l,
                       _Node_ptr __r, _Node_ptr __p)
            : _M_color(_Red), 
              tree_node_basic(__l, __r, __p)
    {}       


    inline _Rbt_node_base *
    _Rbt_node_base::
        left() ustl_cpp_noexcept
    { return    static_cast<_Node_ptr>(_M_left); }



    inline _Rbt_node_base *
    _Rbt_node_base::
        right() ustl_cpp_noexcept
    { return    static_cast<_Node_ptr>(_M_right); }



    inline _Rbt_node_base *
    _Rbt_node_base::
        parent() ustl_cpp_noexcept
    { return    static_cast<_Node_ptr>(_M_parent); }



    inline _Rbt_node_base const *
    _Rbt_node_base::
        left() const ustl_cpp_noexcept
    { return    static_cast<_Node_ptr>(_M_left); }



    inline _Rbt_node_base const *
    _Rbt_node_base::
        right() const ustl_cpp_noexcept
    { return    static_cast<_Node_ptr>(_M_right); }



    inline _Rbt_node_base const *
    _Rbt_node_base::
        parent() const ustl_cpp_noexcept
    { return    static_cast<_Node_ptr>(_M_parent); }



    inline auto
    _Rbt_node_base::
        _S_color(_Rbt_node_base *__p) ustl_cpp_noexcept -> _color
    { return __p ? __p->_M_color : _Black; }   



    inline void
    _Rbt_node_base::
        _M_setcolor(_color __c) ustl_cpp_noexcept
    { if (this)  this->_M_color = __c; }



    inline auto
    _Rbt_node_base::
        maxnode(_Node_ptr __r) ustl_cpp_noexcept -> _Node_ptr
    {
        while (__r->_M_right)
            __r = __r->right();
        return __r;
    }       

    

    inline auto
    _Rbt_node_base::
        maxnode(_CNode_ptr __r) ustl_cpp_noexcept -> _CNode_ptr
    {
        while (__r->_M_right)
            __r = __r->right();
        return __r;
    }    



    inline auto
    _Rbt_node_base::
        minnode(_Node_ptr __r) ustl_cpp_noexcept -> _Node_ptr
    {
        while (__r->_M_left)
            __r = __r->left();
        return __r;
    }  



    inline auto
    _Rbt_node_base::
        minnode(_CNode_ptr __r) ustl_cpp_noexcept -> _CNode_ptr
    {
        while (__r->_M_left)
            __r = __r->right();
        return __r;
    }



    struct _Rbt_header
        : _Rbt_node_base
    {
        size_t _M_count;

        _Rbt_header();

        _Rbt_header(_Node_ptr, _Node_ptr, _Node_ptr, size_t);


        void 
        _M_reset() ustl_cpp_noexcept;

        _Node_ptr
        _S_Min_node() ustl_cpp_noexcept;

        _Node_ptr
        _S_Max_node() ustl_cpp_noexcept;

        _CNode_ptr
        _S_Min_node() const ustl_cpp_noexcept;

        _CNode_ptr
        _S_Max_node() const ustl_cpp_noexcept;
    };


    inline
    _Rbt_header::
        _Rbt_header()
            : _M_count(0),
              _Rbt_node_base(this, this, 0) 
    {}   



    inline
    _Rbt_header::
        _Rbt_header(_Node_ptr __l, _Node_ptr __r, 
                    _Node_ptr __p, size_t __n)
            : _M_count(__n), 
              _Rbt_node_base(__l, __r, __p) 
    {}    
 


    inline auto
    _Rbt_header::
        _S_Min_node() ustl_cpp_noexcept -> _Node_ptr
    { return this->right(); }



    inline auto
    _Rbt_header::
        _S_Max_node() ustl_cpp_noexcept -> _Node_ptr
    { return this->right(); }



    inline auto
    _Rbt_header::
        _S_Min_node() const ustl_cpp_noexcept -> _CNode_ptr
    { return this->right(); }



    inline auto
    _Rbt_header::
        _S_Max_node() const ustl_cpp_noexcept -> _CNode_ptr
    { return this->right(); }
   


    inline void
    _Rbt_header::
        _M_reset() ustl_cpp_noexcept
    {
        _M_count = 0;
        _M_parent = 0;
        _M_left = _M_right = this;
    }


    static inline _Rbt_node_base *
    _rbt_decrement(_Rbt_node_base *__p) ustl_cpp_noexcept
    { return  static_cast<_Rbt_node_base *>(_tree_decrement(__p)); }



    static inline _Rbt_node_base *
    _rbt_increment(_Rbt_node_base *__p) ustl_cpp_noexcept
    { return  static_cast<_Rbt_node_base *>(_tree_increment(__p)); }



    static inline bool
    _rbt_rchild_is_red(_Rbt_node_base *__node)
    { return  0 != __node && _Rbt_node_base::_S_color(__node->right()); }



    static inline bool
    _rbt_lchild_is_red(_Rbt_node_base *__node)
    { return 0 != __node && _Rbt_node_base::_S_color(__node->left()); }



    static inline _Rbt_node_base *
    _rbt_node_bro(_Rbt_node_base *__node)
    { return static_cast<_Rbt_node_base *>(_tree_node_bro(__node)); }



    static inline _Rbt_node_base *
    _rbt_erase(_Rbt_node_base *__del,
               _Rbt_node_base *__h) ustl_cpp_noexcept
    { 
        _tree_erase(__del, __h);
        if(__h->_M_parent) _rbt_rebalance_erase(_tree_is_rchild(__del),__del, __h); 
    }



    static inline void
    _rbt_insert(bool __is_l, _Rbt_node_base *__new,
                _Rbt_node_base *__ist, _Rbt_node_base *__header) ustl_cpp_noexcept
    {
        _tree_insert(__is_l, __new, __ist, __header);
        _rbt_recolor(__new, __header);
    }



    static inline void
    _rbt_rotate_left(_Rbt_node_base *__n,
                     _Rbt_node_base *__h) ustl_cpp_noexcept
    {
        _Rbt_node_base *__new = __n->right();
        __new->right()->_M_setcolor(__new->_M_color);
        __new->_M_setcolor(__n->_M_color);
        _tree_rotate_left(__n, __h);
    }



    static inline void
    _rbt_rotate_right(_Rbt_node_base *__n,
                      _Rbt_node_base *__h) ustl_cpp_noexcept
    {
        _Rbt_node_base *__new = __n->left();
        __new->left()->_M_setcolor(__new->_M_color);
        __new->_M_setcolor(__n->_M_color);
        _tree_rotate_right(__n, __h);
    }


}

#endif