#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_RVALUE_HPP__
#define __USTL_CORE_INTERNAL_TYPETRAITS_RVALUE_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_BASE_HPP__
#include <ustl/core/internal/type_traits/tt_base.hpp>
#endif

#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_REFERENCE_HPP__ 
#include <ustl/core/internal/type_traits/tt_reference.hpp>
#endif


namespace ustl
{
namespace core
{
namespace internal
{
namespace type_traits
{

    template <typename T>
    USTL_ALWAYS_INLINE
    typename RemoveReference<T>::type &&
    move(T &&__lr)
    { return static_cast<typename RemoveReference<T>::type &&>(__lr); }


    template <typename T>
    USTL_ALWAYS_INLINE
    T &&
    forward(T &__lr)
    { return static_cast<T &&>(__lr); }


    template <typename T>
    USTL_ALWAYS_INLINE
    T &&
    forward(T &&__rr)
    { return static_cast<T &&>(__rr); }
    
    
} // namespace ustl::internal::type_traits
} // namespace ustl::internal
} // namespace ustl::core
} // namespace ustl



#endif