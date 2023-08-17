#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_COMPARE_LESS_HPP__
#define __USTL_CORE_INTERNAL_COMPARE_LESS_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_OPERATOR_HPP__ 
#include <ustl/core/internal/type_traits/tt_operator.hpp>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace compare
{

    template <typename Tp>
    struct Less
    {
        typedef Tp  element_type;

        USTL_ALWAYS_INLINE
        bool
        operator()(element_type const &x, element_type const &y) const USTL_NOEXCEPT
        { 
            static_assert(internal::type_traits::IsOverrideLe<Tp>::value, 
                      "Type 'Tp' must overload the less than "
                      "operator (<) for use with Less struct."
            );

            return x < y; 
        }
    };
    
    
} // namespace ustl::core::internal::compare
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif