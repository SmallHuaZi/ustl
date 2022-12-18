#ifndef __basic_string_h
#define __basic_string_h

#include "include/config.h"
#include "algorithm/algorithm.h"
#include "conc/mutex.h"
#include "allocator/shared_ptr.h"
#include "iterator/normal_iterator.h"
#include "iterator/reverse_iterator.h"


namespace ustl
{
    template <typename _CharT, typename _Alloc>
    struct ustl_string_basic
    {
        enum        { __LOCAL_DATA_LIMIT = 24 };
        enum        { __LOCAL_DATA_SIZE = size_t(__LOCAL_DATA_LIMIT) / sizeof(_CharT) };

    protected:
        typedef     _CharT                      value_type;
        typedef     _CharT *                    pointer;
        typedef     _CharT &                    reference;
        typedef     _CharT const *              const_pointer;
        typedef     _CharT const &              const_reference;
        typedef     _Alloc                      allocator_type;
        typedef     ustl::size_t                size_type;
        typedef     ustl::diff_t                difference_type;

        typedef     ustl::normal_iterator<pointer>                  iterator;
        typedef     ustl::normal_iterator<const_pointer>            const_iterator;
        typedef     ustl::reverse_iterator<iterator>                reverse_iterator;
        typedef     ustl::reverse_iterator<const_iterator>          const_reverse_iterator;

    protected:
        typedef     ustl::allocate_traits<_Alloc>                   _Tp_allocate_traits;
        typedef     ustl::char_traits<_CharT>                       _Chart_traits;


        struct basic_string_impl
            : allocator_type
        {        
            void
            _M_reset() ustl_cpp_noexcept;


        public:
            bool
            _M_is_local() ustl_cpp_noexcept
            { return    _M_data_pointer == _M_local_data; }


        public:
            basic_string_impl() ustl_cpp_noexcept
                : _M_data_pointer(_M_local_data),
                  _M_heap_size(0)
            {}


        public:
            ustl::shared_ptr<value_type>        _M_data_pointer;
            size_type                           _M_data_length;
        union {
            value_type                          _M_local_data[size_type(__LOCAL_DATA_SIZE)];
            size_type                           _M_heap_size;
            };
        };

        typedef     basic_string_impl           impl_type;


    protected:
        size_type
        _M_checking_length(size_type __len);


        static void
        _S_copy(ustl_string_basic const &__x, ustl_string_basic &__y) 
    #ifdef  ustl_cpp_noexcept
        noexcept(noexcept(_Chart_traits::copy(0, 0, 0)));
    #else
        ;
    #endif 


    protected:
        allocator_type &
        _M_get_allocator() ustl_cpp_noexcept
        { return    _M_data_plus; }


        pointer
        _M_allocate(size_type __n = 1)
        { _Tp_allocate_traits::allocate(_M_get_allocator(), __n); }


        void
        _M_construct(pointer __p)
        { _Tp_allocate_traits::construct(_M_get_allocator(), __p); }


        void
        _M_destory(pointer __p) ustl_cpp_noexcept
        { _Tp_allocate_traits::destory(_M_get_allocator(), __p); }


        void
        _M_deallocate(pointer __p, size_type __s) ustl_cpp_noexcept
        { _Tp_allocate_traits::deallocate(_M_get_allocator(), __p, __s); }


        size_type
        _M_max_size() ustl_cpp_noexcept
        { return    _Tp_allocate_traits::max_size(_M_get_allocator()); }


        size_type
        _M_capacity() ustl_cpp_noexcept
        { return    _M_data_plus._M_is_local() ? size_type(__LOCAL_DATA_SIZE) : _M_data_plus._M_heap_size; }


        difference_type
        _M_distance(const_iterator __first, const_iterator __last)
        { return    __last.base_iterator() - __first.base_iterator(); }


        template <typename _Iterator>
        difference_type
        _M_distance(_Iterator __first, _Iterator __last)
        { return    ustl::distance(__first, __last); }


        static size_type
        _S_strlen(ustl_string_basic const &__x)
    #ifdef  ustl_cpp_noexcept
        noexcept(noexcept(_Chart_traits::length(0)))
    #endif
        { return    _Chart_traits::length(__x._M_data_plus._M_data_pointer); }


        static void
        _S_assign(_CharT const &__s, _CharT &__d)
    #ifdef  ustl_cpp_noexcept
        noexcept(noexcept(_Chart_traits::assign(0, 0)))
    #endif
        { _Chart_traits::assign(__s, __d); }


        static int
        _S_compare(_CharT const *__l, _CharT const *__r, size_type __len)
    #ifdef  ustl_cpp_noexcept
        noexcept(noexcept(_Chart_traits::compare(0, 0, 0)))
    #endif
        { return    _Chart_traits::compare(__l, __r, __len); }


    protected:
        ustl_string_basic()
            : _M_data_plus()
        {}

    protected:
        impl_type               _M_data_plus;

    };


    template <typename _CharT, typename _Alloc>
    inline auto 
    ustl_string_basic<_CharT, _Alloc>::
        _M_checking_length(size_type __s) -> size_type
    {
        size_type   __old_capacity = _M_capacity();
        if(__s > _M_max_size())
            __ustl_throw_array_length("basic_string::_M_checking_length : size of requested memory overlaps");
        if(__s > __old_capacity && __s <(__old_capacity << 1))
            __s = __old_capacity << 1;
        return  __s;
    }


    template <typename _CharT, typename _Alloc>
    inline void
    ustl_string_basic<_CharT, _Alloc>::
    basic_string_impl::
        _M_reset() ustl_cpp_noexcept
    {
        _M_data_length = 0;
        _M_data_pointer = 0;
        _M_heap_size = 0;
    }


    template <typename _CharT, typename _Alloc>
    inline void
    ustl_string_basic<_CharT, _Alloc>::
        _S_copy(ustl_string_basic const &__x, ustl_string_basic &__y) 
#ifdef  ustl_cpp_noexcept
        noexcept(noexcept(_Chart_traits::copy(0, 0, 0)))
#endif 
    {
        size_type   __len = __x._M_data_plus._M_data_length;
        pointer     __src = __x._M_data_plus._M_data_pointer;
        pointer     __des = __y._M_data_plus._M_data_pointer;
        _Chart_traits::copy(__src, __des, __len);
    }




    template <typename _CharT, typename _Alloc>
    class basic_string
        : ustl_string_basic<_CharT, _Alloc>
    {
        typedef     ustl_string_basic<_CharT, _Alloc>       _Base_type;

    public:

        typedef     _CharT                      value_type;
        typedef     _CharT *                    pointer;
        typedef     _CharT &                    reference;
        typedef     _CharT const *              const_pointer;
        typedef     _CharT const &              const_reference;

        typedef     typename _Base_type::impl_type          impl_type;
        typedef     typename _Base_type::size_type          size_type;
        typedef     typename _Base_type::difference_type    difference_type;
        typedef     typename _Base_type::allocator_type     allocator_type;

        typedef     typename _Base_type::iterator                   iterator;
        typedef     typename _Base_type::const_iterator             const_iterator;
        typedef     typename _Base_type::reverse_iterator           reverse_iterator;
        typedef     typename _Base_type::const_reverse_iterator      const_reverse_iterator;
        typedef     typename _Base_type::_Chart_traits              _Chart_traits;


    protected:
        using       _Base_type::_M_allocate;
        using       _Base_type::_M_deallocate;
        using       _Base_type::_M_construct;
        using       _Base_type::_M_destory;
        using       _Base_type::_M_max_size;
        using       _Base_type::_M_capacity;
        using       _Base_type::_M_get_allocator;
        using       _Base_type::_M_checking_length;
        using       _Base_type::_S_strlen;
        using       _Base_type::_S_copy;
        using       _Base_type::_S_compare;
        using       _Base_type::_S_assign;


    private:
        void
        _M_set_data(pointer __p) ustl_cpp_noexcept 
        { _M_data_plus._M_actual_data = __p; }


        void
        _M_set_length(size_type __new_len) ustl_cpp_noexcept 
        { _M_data_plus._M_data_length = __new_len; }


        void
        _M_set_capacity(size_type __capacity) ustl_cpp_noexcept 
        { _M_data_plus._M_heap_size  = __capacity; }


        pointer
        _M_data_first() ustl_cpp_noexcept 
        { return    _M_data_plus._M_actual_data; }


        pointer
        _M_data_last() ustl_cpp_noexcept 
        { return    _M_data_plus._M_actual_data + _M_data_plus._M_data_length; }


        bool
        _M_shared_data() 
        { return    1 != _M_data_plus._M_ref_count; }


    private:
        void
        _M_assign_aux(value_type const __val, size_type __n);

        template <typename _InputIterator>
        void
        _M_assign(_InputIterator __first, _InputIterator __last);

        template <typename _InputIterator>
        void 
        _M_construct(_InputIterator, _InputIterator);

        basic_string & 
        _M_append(const_pointer __cstr, size_type __len);

        basic_string &
        _M_append_aux(value_type __val, size_type __n);

        basic_string & 
        _M_replace(size_type, size_type, const_pointer, size_type);

        basic_string & 
        _M_replace_aux(size_type, size_type, value_type, size_type = 1);

        void 
        _M_erase(size_type, size_type);

        void 
        _M_amend(const_pointer, size_type, const_pointer, size_type, size_type);


    public:
        pointer
        data() ustl_cpp_noexcept 
        { return _M_data_first(); }


        const_pointer
        data() const ustl_cpp_noexcept 
        { return    _M_data_first(); }


        reference
        front() ustl_cpp_noexcept 
        { return    *_M_data_first(); }


        reference
        back() ustl_cpp_noexcept 
        { return    *(_M_data_last() - 1); }


        const_reference
        front() const ustl_cpp_noexcept 
        { return    *_M_data_first(); }


        const_reference
        back() const ustl_cpp_noexcept 
        { return    *(_M_data_last() - 1); }


        iterator
        begin() ustl_cpp_noexcept 
        { return    iterator(_M_data_first()); }


        iterator
        end() ustl_cpp_noexcept 
        { return    iterator(_M_data_last()); }


        const_iterator
        begin() const ustl_cpp_noexcept 
        { return    const_iterator(_M_data_first()); }


        const_iterator
        end() const ustl_cpp_noexcept 
        { return    const_iterator(_M_data_last()); }


        const_iterator
        cbegin() ustl_cpp_noexcept 
        { return    const_iterator(_M_data_first()); }


        const_iterator
        cend() ustl_cpp_noexcept 
        { return    const_iterator(_M_data_last()); }


        const_iterator
        cbegin() const ustl_cpp_noexcept 
        { return    const_iterator(_M_data_first()); }


        const_iterator
        cend() const ustl_cpp_noexcept 
        { return    const_iterator(_M_data_last()); }


        reverse_iterator
        rbegin() ustl_cpp_noexcept 
        { return    const_iterator(_M_data_last()); }


        reverse_iterator
        rend() ustl_cpp_noexcept 
        { return    reverse_iterator(_M_data_first()); }


        const_reverse_iterator
        rbegin() const ustl_cpp_noexcept 
        { return    const_iterator(_M_data_last()); }


        const_reverse_iterator
        rend() const ustl_cpp_noexcept 
        { return    const_reverse_iterator(_M_data_first()); }


        const_reverse_iterator
        crbegin() ustl_cpp_noexcept 
        { return    const_reverse_iterator(_M_data_last()); }


        const_reverse_iterator
        crend() ustl_cpp_noexcept 
        { return    const_reverse_iterator(_M_data_first()); }


        const_reverse_iterator
        crbegin() const ustl_cpp_noexcept 
        { return    const_reverse_iterator(_M_data_last()); }


        const_reverse_iterator
        crend() const ustl_cpp_noexcept 
        { return    const_reverse_iterator(_M_data_first()); }


        bool
        empty() ustl_cpp_noexcept 
        { return    0 == _M_data_plus._M_data_length; }


        bool
        empty() const ustl_cpp_noexcept 
        { return    0 == _M_data_plus._M_data_length; }


        size_type
        size() ustl_cpp_noexcept 
        { return    _M_data_plus._M_data_length; }


        size_type
        size() const ustl_cpp_noexcept 
        { return    _M_data_plus._M_data_length; }


        size_type
        capacity() ustl_cpp_noexcept 
        { return    _M_capacity(); }


        size_type
        capacity() const ustl_cpp_noexcept 
        { return    _M_capacity(); }


        basic_string &
        append(basic_string const &__lother)
        { return    append(__lother.data(), __lother.size()); }


        basic_string &
        append(const_pointer __cstr)
        { return    _M_append(__cstr, _S_strlen(__cstr)); }


        basic_string &
        append(value_type const __val, size_type __n = 1)
        { return    _M_append(&__val, &__val + 1); }


        basic_string &
        replace(size_type __start, size_type __finish, value_type const __val, size_type __n)
        { return    _M_replace_aux(__start, __finish, __val, __n); }


        basic_string &
        replace(size_type __start, size_type __finish, const_pointer __cstr)
        { return    _M_replace(__start, __finish, __cstr, _S_strlen(__cstr)); }


        basic_string &
        replace(size_type __start, size_type __finish, basic_string const &__other)
        { return    _M_replace(__start, __finish, __other.data(), __other.size()); }


        basic_string &
        replace(const_iterator __start, const_iterator __finish, value_type const __val)
        { return    _M_replace_aux(_M_distance(cbegin(), __start), _M_distance(__start, __finish), __val, _M_distance(__start, __finish)); }


        basic_string &
        replace(const_iterator __start, const_iterator __finish, const_pointer __cstr)
        { return    _M_replace(_M_distance(cbegin(), __start), _M_distance(__start, __finish), __cstr, _S_strlen(__cstr)); }


        basic_string &
        replace(const_iterator __start, const_iterator __finish, basic_string const &__other)
        { return    _M_replace_aux(_M_distance(cbegin(), __start), _M_distance(__start, __finish), __other.data(), __other.size()); }


        void
        push_back(value_type const __val, size_type __n = 1)
        { _M_append_aux(__val, __n); }


        void
        push_back(const_pointer __cstr)
        { _M_append(__cstr, _S_strlen(__cstr)); }


        void
        push_back(basic_string const &__lohter)
        { _M_append(__lohter.data(), __lohter.size()); }


        template <typename _InputIterator>
        void
        push_back(_InputIterator __first, _InputIterator __last)
        { append(__first, __last); }


        void
        erase(size_type __pos)
        { _M_erase(__pos, 1); }


        void
        erase(size_type __pos, size_type __len)
        { _M_erase(__pos, __len); }


        void
        erase(const_iterator __pos)
        { _M_erase(_M_distance(cbegin(), __pos), 1); }


        void
        erase(const_iterator __first, const_iterator __last)
        { _M_erase(_M_distance(cbegin(), __first), _M_distance(__first, __last)); }


        size_type 
        find(basic_string const &__other, size_type __pos = 0) ustl_cpp_noexcept
        { return    rfind(__other.data(), __pos); }


        size_type 
        rfind(basic_string const &__other, size_type __pos = 0) ustl_cpp_noexcept
        { return    rfind(__other.data(), __pos); }


        size_type 
        find_last_of(value_type const __val, size_type __pos = 0) ustl_cpp_noexcept
        { return    rfind(__val, __pos); }


        size_type 
        find_last_of(const_pointer __cstr, size_type __pos = 0) ustl_cpp_noexcept
        { return    rfind(__cstr, __pos); }


        size_type 
        find_last_of(basic_string const &__other, size_type __pos = 0) ustl_cpp_noexcept
        { return    rfind(__other, __pos); }


        size_type 
        find_first_of(value_type const __val, size_type __pos = 0) ustl_cpp_noexcept
        { return    find(__val, __pos); }


        size_type 
        find_first_of(const_pointer __cstr, size_type __pos = 0) ustl_cpp_noexcept
        { return    find(__cstr, __pos); }


        size_type 
        find_first_of(basic_string const &__other, size_type __pos = 0) ustl_cpp_noexcept
        { return    find(__other, __pos); }


        basic_string 
        substr(size_type __pos, size_type __length)
        { return    basic_string(data() + __pos, data() + __pos + __length); }


        int 
        compare(basic_string const &__other) const ustl_cpp_noexcept
        { return    compare(__other.data()); }


        void 
        swap(basic_string &&__rother)
        { *this = ustl::move(__rother); }


        basic_string &
        operator+=(basic_string const &__lother) &
        { return    append(__lother); }


        basic_string &
        operator+=(value_type const __val) &
        { return    append(__val); }


        basic_string &
        operator+=(const_pointer __cstr) &
        { return    append(__cstr); }


    public:
        template <typename _InputIterator>
        basic_string &
        append(_InputIterator __first, _InputIterator __last);

        template <typename _InputIterator>
        basic_string &
        replace(const_iterator, const_iterator, _InputIterator, _InputIterator);

        iterator 
        insert(size_type, value_type const, size_type);

        iterator 
        insert(size_type, const_pointer);

        iterator 
        insert(size_type, basic_string const &);
        
        iterator 
        insert(const_iterator, value_type const, size_type);

        iterator 
        insert(const_iterator, const_pointer);

        iterator 
        insert(const_iterator, basic_string const &);

        template <typename _InputIterator>
        iterator 
        insert(const_iterator, _InputIterator, _InputIterator);

        template <typename _InputIterator>
        iterator 
        insert(size_type, _InputIterator, _InputIterator);

        size_type 
        find(value_type const, size_type = 0) ustl_cpp_noexcept;

        size_type 
        find(const_pointer, size_type = 0) ustl_cpp_noexcept;

        size_type 
        rfind(value_type const, size_type = 0) ustl_cpp_noexcept;

        size_type 
        rfind(const_pointer, size_type = 0) ustl_cpp_noexcept;

        int 
        compare(const_pointer) const ustl_cpp_noexcept;

        void 
        copy(pointer, size_type, size_type = 0) const;

        void 
        swap(basic_string &);

        void 
        assign(value_type const, size_type);

        void 
        assign(const_pointer);
        
        void 
        assign(basic_string const &);

        template <typename _InputIterator>
        void 
        assign(_InputIterator, _InputIterator);

        void 
        reverse();

        void 
        reserve(size_type);

        void 
        resize(size_type);

        void 
        resize(size_type, value_type const);

        void 
        clear();

        basic_string &
        operator=(basic_string const &__lother) &;

        basic_string &
        operator=(basic_string &&__rother) &;

        reference 
        operator[](size_type);

        const_reference 
        operator[](size_type) const;


    public:
        basic_string()
            : ustl_string_basic()
        {}

        basic_string(basic_string const &__other)
            : basic_string(__other.data(), __other.size()) {}

        basic_string(basic_string &&__rother)
            : ustl_string_basic(ustl::move(__rother))
        {}

        basic_string(const_pointer __str)
            : basic_string()
        { assign(__str); }

        template <typename _InputIterator>
        basic_string(_InputIterator __first, _InputIterator __last)
            : basic_string()
        { _M_construct(__first, __last); }

        ~basic_string()
        { clear(); }


    protected:
        using       _Base_type::_M_data_plus;
    };



    template <typename _CharT, typename _Alloc>
    template <typename _InputIterator>
    auto 
    basic_string<_CharT, _Alloc>::
        append(_InputIterator __first, _InputIterator __last) -> basic_string &
    {
        if(__first != __last)
        {
            difference_type __len = _M_distance(__first, __last);
            size_type __old_size = size();
            size_type __new_size = __old_size + __len;
            if(__new_size > capacity())
                _M_amend(data(), __old_size, 0, 0, __new_size);
            
            pointer __start = _M_data_last();
            pointer __last  = __start + __len;
            for(; __start != __last; ++__start, (void)++__first)
                _S_assign(*__first, *__start);
            _M_set_length(__new_size);
        }
        return  *this;
    }



    template <typename _CharT, typename _Alloc>
    auto 
    basic_string<_CharT, _Alloc>::
        _M_append(const_pointer __str, size_type __len) -> basic_string &
    {
        if(0 != __len)
        {
            size_type __old_size = size();
            size_type __new_size = __old_size + __len;
            if (__new_size <= capacity() && !_M_shared_data())
                _S_copy(__str, _M_data_last(), __len);
            else
                _M_amend(data(), size(), __str, __len, __new_size);
            _M_set_len(__new_size);
        }
        return  *this;
    }



    template <typename _CharT, typename _Alloc>
    auto
    basic_string<_CharT, _Alloc>::
        _M_append_aux(value_type __val, size_type __n) -> basic_string &
    {
        if(0 != __n)
        {
            size_type   __old_size = size();
            size_type   __new_size = __old_size + __n;
            if(__new_size > capacity())
                _M_amend(data(), __old_size, 0, 0, __new_size);

            pointer __start = _M_data_last();
            pointer __finish = __start + __n;
            for(; __start != __finish; ++__start)
                _S_assign(__val, *__start);

            _M_set_length(__new_size);
        }
        return  *this;
    }



    template <typename _CharT, typename _Alloc>
    template <typename _InputIterator>
    void
    basic_string<_CharT, _Alloc>::
        _M_construct(_InputIterator __first, _InputIterator __last)
    {
        size_type __len = _M_distance(__first, __last);
        if (__len > capacity())
        {
            pointer __begin = _M_allocate(__len);
            _M_set_data(__begin);
            _M_set_capacity(__len);
        }
        pointer __start = data();
        pointer __finish = __start + __len;
        for(; __start != __finish; ++__start, (void)++__first)
            _S_assign(*__first, *__start);
        _M_set_len(__len);
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
        __new_size = _M_checking_length(__new_size);
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
    auto 
    basic_string<_CharT, _Alloc>::
        _M_replace(size_type __pos, size_type __len1,
                   const_pointer __str, size_type __len2) -> basic_string &
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
        return  *this;
    }



    template <typename _CharT, typename _Alloc>
    auto 
    basic_string<_CharT, _Alloc>::
        _M_replace_aux(size_type __pos, size_type __len1,
                       value_type __char, size_type __n) -> basic_string &
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
        return  *this;
    }



    /** using iterator  */
    template <typename _CharT, typename _Alloc>
    template <typename _ForwardIterator>
    auto
    basic_string<_CharT, _Alloc>::
        replace(const_iterator __start, const_iterator __finish, 
                _ForwardIterator __first, _ForwardIterator __last) -> basic_string &
    {
        if(__first != __last)
        {
            difference_type __len = _M_distance(__first, __last);
            size_type   __old_size   = size();
            size_type   __undo_len   = __finish - __start;
            size_type   __new_size   = __old_size - __undo_len + __len;
            if(__new_size < capacity())
            {

            }
            else
            {

            }
            _M_set_length(__new_size);
        }
        return  *this;
    }



    template <typename _CharT, typename _Alloc>
    void
    basic_string<_CharT, _Alloc>::
        _M_erase(size_type __pos, size_type __len)
    {
        size_type __move_len = size() - __pos - __len;
        if (__len)
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



    template <typename _CharT, typename _Alloc>
    inline auto 
    basic_string<_CharT, _Alloc>::
        insert(size_type __pos, value_type const __val,
               size_type __n) -> iterator
    {
        _M_replace_aux(__pos, 0, __val, __n);
        return iterator(begin() + __pos);
    }


    template <typename _CharT, typename _Alloc>
    inline auto
    basic_string<_CharT, _Alloc>::
        insert(size_type __pos, const_pointer __str) -> iterator
    {
        size_type __len = _S_strlen(__str);
        _M_replace(__pos, 0, __str, __str + __len, __len);
        return iterator(begin() + __pos);
    }


    template <typename _CharT, typename _Alloc>
    inline auto
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
    inline auto
    basic_string<_CharT, _Alloc>::
        insert(size_type __pos, _InputIterator __first,
               _InputIterator __last) -> iterator
    {
        replace(cbegin() + __pos, cbegin() + __pos, __first, __last);
        return iterator(begin() + __pos);
    }


    template <typename _CharT, typename _Alloc>
    inline auto
    basic_string<_CharT, _Alloc>::
        insert(const_iterator __pos, value_type const __val,
               size_type __n) -> iterator
    {
        difference_type __dis = __pos - cbegin();
        return insert(__dis, __val, __n);
    }


    template <typename _CharT, typename _Alloc>
    inline auto
    basic_string<_CharT, _Alloc>::
        insert(const_iterator __pos, const_pointer __str) -> iterator
    {
        difference_type __dis = __pos - cbegin();
        return insert(__pos, __str);
    }


    template <typename _CharT, typename _Alloc>
    inline auto
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
    inline auto
    basic_string<_CharT, _Alloc>::
        insert(const_iterator __pos, _ForwardIterator __first,
               _ForwardIterator __last) -> iterator
    {
        difference_type __dis = __pos - cbegin();
        replace(__pos, __pos, __first, __last);
        return iterator(begin() + __dis);
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
    inline int
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
    inline void 
    basic_string<_CharT, _Alloc>::
        copy(pointer __buf, size_type __n,
             size_type __pos) const
    {
        if (__n && __pos != size)
            _S_copy(data() + __pos, __buf, __n);
    }


    template <typename _CharT, typename _Alloc>
    inline void
    basic_string<_CharT, _Alloc>::
        assign(value_type const __val, size_type __n)
    {
        _M_replace_aux(0, size(), __val, __n);
        _M_set_len(__n);
    }


    template <typename _CharT, typename _Alloc>
    inline void
    basic_string<_CharT, _Alloc>::
        assign(const_pointer __str)
    {
        size_type __str_len = _S_strlen(__str);
        _M_replace(0, size(), __str, __str_len);
    }


    template <typename _CharT, typename _Alloc>
    inline void
    basic_string<_CharT, _Alloc>::
        assign(basic_string const &__str)
    {
        assign(__str.data());
    }


    template <typename _CharT, typename _Alloc>
    template <typename _InputIterator>
    inline void
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
    inline auto 
    basic_string<_CharT, _Alloc>::
    operator[](size_type __idx) -> reference
    {
        if (__idx < size())
            return _M_data_plus->_M_actual_data[__idx];
        __ustl_throw_out_of_range("basic_string::operator[]: index overlaps");
    }


    template <typename _CharT, typename _Alloc>
    inline auto
    basic_string<_CharT, _Alloc>::
    operator[](size_type __idx) const -> const_reference
    {
        if (__idx < size())
            return _M_data_plus->_M_actual_data[__idx];
        __ustl_throw_out_of_range("basic_string::operator[] const: index overlaps");
    }


    template <typename _CharT, typename _Alloc>
    inline bool
    operator==(basic_string<_CharT, _Alloc> const &__l,
               basic_string<_CharT, _Alloc> const &__r) ustl_cpp_noexcept
    { return    0 == __l.compare(__r) ? true : false; }


    template <typename _CharT, typename _Alloc>
    inline bool
    operator!=(basic_string<_CharT, _Alloc> const &__l,
               basic_string<_CharT, _Alloc> const &__r) ustl_cpp_noexcept
    { return    0 != __l.compare(__r) ? true : false; }


    template <typename _CharT, typename _Alloc>
    inline bool
    operator<=(basic_string<_CharT, _Alloc> const &__l,
               basic_string<_CharT, _Alloc> const &__r) ustl_cpp_noexcept
    { return    __l.compare(__r) < 1 ? true : false; }


    template <typename _CharT, typename _Alloc>
    inline bool
    operator<=(basic_string<_CharT, _Alloc> const &__l,
               _CharT const *__r) ustl_cpp_noexcept
    { return    __l.compare(__r) < 1 ? true : false; }


    template <typename _CharT, typename _Alloc>
    inline bool
    operator<=(_CharT const *__l,
               basic_string<_CharT, _Alloc> const &__r) ustl_cpp_noexcept
    { return    __l.compare(__r) < 1 ? true : false; }


    template <typename _CharT, typename _Alloc>
    inline bool
    operator>(basic_string<_CharT, _Alloc> const &__l,
              basic_string<_CharT, _Alloc> const &__r) ustl_cpp_noexcept
    { return  1 == __l.compare(__r) ? true : false; }


    template <typename _CharT, typename _Alloc>
    inline bool
    operator>(basic_string<_CharT, _Alloc> const &__l,
              _CharT const *__r) ustl_cpp_noexcept
    { return  1 == __l.compare(__r) ? true : false; }


    template <typename _CharT, typename _Alloc>
    inline bool
    operator>(_CharT const *__l,
              basic_string<_CharT, _Alloc> const &__r) ustl_cpp_noexcept
    { return  1 == __l.compare(__r) ? true : false; }


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


} // namespace ustl


#endif