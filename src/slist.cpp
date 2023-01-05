#include "container/slist_fwd.h"

namespace ustl
{

    void
    _slist_reverse (slist_header *__header) ustl_cpp_noexcept
    {
        slist_node_basic *__first  = 0;
        slist_node_basic *__second = __header->_M_next;
        slist_node_basic *__third  = __second->_M_next;

        __header->_M_last = __second;
        while (__third)
        {
            __second->_M_next = __first;
            __first  =  __second;
            __second =  __third;
            __third  =  __third->_M_next;
        }
        __second->_M_next = __first;
        __header->_M_next = __second;
    }



    void
    _slist_merge (slist_header *__x, slist_header *__y, slist_compare_basic const &__cmp) ustl_cpp_noexcept
    {
        slist_node_basic *__first   = __x->_M_next;
        slist_node_basic *__first1  = __y->_M_next;
        slist_node_basic *__before  = __x;
        slist_node_basic *__before1 = __y;

        while (0 != __first && 0 != __first1)
        {
            if (__cmp(__first, __first))
            {
                __before = __first;
                __first  = __first->_M_next;
            }
            else
            {
                slist_node_basic *__next =  __before1;
                __first1->_M_unhook(__before1);
                __first1->_M_insert_after(__before);
                __first1 = __next->_M_next;
            }
        }
        if (0 != __first1)
        {
            __x->_M_last = __y->_M_last;
            __before->_M_transer_after(__before1, 0);
        }
        else
            __x->_M_last = __before;
        __y->_M_reset();
    }


    /// @GNU std::forward_list::sort () source code
    void
    _slist_sort (slist_header *__header, slist_compare_basic const &__cmp) ustl_cpp_noexcept
    {
        size_t      __tag;
        size_t      __xsize;
        size_t      __ysize;
        size_t      __counter;
        size_t      __merge_size = 1;

        slist_node_basic *__front = __header->_M_next;
        slist_node_basic *__tail;

        do
        {
            slist_node_basic *__x = __front;
            slist_node_basic *__y = __front;

            __tag  = 0;
            __tail = 0;
            while (__x)
            {
                ++__tag;
                __xsize = __merge_size;
                __ysize = __merge_size;

                for (size_t __i = 0; __i < __merge_size && __x; ++__i)
                    __x = __x ->_M_next;
                
                slist_node_basic *__lower;
                while (__ysize || (__xsize && __x))
                {
                    if (!__ysize)
                    {
                        __lower = __x;
                        __x = __x->_M_next;
                        --__xsize;
                    }
                    else if (!__xsize || !__x)
                    {
                        __lower = __y;
                        __y = __y->_M_next;
                        --__ysize;
                    }
                    else if (__cmp(__x, __y))
                    {
                        __lower = __x;
                        __x = __x->_M_next;
                        --__xsize;
                    }
                    else
                    {
                        __lower = __y;
                        __y = __y->_M_next;
                        --__ysize;

                    }

                    if (0 == __tail)
                        __front = __lower;
                    else
                        __tail->_M_next = __lower;
                    __tail = __lower;
                    
                }
                __y = __x;
            }
            __tail->_M_next = 0;
 
            // last merger was only one merger 
            if (1 >=__tag)
            {
                __header->_M_next = __front;
                __header->_M_last = __tail;
                return;
            }

            __merge_size <<= 1;

        } while (1);
    }

} // namespace ustl
