#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_NUMBERICAL_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_NUMBERICAL_HPP__


namespace ustl 
{
namespace core 
{
namespace internal
{
namespace algorithm
{

    template <typename Number, typename Float>
    static inline Number
    lerp(Number from, Number to, Float t)
    { return  (1 - t) * from + t * to; }


    template <typename Number, typename Float>
    static inline Number
    slerp(Number from, Number to, Float t)
    { return  from + (from - to) * t; }


    template <typename Number, typename Range>
    static inline Number
    clamp(Number n, Range range)
    {
    }

    
} // namespace ustl::core::internal::algorithm
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl




#endif