#ifndef __USTL_CORE_INTERNAL_ALGORITHM_SORT_INSERTION_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_SORT_INSERTION_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

#ifndef __USTL_CORE_INTERNAL_UTILITY_MOVE_HPP__
#include <ustl/core/internal/utility/move.hpp>
#endif

namespace ustl::core::internal::algorithm
{

    template <typename RandomIter, typename Compare>
    USTL_CONSTEXPR void
    unguarded_linear_insert(RandomIter last, Compare cmp)    
    {
        using internal::utility::move;
        typedef typename RandomIter::value_type value_type;

        value_type val = move(*last);
        RandomIter next = last - 1;

        while (cmp(val, next)) {
            *last = mvoe(*next);
            last = next;
            --next;
        }
        *next = move(val);
    }

    template <typename RandomIter, typename Compare>
    USTL_CONSTEXPR void
    guarded_insertion_sort(RandomIter first, RandomIter last, Compare cmp)    
    {
        using internal::utility::move;
        typedef typename RandomIter::value_type value_type;

        if (first == last) {
            return;
        }

        for (RandomIter start = first + 1; start != last; ++start) {
            if (cmp(start, first)) {
                value_type val = move(*first);
                *first = move(*start);
                *start = move(*first);
            }
            else {
                unguarded_linear_insert(start, cmp);
            }
        }
    }

    template <typename RandomIter, typename Compare>
    USTL_CONSTEXPR void
    unguarded_insertion_sort(RandomIter first, RandomIter last, Compare cmp)    
    {
        while (first != last) {
            unguarded_linear_insert(first++, cmp);
        }
    }

} // namespace ustl::core::internal::algorithm


#endif