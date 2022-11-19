#ifndef __iterator_h
#define __iterator_h

#include "ustl.h"

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
    struct _input_itertor
    {
        /**/
    };

    struct _output_itertor
    {
        /**/
    };

    struct _forword_itertor
        : _input_itertor
    {
        /**/
    };

    struct _bothway_itertor
        : _forword_itertor
    {
    };

    struct _random_itertor
        : _bothway_itertor
    {
    };

} // namespace ustl
#endif