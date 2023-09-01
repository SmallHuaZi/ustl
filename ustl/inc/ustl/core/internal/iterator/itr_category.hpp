#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ITERATOR_CATEGORY_HPP__
#define __USTL_CORE_INTERNAL_ITERATOR_CATEGORY_HPP__


namespace ustl::core::internal::iterator
{

    struct InputIter
    {};


    struct OutputIter
    {};


    struct ForwardIter
        : InputIter 
    {};


    struct BothwayIter
        : ForwardIter
    {};


    struct RandomIter
        : BothwayIter
    {};


    typedef iterator::InputIter       input_iter_category;
    typedef iterator::OutputIter      output_iter_category;
    typedef iterator::ForwardIter     forward_iter_category;
    typedef iterator::BothwayIter     bothway_iter_category;
    typedef iterator::RandomIter      random_iter_category;

} // namespace ustl::core::internal::iterator


#endif