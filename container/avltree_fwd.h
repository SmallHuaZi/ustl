#ifndef __USTL_AVL_TREE_FWD_H
#define __USTL_AVL_TREE_FWD_H

#include "algorithm/math.h"
#include "include/config.h"
#include "container/tree_basic.h"

namespace ustl
{

    struct avl_node_basic;

    avl_node_basic * 
    _avlt_erase(avl_node_basic *__del, avl_node_basic *__header) ustl_cpp_noexcept;

    void
    _avlt_insert_balance(bool __right,
                         avl_node_basic *__pos, 
                         avl_node_basic *__header) ustl_cpp_noexcept;

    void
    _avlt_erase_balance(avl_node_basic *__del, 
                        avl_node_basic *__header) ustl_cpp_noexcept;

    void
    _avlt_update_factor(avl_node_basic *__node) ustl_cpp_noexcept;


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

        diff_t
        height() ustl_cpp_noexcept;

        diff_t
        height() const ustl_cpp_noexcept;

        const_node_basic_pointer
        right() const ustl_cpp_noexcept;

        const_node_basic_pointer
        left() const ustl_cpp_noexcept;

        const_node_basic_pointer
        parent() const ustl_cpp_noexcept;

        void 
        update_height() ustl_cpp_noexcept;

        diff_t 
        balance_factor() ustl_cpp_noexcept;

        diff_t 
        balance_factor() const ustl_cpp_noexcept;


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


    inline diff_t
    avl_node_basic::
        height() ustl_cpp_noexcept
    { return    0 == this ? 0 : _M_height; }

    inline diff_t
    avl_node_basic::
        height() const ustl_cpp_noexcept
    { return    0 == this ? 0 : _M_height; }


    inline void 
    avl_node_basic::
        update_height() ustl_cpp_noexcept
    { _M_height = ustl::max(left()->height(), right()->height()) + 1; }



    inline diff_t 
    avl_node_basic::
        balance_factor() ustl_cpp_noexcept
    { return    left()->height() - right()->height(); }

    

    inline diff_t 
    avl_node_basic::
        balance_factor() const ustl_cpp_noexcept
    { return    left()->height()- right()->height(); }




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


        avl_header &
        operator=(avl_header const &__lval) ustl_cpp_noexcept;


        avl_header &
        operator=(avl_header &&_rval) ustl_cpp_noexcept;


        avl_header();


        size_t                 _M_size;
    };



    inline avl_header::
        avl_header()
            : avl_node_basic(),
              _M_size(0)
    {}

    inline avl_node_basic *
    avl_header::
        _M_Min_node() ustl_cpp_noexcept
    { return    left(); }



    inline avl_node_basic *
    avl_header::
        _M_Max_node() ustl_cpp_noexcept
    { return    right(); }



    inline avl_node_basic *
    avl_header::
        _M_root() ustl_cpp_noexcept
    { return    parent(); }



    inline avl_node_basic const *
    avl_header::
        _M_Min_node() const ustl_cpp_noexcept
    { return    left(); }



    inline avl_node_basic const *
    avl_header::
        _M_Max_node() const ustl_cpp_noexcept
    { return    right(); }



    inline avl_node_basic const *
    avl_header::
        _M_root() const ustl_cpp_noexcept
    { return    parent(); }



    inline avl_header &
    avl_header::
        operator=(avl_header const &__lval) ustl_cpp_noexcept
    {
        if(&__lval != this)
        {
            _M_right = __lval._M_right;
            _M_left  = __lval._M_left;
            _M_parent = __lval._M_parent;
        }
        return  *this;
    }


    inline avl_header &
    avl_header::
        operator=(avl_header &&__rval) ustl_cpp_noexcept
    {
        if(&__rval != this)
        {
            *this = __rval;
            __rval._M_reset();
        }
        return  *this;
    }





    static inline avl_node_basic *
    _avlt_node_bro(avl_node_basic *__node) ustl_cpp_noexcept
    { return    static_cast<avl_node_basic *>(_tree_node_bro(__node)); }



    static inline avl_node_basic *
    _avlt_increment(avl_node_basic *__node) ustl_cpp_noexcept
    { return    static_cast<avl_node_basic *>(_tree_increment(__node)); }



    static inline avl_node_basic *
    _avlt_decrement(avl_node_basic *__node) ustl_cpp_noexcept
    { return    static_cast<avl_node_basic *>(_tree_decrement(__node)); }



    static inline void
    _avlt_rotate_left(avl_node_basic *__node, 
                      avl_node_basic *__header) ustl_cpp_noexcept
    { 
        avl_node_basic  *__rchid = __node->right();

        _tree_rotate_left(__node, __header); 

        __node->update_height();
        __rchid->update_height();
    }



    static inline void
    _avlt_rotate_right(avl_node_basic *__node, 
                       avl_node_basic *__header) ustl_cpp_noexcept
    { 
        avl_node_basic  *__lchild = __node->left();

        _tree_rotate_right(__node, __header); 

        __node->update_height();
        __lchild->update_height();
    }



    static inline void
    _avlt_insert(bool __left, avl_node_basic *__new, 
                 avl_node_basic *__pos, avl_node_basic *__header) ustl_cpp_noexcept
    {
        _tree_insert(__left, __new, __pos, __header);
        _avlt_insert_balance(!__left, __pos, __header);
    }



} // namespace ustl


#endif