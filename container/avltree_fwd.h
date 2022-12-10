#ifndef __avl_tree_fwd_h
#define __avl_tree_fwd_h

#include "include/config.h"
#include "container/tree_basic.h"

namespace ustl
{

    struct avl_node_basic;

    void
    _avlt_insert_balance(avl_node_basic *__pos, 
                         avl_node_basic *__header) ustl_cpp_noexcept;

    void
    _avlt_erase_balance(avl_node_basic *__del, 
                        avl_node_basic *__header) ustl_cpp_noexcept;

    void
    _avlt_update_factor(avl_node_basic *__node) ustl_cpp_noexcept;



    enum class _Balance_Foctor { 
        __LEFT_TAKING = -2,
        __LEFT_BANK = -1, 
        __BALANCE   =  0,
        __RIGHT_BANK = 1, 
        __RIGHT_TAKING = 2
    };
    enum class _Rotate_Mode { 
        __LL = 0, 
        __LR = 1, 
        __RR = 2, 
        __RL = 3, 
        __NON = 5
    };

    
    struct avl_node_basic
        : tree_node_basic
    {
        typedef avl_node_basic   node_basic_type;
        typedef avl_node_basic * node_basic_pointer;
        typedef avl_node_basic const * const_node_basic_pointer;

        avl_node_basic();

        node_basic_pointer
        right() ustl_cpp_noexcept;

        node_basic_pointer
        left() ustl_cpp_noexcept;

        node_basic_pointer
        parent() ustl_cpp_noexcept;

        const_node_basic_pointer
        right() const ustl_cpp_noexcept;

        const_node_basic_pointer
        left() const ustl_cpp_noexcept;

        const_node_basic_pointer
        parent() const ustl_cpp_noexcept;

        size_t
        update_height() ustl_cpp_noexcept;

        size_t
        update_height() const ustl_cpp_noexcept;


        diff_t      _M_height;
    };



    inline avl_node_basic::
        avl_node_basic()
            : tree_node_basic(0, 0, 0),
              _M_height(1) 
    {}



    inline avl_node_basic *
    avl_node_basic::
        left() ustl_cpp_noexcept
    { return    static_cast<node_basic_pointer>(_M_left); }



    inline avl_node_basic *
    avl_node_basic::    
        right() ustl_cpp_noexcept
    { return    static_cast<node_basic_pointer>(_M_right); }



    inline avl_node_basic *
    avl_node_basic::
        parent() ustl_cpp_noexcept
    { return    static_cast<node_basic_pointer>(_M_parent); }



    inline avl_node_basic const *
    avl_node_basic::
        left() const ustl_cpp_noexcept
    { return    static_cast<const_node_basic_pointer>(_M_left); }



    inline avl_node_basic const *
    avl_node_basic::
        right() const ustl_cpp_noexcept
    { return    static_cast<const_node_basic_pointer>(_M_right); }



    inline avl_node_basic const *
    avl_node_basic::
        parent() const ustl_cpp_noexcept
    { return    static_cast<const_node_basic_pointer>(_M_parent); }



    inline size_t
    avl_node_basic::
        update_height() ustl_cpp_noexcept
    {
        avl_node_basic const *__cv = this;
        __cv->update_height();
    }



    // avl tree header
    struct avl_header
        : avl_node_basic
    {
        using   avl_node_basic::node_basic_type;
        using   avl_node_basic::node_basic_pointer;

        node_basic_pointer
        _M_Min_node() ustl_cpp_noexcept;

        node_basic_pointer
        _M_Max_node() ustl_cpp_noexcept;

        node_basic_pointer
        _M_root() ustl_cpp_noexcept;

        const_node_basic_pointer
        _M_Min_node() const ustl_cpp_noexcept;

        const_node_basic_pointer
        _M_Max_node() const ustl_cpp_noexcept;

        const_node_basic_pointer
        _M_root() const ustl_cpp_noexcept;

        avl_header();

        size_t                 _M_size;
        _Balance_Foctor        _M_balance_factor;
    };



    avl_header::
        avl_header()
            : avl_node_basic(),
              _M_size(0)
    {}

    avl_node_basic *
    avl_header::
        _M_Min_node() ustl_cpp_noexcept
    { return    left(); }



    avl_node_basic *
    avl_header::
        _M_Max_node() ustl_cpp_noexcept
    { return    right(); }



    avl_node_basic *
    avl_header::
        _M_root() ustl_cpp_noexcept
    { return    parent(); }



    avl_node_basic const *
    avl_header::
        _M_Min_node() const ustl_cpp_noexcept
    { return    left(); }



    avl_node_basic const *
    avl_header::
        _M_Max_node() const ustl_cpp_noexcept
    { return    right(); }



    avl_node_basic const *
    avl_header::
        _M_root() const ustl_cpp_noexcept
    { return    parent(); }



    static inline avl_node_basic *
    _avlt_node_bro(avl_node_basic *__node) ustl_cpp_noexcept
    { return    static_cast<avl_node_basic *>(_tree_node_bro(__node)); }



    static inline void
    _avlt_rotate_left(avl_node_basic *__node, 
                      avl_node_basic *__header) ustl_cpp_noexcept
    { _tree_rotate_left(__node, __header); }



    static inline void
    _avlt_rotate_right(avl_node_basic *__node, 
                       avl_node_basic *__header) ustl_cpp_noexcept
    { _tree_rotate_right(__node, __header); }



    static inline void
    _avlt_insert(bool __right, 
                 avl_node_basic *__new, 
                 avl_node_basic *__pos, 
                 avl_node_basic *__header) ustl_cpp_noexcept
    {
        _tree_insert(__right, __new, __pos, __header);
        _avlt_insert_balance(__pos, __header);
    }



    static inline void
    _avlt_erase(avl_node_basic *__del, 
                avl_node_basic *__header) ustl_cpp_noexcept
    {
         _tree_erase(__del,__header);       
         _avlt_erase_balance(__del, __header);
    }


} // namespace ustl


#endif