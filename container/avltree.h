#ifndef __avl_tree_h
#define __avl_tree_h

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




    template<typename _Val, typename _Comp, typename _ExtractKey ,
            typename _Alloc>
    struct avl_tree_basic
    {
        typedef     _Comp       compare_type;
        typedef     _Alloc      allocator_type;
        typedef     ustl::allocate_traits<_Alloc>     allocate_traits;
        typedef     typename ustl::allocate_traits<_Alloc>::template rebind_t<avl_node<_Val>>    
                    _Node_allocator_type;
        typedef     ustl::allocate_traits<_Node_allocator_type> _Node_allocate_traits;

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
                : _M_header()
            {}

            avl_tree_impl(avl_tree_impl const &__other)
                : _M_header(__other._M_header)
            {}

            avl_tree_impl(avl_tree_impl &&__other)
                : _M_header(__other._M_header)
            { __other._M_reset(); }

        
        public:
            avl_header      _M_header;
            _ExtractKey     _M_extract_key;
            compare_type    _M_compare;
        };

        typedef     avl_node<_Val>      node_type;
        typedef     avl_node<_Val> *    node_pointer;
        typedef     avl_tree_impl       impl_type;

        _Node_allocator_type &
        _M_get_allocator()
        { return    _M_data_plus; }


        node_pointer
        _M_allocate_node(size_t __n = 1)
        { return    _Node_allocate_traits::allocate(_M_data_plus, __n); }


        void
        _M_deallocate_node(node_pointer __p, size_t __n = 1)
        { _Node_allocate_traits::deallocate(_M_data_plus, __p, __n); }


        template<typename ..._Args>
        void
        _M_construct()
        {}
        
        void
        _M_destory()
        { _Node_allocate_traits::destory(); }


        avl_tree_basic() = default;

        impl_type       _M_data_plus;
    };



    template<typename _Val, typename _Comp, typename _ExtractKey ,
            typename _Alloc>
    void
    avl_tree_basic<_Val, _Comp, _ExtractKey, _Alloc>::
    avl_tree_impl::
        _M_reset() ustl_cpp_noexcept
    {                
        _M_header._M_reset();
        _M_header._M_height = 0;
    }


    template<typename _Val, typename _Comp, typename _ExtractKey ,
            typename _Alloc>
    void
    avl_tree_basic<_Val, _Comp, _ExtractKey, _Alloc>::
    avl_tree_impl:: 
        _M_swap(avl_tree_impl &__other) ustl_cpp_noexcept
    {
        avl_tree_impl   __buf(*this);
        _M_move(__other);
        __other._M_move(__buf);
    }


    template<typename _Val, typename _Comp, typename _ExtractKey ,
            typename _Alloc>
    auto
    avl_tree_basic<_Val, _Comp, _ExtractKey, _Alloc>::
    avl_tree_impl:: 
        operator=(avl_tree_impl const &__lother) ustl_cpp_noexcept -> avl_tree_impl &
    {
        if(&__lother != this)
            _M_header = __lother._M_header;
        return  *this;
    }


    template<typename _Val, typename _Comp, typename _ExtractKey ,
            typename _Alloc>
    auto
    avl_tree_basic<_Val, _Comp, _ExtractKey, _Alloc>::
    avl_tree_impl::     
        operator=(avl_tree_impl &&__rother) ustl_cpp_noexcept -> avl_tree_impl &
    {
        if(&__rother != this)
            _M_header = ustl::move(__rother._M_header);
        return  *this;
    }
    


    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc = ustl::allocator<_Val>>
    class avl_tree
        : avl_tree_basic<_Val, _Comp, _ExtractKey, _Alloc>
    {
        typedef     avl_tree_basic<_Val, _Comp, _ExtractKey, _Alloc>    _Base_type;
        typedef     typename _Base_type::impl_type   impl_type;
        typedef     avl_node_basic                   node_base_type;
        typedef     avl_node_basic *                 node_base_pointer;
        typedef     avl_node<_Val>                   node_type;
        typedef     avl_node<_Val> *                 node_pointer;

    public:
        typedef     _Key            key_type;
        typedef     _Val            value_type;
        typedef     _Val *          pointer;
        typedef     _Val &          reference;
        typedef     _Val const *    const_pointer;
        typedef     _Val const &    const_reference;
        typedef     ustl::size_t    size_type;
        typedef     ustl::diff_t    difference_type;

        typedef     typename _Base_type::compare_type            compare_type;
        typedef     typename _Base_type::allocator_type          allocator_type;

        typedef     avlt_iterator<_Val, false>                  iterator;
        typedef     avlt_iterator<_Val, true>                   const_iterator;
        typedef     ustl::reverse_iterator<iterator>            reverse_iterator;
        typedef     ustl::reverse_iterator<const_iterator>      const_reverse_iterator;

    private:
        using       _Base_type::_M_get_allocator;
        using       _Base_type::_M_allocate;
        using       _Base_type::_M_deallocate;
        using       _Base_type::_M_construct;
        using       _Base_type::_M_destory;

        static key_type &
        _S_key(value_type const &__lval)
        { return    _M_data_plus._M_extract_key(__lval); }

        static key_type &
        _S_key(iterator __itr)
        { return    _M_data_plus._M_extract_key(_M_value(__itr._M_data)); }

        static value_type &
        _S_value(node_base_pointer __nptr)
        { return    *static_cast<node_pointer>(__nptr)->_M_valptr(); }

        static pointer
        _S_valptr(node_base_pointer __nptr)
        { return    static_cast<node_pointer>(__nptr)->_M_valptr(); }


    private:
        template<typename ..._Args>
        iterator
        _M_emplace_aux(_Args &&... __init_args);

        template <typename _InputIterator>
        iterator
        _M_range_insert(_InputIterator __first, _InputIterator __last);

        void
        _M_lower_bound();

        void
        _M_upper_bound();

        void
        _M_erase(iterator);

        void
        _M_range_erase(iterator, iterator);
    

    public:
        iterator
        begin() ustl_cpp_noexcept
        { return    iterator(_M_data_plus._M_header._M_Min_node()); }

        iterator
        end() ustl_cpp_noexcept
        { return    iterator(_M_data_plus._M_header._M_Max_node()); }

        const_iterator
        begin() const ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_header._M_Min_node()); }

        const_iterator
        end() const ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_header._M_Max_node()); }

        const_iterator
        cbegin() ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_header._M_Min_node()); }

        const_iterator
        cend() ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_header._M_Max_node()); }

        const_iterator
        cbegin() const ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_header._M_Min_node()); }

        const_iterator
        cend() const ustl_cpp_noexcept
        { return    const_iterator(_M_data_plus._M_header._M_Max_node()); }

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
        insert_unique(value_type const &__val);

        iterator 
        insert_equal(value_type const &__val);

        template<typename ..._Args>
        pair<iterator, bool>
        emplace_unique(_Args &&...__init_args);

        template<typename ..._Args>
        iterator
        emplace_equal(_Args &&...__init_args);

        iterator
        erase(iterator __pos);

        iterator
        erase(iterator __first, iterator __last);

        size_type 
        remove(key_type __key);

        template<typename _CompPredicate>
        size_type
        remove_if(_CompPredicate __pred);

        pair<iterator, iterator> 
        find(key_type);

        template<typename _CompPredicate>
        pair<iterator, iterator>
        find_if(_CompPredicate __pred);

        pair<iterator, iterator>
        lower_bound(key_type __key);

        pair<iterator, iterator>
        upper_bound(key_type __key);

        reference
        operator[](size_type __idx);
    
    protected:
        using   _Base_type::_M_data_plus; 
    };


    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc>
    template<typename ..._Args>
    auto
    avl_tree<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
        _M_emplace_aux(_Args &&...__init_args) -> iterator
    {

    }
    
} // namespace ustl



#endif