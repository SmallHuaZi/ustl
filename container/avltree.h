#ifndef __USTL_AVL_TREE_H
#define __USTL_AVL_TREE_H

#include "container/avltree_fwd.h"
#include "allocator/memory.h"

namespace ustl
{

    template<typename _Val>
    struct avl_node
        : avl_node_basic
    {
        avl_node *
        left() ustl_cpp_noexcept
        { return    static_cast<avl_node *>(_M_left); }

        avl_node *
        right() ustl_cpp_noexcept
        { return    static_cast<avl_node *>(_M_right); }

        avl_node *
        parent() ustl_cpp_noexcept
        { return    static_cast<avl_node *>(_M_parent); }

        avl_node *
        left() const ustl_cpp_noexcept
        { return    static_cast<avl_node *>(_M_left); }

        avl_node *
        right() const ustl_cpp_noexcept
        { return    static_cast<avl_node *>(_M_right); }

        avl_node *
        parent() const ustl_cpp_noexcept
        { return    static_cast<avl_node *>(_M_parent); }

        _Val *
        _M_valptr() ustl_cpp_noexcept
        { return    &_M_value_field; }

        _Val &
        _M_value() ustl_cpp_noexcept
        { return    _M_value_field; }

        _Val const *
        _M_valptr() const ustl_cpp_noexcept
        { return    &_M_value_field; }

        _Val const &
        _M_value() const ustl_cpp_noexcept
        { return    _M_value_field; }

        bool
        _M_is_balance() ustl_cpp_noexcept
        { return    false; }

        bool
        _M_is_balance() const ustl_cpp_noexcept
        { return    false; }

        avl_node()
            : avl_node_basic()
        {}

        avl_node(_Val const &__val)
            : avl_node_basic(),
              _M_value_field(__val)
        {}

        _Val    _M_value_field;
    };


    template<typename _Val, bool _Const>
    struct avlt_iterator
    {
        typedef     _Val                        value_type;
        typedef     _Val *                      pointer;
        typedef     _Val &                      reference;
        typedef     _Val const *                const_pointer;
        typedef     _Val const &                const_reference;
        typedef     ustl::_bothway_iterator     iterator_tag;
        typedef     ustl::diff_t                difference_type;

        typedef     avlt_iterator               _Self;
        typedef     avlt_iterator<_Val, false>  non_cv_iterator;


    public:
        avlt_iterator() = default;

        avlt_iterator(avl_node_basic *__base_pointer)
            : _M_current(__base_pointer)
        {}

        avlt_iterator(non_cv_iterator   __non_cv)
            : _M_current(__non_cv._M_current)
        {}

        avlt_iterator(tree_iterator_basic const &__base)
            : _M_current(__base)
        {}


    public:
        avl_node_basic *
        data() ustl_cpp_noexcept
        { return    static_cast<avl_node_basic *>(_M_current._M_data); }

        non_cv_iterator
        _M_const_cast() ustl_cpp_noexcept
        { return    non_cv_iterator(_M_current); }

        _Self &
        operator++() ustl_cpp_noexcept
        { return    ++_M_current, *this; }

        _Self &
        operator--() ustl_cpp_noexcept
        { return    --_M_current, *this; }

        _Self
        operator--(int) ustl_cpp_noexcept
        { return    _M_current--; }

        _Self
        operator++(int) ustl_cpp_noexcept
        { return    _M_current++; }

        _Self
        operator-(difference_type   __step) ustl_cpp_noexcept
        { return    _M_current - __step; }

        _Self
        operator+(difference_type   __step) ustl_cpp_noexcept
        { return    _M_current + __step; }

        typename ustl::if_else<_Const, const_reference, reference>::type
        operator*() ustl_cpp_noexcept
        { return    static_cast<avl_node<_Val> *>(_M_current._M_data)->_M_value(); }

        typename ustl::if_else<_Const, const_pointer, pointer>::type
        operator->() ustl_cpp_noexcept
        { return    static_cast<avl_node<_Val> *>(_M_current._M_data)->_M_valptr(); }

    public:
        friend bool
        operator==(_Self const &__l, _Self const &__r) ustl_cpp_noexcept
        { return    __l._M_current == __r._M_current; }

        friend bool
        operator!=(_Self const &__l, _Self const &__r) ustl_cpp_noexcept
        { return    __l._M_current != __r._M_current; }

        friend difference_type
        operator-(_Self __last, _Self __first) ustl_cpp_noexcept
        { return    __last - __first; }


    public:

        tree_iterator_basic   _M_current;
    };




    template<typename _Key, typename _Val, typename _Comp, typename _ExtractKey,
            typename _Alloc>
    struct avl_tree_basic
    {
        typedef     _Key                    key_type;
        typedef     _Val                    value_type;
        typedef     _Val *                  pointer;
        typedef     _Val &                  reference;
        typedef     _Val const *            const_pointer;
        typedef     _Val const &            const_reference;

        typedef     avl_node<_Val>          node_type;
        typedef     avl_node<_Val> *        node_pointer;
        typedef     avl_node_basic *        node_base_pointer;

        typedef     ustl::size_t                                size_type;
        typedef     ustl::diff_t                                difference_type;
        typedef     avlt_iterator<_Val, false>                  iterator;
        typedef     avlt_iterator<_Val, true>                   const_iterator;
        typedef     ustl::reverse_iterator<iterator>            reverse_iterator;
        typedef     ustl::reverse_iterator<const_iterator>      const_reverse_iterator;

        typedef     _Comp       compare_type;
        typedef     _Alloc      allocator_type;
        typedef     ustl::allocate_traits<_Alloc>     allocate_traits;
        typedef     typename ustl::allocate_traits<_Alloc>::template rebind_t<avl_node<_Val>>    
                    _Node_allocator_type;
        typedef     ustl::allocate_traits<_Node_allocator_type> _Node_allocate_traits;


    protected:
        struct avltree_node_pool
            : _Node_allocator_type
        {
            using       reusing_t  =  tree_node_pool::tree_recycle;
            using       acquire_t  =  tree_node_pool::tree_extract;
        

        private:
            node_pointer
            _M_allocate(size_type __n)
            { return    _Node_allocate_traits::allocate(*this, __n); }

            void
            _M_deallocate_node(node_base_pointer __p)
            { _Node_allocate_traits::deallocate(*this, __p, sizeof(node_type)); }


        public:
            template<typename ..._Args>
            void
            _M_construct_node(node_pointer __p, _Args &&...__init_args)
            { _Node_allocate_traits::construct(*this, __p->_M_valptr(), forward<_Args &&>(__init_args)...); }

            node_pointer 
            _M_destory_node(node_pointer __p) ustl_cpp_noexcept
            { _Node_allocate_traits::destory(*this, __p->_M_valptr()); }

            void
            _M_recycle_node(node_base_pointer __node)
            { _M_Manager(_M_destory_node(static_cast<node_pointer>(__node))); }


        public:
            template <typename ..._Args>
            node_base_pointer
            _M_reusing_tree(_Args &&...__init_args);

            template <typename ..._Args>
            node_base_pointer
            _M_acquire_node(_Args &&...__init_args);


        public:
            avltree_node_pool(node_base_pointer __p)
                : _M_Manager(__p)
            {}

        
        protected:
            tree_node_pool          _M_Manager;
        };


        struct avl_tree_impl
            :  _Node_allocator_type
        {

            void
            _M_reset() ustl_cpp_noexcept;

            void
            _M_swap(avl_tree_impl &__other) ustl_cpp_noexcept;

            avl_tree_impl &
            operator=(avl_tree_impl const &__lval) ustl_cpp_noexcept;

            avl_tree_impl &
            operator=(avl_tree_impl &&__rval) ustl_cpp_noexcept;


        public:
            void
            _M_move(avl_tree_impl &__other) ustl_cpp_noexcept
            { *this = ustl::move(__other); }


        public:
            avl_tree_impl()
                : _M_node_pool(&_M_header)
            {}

            avl_tree_impl(avl_tree_impl const &__other)
                : _M_header(__other._M_header)
            {}

            avl_tree_impl(avl_tree_impl &&__other)
                : _M_header(__other._M_header)
            { __other._M_reset(); }

        
        public:
            avl_header              _M_header;
            _ExtractKey             _M_extract_key;
            compare_type            _M_compare;
            avltree_node_pool       _M_node_pool;
        };

        typedef     avl_tree_impl       impl_type;


    protected:
        template <typename ..._Args>
        node_pointer
        _M_get_node(_Args &&...__init_args)
        { return    _M_data_plus._M_node_pool._M_acquire_node(forward<_Args &&>(__init_args)...); }

        void
        _M_put_node(node_base_pointer __p)
        { _M_data_plus._M_node_pool._M_recycle_node(__p); }


    protected:
        template<typename ..._Args>
        void
        _M_construct(node_pointer __p, _Args &&...__init_args)
        { _M_data_plus._M_node_pool._M_construct(__p, forward<_Args &&>(__init_args)...); }

        void
        _M_destory(node_pointer __p)
        {  }

        node_base_pointer
        _M_header() ustl_cpp_noexcept
        { return    &_M_data_plus._M_header;}

        node_base_pointer
        _M_root() ustl_cpp_noexcept
        { return    static_cast<node_base_pointer>(_M_data_plus._M_header._M_parent); }


    protected:
        key_type &
        _M_key(value_type const &__lval) ustl_cpp_noexcept
        { return    _M_data_plus._M_extract_key(__lval); }

        key_type &
        _M_key(iterator __itr) ustl_cpp_noexcept
        { return    _M_data_plus._M_extract_key(_S_value(__itr.data())); }

        key_type &
        _M_key(node_pointer __x)
        { return    _M_data_plus._M_extract_key(_S_value(__x)); }

        bool
        _M_compare(iterator __x, iterator __y) ustl_cpp_noexcept
        { return    _M_data_plus._M_compare(_M_key(__x), _M_key(__y)); }

        bool
        _M_compare(node_base_pointer __x, node_base_pointer __y) ustl_cpp_noexcept
        { return    _M_data_plus._M_compare(_M_key(__x), _M_key(__y)); }

        bool
        _M_compare(key_type const &__x, key_type const &__y) ustl_cpp_noexcept
        { return    _Comp()(__x, __y); }

        static value_type &
        _S_value(node_base_pointer __nptr) ustl_cpp_noexcept
        { return    *static_cast<node_pointer>(__nptr)->_M_valptr(); }

        static pointer
        _S_valptr(node_base_pointer __nptr) ustl_cpp_noexcept
        { return    static_cast<node_pointer>(__nptr)->_M_valptr(); }


    protected:
        avl_tree_basic() = default;


    protected:
        impl_type           _M_data_plus;
    };



    template<typename _Key, typename _Val, typename _Comp, typename _ExtractKey ,
            typename _Alloc>
    void
    avl_tree_basic<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
    avl_tree_impl::
        _M_reset() ustl_cpp_noexcept
    {                
        _M_header._M_reset();
        _M_header._M_height = 0;
    }


    template<typename _Key, typename _Val, typename _Comp, typename _ExtractKey ,
            typename _Alloc>
    void
    avl_tree_basic<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
    avl_tree_impl:: 
        _M_swap(avl_tree_impl &__other) ustl_cpp_noexcept
    {
        avl_tree_impl   __buf(*this);
        _M_move(__other);
        __other._M_move(__buf);
    }


    template<typename _Key, typename _Val, typename _Comp, typename _ExtractKey ,
            typename _Alloc>
    auto
    avl_tree_basic<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
    avl_tree_impl:: 
        operator=(avl_tree_impl const &__lother) ustl_cpp_noexcept -> avl_tree_impl &
    {
        if(&__lother != this)
            _M_header = __lother._M_header;
        return  *this;
    }


    template<typename _Key, typename _Val, typename _Comp, typename _ExtractKey ,
            typename _Alloc>
    auto
    avl_tree_basic<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
    avl_tree_impl::     
        operator=(avl_tree_impl &&__rother) ustl_cpp_noexcept -> avl_tree_impl &
    {
        if(&__rother != this)
            _M_header = ustl::move(__rother._M_header);
        return  *this;
    }


    template<typename _Key, typename _Val, typename _Comp, typename _ExtractKey ,
            typename _Alloc>
    template <typename ..._Args>
    auto
    avl_tree_basic<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
    avltree_node_pool::
        _M_reusing_tree(_Args &&...__init_args) -> node_base_pointer
    {
        node_pointer __new = _M_Manager(reusing_t());
        if(0 == __new)
            __new = _M_acquire_node(forward<_Args &&>(__init_args)...);
        else
            _M_construct(__new, forward<_Args &&>(__init_args)...);
        return  __new;
    }

    template<typename _Key, typename _Val, typename _Comp, typename _ExtractKey ,
            typename _Alloc>
    template <typename ..._Args>
    auto
    avl_tree_basic<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
    avltree_node_pool::
        _M_acquire_node(_Args &&...__init_args) -> node_base_pointer
    {
        node_pointer __new = _M_Manager(acquire_t());
        if(0 == __new)
            __new = _M_allocate(1);
        if(0 != __new)
            _M_construct(__new, forward<_Args &&>(__init_args)...);
        return  __new;
    }




/// @class ustl::avl_tree
    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc = ustl::allocator<_Val>>
    class avl_tree
        : avl_tree_basic<_Key, _Val, _Comp, _ExtractKey, _Alloc>
    {
        typedef     avl_tree_basic<_Key, _Val, _Comp, _ExtractKey, _Alloc>    _Base_type;

    public:
        typedef     _Key                    key_type;
        typedef     _Val                    value_type;
        typedef     _Val *                  pointer;
        typedef     _Val &                  reference;
        typedef     _Val const *            const_pointer;
        typedef     _Val const &            const_reference;

        typedef     typename _Base_type::size_type              size_type;
        typedef     typename _Base_type::difference_type        difference_type;
        typedef     typename _Base_type::compare_type           compare_type;
        typedef     typename _Base_type::allocator_type         allocator_type;

        typedef     typename _Base_type::iterator                       iterator;
        typedef     typename _Base_type::const_iterator                 const_iterator;
        typedef     typename _Base_type::reverse_iterator               reverse_iterator;
        typedef     typename _Base_type::const_reverse_iterator         const_reverse_iterator;

    
    protected:
        typedef     avl_node_basic                   node_base_type;
        typedef     avl_node_basic *                 node_base_pointer;
        typedef     avl_node<_Val>                   node_type;
        typedef     avl_node<_Val> *                 node_pointer;
        typedef     typename _Base_type::impl_type   impl_type;


    private:
        using       _Base_type::_M_construct;
        using       _Base_type::_M_destory;
        using       _Base_type::_M_get_node;
        using       _Base_type::_M_put_node;
        using       _Base_type::_M_header;
        using       _Base_type::_M_root;
        using       _Base_type::_M_key;
        using       _Base_type::_M_compare;
        using       _Base_type::_S_value;
        using       _Base_type::_S_valptr;


    private:
        iterator
        _M_insert_node(node_base_pointer __new, node_base_pointer __pos);

        template<typename ..._Args>
        pair<iterator, bool> 
        _M_emplace_unique(_Args &&... __init_args);

        template<typename ..._Args>
        iterator
        _M_emplace_equal(_Args &&... __init_args);

        iterator
        _M_lower_bound(node_base_pointer __root, node_base_pointer __header, key_type const &);

        iterator        
        _M_upper_bound(node_base_pointer __root, node_base_pointer __header, key_type const &);

        void
        _M_erase(iterator);

        void
        _M_range_erase(iterator, iterator);

        iterator
        _M_get_unique_pos(key_type const &__key);

        iterator
        _M_get_equal_pos(key_type const &__key);
    

    public:
        iterator
        begin() ustl_cpp_noexcept
        { return    iterator(_M_data_plus._M_header._M_Min_node()); }

        iterator
        end() ustl_cpp_noexcept
        { return    iterator(_M_header()); }

        const_iterator
        begin() const ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_header._M_Min_node()); }

        const_iterator
        end() const ustl_cpp_noexcept
        { return    const_iterator(_M_header()); }

        const_iterator
        cbegin() ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_header._M_Min_node()); }

        const_iterator
        cend() ustl_cpp_noexcept
        { return    const_iterator(_M_header()); }

        const_iterator
        cbegin() const ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_header._M_Min_node()); }

        const_iterator
        cend() const ustl_cpp_noexcept
        { return    const_iterator(_M_header()); }

        size_type
        size() ustl_cpp_noexcept
        { return    _M_data_plus._M_header._M_size; }

        size_type
        size() const ustl_cpp_noexcept
        { return    _M_data_plus._M_header._M_size; }

        size_type
        height() ustl_cpp_noexcept
        { return    _M_data_plus._M_header._M_height; }

        size_type
        height() const ustl_cpp_noexcept
        { return    _M_data_plus._M_header._M_height; }


    public:
        template<typename _InputIterator>
        void
        assign_unique(_InputIterator __first, _InputIterator __last);

        template<typename _InputIterator>
        void
        assign_equal(_InputIterator __first, _InputIterator __last);

        pair<iterator, bool>
        insert_unique(value_type const &__val)
        { return    _M_emplace_unique(__val); }

        pair<iterator, bool>
        insert_unique(value_type &&__rval)
        { return    _M_emplace_unique(ustl::move(__rval)); }

        iterator 
        insert_equal(value_type const &__val)
        { return    _M_emplace_equal(__val); }

        iterator
        insert_equal(value_type &&__rval)
        { return    _M_emplace_equal(ustl::move(__rval)); }

        template<typename ..._Args>
        pair<iterator, bool>
        emplace_unique(_Args &&...__init_args)
        { return    _M_emplace_unique(ustl::forward<_Args &&>(__init_args)...); }

        template<typename ..._Args>
        iterator
        emplace_equal(_Args &&...__init_args)
        { return    _M_emplace_equal(ustl::forward<_Args &&>(__init_args)...); }

        iterator
        erase(iterator __pos)
        { return    _M_erase(__pos); }

        iterator
        erase(iterator __first, iterator __last)
        { return    _M_range_erase(__first, __last); }

        size_type 
        remove(key_type const &__key);

        template<typename _CompPredicate>
        size_type
        remove_if(_CompPredicate __pred);

        pair<iterator, iterator> 
        find(key_type const &__key);

        template<typename _CompPredicate>
        pair<iterator, iterator>
        find_if(_CompPredicate __pred);

        iterator
        lower_bound(key_type const &__key) ustl_cpp_noexcept
        { return    _M_lower_bound(_M_root(), _M_header(), __key); }

        iterator
        upper_bound(key_type const &__key) ustl_cpp_noexcept
        { return    _M_upper_bound(_M_root(), _M_header(), __key); }

        const_iterator
        lower_bound(key_type const &__key) const ustl_cpp_noexcept
        { return    _M_lower_bound(_M_root(), _M_header(), __key); }

        const_iterator
        upper_bound(key_type const &__key) const ustl_cpp_noexcept
        { return    _M_upper_bound(_M_root(), _M_header(), __key); }

        reference
        operator[](size_type __idx) ustl_cpp_noexcept;

        const_reference
        operator[](size_type __idx) const ustl_cpp_noexcept;
    

    protected:
        using           _Base_type::_M_data_plus; 
    };


    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc>
    auto
    avl_tree<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
        _M_insert_node(node_base_pointer __new, node_base_pointer __pos) -> iterator
    {
        bool  __left = (__pos == _M_header() || _M_compare(__new, __pos));
        _avlt_insert(__left, __new, __pos, _M_header());
        ++_M_data_plus._M_header._M_size;
        return  iterator(__new);
    }



    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc>
    template<typename ..._Args>
    auto
    avl_tree<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
        _M_emplace_equal(_Args &&...__init_args) -> iterator
    {
        node_pointer    __new;
        __ustl_try
        {
            __new = _M_get_node(forward<_Args &&>(__init_args)...);
            key_type const &__key = _S_key(__new);
            iterator        __pos = _M_get_equal_pos(__key);
            return  _M_insert_node(__new.data(), __pos.data());
        }
        __ustl_catch_all
        {
            _M_put_node(__new);
            __ustl_throw_again;
        }
    }



    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc>
    template<typename ..._Args>
    auto
    avl_tree<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
        _M_emplace_unique(_Args &&...__init_args) -> pair<iterator, bool> 
    {
        typedef     pair<iterator, bool>        _Ret_type;
        node_pointer    __new;
        __ustl_try
        {
            __new = _M_get_node(forward<_Args &&>(__init_args)...);
            key_type const &__key = _S_key(__new);
            iterator        __pos = _M_get_unique_pos(__key);
            if(__pos == _M_header() && _M_root() != 0)
            {
                _M_put_node(__new);
                return  _Ret_type(end(), false);
            }
            return  _Ret_type(_M_insert_node(__new, __pos.data()), true);
        }
        __ustl_catch_all
        {
            _M_put_node(__new);
            __ustl_throw_again;
        }
    }
    

    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc>
    auto
    avl_tree<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
        _M_lower_bound(node_base_pointer __root, node_base_pointer __header, key_type const &__key) 
         -> iterator
    {
         while(__root)
         {
            if(_M_compare(_M_key(__root), __key))
                __root = __root->right();
            else
            {
                __header = __root;
                __root   = __root->left();
            }
         }
         return iterator(__header);
    }
    

    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc>
    auto
    avl_tree<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
        _M_upper_bound(node_base_pointer __root, node_base_pointer __header, key_type const &__key) 
         -> iterator
    {
         while(__root)
         {
            if(_M_compare(__key, _M_key(__root)))
            {
                __header = __root;
                __root   = __root->left();
            }
            else
                __root = __root->right();
         }
         return iterator(__header);
    }


    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc>
    auto
    avl_tree<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
        _M_get_equal_pos(key_type const &__key) -> iterator
    {

    }



    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc>
    auto
    avl_tree<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
        _M_get_unique_pos(key_type const &__key) -> iterator
    {

    }

    
} // namespace ustl



#endif