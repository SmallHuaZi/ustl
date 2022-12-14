#ifndef __list_forward_h
#define __list_forward_h

#include "include/config.h"

namespace ustl
{
    struct list_node_basic 
    {
        typedef     list_node_basic *          _Base_pointer;
        typedef     list_node_basic const *    _CBase_pointer;


    public:
        void
        _M_unhook() ustl_cpp_noexcept;

        void
        _M_reset() ustl_cpp_noexcept;

        void
        _M_hook_before(_Base_pointer __p) ustl_cpp_noexcept;

        void
        _M_hook_after(_Base_pointer __p) ustl_cpp_noexcept;


        list_node_basic() = default;


    public:
        _Base_pointer       _M_last;
        _Base_pointer       _M_next;
    };


    inline
    list_node_basic::list_node_basic()
        : _M_last(this), _M_next(this)
    {}

       
    inline void 
    list_node_basic::
        _M_hook_before(_Base_pointer __p) ustl_cpp_noexcept
    {
        _M_last->_M_next = __p;        
        __p->_M_last = _M_last;
        _M_last = __p;
        __p->_M_next = this;
    } 


    inline void
    list_node_basic::
        _M_hook_after(_Base_pointer __p) ustl_cpp_noexcept
    {
        __p->_M_last = this;
        __p->_M_next = _M_next;
        _M_next->_M_last = __p;
        _M_next = __p;
    }


    inline void
    list_node_basic::
        _M_unhook() ustl_cpp_noexcept
    {
        _M_last->_M_next = _M_next;        
        _M_next->_M_last = _M_last;
        _M_reset();
    }


    inline void
    list_node_basic::
        _M_reset() ustl_cpp_noexcept
    {
        _M_last = this;
        _M_next = this;
    }



    struct list_header
        : list_node_basic
    {
        void
        _M_inc_size(size_t __n) ustl_cpp_noexcept
        { _M_count += __n; }

        void
        _M_dec_size(size_t __n) ustl_cpp_noexcept
        { _M_count -= __n; }

        _Base_pointer
        _M_last_node() ustl_cpp_noexcept
        { return    _M_last; }

        _Base_pointer
        _M_first_node() ustl_cpp_noexcept
        { return    _M_next; }

        void
        _M_reset() ustl_cpp_noexcept;

        void
        _M_swap(list_header &__other) ustl_cpp_noexcept;

        void
        _M_move(list_header &__other) ustl_cpp_noexcept;

        void
        _M_copy(list_header const &__other) ustl_cpp_noexcept;


    public:
        size_t      _M_count;
    };


    inline void
    list_header::
        _M_reset() ustl_cpp_noexcept
    {
        list_node_basic::_M_reset();
        _M_count = 0;
    }


    inline void
    list_header::
        _M_copy(list_header const &__other) ustl_cpp_noexcept
    {
        _M_last  = __other._M_last;
        _M_next  = __other._M_next;
        _M_count = __other._M_count;
    }


    inline void
    list_header::
        _M_move(list_header &__other) ustl_cpp_noexcept
    {
        _M_copy(__other);
        __other._M_last  = 0;
        __other._M_next  = 0;
        __other._M_count = 0;
    }


    inline void
    list_header::
        _M_swap(list_header &__other) ustl_cpp_noexcept
    {
        list_header     __tmp(*this);
        _M_move(__other);
        __other._M_move(__tmp);
    }



    struct list_compare_basic
    {
        virtual bool
        operator()(list_node_basic *__x, list_node_basic *__y) const __pure_vritual;
    };


    void
    _list_splice(list_node_basic *__pos, list_node_basic *__start, list_node_basic *__finish) ustl_cpp_noexcept;


    void
    _list_merge(list_header *__x, list_header *__y, list_compare_basic const * const __cmp) ustl_cpp_noexcept;


    void
    _list_sort(list_header *__header, list_compare_basic const * const __cmp) ustl_cpp_noexcept;


    void
    _list_reverse(list_header *__header) ustl_cpp_noexcept;


} // namespace ustl


#endif