#ifndef __ustl_deque_h
#define __ustl_deque_h

#include "include/config.h"
#include "allocator/memory.h"
#include "algorithm/algorithm.h"
#include "type/iterator_type.h"



namespace ustl
{

    template <typename _Tp, bool _Const>
    struct deque_iterator
    {
        enum        { __ALLOC_BLOCK_SIZE        =   512 };

    public:
        typedef     _Tp                         value_type;
        typedef     _Tp *                       pointer;
        typedef     _Tp &                       reference;
        typedef     _Tp const *                 const_pointer; 
        typedef     _Tp const &                 const_reference;

        typedef     deque_iterator                  _Self;
        typedef     _random_iterator                iterator_tag;
        typedef     diff_t                          difference_type;
        typedef     deque_iterator<_Tp, false>      noncv_iterator;
        typedef     _Tp **                  _bc_pointer;


    public:
        static constexpr size_t
        _S_bucket_capacity() ustl_cpp_noexcept;

        void
        _M_update(_bc_pointer __new) ustl_cpp_noexcept;

        _Self & 
        operator++() ustl_cpp_noexcept;

        _Self &
        operator--() ustl_cpp_noexcept;

        _Self &
        operator+=(difference_type  __step) ustl_cpp_noexcept;

        _Self &
        operator-=(difference_type  __step) ustl_cpp_noexcept;

        _Self
        operator++(int) ustl_cpp_noexcept;

        _Self
        operator--(int) ustl_cpp_noexcept;

        _Self
        operator+(difference_type   __step) ustl_cpp_noexcept;

        _Self
        operator-(difference_type   __step) ustl_cpp_noexcept;

        _Self &
        operator=(_Self const &__other) ustl_cpp_noexcept;


    public:
        noncv_iterator 
        _M_const_cast() ustl_cpp_noexcept
        { return     noncv_iterator(_M_data, _M_bucket_cur); }

        pointer
        data() ustl_cpp_noexcept
        { return     _M_data; }

        typename ustl::if_else<_Const, const_reference, reference>::type
        operator*() ustl_cpp_noexcept
        { return    *_M_data; }

        typename ustl::if_else<_Const, const_pointer, pointer>::type
        operator->() ustl_cpp_noexcept
        { return    _M_data; }

        typename ustl::if_else<_Const, const_reference, reference>::type
        operator[](difference_type __idx)
        { return    *(*this + __idx); }

        friend bool
        operator==(_Self const &__l, _Self const &__r)
        { return    __l._M_data == __r._M_data; }

        friend bool
        operator!=(_Self const &__l, _Self const &__r)
        { return    __l._M_data != __r._M_data; }


    public:
        deque_iterator() = default;

        deque_iterator(const_pointer __data, _bc_pointer __bucket)
            :_M_data(const_cast<pointer>(__data))
            { _M_update(__bucket); }

        // 对非只读迭代器来说，这是一个拷贝构造函数， 对只读迭代器来说，
        // 这是一个接受非只读迭代器进行初始化的构造函数
        deque_iterator(noncv_iterator const &__non_cv)
            :_M_data(__non_cv._M_data), _M_bucket_cur((_bc_pointer)__non_cv._M_bucket_cur),
             _M_ele_first(__non_cv._M_ele_first), _M_ele_last(__non_cv._M_ele_last)
             {}

        // 数据按非只读方式存储，但对于只读迭代器，给外部留的访问接口是返回的只读数据
    public:
        pointer                    _M_data;
        pointer                    _M_ele_first;
        pointer                    _M_ele_last;
        _bc_pointer                _M_bucket_cur;
    };


    template <typename _Tp, bool _Const>
    constexpr size_t
    deque_iterator<_Tp, _Const>::
        _S_bucket_capacity() ustl_cpp_noexcept
    {
        constexpr size_t    __size = size_t(__ALLOC_BLOCK_SIZE);
        return  __size > sizeof(_Tp) ? __size / sizeof(_Tp) : 1;
    }


    template <typename _Tp, bool _Const>
    void
    deque_iterator<_Tp, _Const>::
        _M_update(_bc_pointer __new) ustl_cpp_noexcept
    {
        _M_bucket_cur =  __new;
        _M_ele_first  = *__new;
        _M_ele_last   = _M_ele_first + _S_bucket_capacity();
    }


    template <typename _Tp, bool _Const>
    auto
    deque_iterator<_Tp, _Const>::
        operator++() ustl_cpp_noexcept -> _Self &
    {
        if(_M_data == _M_ele_last - 1)
        {
            _M_update(_M_bucket_cur + 1);
            _M_data = _M_ele_first;
        }
        else
            ++_M_data;
        return  *this;
    }


    template <typename _Tp, bool _Const>
    auto
    deque_iterator<_Tp, _Const>::
        operator--() ustl_cpp_noexcept -> _Self &
    {
        if(_M_data == _M_ele_first)
        {
            _M_update(_M_bucket_cur - 1);
            _M_data = _M_ele_last - 1;
        }
        else
            --_M_data;
        return  *this;
    }


    template <typename _Tp, bool _Const>
    auto
    deque_iterator<_Tp, _Const>::
        operator++(int) ustl_cpp_noexcept -> _Self
    {
        _Self   __tmp(*this);
        ++*this;
        return  __tmp;
    }


    template <typename _Tp, bool _Const>
    auto
    deque_iterator<_Tp, _Const>::
        operator--(int) ustl_cpp_noexcept -> _Self
    {
        _Self   __tmp(*this);
        --*this;
        return  __tmp;
    }

    template <typename _Tp, bool _Const>
    auto
    deque_iterator<_Tp, _Const>::
        operator=(deque_iterator const &__other) ustl_cpp_noexcept -> _Self &
    {
        _M_data         =  __other._M_data;
        _M_ele_first    =  __other._M_ele_first;
        _M_ele_last     =  __other._M_ele_last;
        _M_bucket_cur   =  __other._M_bucket_cur;
        return  *this;
    }


    template <typename _Tp, bool _Const>
    auto
    deque_iterator<_Tp, _Const>::
        operator+(difference_type   __step) ustl_cpp_noexcept-> _Self
    {
        deque_iterator  __tmp(*this);
        __tmp += __step;
        return  __tmp;
    }


    template <typename _Tp, bool _Const>
    auto
    deque_iterator<_Tp, _Const>::
        operator-(difference_type   __step) ustl_cpp_noexcept -> _Self
    {
        deque_iterator  __tmp(*this);
        __tmp -= __step;
        return  __tmp;
    }


    template <typename _Tp, bool _Const>
    auto
    deque_iterator<_Tp, _Const>::
        operator+=(difference_type   __step) ustl_cpp_noexcept -> _Self &
    {
        constexpr size_t    __size = _S_bucket_capacity();
        if(__step > 0)
        {
            difference_type __pos = _M_ele_last - _M_data;
            if(__step >= __pos)
            {
                __step -= __pos;
                difference_type __buckets = __step / __size;
                difference_type __surplus = __step % __size;
                _M_update(_M_bucket_cur + __buckets + 1);
                _M_data = _M_ele_first + __surplus;
            }
            else
                _M_data += __step;
        }
        else
            *this -= (-__step);
        return  *this;
    }


    template <typename _Tp, bool _Const>
    auto
    deque_iterator<_Tp, _Const>::
        operator-=(difference_type   __step) ustl_cpp_noexcept -> _Self &
    {
        constexpr size_t    __size = _S_bucket_capacity();
        if(__step > 0)
        {
            size_t  __pos = _M_data - _M_ele_first;
            if(__step >= __pos)
            {
                __step -= __pos;
                difference_type __buckets = __step / __size;
                difference_type __surplus = __step % __size;
                _M_update(_M_bucket_cur - __buckets - 1);
                _M_data = _M_ele_last - __surplus;
            }
            else
                _M_data -= __step;
        }
        else
            *this += (-__step);
        return  *this;
    }


    template<typename _Tp, bool _Const>
    ustl::diff_t
    operator-(deque_iterator<_Tp, _Const> __last, deque_iterator<_Tp, _Const> __first)
    {
        diff_t  __ret = 0;
        for(;__last != __first; ++__first, (void)++__ret);
        return  __ret;
    }




/// @class ustl::deque_basic
    template <typename _Tp, typename _Alloc>
    class deque_basic
    {
        enum        { __ALLOC_BLOCK_SIZE        =   512 };
        enum        { __MIN_BUCKET_TABLE_SIZE   =   16 };

    protected:
        typedef     _Tp                     value_type;
        typedef     _Tp *                   pointer;
        typedef     _Tp &                   reference;
        typedef     _Tp const *             const_pointer;
        typedef     _Tp const &             const_reference;

        typedef     _Tp **                  _bc_pointer;
        typedef     ustl::size_t            size_type;
        typedef     ustl::diff_t            difference_type;

        typedef     deque_iterator<_Tp, false>                      iterator;
        typedef     deque_iterator<_Tp, true>                       const_iterator;
        typedef     ustl::reverse_iterator<iterator>                reverse_iterator;
        typedef     ustl::reverse_iterator<const_iterator>          const_reverse_iterator;

        typedef     _Alloc                                      _Tp_allocator_type;
        typedef     ustl::allocate_traits<_Alloc>               _Tp_allocate_traits;
        typedef     typename allocate_traits<_Alloc>::template rebind_t<pointer>    
                    _Bc_allocator_type;
        typedef     allocate_traits<_Bc_allocator_type>      
                    _Bc_allocate_traits;


    protected:
        static constexpr size_type
        _S_bucket_capacity() ustl_cpp_noexcept;


        struct deque_impl
            : _Tp_allocator_type,
              _Bc_allocator_type
        {
            size_type   
            _M_capacity() ustl_cpp_noexcept
            { return    _M_bucket_size * _S_bucket_capacity(); }


        public:
            void
            _M_reset() ustl_cpp_noexcept;

            void
            _M_move(deque_impl &__other) ustl_cpp_noexcept;

            void
            _M_swap(deque_impl &__other) ustl_cpp_noexcept;

            deque_impl &
            operator=(deque_impl const &__other) ustl_cpp_noexcept;


        public:
            deque_impl()
                : _M_bucket(0),
                  _M_begin(),
                  _M_end(),
                  _M_bucket_size(0)
            {}


        public:
            _bc_pointer         _M_bucket;
            iterator            _M_begin;
            iterator            _M_end;
            size_type           _M_bucket_size;
        };

        typedef     deque_impl          impl_type;


    protected:
        _Tp_allocator_type &
        _M_get_allocator() ustl_cpp_noexcept
        { return    _M_data_plus; }


         _Bc_allocator_type &
        _M_get_bc_allocator() ustl_cpp_noexcept
        { return    _M_data_plus; }


        pointer
        _M_allocate_bucket()
        { return    _Tp_allocate_traits::allocate(_M_get_allocator(), _S_bucket_capacity()); }


        void
        _M_deallocate_bucket(pointer __p)
        { _Tp_allocate_traits::deallocate(_M_get_allocator(), __p, _S_bucket_capacity()); }


        template <typename... _Args>
        void
        _M_construct(pointer __p, _Args &&...__init_args)
        { _Tp_allocate_traits::construct(_M_get_allocator(), __p, forward<_Args &&>(__init_args)...); }


        void
        _M_destory(pointer __p)
        { _Tp_allocate_traits::construct(_M_get_allocator(), __p); }


        void
        _M_deallocate_table(_bc_pointer __start, size_type __n)
        { _Bc_allocate_traits::deallocate(_M_get_bc_allocator(), __start, sizeof(_bc_pointer) * __n); }

        template <typename _InputIterator>
        difference_type
        _M_distance(_InputIterator __first, _InputIterator __last)
        { return    ustl::distance(__first, __last); }


    protected:
        void
        _M_deallocate_bucket(_bc_pointer __start, _bc_pointer __finish);

        _bc_pointer
        _M_allocate_table(size_type &__len);

        void
        _M_create_bucket(_bc_pointer __start, _bc_pointer __finish);

        void
        _M_destory_table(_bc_pointer __start, _bc_pointer __finish);

        void
        _M_initialize_table(size_t __element_number);


    protected:
        deque_basic()
            : _M_data_plus()
        {
            _M_initialize_table(0);
        }


    protected:
        impl_type       _M_data_plus;
    };


    template <typename _Tp, typename _Alloc>
    void
    deque_basic<_Tp, _Alloc>::
    deque_impl::
        _M_reset() ustl_cpp_noexcept
    {
        _M_bucket = 0;
        _M_begin._M_update(0);
        _M_begin._M_data = 0;
        _M_end._M_update(0);
        _M_end._M_data = 0;
        _M_bucket_size = 0;
    }


    template <typename _Tp, typename _Alloc>
    void
    deque_basic<_Tp, _Alloc>::
    deque_impl::
        _M_move(deque_impl &__other) ustl_cpp_noexcept
    {

    }



    template <typename _Tp, typename _Alloc>
    void
    deque_basic<_Tp, _Alloc>::
    deque_impl::
        _M_swap(deque_impl &__other) ustl_cpp_noexcept
    {

    }


    template <typename _Tp, typename _Alloc>
    constexpr size_t
    deque_basic<_Tp, _Alloc>::
        _S_bucket_capacity() ustl_cpp_noexcept
    {
        constexpr size_t    __size = size_t(__ALLOC_BLOCK_SIZE);
        return  __size > sizeof(_Tp) ? __size / sizeof(_Tp) : 1;
    }


    template <typename _Tp, typename _Alloc>
    void
    deque_basic<_Tp, _Alloc>::
        _M_deallocate_bucket(_bc_pointer __start, _bc_pointer __finish)
    {
        while(__start != __finish)
            _M_deallocate_bucket(*__start++);
    }


    template <typename _Tp, typename _Alloc>
    auto 
    deque_basic<_Tp, _Alloc>::
        _M_allocate_table(size_type &__len) -> _bc_pointer
    {
        __len = ustl::max(__len, size_type(__MIN_BUCKET_TABLE_SIZE));
        return  _Bc_allocate_traits::allocate(_M_get_bc_allocator(), __len);
    }


    template <typename _Tp, typename _Alloc>
    void
    deque_basic<_Tp, _Alloc>::
        _M_create_bucket(_bc_pointer __start, _bc_pointer __finish)
    {
        _bc_pointer __tmp = __start;
        __ustl_try
        {
            for (; __tmp != __finish; ++__tmp)
                *__tmp = _M_allocate_bucket();
        }
        __ustl_catch_all
        {
            _M_destory_table(__start, __tmp);
            __ustl_throw_again;
        }
    }


    template <typename _Tp, typename _Alloc>
    void
    deque_basic<_Tp, _Alloc>::
        _M_destory_table(_bc_pointer __start, _bc_pointer __end)
    {
        constexpr size_type __bucket_capacity = _S_bucket_capacity();
        for (; __start != __end; ++__start)
        {
            pointer __ele_first = *__start;
            pointer __ele_last = __ele_first + __bucket_capacity;
            for(; __ele_first != __ele_last; ++__ele_first)
                _Tp_allocate_traits::destory(_M_get_allocator(), __ele_first);
        }
    }



    template <typename _Tp, typename _Alloc>
    void
    deque_basic<_Tp, _Alloc>::
        _M_initialize_table(size_type __element_number)
    {
        size_t const __bucket_count     =   __element_number / _S_bucket_capacity() + 1;
        _M_data_plus._M_bucket_size     =   ustl::max(__element_number, size_type(__MIN_BUCKET_TABLE_SIZE));
        _M_data_plus._M_bucket          =   _M_allocate_table(_M_data_plus._M_bucket_size);
        
        _bc_pointer __new_begin         =   _M_data_plus._M_bucket + ((_M_data_plus._M_bucket_size - __bucket_count) >> 1);
        _bc_pointer __new_end           =   __new_begin + __bucket_count;

        _M_create_bucket(__new_begin, __new_end);

        _M_data_plus._M_begin._M_data   =   *__new_begin;
        _M_data_plus._M_end._M_data     =   (*(__new_end - 1) + __element_number % _S_bucket_capacity());
        _M_data_plus._M_begin._M_update(__new_begin);
        _M_data_plus._M_end._M_update(__new_end - 1);
    }



/// @class ustl::deque
    template <typename _Tp, typename _Alloc = ustl::allocator<_Tp>>
    class deque
        : deque_basic<_Tp, _Alloc>
    {
        typedef     deque_basic<_Tp, _Alloc>                _Base_type;
        typedef     typename _Base_type::_bc_pointer        _bc_pointer;


    public:
        typedef     _Tp                 value_type;
        typedef     _Tp *               pointer;
        typedef     _Tp &               reference;
        typedef     _Tp const *         const_pointer;
        typedef     _Tp const &         const_reference;
        typedef     _Alloc              allocator_type;

        typedef     typename _Base_type::iterator               iterator;
        typedef     typename _Base_type::const_iterator         const_iterator;
        typedef     typename _Base_type::reverse_iterator       reverse_iterator;
        typedef     typename _Base_type::const_reverse_iterator const_reverse_iterator;
        typedef     typename _Base_type::size_type              size_type;
        typedef     typename _Base_type::difference_type        difference_type;


    protected:
        using       _Base_type::_M_get_allocator;
        using       _Base_type::_M_get_bc_allocator;
        using       _Base_type::_M_allocate_bucket;
        using       _Base_type::_M_deallocate_bucket;
        using       _Base_type::_M_construct;
        using       _Base_type::_M_destory;
        using       _Base_type::_M_allocate_table;
        using       _Base_type::_M_deallocate_table;
        using       _Base_type::_M_destory_table;
        using       _Base_type::_M_create_bucket;
        using       _Base_type::_M_initialize_table;
        using       _Base_type::_M_distance;
        using       _Base_type::_S_bucket_capacity;


    private:
        iterator
        _M_reserve_at_back(size_type);

        iterator
        _M_reserve_at_front(size_type);

        void
        _M_new_at_back(size_type);

        void
        _M_new_at_front(size_type);

        void
        _M_relocate_table(size_type);

        void 
        _M_default_initialize();

        void
        _M_default_append(size_type, value_type const &);

        template <typename... _Args>
        iterator
        _M_insert_aux(iterator, _Args &&...);

        iterator 
        _M_insert_aux(iterator, value_type const &, size_type = 1);

        template<typename ..._Args>
        void
        _M_push_back(_Args &&...);

        template<typename ..._Args>
        void
        _M_push_front(_Args &&...);

        template <typename _ForwardIterator>
        iterator
        _M_range_insert(iterator, _ForwardIterator, _ForwardIterator);

        iterator
        _M_fill_insert(iterator,value_type const&,size_type);

        template<typename _ForwardIterator>
        void
        _M_range_initialize(_ForwardIterator __first, _ForwardIterator __last, size_type);

        iterator
        _M_erase(iterator);

        iterator
        _M_erase(iterator, iterator);

        void
        _M_erase_from_front(iterator);

        void
        _M_erase_to_back(iterator);


    public:
        iterator
        begin() 
        { return    _M_data_plus._M_begin; }

        iterator
        end() 
        { return    _M_data_plus._M_end; }

        const_iterator
        begin() const 
        { return    const_iterator(_M_data_plus._M_begin); }

        const_iterator
        end() const 
        { return    const_iterator(_M_data_plus._M_end); }

        const_iterator
        cbegin() 
        { return    const_iterator(_M_data_plus._M_begin); }

        const_iterator
        cend() 
        { return    const_iterator(_M_data_plus._M_end); }

        const_iterator
        cbegin() const 
        { return    const_iterator(_M_data_plus._M_begin); }

        const_iterator
        cend() const 
        { return    const_iterator(_M_data_plus._M_end); }

        reverse_iterator
        rbegin() 
        { return    reverse_iterator(end()); }

        reverse_iterator
        rend() 
        { return    reverse_iterator(begin()); }

        const_reverse_iterator
        rbegin() const 
        { return    const_reverse_iterator(rbegin()); }

        const_reverse_iterator
        rend() const 
        { return    const_reverse_iterator(rend()); }

        const_reverse_iterator
        crbegin() 
        { return    const_reverse_iterator(rbegin()); }

        const_reverse_iterator
        crend() 
        { return    const_reverse_iterator(rend()); }

        const_reverse_iterator
        crbegin() const 
        { return    const_reverse_iterator(rbegin()); }

        const_reverse_iterator
        crend() const 
        { return    const_reverse_iterator(rend()); }

        reference
        back() 
        { return    *_M_data_plus._M_begin; }

        reference
        front() 
        { return    *_M_data_plus._M_end; }

        const_reference
        back() const 
        { return    *_M_data_plus._M_begin; }

        const_reference
        front() const 
        { return    *_M_data_plus._M_end; }

        size_type
        capacity() 
        { return    _M_data_plus._M_capacity(); }

        size_type
        capacity() const
        { return    _M_data_plus._M_capacity(); }

        bool
        empty() 
        { return    _M_data_plus._M_begin == _M_data_plus._M_end; }

        bool
        empty() const
        { return    _M_data_plus._M_begin == _M_data_plus._M_end; }

        void 
        push_back(value_type const &__lval)
        { emplace_back(__lval); }

        void
        push_back(value_type &&__rval)
        { emplace_back(ustl::move(__rval)); }

        void 
        push_front(value_type const &__lval)
        { emplace_front(__lval); }

        void
        push_front(value_type &&__rval)
        { emplace_front(ustl::move(__rval)); }

        iterator 
        erase(const_iterator __pos)
        { return    _M_erase(__pos._M_const_cast()); }

        iterator 
        erase(const_iterator __first, const_iterator __last)
        { return    _M_erase(__first._M_const_cast(), __last._M_const_cast()); }

        void 
        swap(deque &&__rval)  ustl_cpp_noexcept
        { *this = ustl::move(__rval); }

        reference 
        operator[](size_type __idx) ustl_cpp_noexcept
        { return    const_cast<reference>((deque const)*this[__idx]); }

        iterator 
        insert(const_iterator __pos, value_type &&__rval)
        { return    emplace(__pos, __rval); }

        template <typename _ForwardIterator>
        iterator 
        insert(const_iterator __pos, _ForwardIterator __first, _ForwardIterator __last)
        { return    _M_range_insert(__pos._M_const_cast(), __first, __last); }


    public:
        void
        assign(value_type const &, size_type);

        template <typename _InputIterator>
        void 
        assign(_InputIterator, _InputIterator);

        template <typename... _Args>
        iterator 
        emplace(const_iterator, _Args &&...);

        template <typename... _Args>
        void 
        emplace_front(_Args &&...);

        template <typename... _Args>
        void 
        emplace_back(_Args &&...);

        template<typename _InputIterator>
        void
        push_front(_InputIterator, _InputIterator);

        template<typename _InputIterator>
        void
        push_back(_InputIterator, _InputIterator);

        iterator 
        insert(const_iterator, value_type const &, size_type = 1);

        void 
        pop_back();

        void 
        pop_front();

        void
        resize(size_type);

        void 
        resize(size_type, value_type const &);

        void 
        swap(deque &) ustl_cpp_noexcept;

        size_type
        size() const;

        void 
        clear();

        deque &
        operator=(deque &&) ustl_cpp_noexcept;

        deque &
        operator=(deque const &)ustl_cpp_noexcept;

        const_reference 
        operator[](size_type) const ustl_cpp_noexcept;


    public:
        deque()
            : _Base_type() {}

        deque(size_type __n, value_type const &__val)
            : _Base_type()
        { _M_default_append(__n, __val); }

        template<typename _InputIterator, typename = RequireInputItr<_InputIterator>>
        deque(_InputIterator __first, _InputIterator __last)
            : _Base_type()
        { _M_range_initialize(__first, __last, 0); }

        deque(deque const &__other)
            : _Base_type()
        { _M_range_initialize(__other.begin(), __other.end()); }

        deque(deque &&__rother)
            :_Base_type()
        { swap(ustl::move(__rother)); }


    protected:
        using       _Base_type::_M_data_plus;
    };



    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        assign(value_type const &__val, size_type __n)
    {
        iterator    __first = _M_data_plus._M_begin;
        iterator    __last = _M_data_plus._M_end;
        for(;__first != __last && 0 != __n; ++__first, (void)--__n)
            _M_construct(__first._M_data, __val);
        if(__first != __last)
            _M_erase_to_back(__first);
        if(__n)
            _M_fill_insert(end(), __val, __n);
    }



    template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
    void
    deque<_Tp, _Alloc>::
        assign(_InputIterator __first, _InputIterator __last)
    {
        iterator    __first1 = _M_data_plus._M_begin;
        iterator    __last1  = _M_data_plus._M_end;
        for(;__first != __last && __first1 != __last1; ++__first1, (void)++__first)
            _M_construct(__first1._M_data, *__first);
        if(__first1 != __last1)
            _M_erase_to_back(__first1);
        if(__first != __last)
            _M_range_insert(__last1, __first, __last);
    }



    template<typename _Tp, typename _Alloc>
    auto
    deque<_Tp,_Alloc>::
        _M_reserve_at_back(size_type __n) -> iterator
    {
        size_type const __tail_surplus = _M_data_plus._M_end._M_ele_last -
                                         _M_data_plus._M_end._M_data;
        // 使用 __n + 1是为了在末尾插入时图个方便
        if(__n + 1 > __tail_surplus)
            _M_new_at_back(__n + 1 - __tail_surplus);
        return _M_data_plus._M_end + __n;
    }



    template<typename _Tp, typename _Alloc>
    auto
    deque<_Tp,_Alloc>::
        _M_reserve_at_front(size_type __n) -> iterator
    {
        size_type const __start_surplus = _M_data_plus._M_begin._M_data - 
                                          _M_data_plus._M_begin._M_ele_first;
        if(__n + 1 > __start_surplus)
            _M_new_at_front(__n - __start_surplus);
        return  _M_data_plus._M_begin - __n;
    }



    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp,_Alloc>::
        _M_new_at_back(size_type __n) 
    {
        size_type const __add_bucket_count = (__n + _S_bucket_capacity() - 1) /
                                              _S_bucket_capacity();
        size_type __idx;
        // catch allocate exception
        _M_relocate_table(__add_bucket_count);
        __ustl_try {
            for(__idx = 0; __idx < __add_bucket_count; ++__idx)
                *(_M_data_plus._M_end._M_bucket_cur + __idx + 1) = _M_allocate_bucket();
        }
        __ustl_catch_all {
            for(size_type __r = 0; __r < __idx; ++__r)
                _M_deallocate_bucket(*(_M_data_plus._M_end._M_bucket_cur + __r + 1));
                __ustl_throw_again;
        }
    }



    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp,_Alloc>::
        _M_new_at_front(size_type __n) 
    {
        size_type __add_bucket_count = (__n + _S_bucket_capacity() - 1) /
                                        _S_bucket_capacity();
        size_type __idx;
        // catch allocate exception
        _M_relocate_table(__add_bucket_count);
        __ustl_try {
            for(__idx = 0; __idx < __add_bucket_count; ++__idx)
                *(_M_data_plus._M_begin._M_bucket_cur -__idx - 1) = _M_allocate_bucket();
        }
        __ustl_catch_all {
            for(size_type __r = 0; __r < __idx; ++__r)
                _M_deallocate_bucket(*(_M_data_plus._M_begin._M_bucket_cur - __r - 1));
            __ustl_throw_again;
        }
    }

/**
 *  @interface _M_reallocate_table(size_type)
 *  基本上是 @GNU C++ STL deque::_M_reallcoate_map(size_type, bool) 源码
 *  开源不是抄写，虽然我感觉跟抄写 @GNU source code 差不多，但是遵守开源协议，标注上来处
 *  最近不想写代码了，心态发生了问题，需要好好调整一下
 */
    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp,_Alloc>::
        _M_relocate_table(size_type __add)
    {
        if(__add > size_type(_M_data_plus._M_bucket + _M_data_plus._M_bucket_size
                           - _M_data_plus._M_end._M_bucket_cur))
        {
            size_type const __old_bucket_number = _M_data_plus._M_end._M_bucket_cur -
                                            _M_data_plus._M_begin._M_bucket_cur + 1;
            size_type const __new_bucket_number = __old_bucket_number + __add; 

            _bc_pointer __new_start;
            if(_M_data_plus._M_bucket_size > (__new_bucket_number << 1))
            {
                // 此处是为了均衡队列两端空余，使得插入与删除操作可以减少 reallocate 操作
                __new_start = _M_data_plus._M_bucket + ((_M_data_plus._M_bucket_size -
                              __new_bucket_number) >> 1);
                ustl::memmove(_M_data_plus._M_begin._M_bucket_cur,
                              __new_start, __old_bucket_number);
            }
            else // reallocate memory
            {
                size_type   __new_table_len = __old_bucket_number + (__old_bucket_number > __add 
                                            ? __old_bucket_number : __add);
                _bc_pointer __new_table = _M_allocate_table(__new_table_len);
                __new_start = __new_table + ((__new_table_len - __new_bucket_number) >> 1);
                ustl::memcopy(_M_data_plus._M_begin._M_bucket_cur, __new_start, 
                              _M_data_plus._M_end._M_bucket_cur - _M_data_plus._M_end._M_bucket_cur);
                
                // free old table
                _M_deallocate_table(_M_data_plus._M_bucket, _M_data_plus._M_bucket_size);
                _M_data_plus._M_bucket = __new_table;
                _M_data_plus._M_bucket_size = __new_table_len;
            }
            _M_data_plus._M_begin._M_update(__new_start);
            _M_data_plus._M_end._M_update(__new_start + __old_bucket_number -1);
        }
    }
    

    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp,_Alloc>::
        _M_default_initialize()
    {
        _bc_pointer     __bucket_ptr;
        __ustl_try {
            for(__bucket_ptr = _M_data_plus._M_begin; 
                __bucket_ptr != _M_data_plus._M_end; ++__bucket_ptr ) {
                ustl::constructor(*__bucket_ptr, *__bucket_ptr + _S_bucket_capacity(),
                                    _M_get_allocator());
            }
        }
        __ustl_catch_all {
            _bc_pointer     __start = _M_data_plus._M_begin;
            for( ++__bucket_ptr; __start != __bucket_ptr; ++__start) {
                    ustl::destructor(*__bucket_ptr, *__bucket_ptr + _S_bucket_capacity(),
                                    _M_get_allocator());
            }
            __ustl_throw_again;
        }
    }



    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp,_Alloc>::
        _M_default_append(size_type __n, value_type const &__val)
    {
        if(0 != __n)
        {
            iterator    __first =  _M_data_plus._M_end;
            iterator    __last  =  _M_reserve_at_back(__n);
            __ustl_try {
                for(; __first != __last; ++__first)
                    _M_construct(__first.data(), __val);
                _M_data_plus._M_end = __last;
            }
            __ustl_catch_all {
                ustl::destructor(_M_data_plus._M_end, __last,
                                 _M_get_allocator());
                __ustl_throw_again;
            }
        }
    }



    template<typename _Tp, typename _Alloc>
    template<typename _ForwardIterator>
    typename deque<_Tp,_Alloc>::iterator 
    deque<_Tp,_Alloc>::
        _M_range_insert(iterator __pos,
                        _ForwardIterator __first,
                        _ForwardIterator __last)
    {
        difference_type __len = ustl::distance(__first, __last);
        if(__len) 
        {
            difference_type  __ele_before = __pos - _M_data_plus._M_begin;
            difference_type  __ele_after  = _M_data_plus._M_end - __pos;
            if(__ele_after > __ele_before)
            {
                iterator __new_begin = _M_reserve_at_front(__len);
                ustl::relocate_forward(_M_data_plus._M_begin, __pos, __new_begin, _M_get_allocator());
                ustl::relocate_forward(__first, __last, __pos - __len, _M_get_allocator());
                _M_data_plus._M_begin = __new_begin;
            }
            else
            {
                iterator __new_last = _M_reserve_at_back(__len); // reserve new elemens space
                ustl::relocate_back(__pos, _M_data_plus._M_end, __new_last, _M_get_allocator());
                ustl::relocate_forward(__first, __last, __pos, _M_get_allocator());
                _M_data_plus._M_end = __new_last;
            }
        }
        return __pos;
    }



    template<typename _Tp, typename _Alloc>
    typename deque<_Tp,_Alloc>::iterator 
    deque<_Tp,_Alloc>::
        _M_fill_insert(iterator __pos,
                       value_type const &__val,
                       size_type __n)
    {
        if(0 != __n)
        {
            if(end() == __pos)
            {
                iterator __old_last = end();
                iterator __new_last = _M_reserve_at_back(__n);
                ustl::fill(__old_last, __new_last, __val);
                _M_data_plus._M_end = __new_last;
            } 
            else if(begin() == __pos)
            {
                iterator __new_begin = _M_reserve_at_front(__n);
                ustl::fill(__new_begin, __new_begin + __n, __val);
                _M_data_plus._M_begin = __new_begin;
            }
            else
                _M_insert_aux(__pos, __val, __n);
        }
        return __pos;
    }


    // initialization
    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    auto
    deque<_Tp,_Alloc>::
        _M_insert_aux(iterator __pos, _Args &&... __init_args) -> iterator
    {
         difference_type    __ele_before = __pos - begin();
         difference_type    __half_of_all = size() >> 1;
         if(__ele_before > __half_of_all)
         {
            iterator __old_last = end();
            iterator __new_last = _M_reserve_at_back(1);
            ustl::relocate_back(__pos, __old_last, __new_last, _M_get_allocator());
            _M_data_plus._M_end = __new_last;
         }
         else
         {
            iterator __old_start = begin();
            iterator __new_start = _M_reserve_at_front(1);
            ustl::relocate_forward(__old_start, __pos, __new_start, _M_get_allocator());
            _M_data_plus._M_begin = __new_start;
         }
         _M_construct(__pos.data(), ustl::forward<_Args &&>(__init_args)...);
         return __pos;
    }



    // copy
    template<typename _Tp, typename _Alloc>
    typename deque<_Tp, _Alloc>::iterator 
    deque<_Tp, _Alloc>::
        _M_insert_aux(iterator __pos, value_type const &__val, 
                      size_type __n) 
    {
        if(0 != __n)
        {
            difference_type    __ele_before = __pos - begin();
            difference_type    __half_of_all = size() >> 1;  
            if(__ele_before < __half_of_all) 
            {
                iterator __old_begin = begin();
                iterator __new_begin = _M_reserve_at_front(__n);
                __ustl_try {
                    ++__pos;
                    ustl::relocate_forward(__old_begin, __pos, __new_begin);
                    ustl::fill(__pos - __n, __pos, __val);
                    _M_data_plus._M_begin = __new_begin;
                }
                __ustl_catch_all {
                    _M_deallocate_bucket(__new_begin._M_bucket_cur, __old_begin._M_bucket_cur);
                    __ustl_throw_again;
                }
            }
            else
            {
                iterator __old_last = end();
                iterator __new_last = _M_reserve_at_back(__n);
                __ustl_try {
                    ustl::relocate_back(__pos, __old_last, __new_last);
                    ustl::fill(__pos, __pos + __n, __val);
                    _M_data_plus._M_end = __new_last;
                }
                __ustl_catch_all {
                    _M_destory_bucket(__old_last._M_bucket_cur, __new_last._M_bucket_cur);
                    __ustl_throw_again;
                }
            }
        }
        return  __pos;
    }



    template<typename _Tp, typename _Alloc>
    template<typename _ForwardIterator>
    void
    deque<_Tp,_Alloc>::
        _M_range_initialize(_ForwardIterator __first, _ForwardIterator __last,
                            size_type __n)
    {
        __n = __n ? __n : ustl::distance(__first, __last);
        if(0 != __n)
        {
            _M_initialize_table(__n);
            iterator __first1 = begin();
            iterator __last1  = end();
            __ustl_try {
                ustl::copy_forward(__first, __last, __first1);
            }
            __ustl_catch_all {
                _M_destory_bucket(_M_data_plus._M_begin._M_bucket_cur,
                                  _M_data_plus._M_end._M_bucket_cur);
                __ustl_throw_again;
            }
        }
    }



    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        _M_erase_from_front(iterator __end_pos)
    {
        ustl::destructor(_M_data_plus._M_begin, __end_pos, _M_get_allocator());
        _M_deallocate_bucket(_M_data_plus._M_begin._M_bucket_cur, 
                             __end_pos._M_bucket_cur);
        _M_data_plus._M_begin = __end_pos;
    }



    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        _M_erase_to_back(iterator __start_pos)
    {
        ustl::destructor(__start_pos, _M_data_plus._M_end, _M_get_allocator());
        _M_deallocate_bucket(__start_pos._M_bucket_cur + 1, 
                                   _M_data_plus._M_end._M_bucket_cur + 1);
        _M_data_plus._M_end = __start_pos;
    }



    template<typename _Tp, typename _Alloc>
    auto
    deque<_Tp, _Alloc>::
        _M_erase(iterator __pos) -> iterator
    {
        if(end() == __pos)
            return end();

        difference_type __ele_before  = __pos - _M_data_plus._M_begin;
        difference_type __half_of_all = size() >> 1;
        _M_desotry(__pos._M_data);
        if(__ele_before > __half_of_all)
        {
            iterator __last = _M_data_plus._M_end;
            ustl::relocate_forward(__pos + 1, __last, __pos, _M_get_allocator());
            --_M_data_plus._M_end;
        }
        else
        {
            iterator __first = _M_data_plus._M_begin;
            ustl::relocate_back(__first, __pos, __pos, _M_get_allocator());
            ++_M_data_plus._M_begin;
        }
        return begin() + __ele_before;
    }



    template<typename _Tp,typename _Alloc>
    auto
    deque<_Tp, _Alloc>::
        _M_erase(iterator __first, iterator __last) -> iterator
    {
        if(__first == __last)
            return __first;
        if(_M_data_plus._M_begin == __first)
            _M_erase_from_front(__last);
        else if(_M_data_plus._M_end == __last )
            _M_erase_to_back(__first);
        else
        {
            difference_type __len = __last - __first;
            difference_type __ele_before = __first - _M_data_plus._M_begin; 
            difference_type __ele_after  = _M_data_plus._M_end - __last;

            ustl::destructor(__first, __last, _M_get_allocator());
            if(__ele_after > __ele_before)
            {
                iterator __first1 = begin();
                ustl::relocate_back(__first1, __first, __last, _M_get_allocator());
                _M_data_plus._M_begin = __first1 + __len; 
            }
            else
            {
                iterator __last1 = end();
                ustl::relocate_forward(__last, __last1, __first, _M_get_allocator());
                _M_data_plus._M_end = __last1 - __len;
            }    
            return begin() + __ele_before;       
        }
        
    }



    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    void
    deque<_Tp, _Alloc>::
        _M_push_back(_Args &&...__val)
    {
        _M_reserve_at_back(1);
        __ustl_try {
            _M_construct(_M_data_plus._M_end._M_data, ustl::forward<_Args&&>(__val)...); 
            // *(_M_data_plus._M_end._M_bucket_cur + 1) = _M_allocate_bucket();
            ++_M_data_plus._M_end; 
        }
        __ustl_catch_all {
            --_M_data_plus._M_end;
            _M_deallocate_bucket(*(_M_data_plus._M_end._M_bucket_cur));
            __ustl_throw_again;
        }
    }



    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    void
    deque<_Tp, _Alloc>::
        _M_push_front(_Args &&...__val)
    {
        _M_reserve_at_front(1);
        __ustl_try {
            // *(_M_data_plus._M_begin._M_bucket_cur - 1) = _M_allocate_bucket();
            --_M_data_plus._M_begin;
            _M_construct(_M_data_plus._M_begin._M_data, ustl::forward<_Args&&>(__val)...);
            
        }
        __ustl_catch_all {
            ++_M_data_plus._M_begin;
            _M_deallocate_bucket(*(_M_data_plus._M_begin._M_bucket_cur));
            __ustl_throw_again;
        }
    }



    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    void
    deque<_Tp, _Alloc>::
        emplace_back(_Args &&... __init_args)
    {
        if(_M_data_plus._M_end._M_data != _M_data_plus._M_end._M_ele_last - 1)
        {
            _M_construct(_M_data_plus._M_end._M_data, ustl::forward<_Args &&>(__init_args)...);
            ++_M_data_plus._M_end;
        }
        else
            _M_push_back(ustl::forward<_Args &&>(__init_args)...);

    }



    template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
    void
    deque<_Tp, _Alloc>::
        push_back(_InputIterator __first, _InputIterator __last)
    {
        if(__first == __last)
            emplace_back(*__first);
        else
        {
            difference_type __len = _M_distance(__first, __last);
            iterator __new_last = _M_reserve_at_back(__len);
            ustl::constructor(_M_data_plus._M_end, __new_last, __first,_M_get_allocator());
            _M_data_plus._M_end = __new_last;
        }
    }



    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    void
    deque<_Tp, _Alloc>::
        emplace_front(_Args &&... __init_args)
    {
        if(_M_data_plus._M_begin._M_data != _M_data_plus._M_begin._M_ele_first)
        {
            --_M_data_plus._M_begin;
            _M_construct(_M_data_plus._M_begin._M_data, ustl::forward<_Args &&>(__init_args)...);
        }
        else
            _M_push_front(ustl::forward<_Args &&>(__init_args)...);
    }



    template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
    void
    deque<_Tp, _Alloc>::
        push_front(_InputIterator __first, _InputIterator __last)
    {
        if(__first == __last)
            emplace_front(*__first);
        else
        {
            difference_type __len = _M_distance(__first, __last);
            iterator __new_begin = _M_reserve_at_front(__len);
            ustl::constructor(__new_begin, _M_data_plus._M_begin, __first, _M_get_allocator());
            _M_data_plus._M_begin = __new_begin;
        }
    }



    template<typename _Tp, typename _Alloc>
    auto
    deque<_Tp, _Alloc>::
        insert(const_iterator __pos, value_type const &__val, size_type __n) -> iterator
    {
        if(__pos._M_data == _M_data_plus._M_begin._M_data)
        {
            push_front(__val);
            return  _M_data_plus._M_begin;
        }
        else if(__pos._M_data == _M_data_plus._M_end._M_data)
        {
            push_back(__val);
            return  __pos._M_const_cast();
        }
        else
            return _M_insert_aux(__pos._M_const_cast(), __val, __n);
    }



    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    auto
    deque<_Tp, _Alloc>::
        emplace(const_iterator __pos, _Args &&...__init_args) -> iterator
    {
        if(__pos._M_data == _M_data_plus._M_begin._M_data)
        {
            emplace_front(ustl::forward<_Args &&>(__init_args)...);
            return  _M_data_plus._M_begin;
        }
        else if(__pos._M_data == _M_data_plus._M_end._M_data)
        {
            emplace_back(ustl::forward<_Args &&>(__init_args)...);
            return  __pos._M_const_cast();
        }
        else
            return _M_insert_aux(__pos._M_const_cast(), ustl::forward<_Args &&>(__init_args)...);
    }



    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        pop_back()
    {
        --_M_data_plus._M_end;
        _M_desotry(_M_data_plus._M_end._M_data);
        if(_M_data_plus._M_end._M_data == _M_data_plus._M_end._M_ele_first)
        {
            _bc_pointer __free = _M_data_plus._M_end._M_bucket_cur;
            _M_destory_bucket(__free, __free + 1);
            --_M_data_plus._M_end;
            _M_data_plus._M_end._M_data = *(_M_data_plus._M_end._M_bucket_cur) + _S_bucket_capacity();
        }
    }



    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        pop_front()
    {
        _M_desotry(_M_data_plus._M_begin._M_data);
        ++_M_data_plus._M_begin;
        if(_M_data_plus._M_begin._M_data == _M_data_plus._M_begin._M_ele_last)
        {
            _bc_pointer __free = _M_data_plus._M_begin._M_bucket_cur;
            _M_deallocate_bucket(__free, __free + 1);
            ++_M_data_plus._M_begin;
        }
        
    }
    


    template<typename _Tp, typename _Alloc>
    inline void
    deque<_Tp, _Alloc>::
        resize(size_type __n)
    {
        size_type   __old_size = size();
        if(__n > __old_size)
            _M_default_append(__n - __old_size);
    }



    template<typename _Tp, typename _Alloc>
    inline void
    deque<_Tp, _Alloc>::
        resize(size_type __n, value_type const &__val)
    {
        size_type   __old_size = size();
        if(__n > __old_size)
            _M_fill_insert(_M_data_plus._M_end, __val, __n - __old_size);
    }



    template<typename _Tp, typename _Alloc>
    inline void
    deque<_Tp, _Alloc>::
        swap(deque &__lval) ustl_cpp_noexcept
    {
        if(&__lval != this)
            _M_data_plus._M_swap();
    }



    template<typename _Tp, typename _Alloc>
    inline void
    deque<_Tp, _Alloc>::
        clear()
    {
        _M_erase_from_front(_M_data_plus._M_end);
        _M_data_plus._M_reset();
    }



    template<typename _Tp, typename _Alloc>
    auto
    deque<_Tp, _Alloc>::
        operator[](size_type __idx) const ustl_cpp_noexcept -> const_reference
    {
        constexpr  size_type __bucket_capacity = _S_bucket_capacity();
        if(__idx > size())
            __ustl_throw_array_length("deque::operator=(): array access overflap");

        _bc_pointer __start = _M_data_plus._M_begin._M_bucket_cur;
        _bc_pointer __finish = _M_data_plus._M_end._M_bucket_cur;
        size_type   __first_bc = _M_data_plus._M_begin._M_ele_last - _M_data_plus._M_begin._M_data;

        bool    __in_first_bucket = difference_type(__idx - __first_bc) < 0 ? true : false;

        if(__in_first_bucket)
                return  *(_M_data_plus._M_begin._M_data + __idx);

        __idx -= __first_bc;
        size_type   __in_bucket = __idx / __bucket_capacity;
        size_type   __offset = __idx % __bucket_capacity;
        return  *(*(__start + __in_bucket + 1) + __offset);
    }



    template<typename _Tp, typename _Alloc>
    auto
    deque<_Tp, _Alloc>::
        size() const -> size_type 
    {
        size_type   __totality(0);
        if(_M_data_plus._M_begin != _M_data_plus._M_end)
        {
            _bc_pointer __start = _M_data_plus._M_begin._M_bucket_cur;
            _bc_pointer __finish = _M_data_plus._M_end._M_bucket_cur;
            size_type   __full_number = __finish - __start - 1;
            size_type   __first_bc = _M_data_plus._M_begin._M_ele_last - _M_data_plus._M_begin._M_data;
            size_type   __last_bc  = _M_data_plus._M_end._M_data - _M_data_plus._M_end._M_ele_first;
            __totality = __first_bc + __last_bc + __full_number * _S_bucket_capacity();
        }
        return __totality;
    }

    

    template<typename _Tp, typename _Alloc>
    inline auto
    deque<_Tp, _Alloc>::
        operator=(deque const &__val) ustl_cpp_noexcept -> deque & 
    {
        assign(__val.begin(), __val.end());
        return *this;
    }



    template<typename _Tp, typename _Alloc>
    inline auto
    deque<_Tp, _Alloc>::
        operator=(deque &&__rval) ustl_cpp_noexcept -> deque &
    {
        if(&__rval != this)
        {
            clear();
            _M_data_plus._M_swap();
        } 
        return  *this;
    }



    template<typename _Tp, typename _Alloc>
    bool
    operator==(deque<_Tp, _Alloc> const &__l, deque<_Tp, _Alloc> const &__r) ustl_cpp_noexcept
    {
        typedef typename deque<_Tp, _Alloc>::iterator iterator;
        iterator __first  = __l.begin();
        iterator __last   = __l.end();
        iterator __first1 = __r.begin();
        iterator __last1  = __r.end();

        while( __first1 != __last1 && __first != __last && *__first1 == *__first)
             ++__first1, (void) ++__first;
            
        return  __first1 == __last1 && __first == __last;
    }


    template<typename _Tp, typename _Alloc>
    inline bool
    operator!=(deque<_Tp, _Alloc> const &__l, deque<_Tp, _Alloc> const &__r) ustl_cpp_noexcept
    { return    !(__l == __r); }


} // namespace ustl

#endif
