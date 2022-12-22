#ifndef __signle_list_h
#define __signle_list_h

#include "include/config.h"

namespace ustl
{
    struct slist_node_basic
    {
        typedef     slist_node_basic        _Node_base_type;
        typedef     slist_node_basic *      _Node_base_pointer;


    public:
        void
        _M_insert_after(_Node_base_pointer __last) ustl_cpp_noexcept;

        void
        _M_unhook(_Node_base_pointer __last) ustl_cpp_noexcept;

        void
        _M_transer_after(_Node_base_pointer __before, _Node_base_pointer __last) ustl_cpp_noexcept;

        static _Node_base_pointer
        _S_find_pre(_Node_base_pointer __start, _Node_base_pointer __aim) ustl_cpp_noexcept;
    

    public:
        _Node_base_pointer          _M_next;
    };


    inline void
    slist_node_basic::
        _M_insert_after(_Node_base_pointer __last) ustl_cpp_noexcept
    {
        _M_next = __last->_M_next;
        __last->_M_next = this;
    }


    inline void
    slist_node_basic::
        _M_unhook(_Node_base_pointer __last) ustl_cpp_noexcept
    {
        __last->_M_next = _M_next;
        _M_next = 0;
    }


    inline void
    slist_node_basic::
        _M_transer_after(_Node_base_pointer __before, _Node_base_pointer __last) ustl_cpp_noexcept
    {
        _Node_base_pointer  __end_now = _M_next;
        _M_next = __before->_M_next;
        if(0 != __last)
        {
            __before->_M_next = __last->_M_next;
            __last->_M_next = __end_now;
        }
        else
            __before->_M_next = __end_now;
    }


    inline slist_node_basic *
    slist_node_basic::
        _S_find_pre(_Node_base_pointer __start, _Node_base_pointer __aim) ustl_cpp_noexcept
    {
        _Node_base_pointer __tmp = __start;
        while (__tmp && __tmp->_M_next != __aim)
            __tmp = __tmp->_M_next;
        return __tmp;
    }


    struct slist_header
        : slist_node_basic
    {
        _Node_base_pointer
        _M_first_node() ustl_cpp_noexcept
        { return    _M_next; }


        _Node_base_pointer
        _M_last_node() ustl_cpp_noexcept
        { return    _M_last; }


        void
        _M_reset() ustl_cpp_noexcept
        { _M_next = _M_last = 0; }


    public:
        _Node_base_pointer      _M_last; 
    };


    static inline size_t
    _slist_node_distance(slist_node_basic *__start, slist_node_basic *__finish) ustl_cpp_noexcept
    {
        size_t  __dis = 0;
        while(__start != __finish)
        {
            __start = __start->_M_next;
            ++__dis;
        }
        return  __dis;
    }


    struct slist_compare_basic
    {
        virtual bool
        operator()(slist_node_basic *__x, slist_node_basic *__y) const __pure_vritual;
    };


    void
    _slist_reverse(slist_header *__header) ustl_cpp_noexcept;

    void
    _slist_merge(slist_header *__x, slist_header *__y, slist_compare_basic const &__cmp) ustl_cpp_noexcept;

    void
    _slist_sort(slist_header *__header, slist_compare_basic const &__cmp) ustl_cpp_noexcept;

} // namespace ustl


#endif