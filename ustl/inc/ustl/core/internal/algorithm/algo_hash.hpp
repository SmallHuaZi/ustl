#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_HASH_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_HASH_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

#ifndef __USTL_CORE_CONTAINER_FORWARD_DECLARATION__ 
#include <ustl/core/container_fwd>
#endif

#ifndef __USTL_CORE_INTERNAL_ALGORITHM_HASH_XXHASH_HPP__
#include <ustl/core/internal/algorithm/hash/algo_xxhash.hpp>
#endif

namespace ustl::core::internal::algorithm
{

    typedef usize   hash_t;

    template <typename _Key, typename _Hasher = hash::XxHash>
    struct Hash
    {
        typedef _Key     key_type;
        typedef _Hasher  hasher_type;

        hash_t 
        operator(key_type const &key) const
        { return hasher_type()(key); }
    };
    
    extern template struct Hash<char>;
    extern template struct Hash<short>;
    extern template struct Hash<int>;
    extern template struct Hash<long>;
    extern template struct Hash<long long>;
    extern template struct Hash<float>;
    extern template struct Hash<double>;
    extern template struct Hash<string>;
    extern template struct Hash<wstring>;
    
} // namespace ustl::core::internal::algorithm


#endif