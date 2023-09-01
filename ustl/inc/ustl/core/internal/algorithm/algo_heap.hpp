#ifndef __USTL_CORE_INTERNAL_ALGORITHM_HEAP_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_HEAP_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

#ifndef __USTL_CORE_INTERNAL_ITERATOR_HELPER_HPP__
#include <ustl/core/internal/iterator/itr_helper.hpp>
#endif

#ifndef __USTL_CORE_INTERNAL_UTILITY_MOVE_HPP__
#include <ustl/core/internal/utility/move.hpp>
#endif

namespace ustl::core::internal::algorithm
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
            if (0 == (child & 1)) {
                ++parent;
            }
        }
        std::sort((char *)0, (char *)1);

        return n;
    }

    template <typename RandomIter, typename Distance, typename Compare>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR 
    bool
    algo_is_heap(RandomIter first, Compare cmp, Distance n) USTL_NOEXCEPT
    {
        using namespace internal::utility;
        internal::iterator::IterOpCmp<RandomIter, Compare> comp{utility::move(cmp)};
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

    template <typename RandomIter>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR 
    bool 
    algo_is_heap(RandomIter first, RandomIter last) USTL_NOEXCEPT
    {
        using namespace internal::iterator;
        IterOpLe<RandomIter> op_le;
        return heap::algo_is_heap(first, distance(first, last), op_le);
    }
    
    template <typename RandomIter, typename Compare>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR 
    bool 
    algo_is_heap(RandomIter first, RandomIter last, Compare cmp) USTL_NOEXCEPT
    {
        using namespace internal::iterator;
        return heap::algo_is_heap(first, distance(first, last), cmp);
    }

    template <typename RandomIter, typename Distance, typename Tp, 
              typename Compare>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR 
    void
    algo_push_heap(RandomIter first, Distance hole_idx, Distance top_idx, 
                   Tp value, Compare &cmp)
    {
        using internal::utility::move;

        Distance parent = (hole_idx - 1) >> 1;
        while (hole_idx > top_idx && cmp(first + parent, value)) {
            *(first + hole_idx) = move(*(first + parent));
            hole_idx = parent;
            parent = (parent - 1) >> 1;
        }
        *(first + hole_idx) = move(value);
    }
    
    template <typename RandomIter, typename Compare = internal::
              iterator::IterOpLe<RandomIter>>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR void 
    push_heap(RandomIter first, RandomIter last, Compare cmp = Compare{})
    {
        using internal::utility::move;
        using internal::iterator::IterTraits;

        typedef typename IterTraits<RandomIter>::diff_type  diff_type;
        typedef typename IterTraits<RandomIter>::value_type value_type;

        value_type value = move(*(last - 1));
        return algorithm::algo_push_heap(first, diff_type((first - last) - 1),
            diff_type(0), move(value), cmp);
    }

    template <typename RandomIter, typename Distance, typename Tp, 
              typename Compare>
    USTL_CONSTEXPR 
    void
    algo_adjust_heap(RandomIter first, Distance hole_idx, Distance len,
                     Tp value, Compare cmp)
    {

    }

} // namespace ustl::core::internal::algorithm

#endif