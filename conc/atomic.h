#ifndef __USTL_ATOMIC_H
#define __USTL_ATOMIC_H

#include "include/config.h"


#ifdef  __ustl_multi_processtor

#define __USTL_MEMORY_BARRIER_LOAD \
asm inline("lfence    \n\t" : : : "memory");

#define __USTL_MEMORY_BARRIER_STORE \
asm inline("sfence    \n\t" : : : "memory");

#define __USTL_MEMORY_BARRIER_ALL \
asm inline("mfence    \n\t" : : : "memory");

#else

#define __USTL_MEMORY_BARRIER_LOAD 

#define __USTL_MEMORY_BARRIER_STORE

#define __USTL_MEMORY_BARRIER_ALL

#endif


namespace ustl
{
    typedef     long long       atomic_t;


#ifdef  __ustl_multi_processtor    

    template <typename _Tp>
    [[gnu::always_inline]]
    static inline void
    atomic_add(_Tp volatile *__dest, _Tp __inc) ustl_cpp_noexcept
    {
        asm volatile("lock xadd  %1, %0  \n\t"
                    : "+m"(*__dest) 
                    : "ir"(__inc)
                    : "memory");
    }


    template <typename _Tp>
    [[gnu::always_inline]]
    static inline void
    atomic_sub(_Tp volatile *__dest, _Tp __dec) ustl_cpp_noexcept
    {
        asm volatile("lock xadd  %1, %0  \n\t"
                    : "+m"(*__dest) 
                    : "ir"(-__dec)
                    : "memory");
    }


    template <typename _Tp>
    [[gnu::always_inline]]
    static inline void
    atomic_mul(_Tp volatile *__dest, _Tp __multiplier) ustl_cpp_noexcept
    {
        asm volatile("lock mul  %1, %0  \n\t"
                    : "+m"(*__dest) 
                    : "ir"(__multiplier)
                    : "memory");
    }


    template <typename _Tp>
    [[gnu::always_inline]]
    static inline void
    atomic_div(_Tp volatile *__dest, _Tp __divisor) ustl_cpp_noexcept
    {
        asm volatile("lock div  %1, %0  \n\t"
                    : "+m"(*__dest) 
                    : "ir"(__divisor)
                    : "memory");
    }


    template <typename _Tp>
    [[gnu::always_inline]]
    static inline void
    atomic_swap(_Tp volatile *__x, _Tp volatile &__y) ustl_cpp_noexcept
    {
        asm volatile("lock xchg %0, %1  \n\t"
                    : "+m"(*__x), "+r"(__y)
                    : "memory");
    }


    template <typename _Tp>
    [[gnu::always_inline]]
    static inline void
    atomic_assign(_Tp volatile *__x, _Tp __y) ustl_cpp_noexcept
    {
        asm volatile("mov   %1, %0  \n\t"
                    : "=m"(*__x)
                    : "ir"(__y)
                    : "memory")
    }


    template <typename _Tp>
    [[gnu::always_inline]]
    static inline _Tp 
    atomic_load(_Tp volatile *__x) ustl_cpp_noexcept
    {
        _Tp     __tmp;
        asm volatile("mov   %1, %0  \n\t"
                    : "=r"(__tmp) 
                    : "m"(*__x)
                    : "memory");
        return  __tmp;
    }

#else

    template <typename _Tp>
    [[gnu::always_inline]]
    static inline void
    atomic_add(_Tp *__dest, _Tp __inc) ustl_cpp_noexcept
    { *__dest += __inc; }


    template <typename _Tp>
    [[gnu::always_inline]]
    static inline void
    atomic_sub(_Tp *__dest, _Tp __dec) ustl_cpp_noexcept
    { *__dest -= __dec; }


    template <typename _Tp>
    [[gnu::always_inline]]
    static inline void
    atomic_mul(_Tp *__dest, _Tp __multiplier) ustl_cpp_noexcept
    { *__dest *= __multiplier; }


    template <typename _Tp>
    [[gnu::always_inline]]
    static inline void
    atomic_div(_Tp *__dest, _Tp __divisor) ustl_cpp_noexcept
    { *__dest /= __divisor; }


    template <typename _Tp>
    [[gnu::always_inline]]
    static inline void
    atomic_swap(_Tp *__x, _Tp *__y) ustl_cpp_noexcept
    {
        _Tp  __z = *__x;
        *__x = *__y;
        *__y =  __z;
    }


    template <typename _Tp>
    [[gnu::always_inline]]
    static inline void
    atomic_assign(_Tp *__x, _Tp __y) ustl_cpp_noexcept
    { *__x = __y; }


    template <typename _Tp>
    [[gnu::always_inline]]
    static inline _Tp 
    atomic_load(_Tp *__x)
    { return    *__x; }

#endif

} // namespace ustl



#endif