#ifndef __iterator_h
#define __iterator_h

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
    };

    struct _output_itertor
    {
    };

    struct _forword_itertor
        : _input_itertor
    {
    };

    struct _bothway_itertor
        : _forword_itertor
    {
    };

    struct _random_itertor
        : _bothway_itertor
    {
    };

    template <typename _Tp, typename _Tag, typename _Diff>
    struct iterator
    {
        using value_type = _Tp;
        using pointer = _Tp *;
        using reference = _Tp &;
        using diffence_type = _Diff;
        using itr_tag = _Tag;
    };

} // namespace ustl
#endif