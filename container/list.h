#ifndef __List_h
#define __list_h

#include "container/list_fwd.h"
#include "allocator/memory.h"
#include "iterator/iterator.h"
#include "iterator/reverse_iterator.h"
#include "algorithm/math.h"
#include "type/iterator_type.h"

namespace ustl
{
    /**
     * @brief ring list
     *              header
     *        suc          pre
     *        /\            /\
     *       /                \
     *     /                    \
     *   /                        \
     *  \/                        \/
     *  A <----> B <----> C <----> D
     */
    template <typename _Tp>
    struct _list_node
        : list_node_basic
    {
        typedef     _Tp                 value_type;
        typedef     _Tp *               pointer;
        typedef     _Tp &               reference;
        typedef     _Tp const *         const_pointer;
        typedef     _Tp const &         const_reference;
        typedef     list_node_basic     _Base_type;

    public:
        pointer
        _M_valptr() ustl_cpp_noexcept
        { return    &_M_value_field; }


        reference
        _M_value() ustl_cpp_noexcept
        { return    _M_value_field; }


        const_pointer
        _M_valptr() const ustl_cpp_noexcept
        { return    &_M_value_field; }


        const_reference
        _M_value() const ustl_cpp_noexcept
        { return    _M_value_field; }


        _list_node()
            : _Base_type() {}

    public:
        value_type          _M_value_field;
    };




    template <typename _Tp, bool _Const>
    struct list_iterator
    {
        typedef     _Tp                     value_type;
        typedef     _Tp *                   pointer;
        typedef     _Tp &                   reference;
        typedef     _Tp const *             const_pointer;
        typedef     _Tp const &             const_reference;
        typedef     ustl::diff_t            difference_type;

        typedef     list_iterator                   _Self;
        typedef     ustl::_bothway_iterator         iterator_tag;
        typedef     list_iterator<_Tp, false>       noncv_iterator;
    
    protected:
        typedef     list_node_basic *               _Node_base_pointer;
        typedef     list_node_basic *               _CNode_base_pointer;
        typedef     _list_node<_Tp> *               _Node_pointer;
        typedef     _list_node<_Tp> const *         _CNode_pointer;


    public:
        _Self &
        operator++() ustl_cpp_noexcept;

        _Self &
        operator--() ustl_cpp_noexcept;

        _Self
        operator++(int) ustl_cpp_noexcept;

        _Self
        operator--(int) ustl_cpp_noexcept;

        _Self
        operator+(difference_type   __step) ustl_cpp_noexcept;

        _Self
        operator-(difference_type   __step) ustl_cpp_noexcept;

        _Self &
        operator+=(difference_type  __step) ustl_cpp_noexcept;

        _Self &
        operator-=(difference_type  __step)ustl_cpp_noexcept;


        typename ustl::if_else<_Const, const_pointer, pointer>::type
        operator->() ustl_cpp_noexcept
        { return    static_cast<_Node_pointer>(_M_current)->_M_valptr(); }


        typename ustl::if_else<_Const, const_reference, reference>::type
        operator*() ustl_cpp_noexcept
        { return    static_cast<_Node_pointer>(_M_current)->_M_value(); }


        noncv_iterator
        _M_const_cast() ustl_cpp_noexcept
        { return    noncv_iterator(_M_current); }


        _Node_pointer
        _M_data() ustl_cpp_noexcept
        { return    static_cast<_Node_pointer>(_M_current); }


    public:
        friend bool
        operator==(_Self const &__l, _Self const &__r) ustl_cpp_noexcept
        { return    __l._M_current == __r._M_current; }


        friend bool
        operator!=(_Self const &__l, _Self const &__r) ustl_cpp_noexcept
        { return    __l._M_current != __r._M_current; }


        explicit list_iterator() = default;

        explicit list_iterator(_Node_base_pointer __p)
            : _M_current(__p)
        {}

        explicit list_iterator(noncv_iterator const &__other)
            : _M_current(__other._M_current)
        {}


    protected:
        _Node_base_pointer       _M_current;
    };



    template <typename _Tp, bool _Const>
    inline auto
    list_iterator<_Tp, _Const>::
        operator++() ustl_cpp_noexcept -> _Self &
    {
        _M_current = _M_current->_M_next;
        return  *this;
    }



    template <typename _Tp, bool _Const>
    inline auto
    list_iterator<_Tp, _Const>::
        operator--() ustl_cpp_noexcept -> _Self &
    {
        _M_current = _M_current->_M_last;
        return  *this;
    }



    template <typename _Tp, bool _Const>
    inline auto
    list_iterator<_Tp, _Const>::
        operator++(int) ustl_cpp_noexcept -> _Self
    {
        _Node_pointer   __tmp = _M_current;
        _M_current = _M_current->_M_next;
        return  _Self(__tmp);
    }



    template <typename _Tp, bool _Const>
    inline auto
    list_iterator<_Tp, _Const>::
        operator--(int) ustl_cpp_noexcept -> _Self 
    {
        _Node_pointer   __tmp = _M_current;
        _M_current = _M_current->_M_last;
        return  _Self(__tmp);
    }



    template <typename _Tp, bool _Const>
    inline auto
    list_iterator<_Tp, _Const>::
        operator+(difference_type   __step) ustl_cpp_noexcept -> _Self
    {
        _Self   __tmp(*this);
        return  __tmp += __step;
    }



    template <typename _Tp, bool _Const>
    inline auto
    list_iterator<_Tp, _Const>::
        operator-(difference_type   __step) ustl_cpp_noexcept -> _Self 
    {
        _Self   __tmp(*this);
        return  __tmp -= __step;
    }



    template <typename _Tp, bool _Const>
    inline auto
    list_iterator<_Tp, _Const>::
        operator-=(difference_type   __step) ustl_cpp_noexcept -> _Self &
    {
        for(; 0 < __step; --__step)
            _M_current = _M_current->_M_last;
        if(0 < __step)
            *this += (-__step);
        return  *this;
    }

    template <typename _Tp, bool _Const>
    inline auto
    list_iterator<_Tp, _Const>::
        operator+=(difference_type   __step) ustl_cpp_noexcept -> _Self &
    {
        for(; 0 < __step; --__step)
            _M_current = _M_current->_M_next;
        if(0 < __step)
            *this -= (-__step);
        return  *this;
    }



    template <typename _Tp, typename _Alloc>
    struct list_basic
    {
    protected:
        typedef     _list_node<_Tp>                 _Node_type;
        typedef     _list_node<_Tp> *               _Node_pointer;
        typedef     _list_node<_Tp> const *         _CNode_pointer;
        typedef     list_node_basic *               _Node_base_pointer; 
        typedef     list_node_basic const *         _CNode_base_pointer; 
        typedef     list_header *                   _Header_pointer;
    
    public:
        typedef     _Tp                         value_type; 
        typedef     _Tp *                       pointer;
        typedef     _Tp &                       reference;
        typedef     _Tp const *                 const_pointer;
        typedef     _Tp const &                 const_reference;
        typedef     ustl::size_t                size_type;
        typedef     ustl::diff_t                difference_type;
        typedef     _Alloc                      allocator_type;

        typedef     list_iterator<_Tp, false>                       iterator;
        typedef     list_iterator<_Tp, true>                        const_iterator;
        typedef     ustl::reverse_iterator<iterator>                reverse_iterator;
        typedef     ustl::reverse_iterator<const_iterator>          const_reverse_iterator;

        typedef     typename ustl::allocate_traits<_Alloc>::template rebind_t<_Node_type>
                    _Node_allocator_type;
        typedef     ustl::allocate_traits<_Alloc>                   _Tp_allocate_traits;
        typedef     ustl::allocate_traits<_Node_allocator_type>     _Node_allocate_traits;


    protected:
        template <typename _CompPredicate>
        struct list_compare
            : list_compare_basic
        {

            static_assert(ustl::is_same<bool (_CompPredicate::*)(_Tp const &, _Tp const &) const, decltype(&_CompPredicate::operator())>::value ||
                          ustl::is_same<bool (_CompPredicate::*)(_Tp &, _Tp &) const, decltype(&_CompPredicate::operator())>::value   ||
                          ustl::is_same<bool (_CompPredicate::*)(_Tp, _Tp) const, decltype(&_CompPredicate::operator())>::value,
                          "list_basic::list_compare template parameter -> _CompPredicate::operator() invaild convert to bool"
                          " (_CompPredicate::*)(_Tp const &, _Tp const &) or bool (_CompPredicate::*(_Tp, _Tp) !");

            virtual bool
            operator()(list_node_basic *__x, list_node_basic *__y) const 
#ifdef  ustl_cpp_noexcept
            noexcept(noexcept(_CompPredicate()(_Tp(), _Tp()))) 
#endif
            override
            { return     _M_cmp(static_cast<_Node_pointer>(__x)->_M_value(), static_cast<_Node_pointer>(__y)->_M_value()); }


            list_compare(_CompPredicate __comp = _CompPredicate())
                : _M_cmp(__comp)
            {}

        protected:
            _CompPredicate      _M_cmp;
        };


        template <typename _CompPredicate = ustl::less_t<_Tp>>
        using   compare_t = list_compare<_CompPredicate>;



        struct list_impl
            : _Node_allocator_type
        {
            void
            _M_reset() ustl_cpp_noexcept
            { _M_header._M_reset(); }


            void
            _M_move(list_impl &__other) ustl_cpp_noexcept
            { _M_header._M_move(__other._M_header); }


            void
            _M_swap(list_impl &__other) ustl_cpp_noexcept
            { _M_header._M_swap(__other._M_header); }


            list_impl &
            operator=(list_impl const &__lval) ustl_cpp_noexcept
            { _M_header._M_copy(__lval._M_header); }


            list_impl &
            operator=(list_impl &&__rval) ustl_cpp_noexcept
            { _M_header._M_move(__rval._M_header); }
        

        public:
            list_impl()
                : _M_header(), _M_compare()
            {}

            template <typename _CompPredicate>
            list_impl(_CompPredicate __cmp)
                : _M_header(), _M_compare(__cmp)
            {}


        public:
            list_header         _M_header;
            compare_t<>           _M_compare;

        };


        typedef     list_impl               impl_type;
        typedef     typename ustl::allocate_traits<_Alloc>::template rebind_t<impl_type>
                    _Impl_allocator_type;
        typedef     ustl::allocate_traits<_Impl_allocator_type>
                    _Impl_allocate_traits;
        typedef     compare_t<>             compare_type;


    protected:
        template <typename ..._Args>
        _Node_pointer
        _M_get_node(_Args &&...__init_args);

        void
        _M_put_node(_Node_pointer   __p, size_type __n = 1) ustl_cpp_noexcept;
        
    
    protected:
        _Node_allocator_type &
        _M_get_allocator() ustl_cpp_noexcept
        { return    *_M_data_plus; }


        _Node_pointer 
        _M_allocate_node(size_type  __n = 1)
        { return     _Node_allocate_traits::allocate(_M_get_allocator(), __n); }
        

        template <typename ..._Args>
        void
        _M_construct(_Node_pointer  __p, _Args &&...__init_args)
        { _Node_allocate_traits::construct(_M_get_allocator(), __p->_M_valptr(), ustl::forward<_Args &&>(__init_args)...); }


        void
        _M_destory(_Node_pointer    __p) ustl_cpp_noexcept
        { _Node_allocate_traits::destory(_M_get_allocator(), __p->_M_valptr()); }


        _Node_pointer
        _M_first_node() ustl_cpp_noexcept
        { return    static_cast<_Node_pointer>(_M_data_plus->_M_header._M_next); }


        _Node_base_pointer
        _M_last_node() ustl_cpp_noexcept
        { return    static_cast<_Node_base_pointer>(&_M_data_plus->_M_header); }


        _Header_pointer
        _M_header() ustl_cpp_noexcept
        { return    &_M_data_plus->_M_header; }


    protected:
        template <typename _ImplAlloc, typename _ATraits = allocate_traits<_ImplAlloc>>
        list_basic(_ImplAlloc const &__impl_alloctor = _ImplAlloc())
            : _M_data_plus(_ATraits::allocate(__impl_alloctor, 1))
        { _ATraits::construct(__impl_alloctor, _M_data_plus); }

        list_basic(list_basic const &__lother)
            : list_basic()
        {}

        list_basic(list_basic &&__rother)
            : _M_data_plus(__rother._M_data_plus)
        { __rother._M_data_plus = 0; }

        ~list_basic()
        { 
            _Impl_allocator_type    __tmp;
            _Impl_allocate_traits::destory(__tmp, _M_data_plus);
            _Impl_allocate_traits::deallocate(__tmp, _M_data_plus, sizeof(impl_type));
        }


    protected:  
        impl_type               *_M_data_plus;
    };


    template <typename _Tp, typename _Alloc>
    template <typename ..._Args>
    inline auto 
    list_basic<_Tp, _Alloc>::
        _M_get_node(_Args &&...__init_args) -> _Node_pointer
    {
        _Node_pointer   __new = _M_allocate_node();
        __ustl_try {
            _M_construct(__new, ustl::forward<_Args &&>(__init_args)...);
        }
        __ustl_catch_all {
            _M_put_node(__new);
            __ustl_throw_again
        }
        return  __new;
    }

    
    template <typename _Tp, typename _Alloc>
    inline void
    list_basic<_Tp, _Alloc>::
        _M_put_node(_Node_pointer   __p, size_type  __n) ustl_cpp_noexcept
    {
        for(size_type __idx = 0; __idx < __n; ++__idx)
            _M_destory(__p + __idx);     
        _Node_allocate_traits::deallocate(_M_get_allocator(), __p, __n); 
    }




    template <typename _Tp, typename _Alloc = ustl::allocator<_Tp>>
    class list
        : list_basic<_Tp, _Alloc>
    {
        typedef     list_basic<_Tp, _Alloc>         _Base_type;

    public:
        typedef     _Tp                     value_type;
        typedef     _Tp *                   pointer;
        typedef     _Tp &                   reference;
        typedef     _Tp const *             const_pointer;
        typedef     _Tp const &             const_reference;

        typedef     typename _Base_type::impl_type                   impl_type;
        typedef     typename _Base_type::size_type                   size_type;
        typedef     typename _Base_type::difference_type             difference_type;
        typedef     typename _Base_type::allocator_type              allocator_type;
        typedef     typename _Base_type::iterator                    iterator;
        typedef     typename _Base_type::const_iterator              const_iterator;
        typedef     typename _Base_type::reverse_iterator            reverse_iterator;
        typedef     typename _Base_type::const_reverse_iterator      const_reverse_iterator;

    protected:
        typedef     typename _Base_type::_Node_pointer               _Node_pointer;
        typedef     typename _Base_type::_CNode_pointer              _CNode_pointer;
        typedef     typename _Base_type::_Node_base_pointer          _Node_base_pointer;
        typedef     typename _Base_type::_CNode_base_pointer         _CNode_base_pointer;
        typedef     typename _Base_type::_Node_allocator_type        _Node_allocator_type;
        typedef     typename _Base_type::_Tp_allocate_traits         _Tp_allocate_traits;
        typedef     typename _Base_type::_Node_allocate_traits       _Node_allocate_traits;
        typedef     typename _Base_type::_Impl_allocator_type        _Impl_allocator_type;


    private:
        using       _Base_type::_M_get_node;
        using       _Base_type::_M_put_node;
        using       _Base_type::_M_get_allocator;
        using       _Base_type::_M_allocate_node;
        using       _Base_type::_M_construct;
        using       _Base_type::_M_destory;
        using       _Base_type::_M_first_node;
        using       _Base_type::_M_last_node;
        using       _Base_type::_M_header;

        template <typename _CompPredicate>
        using       compare_t = typename _Base_type::compare_t<_CompPredicate>;

    // Interface Isolation
    private:
        void
        _M_inc_size(size_type   __n) ustl_cpp_noexcept
        { _M_data_plus->_M_header._M_inc_size(__n); }


        void
        _M_dec_size(size_type   __n) ustl_cpp_noexcept
        { _M_data_plus->_M_header._M_dec_size(__n); }


        difference_type
        _M_distance(iterator __first, iterator __last) ustl_cpp_noexcept
        { return    ustl::distance(__first, __last); }


        void
        _M_transer(iterator __pos, iterator __first, iterator __last) ustl_cpp_noexcept
        { _list_splice(__pos._M_data(), __first._M_data(), __last._M_data()); }


    private:
        iterator
        _M_insert_node(_Node_base_pointer __pos, _Node_base_pointer __new);

        template <typename ..._Args>
        iterator
        _M_insert_aux(const_iterator __pos, _Args &&...__init_args);

        template <typename ..._Args>
        iterator
        _M_insert_aux(const_iterator __pos, size_type __n, _Args &&...__init_args);

        template <typename _ForwardIterator>
        iterator 
        _M_range_insert(const_iterator __pos, _ForwardIterator __first, _ForwardIterator __last);

        template <typename _ForwardIterator>
        void
        _M_range_fill(_ForwardIterator __first, _ForwardIterator __last);

        void
        _M_default_append(size_type __n, value_type const &__val = value_type());

        iterator
        _M_erase(iterator __pos);

        size_type
        _M_range_erase(iterator __first, iterator __last);


    public:
        void
        assign(value_type const &__lval, size_type __n)
        { _M_insert_aux(cbegin(), __n, __lval); }


        template <typename _InputIterator>
        void
        assign(_InputIterator __first, _InputIterator __last)
        { _M_range_fill(__first, __last); }


        template <typename _InputIterator>
        size_t 
        insert(const_iterator __pos, _InputIterator __first, _InputIterator __last) 
        { return    _M_range_insert(__pos, __first, __last); }


        iterator 
        insert(const_iterator __pos, value_type const &__lval)
        { return    _M_insert_aux(__pos, __lval); }


        iterator 
        insert(const_iterator __pos, value_type const & __lval, size_t __n) 
        { return    _M_insert_aux(__pos, __lval, __n); }


        template <typename... _Args>
        reference 
        emplace(const_iterator __pos, _Args &&...__init_args)
        { return    *_M_insert_aux(__pos, ustl::forward<_Args &&>(__init_args)...); }


        template <typename... _Args>
        reference 
        emplace_back(_Args &&...__init_args)
        { return    *_M_insert_aux(cend(), ustl::forward<_Args &&>(__init_args)...); }


        template <typename... _Args>
        reference 
        emplace_front(_Args &&...__init_args)
        { return    *_M_insert_aux(cbegin(), ustl::forward<_Args &&>(__init_args)...); }


        void 
        push_back(value_type const &__lval)
        { _M_insert_aux(cend(), __lval); }


        void 
        push_back(value_type &&__rval)
        { _M_insert_aux(cend(), ustl::move(__rval)); }


        void 
        push_back(iterator __itr)
        { _M_insert_aux(end(), *__itr); }


        void 
        push_front(value_type const &__lval)
        { _M_insert_aux(begin(), __lval); }


        void 
        push_front(value_type &&__rval)
        { _M_insert_aux(begin(), ustl::move(__rval)); }


        void 
        push_front(iterator __itr)
        { _M_insert_aux(begin(), *__itr); }


        void 
        pop_back()
        { _M_erase(iterator(_M_data_plus->_M_header._M_last)); }


        void 
        pop_front()
        { _M_erase(begin()); }


        iterator 
        erase(iterator __pos)
        { return    _M_erase(__pos); }


        size_type
        erase(iterator __first, iterator __last)
        { return    _M_erase(__first, __last); }


        reference 
        front() ustl_cpp_noexcept
        { return    static_cast<_Node_pointer>(_M_data_plus->_M_header._M_next)->_M_value(); }


        reference
        back() ustl_cpp_noexcept
        { return    static_cast<_Node_pointer>(_M_data_plus->_M_header._M_last)->_M_value(); }


        iterator 
        begin() ustl_cpp_noexcept
        { return    iterator(_M_first_node()); }


        iterator 
        end() ustl_cpp_noexcept
        { return    iterator(_M_last_node()); }


        const_iterator 
        begin() const ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus->_M_header._M_next); }
        

        const_iterator 
        end() const ustl_cpp_noexcept
        { return    const_iterator(_M_last_node()); }


        const_iterator 
        cbegin() ustl_cpp_noexcept
        { return    const_iterator(_M_first_node()); }


        const_iterator 
        cend() ustl_cpp_noexcept
        { return    const_iterator(_M_last_node()); }


        const_iterator 
        cbegin() const ustl_cpp_noexcept
        { return    const_iterator(_M_first_node()); }


        const_iterator 
        cend() const ustl_cpp_noexcept
        { return    const_iterator(_M_last_node()); }


        reverse_iterator
        rbegin() ustl_cpp_noexcept
        { return    reverse_iterator(end()); }


        reverse_iterator
        rend() ustl_cpp_noexcept
        { return    reverse_iterator(begin()); }


        const_reverse_iterator
        rbegin() const ustl_cpp_noexcept
        { return    const_reverse_iterator(cend()); }


        const_reverse_iterator
        rend() const ustl_cpp_noexcept
        { return    const_reverse_iterator(cbegin()); }


        const_reverse_iterator
        crbegin() ustl_cpp_noexcept
        { return    const_reverse_iterator(cend()); }


        const_reverse_iterator
        crend() ustl_cpp_noexcept
        { return    const_reverse_iterator(cbegin()); }


        const_reverse_iterator
        crbegin() const ustl_cpp_noexcept
        { return    const_reverse_iterator(cend()); }


        const_reverse_iterator
        crend() const ustl_cpp_noexcept
        { return    const_reverse_iterator(cbegin()); }


        size_t 
        size() ustl_cpp_noexcept
        { return    _M_data_plus->_M_header._M_count; }


        size_t 
        size() const ustl_cpp_noexcept
        { return    _M_data_plus->_M_header._M_count; }


        bool 
        empty() ustl_cpp_noexcept
        { return    0 == _M_data_plus->_M_header._M_count; }


        bool 
        empty() const ustl_cpp_noexcept
        { return    0 == _M_data_plus->_M_header._M_count; }


        void 
        swap(list &__l)
        { _M_data_plus->_M_swap(__l._M_data_plus); }



        void 
        sort() ustl_cpp_noexcept
        { _list_sort(&_M_data_plus->_M_header, _M_data_plus->_M_compare); }


        template <typename _Predicate>
        void
        sort(_Predicate __cmp)
        { _list_sort(&_M_data_plus->_M_header, compare_t<_Predicate>(__cmp)); }


        void
        merge(list &__lother) 
#ifdef  ustl_cpp_noexcept
        noexcept(noexcept(_list_merge(0, 0, compare_t<ustl::less_t<_Tp>>())))
#endif
        { _list_merge(_M_header(), __lother._M_header(), _M_data_plus->_M_compare); }


        void
        merge(list &&__rother) 
#ifdef  ustl_cpp_noexcept
        noexcept(noexcept(_list_merge(0, 0, compare_t<ustl::less_t<_Tp>>())))
#endif
        { _list_merge(_M_header(), __rother._M_header(), _M_data_plus->_M_compare); }


        void 
        reverse() ustl_cpp_noexcept
        { _list_reverse(&_M_data_plus->_M_header); }


        void 
        splice(iterator __pos , list &__other, iterator __pos1)
        { _list_splice(_M_header(), __pos._M_data(), __other._M_header(), __pos1._M_data()); }


        void 
        splice(iterator __pos, list &__other, iterator __first, iterator __last)
        { _list_splice(_M_header(), __pos._M_data(), __other._M_header(), __first._M_data(), __last._M_data()); }
        
        
    public:
        list &
        operator=(list const &);

        list &
        operator=(list &&);

        size_t 
        remove(value_type const &);

        template <typename _CompPredicate>
        size_t 
        remove_if(_CompPredicate);        

        template <typename _Predicate = ustl::equal_t<_Tp>>
        void 
        unique(_Predicate = equal_t<_Tp>());

        void 
        clear();

        void 
        resize(size_t);

        void 
        resize(size_t, value_type const &);

        void 
        swap(list &&__rother);


    public:
        template <typename _ImplAlloc = _Impl_allocator_type>
        list(_ImplAlloc const &__impl_allocator = _ImplAlloc())
            : _Base_type(__impl_allocator)
        {}


        list(size_type  __n, value_type const &__val)
            : list() 
        { _M_default_append(__n, __val); }


        template <typename _InputItr, typename = ustl::RequireInputItr<_InputItr>>
        list(_InputItr __first, _InputItr __last)
            : list() 
        {  _M_range_fill(__first, __last); }


        list(list const &__other)
            : _Base_type(__other) 
        {
            if (&__other != this)
                _M_range_fill(__other.begin(), __other.end());
        }


        list(list &&__other)
            : _Base_type(ustl::move(__other)) 
        {}


        ~list() ustl_cpp_noexcept
        { clear(); }


    private:
        using       _Base_type::_M_data_plus;
    };



    template <typename _Tp, typename _Alloc>
    inline auto
    list<_Tp, _Alloc>::
        _M_insert_node(_Node_base_pointer  __pos, _Node_base_pointer __new) -> iterator
    {
        __pos->_M_hook_before(__new);
        _M_inc_size(1);
        return  iterator(__new);
    }


    template <typename _Tp, typename _Alloc>
    template <typename ..._Args>
    inline auto
    list<_Tp, _Alloc>::
        _M_insert_aux(const_iterator __pos, _Args &&...__init_args) -> iterator
    {       
        _Node_pointer __npos = __pos._M_data();
        _Node_pointer __new = _M_get_node(ustl::forward<_Args &&>(__init_args)...);

        __new->_M_debug_data = int(__init_args...);

        return  _M_insert_node(__npos, __new);
    }



    template <typename _Tp, typename _Alloc>
    template <typename ..._Args>
    auto
    list<_Tp, _Alloc>::
        _M_insert_aux(const_iterator __pos, size_type __n, _Args &&...__init_args) -> iterator
    {
        if(0 == __n)
            return end();
        // 防止 构造参数 是个右值
        value_type __val = value_type(ustl::forward<_Args &&>(__init_args)...);
        _Node_pointer __npos  = __pos._M_data();
        _Node_pointer __news = _M_allocate_node(__n);
        _Node_pointer __now = __news;
        _Node_pointer __new_end = __news + __n;
        list_header   __list;
        __list._M_reset();
        __list._M_hook_before(__news);

        __ustl_try
        {
            while(__now != __new_end)
            {
                _M_construct(__now, __val); 
                if(__now != __new_end - 1)
                    __now->_M_hook_after(__now + 1);
                ++__now;
            }
        }
        __ustl_catch_all
        {
            _M_put_node(__news, __n);
            __ustl_throw_again
        }
        _list_splice(__npos, __news, &__list);
        _M_inc_size(__n);
        return      iterator(__news);
    }



    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    auto
    list<_Tp, _Alloc>::
        _M_range_insert(const_iterator  __pos, _ForwardIterator __first, _ForwardIterator __last) -> iterator 
    {
        if(__last == __first)
            return 0;
        
        difference_type __len = _M_distance(__first, __last);
        _Node_pointer __npos  = __pos._M_data();
        _Node_pointer __news = _M_allocate_node(__len);
        _Node_pointer __now = __news;
        _Node_pointer __new_end = __news + __len;
        list_header   __list;
        __list._M_reset();
        __list._M_hook_before(__news);

        __ustl_try
        {
            while(__first != __last && __now != __new_end)
            {
                _M_construct(__now, *__first); 
                if(__now != __new_end - 1)
                    __now->_M_hook_after(__now + 1);
                ++__now;
                ++__first; 
            }
        }
        __ustl_catch_all
        {
           _M_put_node(__news, __len);
           __ustl_throw_again
        }

        _list_splice(__npos, __news, &__list);
        _M_inc_size(__len);
        return      iterator(__news);
    }



    template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
    void
    list<_Tp, _Alloc>::
        _M_range_fill(_ForwardIterator __first, _ForwardIterator __last)
    {
        if(__first == __last)
            return;
        _Node_pointer        __start  = _M_first_node();
        _Node_base_pointer   __finish = _M_last_node();
        __ustl_try
        {
            for(; __start != __finish && __first != __last;
                  ++__start, (void)++__first)
            {
                _M_construct(__start, *__first);
            }
            if(__start != __finish)
               _M_erase(iterator(__start), iterator(__finish));
            else if(__first != __last)
                _M_range_insert(end(), __first, __last);
        }
        __ustl_catch_all
        { __ustl_throw_again; }
    }



    template <typename _Tp, typename _Alloc>
    void
    list<_Tp, _Alloc>::
        _M_default_append(size_type __n, value_type const &__val)
    {
        _Node_pointer __news   =  _M_allocate_node(__n);
        _Node_pointer __start  = __news;
        _Node_pointer __finish = __start + __n;
        __ustl_try {
            for(; __start != __finish; ++__start)
                _M_construct(__start, __val);
        }
        __ustl_catch_all {
            _M_put_node(__news, __n);
            __ustl_throw_again
        }
        for(__start = __news; __start != __finish; ++__start)
            _M_insert_node(&_M_data_plus->_M_header, __start);
    }




    template <typename _Tp, typename _Alloc>
    auto 
    list<_Tp, _Alloc>::
        _M_erase(iterator __pos) -> iterator
    {
        _Node_base_pointer   __npos = __pos._M_data();
        _Node_base_pointer   __next = __npos->_M_next;
        __npos->_M_unhook();
        _M_dec_size(1);
        _M_put_node(static_cast<_Node_pointer>(__npos));
        return  iterator(__next);
    }



    template <typename _Tp, typename _Alloc>
    auto 
    list<_Tp, _Alloc>::
        _M_range_erase(iterator __first, iterator __last) -> size_type
    {
        size_type   __len = 0;
        size_type   __old_size = size();
        _Node_base_pointer   __nstart  = __first._M_data();
        _Node_base_pointer   __nfinish = __last._M_data();
        _Node_base_pointer   __tmp;
        for(; __nstart != __nfinish; ++__len)
        {
            __tmp = __nstart;
            __nstart = __nstart->_M_next;
            __tmp->_M_unhook();
            _M_put_node(__tmp);
        }
        _M_dec_size(__len);
        return  size();
    }



    template <typename _Tp, typename _Alloc>
    size_t
    list<_Tp, _Alloc>::
        remove(value_type const &__val)
    {
        iterator __tmp;
        iterator __begin = begin();
        iterator __end = end();
        while (__begin != __end)
        {
            __tmp = __begin;
            ++__begin;
            if (*__tmp == __val)
                _M_erase(__tmp);
        }
        return size();
    }



    template <typename _Tp, typename _Alloc>
    template <typename _CompPredicate>
    size_t
    list<_Tp, _Alloc>::
        remove_if(_CompPredicate __pred)
    {
        size_t __oldsize = size();
        iterator __tmp;
        iterator __begin = begin();
        iterator __end = end();
        while (__begin != __end)
        {
            __tmp = __begin;
            ++__begin;
            if (__pred(*__tmp))
                _M_erase(__tmp);
        }
        return __oldsize - size();
    }



    template <typename _Tp, typename _Alloc>
    template <typename _Predicate>
    void list<_Tp, _Alloc>::
        unique(_Predicate __pred)
    {
        iterator __begin = begin();
        iterator __end = end();
        iterator __next = __begin;
        while (++__next != __end)
        {
            if (__pred(*__begin, *__next))
                _M_erase(__next);
            else
                __begin = __next;
            __next = __begin;
        }
    }



    template <typename _Tp, typename _Alloc>
    inline void
    list<_Tp, _Alloc>::
        resize(size_t __s)
    {
        if (__s > size())
            _M_default_append(__s - size());
    }



    template <typename _Tp, typename _Alloc>
    inline void
    list<_Tp, _Alloc>::
        resize(size_t __s, value_type const &__val)
    {
        if (__s > size())
            _M_default_append(__s - size(), __val); 
    }



    template <typename _Tp, typename _Alloc>
    inline void
    list<_Tp, _Alloc>::
        clear()
    {
        if(0 == size())
            return;
        iterator __first = begin();
        iterator __last = end();
        while (__first != __last)
            __first = _M_erase(iterator(__first));
        _M_data_plus->_M_reset();
    }


    template <typename _Tp, typename _Alloc>
    inline void
    list<_Tp, _Alloc>::
        swap(list &&__rother)
    {
        if(&__rother == this)
            return;
        clear();
        _M_data_plus->_M_move(__rother._M_data_plus);
    }



    template <typename _Tp, typename _Alloc>
    inline list<_Tp, _Alloc> &
    list<_Tp, _Alloc>::
    operator=(list &&__other)
    {
        if (&__other != this)
        {
            clear();
            swap(__other);
        }
        return *this;
    }


    template <typename _Tp, typename _Alloc>
    inline list<_Tp, _Alloc> &
    list<_Tp, _Alloc>::
    operator=(list const &__other)
    {
        if (&__other != this)
            _M_range_fill(__other.begin(), __other.end());
        return *this;
    }


    template <typename _Tp, typename _Alloc>
    bool
    operator==(list<_Tp, _Alloc> const &__l,
               list<_Tp, _Alloc> const &__r)
    {
        typedef typename list<_Tp, _Alloc>::const_iterator const_iterator;
        const_iterator __first  = __l.begin();
        const_iterator __last   = __l.end();
        const_iterator __first1 = __r.begin();
        const_iterator __last1  = __r.end();
        while (__first1 != __last1 && __first != __last &&
               *__first1 == *__first)
            ++__first1, ++__first;

        return __first1 == __last1 && __first == __last;
    }


    template <typename _Tp, typename _Alloc>
    static inline bool
    operator!=(list<_Tp, _Alloc> const &__l,
               list<_Tp, _Alloc> const &__r)
    { return !(__l == __r); }
}

#endif