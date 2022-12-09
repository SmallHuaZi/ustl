#ifndef __rbt_fwd_h
#define __rbt_fwd_h

#include "include/config.h"
#include "container/tree_basic.h"

#define _r_is_red(__ptr) \
    (__ptr != 0 && _Red == _Rbt_node_base::_S_color(__ptr->right()))

#define _l_is_red(__ptr) \
    (__ptr != 0 && _Red == _Rbt_node_base::_S_color(__ptr->left()))

#define _rbt_bro_ptr(__ptr) \
    (__ptr == __ptr->_M_parent->_M_left ? __ptr->parent()->right(): __ptr->parent()->left())

#define _is_rchild(__ptr) \
    (__ptr == __ptr->_M_parent->_M_right)

#define _is_lchild(__ptr) \
    (__ptr == __ptr->_M_parent->_M_left)

namespace ustl
{
    enum _color : unsigned long
    {
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


        static _color
        _S_color(_Rbt_node_base *__p) ustl_cpp_noexcept;


        void
        _M_setcolor(_color __c) ustl_cpp_noexcept;


        static _Node_ptr
        maxnode(_Node_ptr __r) ustl_cpp_noexcept;


        static _CNode_ptr
        maxnode(_CNode_ptr __r) ustl_cpp_noexcept;


        static _Node_ptr
        minnode(_Node_ptr __r) ustl_cpp_noexcept;


        static _CNode_ptr
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

    inline _Rbt_node_base *
    _rbt_decrement(_Rbt_node_base *__p) ustl_cpp_noexcept;

    inline _Rbt_node_base *
    _rbt_increment(_Rbt_node_base *__p) ustl_cpp_noexcept;

    _Rbt_node_base *
    _rbt_erase(_Rbt_node_base *__del,
               _Rbt_node_base *__h) ustl_cpp_noexcept;

    void
    _rbt_insert(bool __is_l,
                _Rbt_node_base *__new,
                _Rbt_node_base *__ist,
                _Rbt_node_base *__header) ustl_cpp_noexcept;

    void
    _rbt_recolor(_Rbt_node_base *__n,
                 _Rbt_node_base *__h) ustl_cpp_noexcept;

    void
    _rbt_rotate_left(_Rbt_node_base *__n,
                     _Rbt_node_base *__h) ustl_cpp_noexcept;

    void
    _rbt_rotate_right(_Rbt_node_base *__n,
                      _Rbt_node_base *__h) ustl_cpp_noexcept;

    void
    _rbt_rebalance_insert(_Rbt_node_base *__n,
                          _Rbt_node_base *__h) ustl_cpp_noexcept;

    void
    _rbt_rebalance_erase(_Rbt_node_base *__n,
                         _Rbt_node_base *__h) ustl_cpp_noexcept;

}
#endif