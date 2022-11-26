#ifndef __ustl_deque_h
#define __ustl_deque_h

#define _DEQUE_ALLOC_SIZE 512

namespace ustl
{
    template <typename _Tp, typename _Ref, typename _Ptr>
    struct deque_iterator
    {
        typedef _Tp value_type;
        typedef _Ref reference;
        typedef _Ptr _ele_pointer;
        typedef _Ptr *_bc_pointer;
        typedef ustl::_random_itertor iterator_tag;
        typedef ustl::diff_t difference_type;
        typedef deque_iterator _Self;

    private:
        static constexpr size_t
        _M_size_of_bucket()
        {
            return _DEQUE_ALLOC_SIZE / sizeof(_Tp);
        }

        void
        _M_update(_bc_pointer __new_bucket)
        {
            _M_bucket_cur = __new_bucket;
            _M_ele_first = *__new_bucket;
            _M_ele_last = _M_ele_first + _M_ele_of_bucket();
        }

    public:
        _Self &
        operator++()
        {
            ++_M_data;
            if (_M_data == _M_ele_last)
            {
                _M_update(_M_bucket_cur + 1);
                _M_data = _M_ele_first;
            }
            return *this;
        }

        _Self
        operator++(int)
        {
            _Self __ret(*this);
            ++*this;
            return __ret;
        }

        _Self &
        operator--()
        {
            --_M_data;
            if (_M_data == _M_ele_first)
            {
                _M_update(_M_bucket_cur - 1);
                _M_data = _M_ele_last;
            }
        }

        _Self
        operator--(int)
        {
            _Self __ret(*this);
            --*this;
            return __ret;
        }

        reference
        operator*()
        {
            return *_M_data;
        }

        _ele_pointer
        operator->()
        {
            return _M_data;
        }

        _Self
        operator+(difference_type __step)
        {
            _Self __ret(*this);
            for (; __step > 0; --__step)
                ++__ret;
            if (__step < 0)
                __ret - (-__step);
            return __ret;
        }

        _Self
        operator-(difference_type __step)
        {
            _Self __ret(*this);
            for (; __step > 0; --__step)
                --__ret;
            if (__step < 0)
                __ret + (-__step);
            return __ret;
        }

        _Self &
        operator+=(difference_type __step)
        {
            for (; __step > 0; --__step)
                ++*this;
            if (__step < 0)
                *this - (-__step);
            return *this;
        }

        _Self &
        operator-=(difference_type __step)
        {
            for (; __step > 0; --__step)
                --*this;
            if (__step < 0)
                *this - (-__step);
            return *this;
        }

        _Self &
        operator=(_Self const &__other)
        {
            _M_data = __other._M_data;
            _M_ele_first = __other._M_ele_first;
            _M_ele_last = __other._M_ele_last;
            _M_bucket_cur = __other._M_bucket_cur;
            return *this;
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

        _ele_pointer _M_data;

        _ele_pointer _M_ele_first;
        _ele_pointer _M_ele_last;

        _bc_pointer _M_bucket_cur;
    };

    template <typename _Tp, typename _Alloc>
    struct debue_impl
        : _Alloc,
          _Alloc::template rebind<_Tp **>::other
    {
        typedef _Tp *_ele_pointer;
        typedef _Tp **_bc_pointer;
        typedef deque_iterator<_Tp, _Tp &, _Tp *> iterator;

        _bc_pointer _M_bucket;
        iterator _M_begin;
        iterator _M_end;
        size_t _M_bucket_count;
    };

    template <typename _Tp, typename _Alloc>
    class deque
    {
        typedef debue_impl<_Tp, _Alloc> impl_type;
        typedef _Tp **_bc_pointer;

    public:
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;

        typedef _Alloc allocator_type;
        typedef typename allocate_traits<_Alloc>::template rebind<_bc_pointer>::other bc_allocator_type;
        typedef ustl::diff_t difference_type;
        typedef ustl::size_t size_type;

        typedef deque_iterator<_Tp, _Tp &, _Tp *> iterator;
        typedef deque_iterator<_Tp, _Tp const &, _Tp const *> const_iterator;
        typedef ustl::reverse_iterator<iterator> reverse_iterator;
        typedef ustl::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
        /** private interface */
        allocator_type &
        _M_get_allocator() { return _M_data_plus; }

        pointer
        _M_create_bucket() {}

        _bc_pointer
        _M_create_bucket_table() {}

        void
        _M_destory_bucket() {}

        void
        _M_destory_bucket_table() {}

        template <typename... _Args>
        void
        _M_construct(pointer __p, _Args &&...__init_args) {}

        void
        _M_desotry() {}

    public:
        iterator
        begin() { return _M_data_plus._M_begin(); }

        iterator
        end() { return _M_data_plus._M_end(); }

        const_iterator
        begin() const { return const_iterator(begin()); }

        const_iterator
        end() const { return const_iterator(end()); }

        const_iterator
        cbegin() { return const_iterator(begin()); }

        const_iterator
        cend() { return const_iterator(end()); }

        const_iterator
        cbegin() const { return begin(); }

        const_iterator
        cend() const { return end(); }

        reverse_iterator
        rbegin() { return reverse_iterator(begin()); }

        reverse_iterator
        rend() { return reverse_iterator(end()); }

        const_reverse_iterator
        rbegin() const { return const_reverse_iterator(rbegin()); }

        const_reverse_iterator
        rend() const { return const_reverse_iterator(rend()); }

        const_reverse_iterator
        crbegin() { return const_reverse_iterator(rbegin()); }

        const_reverse_iterator
        crend() { return const_reverse_iterator(rend()); }

        const_reverse_iterator
        crbegin() const { return const_reverse_iterator(rbegin()); }

        const_reverse_iterator
        crend() const { return const_reverse_iterator(rend()); }

        reference
        back() {}

        reference
        front() {}

        const_reference
        back() const {}

        const_reference
        front() const {}

        size_type
        capacity() {}

        size_type
        size() {}

        bool
        empty() {}

    public:
        void assign(value_type const &, size_type);
        template <typename _ForwardIterator>
        void assign(_ForwardIterator, _ForwardIterator);

        template <typename... _Args>
        iterator emplace(const_iterator, _Args &&...);
        template <typename... _Args>
        void emplace_front(_Args &&...);
        template <typename... _Args>
        void emplace_back(_Args &&...);

        void push_front(value_type const &);
        void push_back(value_type const &);

        iterator insert(const_iterator, value_type &&);
        iterator insert(const_iterator, value_type const &, size_type = 1);
        template <typename _ForwardIterator>
        iterator insert(const_iterator, _ForwardIterator, _ForwardIterator);

        iterator erase(const_iterator);
        iterator erase(const_iterator, const_iterator);

        void pop_back();
        void pop_front();

        void reserve(size_type);
        void resize(size_type, value_type const &= value_type());

        void swap(deque &) ustl_cpp_noexcept;
        void swap(deque &&) ustl_cpp_noexcept;

        void clear();

        deque &operator=(deque &&) ustl_cpp_noexcept;
        deque &operator=(deque const &) ustl_cpp_noexcept;

        reference operator[](size_type);
        const_reference operator[](size_type) const;

    protected:
        impl_type _M_data_plus;
    };

} // namespace ustl

#endif
