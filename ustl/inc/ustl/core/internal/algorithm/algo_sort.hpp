#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_SORT_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_SORT_HPP__

#include <algorithm>

namespace ustl
{
namespace core
{
namespace internal
{
namespace algorithm
{

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
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif