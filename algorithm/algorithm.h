#ifndef __algorithm_h
#define __algorithm_h

#include "ustl.h"

namespace ustl
{
    /**
     * range : [__first, __last)
     * __restart = __last- __first
     * move [__first, __last] to [__restart, __result)
     */
    template <typename _Tp, typename _Vp>
    _Vp
    copy_back(_Tp __first, _Tp __last, _Vp __result)
    {
        while (__first != __last)
            *--__result = *--__last;
        return __result;
    }

    template <typename _Tp, typename _Vp>
    _Vp
    copy_forward(_Tp __first, _Tp __last, _Vp __result)
    {
        while (__first != __last)
            *__result++ = *__first++;
        return __result;
    }

    template <typename _Tp, typename _Vp, typename _Alloc>
    void
    relocate_back(_Tp __first, _Tp __last,
                  _Vp __result, _Alloc &__alloc)
    {
        typedef allocate_traits<_Alloc> __alloc_traits;
        while (__last != __first)
            __alloc_traits::construct(__alloc, &*--__result,
                                      ustl::move(*--__last));
    }

    /**
     *
     *
     */
    template <typename _Tp, typename _Alloc>
    void fill_default(_Tp __first, size_t __n, _Alloc &__alloc)
    {
        typedef allocate_traits<_Alloc> __alloc_traits;
        size_t const __x = __n;
        _Tp __tmp = __first;
        __ustl_try
        {
            for (; 0 != __n; --__n, ++__tmp)
                __alloc_traits::construct(__alloc, &*__tmp);
        }
        __ustl_catch_all
        {
            for (; __n <= __x; ++__n, --__tmp)
                __alloc_traits::destory(__alloc, &*__tmp);
            __ustl_throw_again;
        }
    }

    template <typename _ForwardIterator, typename _Val>
    void
    fill(_ForwardIterator __first, _ForwardIterator __last,
         _Val const &__val)
    {
        while (__first != __last)
            *__first++ = __val;
    }

    template <typename _InputIterator, typename _ForwardIterator,
              typename _Alloc>
    void
    relocate_forward(_InputIterator __first, _InputIterator __last,
                     _ForwardIterator __result, _Alloc &__alloc)
    {
        typedef allocate_traits<_Alloc> __alloc_traits;
        __ustl_try
        {
            for (; __first != __last; ++__first, ++__result)
                __alloc_traits::construct(__alloc, &*(__result),
                                          ustl::move(*__first));
        }
        __ustl_catch_all
        {
            /** initialization exception, process to the client */
            __ustl_throw_again;
        }
    }

    template <typename _ForwardIterator, typename _ForwardIterator2>
    size_t
    distance(_ForwardIterator __first, _ForwardIterator2 __last)
    {
        size_t __counter = 0;
        while (__first != __last)
            ++__first, ++__counter;
        return __counter;
    }

} // namespace ustl
#endif