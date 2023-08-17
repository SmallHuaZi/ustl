#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_POINTER_HPP__
#define __USTL_CORE_INTERNAL_TYPETRAITS_POINTER_HPP__

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
    struct IsPointer
        : false_type 
    {};

    template <typename _Tp>
    struct IsPointer<_Tp *>
        : true_type
    {};    

    template <typename _Tp>
    struct IsPointer<_Tp const *>
        : true_type
    {};
    
    template <typename _Tp>
    struct IsPointer<_Tp volatile *>
        : true_type
    {};
    
    template <typename _Tp>
    struct IsPointer<_Tp const * const>
        : true_type
    {};
    
    template <typename _Tp>
    struct IsPointer<_Tp volatile * volatile>
        : true_type
    {};
    
    
} // namespace ustl::core::internal::type_traits
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif