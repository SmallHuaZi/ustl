#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_COMPARE_MAX_HPP__
#define __USTL_CORE_INTERNAL_COMPARE_MAX_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif


namespace ustl
{
namespace core
{
namespace internal
{
namespace compare
{

    template <typename _Tp>
    USTL_ALWAYS_INLINE
    static _Tp
    max(_Tp const &x, _Tp const &y) USTL_NOEXCEPT
    { return x < y ? y : x; }

    template <typename _Tp, typename _Predicate>
    USTL_ALWAYS_INLINE
    static _Tp
    max(_Tp const &x, _Tp const &y, _Predicate const &cmp) USTL_NOEXCEPT
    { return cmp(x, y) ? y : x; }
    
} // namespace ustl::core::internal::compare
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif