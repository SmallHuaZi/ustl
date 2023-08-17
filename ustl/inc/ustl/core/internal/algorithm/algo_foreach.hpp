#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_FOREACH_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_FOREACH_HPP__

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

    template <typename InputIter, typename UnaryFn>
    UnaryFn
    for_each(InputIter first, InputIter last, UnaryFn fn)
    USTL_NOEXCEPT(USTL_NOEXCEPT(fn(*first)))
    {
        for (; first != last; ++first) {
            fn(*first);
        }

        return fn;
    }

    template <typename InputIter, typename UnaryFn>
    UnaryFn
    for_each_n(InputIter first, usize n, UnaryFn fn)
    USTL_NOEXCEPT(USTL_NOEXCEPT(fn(*first)))
    {
        for (; 0 != n; ++first, --n) {
            fn(*first);
        }

        return fn;
    }

} // namespace ustl::core::internal::algorithm
} // namespace ustl::core::internal 
} // namespace ustl::core
} // namespace ustl


#endif