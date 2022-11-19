#ifndef __List_h
#define __list_h

namespace ustl
{
    /**
     * @brief ring list
     *              header
     *        suc          pre
     *        /\            /\
     *       /                \
     *     /                    \
     *   /                        \
     *  \/                        \/
     *  A <----> B <----> C <----> D
     */
    struct _list_node_basic
    {
        using _base_ptr = struct _list_node_basic *;

        void
        _M_move(_list_node_basic &__l) ustl_cpp_noexcept
        {
            _M_pre = __l._M_pre;
            _M_suc = __l._M_suc;
        }

        void
        _M_swap(_list_node_basic &__l) ustl_cpp_noexcept
        {
            _list_node_basic __tmp = *this;
            _M_move(__l);
            __l._M_move(__tmp);
        }

        void
        _M_reset() ustl_cpp_noexcept
        {
            _M_pre = _M_suc = this;
        }

        /* insert before this */
        void
        _M_hook(_base_ptr const __p) ustl_cpp_noexcept
        {
            _M_pre->_M_suc = __p;
            __p->_M_pre = _M_pre;
            _M_pre = __p;
            __p->_M_suc = this;
        }

        void
        _M_unhook() ustl_cpp_noexcept
        {
            _M_pre->_M_suc = _M_suc;
            _M_suc->_M_pre = _M_pre;
            _M_reset();
        }

        void
        _M_transer(_base_ptr __first,
                   _base_ptr __last) ustl_cpp_noexcept
        {
            /**
             * insert before this
             * [__first, __last)
             *
             * [__first, __lpre]
             *
             * (__fpre,  __last)
             *
             */
            _base_ptr const __lpre = __last->_M_pre;
            _base_ptr const __fpre = __first->_M_pre;

            __fpre->_M_suc = __last;
            __last->_M_pre = __fpre;

            __first->_M_pre = _M_pre;
            _M_pre->_M_suc = __first;

            _M_pre = __lpre;
            __lpre->_M_suc = this;
        }

        _list_node_basic()
            : _M_pre(this), _M_suc(this) {}

        _base_ptr _M_pre;
        _base_ptr _M_suc;

#ifdef __debug_ustl

        _list_node_basic(int __a)
            : _list_node_basic()
        {
            _M_value_field = __a;
        }

        int _M_value_field;
#endif
    };

    struct _list_header
        : _list_node_basic
    {
        void
        _M_reset() ustl_cpp_noexcept
        {
            _M_count = 0;
            _M_pre = _M_suc = this;
        }

        void
        _M_inc_size(int __n) ustl_cpp_noexcept
        {
            _M_count += __n;
        };

        void
        _M_dec_size(int __n) ustl_cpp_noexcept
        {
            _M_count -= __n;
        }

        _base_ptr
        _M_last() const ustl_cpp_noexcept
        {
            return _M_pre;
        }

        _base_ptr
        _M_first() const ustl_cpp_noexcept
        {
            return _M_suc;
        }

        void
        _M_swap(_list_header &__h) ustl_cpp_noexcept
        {
            _list_header __tmp = __h;
            __h._M_move(*this);
            _M_move(__tmp);
        }

        void
        _M_move(_list_header &__h) ustl_cpp_noexcept
        {
            _M_pre = __h._M_pre;
            _M_suc = __h._M_suc;
            _M_count = __h._M_count;
        }

        _list_header()
            : _list_node_basic() {}

        size_t _M_count;
    };

    template <typename _Tp>
    struct _list_node
        : _list_node_basic
    {
#ifdef __debug_ustl
        typedef int value_type;
#else
        typedef _Tp value_type;
#endif
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _list_node_basic base_type;

        pointer
        _M_valptr() ustl_cpp_noexcept
        {
            return &_M_value_field;
        }

        reference
        _M_value() ustl_cpp_noexcept
        {
            return _M_value_field;
        }

        void
        _M_move(_list_node const &__n) ustl_cpp_noexcept
        {
            base_type::_M_move(__n);
            _M_value_field = __n._M_value_field;
        }

        void
        _M_swap(_list_node &__n) ustl_cpp_noexcept
        {
            _list_node __tmp = __n;
            __n._M_move(*this);
            _M_move(__tmp);
        }

        _list_node()
            : _list_node_basic() {}

#ifndef __debug_ustl

        _list_node(value_type const &__v)
            : _M_value_field(__v), _list_node()
        {
        }

        value_type _M_value_field;
#else
        _list_node(value_type const &__v)
            : _list_node(__v)
        {
        }
#endif
    };

    template <typename _Tp>
    struct _list_iterator
    {
        typedef _Tp vlaue_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef diff_t difference_type;

        typedef _bothway_itertor itr_tag;
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
        operator++() ustl_cpp_noexcept
        {
            _M_node = _M_node->_M_suc;
            return _Self(_M_node);
        }

        _Self
        operator--() ustl_cpp_noexcept
        {
            _M_node = _M_node->_M_pre;
            return _Self(_M_node);
        }

        _Self
        operator++(int) ustl_cpp_noexcept
        {
            _base_ptr __tmp = _M_node;
            _M_node = _M_node->_M_suc;
            return _Self(__tmp);
        }

        _Self
        operator--(int) ustl_cpp_noexcept
        {
            _base_ptr __tmp = _M_node;
            _M_node = _M_node->_M_pre;
            return _Self(__tmp);
        }

        friend bool
        operator==(_Self __l, _Self __r) ustl_cpp_noexcept
        {
            return __l._M_node == __r._M_node;
        }

        friend bool
        operator!=(_Self __l, _Self __r) ustl_cpp_noexcept
        {
            return __l._M_node != __r._M_node;
        }

        _list_iterator() = default;

        explicit _list_iterator(_base_ptr __p)
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

        typedef _bothway_itertor itr_tag;
        typedef _list_node<_Tp> *_node_ptr;
        typedef _list_node_basic *_base_ptr;
        typedef _list_const_iterator _Self;

        pointer
        operator->() ustl_cpp_noexcept
        {
            return static_cast<_node_ptr>(_M_node)->_M_valptr();
        }

        reference
        operator*() ustl_cpp_noexcept
        {
            return *static_cast<_node_ptr>(_M_node)->_M_valptr();
        }

        _Self
        operator++() ustl_cpp_noexcept
        {
            _M_node = _M_node->_M_suc;
            return _Self(_M_node);
        }

        _Self
        operator--() ustl_cpp_noexcept
        {
            _M_node = _M_node->_M_pre;
            return _Self(_M_node);
        }

        _Self
        operator++(int) ustl_cpp_noexcept
        {
            _base_ptr __tmp = _M_node;
            _M_node = _M_node->_M_suc;
            return __tmp;
        }

        _Self
        operator--(int) ustl_cpp_noexcept
        {
            _base_ptr __tmp = _M_node;
            _M_node = _M_node->_M_pre;
            return __tmp;
        }

        friend bool
        operator==(_Self __l, _Self __r) ustl_cpp_noexcept
        {
            return __l._M_node == __r._M_node;
        }

        friend bool
        operator!=(_Self __l, _Self __r) ustl_cpp_noexcept
        {
            return __l._M_node != __r._M_node;
        }

        _list_const_iterator() = default;

        explicit _list_const_iterator(_base_ptr __p)
            : _M_node(__p) {}

        explicit _list_const_iterator(_list_iterator<_Tp> __itr)
            : _M_node(__itr._M_node) {}

        _base_ptr _M_node;
    };

    template <typename _Tp, typename _Alloc>
    struct _list_impl
        : allocate_traits<_Alloc>::
              template rebind<_list_node<_Tp>>::other
    {
        void
        _M_swap(_list_impl &__other) ustl_cpp_noexcept
        {
            _M_header._M_swap(__other._M_header);
        }

        void
        _M_reset() ustl_cpp_noexcept
        {
            _M_header._M_reset();
        }

        _list_impl() = default;

        _list_impl(size_t __c, _list_node_basic *__h,
                   _list_node_basic *__e)
        {
            _M_header._M_count = __c;
            _M_header._M_pre = __h;
            _M_header._M_suc = __e;
        }

        _list_header _M_header;
    };

    /**
     *
     *
     */
    template <typename _Tp, typename _Alloc = ustl::allocator<_Tp>>
    class list
    {
    public:
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;
        typedef diff_t difference_type;
        typedef size_t size_type;

        typedef _list_iterator<_Tp> iterator;
        typedef _list_const_iterator<_Tp> const_iterator;

        typedef _list_node<_Tp> node_type;
        typedef _list_node_basic *base_ptr;
        typedef _list_node<_Tp> *node_ptr;

        typedef _Alloc allocator_type;
        typedef typename allocate_traits<allocator_type>::
            template rebind<node_type>::other _Node_allocator_type;

        typedef allocate_traits<allocator_type> _Tp_allocator_traits;
        typedef allocate_traits<_Node_allocator_type> _NAlloc_traits;

        typedef _list_impl<_Tp, _Alloc> impl_type;

    private:
        /**
         * _M_begin and _M_end
         * header to tail
         */
        iterator
        _M_begin() ustl_cpp_noexcept
        {
            return iterator(&_M_data_plus->_M_header);
        }

        iterator
        _M_end() ustl_cpp_noexcept
        {
            return iterator(_M_data_plus->_M_header._M_last());
        }

        _Node_allocator_type &
        _M_get_node_allocator() ustl_cpp_noexcept
        {
            return *_M_data_plus;
        }

        node_ptr
        _M_get_node()
        {
            node_ptr __ret = _NAlloc_traits::
                allocate(_M_get_node_allocator(), 1);
#ifdef __debug_ustl

            _NAlloc_traits::construct(_M_get_node_allocator(),
                                      __ret);

#endif
            return __ret;
        }
        void
        _M_put_node(base_ptr __p)
        {
            _NAlloc_traits::
                deallocate(_M_get_node_allocator(), __p, 1);
        }

        void
        _M_transer(iterator __pos,
                   iterator __first,
                   iterator __last) ustl_cpp_noexcept
        {
            __pos._M_node->_M_transer(__first._M_node, __last._M_node);
        }

        size_t
        _M_distance(iterator __first,
                    iterator __last) ustl_cpp_noexcept
        {
            size_t __dis = 0;
            while (__first++ != __last)
                ++__dis;
            return __dis;
        }

        template <typename... _Args>
        node_ptr
        _M_create_node(_Args &&...__args)
        {
            node_ptr __ret = _M_get_node();
            _NAlloc_traits::construct(_M_get_node_allocator(),
                                      __ret->_M_valptr(), forward<_Args>(__args)...);
            return __ret;
        }

        void
        _M_set_size(size_t __n) ustl_cpp_noexcept
        {
            _M_data_plus->_M_header._M_count = __n;
        }

        void
        _M_default_append(size_t __n)
        {
            size_t __i = 0;
            while (__i++ < __n)
                emplace_back();
        }

        void
        _M_fill(size_t __n, value_type const &__val)
        {
            for (; __n != 0; --__n)
                push_back(__val);
        }

        template <typename _Itr>
        void
        _M_fill(_Itr __first, _Itr __last)
        {
            for (; __first != __last; ++__first)
                emplace_back(*__first);
        }

        template <typename _Itr>
        void _M_fill_assign(iterator __pos,
                            _Itr __first, _Itr __last)
        {
            iterator __first2 = __pos;
            iterator __last2 = end();
            while (__first != __last && __first2 != __last2)
            {
                *__first2 = *__first;
                ++__first, ++__first2;
            }
            if (__first2 != __last2)
                erase(__first2, __last2);
            if (__first != __last)
                _M_fill(__first, __last);
        }

        template <typename... _Args>
        iterator _M_insert(iterator, _Args &&...);

        template <typename... _Args>
        size_t _M_insert(iterator, size_t, _Args &&...);

        void _M_erase(iterator);
        void _M_erase(iterator, iterator);

    public:
        inline size_t insert(iterator, iterator, iterator);
        inline iterator insert(const_iterator, value_type const &);
        inline iterator insert(const_iterator, value_type const &, size_t);

        inline void push_back(value_type const &);
        inline void push_back(iterator);
        inline void push_front(value_type const &);
        inline void push_front(iterator);

        template <typename... _Args>
        inline reference emplace(const_iterator, _Args &&...);
        template <typename... _Args>
        inline reference emplace_back(_Args &&...);
        template <typename... _Args>
        inline reference emplace_front(_Args &&...);

        template <typename _Itr>
        inline void assign(_Itr, _Itr);
        template <typename _Itr>
        inline void assign(iterator, _Itr, _Itr);

        inline reference front() ustl_cpp_noexcept;
        inline reference back() ustl_cpp_noexcept;

        size_t remove(value_type const &);
        template <typename _CompPredicate>
        size_t remove_if(_CompPredicate);

        inline void pop_back();
        inline void pop_front();

        inline void erase(iterator);
        inline size_t erase(iterator, iterator);

        void unique();
        template <typename _Predicate>
        void unique(_Predicate);

        void merge(list &&) ustl_cpp_noexcept;
        void merge(list &) ustl_cpp_noexcept;
        template <typename _CompPredicate>
        void merge(list &&, _CompPredicate);
        template <typename _CompPredicate>
        void merge(list &, _CompPredicate);

        void splice(iterator, list &, iterator);
        void splice(iterator, list &, iterator, iterator);

        void sort();
        template <typename _CompPredicate>
        void sort(_CompPredicate);

        void swap(list &__l);
        void swap(list &&__l);

        void reverse() ustl_cpp_noexcept;

        void resize(size_t);
        void resize(size_t, value_type const &);

        void clear();

        inline iterator begin() ustl_cpp_noexcept;
        inline iterator end() ustl_cpp_noexcept;
        inline const_iterator begin() const ustl_cpp_noexcept;
        inline const_iterator end() const ustl_cpp_noexcept;

        inline const_iterator cbegin() ustl_cpp_noexcept;
        inline const_iterator cend() ustl_cpp_noexcept;
        inline const_iterator cbegin() const ustl_cpp_noexcept;
        inline const_iterator cend() const ustl_cpp_noexcept;

        inline size_t size() const ustl_cpp_noexcept;

        inline bool empty() const ustl_cpp_noexcept;

        list &operator=(list const &);
        list &operator=(list &&);

    public:
        template <typename _Alloc_Impl = ustl::allocator<impl_type>>
        list()
            : _M_data_plus(_Alloc_Impl().allocate(1))
        {
            _Alloc_Impl().construct(_M_data_plus);
        }

        template <typename _Alloc_Impl>
        list(_Alloc_Impl &&__alloc)
            : _M_data_plus(__alloc.allocate(1))
        {
            __alloc.construct(_M_data_plus);
        }

        list(list const &__other)
        {
            if (&__other != this)
                assign(__other.begin(), __other.end());
        }

        list(list &&__other)
        {
            if (&__other == this)
                return;
            clear();
            swap(__other);
        }

        template <typename _InputItr>
        list(_InputItr __first, _InputItr __last)
        {
            _M_fill(__first, __last);
        }

        ~list() ustl_cpp_noexcept
        {
            clear();
        }

    private:
        impl_type *_M_data_plus;
    };

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    typename list<_Tp, _Alloc>::iterator
    list<_Tp, _Alloc>::
        _M_insert(iterator __pos,
                  _Args &&...__a)
    {
        base_ptr __new = _M_create_node(forward<_Args &&>(__a)...);
        __pos._M_node->_M_hook(__new);
        _M_data_plus->_M_header._M_inc_size(1);
        return iterator(__new);
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    size_t
    list<_Tp, _Alloc>::
        _M_insert(iterator __pos,
                  size_t __n,
                  _Args &&...__a)
    {
        if (0 == __n)
            return 0;
        while (__n--)
            _M_insert(__pos, forward<_Args &&>(__a)...);
        _M_data_plus->_M_header._M_inc_size(__n);
        return __n;
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        _M_erase(iterator __pos)
    {
        __pos._M_node->_M_unhook();
        _M_data_plus->_M_header._M_dec_size(1);
        _M_put_node(__pos._M_node);
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        _M_erase(iterator __first,
                 iterator __last)
    {
        for (; __first != __last; ++__first)
            _M_erase(__first);
    }

    template <typename _Tp, typename _Alloc>
    typename list<_Tp, _Alloc>::iterator
    list<_Tp, _Alloc>::
        insert(const_iterator __itr,
               value_type const &__val)
    {
        return _M_insert(__itr, forward(__val));
    }

    template <typename _Tp, typename _Alloc>
    typename list<_Tp, _Alloc>::iterator
    list<_Tp, _Alloc>::
        insert(const_iterator __itr,
               value_type const &__val,
               size_t __count)
    {
        iterator __ret = end();
        while (__count--)
            __ret = _M_insert(__itr, __val);
        return __ret;
    }

    template <typename _Tp, typename _Alloc>
    size_t
    list<_Tp, _Alloc>::
        insert(iterator __pos,
               iterator __first,
               iterator __last)
    {
        size_t __counter = _M_distance(__first, __last);
        _M_transer(__pos, __first, __last);
        return __counter;
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        push_back(value_type const &__val)
    {
        _M_insert(end(), forward(__val));
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        push_back(iterator __itr)
    {
        _M_insert(end(), *__itr);
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        push_front(value_type const &__val)
    {
        _M_insert(begin(), __val);
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        push_front(iterator __itr)
    {
        _M_insert(begin(), *__itr);
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    typename list<_Tp, _Alloc>::reference
    list<_Tp, _Alloc>::
        emplace(const_iterator __pos,
                _Args &&...__args)
    {
        return *_M_insert(__pos, forward<_Args>(__args)...);
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    typename list<_Tp, _Alloc>::reference
    list<_Tp, _Alloc>::
        emplace_front(_Args &&...__args)
    {
        return *_M_insert(begin(), forward<_Args>(__args)...);
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    typename list<_Tp, _Alloc>::reference
    list<_Tp, _Alloc>::
        emplace_back(_Args &&...__args)
    {
        return *_M_insert(end(), forward<_Args>(__args)...);
    }

    template <typename _Tp, typename _Alloc>
    template <typename _Itr>
    void
    list<_Tp, _Alloc>::
        assign(_Itr __first, _Itr __last)
    {
        _M_fill_assign(begin(), __first, __last);
    }

    template <typename _Tp, typename _Alloc>
    template <typename _Itr>
    void
    list<_Tp, _Alloc>::
        assign(iterator __pos,
               _Itr __first, _Itr __last)
    {
        _M_fill_assign(__pos, __first, __last);
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        pop_front()
    {
        _M_erase(begin());
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        pop_back()
    {
        _M_erase(_M_end());
    }

    template <typename _Tp, typename _Alloc>
    size_t
    list<_Tp, _Alloc>::
        remove(value_type const &__val)
    {
        iterator __tmp;
        iterator __begin = begin();
        iterator __end = end();
        while (__begin != __end)
        {
            __tmp = __begin;
            ++__begin;
            if (*__tmp == __val)
                _M_erase(__tmp);
        }
        return size();
    }

    template <typename _Tp, typename _Alloc>
    template <typename _CompPredicate>
    size_t
    list<_Tp, _Alloc>::
        remove_if(_CompPredicate __pred)
    {
        size_t __oldsize = size();
        iterator __tmp;
        iterator __begin = begin();
        iterator __end = end();
        while (__begin != __end)
        {
            __tmp = __begin;
            ++__begin;
            if (__pred(*__tmp))
                _M_erase(__tmp);
        }
        return __oldsize - size();
    }

    template <typename _Tp, typename _Alloc>
    inline void
    list<_Tp, _Alloc>::
        erase(iterator __pos)
    {
        _M_erase(__pos);
    }

    template <typename _Tp, typename _Alloc>
    inline size_t
    list<_Tp, _Alloc>::
        erase(iterator __first, iterator __last)
    {
        size_t __dis = _M_distance(__first, __last);
        _M_erase(__first, __last);
        return __dis;
    }
    /**
     * @brief removes all duplicate consecutive elements
     */
    template <typename _Tp, typename _Alloc>
    void list<_Tp, _Alloc>::
        unique()
    {
        iterator __begin = begin();
        iterator __end = end();
        iterator __next = __begin;
        while (++__next != __end)
        {
            if (*__begin == *__next)
                _M_erase(__next);
            else
                __begin = __next;
            __next = __begin;
        }
    }

    template <typename _Tp, typename _Alloc>
    template <typename _Predicate>
    void list<_Tp, _Alloc>::
        unique(_Predicate __pred)
    {
        iterator __begin = begin();
        iterator __end = end();
        iterator __next = __begin;
        while (++__next != __end)
        {
            if (__pred(*__begin, *__next))
                _M_erase(__next);
            else
                __begin = __next;
            __next = __begin;
        }
    }

    template <typename _Tp, typename _Alloc>
    inline void
    list<_Tp, _Alloc>::
        merge(list &&__l) ustl_cpp_noexcept
    {
        merge(__l);
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        merge(list &__l) ustl_cpp_noexcept
    {
        if (&__l == this)
            return;
        iterator __first = begin();
        iterator __last = end();
        iterator __first2 = __l.begin();
        iterator __last2 = __l.end();
        iterator __next;
        while (__first2 != __last2 && __first != __last)
        {
            if (*__first < *__first2)
                __first++;
            else
            {
                __next = __first2;
                _M_transer(__first, __first2, ++__next);
                __first2 = __next;
            }
        }
        if (__first2 != __last2)
            _M_transer(__first, __first2, __last2);
        _M_data_plus->_M_header._M_inc_size(__l.size());
        __l._M_set_size(0);
    }

    template <typename _Tp, typename _Alloc>
    template <typename _CompPredicate>
    void
    list<_Tp, _Alloc>::
        merge(list &__l, _CompPredicate __comp)
    {
        if (&__l == this)
            return;
        iterator __first = begin();
        iterator __last = end();
        iterator __first2 = __l.begin();
        iterator __last2 = __l.end();
        iterator __next;
        while (__first2 != __last2 &&
               __first != __last)
        {
            if (__comp(*__first, *__first2))
                ++__first;
            else
            {
                __next = __first2;
                _M_transer(__first, __first2, ++__next);
                __first2 = __next;
            }
        }
        if (__first2 != __last2)
            _M_transer(__first, __first2, __last2);
        _M_data_plus->_M_header._M_inc_size(__l.size());
        __l._M_set_size(0);
    }
    template <typename _Tp, typename _Alloc>
    template <typename _CompPredicate>
    void
    list<_Tp, _Alloc>::
        merge(list &&__l, _CompPredicate __comp)
    {
        merge(__l, __comp);
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        splice(iterator __pos,
               list &__l,
               iterator __first)
    {
        if (this == &__l)
            return;
        iterator __tmp = __first;
        _M_transer(__pos, __first, ++__tmp);
        _M_data_plus->_M_header._M_inc_size(1);
        __l._M_data_plus->_M_header._M_dec_size(1);
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        splice(iterator __pos, list &__l,
               iterator __first, iterator __last)
    {
        if (this == &__l)
            return;
        size_t __dis = _M_distance(__first, __last);
        _M_transer(__pos, __first, __last);
        _M_data_plus->_M_header._M_inc_size(__dis);
        __l._M_data_plus->_M_header._M_dec_size(__dis);
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        sort()
    {
        if (size() <= 1UL)
            return;
        list __tmp;
        list __tmps[sizeof(ustl::size_t) << 3];
        size_t __fill = 0;
        size_t __counter;
        do
        {
            __tmp.splice(__tmp.begin(), *this, begin());

            for (__counter = 0;
                 __counter != __fill && __tmps[__counter].size();
                 ++__counter)
                __tmp.merge(__tmps[__counter]);
            __tmp.swap(__tmps[__counter]);
            if (__counter == __fill)
                ++__fill;
        } while (size());

        for (__counter = 0; __counter != __fill; ++__counter)
            __tmp.merge(__tmps[__counter]);
        swap(__tmp);
    }

    template <typename _Tp, typename _Alloc>
    template <typename _CompPredicate>
    void
    list<_Tp, _Alloc>::
        sort(_CompPredicate __pred)
    {
        if (size() <= 1)
            return;
        list __tmp;
        list __tmps[sizeof(ustl::size_t) << 3];
        size_t __fill = 0;
        size_t __counter;
        do
        {
            __tmp.splice(__tmp.begin(), *this, begin());

            for (__counter = 0;
                 __counter != __fill && __tmps[__counter].size();
                 ++__counter)
                __tmp.merge(__tmps[__counter], __pred);
            __tmp.swap(__tmps[__counter]);
            if (__counter == __fill)
                ++__fill;
        } while (size());

        for (__counter = 0; __counter != __fill; ++__counter)
            __tmp.merge(__tmps[__counter], __pred);
        swap(__tmp);
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        swap(list &__l)
    {
        _M_data_plus->_M_swap(__l._M_data_plus);
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        swap(list &&__l)
    {
        _M_data_plus->_M_swap(__l._M_data_plus);
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        resize(size_t __s)
    {
        if (__s > size())
            _M_default_append(__s - size());
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        resize(size_t __s, value_type const &__def_val)
    {
        if (__s > size())
            _M_fill(__s - size(), __def_val);
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        reverse() ustl_cpp_noexcept
    {
        if (size() <= 1)
            return;
        iterator __first = begin();
        iterator __last = end();
        --__last;
        while (__first != __last)
        {
            iterator __tmp = __last;
            --__last;
            __tmp._M_node->_M_unhook();
            __first._M_node->_M_hook(__tmp._M_node);
        }
    }

    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        clear()
    {
        iterator __first = begin();
        iterator __last = end();
        iterator __tmp;
        while (__first != __last)
        {
            __tmp = __first++;
            _M_erase(__tmp);
        }
        _M_data_plus->_M_reset();
    }

    template <typename _Tp, typename _Alloc>
    typename list<_Tp, _Alloc>::iterator
    list<_Tp, _Alloc>::
        begin() ustl_cpp_noexcept
    {
        return iterator(_M_data_plus->_M_header._M_first());
    }

    template <typename _Tp, typename _Alloc>
    typename list<_Tp, _Alloc>::iterator
    list<_Tp, _Alloc>::
        end() ustl_cpp_noexcept
    {
        return iterator(&_M_data_plus->_M_header);
    }

    template <typename _Tp, typename _Alloc>
    typename list<_Tp, _Alloc>::const_iterator
    list<_Tp, _Alloc>::
        begin() const ustl_cpp_noexcept
    {
        return const_iterator(_M_data_plus->_M_header._M_first());
    }

    template <typename _Tp, typename _Alloc>
    typename list<_Tp, _Alloc>::const_iterator
    list<_Tp, _Alloc>::
        end() const ustl_cpp_noexcept
    {
        return const_iterator(&_M_data_plus->_M_header);
    }

    template <typename _Tp, typename _Alloc>
    typename list<_Tp, _Alloc>::const_iterator
    list<_Tp, _Alloc>::
        cbegin() ustl_cpp_noexcept
    {
        return const_iterator(begin());
    }

    template <typename _Tp, typename _Alloc>
    typename list<_Tp, _Alloc>::const_iterator
    list<_Tp, _Alloc>::
        cend() ustl_cpp_noexcept
    {
        return const_iterator(end());
    }

    template <typename _Tp, typename _Alloc>
    typename list<_Tp, _Alloc>::const_iterator
    list<_Tp, _Alloc>::
        cbegin() const ustl_cpp_noexcept
    {
        return const_iterator(begin());
    }

    template <typename _Tp, typename _Alloc>
    typename list<_Tp, _Alloc>::const_iterator
    list<_Tp, _Alloc>::
        cend() const ustl_cpp_noexcept
    {
        return const_iterator(end());
    }

    template <typename _Tp, typename _Alloc>
    typename list<_Tp, _Alloc>::reference
    list<_Tp, _Alloc>::
        front() ustl_cpp_noexcept
    {
        return *begin();
    }

    template <typename _Tp, typename _Alloc>
    typename list<_Tp, _Alloc>::reference
    list<_Tp, _Alloc>::
        back() ustl_cpp_noexcept
    {
        return *iterator(_M_data_plus->_M_header._M_last());
    }

    template <typename _Tp, typename _Alloc>
    size_t
    list<_Tp, _Alloc>::
        size() const ustl_cpp_noexcept
    {
        return _M_data_plus->_M_header._M_count;
    }

    template <typename _Tp, typename _Alloc>
    bool list<_Tp, _Alloc>::
        empty() const ustl_cpp_noexcept
    {
        return (0 == size());
    }

    template <typename _Tp, typename _Alloc>
    list<_Tp, _Alloc> &
    list<_Tp, _Alloc>::
    operator=(list &&__other)
    {
        if (&__other != this)
        {
            clear();
            swap(__other);
        }
        return *this;
    }

    template <typename _Tp, typename _Alloc>
    list<_Tp, _Alloc> &
    list<_Tp, _Alloc>::
    operator=(list const &__other)
    {
        if (&__other != this)
            _M_fill_assign(begin(), __other.begin(), __other.end());
        return *this;
    }

    template <typename _Tp, typename _Alloc>
    inline bool
    operator==(list<_Tp, _Alloc> const &__l,
               list<_Tp, _Alloc> const &__r)
    {
        typedef typename list<_Tp, _Alloc>::const_iterator iterator;
        iterator __first = __l.begin();
        iterator __last = __l.end();
        iterator __first1 = __l.begin();
        iterator __last1 = __l.end();
        while (__first1 != __last1 && __first != __last &&
               *__first1 == *__first)
            ++__first1, ++__first;

        return __first1 == __last1 && __first == __last;
    }

    template <typename _Tp, typename _Alloc>
    inline bool
    operator!=(list<_Tp, _Alloc> const &__l,
               list<_Tp, _Alloc> const &__r)
    {
        return !(__l == __r);
    }
}

#endif