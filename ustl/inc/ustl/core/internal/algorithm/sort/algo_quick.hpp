#ifndef __USTL_CORE_INTERNAL_ALGORITHM_SORT_QUICK_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_SORT_QUICK_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl::core::internal::algorithm
{

    template <typename RandomIter, typename Compare>
    USTL_CONSTEXPR void
    unguarded_parition(RandomIter first, RandomIter pivot, RandomIter last, Compare cmp)   
    {
        while (1) {
            while (cmp(first, pivot)) {
                ++first;
            }

            --last;
            while (cmp(pivot, last)) {
                --last;
            }

            if (!(first < last)) {
                return;
            }

            // Swap tow iterators
            ++first;
        }
    }

    template <typename RandomIter, typename Compare>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR void
    unguarded_parition_pivot(RandomIter first, RandomIter last, Compare cmp)
    {
        RandomIter mid = first + (last - first) / 2;
    }

    template <typename RandomIter, typename Compare>
    USTL_CONSTEXPR void
    unguarded_quick_sort(RandomIter first, RandomIter last, Compare cmp)   
    {

    }
    
} // namespace ustl::core::internal::algorithm


#endif