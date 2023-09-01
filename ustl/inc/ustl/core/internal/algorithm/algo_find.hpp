#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_FIND_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_FIND_HPP__


namespace ustl::core::internal::algorithm
{

    template <typename InputIter, typename T>
    auto
    find(InputIter first, InputIter last, T const &value) -> InputIter 
    {
        for (; first != last; ++first) {
            if (value == *first) {
                return first;
            }
        }

        return last;
    }


    template <typename ExecutionPolicy, typename InputIter, typename T>
    auto
    find(ExecutionPolicy &&policy, InputIter first, InputIter last, T const &value) -> InputIter
    {

    }


    template <typename FwdIter, typename UnaryPredicate>
    auto 
    find_if(FwdIter first, FwdIter last, UnaryPredicate p) -> FwdIter
    {

    }


    template <typename FwdIter, typename UnaryPredicate>
    auto 
    find_if_not(FwdIter first, FwdIter last, UnaryPredicate p) -> FwdIter
    {

    }

    
} // namespace ustl::core::internal::algorithm


#endif