#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_BASE_HPP__ 
#define __USTL_CORE_INTERNAL_TYPETRAITS_BASE_HPP__ 

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl
{
namespace core
{
namespace internal
{    
namespace type_traits
{

    /// @brief 
    /// @tparam Tp 
    /// @return 
    template <typename Tp>
    static Tp &
    declval();


    /// @brief 
    /// @tparam T 
    /// @tparam v 
    template <typename T, T v>
    struct IntegralConstant
    {
        typedef T  value_type;
        typedef IntegralConstant<T, v>   type;

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        operator bool() USTL_NOEXCEPT
        { return    value; }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        value_type
        operator()() USTL_NOEXCEPT
        { return    value; }

        static USTL_CONSTEXPR value_type value = v;
    };


    /// @brief 
    /// @tparam val 
    template <bool val>
    struct BooleanConstant
        : public IntegralConstant<bool, val>
    {};

    typedef BooleanConstant<true>       true_type;
    typedef BooleanConstant<false>      false_type;


    /// @brief 
    /// @tparam T 
    template <typename... T>
    struct MakeVoid 
    { typedef void type; };


    /// @brief 
    /// @tparam _Tp 
    /// @tparam  
    template <bool, typename _Tp = void>
    struct EnableIf
    {};

    template <typename _Tp>
    struct EnableIf<true, _Tp>
    { typedef   _Tp         type; };


    /// @brief 
    /// @tparam _Then 
    /// @tparam _Else 
    /// @tparam _Condition 
    template <bool _Condition, typename _Then, typename _Else>
    struct Conditional;

    template <typename _Then, typename _Else>
    struct Conditional<true, _Then, _Else>
    { typedef   _Then   type; };

    template <typename _Then, typename _Else>
    struct Conditional<false, _Then, _Else>
    { typedef   _Else   type; };


    /// @brief 
    /// @tparam T 
    /// @tparam U 
    template <typename T, typename U>
    struct IsSame 
        : false_type {};

    template <typename T>
    struct IsSame<T, T>
        : true_type {};


    /// @brief 
    /// @tparam _Tp 
    template <typename _Tp>
    struct TypeIdextity
    { typedef   _Tp     type; };


} // namespace ustl::core::internal::type_traits
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif