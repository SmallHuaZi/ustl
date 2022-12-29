#ifndef __USTL_VECTOR_H 
#define __USTL_VECTOR_H 

#include "allocator/memory.h"
#include "type/iterator_type.h"
#include "iterator/reverse_iterator.h"

namespace ustl
{

    template <typename _Tp, bool _Const>
    struct vector_iterator
    {
        typedef     _Tp                 value_type;
        typedef     _Tp *               pointer;
        typedef     _Tp &               reference;
        typedef     _Tp const *         const_pointer;
        typedef     _Tp const &         const_reference;

        typedef     vector_iterator                 _Self;
        typedef     ustl::diff_t                    difference_type;
        typedef     _random_iterator                iterator_tag;
        typedef     vector_iterator<_Tp, false>     noncv_iterator;


    public:
        _Self
        operator+(difference_type   __step);

        _Self
        operator-(difference_type   __step);        


    public:
        noncv_iterator
        _M_const_cast() ustl_cpp_noexcept
        { return    noncv_iterator(_M_data); }

        pointer
        data() ustl_cpp_noexcept
        { return    _M_data; }

        typename if_else<_Const, const_pointer, pointer>::type 
        operator->() ustl_cpp_noexcept
        { return    _M_data; }

        typename if_else<_Const, const_reference, reference>::type 
        operator*() ustl_cpp_noexcept
        { return    *_M_data; }

        _Self &
        operator++() ustl_cpp_noexcept
        { return  ++_M_data, *this; }

        _Self &
        operator--() ustl_cpp_noexcept
        { return  --_M_data, *this; }

        _Self
        operator++(int) ustl_cpp_noexcept
        { return    _Self(_M_data++); }

        _Self
        operator--(int) ustl_cpp_noexcept
        { return    _Self(_M_data--); }

        _Self &
        operator+=(difference_type   __step) ustl_cpp_noexcept
        { return    _M_data += __step, *this; }

        _Self &
        operator-=(difference_type   __step) ustl_cpp_noexcept
        { return    _M_data -= __step, *this; }

        friend bool
        operator==(vector_iterator __x, vector_iterator __y) ustl_cpp_noexcept
        { return    __x._M_data == __y._M_data; }

        friend bool
        operator!=(vector_iterator __x, vector_iterator __y) ustl_cpp_noexcept
        { return    __x._M_data != __y._M_data; }

        friend difference_type
        operator-(vector_iterator const &__last, vector_iterator const &__first) ustl_cpp_noexcept
        { return     __last._M_data - __first._M_data; }


    public:
        vector_iterator() = default;

        vector_iterator(pointer __p)
            : _M_data(__p)
        {}

        vector_iterator(noncv_iterator const &__non_cv)
            : _M_data(__non_cv._M_data)
        {}


    protected:
        pointer             _M_data;
    };


    template <typename _Tp, bool _Const>
    auto
    vector_iterator<_Tp, _Const>::
        operator+(difference_type __step) -> _Self
    {
        _Self   __tmp(*this);
        if(__step < 0)
            __tmp -= (-__step);
        else
            __tmp += __step;
        return  __tmp;
    }


    template <typename _Tp, bool _Const>
    auto
    vector_iterator<_Tp, _Const>::
        operator-(difference_type __step) -> _Self
    {
        _Self   __tmp(*this);
        if(__step < 0)
            __tmp += (-__step);
        else
            __tmp -= __step;
        return  __tmp;
    }



    template <typename _Tp, typename _Alloc>
    struct vector_basic
    {
        typedef     _Tp                 value_type;
        typedef     _Tp *               pointer;
        typedef     _Tp &               reference;
        typedef     _Tp const *         const_pointer;
        typedef     _Tp const &         const_reference;

        typedef     _Alloc              allocator_type;
        typedef     ustl::size_t        size_type;
        typedef     ustl::diff_t        difference_type;

        typedef     vector_iterator<_Tp, false>                 iterator;
        typedef     vector_iterator<_Tp, true>                  const_iterator;
        typedef     ustl::reverse_iterator<iterator>            reverse_iterator;
        typedef     ustl::reverse_iterator<const_iterator>      const_reverse_iterator;


    protected:
        typedef     allocate_traits<_Alloc>         _Tp_allocate_traits;

        struct vector_impl
            : allocator_type
        {
            void
            _M_reset() ustl_cpp_noexcept;

            void
            _M_copy(vector_impl &__other) ustl_cpp_noexcept;

            void
            _M_move(vector_impl &__other) ustl_cpp_noexcept;

            void
            _M_swap(vector_impl &__other) ustl_cpp_noexcept;

            void
            _M_amend(pointer __start, size_type __len, size_type __capacity) ustl_cpp_noexcept;


        public:
            vector_impl()
                : _M_storage(0),
                  _M_start(0),
                  _M_finish(0)
            {}
            

        public:
            pointer         _M_start;
            pointer         _M_storage;
            pointer         _M_finish;
        };

        typedef     vector_impl             impl_type;


    public:
        void
        _M_destory(pointer __start, pointer __finish);

        size_type
        _M_checking_length(size_type __s);


    protected:
        size_type
        _M_capacity()
        { return    _M_data_plus._M_finish - _M_data_plus._M_start; }

        allocator_type &
        _M_get_allocator() ustl_cpp_noexcept
        { return    _M_data_plus; }

        pointer
        _M_allocate(size_type __s)
        { return    _Tp_allocate_traits::allocate(_M_get_allocator(), __s); }

        void
        _M_deallocate(pointer __p, size_type __len)
        { return    _Tp_allocate_traits::deallocate(_M_get_allocator(), __p, sizeof(_Tp) * __len); }

        template <typename ..._Args>
        void
        _M_construct(pointer __p, _Args &&...__init_args)
        { _Tp_allocate_traits::construct(_M_get_allocator(), __p, ustl::forward<_Args &&>(__init_args)...); }

        size_type
        _M_max_size() ustl_cpp_noexcept
        { return    _Tp_allocate_traits::max_size(_M_get_allocator()); }

        size_type
        _M_size() ustl_cpp_noexcept
        { return    _M_data_plus._M_storage - _M_data_plus._M_start; }


    protected:
        impl_type               _M_data_plus;
    };


    template <typename _Tp, typename _Alloc>
    void
    vector_basic<_Tp, _Alloc>::
    vector_impl::
        _M_amend(pointer __start, size_type __len, size_type __capacity) ustl_cpp_noexcept
    {
        _M_start   =   __start;
        _M_storage =   __start + __len;
        _M_finish  =   __start + __capacity;
    }


    template <typename _Tp, typename _Alloc>
    void
    vector_basic<_Tp, _Alloc>::
    vector_impl::
        _M_reset() ustl_cpp_noexcept
    {
        _M_start   =  0;
        _M_storage =  0;
        _M_finish  =  0;
    }


    template <typename _Tp, typename _Alloc>
    void
    vector_basic<_Tp, _Alloc>::
    vector_impl::
        _M_copy(vector_impl &__other) ustl_cpp_noexcept
    {
        _M_start   =   __other._M_start;
        _M_storage =   __other._M_storage;
        _M_finish  =   __other._M_finish;
    }
            

    template <typename _Tp, typename _Alloc>
    void
    vector_basic<_Tp, _Alloc>::
    vector_impl::
        _M_move(vector_impl &__other) ustl_cpp_noexcept
    {
        _M_copy(__other);
        __other._M_reset();
    }


    template <typename _Tp, typename _Alloc>
    void
    vector_basic<_Tp, _Alloc>::
    vector_impl::
        _M_swap(vector_impl &__other) ustl_cpp_noexcept
    {
        vector_impl __tmp(*this);
        _M_copy(__other);
        __other._M_copy(__tmp);
    }


    template <typename _Tp, typename _Alloc>
    void 
    vector_basic<_Tp, _Alloc>::
        _M_destory(pointer __start, pointer __finish)
    {
        for(; __start != __finish; ++__start)
            _Tp_allocate_traits::destory(_M_get_allocator(), __start);
    }


    template <typename _Tp, typename _Alloc>
    auto 
    vector_basic<_Tp, _Alloc>::
        _M_checking_length(size_type __s) -> size_type
    {
        if (_M_max_size() - _M_size() < __s)
            __ustl_throw_array_length();
        size_type __new_len = _M_size() + (_M_size() > __s ? _M_size() : __s);
        return __new_len < _M_max_size() ? __new_len : _M_max_size();
    }


    /// @class ustl::vector
    template <typename _Tp, typename _Alloc = ustl::allocator<_Tp>>
    class vector
        : vector_basic<_Tp, _Alloc>
    {
        typedef     vector_basic<_Tp, _Alloc>           _Base_type;

    public:
        typedef     _Tp                 value_type;
        typedef     _Tp *               pointer;
        typedef     _Tp &               reference;
        typedef     _Tp const *         const_pointer;
        typedef     _Tp const &         const_reference;

        typedef     typename _Base_type::iterator                       iterator;
        typedef     typename _Base_type::const_iterator                 const_iterator;
        typedef     typename _Base_type::reverse_iterator               reverse_iterator;
        typedef     typename _Base_type::const_reverse_iterator         const_reverse_iterator;

        typedef     typename _Base_type::size_type                      size_type;
        typedef     typename _Base_type::allocator_type                 allocator_type;
        typedef     typename _Base_type::difference_type                difference_type;

    private:
        using       _Base_type::_M_get_allocator;
        using       _Base_type::_M_allocate;
        using       _Base_type::_M_deallocate;
        using       _Base_type::_M_construct;
        using       _Base_type::_M_destory;
        using       _Base_type::_M_max_size;
        using       _Base_type::_M_checking_length;
        using       _Base_type::_M_capacity;


    private:
        void 
        _M_default_append(size_type); 

        void 
        _M_fill_assgin(size_type, value_type const &);

        iterator 
        _M_fill_insert(const_iterator, size_type, value_type const &);

        template <typename... _Args>  
        iterator 
        _M_emplace_aux(const_iterator, _Args &&...); 

        template <typename _ForwardIterator>                        
        iterator 
        _M_range_insert(const_iterator, _ForwardIterator, _ForwardIterator); 

        template <typename... _Args>                     
        iterator 
        _M_realloc_insert(const_iterator, _Args &&...);  

        iterator 
        _M_erase(iterator);

        size_type 
        _M_erase(iterator, iterator);


    public:
        bool 
        empty() const ustl_cpp_noexcept
        { return    _M_data_plus._M_start == _M_data_plus._M_storage; }

        size_t 
        size() const ustl_cpp_noexcept
        { return    _M_data_plus._M_storage - _M_data_plus._M_start; }

        size_t 
        capacity() const ustl_cpp_noexcept
        { return    _M_data_plus._M_finish - _M_data_plus._M_start; }

        iterator 
        begin() ustl_cpp_noexcept
        { return    iterator(_M_data_plus._M_start); }

        iterator 
        end() ustl_cpp_noexcept
        { return    iterator(_M_data_plus._M_storage); }

        const_iterator 
        cbegin() ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_start); }

        const_iterator 
        cend() ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_storage); }

        reverse_iterator 
        rbegin() ustl_cpp_noexcept
        { return    reverse_iterator(end()); }

        reverse_iterator 
        rend() ustl_cpp_noexcept
        { return    reverse_iterator(begin()); }

        const_reverse_iterator 
        crbegin() ustl_cpp_noexcept
        { return    const_reverse_iterator(cend()); }

        const_reverse_iterator 
        crend() ustl_cpp_noexcept
        { return    const_reverse_iterator(cbegin()); }

        const_iterator 
        begin() const ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_start); }

        const_iterator 
        end() const ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_storage); }

        const_iterator 
        cbegin() const ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_start); }

        const_iterator 
        cend() const ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_storage); }

        const_reverse_iterator 
        rbegin() const ustl_cpp_noexcept
        { return    const_reverse_iterator(cend()); }

        const_reverse_iterator 
        rend() const ustl_cpp_noexcept
        { return    const_reverse_iterator(cbegin()); }

        const_reverse_iterator 
        crbegin() const ustl_cpp_noexcept
        { return    const_reverse_iterator(cend()); }

        const_reverse_iterator 
        crend() const ustl_cpp_noexcept
        { return    const_reverse_iterator(cbegin()); }

        iterator 
        erase(const_iterator __pos)
        { return    _M_erase(__pos._M_const_cast()); }

        size_type 
        erase(const_iterator __first, const_iterator __last)
        { return    _M_erase(__first, __last); }

        void 
        swap(vector &__other)
        { _M_data_plus._M_swap(__other._M_data_plus); }

        void 
        swap(vector &&__rother)
        { *this = ustl::move(__rother); }

        void
        assign(value_type const &__val, size_type __n)
        { _M_fill_assgin(__n, __val); }

        void 
        push_back(value_type const &__lval)
        { emplace_back(__lval); }

        void
        push_back(value_type &&__rval)
        { emplace_back(ustl::move(__rval)); }

        void 
        push_back(iterator __itr)
        { emplace_back(*__itr); }

        void 
        push_front(value_type const &__lval)
        { emplace_front(__lval); }

        void
        push_front(value_type &&__rval)
        { emplace_front(ustl::move(__rval)); }

        void 
        push_front(iterator __itr)
        { emplace_front(*__itr); }

        iterator
        insert(const_iterator __pos, value_type const &__lval)
        { return    _M_emplace_aux(__pos, __lval); }

        iterator
        insert(const_iterator __pos, value_type &&__rval)
        { return    _M_emplace_aux(__pos, ustl::move(__rval)); }

        iterator
        insert(const_iterator __pos, value_type const &__lval, size_type __n)
        { return    _M_fill_insert(__pos, __n, __lval); } 

        template <typename _ForwardIterator>
        iterator 
        insert(const_iterator __pos, _ForwardIterator __first, _ForwardIterator __last)
        { return    _M_range_insert(__pos, __first, __last); }


    public:
        template <typename... _Args>
        void 
        emplace(const_iterator, _Args &&...);

        template <typename... _Args>
        void 
        emplace_back(_Args &&...);

        template <typename... _Args>
        void 
        emplace_front(_Args &&...);

        void
        remove(value_type const &__val);

        template <typename _Predicate>
        size_type 
        remove_if(_Predicate);

        template <typename _Itr>
        void 
        assign(_Itr, _Itr);

        void 
        clear();

        void 
        resize(size_type __n);

        void 
        resize(size_type, value_type const &);

        void 
        reserve(size_type);

        void 
        reverse();

        reference 
        operator[](size_t);

        const_reference 
        operator[](size_t) const;

        vector &
        operator=(vector const &) &;

        vector &
        operator=(vector &&) &;

    public:
        vector() = default;

        vector(vector const &__other)
        { assign(__other.begin(), __other.end()); }

        vector(vector &&__other)
        { *this = ustl::move(__other); }

        vector(value_type const &__val, size_type __n)
        { assign(__val, __n); }

        template <typename _InputIterator, typename = RequireInputItr<_InputIterator>>
        vector(_InputIterator __first, _InputIterator __last)
        { assign(__first, __last); }


    protected:
        using       _Base_type::_M_data_plus;
    };


    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    inline void
    vector<_Tp, _Alloc>::
        emplace(const_iterator __pos, _Args &&...__a)
    {
        if (_M_data_plus._M_finish != _M_data_plus._M_storage)
            if (cend() == __pos)
                _M_construct(_M_data_plus._M_storage++, ustl::forward<_Args &&>(__a)...);
            else
                _M_emplace_aux(__pos, ustl::forward<_Args &&>(__a)...);
        else
            _M_realloc_insert(__pos, ustl::forward<_Args &&>(__a)...);
    }


    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    inline void
    vector<_Tp, _Alloc>::
        emplace_back(_Args &&...__a)
    {
        if (_M_data_plus._M_finish != _M_data_plus._M_storage)
            _M_construct(_M_data_plus._M_storage++, ustl::forward<_Args &&>(__a)...);
        else
            _M_realloc_insert(cend(), ustl::forward<_Args &&>(__a)...);
    }


    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    inline void
    vector<_Tp, _Alloc>::
        emplace_front(_Args &&...__a)
    {
        if (_M_data_plus._M_finish != _M_data_plus._M_storage)
            _M_emplace_aux(cbegin(), ustl::forward<_Args &&>(__a)...);
        else
            _M_realloc_insert(cbegin(), ustl::forward<_Args &&>(__a)...);
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        remove(value_type const &__val)
    {
        iterator    __first = begin();
        while(__first != end())
        {
            if(__val == *__first)
                _M_erase(__first);
            else
                ++__first;
        }
    }


    template <typename _Tp, typename _Alloc>
    template <typename _CompPredicate>
    auto 
    vector<_Tp, _Alloc>::
        remove_if(_CompPredicate __cmp) -> size_type
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
    void
    vector<_Tp, _Alloc>::
        clear()
    {
        _M_destory(_M_data_plus._M_start, _M_data_plus._M_storage);
        _M_deallocate(_M_data_plus._M_start, capacity());
        _M_data_plus._M_amend(0, 0, 0);
    }


    template <typename _Tp, typename _Alloc>
    template <typename _Itr>
    void
    vector<_Tp, _Alloc>::
        assign(_Itr __first, _Itr __last)
    {
        size_type __distance = ustl::distance(__first, __last);
        if (_M_data_plus._M_finish - _M_data_plus._M_start > __distance)
        {
            ustl::copy_forward(__first, __last, _M_data_plus._M_start);
            _M_data_plus._M_storage = _M_data_plus._M_start + __distance;
        }
        else
        {
            size_type __len = _M_checking_length(__distance);
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
    inline void
    vector<_Tp, _Alloc>::
        resize(size_type __n)
    {
        if (__n > size())
            _M_default_append(__n - size());
    }


    template <typename _Tp, typename _Alloc>
    inline void
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
                ustl::relocate_forward(_M_data_plus._M_start,
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
        iterator    __first = begin();
        iterator    __last  = --end();
        size_type   __mid   = size() >> 1;
        for(size_type __i = 0; __i < __mid; 
            ++__i,(void)--__last, (void)++__first)
        {
            value_type  __tmp(ustl::move(*__first));
            *__first = ustl::move(*__last);
            *__last  = ustl::move(__tmp);
        }
    }


    template <typename _Tp, typename _Alloc>
    inline _Tp &
    vector<_Tp, _Alloc>::
    operator[](size_t __idx)
    {
        if (__idx > size())
            return *(_M_data_plus._M_start + __idx);
        __ustl_throw_out_of_range("vector.operator[]: index out of the overlaps");
    }


    template <typename _Tp, typename _Alloc>
    inline _Tp const &
    vector<_Tp, _Alloc>::
    operator[](size_t __idx) const
    {
        if (__idx > size())
            return *(_M_data_plus._M_start + __idx);
        __ustl_throw_out_of_range("vector.operator[]: index out of the overlaps");
    }


    template <typename _Tp, typename _Alloc>
    inline auto
    vector<_Tp, _Alloc>::
    operator=(vector const &__other) & -> vector &
    {
        if (this != &__other)
            assign(__other.begin(), __other.end());
        return *this;
    }


    template <typename _Tp, typename _Alloc>
    inline auto
    vector<_Tp, _Alloc>::
    operator=(vector &&__other) & -> vector &
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
    { return !__l == __r; }


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
    { return !__l <= __r; }


    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    auto 
    vector<_Tp, _Alloc>::
        _M_emplace_aux(const_iterator __pos, _Args &&...__init_args) -> iterator
    {
        if(cend() == __pos)
            emplace_back(ustl::forward<_Args &&>(__init_args)...);
        if(_M_data_plus._M_finish != _M_data_plus._M_storage)
        {
            pointer  __start  =  __pos.data();
            pointer  __finish =  _M_data_plus._M_storage;
            ustl::relocate_back(__start, __finish, _M_data_plus._M_storage, _M_get_allocator());
            _M_construct(__start, ustl::forward<_Args &&>(__init_args)...);

        }
        else
            return  _M_realloc_insert(__pos, ustl::forward<_Args &&>(__init_args)...);
        return  __pos._M_const_cast();
    }


    template <typename _Tp, typename _Alloc>
    auto 
    vector<_Tp, _Alloc>::
        _M_fill_insert(const_iterator __pos, size_type __n, value_type const &__val) -> iterator
    {
        pointer __pos_ptr = __pos.data();

        if (_M_data_plus._M_finish - _M_data_plus._M_storage >= __n)
        {
            pointer __storage = _M_data_plus._M_storage;
            ustl::relocate_back(__pos_ptr, __storage, __storage + __n, _M_get_allocator());
            ustl::fill(__pos_ptr, __pos_ptr + __n, __val);
        }
        else
        {
            size_type __old_size = size();
            size_type __len = _M_check_length(__n);
            pointer __new_begin = _M_allocate(__len);
            difference_type __distance = __pos - cbegin();
            __pos_ptr = __new_begin + __distance;
            __ustl_try
            {
                ustl::relocate_forward(_M_data_plus._M_start , __pos_ptr, __new_begin, _M_get_allocator());
                ustl::fill(__pos_ptr, __pos_ptr + __n, __val);
                ustl::relocate_back(__pos, cend(), __pos_ptr + __n, _M_get_allocator());
            }
            __ustl_catch_all
            {
                _M_destory(__new_begin, __pos_ptr + __n);
                _M_deallocate(__new_begin, __len);
                __ustl_throw_again;
            }
            _M_deallocate(_M_data_plus._M_start, _M_capacity());
            _M_data_plus._M_amend(__new_begin, __old_size + __n, __len);
        }

        return      iterator(__pos_ptr);
    }

    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    auto 
    vector<_Tp, _Alloc>::
        _M_realloc_insert(const_iterator __pos, _Args &&...__a) -> iterator
    {
        size_type __old_size = size();
        size_type __len = _M_checking_length(size_type(1));
        pointer __new_begin = _M_allocate(__len);
        pointer __new_storage{__new_begin};

        iterator __first = begin();
        iterator __last = end();
        size_type __distance = __pos - cbegin();
        __ustl_try
        {
            __new_storage += __distance;
            iterator __ist_pos = __first + __distance;
            ustl::relocate_forward(__ist_pos, __last, __new_storage + 1, _M_get_allocator());
            _M_construct(__new_storage, ustl::forward<_Args &&>(__a)...);
            ustl::relocate_back(__first, __ist_pos, __new_storage, _M_get_allocator());
        }
        __ustl_catch_all
        {
            _M_destory(__new_begin, __new_begin + __old_size + 1);
            _M_deallocate(__new_begin, __len);
            __ustl_throw_again;
        }
        _M_deallocate(_M_data_plus._M_start, __old_size);
        _M_data_plus._M_amend(__new_begin, __old_size + 1, __len);
        return  iterator(_M_data_plus._M_start + __distance);
    }


    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    auto 
    vector<_Tp, _Alloc>::
        _M_range_insert(const_iterator __pos,
                        _ForwardIterator __first,
                        _ForwardIterator __last) -> iterator
    {
        size_type __old_size   =  size();
        size_type __distance   =  ustl::distance(__first, __last);
        size_type __ele_before =  __pos - cbegin();
        iterator  __ist_pos    =  __pos._M_const_cast();
        pointer   __start      =  __ist_pos.data();
        if (__distance)
        {
            if (_M_data_plus._M_finish - _M_data_plus._M_storage >= __distance) // move data
            {
                iterator __last = end();
                _M_data_plus._M_storage += __distance;
                ustl::relocate_back(__ist_pos, end(), _M_data_plus._M_storage, _M_get_allocator());
                ustl::copy_forward(__first, __last, __start);
            }
            else // realloc
            {
                size_type __len     = _M_check_length(size_type(__distance));
                pointer __old_begin = _M_data_plus._M_start;
                pointer __new_begin = _M_allocate(__len);
                __start = __new_begin;
                ustl::relocate_forward(__old_begin, __old_begin + __ele_before, __start, _M_get_allocator());
                ustl::copy_forward(__first, __last, __start + __ele_before);
                ustl::relocate_forward(__ist_pos, end(), __start + __ele_before + __distance, _M_get_allocator());
                _M_data_plus._M_amend(__new_begin, __distance + __old_size, __len);
            }
        }
        return  iterator(__start + __ele_before);
    }


    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        _M_default_append(size_type __n)
    {
        if (_M_data_plus._M_finish - _M_data_plus._M_storage >= __n)
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
        _M_fill_assgin(size_type __n,
                      value_type const &__val)
    {
        if (_M_data_plus._M_finish - _M_data_plus._M_storage >= __n)
        {
            pointer __old_storage = _M_data_plus._M_storage;
            __ustl_try
            {
                ustl::constructor(_M_data_plus._M_storage, size_type(__n), __val);
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
            size_type __len = _M_checking_length(__n);
            pointer __new_begin = _M_allocate(__len);
            pointer __new_storage = __new_begin;
            ustl::copy_forward(begin(), end(), __new_begin);
            size_type __counter = __n;
            __ustl_try
            {
                ustl::constructor(__new_storage, size_type(__n), __val);
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
        pointer __del = __pos.data();
        _M_destory(__del, __del + 1);
        ustl::relocate_forward(__del + 1, 
            _M_data_plus._M_storage, 
            __del, 
            _M_get_allocator()
        );
        --_M_data_plus._M_storage;
        return __pos;
    }


    template <typename _Tp, typename _Alloc>
    auto 
    vector<_Tp, _Alloc>::
        _M_erase(iterator __first, iterator __last) -> size_type
    {
        pointer __del_first =  __first.data();
        pointer __del_last  =  __last.data();
        pointer __tmp = __del_first;
        size_type __dis = 0;
        _M_destory(__del_first, __del_last);
        ustl::relocate_forward(__del_last, 
            _M_data_plus._M_storage, 
            __tmp,
            _M_get_allocator()
        );
        _M_data_plus._M_storage -= __dis;
        return __dis;
    }

}

#endif