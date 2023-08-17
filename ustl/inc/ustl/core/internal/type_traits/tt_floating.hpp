#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_FLOATING_HPP__
#define __USTL_CORE_INTERNAL_TYPETRAITS_FLOATING_HPP__

#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_BASE_HPP__ 
#include <ustl/core/internal/type_traits/tt_base.hpp>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace type_traits 
{

    template <typename Tp>
    struct IsFloating
        : false_type 
    {};

    template <>
    struct IsFloating<float>
        : true_type
    {};

    template <>
    struct IsFloating<double>
        : true_type
    {}; 

    template <>
    struct IsFloating<long double>
        : true_type
    {};

    template <>
    struct IsFloating<float const>
        : true_type
    {}; 

    template <>
    struct IsFloating<double const>
        : true_type
    {}; 
    
    template <>
    struct IsFloating<long double>
        : true_type
    {};

} // namespace ustl::core::internal::type_traits
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl


#endif