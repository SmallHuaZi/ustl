#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_MOVE_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_MOVE_HPP__

#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_RVALUE_HPP__ 
#include <ustl/core/internal/type_traits/tt_rvalue.hpp>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace algorithm
{

    template <typename InputIter, typename OutputIter>
    OutputIter 
    move_forward(InputIter first, InputIter last, OutputIter result)
    {
        while (first != last) {
            *result++ = move(*first++);
        }

        return result;
    }
    

    template <typename InputIter, typename Size, typename OutputIter>
    OutputIter 
    move_forward_n(InputIter first, Size count, OutputIter result)
    {
        while (count--) {
            *result++ = move(*first++);
        }

        return result;
    }
    

    template <typename InputIter, typename OutputIter, typename UnaryPredicate>
    OutputIter 
    move_forward_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate pred)
    {
        while (first != last) {
            if (pred(*first)) {
                *result++ = move(*first);
            }
            ++first;
        }

        return result;
    }


    template <typename BothWayIter, typename BothWayIter2>
    BothWayIter2 
    move_backward(BothWayIter  first, BothWayIter last, BothWayIter2 result)
    {
        while (first != last) {
            *--result = move(*--last);
        }

        return result;
    }


    template <typename BothWayIter, typename Size, typename BothWayIter2>
    BothWayIter2 
    move_backward_n(BothWayIter last, Size count, BothWayIter2 result)
    {
        while (count--) {
            *--result = move(*--last);
        }

        return result;
    }


    template <typename BothWayIter, typename BothWayIter2, typename UnaryPredicate>
    BothWayIter2 
    move_backward_if(BothWayIter first, BothWayIter last, BothWayIter2 result, UnaryPredicate pred)
    {
        while (first != last) {
            if (pred(*last)) {
                *--result = move(*last);
            }
            --last;
        }

        return result;
    }


    template <typename BothWayIter, typename BothWayIter2>
    BothWayIter2 
    reverse_move(BothWayIter first, BothWayIter last, BothWayIter2 first1)
    {
        while (first != last) {
            *first1++ = move(*--last);
        }

        return first1;
    }


    template <typename BothWayIter, typename Size, typename BothWayIter2>
    BothWayIter2 
    reverse_move_n(BothWayIter last, Size count, BothWayIter2 first1)
    {
        while (count--) {
            *first1++ = move(*--last);
        }

        return first1;
    }


    template <typename BothWayIter, typename BothWayIter2, typename UnaryPredicate>
    BothWayIter2 
    reverse_move_if(BothWayIter first, BothWayIter last, BothWayIter2 first1, UnaryPredicate pred)
    {
        while (first != last) {
            if (pred(*--last)) {
                *first1++ = move(*last);
            }
        }

        return first1;
    }
    
    
} // namespace ustl::core::internal::algorithm
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl


#endif