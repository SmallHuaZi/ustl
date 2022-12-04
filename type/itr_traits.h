#ifndef __itr_traits_h
#define __itr_traits_h

namespace ustl
{
    template <typename>
    struct itr_traits;

    template <typename _Iterator>
    struct itr_traits
    {
        typedef typename _Iterator::value_type value_type;
        typedef typename _Iterator::pointer pointer;
        typedef typename _Iterator::reference reference;
        typedef typename _Iterator::const_pointer const_pointer;
        typedef typename _Iterator::const_reference const_reference;
        typedef typename _Iterator::iterator_tag iterator_tag;

        typedef ustl::diff_t difference_type;
    };

    template <typename _Tp>
    struct itr_traits<_Tp *>
    {
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;
        typedef ustl::_random_iterator iterator_tag;

        typedef ustl::diff_t difference_type;
    };

    template <typename _Tp>
    struct itr_traits<_Tp const *>
    {
        typedef _Tp value_type;
        typedef _Tp const *pointer;
        typedef _Tp const &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;
        typedef ustl::_random_iterator iterator_tag;

        typedef ustl::diff_t difference_type;
    };

}
#endif