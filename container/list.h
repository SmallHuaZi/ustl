#ifndef __List_h
#define __list_h

#include "ustl.h"

namespace ustl
{
    struct _list_node_basic
    {
        using _base_ptr = struct _list_node_basic *;

        _base_ptr _M_pre;
        _base_ptr _M_suc;

        void
        _M_move(_list_node_basic &__l)
        {
            _M_pre = __l._M_pre;
            _M_suc = __l._M_suc;
        }

        void
        _M_swap(_list_node_basic &__l)
        {
            _list_node_basic __tmp = *this;
            _M_move(__l);
            __l._M_move(__tmp);
        }
    };

    struct _list_header
        : _list_node_basic
    {
        size_t _M_count;

        void
        _M_reset()
        {
            _M_count = 0;
            _M_pre = _M_suc = 0;
        }

        _base_ptr
        _M_last() { return _M_suc; }

        _base_ptr
        _M_first() { return _M_pre; }
    };

    template <typename _Tp>
    struct _list_node
        : _list_node_basic
    {
        typedef _Tp vlaue_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;

        pointer
        _M_valptr() { return &_M_val; }

        reference
        _M_value() { return _M_val; }

        void
        _M_move(_list_node const &__n)
        {
            _M_val = __n._M_val;
            _M_pre = _M_pre;
            _M_suc = _M_suc;
        }

        void
        _M_swap(_list_node &__n)
        {
            _list_node __tmp = __n;
            __n._M_move(*this);
            _M_move(__tmp);
        }

        vlaue_type _M_val;
    };

    template <typename _Tp>
    struct _list_iterator
    {
        typedef _Tp vlaue_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef diff_t difference_type;

        typedef _list_node<_Tp> *_node_ptr;
        typedef _list_node_basic *_base_ptr;
        typedef _list_iterator _Self;

        pointer
        operator->()
        {
            return static_cast<_node_ptr>(_M_node)->_M_valptr();
        }

        reference
        operator*()
        {
            return *static_cast<_node_ptr>(_M_node)->_M_valptr();
        }

        _Self
        operator++()
        {
            _M_node = _M_node->_M_suc;
            return _Self(_M_node);
        }

        _Self
        operator--()
        {
            _M_node = _M_node->_M_pre;
            return _Self(_M_node);
        }

        _Self
        operator++(int)
        {
            _base_ptr __tmp = _M_node;
            _M_node = _M_node->_M_suc;
            return __tmp;
        }

        _Self
        operator--(int)
        {
            _base_ptr __tmp = _M_node;
            _M_node = _M_node->_M_pre;
            return __tmp;
        }

        friend bool
        operator==(_Self __l, _Self __r)
        {
            return __l._M_node == __r._M_node;
        }

        friend bool
        operator!=(_Self __l, _Self __r)
        {
            return __l._M_node != __r._M_node;
        }

        _list_iterator() = default;

        _list_iterator(_base_ptr __p)
            : _M_node(__p) {}

        _base_ptr _M_node;
    };

    template <typename _Tp>
    struct _list_const_iterator
    {
        typedef _Tp vlaue_type;
        typedef _Tp const *pointer;
        typedef _Tp const &reference;
        typedef diff_t difference_type;

        typedef _list_node<_Tp> *_node_ptr;
        typedef _list_node_basic *_base_ptr;
        typedef _list_const_iterator _Self;

        pointer
        operator->()
        {
            return static_cast<_node_ptr>(_M_node)->_M_valptr();
        }

        reference
        operator*()
        {
            return *static_cast<_node_ptr>(_M_node)->_M_valptr();
        }

        _Self
        operator++()
        {
            _M_node = _M_node->_M_suc;
            return _Self(_M_node);
        }

        _Self
        operator--()
        {
            _M_node = _M_node->_M_pre;
            return _Self(_M_node);
        }

        _Self
        operator++(int)
        {
            _base_ptr __tmp = _M_node;
            _M_node = _M_node->_M_suc;
            return __tmp;
        }

        _Self
        operator--(int)
        {
            _base_ptr __tmp = _M_node;
            _M_node = _M_node->_M_pre;
            return __tmp;
        }

        friend bool
        operator==(_Self __l, _Self __r)
        {
            return __l._M_node == __r._M_node;
        }

        friend bool
        operator!=(_Self __l, _Self __r)
        {
            return __l._M_node != __r._M_node;
        }

        _list_const_iterator() = default;

        _list_const_iterator(_base_ptr __p)
            : _M_node(__p) {}

        _base_ptr _M_node;
    };

    template <typename _Tp, typename _Alloc = ustl::allocator<_Tp>>
    class list
    {
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;

        typedef _list_iterator<_Tp> iterator;
        typedef _list_const_iterator<_Tp> const_iterator;
        typedef diff_t difference_type;

    public:
        iterator
            insert(iterator);
        iterator
        insert(value_type const &);
        iterator
        push_back(value_type const &);
        iterator
        push_front(value_type const &);

        template <typename... _Args>
        iterator
        emplace(iterator, _Args &&...);

        template <typename... _Args>
        iterator
        emplace_back(_Args &&...);

        template <typename... _Args>
        iterator
        emplace_front(_Args &&...);

        template <typename _Itr>
        void assgin(_Itr, _Itr);

        iterator
        remove(value_type const &);
        iterator
            remove_if(/**condition*/);
        iterator
        pop_back();
        iterator
        pop_front();

        iterator
        erase(value_type const &);
        iterator
        erase(iterator const &);

        void
        clear();

        void
        unique();

        iterator
        begin();

        iterator
        end();

        const_iterator
        cbegin();

        const_iterator
        cend();

        size_t
        size();
    };

}

#endif