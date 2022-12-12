#ifndef __rbtree_h
#define __rbtree_h

#include "include/config.h"
#include "iterator/iterator.h"
#include "container/pair.h"
#include "allocator/memory.h"
#include "container/rbtree_fwd.h"
#include "iterator/tree_iterator.h"
#include "type/allocate_traits.h"

namespace ustl
{
    template <typename _Val>
    struct _Rbtree_Node
        : _Rbt_node_base
    {
        typedef         _Val            value_type;
        typedef         _Rbtree_Node<_Val> *            _Node_ptr;
        typedef         _Rbtree_Node<_Val> const *      _CNode_ptr;


    public:
        _Rbtree_Node() = default;

        _Rbtree_Node(value_type __v)
            : _M_value_field(__v),
              _Rbt_node_base()
        {}

        _Rbtree_Node(value_type __v, _Node_ptr __p)
            : _M_value_field(__v),
              _Rbt_node_base(__p)
        {}

        _Rbtree_Node(value_type __v, _Node_ptr __l, _Node_ptr __r, _Node_ptr __p)
            : _M_value_field(__v),
              _Rbt_node_base(__l, __r, __p)
        {}


    public:
        value_type *
        _M_valptr() ustl_cpp_noexcept
        { return    &this->_M_value_field; }


        value_type const *
        _M_valptr() const ustl_cpp_noexcept
        { return    &this->_M_value_field; }


        value_type &
        _M_value() ustl_cpp_noexcept
        { return    _M_value_field; }


        value_type const &
        _M_value() const ustl_cpp_noexcept
        { return    _M_value_field; }


    public:
        static void
        _S_swap(_Node_ptr __l, _Node_ptr __r) ustl_cpp_noexcept;


        static void
        _S_swap(_Rbt_node_base *__l, _Rbt_node_base *__r) ustl_cpp_noexcept;
    

    public:

        value_type _M_value_field;
    };



    template<typename _Val>
    inline void
    _Rbtree_Node<_Val>::
        _S_swap(_Node_ptr   __l, _Node_ptr  __r) ustl_cpp_noexcept
    {
        value_type  __tmp(__l->_M_value_field);
        __l->_M_value_field = __r->_M_value_field;
        __r->_M_value_field = __tmp;
    }



    template<typename _Val>
    inline void
    _Rbtree_Node<_Val>::
        _S_swap(_Rbt_node_base *__l, _Rbt_node_base *__r) ustl_cpp_noexcept
    {
        _Node_ptr   __lptr = static_cast<_Node_ptr>(__l);
        _Node_ptr   __rptr = static_cast<_Node_ptr>(__r);
        _S_swap(__lptr, __rptr);
    }




    template<typename _Tp, bool _Const>
    struct _rbtree_iterator
    {
        typedef     _Tp                 value_type;
        typedef     _Tp *               pointer;
        typedef     _Tp &               reference;
        typedef     _Tp const *         const_pointer;
        typedef     _Tp const &         const_reference;

        typedef     ustl::diff_t                    difference_type;
        typedef     ustl::_bothway_iterator         iterator_tag;
        typedef     _rbtree_iterator                _Self;

    protected:
        typedef     _Rbt_node_base                  _Rbt_node_base_type;
        typedef     _Rbt_node_base *                _Rbt_node_base_pointer;
        typedef     _Rbtree_Node<_Tp>               _Rbt_node_type;
        typedef     _Rbtree_Node<_Tp> *             _Rbt_node_pointer;
        typedef     _rbtree_iterator<_Tp, false>    non_cv_iterator;


    public:
        _rbtree_iterator() = default;

        _rbtree_iterator(_Rbt_node_base_pointer __p)
            : _M_current(__p)
        {}

        _rbtree_iterator(non_cv_iterator const &__non_cv)
            : _M_current(__non_cv._M_current)
        {}

        _rbtree_iterator(tree_iterator_basic const &__base)
            : _M_current(__base)
        {}


    public:
        _Rbt_node_pointer
        _M_data()
        { return    static_cast<_Rbt_node_pointer>(_M_current._M_data); }


        non_cv_iterator
        _M_const_cast()
        { return    non_cv_iterator(_M_current); }


        _Self &
        operator--() ustl_cpp_noexcept
        { return    --_M_current; }


        _Self &
        operator++() ustl_cpp_noexcept
        { return    ++_M_current; }


        _Self
        operator--(int) ustl_cpp_noexcept
        { return    _M_current--; }


        _Self
        operator++(int) ustl_cpp_noexcept
        { return    _M_current++; }


        _Self
        operator+(difference_type __step) ustl_cpp_noexcept
        { return    _M_current + __step; }


        _Self
        operator-(difference_type __step) ustl_cpp_noexcept
        { return    _M_current - __step; }


        typename ustl::if_else<_Const, const_reference, reference>::type
        operator*() ustl_cpp_noexcept
        { return    static_cast<_Rbt_node_pointer>(_M_current._M_data)->_M_value(); }


        typename ustl::if_else<_Const, const_reference, reference>::type
        operator->() ustl_cpp_noexcept
        { return    static_cast<_Rbt_node_pointer>(_M_current._M_data)->_M_valptr(); }


    public:
        friend bool
        operator==(_Self const &__l, _Self  const&__r) ustl_cpp_noexcept
        { return    __l._M_current == __r._M_current; }

        friend bool
        operator!=(_Self const &__l,_Self  const &__r) ustl_cpp_noexcept
        { return    __l._M_current != __r._M_current; }

        friend difference_type
        operator-(_Self __last, _Self __first) ustl_cpp_noexcept
        { return    __last._M_current - __first._M_current; }


    protected:
        tree_iterator_basic         _M_current;
    };


    
    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc>
    struct rb_tree_basic
    {
        typedef         _Key                key_type;
        typedef         _Val                value_type;
        typedef         _Val *              pointer;
        typedef         _Val &              reference;
        typedef         _Val const *        const_pointer;
        typedef         _Val const &        const_reference;
        typedef         _Compare            compare_type;
        typedef         _Alloc              allocator_type;
        typedef         ustl::size_t        size_type;
        typedef         ustl::diff_t        difference_type;

        typedef         _rbtree_iterator<_Val, false>       iterator;
        typedef         _rbtree_iterator<_Val, true>        const_iterator;

    public:
        typedef         _Rbtree_Node<_Val>                  _Node_type;
        typedef         _Rbtree_Node<_Val> *                _Node_ptr;
        typedef         _Rbtree_Node<_Val> const *          _CNode_ptr;
        typedef         _Rbt_node_base *                    _Node_base_ptr;
        typedef         _Rbt_node_base const *              _CNode_base_ptr; 

        typedef         ustl::allocate_traits<_Alloc>       _Tp_allocate_traits;
        typedef         typename _Tp_allocate_traits::template rebind_t<_Node_type>  _Node_allocator_type;
        typedef         ustl::allocate_traits<_Node_allocator_type>   _Node_allocate_traits;


        struct rbtree_node_pool
            : _Node_allocator_type
        {
            using       reusing_t  =   tree_node_pool::tree_recycle;
            using       acquire_t  =   tree_node_pool::tree_extract; 


        public:
            _Node_ptr
            _M_allocate_node(size_type  __n)
            { return    _Node_allocate_traits::allocate(*this, __n); }


            void
            _M_deallocate_node(_Node_base_ptr __p)
            { _Node_allocate_traits::deallocate(*this, __p, 1); }


            template<typename ..._Args>
            void
            _M_construct(_Node_ptr __p, _Args &&...__init_args)
            { _Node_allocate_traits::construct(*this, __p->_M_valptr(), ustl::forward<_Args &&>(__init_args)...); }


            void
            _M_destory_node(_Node_ptr __p) ustl_cpp_noexcept
            { _Node_allocate_traits::destory(*this, __p); }


            void
            _M_destory_value(_Node_ptr __p) ustl_cpp_noexcept
            { _Tp_allocate_traits::destory(*this, __p->_M_valptr()); }


            void
            _M_recycle_node(_Rbt_node_base *__node)
            { _M_Manager(__node); }


        public:
            template<typename ..._Args>
            _Rbt_node_base *
            _M_reusing_tree(_Args &&...__init_args);


            template<typename ..._Args>
            _Rbt_node_base *
            _M_acquire_node(_Args &&...__init_args);


        protected:
            tree_node_pool      _M_Manager;
        };



        struct rbt_impl
        {
            void
            _M_move(rbt_impl &__other);

            void
            _M_swap(rbt_impl &__other);


            _Rbt_header                     _M_header;
            compare_type                    _M_compare;
            rbtree_node_pool                _M_node_pool;
        };

        typedef     rbt_impl            impl_type;

    protected:

        impl_type               _M_data_plus;
    };


    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc>
    template<typename ..._Args>
    inline _Rbt_node_base *
    rb_tree_basic<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
    rbtree_node_pool::
        _M_acquire_node(_Args &&...__init_args)
    {
        _Node_ptr   __ret = _M_Manager(acquire_t());
        if(0 == __ret)
            __ret = _M_allocate_node(1);
        if(0 != __ret) 
            _M_construct(__ret, ustl::forward<_Args &&>(__init_args)...);
        return  __ret;
    }


    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc>
    template<typename ..._Args>
    inline _Rbt_node_base *
    rb_tree_basic<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
    rbtree_node_pool::
        _M_reusing_tree(_Args &&...__init_args)
    {
        _Node_ptr   __ret = _M_Manager(reusing_t());
        if(0 == __ret)
            __ret = _M_acquire_node(ustl::forward<_Args &&>(__init_args)...);
        else
            _M_construct(__ret, ustl::forward<_Args &&>(__init_args)...);
        return  __ret;
    }


    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc>
    inline void
    rb_tree_basic<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
    rbt_impl::
        _M_move(rbt_impl &__other)
    {                
        _M_compare = __other._M_compare;
        _M_header._M_color = __other._M_header._M_color;
        _M_header._M_left = __other._M_header._M_left;
        _M_header._M_right = __other._M_header._M_right;
        _M_header._M_parent = __other._M_header._M_parent;
        _M_header._M_count = __other._M_header._M_count;
        __other._M_header.parent = 0;
        __other._M_header.left = 0;
        __other._M_header.right = 0;
    }
    

    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc>
    inline void
    rb_tree_basic<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
    rbt_impl::
        _M_swap(rbt_impl &__other)
    {
        rbt_impl    __tmp = *this;
        _M_move(__other);
        __other._M_move(__tmp);
    }



    /**
     *  @tparam _Key : key type
     *  @tparam _Val : stroge key and data
     *  @tparam _KeyOfVal : get key from KVpairs
     *  @tparam _Compare : compare key
     *  @tparam _Alloc : memory alloctor
     */
    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc = ustl::allocator<_Val>>
    class rb_tree
        : rb_tree_basic<_Key, _Val, _KeyOfVal, _Compare, _Alloc>
    {
        typedef         rb_tree_basic<_Key, _Val, _KeyOfVal, _Compare, _Alloc>  _Base_type;

    public:
        typedef         _Key                key_type;
        typedef         _Val                value_type;
        typedef         _Val *              pointer;
        typedef         _Val &              reference;
        typedef         _Val const *        const_pointer;
        typedef         _Val const &        const_reference;

        typedef         typename _Base_type::iterator           iterator;
        typedef         typename _Base_type::const_iterator     const_iterator;
        typedef         typename _Base_type::compare_type       compare_type;
        typedef         typename _Base_type::allocator_type     allocator_type;
        typedef         typename _Base_type::size_type          size_type;
        typedef         typename _Base_type::difference_type    difference_type;
        typedef         typename _Base_type::impl_type          impl_type;

    protected:
        typedef         typename _Base_type::_Node_type         _Node_type;
        typedef         typename _Base_type::_Node_ptr          _Node_ptr;
        typedef         typename _Base_type::_CNode_ptr         _CNode_ptr;
        typedef         typename _Base_type::_Node_base_ptr     _Node_base_ptr;
        typedef         typename _Base_type::_CNode_base_ptr    _CNode_base_ptr;


    protected:
        _Node_ptr
        _M_root() const ustl_cpp_noexcept
        { return    static_cast<_Node_ptr>(_M_data_plus->_M_header._M_parent); }


        _Node_base_ptr
        _M_left_most() const ustl_cpp_noexcept
        { return    _M_data_plus->_M_header.left(); }


        _Node_base_ptr
        _M_right_most() const ustl_cpp_noexcept
        { return    _M_data_plus->_M_header.right(); }


        _Node_ptr
        _M_begin() const ustl_cpp_noexcept
        { return    _M_data_plus->_M_header._M_parent; }


        _Node_base_ptr
        _M_end() const ustl_cpp_noexcept
        { return    &_M_data_plus->_M_header; }


        bool
        _M_compare_key(key_type const &__l, key_type const &__r) const ustl_cpp_noexcept
        { return    _M_data_plus->_M_compare(__l, __r); }


        _Node_ptr
        _M_extract_key(iterator &__itr) ustl_cpp_noexcept
        { return    static_cast<_Node_ptr>(__itr._M_data()); }


        _CNode_ptr 
        _M_extract_key(const_iterator &__citr) ustl_cpp_noexcept
        { return    static_cast<_CNode_ptr>(__citr._M_data()); }


        static _Node_ptr
        _S_left(_Node_base_ptr __p) ustl_cpp_noexcept
        { return    static_cast<_Node_ptr>(__p->_M_left); }


        static _Node_ptr
        _S_right(_Node_base_ptr __p) ustl_cpp_noexcept
        { return    static_cast<_Node_ptr>(__p->_M_right); }


        static key_type const &
        _S_key(value_type const &__val)
        { return    _KeyOfVal(__val); }


        static key_type const &
        _S_key(_Node_ptr __p)
        { return    _KeyOfVal()((__p->_M_vlaue())); }


        static key_type const &
        _S_key(iterator &__itr)
        { return    _S_key(__itr._M_data()); }


        static key_type const &
        _S_key(const_iterator &__itr)
        { return    _S_key(__itr._M_data()); }


        static key_type const &
        _S_key(_Node_base_ptr __p)
        { return    _S_key(static_cast<_Node_ptr>(__p)); }


        template <typename... _Args>
        _Node_ptr
        _M_create_node(_Args &&...__a)
        { return    _M_data_plus._M_node_pool._M_acquire_node(ustl::forward<_Args &&>(__a)...); }


        template <typename... _Args>
        void
        _M_construct_node(_Node_ptr __p, _Args &&...__a)
        { _M_data_plus._M_node_pool._M_construct(__p, forward<_Args>(__a)...); }


        void
        _M_destory_node(_Node_base_ptr __p)
        { _M_data_plus._M_node_pool._M_destory(__p); }


        void
        _M_deallocate_node(_Node_base_ptr __p)
        { _M_data_plus._M_node_pool.recycle_node(__p); }


    public:
        rb_tree()
            : _M_data_plus()
        {}


        rb_tree(rb_tree const &__other)
            : _M_data_plus(0)
        {
            if (&__other == this)
                return;
            clear();
            assign_equal(__other.begin(), __other.end());
        }


        rb_tree(rb_tree &&__other)
        {
            if (&__other == this)
                return;
            clear();
            _M_data_plus->_M_move(__other._M_data_plus);
        }


        template <typename _Itr>
        rb_tree(_Itr __first, _Itr __last)
        {
        }



        ~rb_tree() ustl_cpp_noexcept
        { clear(); }


    private:
        iterator
        _M_insert_aux(_Node_base_ptr, value_type const &);

        iterator
        _M_insert_rval(_Node_base_ptr __pos, value_type &&);

        template<typename _ForwardIterator>
        void
        _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last);


        inline iterator
        _M_insert_equal(iterator);

        iterator
        _M_insert_equal(value_type const &);

        inline pair<iterator, bool>
        _M_insert_unique(iterator);

        pair<iterator, bool>
        _M_insert_unique(value_type const &);

        void 
        _M_erase(iterator);

        iterator
        _M_get_insert_pos_unique(key_type const &) ustl_cpp_noexcept;

        iterator
        _M_get_insert_pos_equal(key_type const &) ustl_cpp_noexcept;

        iterator
        _M_lower_bound(_Node_base_ptr, _Node_base_ptr, key_type const &) const ustl_cpp_noexcept;

        iterator
        _M_upper_bound(_Node_base_ptr, _Node_base_ptr, key_type const &) const ustl_cpp_noexcept;


    public:
        iterator 
        begin() ustl_cpp_noexcept
        { return    iterator(_M_left_most()); }


        iterator 
        end() ustl_cpp_noexcept
        { return    iterator(&_M_data_plus->_M_header); }


        const_iterator 
        begin() const ustl_cpp_noexcept
        { return    const_iterator(_M_left_most()); }


        const_iterator 
        end() const ustl_cpp_noexcept
        { return    const_iterator(&_M_data_plus->_M_header); }


        const_iterator 
        cbegin() ustl_cpp_noexcept
        { return    const_iterator(_M_left_most()); }


        const_iterator 
        cend() ustl_cpp_noexcept
        { return    const_iterator(&_M_data_plus->_M_header); }


        const_iterator 
        cbegin() const ustl_cpp_noexcept
        { return    const_iterator(_M_left_most()); }


        const_iterator 
        cend() const ustl_cpp_noexcept
        { return    const_iterator(&_M_data_plus->_M_header); }


        size_type
        count()  ustl_cpp_noexcept
        { return    _M_data_plus->_M_header._M_count; }


        size_type
        count() const ustl_cpp_noexcept
        { return    _M_data_plus->_M_header._M_count; }


        bool
        empty() ustl_cpp_noexcept
        { return    0 == _M_data_plus->_M_header._M_count; }

        bool
        empty() const ustl_cpp_noexcept
        { return    0 == _M_data_plus->_M_header._M_count; }


        _Node_ptr
        root() ustl_cpp_noexcept
        { return    static_cast<_Node_ptr>(_M_data_plus->_M_header.parent()); }


        _CNode_ptr
        root() const ustl_cpp_noexcept
        { return    static_cast<_Node_ptr>(_M_data_plus->_M_header.parent()); }


    public:
        template <typename _Itr>
        void 
        assign_equal(_Itr, _Itr);

        template <typename _Itr>
        void 
        assign_unique(_Itr, _Itr);

        template <typename... _Args>
        iterator 
        emplace_equal(_Args &&...);

        iterator 
        insert_equal(iterator);

        iterator 
        insert_equal(value_type const &);

        template <typename... _Args>
        iterator 
        emplace_unique(_Args &&...);

        pair<iterator, bool> 
        insert_unique(iterator);

        pair<iterator, bool> 
        insert_unique(value_type const &);

        iterator 
        erase(iterator);

        iterator 
        erase(iterator, iterator);

        size_t 
        erase(key_type const &);

        iterator 
        find(key_type const &) const ustl_cpp_noexcept;

        iterator 
        lower_bound(key_type const &) const ustl_cpp_noexcept;

        iterator 
        upper_bound(key_type const &) const ustl_cpp_noexcept;
        
        pair<iterator, iterator> 
        equal_range(key_type const &) const ustl_cpp_noexcept;

        void 
        clear();

        void 
        swap(rb_tree &) ustl_cpp_noexcept;

        rb_tree &
        operator=(rb_tree const &);

        rb_tree &
        operator=(rb_tree &&);


    protected:

        using       _Base_type::_M_data_plus;
    };



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        _M_insert_aux(_Node_base_ptr __pos, value_type const &__val) -> iterator
    {
        key_type const &__k = _S_key(__val);
        bool __is_left = (__pos == _M_end() || _M_compare_key(__k, _S_key(__pos)));
        _Node_ptr __new = _M_create_node(__val);
        _rbt_insert(__is_left, __new, __pos, &_M_data_plus->_M_header);
        ++_M_data_plus->_M_header._M_count;
        return iterator(__new);
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        _M_insert_rval(_Node_base_ptr __pos, value_type &&__rval) -> iterator
    {
        key_type const &__key = _S_key(__rval);
        bool __is_left = (__pos == _M_end() || _M_compare_key(__k, _S_key(__pos)));
        _Node_ptr __new = _M_create_node(ustl::move(__rval));
        _rbt_insert(__is_left, __new, __pos, &_M_data_plus->_M_header);
        ++_M_data_plus->_M_header._M_count;
        return iterator(__new);
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    template <typename _ForwardIterator>
    void
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last)
    {

    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    void
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        _M_erase(iterator __del)
    {
        _Node_base_ptr __val = _rbt_erase(__del._M_node, &_M_data_plus->_M_header);
        _Node_type::_S_swap(__val, __del._M_node);
        /// @bug if recycle, the itr of client taked is unknown
        /// if no recycle, the memory of heap unable to release
        _M_deallocate_node(__val);
        --_M_data_plus->_M_header._M_count;
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        _M_get_insert_pos_unique(_Key const &__k) ustl_cpp_noexcept -> iterator
    {
        _Node_ptr __s{_M_begin()};
        _Node_base_ptr __e{_M_end()};
        bool __comp{true};
        while (__s)
        {
            __e = __s;
            __comp = _M_compare_key(__k, _S_key(__s));
            __s = __comp ? _S_left(__s) : _S_right(__s);
        }

        _Node_ptr __pre = static_cast<_Node_ptr>(__e);
        // if go left one last time, the precursor of __e
        // must >= __k, so we should compare precursor of __e
        // and __k are equals, but wo must check __e is minimum
        // node before it, because the node of minimum don`t have
        // node of precursor
        if (__comp)
        {
            if (static_cast<_Node_ptr>(_M_left_most()) == __pre)
                return iterator(__pre);
            __pre = static_cast<_Node_ptr>(_rbt_decrement(__pre));
        }
        // estimate the key(node of precursor) whether is equal to the __k
        /// @if result of comparsion is true, return __e
        /// @else return end()
        if (_M_compare_key(_S_key(__pre), __k))
            return iterator(__e);
        return end();
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        _M_get_insert_pos_equal(_Key const &__k) ustl_cpp_noexcept -> iterator
    {
        _Node_ptr __s{_M_begin()};
        _Node_base_ptr __e{_M_end()};
        bool __comp;
        while (__s)
        {
            __e = __s;
            __comp = _M_compare_key(__k, _S_key(__s));
            __s = __comp ? _S_left(__s) : _S_right(__s);
        }
        /// don`t estimate double key is equal, event if it happens,
        /// the result of found are correct
        return iterator(__e);
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        _M_lower_bound(_Node_base_ptr __s,
                       _Node_base_ptr __e,
                       key_type const &__k) const ustl_cpp_noexcept -> iterator
    {
        while (__s)
        {
            // __k > __s, stroge the node that lower __k
            if (_M_compare_key(_S_key(__s), __k))
                __s = _S_right(__s);
            // __k <= __s
            else
                __e = __s, __s = _S_left(__s);
        }
        // return succursor or the node
        return iterator(__e);
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        _M_upper_bound(_Node_base_ptr __s,
                       _Node_base_ptr __e,
                       key_type const &__k) const ustl_cpp_noexcept -> iterator
    {
        while (__s)
        {
            // __k < __s
            if (_M_compare_key(__k, _S_key(__s)))
                __e = __s, __s = _S_left(__s);
            // __k >= __s
            else
                __s = _S_right(__s);
        }
        return iterator(__e);
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        _M_insert_equal(value_type const &__val) -> iterator
    {
        key_type const &__key = _KeyOfVal()(__val);
        iterator __pos = _M_get_insert_pos_equal(__key);
        return iterator(_M_insert(__pos._M_node, __val, __rcru));
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        _M_insert_equal(iterator __itr) -> iterator
    {
        value_type const &__val = static_cast<_Node_ptr>(__itr._M_node)->_M_value();
        key_type const &__key = _KeyOfVal()(__val);
        iterator __pos = _M_get_insert_pos_equal(__key);
        return iterator(_M_insert(__pos._M_node, __val, __rcru));
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        _M_insert_unique(value_type const &__val) -> pair<iterator, bool>
    {
        /// @if null != root && end() = pos
        ///     then : double key is equals
        /// @elseif null = root && end() = pos
        ///     then : root is null
        using ret_type = pair<iterator, bool>;
        key_type const &__key = _KeyOfVal()(__val);
        iterator __pos = _M_get_insert_pos_unique(__key);

        if (0 != _M_root() && end() == __pos)
            return ret_type(__pos, false);
        return ret_type(_M_insert(__pos._M_node, __val, __rcru), true);
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    inline auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        _M_insert_unique(iterator __itr) -> pair<iterator, bool>
    {
        value_type __val = *static_cast<_Node_ptr>(__itr._M_node)->_M_valptr();
        return _M_insert_unique(__val, __rcru);
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    template <typename... _Args>
    inline auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        emplace_equal(_Args &&...__a) -> iterator
    {
        _Node_ptr __new = _M_create_node();
        _M_construct_node(__new, forward(__a)...);
        key_type __k = _S_key(__new);
        iterator __pos = _M_get_insert_pos_equal(__k);
        bool __is_left = (__pos == _M_end() || _M_compare_key(__k, _S_key(__pos)));
        _rbt_insert(__is_left, __new, __pos._M_node, &_M_data_plus->_M_header);
        return iterator(__new);
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    inline auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        insert_equal(value_type const &__val) -> iterator 
    { return _M_insert_equal(__val, 0); }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    inline auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        insert_unique(value_type const &__itr) -> pair<iterator, bool>
    { return _M_insert_unique(__itr, 0); }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    inline auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        insert_equal(iterator __itr) -> iterator
    { return _M_insert_equal(__itr, 0); }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    inline auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        insert_unique(iterator __itr) -> pair<iterator, bool>
    { return _M_insert_unique(__itr, 0); }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    template <typename _Itr>
    inline void 
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        assign_equal(_Itr __b, _Itr __e)
    {
        _rbt_recycle_reuse __rcru(*this);
        while (__b != __e)
            _M_insert_equal(__b++, &__rcru);
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    template <typename _Itr>
    inline void
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        assign_unique(_Itr __b, _Itr __e)
    {
        _rbt_recycle_reuse __rcru(*this);
        while (__b != __e)
            _M_insert_unique(__b++, &__rcru);
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc> ::iterator
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        erase(iterator __begin, iterator __end)
    {
        if (begin() == __begin && end() == __end)
        {
            clear();
            return end();
        }
        else
        {
            while (__begin != __end)
                _M_erase(__begin++);
            iterator __ret = __end;
            ++__ret;
            return __ret;
        }
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        erase(iterator __itr)
    {
        if (end() == __itr)
            return end();
        iterator __suc = __itr;
        ++__suc;
        _M_erase(__itr);
        return __suc;
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    size_t
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        erase(key_type const &__key)
    {
        size_t __count = count();
        pair<iterator, iterator>
            __range = equal_range(__key);
        erase(__range._M_fisrt_val, __range._M_second_val);
        return __count - count();
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    inline auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        find(key_type const &__k) const ustl_cpp_noexcept -> iterator
    {
        iterator __ret = lower_bound(__k);
        // check __k = key(__ret) or __k > key(__ret)
        if (end() != __ret || !_M_compare_key(__k, _S_key(__ret)))
            return __ret;
        return end();
    }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    inline auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        lower_bound(key_type const &__k) const ustl_cpp_noexcept -> iterator
    { return _M_lower_bound(_M_root(), _M_end(), __k); }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    inline auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        upper_bound(key_type const &__k) const ustl_cpp_noexcept -> iterator
    { return _M_upper_bound(_M_root(), _M_end(), __k); }



    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    auto
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            equal_range(key_type const &__k) const ustl_cpp_noexcept -> pair<iterator, iterator>
    {
        typedef pair<iterator, iterator> ret_type;
        _Node_ptr __aim = _M_root();
        _Node_base_ptr __suc = _M_end();
        while (__aim)
        {
            // __k < key(__tmp), storage it`s succursor
            //  for which foreach using operator!=()
            if (_M_compare_key(__k, _S_key(__aim)))
                __suc = __aim, __aim = _S_left(__aim);
            // __k > key(__tmp)
            else if (_M_compare_key(_S_key(__aim), __k))
                __aim = _S_right(__aim);
            //  __k = key(__tmp)
            else
            {
                // __begin storage lower key(__tmp)
                return ret_type(_M_lower_bound(_S_left(__aim), __aim, __k),
                                _M_upper_bound(_S_right(__aim), __suc, __k));
            }
        }
        /** if haven`t the node, return it`s logical succursor */
        return ret_type(iterator(__suc), iterator(__suc));
    }

    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    inline void
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        swap(rb_tree &__other) ustl_cpp_noexcept
    {
        if (0 == _M_root())
        {
            if (0 != __other._M_root())
                _M_data_plus->_M_move(__other._M_data_plus);
        }
        else if (0 == __other._M_root())
            __other._M_data_plus->_M_move(_M_data_plus);
        else
            _M_data_plus->_M_swap(__other._M_data_plus);
    }

    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    void
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        clear()
    {
        _Node_base_ptr __parent;
        _Node_base_ptr __root = _M_left_most();
        while (__root && _M_end() != __root)
        {
            if (__root->_M_left)
                __root = _S_left(__root);
            while (__root->_M_right)
                __root = _S_right(__root);
            if (__root->_M_left)
                __root = _S_left(__root);
            __parent = __root->parent();
            _M_destory_node(__root);
            _M_deallocate_node(__root);
            __root = __parent;
        }
        _M_data_plus->_M_header._M_reset();
    }


     
    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    inline rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc> &
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
    operator=(rb_tree const &__other)
    {
        if (&__other != this)
            assign_equal(__other);
        return *this;
    }


     
    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    bool
    operator==(rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc> const &__l,
               rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc> const &__r)
    {
        typedef typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::const_iterator iterator;

        iterator __frist = __l.begin();
        iterator __last = __l.end();
        iterator __frist1 = __r.begin();
        iterator __last1 = __r.end();

        while (__frist1 != __last1 && __frist != __last &&
               *__frist1 == *__frist)
            ++__frist1, ++__frist;
        return __frist1 == __last1 && __frist == __last;

#ifdef __tree_struct_equal
        typedef _Rbt_node_base *base_ptr;
        typedef _Rbtree_Node<_Val> *node_ptr;
        base_ptr __Lroot = rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::root(__l);
        base_ptr __Rroot = rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::root(__r);
        bool __is_go_back = false;
        bool __from_lchild = false;

        while (*static_cast<node_ptr>(__Lroot)->_M_valptr() ==
                   *static_cast<node_ptr>(__Rroot)->_M_valptr() &&
               0 != __Lroot && 0 != __Rroot)
        {
            base_ptr __parent = __Lroot->_M_parent;
            base_ptr __rparent = __Rroot->_M_parent;

            if (__Lroot == __parent->_M_left && __from_lchild)
                return true;

            if (__is_go_back)
            {
                if (__from_lchild)
                {
                    __Rroot = __Rroot->_M_right;
                    __Lroot = __Lroot->_M_right;
                    __is_go_back = false;
                }
                else
                {
                    if (__Lroot == __parent->_M_left)
                        __from_lchild = true;
                    __Lroot = __parent;
                    __Rroot = __rparent;
                }
            }
            else
            {
                if (__Lroot->_M_left)
                {
                    __Lroot = __Lroot->_M_left;
                    __Rroot = __Rroot->_M_left;
                }
                else if (__Lroot->_M_right)
                {
                    __Lroot = __Lroot->_M_right;
                    __Rroot = __Rroot->_M_right;
                }
                else
                {
                    if (__parent->_M_parent == __Lroot && !__from_lchild)
                        break;
                    __from_lchild = (__Lroot == __parent->_M_left ? true : false);
                    __is_go_back = true;
                    __Lroot = __parent;
                    __Rroot = __rparent;
                }
            }
        }
        return false;
#endif
    }

    
    template <typename _Key, typename _Val, typename _KeyOfVal,
              typename _Compare, typename _Alloc> 
    inline rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc> &
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
        operator=(rb_tree &&__rval)
    {
        if(&__rval != this)
        {
            clear();
            _M_data_plus->_M_move(__rval._M_data_plus);
        }
    }
}
#endif