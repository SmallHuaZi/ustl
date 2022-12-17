#ifndef __list_forward_h
#define __list_forward_h

#include "include/config.h"

namespace ustl
{
    struct list_node_basic;

    struct list_header;

    struct list_compare_basic;

    void
    _list_node_splice(list_node_basic *__pos, list_node_basic *__start, list_node_basic *__finish) ustl_cpp_noexcept;


    void
    _list_merge(list_header *__x, list_header *__y, list_compare_basic const &__cmp) ustl_cpp_noexcept;


    void
    _list_sort(list_header *__header, list_compare_basic const &__cmp) ustl_cpp_noexcept;


    void
    _list_reverse(list_header *__header) ustl_cpp_noexcept;



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


        list_node_basic();


    public:
        _Base_pointer       _M_last;
        _Base_pointer       _M_next;

        int                 _M_debug_data = 0;
    };


    inline
    list_node_basic::
        list_node_basic()
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
        __other._M_last->_M_next = this;
        __other._M_next->_M_last = this;       
        __other._M_reset();
    }


    inline void
    list_header::
        _M_swap(list_header &__other) ustl_cpp_noexcept
    {
        if(0 != __other._M_count && 0 != _M_count)
        {
            list_header     __tmp(*this);
            _M_move(__other);
            __other._M_move(__tmp);
        }
        else if(0 == __other._M_count && 0 != _M_count)
            __other._M_move(*this);
        else if(0 == _M_count && 0 != __other._M_count)
            _M_move(__other);
    }



    struct list_compare_basic
    {
        virtual bool
        operator()(list_node_basic *__x, list_node_basic *__y) const __pure_vritual;
    };


    static inline diff_t
    _list_node_distance(list_node_basic *__start, list_node_basic *__finish) ustl_cpp_noexcept
    {
        diff_t  __len = 0;
        while( __start != __finish)
        {
            __start = __start->_M_next;
            ++__len;
        }
        return  __len;
    }


    static inline void
    _list_splice(list_header *__header, list_node_basic *__pos, list_header *__other, list_node_basic *__pos1) ustl_cpp_noexcept
    {
        if(__pos == __other)
            return;
        _list_node_splice(__pos, __pos1, __pos1->_M_next);
        __header->_M_inc_size(1);
        __other->_M_dec_size(1);
    }


    static inline void
    _list_splice(list_header *__header, list_node_basic *__pos, list_header *__other, 
                 list_node_basic *__start, list_node_basic *__finish) ustl_cpp_noexcept
    {
        if(__start == __finish || __header == __pos)
            return;
        diff_t  __size = _list_node_distance(__start, __finish);
        _list_node_splice(__pos, __start, __finish);
        __header->_M_inc_size(__size);
        __other->_M_dec_size(__size);
    }

} // namespace ustl


#endif