#ifndef __avl_tree_fwd_h
#define __avl_tree_fwd_h

#include "include/config.h"

namespace ustl
{
    enum class _Balance_Foctor { __LEFT_BANK = -1, __RIGHT_BANK = 1, __BALANCE = 0 };
    enum class _Rotate_Mode   { __LL = 0, __LR = 1, __RR = 2, __RL = 3, __NON = 5};

    
    struct avl_node_basic
    {
        typedef avl_node_basic   node_basic_type;
        typedef avl_node_basic * node_basic_pointer;

        avl_node_basic();


        node_basic_pointer  _M_left;
        node_basic_pointer  _M_right;
        node_basic_pointer  _M_parent;

        _Balance_Foctor        _M_balance_factor;
    };

    struct avl_header
        : avl_node_basic
    {
        using   avl_node_basic::node_basic_type;
        using   avl_node_basic::node_basic_pointer;

        node_basic_pointer
        _M_Min_node();

        node_basic_pointer
        _M_Max_node();

        node_basic_pointer
        _M_root();

        avl_header();

        ustl::size_t    _M_size;
    };

    template<typename _Val>
    struct avl_node
        : avl_node_basic
    {
        static node_basic_pointer
        _S_left(avl_node *__node)
        { return    __node->_M_left; }

        static node_basic_pointer
        _S_right(avl_node *__node)
        { return    __node->_M_right; }

        _Val *
        _M_valptr()
        { return    &_M_value_field; }

        _Val &
        _M_value()
        { return    _M_value_field; }

        bool
        _M_is_balance()
        { return    _Balance_Foctor::__BALANCE == _M_balance_factor; }

        avl_node()
            : avl_node_basic()
        {}

        avl_node(_Val const &__val)
            : avl_node_basic(),
              _M_value_field(__val)
        {}

        _Val    _M_value_field;
    };

    void
    _avlt_left_rotate(avl_node_basic *__ist);

    void
    _avlt_right_rotate(avl_node_basic *__ist);

    void
    _avlt_estimate_balance(avl_node_basic *__start, avl_node_basic *__root);

    void
    _avlt_insert(avl_node_basic *__new, avl_node_basic *__pos, bool __right);

    void
    _avlt_erase(avl_node_basic *__del, avl_node_basic *__root);

    void
    _avlt_insert_balance(avl_node_basic *__pos, _Rotate_Mode);

    void
    _avlt_erase_balance(avl_node_basic *__del, avl_node_basic *__root);
        

} // namespace ustl


#endif