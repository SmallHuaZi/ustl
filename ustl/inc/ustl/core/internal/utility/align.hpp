#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_UTILITY_ALIGN_HPP__
#define __USTL_CORE_INTERNAL_UTILITY_ALIGN_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace utility
{

    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    static usize 
    align_lower(usize n, usize a) USTL_NOEXCEPT
    { return n & ~(a - 1); }

    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    static usize 
    align_upper(usize n, usize a) USTL_NOEXCEPT
    { return (n + a - 1) & ~(a - 1); }

} // namespace ustl::core::internal::utility
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl

#endif