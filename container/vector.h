#ifndef __vector_h
#define __vector_h

namespace ustl
{
    template <typename _Tp, typename _Alloc>
    struct _vec_impl
        : allocate_traits<_Alloc>::allocator_type
    {
        typedef _Tp *pointer;
        typedef _Tp &reference;

        size_t
        _M_element_count()
        {
            return _M_storage - _M_begin;
        }

        void
        _M_copy_data(_vec_impl &__other)
        {
            _M_begin = __other._M_begin;
            _M_end = __other._M_end;
            _M_storage = __other._M_storage;
        }

        void
        _M_move_data(_vec_impl &__other)
        {
            _M_copy_data(__other);
            __other._M_begin = 0;
            __other._M_storage = 0;
            __other._M_end = 0;
        }

        void
        _M_swap(_vec_impl &__other)
        {
            _vec_impl __tmp{*this};
            _M_copy_data(__other);
            __other._M_copy_data(__tmp);
        }

        void
        _M_amend(pointer __begin,
                 size_t __size,
                 size_t __capacity)
        {
            _M_begin = __begin;
            _M_end = __begin + __capacity;
            _M_storage = __begin + __size;
        }

        _vec_impl()
            : _M_begin(0),
              _M_end(0),
              _M_storage(0) {}

        pointer _M_begin;
        pointer _M_storage;
        pointer _M_end;
    };

    template <typename _Tp>
    struct _vector_iterator
    {
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;
        typedef ustl::diff_t difference_type;
        typedef _vector_iterator _Self;
        typedef _random_iterator iterator_tag;

        pointer
        operator->()
        {
            return _M_data_ptr;
        }

        reference
        operator*()
        {
            return *_M_data_ptr;
        }

        _Self
        operator++()
        {
            ++_M_data_ptr;
            return *this;
        }

        _Self
        operator--()
        {
            --_M_data_ptr;
            return *this;
        }

        _Self
        operator++(int)
        {
            pointer __ret = _M_data_ptr++;
            return _Self(__ret);
        }

        _Self
        operator--(int)
        {
            pointer __ret = _M_data_ptr--;
            return _Self(__ret);
        }

        friend bool
        operator!=(_Self __l, _Self __r)
        {
            return __l._M_data_ptr != __r._M_data_ptr;
        }

        friend bool
        operator==(_Self __l, _Self __r)
        {
            return __l._M_data_ptr == __r._M_data_ptr;
        }

        _vector_iterator() = default;

        _vector_iterator(pointer __p)
            : _M_data_ptr(__p) {}

        pointer _M_data_ptr;
    };

    template <typename _Tp>
    struct _vector_const_iterator
    {
        typedef _Tp value_type;
        typedef _Tp const *pointer;
        typedef _Tp const &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;
        typedef ustl::diff_t difference_type;
        typedef _vector_const_iterator _Self;
        typedef _random_iterator iterator_tag;

        pointer
        operator->()
        {
            return _M_data_ptr;
        }

        reference
        operator*()
        {
            return *_M_data_ptr;
        }

        _Self
        operator++()
        {
            ++_M_data_ptr;
            return *this;
        }

        _Self
        operator--()
        {
            --_M_data_ptr;
            return *this;
        }

        _Self
        operator++(int)
        {
            pointer __ret = _M_data_ptr++;
            return _Self(__ret);
        }

        _Self
        operator--(int)
        {
            pointer __ret = _M_data_ptr--;
            return _Self(__ret);
        }

        friend bool
        operator!=(_Self __l, _Self __r)
        {
            return __l._M_data_ptr != __r._M_data_ptr;
        }

        friend bool
        operator==(_Self __l, _Self __r)
        {
            return __l._M_data_ptr == __r._M_data_ptr;
        }

        _vector_const_iterator() = default;

        _vector_const_iterator(_vector_iterator<_Tp> __itr)
            : _M_data_ptr(__itr._M_data_ptr) {}

        _vector_const_iterator(pointer __p)
            : _M_data_ptr(__p) {}

        pointer _M_data_ptr;
    };

    template <typename _Tp, typename _Alloc = ustl::allocator<_Tp>>
    class vector
    {
    public:
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;
        typedef diff_t difference_type;
        typedef size_t size_type;

        typedef _Alloc allocator_type;
        typedef ustl::normal_iterator<_vector_iterator<_Tp>> iterator;
        typedef ustl::normal_iterator<_vector_const_iterator<_Tp>> const_iterator;
        typedef ustl::reverse_iterator<iterator> reverse_iterator;
        typedef ustl::reverse_iterator<const_iterator> const_reverse_iterator;

        typedef allocate_traits<_Alloc> _Tp_alloc_traits;

    private:
        bool
        _M_check_overflow(size_t __idx)
        {
            return __idx < size();
        }
        size_type
        _M_check_length(size_type __n)
        {
            if (_M_max_size() - size() < __n)
                __ustl_throw_array_length();
            size_type __new_len = size() + (size() > __n ? size() : __n);
            return __new_len < _M_max_size() ? __new_len : _M_max_size();
        }

        allocator_type &
        _M_get_allocator()
        {
            return _M_data_plus;
        }

        pointer
        _M_allocate(size_t __n)
        {
            return _Tp_alloc_traits::allocate(_M_get_allocator(), __n);
        }

        void
        _M_deallocate(pointer __ptr, size_type __len)
        {
            _Tp_alloc_traits::deallocate(_M_get_allocator(),
                                         __ptr, __len);
        }

        size_type
        _M_max_size()
        {
            return _Tp_alloc_traits::max_size(_M_get_allocator());
        }

        void _M_default_append(size_type); // append element on default state
        void _M_fll_assgin(size_type, value_type const &);
        void _M_fill_insert(iterator, size_type, value_type const &);

        void _M_insert_rval(iterator, value_type &&);                             // insert rvalue
        template <typename _Args>                                                 //
        void _M_insert_aux(iterator, _Args &&);                                   // normal insert
        template <typename... _Args>                                              //
        void _M_emplace_aux(const_iterator, _Args &&...);                         //
        template <typename _ForwardIterator>                                      //
        void _M_range_insert(const_iterator, _ForwardIterator, _ForwardIterator); // range [__first, __last) insert
        template <typename... _Args>                                              //
        void _M_realloc_insert(const_iterator, _Args &&...);                      // realloc memory and insert

        iterator _M_erase(iterator);
        size_type _M_erase(iterator, iterator);

    public:
        vector() = default;

        vector(vector const &__other)
        {
            assign(__other.begin(), __other.end());
        }

        vector(vector &&__other)
        {
            *this = ustl::move(__other);
        }

        template <typename _InputIterator>
        vector(_InputIterator __first, _InputIterator __last)
        {
            assign(__first, __last);
        }

    public:
        template <typename... _Args>
        inline iterator insert(const_iterator, _Args &&...);
        template <typename _ForwardIterator>
        inline iterator insert(const_iterator, _ForwardIterator, _ForwardIterator);
        inline iterator insert(const_iterator, value_type const &);

        inline void push_back(value_type const &);
        inline void push_front(value_type const &);
        inline void push_back(iterator);
        inline void push_front(iterator);

        template <typename... _Args>
        inline void emplace(const_iterator, _Args &&...);
        template <typename... _Args>
        inline void emplace_back(_Args &&...);
        template <typename... _Args>
        inline void emplace_front(_Args &&...);

        iterator erase(iterator);
        size_type erase(value_type const &);
        size_type erase(iterator, iterator);

        template <typename _Predicate>
        size_type remove_if(_Predicate);

        template <typename _Itr>
        inline void assign(_Itr, _Itr);

        inline void swap(vector &);
        inline void swap(vector &&);

        inline void clear();

        void resize(size_type);
        void resize(size_type, value_type const &);
        void reserve(size_type);

        void reverse();

        inline bool empty() ustl_cpp_noexcept;
        inline bool empty() const ustl_cpp_noexcept;

        inline size_t size() ustl_cpp_noexcept;
        inline size_t size() const ustl_cpp_noexcept;

        inline size_t capacity() ustl_cpp_noexcept;
        inline size_t capacity() const ustl_cpp_noexcept;

        inline iterator begin() ustl_cpp_noexcept;
        inline iterator end() ustl_cpp_noexcept;
        inline const_iterator cbegin() ustl_cpp_noexcept;
        inline const_iterator cend() ustl_cpp_noexcept;
        inline reverse_iterator rbegin() ustl_cpp_noexcept;
        inline reverse_iterator rend() ustl_cpp_noexcept;
        inline const_reverse_iterator crbegin() ustl_cpp_noexcept;
        inline const_reverse_iterator crend() ustl_cpp_noexcept;

        inline const_iterator begin() const ustl_cpp_noexcept;
        inline const_iterator end() const ustl_cpp_noexcept;
        inline const_iterator cbegin() const ustl_cpp_noexcept;
        inline const_iterator cend() const ustl_cpp_noexcept;
        inline const_reverse_iterator rbegin() const ustl_cpp_noexcept;
        inline const_reverse_iterator rend() const ustl_cpp_noexcept;
        inline const_reverse_iterator crbegin() const ustl_cpp_noexcept;
        inline const_reverse_iterator crend() const ustl_cpp_noexcept;

        inline reference operator[](size_t);
        inline const_reference operator[](size_t) const;
        vector &operator=(vector const &);
        vector &operator=(vector &&);

    protected:
        typedef _vec_impl<_Tp, _Alloc> impl_type;

        impl_type _M_data_plus;
    };

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
        insert(const_iterator __pos, value_type const &__val)
    {
        iterator __p = begin() + ustl::distance(cbegin(), __pos);
        if (_M_data_plus._M_end != _M_data_plus._M_storage)
            if (cend() == __pos)
                ustl::constructor(_M_data_plus._M_storage++, 1,
                                  __val);
            else
                _M_insert_aux(__p, __val);
        else
            _M_realloc_insert(__p, __val);
        return __p;
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
        insert(const_iterator __pos, _Args &&...__a)
    {
        if (_M_data_plus._M_end != _M_data_plus._M_storage)
            if (cend() == __pos)
                ustl::constructor(_M_data_plus._M_storage++, 1,
                                  ustl::forward<_Args &&>(__a)...);
            else
                _M_emplace_aux(__pos, ustl::forward<_Args &&>(__a)...);
        else
            _M_realloc_insert(__pos, ustl::forward<_Args &&>(__a)...);
        return begin() + ustl::distance(cbegin(), __pos);
    }

    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
        insert(const_iterator __pos, _ForwardIterator __first,
               _ForwardIterator __last)
    {
        _M_range_insert(__pos, __first, __last);
        return begin() + ustl::distance(cbegin(), __pos);
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        push_back(value_type const &__val)
    {
        if (_M_data_plus._M_end != _M_data_plus._M_storage)
            ustl::constructor(_M_data_plus._M_storage++, 1, __val);
        else
            _M_realloc_insert(cend(), __val);
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        push_front(value_type const &__val)
    {
        if (_M_data_plus._M_end != _M_data_plus._M_storage)
            _M_insert_aux(begin(), __val);
        else
            _M_realloc_insert(cbegin(), __val);
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        push_back(iterator __itr)
    {
        if (_M_data_plus._M_end != _M_data_plus._M_storage)
            ustl::constructor(_M_data_plus._M_storage++, 1, ustl::move(*__itr));
        else
            _M_realloc_insert(end(), ustl::move(*__itr));
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        push_front(iterator __itr)
    {
        if (_M_data_plus._M_end != _M_data_plus._M_storage)
            _M_insert_aux(begin(), ustl::move(*__itr));
        else
            _M_realloc_insert(begin(), ustl::move(*__itr));
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    void
    vector<_Tp, _Alloc>::
        emplace(const_iterator __pos, _Args &&...__a)
    {
        if (_M_data_plus._M_end != _M_data_plus._M_storage)
            if (cend() == __pos)
                ustl::constructor(_M_data_plus._M_storage++, 1,
                                  ustl::forward<_Args &&>(__a)...);
            else
                _M_emplace_aux(__pos, ustl::forward<_Args &&>(__a)...);
        else
            _M_realloc_insert(__pos, ustl::forward<_Args &&>(__a)...);
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    void
    vector<_Tp, _Alloc>::
        emplace_back(_Args &&...__a)
    {
        if (_M_data_plus._M_end != _M_data_plus._M_storage)
            ustl::constructor(_M_data_plus._M_storage++, 1,
                              ustl::forward<_Args &&>(__a)...);
        else
            _M_realloc_insert(cend(), ustl::forward<_Args &&>(__a)...);
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    void
    vector<_Tp, _Alloc>::
        emplace_front(_Args &&...__a)
    {
        if (_M_data_plus._M_end != _M_data_plus._M_storage)
            _M_emplace_aux(cbegin(), ustl::forward<_Args &&>(__a)...);
        else
            _M_realloc_insert(cbegin(), ustl::forward<_Args &&>(__a)...);
    }

    template <typename _Tp, typename _Alloc>
    auto
    vector<_Tp, _Alloc>::
        erase(iterator __pos) -> iterator
    {
        _M_erase(__pos);
        return __pos;
    }

    template <typename _Tp, typename _Alloc>
    size_t
    vector<_Tp, _Alloc>::
        erase(value_type const &__val)
    {
        size_type __old_size = size();
        iterator __first = begin();
        while (__first != end())
        {
            if (__val == *__first)
                _M_erase(__first);
            else
                ++__first;
        }
        return __old_size - size();
    }

    template <typename _Tp, typename _Alloc>
    size_t
    vector<_Tp, _Alloc>::
        erase(iterator __first, iterator __last)
    {
        return _M_erase(__first, __last);
    }

    template <typename _Tp, typename _Alloc>
    template <typename _CompPredicate>
    size_t
    vector<_Tp, _Alloc>::
        remove_if(_CompPredicate __cmp)
    {
        size_type __old_size = size();
        iterator __first = begin();
        while (__first != end())
        {
            if (__cmp(*__first))
                _M_erase(__first);
            else
                ++__first;
        }
        return __old_size - size();
    }

    template <typename _Tp, typename _Alloc>
    bool
    vector<_Tp, _Alloc>::
        empty() ustl_cpp_noexcept
    {
        return _M_data_plus._M_begin == _M_data_plus._M_storage;
    }

    template <typename _Tp, typename _Alloc>
    bool
    vector<_Tp, _Alloc>::
        empty() const ustl_cpp_noexcept
    {
        return _M_data_plus._M_begin == _M_data_plus._M_storage;
    }

    template <typename _Tp, typename _Alloc>
    size_t
    vector<_Tp, _Alloc>::
        size() ustl_cpp_noexcept
    {
        return _M_data_plus._M_element_count();
    }

    template <typename _Tp, typename _Alloc>
    size_t
    vector<_Tp, _Alloc>::
        size() const ustl_cpp_noexcept
    {
        return _M_data_plus._M_element_count();
    }

    template <typename _Tp, typename _Alloc>
    size_t
    vector<_Tp, _Alloc>::
        capacity() ustl_cpp_noexcept
    {
        return _M_data_plus._M_end - _M_data_plus._M_begin;
    }

    template <typename _Tp, typename _Alloc>
    size_t
    vector<_Tp, _Alloc>::
        capacity() const ustl_cpp_noexcept
    {
        return _M_data_plus._M_end - _M_data_plus._M_begin;
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        swap(vector &__other)
    {
        _M_data_plus._M_swap(__other._M_data_plus);
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        swap(vector &&__other)
    {
        _M_data_plus._M_move_data(ustl::move(__other));
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        clear()
    {
        pointer __tmp = _M_data_plus._M_begin;
        /**
         *  the object`s destructor must be invoked,
         *otherwise, a memory leak may occur
         */
        ustl::destructor(__tmp, _M_data_plus._M_storage - __tmp);
        _M_deallocate(_M_data_plus._M_begin,
                      _M_data_plus._M_end - _M_data_plus._M_begin);
        _M_data_plus._M_amend(0, 0, 0);
    }

    template <typename _Tp, typename _Alloc>
    template <typename _Itr>
    void
    vector<_Tp, _Alloc>::
        assign(_Itr __first, _Itr __last)
    {
        size_type __distance = ustl::distance(__first, __last);
        if (_M_data_plus._M_end - _M_data_plus._M_begin > __distance)
        {
            ustl::copy_forward(__first, __last, _M_data_plus._M_begin);
            _M_data_plus._M_storage = _M_data_plus._M_begin + __distance;
        }
        else
        {
            size_type __len = _M_check_length(__distance);
            pointer __new_begin = _M_allocate(__len);
            pointer __new_storage = __new_begin;
            __ustl_try
            {
                ustl::copy_forward(__first, __last, __new_begin);
            }
            __ustl_catch_all
            {
                ustl::destructor(__new_begin, __distance);
                _M_deallocate(__new_begin, __len);
                __ustl_throw_again;
            }
            _M_data_plus._M_amend(__new_begin, __distance, __len);
        }
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        resize(size_type __n)
    {
        if (__n > size())
            _M_default_append(__n - size());
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        resize(size_type __n, value_type const &__val)
    {
        if (__n > size())
            _M_fill_insert(end(), __n, __val);
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        reserve(size_type __n)
    {
        if (__n > capacity())
        {
            pointer __new_begin = _M_allocate(__n);
            __ustl_try
            {
                ustl::relocate_forward(_M_data_plus._M_begin,
                                       _M_data_plus._M_storage,
                                       __new_begin,
                                       _M_get_allocator());
            }
            __ustl_catch_all
            {
                ustl::destructor(__new_begin, size());
                _M_deallocate(__new_begin, __n);
                __ustl_throw_again;
            }
            _M_data_plus._M_amend(__new_begin, size(), __n);
        }
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        reverse()
    {
        reverse_iterator __first = rbegin();
        reverse_iterator __last = rend();
        vector __tmp(++__first, ++__last);
        swap(__tmp);
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
        begin() ustl_cpp_noexcept
    {
        return iterator(_M_data_plus._M_begin);
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_iterator
    vector<_Tp, _Alloc>::
        begin() const ustl_cpp_noexcept
    {
        return const_iterator(_M_data_plus._M_begin);
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
        end() ustl_cpp_noexcept
    {
        return iterator(_M_data_plus._M_storage);
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_iterator
    vector<_Tp, _Alloc>::
        end() const ustl_cpp_noexcept
    {
        return const_iterator(_M_data_plus._M_storage);
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_iterator
    vector<_Tp, _Alloc>::
        cbegin() ustl_cpp_noexcept
    {
        return const_iterator(_M_data_plus._M_begin);
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_iterator
    vector<_Tp, _Alloc>::
        cbegin() const ustl_cpp_noexcept
    {
        return const_iterator(_M_data_plus._M_begin);
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_iterator
    vector<_Tp, _Alloc>::
        cend() ustl_cpp_noexcept
    {
        return const_iterator(_M_data_plus._M_storage);
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_iterator
    vector<_Tp, _Alloc>::
        cend() const ustl_cpp_noexcept
    {
        return const_iterator(_M_data_plus._M_storage);
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::reverse_iterator
    vector<_Tp, _Alloc>::
        rbegin() ustl_cpp_noexcept
    {
        return reverse_iterator(end());
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::reverse_iterator
    vector<_Tp, _Alloc>::
        rend() ustl_cpp_noexcept
    {
        return reverse_iterator(begin());
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_reverse_iterator
    vector<_Tp, _Alloc>::
        rbegin() const ustl_cpp_noexcept
    {
        return const_reverse_iterator(cend());
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_reverse_iterator
    vector<_Tp, _Alloc>::
        rend() const ustl_cpp_noexcept
    {
        return const_reverse_iterator(cbegin());
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_reverse_iterator
    vector<_Tp, _Alloc>::
        crbegin() ustl_cpp_noexcept
    {
        return const_reverse_iterator(cend());
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_reverse_iterator
    vector<_Tp, _Alloc>::
        crend() ustl_cpp_noexcept
    {
        return const_reverse_iterator(cbegin());
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_reverse_iterator
    vector<_Tp, _Alloc>::
        crbegin() const ustl_cpp_noexcept
    {
        return const_reverse_iterator(cend());
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_reverse_iterator
    vector<_Tp, _Alloc>::
        crend() const ustl_cpp_noexcept
    {
        return const_reverse_iterator(cbegin());
    }

    template <typename _Tp, typename _Alloc>
    _Tp &
    vector<_Tp, _Alloc>::
    operator[](size_t __idx)
    {
        if (_M_check_overflow(__idx))
            return *(_M_data_plus._M_begin + __idx);
        __ustl_throw_out_of_range("vector.operator[]: index out of the overlaps");
    }

    template <typename _Tp, typename _Alloc>
    _Tp const &
    vector<_Tp, _Alloc>::
    operator[](size_t __idx) const
    {
        if (_M_check_overflow(__idx))
            return *(_M_data_plus._M_begin + __idx);
        __ustl_throw_out_of_range("vector.operator[]: index out of the overlaps");
    }

    template <typename _Tp, typename _Alloc>
    auto
    vector<_Tp, _Alloc>::
    operator=(vector const &__other) -> vector &
    {
        if (this != &__other)
            assign(__other.begin(), __other.end());
        return *this;
    }

    template <typename _Tp, typename _Alloc>
    auto
    vector<_Tp, _Alloc>::
    operator=(vector &&__other) -> vector &
    {
        if (&__other != this)
        {
            clear();
            _M_data_plus._M_move_data(__other._M_data_plus);
        }
        return *this;
    }

    template <typename _Tp, typename _Alloc>
    bool
    operator==(ustl::vector<_Tp, _Alloc> const &__l,
               ustl::vector<_Tp, _Alloc> const &__r)
    {
        typedef typename ustl::vector<_Tp, _Alloc>::const_iterator iterator;
        iterator __first1 = __l.begin();
        iterator __last1 = __l.end();
        iterator __first2 = __r.begin();
        iterator __last2 = __r.end();
        while (__first1 != __last1 && __first2 != __last2 &&
               *__first1 == *__first2)
        {
            ++__first1, (void)++__first2;
        }
        return __first1 == __last1 && __first2 == __last2;
    }

    template <typename _Tp, typename _Alloc>
    inline bool
    operator!=(vector<_Tp, _Alloc> const &__l,
               vector<_Tp, _Alloc> const &__r)
    {
        return !__l == __r;
    }

    template <typename _Tp, typename _Alloc>
    bool
    operator<=(vector<_Tp, _Alloc> const &__l,
               vector<_Tp, _Alloc> const &__r)
    {
        typedef typename ustl::vector<_Tp, _Alloc>::const_iterator iterator;
        iterator __first1 = __l.begin();
        iterator __last1 = __l.end();
        iterator __first2 = __r.begin();
        iterator __last2 = __r.end();
        while (__first1 != __last1 && __first2 != __last2 &&
               *__first1 == *__first2)
        {
            ++__first1, (void)++__first2;
        }
        if ((__first1 == __last1 && __first2 == __last2) ||
            (__first1 != __last1 && __first2 == __last2) ||
            *__first1 < *__first2)
            return true;
        return false;
    }

    template <typename _Tp, typename _Alloc>
    inline bool
    operator>(vector<_Tp, _Alloc> const &__l,
              vector<_Tp, _Alloc> const &__r)
    {
        return !__l <= __r;
    }
}

/**
 * vector interanl member fucntion implement
 */

namespace ustl
{
    template <typename _Tp, typename _Alloc>
    template <typename _Arg>
    void
    vector<_Tp, _Alloc>::
        _M_insert_aux(iterator __pos,
                      _Arg &&__val)
    {
        iterator __last = end();
        ++_M_data_plus._M_storage;
        ustl::relocate_back(__pos, __last,
                            _M_data_plus._M_storage,
                            _M_get_allocator());
        *__pos = ustl::forward<_Arg &&>(__val);
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    void
    vector<_Tp, _Alloc>::
        _M_emplace_aux(const_iterator __pos,
                       _Args &&...__val)
    {
        iterator __last = end();
        ++_M_data_plus._M_storage;
        iterator __ist_pos = begin() + ustl::distance(cbegin(), __pos);
        ustl::relocate_back(__ist_pos, __last,
                            _M_data_plus._M_storage,
                            _M_get_allocator());

        ustl::constructor(&*__ist_pos, 1, ustl::forward<_Args &&>(__val)...);
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        _M_insert_rval(iterator __pos,
                       value_type &&__rval)
    {
        iterator __last = end();
        ++_M_data_plus._M_storage;
        ustl::relocate_back(__pos, __last,
                            _M_data_plus._M_storage,
                            _M_get_allocator());
        ustl::constructor(&*__pos, 1, ustl::move(__rval));
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        _M_fill_insert(iterator __pos,
                       size_type __n,
                       value_type const &__val)
    {
        pointer __pos_ptr = &*__pos;

        if (_M_data_plus._M_end - _M_data_plus._M_storage >= __n)
        {
            ustl::copy_back(__pos_ptr,
                            _M_data_plus._M_storage,
                            _M_data_plus._M_storage + __n);
            ustl::fill(__pos_ptr, __pos_ptr + __n, __val);
        }
        else
        {
            size_type __old_size = size();
            size_type __len = _M_check_length(__n);
            pointer __new_begin = _M_allocate(__len);
            pointer __new_storage = __new_begin;
            difference_type __distance = ustl::distance(begin(), __pos);
            __ustl_try
            {
                /**
                 * catch constructor exception
                 */
                ustl::copy_back(begin(), __pos, __new_storage);
                ustl::fill(__new_storage + __distance,
                           __new_storage + __distance + __n, __val);
                ustl::copy_back(__pos, end(), __new_storage + __distance + __n);
            }
            __ustl_catch_all
            {
                ustl::destructor(__new_begin, __new_storage - __new_begin);
                _M_deallocate(__new_begin, __len);
                __ustl_throw_again;
            }
            _M_deallocate(_M_data_plus._M_begin,
                          _M_data_plus._M_end - _M_data_plus._M_begin);
            _M_data_plus._M_amend(__new_begin, __old_size + __n, __len);
        }
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    void
    vector<_Tp, _Alloc>::
        _M_realloc_insert(const_iterator __pos,
                          _Args &&...__a)
    {
        size_type __old_size = size();
        size_type __len = _M_check_length(size_type(1));
        pointer __new_begin = _M_allocate(__len);
        pointer __new_storage{__new_begin};

        iterator __first = begin();
        iterator __last = end();
        size_type __distance = ustl::distance(cbegin(), __pos);
        __ustl_try
        {
            __new_storage += __distance;
            iterator __ist_pos = __first + __distance;
            ustl::copy_forward(__ist_pos, __last, __new_storage + 1);
            _Tp_alloc_traits::construct(_M_get_allocator(),
                                        __new_storage,
                                        forward<_Args &&>(__a)...);
            ustl::copy_back(__first, __ist_pos, __new_storage);
        }
        __ustl_catch_all
        {
            ustl::destructor(__new_begin, __old_size + 1);
            _M_deallocate(__new_begin, __len);
            __ustl_throw_again;
        }
        _M_deallocate(_M_data_plus._M_begin, __old_size);
        _M_data_plus._M_amend(__new_begin, __old_size + 1, __len);
    }

    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    void
    vector<_Tp, _Alloc>::
        _M_range_insert(const_iterator __pos,
                        _ForwardIterator __first,
                        _ForwardIterator __last)
    {
        size_type __distance = ustl::distance(__first, __last);
        size_type __ele_before = ustl::distance(cbegin(), __pos);
        size_type __old_size = size();
        iterator __ist_pos = begin() + ustl::distance(cbegin(), __pos);
        if (__distance)
        {
            if (_M_data_plus._M_end - _M_data_plus._M_storage >= __distance) // move data
            {
                iterator __last = end();
                _M_data_plus._M_storage += __distance;
                ustl::relocate_back(__ist_pos, end(),
                                    _M_data_plus._M_storage,
                                    _M_get_allocator());
                ustl::copy_forward(__first, __last, __ist_pos);
            }
            else // realloc
            {
                size_type __len = _M_check_length(size_type(__distance));
                pointer __new_begin = _M_allocate(__len);
                pointer __new_storage = __new_begin;
                ustl::relocate_forward(_M_data_plus._M_begin,
                                       _M_data_plus._M_begin + __ele_before,
                                       __new_storage,
                                       _M_get_allocator());
                ustl::copy_forward(__first, __last,
                                   __new_storage + __ele_before);
                ustl::relocate_forward(__ist_pos, end(),
                                       __new_storage + __ele_before + __distance,
                                       _M_get_allocator());
                _M_data_plus._M_amend(__new_begin, __distance + __old_size, __len);
            }
        }
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        _M_default_append(size_type __n)
    {
        if (_M_data_plus._M_end - _M_data_plus._M_storage >= __n)
        {
            pointer __old_storage = _M_data_plus._M_storage;
            size_type __counter = __n;
            __ustl_try
            {
                ustl::constructor(_M_data_plus._M_storage, __n);
            }
            __ustl_catch_all
            {
                ustl::destructor(_M_data_plus._M_storage, __counter - __n);
                __ustl_throw_again;
            }
            _M_data_plus._M_storage += __n;
        }
        else
        {
            size_type __len = _M_check_length(__n);
            pointer __new_begin = _M_allocate(__len);
            pointer __new_storage = __new_begin + size();
            ustl::copy_forward(begin(), end(), __new_begin);
            size_type __counter = __n;
            __ustl_try
            {
                ustl::constructor(__new_storage, __n);
            }
            __ustl_catch_all
            {
                ustl::destructor(__new_storage, __counter - __n);
                _M_deallocate(__new_begin, __len);
                __ustl_throw_again;
            }
            _M_data_plus._M_amend(__new_begin, __counter + size(), __len);
        }
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        _M_fll_assgin(size_type __n,
                      value_type const &__val)
    {
        if (_M_data_plus._M_end - _M_data_plus._M_storage >= __n)
        {
            pointer __old_storage = _M_data_plus._M_storage;
            __ustl_try
            {
                ustl::constructor(_M_data_plus._M_storage, __n, __val);
            }
            __ustl_catch_all
            {
                pointer __new_storage = __old_storage;
                ustl::destructor(__old_storage, _M_data_plus._M_storage - __old_storage);
                _M_data_plus._M_storage = __new_storage;
                __ustl_throw_again;
            }
        }
        else
        {
            size_type __len = _M_check_length(__n);
            pointer __new_begin = _M_allocate(__len);
            pointer __new_storage = __new_begin;
            ustl::copy_forward(begin(), end(), __new_begin);
            size_type __counter = __n;
            __ustl_try
            {
                ustl::constructor(__new_storage, __n, __val);
            }
            __ustl_catch_all
            {
                ustl::destructor(__new_storage, __counter - __n);
                _M_deallocate(__new_begin, __len);
                __ustl_throw_again;
            }
            _M_data_plus._M_amend(__new_begin, __counter + size(), __len);
        }
    }

    template <typename _Tp, typename _Alloc>
    auto
    vector<_Tp, _Alloc>::
        _M_erase(iterator __pos) -> iterator
    {
        pointer __del = &*__pos;
        _Tp_alloc_traits::destory(_M_get_allocator(), __del);
        ustl::copy_forward(__del + 1, _M_data_plus._M_storage, __del);
        --_M_data_plus._M_storage;
        return __pos;
    }

    template <typename _Tp, typename _Alloc>
    size_t
    vector<_Tp, _Alloc>::
        _M_erase(iterator __first, iterator __last)
    {
        pointer __del_first = &*__first;
        pointer __del_last = &*__last;
        pointer __tmp = __del_first;
        size_type __dis = 0;
        for (; __del_first != __del_last; ++__del_first, ++__dis)
            _Tp_alloc_traits::destory(_M_get_allocator(), __del_first);
        ustl::copy_forward(__del_last, _M_data_plus._M_storage, __tmp);
        _M_data_plus._M_storage -= __dis;
        return __dis;
    }

}

#endif