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

        avl_node_basic  *_M_data;
    };
    
    template<typename _Key, typename _Val, typename _Comp,
             typename _ExtractKey, typename _Alloc>
    class avl_tree
    {
        struct avl_tree_impl
        {

            avl_header  _M_header;
        };

        typedef     avl_tree_impl   impl_type;

    public:
        typedef     avlt_iterator<_Val, false>      iterator;
        typedef     avlt_iterator<_Val, true>       const_iterator;

    public:

        void
        insert();
        
    };
    
} // namespace ustl



#endif