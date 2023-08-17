#ifndef __USTL_CORE_INTERNAL_ALGORITHM_HASH_XXHASH_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_HASH_XXHASH_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace algorithm
{
namespace hash
{

    struct XxHash
    {
        hash_t
        operator()();
    };
    
    
} // namespace ustl::core::internal::algorithm::hash
} // namespace ustl::core::internal::algorithm
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl::ustl



#endif