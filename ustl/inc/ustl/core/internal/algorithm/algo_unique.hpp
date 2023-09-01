#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_UNIQUE_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_UNIQUE_HPP__


namespace ustl::core::internal::algorithm
{

    template <typename FwdIter>
    FwdIter
    unique(FwdIter first, FwdIter last)
    {
        for (; first != last; ++first) {

        }
    }
    
    
} // namespace ustl::core;:internal::algorithm

#endif