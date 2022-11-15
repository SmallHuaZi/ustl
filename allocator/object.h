#ifndef __object_h
#define __object_h

#include "ustl.h"
#include "move.h"

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

    template <typename _Tp>
    void
    destructor(_Tp *__ptr, size_t __n)
    {
        for (; __n; ++__ptr, (void)--__n)
            __ptr->~_Tp();
    }

}

#endif