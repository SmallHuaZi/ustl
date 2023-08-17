#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_CONTAINER_PAIR_HPP__
#define __USTL_CORE_INTERNAL_CONTAINER_PAIR_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace container 
{

    template <typename First, typename Second>
    struct Pair
    {
        USTL_GENERAL_ASSOCIATION_TYPE(Pair);
    
        typedef First      first_type;
        typedef Second     second_type;

    public:
        USTL_ALWAYS_INLINE
        USTL_CONSTEXPR Pair() = default;

        USTL_ALWAYS_INLINE
        USTL_CONSTEXPR Pair(
            first_type const &f, 
            second_type const &s
        );

    public:
        USTL_ALWAYS_INLINE
        first_type *
        first_ptr() USTL_NOEXCEPT
        { return    &this->_M_first; }

        USTL_ALWAYS_INLINE
        second_type *
        second_ptr() USTL_NOEXCEPT
        { return    &this->_M_second; }

        USTL_ALWAYS_INLINE
        first_type &
        first() USTL_NOEXCEPT
        { return    this->_M_first; }

        USTL_ALWAYS_INLINE
        second_type &
        second() USTL_NOEXCEPT
        { return    this->_M_second; }

        void
        swap(Ref other);

        Ref
        operator=(ConstRef other) &;

        Ref
        operator=(Self &&other) &;

    private:
        first_type     _M_first;
        second_type    _M_second;
    };


    template <unsigned int Idx, typename... Elems>
    struct ElemExtractor;

    template <typename... Elems>
    struct ElemExtractor<0, Pair<Elems...>>
    {
        typedef typename internal::type_traits::TypeSeqIndexer<0, Elems...>::type   type;

        USTL_ALWAYS_INLINE
        type const &
        operator()(Pair<Elems...> const &pair) const USTL_NOEXCEPT
        {
            return pair.first();
        }

        USTL_ALWAYS_INLINE
        type &
        operator()(Pair<Elems...> &&pair) const USTL_NOEXCEPT
        {
            return pair.first();
        }
    };

    template <typename... Elems>
    struct ElemExtractor<1, Pair<Elems...>>
    {
        typedef typename internal::type_traits::TypeSeqIndexer<1, Elems...>::type   type;

        USTL_ALWAYS_INLINE
        type const &
        operator()(Pair<Elems...> const &pair) const USTL_NOEXCEPT
        {
            return pair.second();
        }

        USTL_ALWAYS_INLINE
        type &
        operator()(Pair<Elems...> &pair) const USTL_NOEXCEPT
        {
            return pair.second();
        }
    };


    template <typename First, typename Second>
    USTL_CONSTEXPR
    Pair<First, Second>:: 
        Pair(first_type const &f, second_type const &s)
        : _M_first(f), 
          _M_second(s)
    {}


    template <typename First, typename Second>
    void
    Pair<First, Second>:: 
        swap(Ref other)
    {
        
    }


    template <typename First, typename Second>
    auto
    Pair<First, Second>:: 
        operator=(ConstRef other) & -> Self &
    {

    }


    template <typename First, typename Second>
    auto
    Pair<First, Second>:: 
        operator=(Self &&other) & -> Self &
    {

    }

    
} // namespace ustl::core::internal::container
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl


#endif