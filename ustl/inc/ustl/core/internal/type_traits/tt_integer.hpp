#ifndef __USTL_CORE_INTERNAL_TYPE_INTEGER_HPP__
#define __USTL_CORE_INTERNAL_TYPE_INTEGER_HPP__

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

    /** partial specialization  */
    template <typename Tp>
    struct IsInteger
        : false_type 
    {};

    template <>
    struct IsInteger<char>
        : true_type
    {};

    template <>
    struct IsInteger<short>
        : true_type
    {};

    template <>
    struct IsInteger<int>
        : true_type
    {};

    template <>
    struct IsInteger<long>
        : true_type
    {};

    template <>
    struct IsInteger<long long>
        : true_type
    {};

    template <>
    struct IsInteger<char const>
        : true_type
    {};

    template <>
    struct IsInteger<short const>
        : true_type
    {};

    template <>
    struct IsInteger<int const>
        : true_type
    {};

    template <>
    struct IsInteger<long const>
        : true_type
    {};

    template <>
    struct IsInteger<long long const>
        : true_type
    {}; 

    template <>
    struct IsInteger<unsigned char>
        : true_type
    {};

    template <>
    struct IsInteger<unsigned short>
        : true_type
    {};

    template <>
    struct IsInteger<unsigned int>
        : true_type
    {};

    template <>
    struct IsInteger<unsigned long>
        : true_type
    {};

    template <>
    struct IsInteger<unsigned long long>
        : true_type
    {};

    template <>
    struct IsInteger<unsigned char const>
        : true_type
    {};

    template <>
    struct IsInteger<unsigned short const>
        : true_type
    {};

    template <>
    struct IsInteger<unsigned int const>
        : true_type
    {};

    template <>
    struct IsInteger<unsigned long const>
        : true_type
    {};

    template <>
    struct IsInteger<unsigned long long const>
        : true_type
    {}; 
    
} // namespace ustl::core::internal::type_traits
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif