#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_CV_HPP__ 
#define __USTL_CORE_INTERNAL_TYPETRAITS_CV_HPP__ 

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

    template <typename _Tp>
    struct RemoveConst
    { typedef _Tp   type; };

    template <typename _Tp>
    struct RemoveConst<_Tp const>
    { typedef _Tp   type; };


    template <typename _Tp>
    struct RemoveVolatile
    { typedef _Tp   type; };

    template <typename _Tp>
    struct RemoveVolatile<_Tp volatile>
    { typedef _Tp   type; };


    template <typename _Tp>
    struct RemoveConstAndVolatile 
    { typedef _Tp   type; };

    template <typename _Tp>
    struct RemoveConstAndVolatile<_Tp const>
    { typedef _Tp   type; };

    template <typename _Tp>
    struct RemoveConstAndVolatile<_Tp volatile>
    { typedef _Tp   type; };

    template <typename _Tp>
    struct RemoveConstAndVolatile<_Tp const volatile>
    { typedef _Tp   type; };


    template <typename _Tp>
    struct HadConst 
        : false_type
    {};

    template <typename _Tp>
    struct HadConst<_Tp const>
        : true_type
    {};

    template <typename _Tp>
    struct HadConst<_Tp const *>
        : true_type
    {};

    template <typename _Tp>
    struct HadConst<_Tp * const>
        : false_type
    {};


    template <typename _Tp>
    struct HadVolatile
        : false_type
    {};

    template <typename _Tp>
    struct HadVolatile<_Tp volatile>
        : true_type
    {};

    template <typename _Tp>
    struct HadVolatile<_Tp volatile *>
        : true_type
    {};

    template <typename _Tp>
    struct HadVolatile<_Tp * volatile>
        : false_type
    {};


    template <typename _Tp>
    struct HadConstOrVolatile
        : false_type
    {};

    template <typename _Tp>
    struct HadConstOrVolatile
        : BooleanConstant<HadConst<_Tp>::value || HadVolatile<_Tp>::value>
    {};

} // namespace ustl::core::internal::type_traits
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif