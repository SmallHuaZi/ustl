#ifndef __char_traits_h
#define __char_traits_h

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
    };

} // namespace ustl

#endif