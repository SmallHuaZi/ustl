#include "container/list_fwd.h"

namespace ustl
{


    void
    _list_splice(list_node_basic *__pos, list_node_basic *__start, 
                 list_node_basic *__finish) ustl_cpp_noexcept
    {
        list_node_basic *__start_pre  = __start->_M_last;
        list_node_basic *__finish_pre = __finish->_M_last;

        __start_pre->_M_next    = __finish;
        __finish->_M_last       = __start_pre;

       __start->_M_last         = __pos->_M_last; 
       __pos->_M_last->_M_next  = __start;

       __pos->_M_last        = __finish_pre;
       __finish_pre->_M_next = __pos;
    }



    void
    _list_merge(list_header *__x, list_header *__y, list_compare_basic const &__cmp) ustl_cpp_noexcept
    {
        if(__x == __y)
            return;
        list_node_basic *__xfirst = __x->_M_next;
        list_node_basic *__xend   = __x;
        list_node_basic *__yfirst = __y->_M_next;
        list_node_basic *__yend   = __y;

        while(__xfirst != __xend && __yfirst != __yend)
        {
            if(__cmp(__xfirst, __yfirst))
                __xfirst = __xfirst->_M_next;
            else
            {
                list_node_basic *__next = __yfirst->_M_next;
                _list_splice(__xfirst, __yfirst, __next);
                __yfirst = __next;
            }
        }
        if(__yfirst != __yend)
            _list_splice(__xfirst, __yfirst, __yend);
        __x->_M_inc_size(__y->_M_count);
        __y->_M_count = 0;
    }



    void
    _list_sort(list_header *__header, list_compare_basic const &__cmp)ustl_cpp_noexcept
    {
        if(2 > __header->_M_count)
            return;

        constexpr size_t  __len = sizeof(ustl::size_t) << 3;
        size_t  __counter;
        size_t  __fill_number = 0;
        list_header      __z;
        list_header      __y[__len];
        list_node_basic *__tmp = __header->_M_next;

        do
        {
            --__header->_M_count;
            list_node_basic *__last = __tmp;
            __tmp = __tmp->_M_next;
            __last->_M_unhook();
            __z._M_hook_before(__last);
            __z._M_count = 1;

            for(__counter = 0; 
                __counter != __fill_number && __y[__counter]._M_count;
                ++__counter)
            {
                _list_merge(&__z, &__y[__counter], __cmp);
            }
            __z._M_swap(__y[__counter]);
            if(__counter == __fill_number)
                ++__fill_number;

        } while (0 != __header->_M_count);

       for(__counter = 0; __counter != __fill_number; ++__counter) 
            _list_merge(&__z, &__y[__counter], __cmp);

        __header->_M_swap(__z);
    }


    void
    _list_reverse(list_header *__header) ustl_cpp_noexcept
    {
        if(1 >= __header->_M_count)
            return;
        list_node_basic *__first = __header->_M_next;
        list_node_basic *__last  = __header->_M_last;
        list_node_basic *__tmp;
        while (__first != __last)
        {
            __tmp = __last;
            __last = __last->_M_last;
            __tmp->_M_unhook();
            __first->_M_hook_before(__tmp);
        }
        
    }


} // namespace ustl
