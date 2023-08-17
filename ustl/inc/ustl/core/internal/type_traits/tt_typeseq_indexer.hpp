#ifndef __USTL_CORE_INTERNAL_TYPE_TYPESEQUINDEXER_HPP__
#define __USTL_CORE_INTERNAL_TYPE_TYPESEQUINDEXER_HPP__


namespace ustl
{
namespace core
{
namespace internal
{
namespace type_traits
{

    template <unsigned int Idx, typename Head, typename... Tails>
    struct TypeSeqIndexerHelper
        : TypeSeqIndexerHelper<Idx - 1, Tails...> 
    {};

    template <typename Head, typename... Tails>
    struct TypeSeqIndexerHelper<0, Head, Tails...>
    { typedef Head    type; };

    template <unsigned int Idx, typename... Elems>
    struct TypeSeqIndexer
        : TypeSeqIndexerHelper<Idx, Elems...>
    {};


    template <unsigned int Len, typename Head, typename... Tails>
    struct TypeSeqLengthHelper
        : TypeSeqLengthHelper<Len + 1, Tails...>
    {};

    template <unsigned int Len, typename Head>
    struct TypeSeqLengthHelper<Len, Head>
    { static USTL_CONSTEXPR unsigned int value = Len + 1; };

    template <typename... Elems>
    struct TypeSeqLength
        : TypeSeqLengthHelper<0, Elems...>
    {};
    
} // namespace ustl::core::internal::type_traits
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif