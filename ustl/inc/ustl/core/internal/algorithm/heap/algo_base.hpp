#ifndef __USTL_CORE_INTERNAL_ALGORITHM_HEAP_BASE_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_HEAP_BASE_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

#ifndef __USTL_CORE_INTERNAL_ITERATOR_HELPER_HPP__
#include <ustl/core/internal/iterator/itr_helper.hpp>
#endif

#ifndef __USTL_CORE_INTERNAL_UTILITY_MOVE_HPP__
#include <ustl/core/internal/utility/move.hpp>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace algorithm
{
namespace heap
{

    template <typename RandomIter, typename Distance, typename Compare>
    USTL_CONSTEXPR 
    Distance
    algo_is_heap_until(RandomIter first, Distance n, Compare &cmp) USTL_NOEXCEPT
    {
        Distance parent = 0;
        for (Distance child = 1; child < n; ++child) {
            if (cmp(first + parent, first + child)) {
                return child;
            }
            if (0 == (child & 1) {
                ++parent;
            }
        }

        return n;
    }

    template <typename RandomIter, typename Distance, typename Compare>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR 
    bool
    algo_is_heap(RandomIter first, Compare cmp, Distance n) USTL_NOEXCEPT
    {
        using namespace internal::utility;
        internal::iterator::IterCmp<RandomIter, Compare> comp{utility::move(cmp)};
        return heap::algo_is_heap_until(first, n, comp) == n;
    }

    template <typename RandomIter, typename Distance>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR 
    bool
    algo_is_heap(RandomIter first, Distance n) USTL_NOEXCEPT
    {
        internal::iterator::IterOpLe<RandomIter> op_le;
        return heap::algo_is_heap_until(first, n, op_le) == n;
    }

    
} // namespace ustl::core::internal::algorithm::heap
} // namespace ustl::core::internal::algorithm
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl::ustl


#endif