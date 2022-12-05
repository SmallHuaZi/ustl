#ifndef __ustl_deque_h
#define __ustl_deque_h

#include "config.h"

#define _DEQUE_ALLOC_SIZE 512

namespace ustl
{
    static inline constexpr size_t
    _S_size_of_bucket(size_t __size)
    {
        return _DEQUE_ALLOC_SIZE > __size ? _DEQUE_ALLOC_SIZE / __size : 1;
    }

    template <typename _Tp, typename _Ref, typename _Ptr>
    struct deque_iterator
    {
        typedef     _Tp                     value_type;
        typedef     _Ref                    reference;
        typedef     _Ptr                    _ele_pointer;
        typedef     _Ptr *                  _bc_pointer;
        typedef     ustl::_random_iterator   iterator_tag;
        typedef     ustl::diff_t            difference_type;
        typedef     deque_iterator          _Self;


    public:
        void
        _M_update(_bc_pointer __new_bucket)
        {
            _M_bucket_cur = __new_bucket;
            _M_ele_first = *__new_bucket;
            _M_ele_last = _M_ele_first + _S_size_of_bucket(sizeof(_Tp));
        }

        _Self &
        operator++()
        {
            if (_M_data == _M_ele_last)
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
                _M_data = _M_ele_last;
            }
            --_M_data;

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

        reference
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

        _ele_pointer        _M_data;
        _ele_pointer        _M_ele_first;
        _ele_pointer        _M_ele_last;
        _bc_pointer         _M_bucket_cur;
    };

    template <typename _Tp, typename _Alloc>
    struct deque_impl
        : _Alloc,
          _Alloc::template rebind<_Tp *>::other
    {
        typedef     _Tp *       _ele_pointer;
        typedef     _Tp **      _bc_pointer;
        typedef     deque_iterator<_Tp, _Tp &, _Tp *>   iterator;

        static constexpr size_t
        _M_bucket_capacity() ustl_cpp_noexcept
        { return    _S_size_of_bucket(sizeof(_Tp)); }

        size_t
        _M_capacity() ustl_cpp_noexcept
        { return    _M_bucket_size * _M_bucket_capacity(); }

        size_t
        _M_ele_size() ustl_cpp_noexcept
        { return    size_t(_M_end - _M_begin); }

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

        typedef     deque_iterator<_Tp, _Tp &, _Tp *>               iterator;
        typedef     deque_iterator<_Tp, _Tp const &, _Tp const *>   const_iterator;
        typedef     ustl::reverse_iterator<iterator>                reverse_iterator;
        typedef     ustl::reverse_iterator<const_iterator>          const_reverse_iterator;

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
        { return    const_iterator(begin()); }

        const_iterator
        end() const 
        { return    const_iterator(end()); }

        const_iterator
        cbegin() 
        { return    const_iterator(begin()); }

        const_iterator
        cend() 
        { return    const_iterator(end()); }

        const_iterator
        cbegin() const 
        { return    const_iterator(begin()); }

        const_iterator
        cend() const 
        { return    const_iterator(end()); }

        reverse_iterator
        rbegin() 
        { return    reverse_iterator(begin()); }

        reverse_iterator
        rend() 
        { return    reverse_iterator(end()); }

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

        size_type
        size() 
        { return    _M_data_plus._M_ele_size(); }

        size_type
        size() const
        { return    _M_data_plus._M_ele_size(); }

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
        void 
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

        template <typename _ForwardIterator>
        void 
        assign(_ForwardIterator, _ForwardIterator);

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

        void 
        push_back(value_type const &);
        void
        push_back(value_type &&);

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

        void pop_back();
        void pop_front();

        void
        resize(size_type);
        void 
        resize(size_type, value_type const &);

        void 
        swap(deque &)   ustl_cpp_noexcept;

        void 
        swap(deque &&)  ustl_cpp_noexcept;

        void 
        clear();

        deque &
        operator=(deque &&)     ustl_cpp_noexcept;

        deque &
        operator=(deque const &)ustl_cpp_noexcept;

        reference 
        operator[](size_type);

        const_reference 
        operator[](size_type) const;

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
    auto
    deque<_Tp,_Alloc>::
        _M_reserve_at_back(size_type __n) -> iterator
    {
        size_type const __tail_surplus = _M_data_plus._M_end._M_ele_last -
                                         _M_data_plus._M_end._M_data;
        // 使用 __n + 1是为了在末尾插入时图个方便
        if(__n + 1 > __tail_surplus)
            _M_new_at_back(__n - __tail_surplus);
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
            for(__idx = 1; __idx < __add_bucket_count; ++__idx)
                *(_M_data_plus._M_end._M_bucket_cur + __idx) = _M_allocate_bucket();
        }
        __ustl_catch_all {
            for(size_type __r = 1; __r < __idx; ++__r)
                _M_deallocate_bucket(*(_M_data_plus._M_end._M_bucket_cur + __idx));
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
            for(__idx = 1; __idx < __add_bucket_count; ++__idx)
                *(_M_data_plus._M_begin._M_bucket_cur -__idx) = _M_allocate_bucket();
        }
        __ustl_catch_all {
            for(size_type __r = 1; __r < __idx; ++__r)
                _M_deallocate_bucket(*(_M_data_plus._M_begin._M_bucket_cur - __idx));
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
            iterator __last = end();
            iterator __new_last = _M_reserve_at_back(__len); // reserve new elemens space
            ustl::relocate_back(__pos, __pos + __len, __new_last);
            ustl::relocate_forward(__first, __last, __pos);
            _M_data_plus._M_begin = __new_last;
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
            _M_data_plus._M_end = -__new_last;
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
    void 
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
        _M_deallocate_bucket_table(__start_pos._M_bucket_cur, 
                                   _M_data_plus._M_end._M_bucket_cur);
        _M_data_plus._M_end = __start_pos;
    }

    template<typename _Tp, typename _Alloc>
    auto
    deque<_Tp, _Alloc>::
        _M_erase(iterator __pos) -> iterator
    {
        if(end() == __pos)
            return end();

        difference_type __ele_before  = __pos - begin();
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
        if(begin() == __first &&  end() == __last)
        {
            clear();
            return end();
        }

        difference_type __len = __last - __first;
        difference_type __ele_before = __first - _M_data_plus._M_begin; 
        difference_type __ele_after  = _M_data_plus._M_end - __last;

        ustl::destructor(__first, __last, _M_get_allocator());
        if(__ele_after > __ele_before)
        {
            iterator __first1 = begin();
            ustl::relocate_back(__first1, __first, __last);
            _M_data_plus._M_begin = __first1 + __len; 
        }
        else
        {
            iterator __last1 = end();
            ustl::relocate_forward(__last, __last1, __first);
            _M_data_plus._M_end = __last1 - __len;
        }
        return begin() + __ele_before;
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
            *(_M_data_plus._M_end._M_bucket_cur + 1) = _M_allocate_bucket();
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
            *(_M_data_plus._M_begin._M_bucket_cur - 1) = _M_allocate_bucket();
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
            _M_construct(_M_data_plus._M_end._M_data, __val);
            ++_M_data_plus._M_end;
        }
        else
            _M_push_back(ustl::forward<value_type const &>(__val));
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
            _M_construct(_M_data_plus._M_begin._M_data, ustl::forward<value_type const&>(__val));
            --_M_data_plus._M_begin;
        }
        else
            _M_push_front(ustl::forward<value_type const&>(__val));
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

} // namespace ustl

#endif
