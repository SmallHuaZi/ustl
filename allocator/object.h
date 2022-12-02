#ifndef __object_h
#define __object_h

#include "move.h"
#include "type/allocate_traits.h"

namespace ustl
{

    /**
     *  use reference to tell the customer
     * how many objects are initialized
     */
    template <typename _Tp, typename... _Args>
    void
    constructor(_Tp *__ptr, size_t &__n,
                _Args &&...__a)
    {
        for (; __n; ++__ptr, (void)--__n)
            new (__ptr) _Tp(ustl::forward<_Args &&>(__a)...);
    }

    template <typename _Tp, typename... _Args>
    void
    constructor(_Tp *__ptr, size_t __n,
                _Args &&...__a)
    {
        for (; __n; ++__ptr, (void)--__n)
            new (__ptr) _Tp(ustl::forward<_Args &&>(__a)...);
    }

    template<typename _Iterator, typename _Alloc, typename ..._Args>
    void
    constructor(_Iterator __first, _Iterator __last, 
                _Alloc & __alloc, _Args && ... __init_args)
    {
        typedef     ustl::allocate_traits<_Alloc>     __traits;
        for(; __first != __last; ++__first) {
            __traits::construct(__alloc, &*__first, ustl::forward<_Args&&>(__init_args)...);
        }
    }

    template<typename _Iterator, typename _Alloc>
    void
    destructor(_Iterator __first, _Iterator __last, _Alloc & __alloc)
    {
        typedef     ustl::allocate_traits<_Alloc>     __traits;
        for(;__first != __last; ++__first) {
            __traits::destory(__alloc, &*__first);
        }
        
    }

    template <typename _Tp>
    void
    destructor(_Tp *__ptr, size_t __n)
    {
        for (; __n; ++__ptr, (void)--__n)
            __ptr->~_Tp();
    }

}

#endif