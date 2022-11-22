#ifndef __basic_string_h
#define __basic_string_h

namespace ustl
{
    template <typename _CharT, typename _Alloc>
    struct basic_string_impl
        : _Alloc
    {
        typedef _CharT value_type;
        typedef _CharT *pointer;
        typedef _CharT &reference;
        typedef size_t size_type;

        void
        _M_move(basic_string_impl &__other)
        {
            _M_actual_data = __other._M_actual_data;
            __other._M_actual_data = 0;
        }

        void
        _M_swap(basic_string_impl &__other)
        {
            basic_string_impl __tmp(*this);
            _M_move(__other);
            __other._M_move(__tmp);
        }

        void
        _M_copy(basic_string_impl const &__other)
        {
            _M_actual_data = __other._M_actual_data;
            _M_add_sharer();
        }

        void
        _M_add_sharer(size_type __number = 1)
        {
#if defined(__ustl_lib) && __ustl_lib == 20221018UL
            /** bus lock for atomic operation */
            asm volatile("lock add  %1, %0\n\t"
                         : "=m"(_M_ref_count)
                         : "ir"(__number));

#endif
        }

        void
        _M_rmv_sharer(size_type __number = 1)
        {
#if defined(__ustl_lib) && __ustl_lib == 20221018UL
            /** bus lock for atomic operation */
            asm volatile("lock sub  %1, %0\n\t"
                         : "=m"(_M_ref_count)
                         : "ir"(__number));

#endif
        }

        basic_string_impl()
            : _M_actual_data(0), _M_ref_count(1) {}

        ~basic_string_impl() { _M_rmv_sharer(); }

        size_type _M_ref_count;
        pointer _M_actual_data;
    };

    template <typename _CharT, typename _Alloc>
    class basic_string
    {
        typedef allocate_traits<_Alloc> _Alloc_traits;

    public:
        typedef _CharT value_type;
        typedef _CharT *pointer;
        typedef _CharT &reference;
        typedef _CharT const *const_pointer;
        typedef _CharT const &const_reference;

        typedef size_t size_type;
        typedef diff_t difference_type;
        typedef _Alloc allocator_type;

        typedef ustl::normal_iterator<pointer> iterator;
        typedef ustl::normal_iterator<const_pointer> const_iterator;
        typedef ustl::reverse_iterator<pointer> reverse_iterator;
        typedef ustl::reverse_iterator<const_pointer> const_reverse_iterator;

        typedef char_traits<_CharT> _CharT_traits;

        enum
        {
            _S_EOF = -1
        };

        /** constructor */
    public:
        basic_string()
            : _M_data_length(0)
        {
            _M_data_plus._M_actual_data = _M_stack_buf;
            _M_data_plus._M_ref_count = 1;
        }

        basic_string(basic_string const &__other)
            : basic_string(__other.data(), __other.size()) {}

        basic_string(const_pointer __str)
            : basic_string()
        {
            assign(__str);
        }

        template <typename _InputIterator>
        basic_string(_InputIterator __first, _InputIterator __last)
            : basic_string()
        {
            _M_construct(__first, __last);
        }

        ~basic_string()
        {
            clear();
        }

    private:
        pointer
        _M_allocate(size_type &__n) ustl_cpp_noexcept { return _Alloc_traits::allocate(_M_data_plus, __n); }

        void
        _M_deallocate(pointer __p, size_type __n) ustl_cpp_noexcept { _Alloc_traits::deallocate(_M_data_plus, __p, __n); }

        void
        _M_destory(pointer __p, size_type __n) ustl_cpp_noexcept { ustl::destructor(__p, __n); }

        void
        _M_set_data(pointer __p) ustl_cpp_noexcept { _M_data_plus._M_actual_data = __p; }

        void
        _M_set_len(size_type __new_len) ustl_cpp_noexcept { _M_data_length = __new_len; }

        void
        _M_set_capacity(size_type __capacity) ustl_cpp_noexcept { _M_allocated_length = __capacity; }

        pointer
        _M_data() ustl_cpp_noexcept { return _M_data_plus._M_actual_data; }

        pointer
        _M_data_last() ustl_cpp_noexcept { return _M_data_plus._M_actual_data + _M_data_length; }

        pointer
        _M_local_data() ustl_cpp_noexcept { return static_cast<pointer>(_M_stack_buf); }

        bool
        _M_shared_data() { return 1 != _M_data_plus._M_ref_count; }

        bool
        _M_data_is_local() ustl_cpp_noexcept { return _M_data() == _M_local_data(); }

        /// @interface 维护接口一致性，减少重构压力
        static bool
        _S_comp(value_type const __l, value_type const __r) ustl_cpp_noexcept { return _CharT_traits::equal(__l, __r); }

        static size_type
        _S_strlen(const_pointer __str) ustl_cpp_noexcept { return _CharT_traits::length(__str); }

        static int
        _S_compare(const_pointer __l, const_pointer __r, size_type __len) { return _CharT_traits::compare(__l, __r, __len); }

        static void
        _S_assign(const_reference __s, reference __d) { _CharT_traits::assign(__s, __d); }

        static void
        _S_copy(const_pointer __s, pointer __d, size_type __len) { _CharT_traits::copy(__s, __d, __len); }

    public:
        pointer
        data() ustl_cpp_noexcept { return _M_data_plus._M_actual_data; }

        const_pointer
        data() const ustl_cpp_noexcept { return _M_data_plus._M_actual_data; }

        reference
        front() ustl_cpp_noexcept { return *_M_data_plus._M_actual_data; }

        reference
        back() ustl_cpp_noexcept { return *(_M_data_plus._M_actual_data + _M_data_length - 1); }

        const_reference
        front() const ustl_cpp_noexcept { return *_M_data_plus._M_actual_data; }

        const_reference
        back() const ustl_cpp_noexcept { return *(_M_data_plus._M_actual_data + _M_data_length - 1); }

        iterator
        begin() ustl_cpp_noexcept { return iterator(_M_data_plus._M_actual_data); }

        iterator
        end() ustl_cpp_noexcept { return iterator(_M_data_plus._M_actual_data + _M_data_length); }

        const_iterator
        begin() const ustl_cpp_noexcept { return const_iterator(_M_data_plus._M_actual_data); }

        const_iterator
        end() const ustl_cpp_noexcept { return const_iterator(_M_data_plus._M_actual_data + _M_data_length); }

        const_iterator
        cbegin() ustl_cpp_noexcept { return const_iterator(_M_data_plus._M_actual_data); }

        const_iterator
        cend() ustl_cpp_noexcept { return const_iterator(_M_data_plus._M_actual_data + _M_data_length); }

        const_iterator
        cbegin() const ustl_cpp_noexcept { return const_iterator(_M_data_plus._M_actual_data); }

        const_iterator
        cend() const ustl_cpp_noexcept { return const_iterator(_M_data_plus._M_actual_data + _M_data_length); }

        reverse_iterator
        rbegin() ustl_cpp_noexcept { return reverse_iterator(_M_data_plus._M_actual_data + _M_data_length); }

        reverse_iterator
        rend() ustl_cpp_noexcept { return reverse_iterator(_M_data_plus._M_actual_data); }

        const_reverse_iterator
        rbegin() const ustl_cpp_noexcept { return const_reverse_iterator(_M_data_plus._M_actual_data + _M_data_length); }

        const_reverse_iterator
        rend() const ustl_cpp_noexcept { return const_reverse_iterator(_M_data_plus._M_actual_data); }

        const_reverse_iterator
        crbegin() ustl_cpp_noexcept { return const_reverse_iterator(_M_data_plus._M_actual_data + _M_data_length); }

        const_reverse_iterator
        crend() ustl_cpp_noexcept { return const_reverse_iterator(_M_data_plus._M_actual_data); }

        const_reverse_iterator
        crbegin() const ustl_cpp_noexcept { return const_reverse_iterator(_M_data_plus._M_actual_data + _M_data_length); }

        const_reverse_iterator
        crend() const ustl_cpp_noexcept { return const_reverse_iterator(_M_data_plus._M_actual_data); }

        bool
        empty() ustl_cpp_noexcept { return 0 == _M_data_length; }

        bool
        empty() const ustl_cpp_noexcept { return 0 == _M_data_length; }

        size_type
        size() ustl_cpp_noexcept { return _M_data_length; }

        size_type
        size() const ustl_cpp_noexcept { return _M_data_length; }

        size_type
        capacity() ustl_cpp_noexcept { return _M_data_is_local() ? _S_stack_buffer_size : _M_allocated_length; }

        size_type
        capacity() const ustl_cpp_noexcept { return _M_data_is_local() ? _S_stack_buffer_size : _M_allocated_length; }

    private:
        template <typename _InputIterator>
        void _M_construct(_InputIterator, _InputIterator);
        void _M_append(const_pointer, size_type = 1);
        void _M_replace(size_type, size_type, const_pointer, size_type);
        void _M_replace_aux(size_type, size_type, value_type, size_type = 1);
        template <typename _ForwardIterator>
        void _M_replace_copy(const_iterator, const_iterator, _ForwardIterator, _ForwardIterator);
        void _M_erase(size_type, size_type);
        void _M_amend(const_pointer, size_type, const_pointer, size_type, size_type);
        size_type _M_check_length(size_type __len);

    public:
        inline basic_string &append(basic_string const &);
        inline basic_string &append(const_pointer);
        inline basic_string &append(value_type const, size_type = 1);

        inline basic_string &replace(size_type, size_type, value_type const, size_type);
        inline basic_string &replace(size_type, size_type, const_pointer, size_type);
        inline basic_string &replace(size_type, size_type, basic_string const &);
        inline basic_string &replace(const_iterator, const_iterator, value_type const);
        inline basic_string &replace(const_iterator, const_iterator, const_pointer);
        inline basic_string &replace(const_iterator, const_iterator, basic_string const &);
        template <typename _InputIterator>
        basic_string &replace(const_iterator, const_iterator, _InputIterator, _InputIterator);

        inline iterator insert(size_type, value_type const, size_type);
        inline iterator insert(size_type, const_pointer);
        inline iterator insert(size_type, basic_string const &);
        inline iterator insert(const_iterator, value_type const, size_type);
        inline iterator insert(const_iterator, const_pointer);
        inline iterator insert(const_iterator, basic_string const &);
        template <typename _InputIterator>
        inline iterator insert(const_iterator, _InputIterator, _InputIterator);
        template <typename _InputIterator>
        inline iterator insert(size_type, _InputIterator, _InputIterator);

        inline void push_back(value_type const, size_type = 1);
        inline void push_back(const_pointer);
        inline void push_back(basic_string const &);

        /** 1 : start pos     2 : erase counter */
        void erase(const_iterator);
        void erase(const_iterator, const_iterator);
        void erase(size_type, size_type);

        size_type find(value_type const, size_type = 0) ustl_cpp_noexcept;
        size_type find(const_pointer, size_type = 0) ustl_cpp_noexcept;
        inline size_type find(basic_string const &, size_type = 0) ustl_cpp_noexcept;

        size_type rfind(value_type const, size_type = 0) ustl_cpp_noexcept;
        size_type rfind(const_pointer, size_type = 0) ustl_cpp_noexcept;
        inline size_type rfind(basic_string const &, size_type = 0) ustl_cpp_noexcept;

        inline size_type find_last_of(value_type const, size_type = 0) ustl_cpp_noexcept;
        inline size_type find_last_of(const_pointer, size_type = 0) ustl_cpp_noexcept;
        inline size_type find_last_of(basic_string const &, size_type = 0) ustl_cpp_noexcept;
        inline size_type find_first_of(value_type const, size_type = 0) ustl_cpp_noexcept;
        inline size_type find_first_of(const_pointer, size_type = 0) ustl_cpp_noexcept;
        inline size_type find_first_of(basic_string const &, size_type = 0) ustl_cpp_noexcept;

        int compare(const_pointer) const ustl_cpp_noexcept;
        inline int compare(basic_string const &) const ustl_cpp_noexcept;

        basic_string substr(size_type, size_type);

        inline void copy(pointer, size_type, size_type = 0) const;

        void swap(basic_string &);
        inline void swap(basic_string &&);

        void assign(value_type const, size_type);
        void assign(const_pointer);
        void assign(basic_string const &);
        template <typename _InputIterator>
        void assign(_InputIterator, _InputIterator);

        void reverse();

        void reserve(size_type);

        inline void resize(size_type);
        inline void resize(size_type, value_type const);

        inline void clear();

        /* just lvalue */
        /** assignment operator */
        basic_string &operator=(basic_string const &) &;
        basic_string &operator=(basic_string &&) &;

        basic_string &operator+=(basic_string const &) &;
        basic_string &operator+=(value_type const) &;
        basic_string &operator+=(const_pointer) &;
        /** just lvalue */

        inline reference operator[](size_type);
        inline const_reference operator[](size_type) const;

    protected:
        typedef basic_string_impl<value_type, allocator_type> impl_type;

        enum
        {
            _S_stack_buffer_size = 16 / sizeof(value_type)
        };

        /**
         * @if data is local
         *      use _M_stack_buf, end of string is '\0'
         * @else
         *      use _M_data_plus, end of string don`t storage '\0'
         */
        union
        {

            value_type _M_stack_buf[_S_stack_buffer_size];
            size_type _M_allocated_length;
        };

        size_type _M_data_length;
        impl_type _M_data_plus;
    };

} // namespace ustl

namespace ustl
{

    template <typename _CharT, typename _Alloc>
    template <typename _InputIterator>
    void
    basic_string<_CharT, _Alloc>::
        _M_construct(_InputIterator __first, _InputIterator __last)
    {
        size_type __len = ustl::distance(__first, __last);
        if (__len > capacity())
        {
            pointer __begin = _M_allocate(__len);
            _M_set_data(__begin);
            _M_set_capacity(__len);
        }
        ustl::copy_forward(__first, __last, data());
        _M_set_len(__len);
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        _M_check_length(size_type __len) -> size_type
    {
        size_type __old_capacity = capacity();
        if (__len > _Alloc_traits::max_size(_M_data_plus))
            __throw_array_length("basic_string::_M_check_length : size of requested memory overlaps");
        if (__len > __old_capacity && __len < (__old_capacity << 1))
            __len = __old_capacity << 1;
        return __len;
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        _M_amend(const_pointer __str, size_type __len,
                 const_pointer __str1, size_type __len1,
                 size_type __new_size)
    {
        size_type __old_capacity = capacity();
        size_type __retain = __new_size - __len - __len1;
        __new_size = _M_check_length(__new_size);
        pointer __new_begin = _M_allocate(__new_size);
        pointer __storage = __new_begin;

        if (__str && __len)
            _S_copy(__str, __storage, __len);
        __storage += (__len + __retain);
        if (__str1 && __len1)
            _S_copy(__str1, __storage, __len1);
        clear();
        _M_set_data(__new_begin);
        _M_set_capacity(__new_size);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        _M_replace_aux(size_type __pos, size_type __len1,
                       value_type __char, size_type __n)
    {
        size_type __new_size = size() + __n - __len1;
        size_type __move_len = size() - __pos;
        pointer __p = data() + __pos;

        if (__new_size <= capacity() && !_M_shared_data())
            _S_copy(__p + __len1, __p + __n, __move_len);
        else
            _M_amend(data(), __pos, __p + __n, __move_len, __new_size);
        __p = data();
        ustl::fill(__p + __pos, __p + __pos + __n, __char);
        _M_set_len(__new_size);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        _M_replace(size_type __pos, size_type __len1,
                   const_pointer __str, size_type __len2)
    {
        size_type __new_size = size() + __len2 - __len1;
        size_type __move_len = size() - __pos - __len1;
        pointer __p = data() + __pos;

        if (__new_size <= capacity() && !_M_shared_data())
            _S_copy(__p + __len1, __p + __len2, __move_len);
        else
            _M_amend(data(), __pos, __p + __len1, __move_len, __new_size);
        __p = data();
        _S_copy(__str, __p + __pos, __len2);
        _M_set_len(__new_size);
    }

    /** using iterator  */
    template <typename _CharT, typename _Alloc>
    template <typename _ForwardIterator>
    void
    basic_string<_CharT, _Alloc>::
        _M_replace_copy(const_iterator __first, const_iterator __last,
                        _ForwardIterator __frist1, _ForwardIterator __last1)
    {
        basic_string __tmp(__frist1, __last1);
        _M_replace(__first - cbegin(), __last - __first, __tmp.data(), __tmp.size());
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        _M_append(const_pointer __str, size_type __len)
    {
        size_type __old_size = size();
        size_type __new_size = __old_size + __len;
        if (__new_size <= capacity() && !_M_shared_data())
            _S_copy(__str, _M_data_last(), __len);
        else
            _M_amend(data(), size(), __str, __len, __new_size);
        _M_set_len(__new_size);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        _M_erase(size_type __pos, size_type __len)
    {
        size_type __move_len = size() - __pos - __len;
        if (__move_len && __len)
        {
            size_type __old_len = size();
            pointer __begin = data();
            pointer __result = __begin + __pos;
            pointer __last = __begin + __old_len;
            pointer __first = __last - __move_len;

            if (!_M_shared_data())
                _S_copy(__first, __result, __move_len);
            else
                _M_amend(__begin, __pos, __first, __move_len, capacity());

            _M_set_len(__old_len - __len);
        }
    }

} // namespace ustl::basic_string

namespace ustl
{

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        append(basic_string const &__other) -> basic_string &
    {
        _M_append(__other.data(), __other.size());
        return *this;
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        append(const_pointer __str) -> basic_string &
    {
        size_type __len = _S_strlen(__str);
        if (__len)
            _M_append(__str, __len);
        return *this;
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        append(value_type const __val, size_type __n) -> basic_string &
    {
        _M_replace_aux(size(), 0, __val, __n);
        return *this;
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        replace(size_type __pos, size_type __n,
                const_pointer __str, size_type __len1) -> basic_string &
    {
        _M_replace(__pos, __n, __str, __str + __len1, __len1);
        return *this;
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        replace(size_type __pos, size_type __n,
                value_type const __val, size_type __len) -> basic_string &
    {
        _M_replace_aux(__pos, __n, __val, __len);
        return *this;
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        replace(size_type __pos, size_type __n,
                basic_string const &__str) -> basic_string &
    {
        _M_replace(__pos, __n, __str.begin(), __str.end(), __str.size());
        return *this;
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        replace(const_iterator __first, const_iterator __last,
                value_type const __val) -> basic_string &
    {
        difference_type __pos = __first - cbegin();
        difference_type __dis = __last - __first;
        if (__dis)
            _M_replace_aux(__pos, __dis, __val);
        return *this;
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        replace(const_iterator __first, const_iterator __last,
                const_pointer __str) -> basic_string &
    {
        size_type __str_len = _S_strlen(__str);
        _M_replace_copy(__first, __last, __str, __str + __str_len);
        return *this;
    }

    template <typename _CharT, typename _Alloc>
    template <typename _InputIterator>
    auto
    basic_string<_CharT, _Alloc>::
        replace(const_iterator __first, const_iterator __last,
                _InputIterator __first1, _InputIterator __last1) -> basic_string &
    {
        _M_replace_copy(__first, __last, __first1, __last1);
        return *this;
    }

    template <typename _CharT, typename _Alloc>
    auto basic_string<_CharT, _Alloc>::
        insert(size_type __pos, value_type const __val,
               size_type __n) -> iterator
    {
        _M_replace_aux(__pos, 0, __val, __n);
        return iterator(begin() + __pos);
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        insert(size_type __pos, const_pointer __str) -> iterator
    {
        size_type __len = _S_strlen(__str);
        _M_replace(__pos, 0, __str, __str + __len, __len);
        return iterator(begin() + __pos);
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        insert(size_type __pos, basic_string const &__str) -> iterator
    {
        pointer __p = __str.data();
        size_type __size = __str.size();
        _M_replace(__pos, 0, __p, __p + __size, __size);
        return iterator(begin() + __pos);
    }

    template <typename _CharT, typename _Alloc>
    template <typename _InputIterator>
    auto
    basic_string<_CharT, _Alloc>::
        insert(size_type __pos, _InputIterator __first,
               _InputIterator __last) -> iterator
    {
        replace(cbegin() + __pos, cbegin() + __pos, __first, __last);
        return iterator(begin() + __pos);
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        insert(const_iterator __pos, value_type const __val,
               size_type __n) -> iterator
    {
        difference_type __dis = __pos - cbegin();
        return insert(__dis, __val, __n);
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        insert(const_iterator __pos, const_pointer __str) -> iterator
    {
        difference_type __dis = __pos - cbegin();
        return insert(__pos, __str);
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        insert(const_iterator __pos, basic_string const &__str) -> iterator
    {
        difference_type __dis = __pos - cbegin();
        pointer __p = __str.data();
        size_type __size = __str.size();
        _M_replace(__dis, 0, __p, __p + __size, __size);
        return iterator(begin() + __pos);
    }

    template <typename _CharT, typename _Alloc>
    template <typename _ForwardIterator>
    auto
    basic_string<_CharT, _Alloc>::
        insert(const_iterator __pos, _ForwardIterator __first,
               _ForwardIterator __last) -> iterator
    {
        difference_type __dis = __pos - cbegin();
        replace(__pos, __pos, __first, __last);
        return iterator(begin() + __dis);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        push_back(value_type const __val, size_type __n)
    {
        _M_replace_aux(size(), __val, __n);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        push_back(const_pointer __str)
    {
        size_type __len = _S_strlen(__str);
        _M_append(__str, __len);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        push_back(basic_string const &__str)
    {
        _M_append(__str.data(), __str.size());
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        erase(const_iterator __pos)
    {
        difference_type __dis = __pos - cbegin();
        if (__dis < size())
            _M_erase(__dis);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        erase(const_iterator __first, const_iterator __last)
    {
        difference_type __dis = __first - cbegin();
        difference_type __len = __last - __first;
        if (__dis < size() && __len)
            _M_erase(__dis, __len);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        erase(size_type __pos, size_type __count)
    {
        if (__pos < size() && __count)
            _M_erase(__pos, __count);
    }

    template <typename _CharT, typename _Alloc>
    typename basic_string<_CharT, _Alloc>::size_type
    basic_string<_CharT, _Alloc>::
        find(value_type const __val, size_type __pos)
            ustl_cpp_noexcept
    {
        const_iterator __first = cbegin() + __pos;
        const_iterator __last = cend();
        size_type __idx = 0;
        for (; __first != __last; ++__first, ++__idx)
            if (_S_comp(*__first, __val))
                return __idx;
        return size_type(_S_EOF);
    }

    template <typename _CharT, typename _Alloc>
    typename basic_string<_CharT, _Alloc>::size_type
    basic_string<_CharT, _Alloc>::
        find(const_pointer __val, size_type __pos)
            ustl_cpp_noexcept
    {
        const_iterator __first = cbegin() + __pos;
        const_iterator __last = cend();
        size_type __idx = 0;
        size_type __ret = 0;
        for (; __first != __last && 0 != __val[__ret];
             ++__first, (void)++__ret, (void)++__idx)
            if (!_S_comp(*__first, __val[__ret]))
                __ret = -1;

        return _S_comp(value_type(0), __val[__ret]) ? __idx - __ret : size_type(_S_EOF);
    }

    template <typename _CharT, typename _Alloc>
    typename basic_string<_CharT, _Alloc>::size_type
    basic_string<_CharT, _Alloc>::
        find(basic_string const &__val, size_type __pos)
            ustl_cpp_noexcept
    {
        return find(__val.data());
    }

    template <typename _CharT, typename _Alloc>
    typename basic_string<_CharT, _Alloc>::size_type
    basic_string<_CharT, _Alloc>::
        rfind(value_type const __val, size_type __pos)
            ustl_cpp_noexcept
    {
        reverse_iterator __rfirst = rbegin() + __pos;
        reverse_iterator __rend = rend();
        size_type __ret = size();
        for (; __rfirst != __rend; --__ret)
            if (_S_comp(*++__rfirst, __val))
                return __ret - 1;
        return size_type(_S_EOF);
    }

    template <typename _CharT, typename _Alloc>
    typename basic_string<_CharT, _Alloc>::size_type
    basic_string<_CharT, _Alloc>::
        rfind(const_pointer __val, size_type __pos)
            ustl_cpp_noexcept
    {
        reverse_iterator __first = rbegin() + __pos;
        reverse_iterator __last = rend();
        size_type __ret = size();
        size_type __len = _S_strlen(__val);
        size_type __idx = __len - 1;
        for (; __first != __last && size_type(_S_EOF) != __idx;
             --__idx, (void)--__ret)
            if (!_S_comp(*++__first, __val[__idx]))
                __idx = __len;
        return size_type(_S_EOF) == __idx ? __ret : size_type(_S_EOF);
    }

    template <typename _CharT, typename _Alloc>
    typename basic_string<_CharT, _Alloc>::size_type
    basic_string<_CharT, _Alloc>::
        rfind(basic_string const &__val, size_type __pos)
            ustl_cpp_noexcept
    {
        return rfind(__val.data(), __pos);
    }

    template <typename _CharT, typename _Alloc>
    typename basic_string<_CharT, _Alloc>::size_type
    basic_string<_CharT, _Alloc>::
        find_last_of(value_type __val, size_type __pos)
            ustl_cpp_noexcept
    {
        return rfind(__val, __pos);
    }

    template <typename _CharT, typename _Alloc>
    typename basic_string<_CharT, _Alloc>::size_type
    basic_string<_CharT, _Alloc>::
        find_last_of(const_pointer __val, size_type __pos)
            ustl_cpp_noexcept
    {
        return rfind(__val, __pos);
    }

    template <typename _CharT, typename _Alloc>
    typename basic_string<_CharT, _Alloc>::size_type
    basic_string<_CharT, _Alloc>::
        find_last_of(basic_string const &__val, size_type __pos)
            ustl_cpp_noexcept
    {
        return rfind(__val, __pos);
    }

    template <typename _CharT, typename _Alloc>
    typename basic_string<_CharT, _Alloc>::size_type
    basic_string<_CharT, _Alloc>::
        find_first_of(value_type const __val, size_type __pos)
            ustl_cpp_noexcept
    {
        return find(__val, __pos);
    }

    template <typename _CharT, typename _Alloc>
    typename basic_string<_CharT, _Alloc>::size_type
    basic_string<_CharT, _Alloc>::
        find_first_of(basic_string const &__val, size_type __pos)
            ustl_cpp_noexcept
    {
        return find(__val, __pos);
    }

    template <typename _CharT, typename _Alloc>
    typename basic_string<_CharT, _Alloc>::size_type
    basic_string<_CharT, _Alloc>::
        find_first_of(const_pointer __val, size_type __pos)
            ustl_cpp_noexcept
    {
        return find(__val, __pos);
    }

    template <typename _CharT, typename _Alloc>
    int
    basic_string<_CharT, _Alloc>::
        compare(const_pointer __str) const ustl_cpp_noexcept
    {
        size_type const __my_len = size();
        size_type const __olen = _S_strlen(__str);
        size_type __len = ustl::min(__my_len, __olen);
        const_pointer __p = data();
        int __result = _S_compare(__p, __str, __len);
        if (0 == __result && __olen != __my_len)
            return __olen > size() ? -1 : 1;
        return __result;
    }

    template <typename _CharT, typename _Alloc>
    int
    basic_string<_CharT, _Alloc>::
        compare(basic_string const &__other) const ustl_cpp_noexcept
    {
        return compare(__other.data());
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        substr(size_type __pos, size_type __len) -> basic_string
    {
        pointer __first = data() + __pos;
        pointer __last = __first + __len;
        return basic_string(__first, __last);
    }

    template <typename _CharT, typename _Alloc>
    void basic_string<_CharT, _Alloc>::
        copy(pointer __buf, size_type __n,
             size_type __pos) const
    {
        if (__n && __pos != _M_data_length)
            _S_copy(data() + __pos, __buf, __n);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        assign(value_type const __val, size_type __n)
    {
        _M_replace_aux(0, size(), __val, __n);
        _M_set_len(__n);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        assign(const_pointer __str)
    {
        size_type __str_len = _S_strlen(__str);
        _M_replace(0, size(), __str, __str_len);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        assign(basic_string const &__str)
    {
        assign(__str.data());
    }

    template <typename _CharT, typename _Alloc>
    template <typename _InputIterator>
    void
    basic_string<_CharT, _Alloc>::
        assign(_InputIterator __first, _InputIterator __last)
    {
        _M_replace_copy(cbegin(), cend(), __first, __last);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        swap(basic_string &__other)
    {
        if (this == &__other)
            return;

        size_type __my_len = size();
        size_type __ot_len = __other.size();
        if (_M_data_is_local())
        {
            if (__other._M_data_is_local())
            {
                value_type __tmp[__my_len];
                _S_copy(_M_data(), __tmp, __my_len);
                _S_copy(__other._M_data(), _M_data(), __ot_len);
                _S_copy(__tmp, __other._M_data(), __my_len);
            }
            else
            {
                size_type __new_capacity = __other.capacity();
                pointer __local_data = this->_M_local_data();
                this->_M_set_data(__other._M_data());
                __other._M_set_data(__other._M_local_data());
                _S_copy(__local_data, __other._M_local_data(), __my_len);
                _M_set_capacity(__new_capacity);
            }
        }
        else
        {
            if (__other._M_local_data())
            {
                size_type __new_capacity = this->capacity();
                pointer __local_data = __other._M_local_data();
                __other._M_set_data(this->_M_data());
                this->_M_set_data(this->_M_local_data());
                _S_copy(__local_data, _M_local_data(), __ot_len);
                __other._M_set_capacity(__new_capacity);
            }
            else
                _M_data_plus._M_swap(__other._M_data_plus);
        }
        _M_set_len(__ot_len);
        __other._M_set_len(__my_len);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        swap(basic_string &&__other)
    {
        *this = ustl::move(__other);
    }

    template <typename _CharT, typename _Alloc>
    inline void
    basic_string<_CharT, _Alloc>::
        reverse()
    {
        pointer __data = &front();
        pointer __data_last = &back();
        size_type __mid = size() >> 1;
        for (; __mid--; ++__data, (void)--__data_last)
            _CharT_traits::swap(*__data, *__data_last);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        reserve(size_type __new_size)
    {
        if (__new_size < capacity())
            return;

        pointer __new_begin = _M_allocate(__new_size);
        pointer __p = data();
        size_type __old_size = size();
        ustl::copy_forward(__p, __p + __old_size, __new_begin);
        _M_destory(__p, __old_size);
        _M_deallocate(__p, __old_size);
        _M_set_data(__new_begin);
        _M_set_capacity(__new_size);
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        resize(size_type __new_size)
    {
        if (__new_size > size())
        {
            if (__new_size > capacity())
            {
                pointer __p = data();
                _M_amend(__p, size(), 0, 0, __new_size);
            }
            _M_set_len(__new_size);
        }
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        resize(size_type __new_size, value_type const __val)
    {
        if (__new_size > size())
        {
            pointer __p = data();
            size_type __old_len = size();
            if (__new_size > capacity())
                _M_amend(__p, __p + __old_len, 0, 0, __new_size);
            ustl::fill(__p + __old_len, __new_size - __old_len);
            _M_set_len(__new_size);
        }
    }

    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        clear()
    {
        if (!_M_data_is_local())
        {
            if (!_M_shared_data())
            {
                pointer __begin = data();
                size_type __len = size();
                size_type __capacity = capacity();
                _M_destory(__begin, __len);
                _M_deallocate(__begin, __capacity);
                _M_set_data(_M_local_data());
                _M_set_capacity(0);
            }
            else
                _M_data_plus._M_rmv_sharer();
        }
        _M_set_len(0);
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
    operator=(basic_string const &__other) & -> basic_string &
    {
        if (&__other != this)
        {
            if (!_M_data_is_local())
                _M_replace(0, 0, __other.data(), __other.size());
            else
                _M_data_plus._M_copy(__other._M_data_plus);

            _M_set_len(__other.size());
        }
        return *this;
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
    operator=(basic_string &&__other) & -> basic_string &
    {
        if (&__other != this)
        {
            if (__other._M_data_is_local())
                assign(__other.begin(), __other.end());
            else
            {
                clear();
                _M_data_plus._M_move(__other._M_data_plus);
                _M_set_capacity(__other.capacity());
            }
            _M_set_len(__other.size());
        }
        return *this;
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
    operator+=(basic_string const &__other) & -> basic_string &
    {
        return this->append(__other);
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
    operator+=(const_pointer __str) & -> basic_string &
    {
        return this->append(__str);
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
    operator+=(value_type const __val) & -> basic_string &
    {
        return this->append(__val);
    }

    template <typename _CharT, typename _Alloc>
    auto basic_string<_CharT, _Alloc>::
    operator[](size_type __idx) -> reference
    {
        if (__idx < size())
            return _M_data_plus->_M_actual_data[__idx];
        __throw_index_outof("basic_string::operator[]: index overlaps");
    }

    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
    operator[](size_type __idx) const -> const_reference
    {
        if (__idx < size())
            return _M_data_plus->_M_actual_data[__idx];
        __throw_index_outof("basic_string::operator[] const: index overlaps");
    }

} // namespace ustl

/** string operator funtion implement */
namespace ustl
{

    template <typename _CharT, typename _Alloc>
    inline bool
    operator==(basic_string<_CharT, _Alloc> const &__l,
               basic_string<_CharT, _Alloc> const &__r)
    {
        return 0 == __l.compare(__r) ? true : false;
    }

    template <typename _CharT, typename _Alloc>
    inline bool
    operator!=(basic_string<_CharT, _Alloc> const &__l,
               basic_string<_CharT, _Alloc> const &__r)
    {
        return 0 != __l.compare(__r) ? true : false;
    }

    template <typename _CharT, typename _Alloc>
    inline bool
    operator<=(basic_string<_CharT, _Alloc> const &__l,
               basic_string<_CharT, _Alloc> const &__r)
        ustl_cpp_noexcept
    {
        int __result = __l.compare(__r);
        return -1 == __result || 0 == __result ? true : false;
    }

    template <typename _CharT, typename _Alloc>
    inline bool
    operator<=(basic_string<_CharT, _Alloc> const &__l,
               _CharT const *__r)
        ustl_cpp_noexcept
    {
        int __result = __l.compare(__r);
        return -1 == __result || 0 == __result ? true : false;
    }

    template <typename _CharT, typename _Alloc>
    inline bool
    operator<=(_CharT const *__l,
               basic_string<_CharT, _Alloc> const &__r)
        ustl_cpp_noexcept
    {
        int __result = __r.compare(__l);
        return -1 == __result || 0 == __result ? true : false;
    }

    template <typename _CharT, typename _Alloc>
    inline bool
    operator>(basic_string<_CharT, _Alloc> const &__l,
              basic_string<_CharT, _Alloc> const &__r)
        ustl_cpp_noexcept
    {
        int __result = __l.compare(__r);
        return 1 == __result ? true : false;
    }

    template <typename _CharT, typename _Alloc>
    inline bool
    operator>(basic_string<_CharT, _Alloc> const &__l,
              _CharT const *__r)
        ustl_cpp_noexcept
    {
        int __result = __l.compare(__r);
        return 1 == __result ? true : false;
    }

    template <typename _CharT, typename _Alloc>
    inline bool
    operator>(_CharT const *__l,
              basic_string<_CharT, _Alloc> const &__r)
        ustl_cpp_noexcept
    {
        int __result = __r.compare(__l);
        return 1 == __result ? true : false;
    }

    template <typename _CharT, typename _Alloc>
    inline basic_string<_CharT, _Alloc>
    operator+(_CharT const *__l,
              basic_string<_CharT, _Alloc> const &__r)
    {
        basic_string<_CharT, _Alloc> __tmp(__l);
        __tmp.append(__r);
        return __tmp;
    }

    template <typename _CharT, typename _Alloc>
    inline basic_string<_CharT, _Alloc>
    operator+(basic_string<_CharT, _Alloc> const &__l,
              _CharT const *__r)
    {
        basic_string<_CharT, _Alloc> __tmp(__l);
        __tmp.append(__r);
        return __tmp;
    }

    template <typename _CharT, typename _Alloc>
    basic_string<_CharT, _Alloc>
    operator+(_CharT const __l,
              basic_string<_CharT, _Alloc> const &__r)
    {
        basic_string<_CharT, _Alloc> __tmp(__l);
        __tmp.append(__r);
        return __tmp;
    }

    template <typename _CharT, typename _Alloc>
    inline basic_string<_CharT, _Alloc>
    operator+(basic_string<_CharT, _Alloc> const &__r,
              _CharT const __l)
    {
        basic_string<_CharT, _Alloc> __tmp(__l);
        __l.append(__r);
        return __tmp;
    }

    template <typename _CharT, typename _Alloc>
    inline basic_string<_CharT, _Alloc>
    operator+(basic_string<_CharT, _Alloc> const &__l,
              basic_string<_CharT, _Alloc> const &__r)
    {
        basic_string<_CharT, _Alloc> __tmp(__l);
        __l.append(__r);
        return __tmp;
    }

} // namespace ustl::basic_string

#endif