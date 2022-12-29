#ifndef __USTL_SINGLE_LIST_H
#define __USTL_SINGLE_LIST_H

#include "container/slist_fwd.h"
#include "allocator/memory.h"
#include "algorithm/math.h"

namespace ustl
{
    template <typename _Tp>
    struct slist_node
        : slist_node_basic
    {
        typedef     _Tp                 value_type;
        typedef     _Tp *               pointer;
        typedef     _Tp &               reference;
        typedef     _Tp const *         const_pointer;
        typedef     _Tp const &         const_reference;


    public:
        pointer
        _M_valptr()
        { return &_M_value_field; }


        reference
        _M_value()
        { return _M_value_field; }


        slist_node *
        next()
        { return    static_cast<slist_node *>(_M_next); }


    public:
        slist_node() = default;

        slist_node(int a) { _M_value_field = a; }


    public:
        value_type          _M_value_field;
    };


    template <typename _Tp, bool _Const>
    struct slist_iterator
    {
        typedef     _Tp                             value_type;
        typedef     _Tp *                           pointer;
        typedef     _Tp &                           reference;
        typedef     _Tp const *                     const_pointer;
        typedef     _Tp const &                     const_reference;
        typedef     ustl::diff_t                    difference_type;
        typedef     ustl::_forword_iterator         iterator_tag;

        typedef     slist_node<_Tp> *               _Node_pointer;
        typedef     slist_iterator                  _Self;
        typedef     slist_iterator<_Tp, false>      noncv_iterator;


    public:
        _Self &
        operator++() ustl_cpp_noexcept;

        _Self &
        operator+=(difference_type  __step) ustl_cpp_noexcept;

        _Self
        operator++(int) ustl_cpp_noexcept;

        _Self
        operator+(difference_type   __step) ustl_cpp_noexcept;


    public:
        typename ustl::if_else<_Const, const_reference, reference>::type 
        operator*() ustl_cpp_noexcept
        { return    static_cast<_Node_pointer>(_M_data)->_M_value(); }


        typename ustl::if_else<_Const, const_pointer, const_pointer>::type 
        operator->() ustl_cpp_noexcept
        { return    static_cast<_Node_pointer>(_M_data)->_M_valptr(); }


        _Node_pointer 
        data() ustl_cpp_noexcept
        { return    static_cast<_Node_pointer>(_M_data); }


        noncv_iterator
        _M_const_cast() ustl_cpp_noexcept
        { return    noncv_iterator(_M_data); }


        friend bool
        operator==(_Self const &__l, _Self const &__r) ustl_cpp_noexcept
        { return    __l._M_data == __r._M_data; }


        friend bool
        operator!=(_Self const &__l, _Self const &__r) ustl_cpp_noexcept
        { return    __l._M_data != __r._M_data; }


    public:
        slist_iterator() = default;

        slist_iterator(slist_node_basic *__data)
            : _M_data(__data)
        {}

        slist_iterator(noncv_iterator const &__non_cv)
            : _M_data(__non_cv._M_data)
        {}

    public:
        slist_node_basic    *_M_data;
    };


    template <typename _Tp, bool _Const>
    inline auto 
    slist_iterator<_Tp, _Const>::
        operator++() ustl_cpp_noexcept -> slist_iterator &
    {
        _M_data = _M_data->_M_next;
        return  *this;
    }


    template <typename _Tp, bool _Const>
    inline auto 
    slist_iterator<_Tp, _Const>::
        operator++(int) ustl_cpp_noexcept -> slist_iterator
    {
        _Self   __tmp(*this);
        _M_data = _M_data->_M_next;
        return  __tmp;
    } 


    template <typename _Tp, bool _Const>
    inline auto 
    slist_iterator<_Tp, _Const>::
        operator+=(difference_type   __step) ustl_cpp_noexcept -> slist_iterator &
    {
        while(__step--)
            _M_data = _M_data->_M_next;
        return  *this;
    }

    template <typename _Tp, bool _Const>
    inline auto 
    slist_iterator<_Tp, _Const>::
        operator+(difference_type   __step) ustl_cpp_noexcept -> slist_iterator
    {
        _Self   __tmp(*this);
        __tmp += __step;
        return  __tmp;
    }



    /// @class ustl::slist_basic

    template <typename _Tp, typename _Alloc>
    struct slist_basic
    {
        typedef     slist_node<_Tp>                 _Node_type;
        typedef     slist_node<_Tp> *               _Node_pointer;
        typedef     slist_node<_Tp> const *         _CNode_pointer;
        typedef     slist_node_basic *              _Node_base_pointer;
        typedef     slist_node_basic const *        _CNode_base_pointer;


    protected:
        typedef     _Tp                         value_type;
        typedef     _Tp *                       pointer;
        typedef     _Tp const *                 const_pointer;
        typedef     _Tp &                       reference;
        typedef     _Tp const &                 const_reference;
        typedef     _Alloc                      allocator_type;

        typedef     ustl::size_t                        size_type;
        typedef     ustl::diff_t                        difference_type;
        typedef     slist_iterator<_Tp, false>          iterator;
        typedef     slist_iterator<_Tp, true>           const_iterator;

        typedef     ustl::allocate_traits<_Alloc>       
                    _Tp_allocate_traits;
        typedef     typename _Tp_allocate_traits::template rebind_t<_Node_type>
                    _Node_allocator_type;
        typedef     ustl::allocate_traits<_Node_allocator_type>
                    _Node_allocate_traits;


    protected:
        template <typename _CompPredicate>
        struct slist_compare
            : slist_compare_basic
        {
            virtual bool
            operator()(slist_node_basic *__x, slist_node_basic *__y) const override
            { 
                return     _M_compare(static_cast<_Node_pointer>(__x)->_M_value(), 
                                      static_cast<_Node_pointer>(__y)->_M_value()); 
            }


        public:
            slist_compare(_CompPredicate const &__cmp)
                : _M_compare(__cmp)
            {}


        protected:
            _CompPredicate          _M_compare;
        };

        template <typename _CompPredicate = ustl::less_t<_Tp>>
        using   compare_t   =     slist_compare<_CompPredicate>;


        struct slist_impl
            : _Node_allocator_type
        {
            void
            _M_swap(slist_impl &__other) ustl_cpp_noexcept;

            void
            _M_move(slist_impl &__ohter) ustl_cpp_noexcept;

            void
            _M_reset() ustl_cpp_noexcept;

        public: 
            slist_header    _M_header;
        };

        typedef     slist_impl          impl_type;
        typedef     typename _Node_allocate_traits::template rebind_t<impl_type>
                    _Impl_allocator_type;
        typedef     allocate_traits<_Impl_allocator_type>   
                    _Impl_allocate_traits;
    

    protected:
        template <typename ..._Args>
        _Node_pointer 
        _M_get_node(_Args &&... __init_args);

        void
        _M_put_node(_Node_base_pointer __first, _Node_base_pointer __last);


    protected:
        _Node_allocator_type &
        _M_get_allocator() ustl_cpp_noexcept
        { return    *_M_data_plus; }


        _Node_pointer
        _M_allocate(size_t __n) 
        { _Node_allocator_type::allocate(_M_get_allocator(), 1); }


        void
        _M_deallocate(_Node_pointer __p) ustl_cpp_noexcept
        { _Node_allocate_traits::deallocate(_M_get_allocator(), __p, sizeof(_Node_type)); }


    protected:
        template <typename _ImplAlloc, typename _ATraits = allocate_traits<_ImplAlloc>>
        slist_basic(_ImplAlloc &__impl_allocator)
            : _M_data_plus(_ATraits::allocate(__impl_allocator, 1))
        { _ATraits::construct(__impl_allocator, _M_data_plus); }


        slist_basic(slist_basic const &__other)
            : slist_basic()
        {}

        slist_basic(slist_basic &&__other)
        { 
            _M_data_plus = __other._M_data_plus;
            __other._M_data_plus = 0;
        }

        ~slist_basic()
        {
            _Impl_allocator_type    __tmp;
            _Impl_allocate_traits::destory(__tmp, _M_data_plus);
            _Impl_allocate_traits::deallocate(__tmp, _M_data_plus, sizeof(impl_type));
        }


    protected:  
        impl_type               *_M_data_plus;
    };



    template <typename _Tp, typename _Alloc>
    void
    slist_basic<_Tp, _Alloc>::
    slist_impl::
        _M_move(slist_impl &__other) ustl_cpp_noexcept
    {
        _M_header._M_next = __other._M_header._M_next;
        _M_header._M_last = __other._M_header._M_last;
        __other._M_header._M_next = 0;
        __other._M_header._M_last = 0;
    }


    template <typename _Tp, typename _Alloc>
    void
    slist_basic<_Tp, _Alloc>::
    slist_impl::
        _M_swap(slist_impl &__other) ustl_cpp_noexcept
    {
        if(&__other != this)
        {
            slist_impl      __tmp(*this);
            _M_move(__other);
            __other._M_move(__tmp);
        }
    }


    template <typename _Tp, typename _Alloc>
    inline void
    slist_basic<_Tp, _Alloc>::
    slist_impl::
        _M_reset() ustl_cpp_noexcept
    {
        _M_header._M_next = 0;
        _M_header._M_last = 0;
    }


    template <typename _Tp, typename _Alloc>
    template <typename ..._Args>
    auto
    slist_basic<_Tp, _Alloc>::
        _M_get_node(_Args &&...__init_args) -> _Node_pointer
    {
            _Node_pointer __new = _Node_allocate_traits::allocate(_M_get_allocator(), 1);
            /** catch construct exception */
            __ustl_try
            {
                _Node_allocate_traits::construct(
                        _M_get_allocator(),
                        static_cast<_Node_pointer>(__new)->_M_valptr(),
                        ustl::forward<_Args &&>(__init_args)...);
            }
            __ustl_catch_all
            {
                _M_deallocate(__new);
                __ustl_throw_again;
            }
            return __new;
    }


    template <typename _Tp, typename _Alloc>
    void
    slist_basic<_Tp, _Alloc>::
        _M_put_node(_Node_base_pointer __first, _Node_base_pointer __last)
    {
        for(; __first != __last; __first = __first->_M_next)
        {
            _Node_allocate_traits::destory(_M_get_allocator(), static_cast<_Node_pointer>(__first)->_M_valptr());
            _Node_allocate_traits::deallocate(_M_get_allocator(), __first, sizeof(_Node_type));
        }
    }




/// @class  ustl::slist
    template <typename _Tp, typename _Alloc = ustl::allocator<_Tp>>
    class slist
        : slist_basic<_Tp, _Alloc>
    {
        typedef     slist_basic<_Tp, _Alloc>            _Base_type;
    public:
        typedef     _Tp                                 value_type;
        typedef     _Tp *                               pointer;
        typedef     _Tp &                               reference;
        typedef     _Tp const *                         const_pointer;
        typedef     _Tp const &                         const_reference;

        typedef     typename _Base_type::size_type              size_type;
        typedef     typename _Base_type::difference_type        difference_type;
        typedef     typename _Base_type::allocator_type         allocator_type;
        typedef     typename _Base_type::iterator               iterator;
        typedef     typename _Base_type::const_iterator         const_iterator;
        typedef     typename _Base_type::impl_type              impl_type;

    private:
        typedef     typename _Base_type::_Node_pointer          _Node_pointer;
        typedef     typename _Base_type::_CNode_pointer         _CNode_pointer;
        typedef     typename _Base_type::_Node_base_pointer     _Node_base_pointer;
        typedef     typename _Base_type::_CNode_base_pointer    _CNode_base_pointer;
        typedef     typename _Base_type::_Impl_allocator_type   _Impl_allocator_type;
        typedef     typename _Base_type::_Impl_allocate_traits  _Impl_allocate_traits;

        template <typename _CompPredicate = ustl::less_t<_Tp>>
        using   compare_t = typename _Base_type::compare_t<_CompPredicate>;

    
    protected:
        using       _Base_type::_M_get_node;
        using       _Base_type::_M_put_node;


    public:
        _Node_base_pointer
        _M_front() ustl_cpp_noexcept
        { return    _M_data_plus->_M_header._M_next; }

        _Node_base_pointer
        _M_back() ustl_cpp_noexcept
        { return    _M_data_plus->_M_header._M_last; }

        void
        _M_front(_Node_base_pointer __p) ustl_cpp_noexcept
        { _M_data_plus->_M_header._M_next = __p; }

        void
        _M_back(_Node_base_pointer __p) ustl_cpp_noexcept
        { _M_data_plus->_M_header._M_last = __p; }

        slist_header *
        _M_header() ustl_cpp_noexcept
        { return    &_M_data_plus->_M_header; }

        static _Node_base_pointer
        _S_next(_Node_base_pointer __p) ustl_cpp_noexcept
        { return    __p->_M_next; }

        static _Node_base_pointer
        _S_extract_node(const_iterator __pos) ustl_cpp_noexcept
        { return    __pos.data(); }
 

    private:
        void 
        _M_assign_aux(const_iterator, value_type const &, size_type);

        template <typename _ForwardIterator>
        void 
        _M_range_assign(const_iterator, _ForwardIterator, _ForwardIterator);

        template <typename... _Args>
        void 
        _M_fill(size_type, _Args &&...);

        template <typename _ForwardIterator>
        void 
        _M_fill_range(const_iterator, _ForwardIterator, _ForwardIterator);

        slist & 
        _M_splice_after(const_iterator, const_iterator, const_iterator);

        template <typename... _Args>
        void 
        _M_emplace_back(_Args &&...);

        template <typename... _Args>
        iterator 
        _M_emplace_after(const_iterator, _Args &&...);

        void 
        _M_erase_after(const_iterator);

        difference_type 
        _M_erase_after_range(const_iterator, const_iterator);


    public:
        reference
        front() 
        { return    *_M_front(); }


        reference
        back() 
        { return    *_M_back(); }


        iterator
        before_begin() 
        { return    iterator(_M_header()); }


        iterator
        begin() 
        { return    iterator(_M_front()); }


        iterator
        end() 
        { return    iterator(0); }


        const_iterator
        before_begin() const 
        { return    const_iterator(_M_header()); }


        const_iterator
        begin() const 
        { return    const_iterator(_M_front()); }


        const_iterator
        end() const 
        { return    const_iterator(0); }


        const_iterator
        cbegin() 
        { return    const_iterator(_M_front()); }


        const_iterator
        cbefore_begin() 
        { return    const_iterator(_M_header()); }


        const_iterator
        cend() 
        { return    const_iterator(0); }


        const_iterator
        cbefore_begin() const 
        { return    const_iterator(_M_header()); }


        const_iterator
        cbegin() const 
        { return    const_iterator(_M_front()); }


        const_iterator
        cend() const 
        { return    const_iterator(0); }


        bool
        empty() const
        { return    _M_data_plus->_M_next == _M_data_plus->_M_last; }


        void 
        reverse() ustl_cpp_noexcept
        { _slist_reverse(_M_header()); }


        template <typename _Predicate = ustl::less_t<_Tp>>
        void 
        merge(slist &__other, _Predicate __cmp = _Predicate()) ustl_cpp_noexcept
        { _slist_merge(_M_header(), __other._M_header(), compare_t<_Predicate>(__cmp)); }


        template <typename _Predicate = ustl::less_t<_Tp>>
        void 
        merge(slist &&__other, _Predicate __cmp = _Predicate()) ustl_cpp_noexcept
        { _slist_merge(_M_header(), __other._M_header(), compare_t<_Predicate>(__cmp)); }


        template <typename _Predicate = ustl::less_t<_Tp>>
        void 
        sort(_Predicate __cmp = _Predicate()) ustl_cpp_noexcept
        { _slist_sort(_M_header(), compare_t<_Predicate>(__cmp)); }


        void 
        assign(value_type const &__val, size_type __n)
        { _M_assign_aux(__val, __n); }


        template <typename _ForwardIterator>
        void 
        assign(_ForwardIterator __first, _ForwardIterator __last)
        { _M_range_assign(__first, __last); }


        template <typename... _Args>
        void 
        emplace_after(const_iterator __pos, _Args &&...__init_args)
        { _M_emplace_after(__pos, ustl::forward<_Args &&>(__init_args)...); }


        template <typename... _Args>
        void 
        emplace_back(_Args &&...__init_args)
        { _M_emplace_back(ustl::forward<_Args &&>(__init_args)...); }


        template <typename... _Args>
        void 
        emplace_front(_Args &&...__init_args)
        { _M_emplace_after(cbefore_begin(), ustl::forward<_Args &&>(__init_args)...); }
        

        void 
        push_back(value_type const &__val)
        { _M_emplace_back(__val); }


        void 
        push_front(value_type const &__val)
        { _M_emplace_after(cbefore_begin(), __val); }


        iterator
        insert_after(const_iterator __pos, value_type const &__val)
        { return    _M_emplace_after(__pos, __val); }


        void 
        pop_front() ustl_cpp_noexcept
        { _M_erase_after(cbefore_begin()); }


        iterator
        erase_after(const_iterator __del) ustl_cpp_noexcept
        { return    _M_erase_after(__del); }


        difference_type
        erase_range(const_iterator __before, const_iterator __last)
        { return    ; }

        slist &
        splice_after(const_iterator __pos, slist &, const_iterator __before, const_iterator __last)
        { return    _M_splice_after(__pos, __before, __last); }


    public:
        iterator
        insert_after(const_iterator __pos, value_type const &__val, size_type __n);

        template <typename _ForwardIterator>
        iterator 
        insert_after(const_iterator, _ForwardIterator, _ForwardIterator);

        slist &
        splice_after(const_iterator, value_type, size_type);

        slist &
        splice_after(const_iterator, slist &);

        slist &
        splice_after(const_iterator, slist &, const_iterator);

        template <typename _ForwardIterator>
        slist &
        splice_after(const_iterator, _ForwardIterator, _ForwardIterator);

        size_type 
        remove(value_type const &) ustl_cpp_noexcept;

        template <typename _Predicate>
        size_type 
        remove_if(_Predicate) ustl_cpp_noexcept;

        void 
        swap(slist &);

        void 
        swap(slist &&);

        void 
        resize(size_type);

        void 
        resize(size_type, value_type const &);

        void 
        clear();


    public:
        template <typename _ImplAlloc = _Impl_allocator_type>
        slist(_ImplAlloc const &__impl_allocator = _ImplAlloc())
            : _Base_type(__impl_allocator)
        {}

        slist(slist const &__lother)
            : slist()
        { _M_range_assign(__lother.begin(), __lother.en()); }

        slist(slist &&__rother)
            : _Base_type(ustl::move(__rother))
        {}

        slist(value_type const &__val, size_type __n)
            : slist()
        { _M_assign_aux(__val, __n); }

        template <typename _ForwardIterator>
        slist(_ForwardIterator __frist, _ForwardIterator __last)
            : slist()
        { _M_range_assign(__frist, __last); }

        ~slist()
        { clear(); }


    protected:
        using       _Base_type::_M_data_plus;
    };



    template <typename _Tp, typename _Alloc>
    void
    slist<_Tp, _Alloc>::
        _M_assign_aux(const_iterator __pos, value_type const &__val, size_type __n)
    {
        size_type __counter = __n;
        iterator __first = begin();
        for (; __counter; --__counter, (void)++__first)
        {
            *__first = __val;
        }
        if (__counter)
            _M_fill(__counter, __val);
        else
            _M_erase_after_range(__first, end());
    }



    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    void
    slist<_Tp, _Alloc>::
        _M_range_assign(const_iterator __pos,
                       _ForwardIterator __first,
                       _ForwardIterator __last)
    {
        size_type __counter = 0;
        iterator __begin = begin();
        while (__first != __last)
        {
            *__begin = *__first;
            ++__begin, (void)++__first;
        }
        if (__first != __last)
            _M_fill_range(_M_back(), __first, __last);
    }


    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    typename slist<_Tp, _Alloc>::iterator
    slist<_Tp, _Alloc>::
        _M_emplace_after(const_iterator __pos,
                        _Args &&...__init_args)
    {
        _Node_base_pointer __pos_node = _S_extract_node(__pos);
        _Node_base_pointer __new_node = _M_get_node(ustl::forward<_Args &&>(__init_args)...);
        __new_node->_M_next = __pos_node->_M_next;
        __pos_node->_M_next = __new_node;
        return iterator(__new_node);
    }


    template <typename _Tp, typename _Alloc>
    void
    slist<_Tp, _Alloc>::
        _M_erase_after(const_iterator __pos)
    {
        _Node_base_pointer __pos_node = _S_extract_node(__pos);
        _Node_base_pointer __del = _S_next(__pos_node);
        if (__del)
        {
            __pos_node->_M_next = __del->_M_next;
            _M_put_node(__del, __del->_M_next);
        }
    }

    template <typename _Tp, typename _Alloc>
    auto
    slist<_Tp, _Alloc>::
        _M_erase_after_range(const_iterator __before,
                             const_iterator __last) -> difference_type
    {
        _Node_base_pointer __bef = _M_const_cast(__before).data();
        _Node_base_pointer __end = _M_const_cast(__last).data();
        _Node_base_pointer __tmp = _S_next(__bef);
        __bef->_M_next = __end;
        difference_type __counter = 0;
        while (__tmp != __end)
        {
            __bef = __tmp->_M_next;
            _M_put_node(__tmp);
            __tmp = __bef;
            --__counter;
        }
        return __counter;
    }



    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    void
    slist<_Tp, _Alloc>::
        _M_fill(size_type __n, _Args &&...__init_args)
    {
        _Node_base_pointer __tmp = _M_back();
        while (__n--)
        {
            _Node_base_pointer __new = _M_get_node(ustl::forward<_Args &&>(__init_args)...);
            __new->_M_hook(__tmp);
            __tmp = _S_next(__tmp);
        }
    }



    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    void
    slist<_Tp, _Alloc>::
        _M_fill_range(const_iterator __pos,
                      _ForwardIterator __first,
                      _ForwardIterator __last)
    {
        _Node_pointer __tmp = static_cast<_Node_pointer>(_S_extract_node(__pos));
        for (; __first != __last; ++__first)
        {
            _Node_pointer __next = static_cast<_Node_pointer>(_S_next(__tmp));
            __next = static_cast<_Node_pointer>(_M_get_node(*__first));
            __tmp->_M_next = __next;
            __tmp = __next;
        }
        _M_back(__tmp);
    }



    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    void
    slist<_Tp, _Alloc>::
        _M_emplace_back(_Args &&...__init_args)
    {
        _Node_base_pointer __p = _M_back();
        _Node_base_pointer __new_back = _M_get_node(ustl::forward<_Args &&>(__init_args)...);
        __p->_M_next = __new_back;
        _M_back(__new_back);
    }



    template <typename _Tp, typename _Alloc>
    auto 
    slist<_Tp, _Alloc>::
        _M_splice_after(const_iterator __pos,
                        const_iterator __before,
                        const_iterator __last) -> slist &
    {
        _Node_base_pointer __p = _S_extract_node(__pos);
        _Node_base_pointer __begin = _S_extract_node(__before);
        _Node_base_pointer __end = _S_extract_node(__last);

        __end = slist_node_basic::_S_find_pre(__begin, __end);

        __p->_M_transer_after(__begin, __end);
    }



    template <typename _Tp, typename _Alloc>
    auto
    slist<_Tp, _Alloc>::
        insert_after(const_iterator __pos,
                     value_type const &__val,
                     size_type __n) -> iterator
    {
        slist __tmp(__n, __val);
        if (__tmp.empty())
        {
            _M_splice_after(__pos, __tmp.cbefore_begin(), __tmp.cend());
            __tmp.clear();
        }
        return iterator(_S_extract_node(__pos));
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
            __tmp.clear();
        }
        return iterator(_S_extract_node(__pos));
    }



    template <typename _Tp, typename _Alloc>
    inline auto
    slist<_Tp, _Alloc>::
        splice_after(const_iterator __pos, slist &,
                     const_iterator __pos1) -> slist &
    {
        if(end() != __pos1)
        {
            const_iterator  __last = __pos1;
            __last += 2;
            _M_splice_after(__pos, __pos1, __last);
        }
        return  *this;
    }


    template <typename _Tp, typename _Alloc>
    auto
    slist<_Tp, _Alloc>::
        splice_after(const_iterator __pos,
                     slist &__other) -> slist &
    {
        if (!__other.empty())
        {
            _M_splice_after_after(__pos, __other.before_begin(), __other.end());
            __other.clear();
        }
        return  *this;
    }



    template <typename _Tp, typename _Alloc>
    typename slist<_Tp, _Alloc>::size_type
    slist<_Tp, _Alloc>::
        remove(value_type const &__val) ustl_cpp_noexcept
    {
        size_type __del_counter = 0;
        _Node_base_pointer __first = _M_header();
        while (0 != __first->_M_next)
        {
            _Node_base_pointer __next = __first->_M_next;
            if (__val == static_cast<_Node_pointer>(__next)->_M_value())
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
        _Node_base_pointer __first = _M_header();
        while (0 != __first->_M_next)
        {
            _Node_base_pointer __next = __first->_M_next;
            if (__comp(static_cast<_Node_pointer>(__next)->_M_value()))
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
    void
    slist<_Tp, _Alloc>::
        swap(slist &__other)
    {
        if (this == &__other)
            return;
        _M_data_plus._M_swap(__other._M_data_plus);
    }


    template <typename _Tp, typename _Alloc>
    void
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
        resize(size_type __new_size)
    {
        size_type __old_size = 0;
        iterator __first = begin();
        iterator __last  = end();
        for(; __first != __last; ++__first)
            ++__old_size;
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
        size_type __old_size = 0;
        iterator __first = begin();
        iterator __last  = end();
        for(; __first != __last; ++__first)
            ++__old_size;
        if (__new_size > __old_size)
        {
            size_type __add_len = __new_size - __old_size;
            _M_fill(__add_len, __val);
            _M_change_length(__add_len);
        }
    }


    template <typename _Tp, typename _Alloc>
    void
    slist<_Tp, _Alloc>::
        clear()
    {
        _M_put_node(_M_front(), _M_back());
        _M_data_plus._M_reset();
    }

} // namespace ustl::slist

#endif