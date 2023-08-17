#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_COUNT_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_COUNT_HPP__

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

    template <typename InputIter>
    usize
    count(InputIter first, InputIter last) USTL_NOEXCEPT
    {
        usize count = 0;
        while (first++ != last) {
            ++count;
        }

        return count;
    }

    template <typename InputIter, typename Predicate>
    usize
    count_if(InputIter first, InputIter last, Predicate pred)
    USTL_NOEXCEPT(USTL_NOEXCEPT(pred(*first)))
    {
        usize count = 0;
        while (first != last) {
            if (pred(*first++)) {
                ++count;
            }
        }

        return count;
    }

} // namespace ustl::core::internal::algorithm
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif