#ifndef __algorithm_h
#define __algorithm_h

#include "include/config.h"

namespace ustl
{
    /**
     * range : [__first, __last)
     * __restart = __last- __first
     * move [__first, __last] to [__restart, __result)
     */
    template <typename _BothIterator, typename _BothIterator2>
    _BothIterator2
    copy_back(_BothIterator __first, _BothIterator __last, _BothIterator2 __result)
    {

        static_assert(ustl::__is_base<ustl::_bothway_iterator, typename ustl::itr_traits<_BothIterator>::iterator_tag>()(),
                      "ustl::copy_back: template argument 1 -> _BothIterator is not a bothway iterator");
        static_assert(ustl::__is_base<ustl::_bothway_iterator, typename ustl::itr_traits<_BothIterator2>::iterator_tag>()(),
                      "ustl::copy_back: template argument 2 -> _BothIterator2 is not a bothway iterator");

        while (__first != __last)
            *--__result = *--__last;
        return __result;
    }

    template <typename _ForwardIterator, typename _ForwardIterator2>
    _ForwardIterator2
    copy_forward(_ForwardIterator __first, _ForwardIterator __last,_ForwardIterator2  __result)
    {
        static_assert(ustl::__is_base<ustl::_forword_iterator, typename ustl::itr_traits<_ForwardIterator>::iterator_tag>()(),
                      "ustl::copy_forward: template argument 1 -> _ForwardIterator is not a forward iterator");
        static_assert(ustl::__is_base<ustl::_forword_iterator, typename ustl::itr_traits<_ForwardIterator2>::iterator_tag>()(),
                      "ustl::copy_forward: template argument 2 -> _ForwardIterator2 is not a forward iterator");

        while (__first != __last)
            *__result++ = *__first++;
        return __result;
    }

    template <typename _BothIterator, typename _BothIterator2, typename _Alloc>
    void
    relocate_back(_BothIterator __first, _BothIterator __last,
                  _BothIterator2 __result, _Alloc &__alloc)
    {

        static_assert(ustl::__is_base<ustl::_bothway_iterator, typename ustl::itr_traits<_BothIterator>::iterator_tag>()(),
                      "ustl::relocate_back: template argument 1 -> _BothIterator is not a bothway iterator");
        static_assert(ustl::__is_base<ustl::_bothway_iterator, typename ustl::itr_traits<_BothIterator2>::iterator_tag>()(),
                      "ustl::relocate_back: template argument 2 -> _BothIterator2 is not a bothway iterator");

        typedef allocate_traits<_Alloc> __alloc_traits;
        while (__last != __first)
            __alloc_traits::construct(__alloc, &*--__result,
                                      ustl::move(*--__last));
    }

    /**
     *
     *
     */
    template <typename _ForwardIterator, typename _Alloc>
    void fill_default(_ForwardIterator __first, size_t __n, _Alloc &__alloc)
    {
        static_assert(ustl::__is_base<ustl::_forword_iterator, typename ustl::itr_traits<_ForwardIterator>::iterator_tag>()(),
                     "ustl::fill_default: template argument 1 -> _ForwardIterator is not a forward iterator");

        typedef allocate_traits<_Alloc> __alloc_traits;
        size_t const __x = __n;
        _ForwardIterator __tmp = __first;
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

    template<typename _BothIterator, typename _Val>
    void
    fill_backward(_BothIterator __first, _BothIterator __last, 
                  _Val const &__val)
    {
        while(__first != __last)
            *--__last = __val;
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


    template <typename _Tp>
    inline size_t
    distance(_Tp *__first, _Tp *__last)
    { return  __last - __first; }


    template <typename _Tp>
    void
    swap(_Tp *__l, _Tp *__r, size_t __len)
    {
        _Tp __tmp[__len];
        size_t __idx = 0;
        for (; __idx < __len; ++__idx, (void)++__l)
            __tmp[__idx] = *__l;
        for (__r += __len; __idx > 0; --__idx)
            *--__l = *--__r;
        for (; __idx < __len; ++__idx, (void)++__r)
            *__r = __tmp[__idx];
    }

    template <typename _Tp, ustl::size_t _Size>
    constexpr size_t
    arylen(_Tp (&__tmp)[_Size])
    { return _Size; }

} // namespace ustl
#endif