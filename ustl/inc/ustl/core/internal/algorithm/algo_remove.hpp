#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_REMOVE_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_REMOVE_HPP__


namespace ustl
{
namespace core
{
namespace internal
{
namespace algorithm
{

    template <typename FwdIter, typename T>
    FwdIter 
    remove(FwdIter first, FwdIter last, T const &value)
    {
        for (FwdIter cur = first; cur != last; ++cur) {
            if (value == *cur) {
                *first++ = *cur;
            }
        }

        return first;
    }
    
    template <typename FwdIter, typename UnaryPredicate>
    FwdIter 
    remove_if(FwdIter first, FwdIter last, UnaryPredicate pred)
    {
        for (FwdIter cur = first; cur != last; ++cur) {
            if (pred(*cur)) {
                *first++ = *cur;
            }
        }

        return first;
    }

    
} // namespace ustl::core::internal::algorithm
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif