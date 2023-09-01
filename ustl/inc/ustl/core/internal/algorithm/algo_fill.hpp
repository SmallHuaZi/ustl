#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_FILL_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_FILL_HPP__


namespace ustl::core::internal::algorithm
{

    template <typename FwdIter, typename T>
    void
    fill(FwdIter first, FwdIter last, T const &value)
    {
        for (; first != last; ++first) {
            *first = value;
        }
    }


    template <typename ExecutionPolicy, typename FwdIter, typename T>
    void
    fill(ExecutionPolicy &&policy, FwdIter first, FwdIter last, T const &value)
    {}


    template <typename OutputIter, typename Size, typename T>
    void
    fill_n(OutputIter first, Size count, T const &value)
    {
        while (count--) {
            *first++ = value;
        }
    }


    template <typename ExecutionPolicy, typename OutputIter, typename Size, typename T>
    void
    fill_n(ExecutionPolicy &&policy, OutputIter first, Size count, T const &value)
    {} 
    
    
} // namespace ustl::core::internal::algorithm


#endif