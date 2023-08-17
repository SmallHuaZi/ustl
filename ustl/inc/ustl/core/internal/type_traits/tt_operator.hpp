#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_OPERATOR_HPP__
#define __USTL_CORE_INTERNAL_TYPETRAITS_OPERATOR_HPP__

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

    ///
    template <typename Tp, typename Up = Tp, typename Expected = Tp>
    struct IsOverrideMul 
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() * declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = Tp>
    struct IsOverrideDiv
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() / declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = Tp>
    struct IsOverrideAdd
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() + declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = Tp>
    struct IsOverrideSub
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() - declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = Tp>
    struct IsOverrideLeftShift
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() << declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = Tp>
    struct IsOverrideRightShift
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() >> declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = bool>
    struct IsOverrideLt
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() < declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = bool>
    struct IsOverrideGt
        : BooleanConstant<!IsSame<
        typename MakeVoid<decltype(declval<Tp>() > declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = bool>
    struct IsOverrideEq
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() == declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = bool>
    struct IsOverrideLe
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() <= declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = bool>
    struct IsOverrideOr
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() || declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = bool>
    struct IsOverrideAnd
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() && declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = bool>
    struct IsOverrideGe
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() >= declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = bool>
    struct IsOverrideNe
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() != declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Expected>
    struct IsOverrideDef
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(*declval<Tp>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Expected = Tp>
    struct IsOverrideBitNot
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(~declval<Tp>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = Tp>
    struct IsOverrideBitOr
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() | declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = Tp>
    struct IsOverrideBitAnd
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>() & declval<Up>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Expected = bool>
    struct IsOverrideNot
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(!declval<Tp>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Expected = Tp>
    struct IsOverrideIncf
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>()--)>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Expected = Tp>
    struct IsOverrideIncb
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(++declval<Tp>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Expected = Tp>
    struct IsOverrideDecf
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(--declval<Tp>())>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Expected = Tp>
    struct IsOverrideDecb
        : BooleanConstant<IsSame<
        typename MakeVoid<decltype(declval<Tp>()--)>::type, 
        Expected>::value>
    {};


    ///
    template <typename Tp, typename Up = Tp, typename Expected = bool>
    struct IsOverrideRel
        : BooleanConstant<IsOverrideLe<Tp, Up, Expected>::value 
                || IsOverrideGt<Tp, Up, Expected>::value
                || IsOverrideEq<Tp, Up, Expected>::value
                || IsOverrideLe<Tp, Up, Expected>::value
                || IsOverrideGe<Tp, Up, Expected>::value
                || IsOverrideNe<Tp, Up, Expected>::value>
    {};
    
} // namespace ustl::core::internal::type_traits
} // namespace ustl::core::internal
} // namespace core
} // namespace ustl



#endif