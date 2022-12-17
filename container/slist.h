#ifndef __ustl_single_list_h
#define __ustl_single_list_h

#include "allocator/memory.h"

namespace ustl
{
    struct slist_node_basic
    {
        typedef slist_node_basic _base_type;
        typedef slist_node_basic *_base_ptr;

        void
        _M_hook(_base_ptr __last)
        {
            _M_next = __last->_M_next;
            __last->_M_next = this;
        }

        void
        _M_unhook(_base_ptr __last)
        {
            __last->_M_next = _M_next;
            _M_next = 0;
        }

        /** (__before, __last]    */
        void
        _M_transer_after(_base_ptr __before,
                         _base_ptr __last)
        {
            _base_ptr __end_now = _M_next;
            _M_next = __before->_M_next;
            if (__last)
            {
                __before->_M_next = __last->_M_next;
                __last->_M_next = __end_now;
            }
            else
                __before->_M_next = 0;
        }

        static _base_ptr
        _S_find_pre(_base_ptr __first, _base_ptr __last)
        {
            _base_ptr __tmp = __first;
            while (__tmp && __tmp->_M_next != __last)
                __tmp = __tmp->_M_next;
            return __tmp;
        }

        slist_node_basic()
            : _M_next(this) {}

#ifdef __debug_ustl
        int _M_value_field;
#endif

        _base_ptr _M_next;
    };

    struct slist_header
        : slist_node_basic
    {
        typedef slist_header _Self;
        typedef slist_node_basic *_base_ptr;

        size_t
        _M_length()
        {
            return _M_count;
        }

        _base_ptr
        _M_front()
        {
            return _M_next;
        }

        _base_ptr
        _M_back()
        {
            return _M_last;
        }

        /** thread safe */
        void
        _M_change_len(ustl::diff_t __x)
        {
            /** bus lock for atomic operation */
            asm volatile("lock add  %1, %0\n\t"
                         : "=m"(_M_count)
                         : "ir"(__x));
        }

        slist_header()
            : _M_count(0), _M_last(this) {}

        size_t _M_count;
        _base_ptr _M_last;
    };

    template <typename _Tp>
    struct slist_node
        : slist_node_basic
    {
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;

        pointer
        _M_valptr()
        {
            return &_M_value_field;
        }

        reference
        _M_value()
        {
            return _M_value_field;
        }

        static _base_ptr
        _S_next(_base_ptr __p)
        {
            return __p->_M_next;
        }

        slist_node() = default;

        slist_node(int a) { _M_value_field = a; }

#ifndef __debug_ustl
        value_type _M_value_field;
#endif
    };

    template <typename _Tp, typename _Alloc>
    struct slist_impl
        : ustl::allocate_traits<_Alloc>::rebind<slist_node<_Tp>>::other
    {
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;

        void
        _M_swap(slist_impl &__other)
        {
            slist_impl __tmp(*this);
            _M_move(__other);
            __other._M_move(__tmp);
        }

        void
        _M_move(slist_impl &__other)
        {
            _M_header._M_count = __other._M_header._M_count;
            _M_header._M_next = __other._M_header._M_next;
            _M_header._M_last = __other._M_header._M_last;
            __other._M_reset();
        }

        void
        _M_reset()
        {
            _M_header._M_count = 0;
            _M_header._M_next = 0;
            _M_header._M_last = 0;
        }

        slist_impl()
            : _M_header(slist_header()) {}

        slist_header _M_header;
    };

    template <typename _Tp>
    struct slist_iterator
    {
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;
        typedef ustl::_forword_iterator iterator_tag;

        typedef slist_node_basic *base_ptr;
        typedef slist_node_basic const *const_base_ptr;
        typedef slist_node<_Tp> *node_ptr;
        typedef slist_node<_Tp> const *const_node_ptr;
        typedef slist_iterator _Self;

        _Self &
        operator++()
        {
            _M_data = _M_data->_M_next;
            return *this;
        }

        _Self
        operator++(int)
        {
            _Self __tmp(*this);
            _M_data = _M_data->_M_next;
            return __tmp;
        }

        reference
        operator*()
        {
            return static_cast<node_ptr>(_M_data)->_M_value();
        }

        pointer
        operator->()
        {
            return static_cast<node_ptr>(_M_data)->_M_valptr();
        }

        base_ptr
        data()
        {
            return _M_data;
        }

        friend bool
        operator==(_Self const &__l, _Self const &__r)
        {
            return __l._M_data == __r._M_data;
        }

        friend bool
        operator!=(_Self const &__l, _Self const &__r)
        {
            return __l._M_data != __r._M_data;
        }

        slist_iterator() = default;

        slist_iterator(base_ptr __p)
            : _M_data(__p) {}

        slist_iterator(slist_iterator const &__other)
            : _M_data(__other._M_data) {}

    protected:
        base_ptr _M_data;
    };

    template <typename _Tp>
    struct slist_const_iterator
    {
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;
        typedef ustl::_forword_iterator iterator_tag;

        typedef slist_node_basic *base_ptr;
        typedef slist_node_basic const *const_base_ptr;
        typedef slist_node<_Tp> *node_ptr;
        typedef slist_node<_Tp> const *const_node_ptr;
        typedef slist_const_iterator _Self;

        _Self &
        operator++()
        {
            _M_data = _M_data->_M_next;
            return *this;
        }

        _Self
        operator++(int)
        {
            _Self __ret(*this);
            _M_data = _M_data->_M_next;
            return __ret;
        }

        const_reference
        operator*()
        {
            return static_cast<node_ptr>(_M_data)->_M_value();
        }

        const_pointer
        operator->()
        {
            return static_cast<node_ptr>(_M_data)->_M_valptr();
        }

        const_base_ptr
        data()
        {
            return _M_data;
        }

        friend bool
        operator==(_Self const &__l, _Self const &__r)
        {
            return __l._M_data == __r._M_data;
        }

        friend bool
        operator!=(_Self const &__l, _Self const &__r)
        {
            return __l._M_data != __r._M_data;
        }

        slist_const_iterator() = default;

        slist_const_iterator(const_base_ptr __p)
            : _M_data(const_cast<base_ptr>(__p)) {}

        slist_const_iterator(slist_iterator<_Tp> __itr)
            : _M_data(__itr.data()) {}

        slist_const_iterator(slist_const_iterator const &__itr)
            : _M_data(__itr._M_data) {}

        slist_const_iterator(slist_const_iterator &&__itr)
            : _M_data(__itr._M_data) { __itr._M_data = 0; }

    protected:
        base_ptr _M_data;
    };

    template <typename _Tp, typename _Alloc = ustl::allocator<_Tp>>
    class slist
    {
    public:
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;
        typedef typename allocate_traits<_Alloc>::rebind<slist_node<_Tp>>::other Nallocator_type;
        typedef allocate_traits<Nallocator_type> Nallocator_traits;

        typedef ustl::size_t size_type;
        typedef ustl::diff_t difference_type;

        typedef ustl::slist_iterator<_Tp> iterator;
        typedef ustl::slist_const_iterator<_Tp> const_iterator;

    private:
        typedef slist_node_basic *base_ptr;
        typedef slist_node<_Tp> node_type;
        typedef slist_node<_Tp> *node_ptr;
        typedef slist_impl<_Tp, _Alloc> impl_type;

    public:
        slist()
            : _M_data_plus(impl_type()) {}

        template <typename _ForwardIterator>
        slist(_ForwardIterator __first, _ForwardIterator __last)
            : _M_data_plus(impl_type())
        {
            _M_assign_copy(before_begin(), __first, __last);
        }

    public:
        Nallocator_type &
        _M_get_allocator()
        {
            return _M_data_plus;
        }

        template <typename... _Args>
        base_ptr
        _M_create_node(_Args &&...__args)
        {
            base_ptr __new = Nallocator_traits::allocate(_M_get_allocator(), 1);
            /** catch construct exception */
            __ustl_try
            {
                Nallocator_traits::construct(_M_get_allocator(),
                                             static_cast<node_ptr>(__new)->_M_valptr(),
                                             ustl::forward<_Args &&>(__args)...);
            }
            __ustl_catch_all
            {
                _M_deallocate_node(__new);
                __ustl_throw_again;
            }
            return __new;
        }

        void
        _M_destory_node(base_ptr __p, size_type __n = 1)
        {
            for (; __n; --__n, (void)(__p = __p->_M_next))
                Nallocator_traits::destory(_M_get_allocator(),
                                           static_cast<node_ptr>(__p)->_M_valptr());
        }

        void
        _M_deallocate_node(base_ptr __p, size_type __n = 1)
        {
            for (; __n; --__n, (void)(__p = __p->_M_next))
                Nallocator_traits::deallocate(_M_get_allocator(), __p, 1);
        }

        base_ptr
        _M_front() { return _M_data_plus._M_header._M_front(); }

        void
        _M_front(base_ptr __p) { _M_data_plus._M_header._M_next = __p; }

        base_ptr
        _M_back() { return _M_data_plus._M_header._M_back(); }

        void
        _M_back(base_ptr __p) { _M_data_plus._M_header._M_last = __p; }

        slist_header *
        _M_header() { return &_M_data_plus._M_header; }

        void
        _M_change_length(ustl::diff_t __n) { _M_data_plus._M_header._M_change_len(__n); }

        iterator
        _M_const_cast(const_iterator __itr) { return iterator(const_cast<base_ptr>(__itr.data())); }

        static base_ptr
        _S_next(base_ptr __p) { return __p->_M_next; }

        static void
        _S_set_next(base_ptr __pos, base_ptr __new) { return __pos->_M_next = __new; }

        static base_ptr
        _S_get_node(const_iterator __pos) { return const_cast<base_ptr>(__pos.data()); }

    public:
        size_type
        size() { return _M_data_plus._M_header._M_length(); }

        reference
        front() { return *_M_front(); }

        reference
        back() { return *_M_back(); }

        iterator
        before_begin() { return iterator(_M_header()); }

        iterator
        begin() { return iterator(_M_front()); }

        iterator
        end() { return iterator(0); }

        const_iterator
        before_begin() const { return const_iterator(_M_header()); }

        const_iterator
        begin() const { return const_iterator(_M_front()); }

        const_iterator
        end() const { return const_iterator(0); }

        const_iterator
        cbegin() { return const_iterator(_M_front()); }

        const_iterator
        before_cbegin() { return const_iterator(_M_header()); }

        const_iterator
        cend() { return const_iterator(0); }

        const_iterator
        before_cbegin() const { return const_iterator(_M_header()); }

        const_iterator
        cbegin() const { return const_iterator(_M_front()); }

        const_iterator
        cend() const { return const_iterator(0); }

        bool
        empty() { return 0 == size(); }

    private:
        void _M_assign_copy_aux(const_iterator, value_type const &, size_type);
        template <typename _ForwardIterator>
        void _M_assign_copy(const_iterator, _ForwardIterator, _ForwardIterator);

        template <typename... _Args>
        void _M_fill(size_type, _Args &&...);
        template <typename _ForwardIterator>
        size_t _M_fill_range(const_iterator, _ForwardIterator, _ForwardIterator);

        void _M_splice_after(const_iterator, const_iterator, const_iterator);
        template <typename _ForwardIterator>
        inline void _M_splice_after(const_iterator, _ForwardIterator, _ForwardIterator, ustl::false_type);
        template <typename _ForwardIterator>
        inline void _M_splice_after(const_iterator, _ForwardIterator, _ForwardIterator, ustl::true_type);

        template <typename... _Args>
        void _M_insert_back(_Args &&...);
        template <typename... _Args>
        iterator _M_insert_after(const_iterator, _Args &&...);

        void _M_erase_after(const_iterator);
        difference_type _M_erase_after_range(const_iterator, const_iterator);

    public:
        inline void assign(value_type const &, size_type);
        template <typename _ForwardIterator>
        inline void assign(_ForwardIterator, _ForwardIterator);

        template <typename... _Args>
        inline void emplace_after(const_iterator, _Args &&...);
        template <typename... _Args>
        inline void emplace_back(_Args &&...);
        template <typename... _Args>
        inline void emplace_front(_Args &&...);

        inline void push_back(value_type const &__val);
        inline void push_front(value_type const &__val);

        inline iterator insert_after(const_iterator, value_type const &);
        inline iterator insert_after(const_iterator, value_type const &, size_type);
        template <typename _ForwardIterator>
        inline iterator insert_after(const_iterator, _ForwardIterator, _ForwardIterator);

        inline slist &splice_after(const_iterator, slist &);
        inline slist &splice_after(const_iterator, slist &&);
        inline slist &splice_after(const_iterator, const_iterator, const_iterator);
        template <typename _ForwardIterator>
        inline slist &splice_after(const_iterator, _ForwardIterator, _ForwardIterator);

        inline void pop_front() ustl_cpp_noexcept;

        inline void erase_after(const_iterator) ustl_cpp_noexcept;
        inline difference_type erase_after(const_iterator, const_iterator) ustl_cpp_noexcept;

        inline size_type remove(value_type const &) ustl_cpp_noexcept;
        template <typename _Predicate>
        inline size_type remove_if(_Predicate) ustl_cpp_noexcept;

        void swap(slist &);
        void swap(slist &&);

        void reverse() ustl_cpp_noexcept;

        void resize(size_type);
        void resize(size_type, value_type const &);

        template <typename _Predicate = ustl::less_t<_Tp>>
        void merge(slist &, _Predicate = ustl::less_t<_Tp>()) ustl_cpp_noexcept;
        template <typename _Predicate = ustl::less_t<_Tp>>
        void merge(slist &&, _Predicate = ustl::less_t<_Tp>()) ustl_cpp_noexcept;

        template <typename _Predicate = ustl::less_t<_Tp>>
        void sort(_Predicate = ustl::less_t<_Tp>()) ustl_cpp_noexcept;

        void clear();

    protected:
        impl_type _M_data_plus;
    };

    template <typename _Tp, typename _Alloc>
    void
    slist<_Tp, _Alloc>::
        _M_assign_copy_aux(const_iterator __pos,
                           value_type const &__val,
                           size_type __n)
    {
        size_type __counter = __n;
        iterator __first = begin();
        size_type __old_size = size();
        for (; __counter && __old_size;
             --__counter, (void)--__old_size, ++__first)
        {
            *__first = __val;
        }
        if (!__old_size)
        {
            _M_fill(__counter, __val);
            _M_change_length(__counter);
        }
        else
            _M_erase_after_range(__first, end());
    }

    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    void
    slist<_Tp, _Alloc>::
        _M_assign_copy(const_iterator __pos,
                       _ForwardIterator __first,
                       _ForwardIterator __last)
    {
        size_type __old_size = size();
        size_type __counter = 0;
        iterator __begin = begin();
        while (__old_size && __first != __last)
        {
            *__begin = *__first;
            ++__begin, (void)++__first;
            --__old_size;
        }
        if (!__old_size)
            __counter = _M_fill_range(_M_back(), __first, __last);
        _M_change_length(__counter);
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    typename slist<_Tp, _Alloc>::iterator
    slist<_Tp, _Alloc>::
        _M_insert_after(const_iterator __pos,
                        _Args &&...__init_args)
    {
        base_ptr __pos_node = _S_get_node(__pos);
        base_ptr __new_node = _M_create_node(ustl::forward<_Args &&>(__init_args)...);
        __new_node->_M_next = __pos_node->_M_next;
        __pos_node->_M_next = __new_node;
        _M_change_length(1);
        return iterator(__new_node);
    }

    template <typename _Tp, typename _Alloc>
    void
    slist<_Tp, _Alloc>::
        _M_erase_after(const_iterator __pos)
    {
        base_ptr __pos_node = _S_get_node(__pos);
        base_ptr __del = _S_next(__pos_node);
        if (__del)
        {
            __pos_node->_M_next = __del->_M_next;
            _M_destory_node(__del);
            _M_deallocate_node(__del);
            _M_change_length(-1);
        }
    }

    template <typename _Tp, typename _Alloc>
    ustl::diff_t
    slist<_Tp, _Alloc>::
        _M_erase_after_range(const_iterator __before,
                             const_iterator __last)
    {
        base_ptr __bef = _M_const_cast(__before).data();
        base_ptr __end = _M_const_cast(__last).data();
        base_ptr __tmp = _S_next(__bef);
        __bef->_M_next = __end;
        difference_type __counter = 0;
        while (__tmp != __end)
        {
            __bef = __tmp->_M_next;
            _M_destory_node(__tmp);
            _M_deallocate_node(__tmp);
            __tmp = __bef;
            --__counter;
        }
        _M_change_length(__counter);
        return __counter;
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    void
    slist<_Tp, _Alloc>::
        _M_fill(size_type __n, _Args &&...__init_args)
    {
        base_ptr __tmp = _M_back();
        while (__n--)
        {
            base_ptr __new = _M_create_node(ustl::forward<_Args &&>(__init_args)...);
            __new->_M_hook(__tmp);
            __tmp = _S_next(__tmp);
        }
        _M_change_length(__n);
    }

    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    size_t
    slist<_Tp, _Alloc>::
        _M_fill_range(const_iterator __pos,
                      _ForwardIterator __first,
                      _ForwardIterator __last)
    {
        size_type __len = 0;
        node_ptr __tmp = static_cast<node_ptr>(_S_get_node(__pos));
        for (; __first != __last; ++__first, (void)++__len)
        {
            node_ptr __next = static_cast<node_ptr>(_S_next(__tmp));
            __next = static_cast<node_ptr>(_M_create_node(*__first));
            __tmp->_M_next = __next;
            __tmp = __next;
        }
        _M_back(__tmp);
        return __len;
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    void
    slist<_Tp, _Alloc>::
        _M_insert_back(_Args &&...__init_args)
    {
        base_ptr __p = _M_back();
        base_ptr __new_back = _M_create_node(ustl::forward<_Args &&>(__init_args)...);
        __p->_M_next = __new_back;
        _M_header()->_M_last = __new_back;
        _M_change_length(1);
    }

    template <typename _Tp, typename _Alloc>
    void
    slist<_Tp, _Alloc>::
        _M_splice_after(const_iterator __pos,
                        const_iterator __before,
                        const_iterator __last)
    {
        base_ptr __p = _S_get_node(__pos);
        base_ptr __begin = _S_get_node(__before);
        base_ptr __end = _S_get_node(__last);

        __end = slist_node_basic::_S_find_pre(__begin, __end);

        __p->_M_transer_after(__begin, __end);
    }

    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    void
    slist<_Tp, _Alloc>::
        _M_splice_after(const_iterator __pos,
                        _ForwardIterator __before,
                        _ForwardIterator __last,
                        ustl::false_type)
    {
        slist __tmp(++__before, __last);
        if (!__tmp.empty())
        {
            _M_splice_after(__pos, __tmp.before_cbegin(), __tmp.end());
            _M_change_length(__tmp.size());
        }
    }

    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    inline void
    slist<_Tp, _Alloc>::
        _M_splice_after(const_iterator __pos,
                        _ForwardIterator __before,
                        _ForwardIterator __last,
                        ustl::true_type)
    {
        _M_splice_after(__pos, const_iterator(__before), const_iterator(__last));
    }

    template <typename _Tp, typename _Alloc>
    inline auto
    slist<_Tp, _Alloc>::
        insert_after(const_iterator __pos,
                     value_type const &__val) -> iterator
    {
        _M_insert_after(__pos, __val);
    }

    template <typename _Tp, typename _Alloc>
    auto
    slist<_Tp, _Alloc>::
        insert_after(const_iterator __pos,
                     value_type const &__val,
                     size_type __n) -> iterator
    {
        slist __tmp(__val, __n);
        if (__tmp.empty())
        {
            _M_splice_after(__pos, __tmp.before_cbegin(), __tmp.cend());
            _M_change_length(__tmp.size());
        }
        return iterator(_S_get_node(__pos));
    }

    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    auto
    slist<_Tp, _Alloc>::
        insert_after(const_iterator __pos,
                     _ForwardIterator __first,
                     _ForwardIterator __last) -> iterator
    {
        slist __tmp(__first, __last);
        if (__tmp.empty())
        {
            _M_splice_after(__pos, __tmp.before_cbegin(), __tmp.cend());
            _M_change_length(__tmp.size());
        }
        return iterator(_S_get_node(__pos));
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    inline void
    slist<_Tp, _Alloc>::
        emplace_after(const_iterator __pos,
                      _Args &&...__init_args)
    {
        _M_insert_after(__pos, ustl::forward<_Args &&>(__init_args)...);
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    inline void
    slist<_Tp, _Alloc>::
        emplace_back(_Args &&...__init_args)
    {
        _M_insert_back(ustl::forward<_Args &&>(__init_args)...);
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    inline void
    slist<_Tp, _Alloc>::
        emplace_front(_Args &&...__init_args)
    {
        _M_insert_after(before_cbegin(), ustl::forward<_Args &&>(__init_args)...);
    }

    template <typename _Tp, typename _Alloc>
    inline void
    slist<_Tp, _Alloc>::
        push_back(value_type const &__val)
    {
        _M_insert_back(__val);
    }

    template <typename _Tp, typename _Alloc>
    inline void
    slist<_Tp, _Alloc>::
        push_front(value_type const &__val)
    {
        _M_insert_after(before_cbegin(), __val);
    }

    /**
     * (__before,   __last) loro
     */
    template <typename _Tp, typename _Alloc>
    auto
    slist<_Tp, _Alloc>::
        splice_after(const_iterator __pos,
                     slist &__other) -> slist &
    {
        size_type __add_len = __other.size();
        if (!__other.empty())
        {
            _M_splice_after_after(__pos, __other.before_begin(), __other.end());
            _M_change_length(__add_len);
            __other._M_data_plus._M_reset();
        }
        return __add_len;
    }

    template <typename _Tp, typename _Alloc>
    inline auto
    slist<_Tp, _Alloc>::
        splice_after(const_iterator __pos,
                     slist &&__other) -> slist &
    {
        return splice_after(__pos, __other);
    }

    template <typename _Tp, typename _Alloc>
    inline auto
    slist<_Tp, _Alloc>::
        splice_after(const_iterator __pos,
                     const_iterator __before,
                     const_iterator __last) -> slist &
    {
        _M_splice_after(__pos, __before, __last, ustl::true_type());
        return *this;
    }

    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    inline auto
    slist<_Tp, _Alloc>::
        splice_after(const_iterator __pos,
                     _ForwardIterator __before,
                     _ForwardIterator __last) -> slist &
    {
        _M_splice_after(__pos, __before, __last,
                        ustl::is_same<_ForwardIterator, iterator>());
        return *this;
    }

    template <typename _Tp, typename _Alloc>
    inline void
    slist<_Tp, _Alloc>::
        assign(value_type const &__val, size_type __n)
    {
        _M_assign_copy_aux(before_cbegin(), __val, __n);
    }

    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    inline void
    slist<_Tp, _Alloc>::
        assign(_ForwardIterator __first, _ForwardIterator __last)
    {
        _M_assign_copy(before_cbegin(), __first, __last);
    }

    template <typename _Tp, typename _Alloc>
    inline void
    slist<_Tp, _Alloc>::
        pop_front() ustl_cpp_noexcept
    {
        _M_erase_after(before_cbegin());
    }

    template <typename _Tp, typename _Alloc>
    inline void
    slist<_Tp, _Alloc>::
        erase_after(const_iterator __pos) ustl_cpp_noexcept
    {
        _M_erase_after(__pos);
    }

    template <typename _Tp, typename _Alloc>
    inline typename slist<_Tp, _Alloc>::difference_type
    slist<_Tp, _Alloc>::
        erase_after(const_iterator __before, const_iterator __last) ustl_cpp_noexcept
    {
        return _M_erase_after_range(__before, __last);
    }

    template <typename _Tp, typename _Alloc>
    typename slist<_Tp, _Alloc>::size_type
    slist<_Tp, _Alloc>::
        remove(value_type const &__val) ustl_cpp_noexcept
    {
        size_type __del_counter = 0;
        base_ptr __first = _M_header();
        while (0 != __first->_M_next)
        {
            base_ptr __next = __first->_M_next;
            if (__val == static_cast<node_ptr>(__next)->_M_value())
            {
                _M_erase_after(const_iterator(__first));
                ++__del_counter;
            }
            else
                __first = __next;
        }
        return __del_counter;
    }

    template <typename _Tp, typename _Alloc>
    template <typename _Predicate>
    typename slist<_Tp, _Alloc>::size_type
    slist<_Tp, _Alloc>::
        remove_if(_Predicate __comp) ustl_cpp_noexcept
    {
        size_type __del_counter = 0;
        base_ptr __first = _M_header();
        while (0 != __first->_M_next)
        {
            base_ptr __next = __first->_M_next;
            if (__comp(static_cast<node_ptr>(__next)->_M_value()))
            {
                _M_erase_after(const_iterator(__first));
                ++__del_counter;
            }
            else
                __first = __next;
        }
        return __del_counter;
    }

    template <typename _Tp, typename _Alloc>
    inline void
    slist<_Tp, _Alloc>::
        swap(slist &__other)
    {
        if (this == &__other)
            return;
        _M_data_plus._M_swap(__other._M_data_plus);
    }

    template <typename _Tp, typename _Alloc>
    inline void
    slist<_Tp, _Alloc>::
        swap(slist &&__other)
    {
        if (this = &__other)
            return;
        clear();
        _M_data_plus._M_move(__other);
    }

    template <typename _Tp, typename _Alloc>
    void
    slist<_Tp, _Alloc>::
        reverse() ustl_cpp_noexcept
    {
        base_ptr __first = 0;
        base_ptr __second = _M_front();
        base_ptr __third = _S_next(__second);

        _M_back(__second);
        while (__third)
        {
            __second->_M_next = __first;
            __first = __second;
            __second = __third;
            __third = __third->_M_next;
        }
        __second->_M_next = __first;
        _M_front(__second);
    }

    template <typename _Tp, typename _Alloc>
    void
    slist<_Tp, _Alloc>::
        resize(size_type __new_size)
    {
        size_type __old_size = size();
        if (__new_size > __old_size)
        {
            size_type __add_len = __new_size - __old_size;
            _M_fill(__add_len);
            _M_change_length(__add_len);
        }
    }

    template <typename _Tp, typename _Alloc>
    void
    slist<_Tp, _Alloc>::
        resize(size_type __new_size,
               value_type const &__val)
    {
        size_type __old_size = size();
        if (__new_size > __old_size)
        {
            size_type __add_len = __new_size - __old_size;
            _M_fill(__add_len, __val);
            _M_change_length(__add_len);
        }
    }

    template <typename _Tp, typename _Alloc>
    template <typename _Predicate>
    void
    slist<_Tp, _Alloc>::
        merge(slist &__other, _Predicate __cmp) ustl_cpp_noexcept
    {
        iterator __first = begin();
        iterator __last = end();
        iterator __first1 = __other.begin();
        iterator __last1 = __other.end();
        iterator __before = before_begin();
        iterator __before1 = __other.before_begin();

        while (__first != __last && __first1 != __last1)
        {
            if (__cmp(*__first * __first1))
                __before = __first++;
            else
            {
                iterator __next = __before1;
                __first1.data()->_M_unhook(__before1.data());
                __first1.data()->_M_hook(__before.data());
                __first1 = ++__next;
            }
        }
        if (__first1 != __last1)
        {
            _M_back(__other._M_back());
            __before.data()->_M_transer_after(__before1.data(), __last1.data());
        }
        else
            _M_back(__before.data());
        _M_change_length(__other.size());
        __other._M_data_plus._M_reset();
    }

    template <typename _Tp, typename _Alloc>
    template <typename _Predicate>
    inline void
    slist<_Tp, _Alloc>::
        merge(slist &&__other, _Predicate __cmp) ustl_cpp_noexcept
    {
        merge(__other, __cmp);
    }

    /**
     * @GNU stadard forward_list::sort
     * 主要思想就是通过遍历链表与增加每次摘取的结点进行归并，放置于新的局部有序链表中
     * 在此对 GNU 的前辈们表示钦佩
     */
    template <typename _Tp, typename _Alloc>
    template <typename _Predicate>
    void
    slist<_Tp, _Alloc>::
        sort(_Predicate __cmp) ustl_cpp_noexcept
    {
        size_type __ysize;
        size_type __xsize;
        size_type __counter;
        size_type __len = size() >> 1;
        size_type __merge_size = 1;

        node_ptr __head = static_cast<node_ptr>(_M_front());
        node_ptr __tail;

        while (__merge_size <= __len)
        {
            node_ptr __x = __head;
            node_ptr __y = __x;

            __tail = 0;
            while (__x)
            {
                __ysize = __merge_size;
                __xsize = __merge_size;

                // Extract nodes from __x linked list to fill the
                // linked list pick node for __y list
                for (__counter = 0;
                     __counter < __merge_size && __x;
                     ++__counter)
                {
                    __x = static_cast<node_ptr>(_S_next(__x));
                }

                // find the node that`s min and insert sorted linker list
                node_ptr __lower;
                while (__ysize || (__xsize && __x))
                {
                    if (!__ysize)
                    {
                        __lower = __x;
                        __x = static_cast<node_ptr>(_S_next(__x));
                        --__xsize;
                    }
                    else if (!__xsize || !__x)
                    {
                        __lower = __y;
                        __y = static_cast<node_ptr>(_S_next(__y));
                        --__ysize;
                    }
                    else if (__cmp(__x->_M_value(), __y->_M_value()))
                    {
                        __lower = __x;
                        __x = static_cast<node_ptr>(_S_next(__x));
                        --__xsize;
                    }
                    else
                    {
                        __lower = __y;
                        __y = static_cast<node_ptr>(_S_next(__y));
                        --__ysize;
                    }

                    // add to new head
                    if (0 == __tail)
                        __head = __lower;
                    else
                        __tail->_M_next = __lower;
                    __tail = __lower;
                }
                __y = __x;
            }
            // new end is pointer to 0
            __tail->_M_next = 0;

            // merge size 2*n
            __merge_size <<= 1;
        }
        _M_front(__head);
        _M_back(__tail);
    }

    template <typename _Tp, typename _Alloc>
    inline void
    slist<_Tp, _Alloc>::
        clear()
    {
        _M_deallocate_node(_M_front(), size());
        _M_data_plus._M_reset();
    }

} // namespace ustl::slist

#endif