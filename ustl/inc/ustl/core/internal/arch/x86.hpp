#ifndef __USTL_CORE_INTERNAL_ARCHITECTURE_X86_HPP__
#define __USTL_CORE_INTERNAL_ARCHITECTURE_X86_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
    USTL_NAKED
    static inline void
    lock() 
    { 
        __asm__ volatile (
            "lock\n\t"
        ); 
    }

    template <typename Element>
    USTL_NAKED
    static inline bool 
    compare_and_exchange(Element &now, Element &flush, Element &expected)
    {
        bool res = false;

        __asm__ volatile (
            ".intel_syntax\n\t"
            "cmpxchg %0, %3\n\t"
            "sete %1\n\t"
            : "+m"(now), "=q"(res)
            : "a"(expected), "r"(flush), 
            : "memory"
        );

        return res;
    };

} // namespace internal
} // namespace core
} // namespace ustl



#endif