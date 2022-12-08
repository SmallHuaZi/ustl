#ifndef __char_traits_h
#define __char_traits_h

#include "allocator/memopt.h"

namespace ustl
{
    template <typename>
    class char_traits;

    template <>
    class char_traits<char>
    {
    public:
        typedef char value_type;
        typedef char *pointer;
        typedef char &reference;

        static bool
        equal(value_type const &__l,
              value_type const &__r)
        {
            return __l == __r;
        }

        static size_t
        length(const char *__str)
        {
            size_t __len = 0;
            for (; __str[__len]; ++__len)
                ;
            return __len;
        }

        static constexpr bool
        lt(char const __l, char const __r)
        {
            return (unsigned char)__l < (unsigned char)__r;
        }

        static int
        compare(char const *__l, char const *__r, size_t __len)
        {
            for (; __len--; (void)++__l, (void)++__r)
            {
                if (lt(*__l, *__r))
                    return -1;
                else if (lt(*__r, *__l))
                    return 1;
            }
            return 0;
        }

        static void
        assign(char const &__s, char &__d)
        {
            __d = __s;
        }

        static void
        copy(char const *__s, char *__d, size_t __len)
        {
            ustl::memmove(__s, __d, __len);
        }

        static void
        swap(char &__x, char &__y)
        {
            char __buf = __x;
            __x = __y;
            __y = __buf;
        }
    };

    template <>
    struct char_traits<wchar_t>
    {
        typedef wchar_t value_type;
        typedef wchar_t *pointer;
        typedef wchar_t &reference;
    };

} // namespace ustl

#endif