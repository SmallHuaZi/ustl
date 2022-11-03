#ifndef __itr_traits_h
#define __itr_traits_h

namespace ustl
{
    template <typename _Iterator>
    class itr_traist
    {
    public:
        typedef typename _Iterator::value_type value_type;
        typedef typename _Iterator::pointer pointer;
        typedef typename _Iterator::reference reference;
        typedef typename _Iterator::iterator_tag iterator_tag;
        typedef typename _Iterator::difference_type difference_type;
    };
}
#endif