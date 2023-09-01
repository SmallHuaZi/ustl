#ifndef __USTL_CORE_INTERNAL_ALGORITHM_HASH_XXHASH_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_HASH_XXHASH_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl::core::internal::algorithm::hash 
{

    struct XxHash
    {
        hash_t
        operator()();
    };
    
    
} // namespace ustl::core::internal::algorithm::hash

#endif