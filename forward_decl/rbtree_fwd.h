#ifndef __rbt_fwd_h
#define __rbt_fwd_h

#define _r_is_red(__ptr) \
    (__ptr != 0 && _Red == _Rbt_node_base::_S_color(__ptr->_M_right))

#define _l_is_red(__ptr) \
    (__ptr != 0 && _Red == _Rbt_node_base::_S_color(__ptr->_M_left))

#define _rbt_bro_ptr(__ptr) \
    (__ptr == __ptr->_M_parent->_M_left ? __ptr->_M_parent->_M_right : __ptr->_M_parent->_M_left)

#define _is_rchild(__ptr) \
    (__ptr == __ptr->_M_parent->_M_right)

#define _is_lchild(__ptr) \
    (__ptr == __ptr->_M_parent->_M_left)

#include "ustl.h"

namespace ustl
{
    namespace internal_ustl
    {
        enum _color : unsigned long
        {
            _Black,
            _Red
        };

        struct _Rbt_node_base
        {
            using _Node_color = _color;
            using _Node_ptr = _Rbt_node_base *;
            using _CNode_ptr = const _Rbt_node_base *;
            /**
             * take typedef or using to cover function overload
             */

            _Node_color _M_color;
            _Node_ptr _M_parent;
            _Node_ptr _M_left;
            _Node_ptr _M_right;

#ifdef __debug_ustl
            int _M_value;
#endif

            _Rbt_node_base()
                : _M_color(_Red)
            {
            }

            _Rbt_node_base(_Node_ptr __p)
                : _M_parent(__p) {}

            _Rbt_node_base(_Node_ptr __l,
                           _Node_ptr __r, _Node_ptr __p)
                : _M_color(_Red), _M_left(__l),
                  _M_right(__r), _M_parent(__p) {}

            static _color
            _S_color(_Rbt_node_base *__p) noexcept
            {
                return __p ? __p->_M_color : _Black;
            }

            void
            _M_setcolor(_color __c) noexcept
            {
                if (this)
                    this->_M_color = __c;
            }

            static _Node_ptr
            maxnode(_Node_ptr __r) noexcept
            {
                while (__r->_M_right)
                    __r = __r->_M_right;
                return __r;
            }

            static _CNode_ptr
            maxnode(_CNode_ptr __r) noexcept
            {
                while (__r->_M_right)
                    __r = __r->_M_right;
                return __r;
            }

            static _Node_ptr
            minnode(_Node_ptr __r) noexcept
            {
                while (__r->_M_left)
                    __r = __r->_M_left;
                return __r;
            }

            static _CNode_ptr
            minnode(_CNode_ptr __r) noexcept
            {
                while (__r->_M_left)
                    __r = __r->_M_left;
                return __r;
            }
        };

        struct _Rbt_header
            : _Rbt_node_base
        {
            size_t _M_count;

            _Rbt_header()
                : _M_count(0),
                  _Rbt_node_base(this, this, 0) {}

            _Rbt_header(_Node_ptr __l,
                        _Node_ptr __r, _Node_ptr __p, size_t __n)
                : _M_count(__n), _Rbt_node_base(__l, __r, __p) {}

            void _M_reset() noexcept
            {
                _M_count = 0;
                _M_parent = _M_left = _M_right = this;
            }

            _Node_ptr
            _S_Min_node() const noexcept
            {
                return this->_M_left;
            }

            _Node_ptr
            _S_Max_node() const noexcept
            {
                return this->_M_right;
            }
        };

        _Rbt_node_base *
        _rbt_decrement(_Rbt_node_base *__p) noexcept;

        _Rbt_node_base *
        _rbt_increment(_Rbt_node_base *__p) noexcept;

        _Rbt_node_base *
        _rbt_erase(_Rbt_node_base *__del,
                   _Rbt_node_base *__h) noexcept;

        void
        _rbt_insert(bool __is_l,
                    _Rbt_node_base *__new,
                    _Rbt_node_base *__ist,
                    _Rbt_node_base *__header) noexcept;

        void
        _rbt_recolor(_Rbt_node_base *__n,
                     _Rbt_node_base *__h) noexcept;

        void
        _rbt_rotate_left(_Rbt_node_base *__n,
                         _Rbt_node_base *__h) noexcept;

        void
        _rbt_rotate_right(_Rbt_node_base *__n,
                          _Rbt_node_base *__h) noexcept;

        void
        _rbt_rebalance_insert(_Rbt_node_base *__n,
                              _Rbt_node_base *__h) noexcept;

        void
        _rbt_rebalance_erase(_Rbt_node_base *__n,
                             _Rbt_node_base *__h) noexcept;

    }

}
#endif