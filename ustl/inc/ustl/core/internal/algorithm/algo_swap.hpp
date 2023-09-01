#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_SWAP_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_SWAP_HPP__

#ifndef __USTL_CORE_INTERNAL_UTILITY_MOVE_HPP__
#include <ustl/core/internal/utility/move.hpp>
#endif

namespace ustl::core::internal::algorithm
{

    template <typename Tp>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    void 
    swap(Tp &x, Tp &y)
    {
        Tp tmp = move(*x);
        *x = move(*y);
        *y = move(tmp);
    }

    template <typename FwdIter>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    void
    swap_ranges(FwdIter first1, FwdIter last1, FwdIter first2)
    {
        while (first1 != last1) {
            algorithm::swap(*first1++, *first2++);
        }
    }

    template <typename FwdIter>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    void 
    iter_swap(FwdIter &x, FwdIter &y)
    { algorithm::swap(*x, *y); }
    
} // namespace ustl::core::internal::algorithm


#endif