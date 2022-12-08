#include "allocator/memopt.h"

namespace ustl
{
    void
    memcopy(const void *__s, void *__d, size_t __len) ustl_cpp_noexcept
    {
        char *__md = (char *)__d;
        char const *__ms = (char const *)__s;
        while (__len--)
            *__md++ = *__ms++;
    }

    void
    memmove(const void *__s, void *__d, size_t __len) ustl_cpp_noexcept
    {
        char *__md = (char *)__d;
        char const *__ms = (char *)__s;
        if (__ustl_safe_checking(__ms, __md))
            while (__len--)
                *__md++ = *__ms++;
        else
            for (__ms += __len, __md += __len; __len--;)
                *--__md = *--__ms;
    }

    void
    memset(void *__d, size_t const __val, size_t __len) ustl_cpp_noexcept
    {
        size_t *__md = (size_t *)__d;
        for(; __len; --__len, (void)++__md)
            *__md = __val;

    }

    int 
    memcmp(void const *__x, void const *__y, size_t __len) ustl_cpp_noexcept
    {
        byte *__mx = (byte *)__x;
        byte *__my = (byte *)__y;
        while(__len && *__mx == *__my) 
        {
            --__len; 
            (void)++__mx, (void)++__my;
        }
        return  __len ? (*__mx > *__my ? 1 : -1) : 0;
    }

    void * 
    memchr(const void *__x, char const __f, size_t __len) ustl_cpp_noexcept
    {
        char const *__mx = (char const *)__x;
        char const * const __range_end = (char const *)__x + __len;
        while(__f != *__mx && __mx != __range_end)
            ++__mx;
        return  (void *)(__mx == __range_end ? 0 : __mx);
    }

} // namespace ustl
