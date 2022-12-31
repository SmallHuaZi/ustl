#ifndef __USLT_FWD_ITERATOR_H
#define __USLT_FWD_ITERATOR_H

#include "include/ustl_type_traits.h"

namespace ustl
{

    template <typename _ForwardIterator>
    class fwd_iterator
    {
    public:
        typedef     fwd_iterator                            _Self;
        typedef     _ForwardIterator                        iterator_type;
        typedef     ustl::itr_traits<_ForwardIterator>      _iterator_traits;

        typedef     ustl::diff_t                                difference_type;
        typedef     ustl::_forword_iterator                     iterator_tag;
        typedef     typename _iterator_traits::value_type       value_type;
        typedef     typename _iterator_traits::pointer          pointer;
        typedef     typename _iterator_traits::reference        reference;
        typedef     typename _iterator_traits::const_pointer    const_pointer;
        typedef     typename _iterator_traits::const_reference  const_reference;

        static_assert(ustl::__is_base<_forword_iterator, iterator_tag>()(),
                      "template paramater::type _ForwardIterator is not forward iterator");

    public:
        _Self
        operator+(difference_type  __step) ustl_cpp_noexcept;

        _Self &
        operator+=(difference_type  __step) ustl_cpp_noexcept;


    public:
        _Self &
        operator++() ustl_cpp_noexcept
        { return  ++_M_current, *this; }

        _Self
        operator++(int) ustl_cpp_noexcept
        { return    _Self(_M_current++); }

        pointer
        operator->() ustl_cpp_noexcept
        { return    _M_current.operator->(); }

        reference
        operator*()     ustl_cpp_noexcept
        { return    *_M_current; }

        iterator_type
        base_iterator() ustl_cpp_noexcept
        { return    _M_current; }


    public:
        fwd_iterator() = default;

        fwd_iterator(iterator_type __itr)
            : _M_current(__itr) {}


    protected:
        iterator_type _M_current;
    };


    template <typename _FwdItr>
    inline auto
    fwd_iterator<_FwdItr>::
        operator+=(difference_type  __step) ustl_cpp_noexcept -> _Self &
    {
        while(__step > 0)
            ++_M_current, --__step;
        return  *this;
    }


    template <typename _FwdItr>
    inline auto
    fwd_iterator<_FwdItr>::
        operator+(difference_type   __step) ustl_cpp_noexcept -> _Self
    {
        _Self   __tmp(*this);
        __tmp += __step;
        return  __tmp;
    }


    template <typename _FwdIterator>
    static inline bool
    operator==(fwd_iterator<_FwdIterator> const &__l,
               fwd_iterator<_FwdIterator> const &__r) ustl_cpp_noexcept
    { return __l.base_iterator() == __r.base_iterator(); }



    template <typename _FwdIterator>
    static inline bool
    operator!=(fwd_iterator<_FwdIterator> const &__l,
               fwd_iterator<_FwdIterator> const &__r) ustl_cpp_noexcept
    { return __l.base_iterator() != __r.base_iterator(); }



    template <typename _FwdIterator>
    ustl::diff_t
    operator-(fwd_iterator<_FwdIterator> &__l,
              fwd_iterator<_FwdIterator> &__r)
    {
        ustl::diff_t __dis = 0;
        for (; __l != __r; ++__dis, (void)++__l)
            ;
        return __dis;
    }

} // namespace ustl

#endif