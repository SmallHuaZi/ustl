#ifndef __avl_tree_h
#define __avl_tree_h

#include "container/avltree_fwd.h"

namespace ustl
{
    template<typename _Val, bool _Const>
    struct avlt_iterator
    {
        typedef     avlt_iterator   _Self;
        typedef     _Val    value_type;
        typedef     _Val *  pointer;
        typedef     _Val &  reference;
        typedef     _Val const * const_pointer;
        typedef     _Val const & const_reference;

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