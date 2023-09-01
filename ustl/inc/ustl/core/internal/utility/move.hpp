#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_UTILITY_MOVE_HPP__
#define __USTL_CORE_INTERNAL_UTILITY_MOVE_HPP__

#ifndef __USTL_CORE_INTERNAL_TYPE_REFERENCE_HPP__
#include <ustl/core/internal/type_traits/tt_reference.hpp>
#endif


namespace ustl
{
namespace core
{
namespace internal
{
namespace utility
{

    template <typename T>
    USTL_ALWAYS_INLINE
    typename internal::type_traits::RemoveReference<T>::type &&
    move(T &&lr) USTL_NOEXCEPT
    { return static_cast<typename internal::type_traits::RemoveReference<T>::type &&>(lr); }


    template <typename T>
    USTL_ALWAYS_INLINE
    T &&
    forward(T &lr) USTL_NOEXCEPT
    { return static_cast<T &&>(lr); }


    template <typename T>
    USTL_ALWAYS_INLINE
    T &&
    forward(T &&rr) USTL_NOEXCEPT
    { return static_cast<T &&>(rr); }   
        
} // namespace ustl::core::internal::utility
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif