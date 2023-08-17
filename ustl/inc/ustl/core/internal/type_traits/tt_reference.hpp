#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_REFERENCE_HPP__
#define __USTL_CORE_INTERNAL_TYPETRAITS_REFERENCE_HPP__

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
    struct IsReference
        : false_type 
    {};

    template <typename _Tp>
    struct IsReference<_Tp &>
        : true_type
    {};


    template <typename _Tp>
    struct IsReference<_Tp &&>
        : true_type
    {};


    template <typename _Tp>
    struct IsReference<_Tp const &>
        : true_type
    {};


    template <typename _Tp>
    struct IsReference<_Tp const &&>
        : true_type
    {};


    template <typename _Tp>
    struct RemoveReference
    { typedef   _Tp     type; };


    template <typename _Tp>
    struct RemoveReference<_Tp &>
    { typedef   _Tp     type; };


    template <typename _Tp>
    struct RemoveReference<_Tp &&>
    { typedef   _Tp     type; };
        
    
} // namespace ustl::core::internal::type_traits
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif