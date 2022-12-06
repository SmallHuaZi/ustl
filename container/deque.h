#ifndef __ustl_deque_h
#define __ustl_deque_h

#include "include/config.h"

#define _DEQUE_ALLOC_SIZE 512

namespace ustl
{
    static inline constexpr size_t
    _S_size_of_bucket(size_t __size)
    {
        return _DEQUE_ALLOC_SIZE > __size ? _DEQUE_ALLOC_SIZE / __size : 1;
    }

    template <typename _Tp, bool _Const>
    struct deque_iterator
    {

        typedef     _Tp                     value_type;
        typedef     _Tp *                   pointer;
        typedef     _Tp &                   reference;
        typedef     _Tp const *             const_pointer; 
        typedef     _Tp const &             const_reference;
        typedef     ustl::_random_iterator  iterator_tag;
        typedef     ustl::diff_t            difference_type;

        typedef     deque_iterator          _Self;
        typedef     deque_iterator<_Tp, false>      noncv_iterator;

        typedef     _Tp **                  _bc_pointer;


    public:
        void
        _M_update(_bc_pointer __new_bucket)
        {
            _M_bucket_cur = __new_bucket;
            _M_ele_first = *__new_bucket;
            _M_ele_last = _M_ele_first + _S_size_of_bucket(sizeof(_Tp));
        }

        noncv_iterator 
       _M_const_cast()
       {
            return noncv_iterator(_M_data, _M_bucket_cur);
       }

        _Self &
        operator++()
        {
            if (_M_data == _M_ele_last - 1)
            {
                _M_update(_M_bucket_cur + 1);
                _M_data = _M_ele_first;
            }
            else
                ++_M_data;
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
            if (_M_data == _M_ele_first)
            {
                _M_update(_M_bucket_cur - 1);
                _M_data = _M_ele_last - 1;
            }
            else
                --_M_data;
            return *this;
        }

        _Self
        operator--(int)
        {
            _Self __ret(*this);
            --*this;
            return __ret;
        }

        typename ustl::if_else<_Const, const_reference, reference>::type
        operator*()
        {
            return *_M_data;
        }

        typename ustl::if_else<_Const, const_pointer, pointer>::type
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

        typename ustl::if_else<_Const, const_reference, reference>::type
        operator[](difference_type __idx)
        {
            return *(*this + __idx);
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
        pointer                    _M_data;
        pointer                    _M_ele_first;
        pointer                    _M_ele_last;
        _bc_pointer                _M_bucket_cur;
    };


    template<typename _Tp, bool _Const>
    ustl::diff_t
    operator-(deque_iterator<_Tp, _Const> __last, deque_iterator<_Tp, _Const> __first)
    {
        diff_t  __ret = 0;
        for(;__last != __first; ++__first, (void)++__ret);
        return  __ret;
    }

    template <typename _Tp, typename _Alloc>
    struct deque_impl
        : _Alloc,
          _Alloc::template rebind<_Tp *>::other
    {
        typedef     _Tp *       _ele_pointer;
        typedef     _Tp **      _bc_pointer;
        typedef     deque_iterator<_Tp, false>   iterator;

        static constexpr size_t
        _M_bucket_capacity() ustl_cpp_noexcept
        { return    _S_size_of_bucket(sizeof(_Tp)); }

        size_t
        _M_capacity() ustl_cpp_noexcept
        { return    _M_bucket_size * _M_bucket_capacity(); }

        size_t
        _M_ele_size() ustl_cpp_noexcept
        { return    size_t(_M_end - _M_begin); }

        void
        _M_reset()
        {
            _M_bucket = 0;
            _M_bucket_size = 0;
            _M_begin._M_update(0);
            _M_begin._M_data = 0;
            _M_end._M_update(0);
            _M_end._M_data = 0;
        }

        void
        _M_swap(deque_impl &__other)
        {
            deque_impl __tmp(*this);
            *this = __other;
            __other = this;
        }

        deque_impl &
        operator=(deque_impl &__r)
        {
            _M_bucket = __r._M_bucket;
            _M_begin = __r._M_begin;
            _M_end = __r._M_end;
            _M_bucket_size = __r._M_bucket_size;
        }

        deque_impl()
            : _M_bucket(0), _M_begin(),
              _M_end(), _M_bucket_size(0)
        {}

        _bc_pointer     _M_bucket;
        iterator        _M_begin;
        iterator        _M_end;
        size_t          _M_bucket_size;
    };

    template <typename _Tp, typename _Alloc>
    class deque_basic
    {
    protected:
        typedef     _Tp             value_type;
        typedef     _Tp *           pointer;
        typedef     _Tp &           reference;
        typedef     _Tp const *     const_pointer;
        typedef     _Tp const &     const_reference;
        typedef     _Alloc          allocator_type;
        typedef     ustl::size_t    size_type;
        typedef     ustl::diff_t    difference_type;
        typedef     _Tp **          _bc_pointer;

        typedef     deque_iterator<_Tp, false>            iterator;
        typedef     deque_iterator<_Tp, true>             const_iterator;
        typedef     ustl::reverse_iterator<iterator>            reverse_iterator;
        typedef     ustl::reverse_iterator<const_iterator>      const_reverse_iterator;

        typedef     deque_impl<_Tp, _Alloc>           impl_type;
        typedef     allocate_traits<_Alloc>           _Ele_allocator_traits;
        typedef     typename allocate_traits<_Alloc>::template rebind<pointer>::other       
                        _Bc_allocator_type;
        typedef     allocate_traits<_Bc_allocator_type>      _Bc_allocator_traits;

        enum { __MIN_BUCKET_TABLE_SIZE = 16 };

        /** private interface */
        allocator_type &
        _M_get_allocator()
        { return    _M_data_plus; }

         _Bc_allocator_type &
        _M_get_bc_allocator()
        { return    _M_data_plus; }

        pointer
        _M_allocate_bucket()
        {
            constexpr size_t __default_size = _S_size_of_bucket(sizeof(_Tp));
            return _Ele_allocator_traits::allocate(_M_get_allocator(), __default_size);
        }

        void
        _M_deallocate_bucket(pointer __p)
        {
            constexpr size_t __default_size = _S_size_of_bucket(sizeof(_Tp));
            _Ele_allocator_traits::deallocate(_M_get_allocator(), __p, __default_size);
        }

        void
        _M_deallocate_bucket(_bc_pointer __start, _bc_pointer __finish)
        {
            for(; __start != __finish; ++__start)
                _M_deallocate_bucket(*__start);
        }

        _bc_pointer
        _M_allocate_bucket_table(size_type &__len)
        {
            __len = ustl::max(__len, size_type(__MIN_BUCKET_TABLE_SIZE));
            return _Bc_allocator_traits::allocate(_M_get_bc_allocator(), __len);
        }

        void
        _M_deallocate_bucket_table(_bc_pointer __start, _bc_pointer __finish)
        {
            for(; __start != __finish; ++__start)
                _Bc_allocator_traits::deallocate(_M_get_bc_allocator(), __start, 1);
        }

        void
        _M_destory_bucket(_bc_pointer __start, _bc_pointer __end)
        {
            constexpr size_type __bucket_capacity = _S_size_of_bucket(sizeof(_Tp));
            for (; __start != __end; ++__start)
            {
                pointer __ele_first = *__start;
                pointer __ele_last = __ele_first + __bucket_capacity;
                for(; __ele_first != __ele_last; ++__ele_first)
                    _M_desotry(__ele_first);
            }
        }

        void
        _M_create_bucket(_bc_pointer __start, _bc_pointer __end)
        {
            _bc_pointer __tmp = __start;
            __ustl_try
            {
                for (; __tmp != __end; ++__tmp)
                    *__tmp = _M_allocate_bucket();
            }
            __ustl_catch_all
            {
                _M_destory_bucket(__start, __tmp);
                __ustl_throw_again;
            }
        }

        void
        _M_initialize_table(size_t __element_number)
        {
            size_t const __bucket_count     =   __element_number / _S_size_of_bucket(sizeof(_Tp)) + 1;
            _M_data_plus._M_bucket_size     =   ustl::max(__element_number, size_type(__MIN_BUCKET_TABLE_SIZE));
            _M_data_plus._M_bucket          =   _M_allocate_bucket_table(_M_data_plus._M_bucket_size);
            
            _bc_pointer __new_begin         =   _M_data_plus._M_bucket + ((_M_data_plus._M_bucket_size - __bucket_count) >> 1);
            _bc_pointer __new_end           =   __new_begin + __bucket_count;

            _M_create_bucket(__new_begin, __new_end);

            _M_data_plus._M_begin._M_data   =   *__new_begin;
            _M_data_plus._M_end._M_data     =   (*(__new_end - 1) + __element_number % _S_size_of_bucket(sizeof(_Tp)));
            _M_data_plus._M_begin._M_update(__new_begin);
            _M_data_plus._M_end._M_update(__new_end - 1);
        }

        template <typename... _Args>
        void
        _M_construct(pointer __p, _Args &&...__init_args)
        {
            _Ele_allocator_traits::construct(_M_get_allocator(), __p,
                                             ustl::forward<_Args &&>(__init_args)...);
        }

        void
        _M_desotry(pointer __p)
        {
            _Ele_allocator_traits::destory(_M_get_allocator(), __p);
        }

        deque_basic()
            : _M_data_plus()
        {
            _M_initialize_table(0);
        }

        impl_type       _M_data_plus;
    };

    template <typename _Tp, typename _Alloc = ustl::allocator<_Tp>>
    class deque
        : public deque_basic<_Tp, _Alloc>
    {
        typedef     deque_basic<_Tp, _Alloc>                _Base_type;
        typedef     typename _Base_type::_bc_pointer        _bc_pointer;

    public:
        typedef     _Tp             value_type;
        typedef     _Tp *           pointer;
        typedef     _Tp &           reference;
        typedef     _Tp const *     const_pointer;
        typedef     _Tp const &     const_reference;
        typedef     _Alloc          allocator_type;
        typedef     ustl::diff_t    difference_type;
        typedef     ustl::size_t    size_type;

        typedef     typename _Base_type::iterator               iterator;
        typedef     typename _Base_type::const_iterator         const_iterator;
        typedef     typename _Base_type::reverse_iterator       reverse_iterator;
        typedef     typename _Base_type::const_reverse_iterator const_reverse_iterator;

    public:
        deque()
            : _Base_type() {}

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
        _M_default_append(size_type);

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

        void 
        push_front(value_type const &);
        void
        push_front(value_type &&);
        template<typename _InputIterator>
        void
        push_front(_InputIterator, _InputIterator);

        void 
        push_back(value_type const &);
        void
        push_back(value_type &&);
        void
        push_back(size_type, ...);
        template<typename _InputIterator>
        void
        push_back(_InputIterator, _InputIterator);

        iterator 
        insert(const_iterator, value_type &&);

        iterator 
        insert(const_iterator, value_type const &, size_type = 1);

        template <typename _ForwardIterator>
        iterator 
        insert(const_iterator, _ForwardIterator, _ForwardIterator);

        iterator 
        erase(const_iterator);

        iterator 
        erase(const_iterator, const_iterator);

        void 
        pop_back();
        void 
        pop_front();

        void
        resize(size_type);
        void 
        resize(size_type, value_type const &);

        void 
        swap(deque &)   ustl_cpp_noexcept;

        void 
        swap(deque &&)  ustl_cpp_noexcept;

        size_type
        size();

        size_type
        size() const;

        void 
        clear();

        deque &
        operator=(deque &&)     ustl_cpp_noexcept;

        deque &
        operator=(deque const &)ustl_cpp_noexcept;

        reference 
        operator[](size_type) ustl_cpp_noexcept;

        const_reference 
        operator[](size_type) const ustl_cpp_noexcept;

    protected:
        using   _Base_type::_M_get_allocator;
        using   _Base_type::_M_get_bc_allocator;
        using   _Base_type::_M_allocate_bucket;
        using   _Base_type::_M_allocate_bucket_table;
        using   _Base_type::_M_construct;
        using   _Base_type::_M_deallocate_bucket;
        using   _Base_type::_M_deallocate_bucket_table;
        using   _Base_type::_M_desotry;
        using   _Base_type::_M_destory_bucket;
        using   _Base_type::_M_initialize_table;

    protected:
        using   _Base_type::_M_data_plus;
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
        size_type const __add_bucket_count = (__n +_S_size_of_bucket(sizeof(_Tp)) - 1) /
                                              _S_size_of_bucket(sizeof(_Tp));
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
        size_type __add_bucket_count = (__n +_S_size_of_bucket(sizeof(_Tp)) - 1) /
                                        _S_size_of_bucket(sizeof(_Tp));
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
                _bc_pointer __new_table = _M_allocate_bucket_table(__new_table_len);
                __new_start = __new_table + ((__new_table_len - __new_bucket_number) >> 1);
                ustl::memcopy(_M_data_plus._M_begin._M_bucket_cur, __new_start, 
                              _M_data_plus._M_end._M_bucket_cur - _M_data_plus._M_end._M_bucket_cur);
                
                // free old table
                _M_deallocate_bucket_table(_M_data_plus._M_bucket, 
                                           _M_data_plus._M_bucket + _M_data_plus._M_bucket_size);
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
                ustl::constructor(*__bucket_ptr, *__bucket_ptr + _S_size_of_bucket(sizeof(_Tp)),
                                    _M_get_allocator());
            }
        }
        __ustl_catch_all {
            _bc_pointer     __start = _M_data_plus._M_begin;
            for( ++__bucket_ptr; __start != __bucket_ptr; ++__start) {
                    ustl::destructor(*__bucket_ptr, *__bucket_ptr + _S_size_of_bucket(sizeof(_Tp)),
                                    _M_get_allocator());
            }
            __ustl_throw_again;
        }
    }

    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp,_Alloc>::
        _M_default_append(size_type __n)
    {
        if(0 != __n)
        {
            iterator    __last =  _M_reserve_at_back(__n);
            __ustl_try {
                ustl::constructor(_M_data_plus._M_end, __last,
                                  _M_get_allocator());
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
         _M_construct(&*__pos, ustl::forward<_Args &&>(__init_args)...);
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
    void
    deque<_Tp, _Alloc>::
        push_back(value_type const &__val)
    {
        if(_M_data_plus._M_end._M_data != _M_data_plus._M_end._M_ele_last - 1)
        {
            if(!_M_data_plus._M_end._M_data)
                int a = 10;
            _M_construct(_M_data_plus._M_end._M_data, __val);
            ++_M_data_plus._M_end;
        }
        else
            _M_push_back(ustl::forward<value_type const &>(__val));
    }


    /*  unsafe method:  user must ensure uncertain parameter
        is the constructor parameter of _Tp  */
    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        push_back(size_type __n, ...)
    {
        if(__n)
        {
            pointer __start = static_cast<pointer>(((size_type*)&__n + 1));
            iterator __new_last = _M_reserve_at_back(__n);
            iterator __ctor_start = __new_last - __n;
            for(;__new_last != __ctor_start; ++__ctor_start, (void)++__start)
                *__ctor_start = *__start;
            _M_data_plus._M_end = __new_last;
        }
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
            difference_type __len = __last - __first;
            iterator __new_last = _M_reserve_at_back(__len);
            ustl::constructor(_M_data_plus._M_end, __new_last, __first,_M_get_allocator());
            _M_data_plus._M_end = __new_last;
        }
    }

    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        push_back(value_type &&__rval)
    {
        if(_M_data_plus._M_end._M_data != _M_data_plus._M_end._M_ele_last - 1)
        {
            _M_construct(_M_data_plus._M_end._M_data, ustl::forward<value_type &&>(__rval));
            ++_M_data_plus._M_end;
        }
        else
            _M_push_back(ustl::forward<value_type &&>(__rval));
    }

    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        push_front(value_type const &__val)
    {
        if(_M_data_plus._M_begin._M_data != _M_data_plus._M_begin._M_ele_first)
        {
            --_M_data_plus._M_begin;
            _M_construct(_M_data_plus._M_begin._M_data, ustl::forward<value_type const&>(__val));
        }
        else
            _M_push_front(ustl::forward<value_type const&>(__val));
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
            difference_type __len = __last - __first;
            iterator __new_begin = _M_reserve_at_front(__len);
            ustl::constructor(__new_begin, _M_data_plus._M_begin, __first, _M_get_allocator());
            _M_data_plus._M_begin = __new_begin;
        }
    }

    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        push_front(value_type &&__rval)
    {
        if(_M_data_plus._M_begin._M_data != _M_data_plus._M_begin._M_ele_first)
        {
            --_M_data_plus._M_begin;
            _M_construct(_M_data_plus._M_begin._M_data, ustl::forward<value_type &&>(__rval));
        }
        else
            _M_push_front(ustl::forward<value_type &&>(__rval));
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
    auto
    deque<_Tp, _Alloc>::
        insert(const_iterator __pos, value_type const &__val, size_type __n) -> iterator
    {
        if(__pos._M_data == _M_data_plus._M_begin._M_data)
        {
            push_front(__val);
        }
        else if(__pos._M_data == _M_data_plus._M_end._M_data)
        {
            push_back(__val);
        }
        else
            return _M_insert_aux(__pos._M_const_cast(), __val, __n);
    }

    template<typename _Tp, typename _Alloc>
    auto
    deque<_Tp, _Alloc>::
        insert(const_iterator __pos, value_type &&__rval) -> iterator
    {
        if(__pos._M_data == _M_data_plus._M_begin._M_data)
        {
            push_front(ustl::move(__rval));
            return  _M_data_plus._M_begin;
        }
        else if(__pos._M_data == _M_data_plus._M_end._M_data)
        {
            push_back(ustl::move(__rval));
            return  __pos._M_const_cast();
        }
        else
            return _M_insert_aux(__pos._M_const_cast(), ustl::move(__rval));
    }

    template<typename _Tp, typename _Alloc>
    template<typename _ForwardIterator>
    auto
    deque<_Tp, _Alloc>::
        insert(const_iterator __pos, _ForwardIterator __first,
               _ForwardIterator __last) -> iterator
    {
        return _M_range_insert(__pos._M_const_cast(), __first, __last);
    }

    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    auto
    deque<_Tp, _Alloc>::
        emplace(const_iterator __pos, _Args &&...__init_args) -> iterator
    {
        if(__pos._M_data == _M_data_plus._M_begin._M_data)
            emplace_front(ustl::forward<_Args &&>(__init_args)...);
        else if(__pos._M_data == _M_data_plus._M_end._M_data)
            emplace_back(ustl::forward<_Args &&>(__init_args)...);
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
            _M_data_plus._M_end._M_data = *(_M_data_plus._M_end._M_bucket_cur) + _S_size_of_bucket(sizeof(_Tp));
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
    typename deque<_Tp, _Alloc>::iterator
    deque<_Tp, _Alloc>::
        erase(const_iterator __pos)
    {
        _M_erase(__pos._M_const_cast());
    }

    template<typename _Tp, typename _Alloc>
    typename deque<_Tp, _Alloc>::iterator
    deque<_Tp, _Alloc>::
        erase(const_iterator __first, const_iterator __last)
    {
        _M_erase(__first._M_const_cast(), __last._M_const_cast());
    }

    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        resize(size_type __n)
    {
        size_type   __old_size = size();
        if(__n > __old_size)
            _M_default_append(__n - __old_size);
    }

    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        resize(size_type __n, value_type const &__val)
    {
        size_type   __old_size = size();
        if(__n > __old_size)
            _M_fill_insert(_M_data_plus._M_end, __val, __n - __old_size);
    }

    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        swap(deque &__lval) ustl_cpp_noexcept
    {
        if(&__lval != this)
            _M_data_plus._M_swap();
    }

    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        swap(deque &&__rval) ustl_cpp_noexcept
    {
        if(&__rval != this)
        {
            clear();
            _M_data_plus._M_swap();
        }
    }


    template<typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
        clear()
    {
        _M_erase_from_front(_M_data_plus._M_end);
        _M_data_plus._M_reset();
    }

    template<typename _Tp, typename _Alloc>
    auto
    deque<_Tp, _Alloc>::
        operator[](size_type __idx) ustl_cpp_noexcept -> reference
    {
        const deque &__cv = *this;
        return  const_cast<reference>(__cv[__idx]);
    }

    template<typename _Tp, typename _Alloc>
    auto
    deque<_Tp, _Alloc>::
        operator[](size_type __idx) const ustl_cpp_noexcept -> const_reference
    {
        constexpr  size_type __bucket_capacity = _S_size_of_bucket(sizeof(_Tp));
        if(__idx > size())
            __throw_array_length("deque::operator=(): array access overflap");

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
        size() -> size_type
    {
        const deque *__cv = this;
        return __cv->size();
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
            __totality = __first_bc + __last_bc + __full_number * _S_size_of_bucket(sizeof(_Tp));
        }
        return __totality;
    }

    
    template<typename _Tp, typename _Alloc>
    auto
    deque<_Tp, _Alloc>::
        operator=(deque const &__val) ustl_cpp_noexcept -> deque & 
    {
        assign(__val.begin(), __val.end());
        return *this;
    }

    template<typename _Tp, typename _Alloc>
    auto
    deque<_Tp, _Alloc>::
        operator=(deque &&__rval) ustl_cpp_noexcept -> deque &
    {
        swap(ustl::move(__rval));
        return *this;
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
    {
        return !(__l == __r);
    }


} // namespace ustl

#endif
