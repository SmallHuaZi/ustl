#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ALGORITHM_COPY_HPP__
#define __USTL_CORE_INTERNAL_ALGORITHM_COPY_HPP__


namespace ustl::core::internal::algorithm
{

    template <typename InputIter, typename OutputIter>
    OutputIter 
    copy(InputIter first, InputIter last, OutputIter result)
    {
        while (first != last) {
            *result++ = *first++;
        }

        return result;
    }
    

    template <typename InputIter, typename Size, typename OutputIter>
    OutputIter 
    copy_n(InputIter first, Size count, OutputIter result)
    {
        while (count--) {
            *result++ = *first++;
        }

        return result;
    }
    

    template <typename InputIter, typename OutputIter, typename UnaryPredicate>
    OutputIter 
    copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate pred)
    {
        while (first != last) {
            if (pred(*first)) {
                *result++ = *first;
            }
            ++first;
        }

        return result;
    }


    template <typename BothWayIter, typename BothWayIter2>
    BothWayIter2 
    copy_backward(BothWayIter  first, BothWayIter last, BothWayIter2 result)
    {
        while (first != last) {
            *--result = *--last;
        }

        return result;
    }


    template <typename BothWayIter, typename Size, typename BothWayIter2>
    BothWayIter2 
    copy_backward_n(BothWayIter last, Size count, BothWayIter2 result)
    {
        while (count--) {
            *--result = *--last;
        }

        return result;
    }


    template <typename BothWayIter, typename BothWayIter2, typename UnaryPredicate>
    BothWayIter2 
    copy_backward_if(BothWayIter first, BothWayIter last, BothWayIter2 result, UnaryPredicate pred)
    {
        while (first != last) {
            if (pred(*last)) {
                *--result = *last;
            }
            --last;
        }

        return result;
    }


    template <typename BothWayIter, typename BothWayIter2>
    BothWayIter2 
    reverse_copy(BothWayIter first, BothWayIter last, BothWayIter2 first1)
    {
        while (first != last) {
            *first1++ = *--last;
        }

        return first1;
    }


    template <typename BothWayIter, typename Size, typename BothWayIter2>
    BothWayIter2 
    reverse_copy_n(BothWayIter last, Size count, BothWayIter2 first1)
    {
        while (count--) {
            *first1++ = *--last;
        }

        return first1;
    }


    template <typename BothWayIter, typename BothWayIter2, typename UnaryPredicate>
    BothWayIter2 
    reverse_copy_if(BothWayIter first, BothWayIter last, BothWayIter2 first1, UnaryPredicate pred)
    {
        while (first != last) {
            if (pred(*--last)) {
                *first1++ = *last;
            }
        }

        return first1;
    }

} // namespace ustl::core::internal::algorithm



#endif