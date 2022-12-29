#ifndef __USTL_ITERATOR_H
#define __USTL_ITERATOR_H

#include "include/ustl.h"

#define _CONTROL_PARAMETER_ITERATOR 1

namespace ustl
{
    /**
     *  @brief in ustl, all iteratr template had type member:
     *      @memberof value_type
     *      @memberof pointer : value_type*
     *      @memberof reference : value_type&
     *      @memberof diffence_type : diffence between begin itr and end itr;
     *      @memberof iterator_tag : iterator category
     */
    struct _input_iterator
    {};

    struct _output_iterator
    {};

    struct _forword_iterator
        : _input_iterator
    {};

    struct _bothway_iterator
        : _forword_iterator
    {};

    struct _random_iterator
        : _bothway_iterator
    {};

} // namespace ustl
#endif