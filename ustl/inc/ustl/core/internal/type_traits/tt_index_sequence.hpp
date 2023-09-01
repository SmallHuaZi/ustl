#ifndef __USTL_CORE_INTERNAL_TYPE_INDEX_SEQUENCE_HPP__
#define __USTL_CORE_INTERNAL_TYPE_INDEX_SEQUENCE_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl::core::internal::type_traits 
{

    template <unsigned int Idx, typename Head, typename... Tails>
    struct IndexSequenceHelper
        : IndexSequenceHelper<Idx - 1, Tails...> 
    {};

    template <typename Head, typename... Tails>
    struct IndexSequenceHelper<0, Head, Tails...>
    { typedef Head    type; };

    template <unsigned int Idx, typename... Elems>
    struct IndexSequence
        : IndexSequenceHelper<Idx, Elems...>
    {};


    template <unsigned int Len, typename Head, typename... Tails>
    struct IndexSequenceLengthHelper
        : IndexSequenceLengthHelper<Len + 1, Tails...>
    {};

    template <unsigned int Len, typename Head>
    struct IndexSequenceLengthHelper<Len, Head>
    { static USTL_CONSTEXPR unsigned int value = Len + 1; };

    template <typename... Elems>
    struct IndexSequenceLength
        : IndexSequenceLengthHelper<0, Elems...>
    { static_assert(sizeof...(Elems) != 0, "[ustl-error] Unsupport empty types sequence.\n"); };
    
} // namespace ustl::core::internal::type_traits


#endif