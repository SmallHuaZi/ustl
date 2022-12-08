#ifndef __memory_operator_h
#define __memory_operator_h

#include "include/config.h"

#define __ustl_safe_checking(__src, __desc) \
    ((long)__src) > ((long)__desc)

namespace ustl
{
    constexpr  size_t
    align_extend(size_t __s, size_t __a) ustl_cpp_noexcept
    { return    (__s + --__a) & ~(__a); }

    constexpr  size_t
    align_compress(size_t __s, size_t __a) ustl_cpp_noexcept
    { return    __s & ~(--__a); }

    void
    memcopy(const void *__s, void *__d, size_t  __len) ustl_cpp_noexcept;

    void
    memmove(const void *__s, void *__d, size_t  __len) ustl_cpp_noexcept;

    void
    memset(void *__d, size_t const __val, size_t  __len) ustl_cpp_noexcept;

    int 
    memcmp(void const *__x, void const *__y, size_t  __len) ustl_cpp_noexcept;

    void * 
    memchr(const void *__x, char const __f, size_t __len) ustl_cpp_noexcept;

} // namespace ustl


#endif