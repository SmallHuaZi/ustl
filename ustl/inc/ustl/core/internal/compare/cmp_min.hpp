#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_COMPARE_MIN_HPP__
#define __USTL_CORE_INTERNAL_COMPARE_MIN_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif


namespace ustl
{
namespace core
{
namespace internal
{
namespace compre
{

    template <typename _Tp>
    USTL_ALWAYS_INLINE
    static _Tp
    min(_Tp const &x, _Tp const &y) USTL_NOEXCEPT
    { return x < y ? x : y; }

    template <typename _Tp, typename _Predicate>
    USTL_ALWAYS_INLINE
    static _Tp
    min(_Tp const &x, _Tp const &y, _Predicate const &cmp) USTL_NOEXCEPT
    { return cmp(x, y) ? x : y; }
    
    
} // namespace ustl::core::internal::compre
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif