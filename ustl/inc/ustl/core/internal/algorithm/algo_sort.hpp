#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_SORT_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_SORT_HPP__

#include <ustl/core/internal/algorithm/sort/algo_quick.hpp>
#include <ustl/core/internal/algorithm/sort/algo_insertion.hpp>


namespace ustl::core::internal::algorithm
{

    /// @brief Sort base on provided iterators range
    /// @tparam FwdIter 
    /// @tparam  
    /// @param first 
    /// @param last 
    template <typename FwdIter, typename>
    void
    sort(FwdIter first, FwdIter last)
    {

    }
    

    template <typename FwdIter, typename CompPredicate>
    void
    sort(FwdIter first, FwdIter last, CompPredicate pred)
    {

    }

} // namespace ustl::core::internal::algorithm


#endif