#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_OBJECT_HPP__
#define __USTL_CORE_INTERNAL_TYPETRAITS_OBJECT_HPP__

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

    template <typename Base, typename Deri>
    struct IsBaseOf
    {
    private:
        static true_type
        _decltype(Base *);

        static true_type
        _decltype(Base &);

        static false_type
        _decltype(...);
        
    public:
        static USTL_CONSTEXPR bool const value = decltype(_decltype(declval<Deri>()))::value
                                                || decltype(_decltype(declval<Deri *>()))::value;
    };


    template <typename From, typename To>
    struct IsConvertible
    {
    private:
        static true_type
        _decltype(From);

        static false_type
        _decltype(...);

    public:
        static USTL_CONSTEXPR bool const value = decltype(_decltype(declval<To &>()))::value;
    };

        
    
} // namespace ustl::core::internal::type_traits
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif