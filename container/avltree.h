#ifndef __avl_tree_h
#define __avl_tree_h

#include "container/avltree_fwd.h"

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
        typedef     avlt_iterator   _Self;
        typedef     _Val            value_type;
        typedef     _Val *          pointer;
        typedef     _Val &          reference;
        typedef     _Val const *    const_pointer;
        typedef     _Val const &    const_reference;
        typedef     avlt_iterator<_Val, false> non_cv_iterator;

        non_cv_iterator
        _M_const_cast()
        {}

        _Self &
        operator++()
        {}

        _Self &
        operator--()
        {}

        _Self
        operator--(int)
        {}

        _Self
        operator++(int)
        {}

        typename ustl::if_else<_Const, const_reference, reference>::type
        operator*()
        {}

        typename ustl::if_else<_Const, const_pointer, pointer>::type
        operator->()
        {}

        avlt_iterator() = default;

        avlt_iterator(avl_node_basic *__base_pointer)
            : _M_data(*__base_pointer)
        {}

        avlt_iterator(non_cv_iterator   __non_cv)
            : _M_data(__non_cv._M_data)
        {}

        avl_node_basic  *_M_data;
    };

    template<typename _Val, typename _Alloc>
    struct avl_tree_basic
    {
        struct avl_tree_impl
        {

            avl_header  _M_header;
        };
        typedef     avl_node<_Val>      node_type;
        typedef     avl_node<_Val> *    node_pointer;
        typedef     avl_tree_impl       impl_type;

        

        impl_type       _M_data_plus;
    };
    
    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc = ustl::allocator<_Val>>
    class avl_tree
        : avl_tree_basic<_Val, _Alloc>
    {
        typedef     avl_tree_basic<_Val, _Alloc>    _Base_type;
        typedef     typename _Base_type::impl_type   impl_type;

    public:
        typedef     _Key            key_type;
        typedef     _Val            value_type;
        typedef     _Val *          pointer;
        typedef     _Val &          reference;
        typedef     _Val const *    const_pointer;
        typedef     _Val const &    const_reference;
        typedef     _Comp           compare_type;
        typedef     _Alloc          allocator_type;

        typedef     avlt_iterator<_Val, false>                  iterator;
        typedef     avlt_iterator<_Val, true>                   const_iterator;
        typedef     ustl::reverse_iterator<iterator>            reverse_iterator;
        typedef     ustl::reverse_iterator<const_iterator>      const_reverse_iterator;

    private:
        iterator
        _M_insert_aux(value_type const &__val);
    
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


    public:

        void
        insert_unique(value_type const &__val);

        void
        insert_equal(value_type const &__val);

    
    protected:
        using   _Base_type::_M_data_plus; 
    };

    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc>
    auto
    avl_tree<_Key, _Val, _Comp, _ExtractKey, _Alloc>::
        _M_insert_aux(value_type const &__val) -> iterator
    {

    }

    
} // namespace ustl



#endif