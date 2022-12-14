#include "container/list_fwd.h"

namespace ustl
{


    void
    _list_splice(list_node_basic *__pos, list_node_basic *__start, 
                 list_node_basic *__finish) ustl_cpp_noexcept
    {
        list_node_basic *__start_pre  = __start->_M_last;
        list_node_basic *__finish_pre = __finish->_M_last;

        __start_pre->_M_next = __finish;
        __finish->_M_last = __start_pre;

       __finish->_M_last = __pos->_M_last; 
       __pos->_M_last    = __finish;

       __pos->_M_last = __start_pre;
       __start_pre->_M_next = __pos;
    }



    void
    _list_merge(list_header *__x, list_header *__y, list_compare_basic const * const __cmp) ustl_cpp_noexcept
    {
        if(__x == __y)
            return;
        list_node_basic *__xfirst = __x->_M_next;
        list_node_basic *__xend   = __x->_M_last;
        list_node_basic *__yfirst = __y->_M_next;
        list_node_basic *__yend   = __y->_M_last;

        while(__xfirst != __xend && __yfirst != __yend)
        {
            if((*__cmp)(__xfirst, __yfirst))
                __xfirst = __xfirst->_M_next;
            else
            {
                _list_splice(__xfirst, __yfirst, __yfirst->_M_next);
                __yfirst = __yfirst->_M_next;
            }
        }
        if(__yfirst != __yend)
            _list_splice(__xfirst, __yfirst, __yend);
        __x->_M_inc_size(__y->_M_count);
    }



    void
    _list_sort(list_header *__header, list_compare_basic const * const __cmp)ustl_cpp_noexcept
    {
        if(2 > __header->_M_count)
            return;

        constexpr size_t  __len = sizeof(ustl::size_t) << 3;
        size_t  __counter = 0;
        size_t  __fill_number = 0;
        size_t  __length = __header->_M_count;
        list_header     *__x = __header;
        list_header      __y[__len];
        list_node_basic *__tmp = __header->_M_next;

        do
        {
            list_node_basic *__last = __tmp;
            __tmp = __tmp->_M_next;
            __last->_M_unhook();
            --__length;

            for(__counter != 0; 
                __counter != __fill_number && __y[__counter]._M_count;
                ++__counter)
            {
                _list_merge(__x, &__y[__counter], __cmp);
            }
            __x->_M_swap(__y[__counter]);
            if(__counter == __fill_number)
                ++__fill_number;

        } while (0 != __length);

       for(__counter = 0; __counter != __fill_number; ++__counter) 
            _list_merge(__x, &__y[__counter], __cmp);

        __header->_M_next = __x;
    }

} // namespace ustl
