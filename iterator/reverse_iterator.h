#ifndef __USTL_REVERSE_ITERATOR_H
#define __USTL_REVERSE_ITERATOR_H

#include "include/ustl_type_traits.h"

namespace ustl
{
    template <typename _Itr>
    struct reverse_iterator
    {
        typedef     _Itr                        iterator_type;
        typedef     ustl::diff_t                difference_type;
        typedef     reverse_iterator            _Self;
        typedef     ustl::itr_traits<_Itr>      _iterator_traits;

        typedef     typename _iterator_traits::iterator_tag     iterator_tag;
        typedef     typename _iterator_traits::value_type       value_type;
        typedef     typename _iterator_traits::pointer          pointer;
        typedef     typename _iterator_traits::reference        reference;
        typedef     typename _iterator_traits::const_pointer    const_pointer;
        typedef     typename _iterator_traits::const_reference  const_reference;


    public:
        _Self
        operator+(difference_type   __step) ustl_cpp_noexcept;

        _Self
        operator-(difference_type   __step) ustl_cpp_noexcept;

        _Self &
        operator-=(difference_type  __step) ustl_cpp_noexcept;

        _Self &
        operator+=(difference_type  __step) ustl_cpp_noexcept;


    public:
        _Self &
        operator++()    ustl_cpp_noexcept
        { return  --_M_current, *this; }

        _Self &
        operator--()    ustl_cpp_noexcept
        { return  ++_M_current , *this; }

        _Self
        operator++(int) ustl_cpp_noexcept
        { return _Self(_M_current--); }

        _Self
        operator--(int) ustl_cpp_noexcept
        { return _Self(_M_current++); }

        reference
        operator*()     ustl_cpp_noexcept
        { return    *_M_current; }

        pointer
        operator->()    ustl_cpp_noexcept
        { return    _M_current.operator->(); }

        iterator_type
        base_iterator() ustl_cpp_noexcept
        { return    iterator_type(_M_current); }

        iterator_type const
        base_iterator() const   ustl_cpp_noexcept
        { return    iterator_type(_M_current); }


    public:
        reverse_iterator() = default;

        reverse_iterator(iterator_type __itr)
            : _M_current(__itr) {}


    private:
        iterator_type _M_current;
    };


    template <typename _Itr>
    inline auto
    reverse_iterator<_Itr>::
        operator+=(difference_type  __step) ustl_cpp_noexcept -> _Self &
    {
        while(__step > 0)
            ++_M_current, --__step;
        if(__step < 0)
            _M_current -= __step;
        return  *this;
    }


    template <typename _Itr>
    inline auto
    reverse_iterator<_Itr>::
        operator-=(difference_type  __step) ustl_cpp_noexcept -> _Self &
    {
        while(__step < 0)
            --_M_current, ++__step;
        if(__step > 0)
            _M_current += __step;
        return  *this;
    }


    template <typename _Itr>
    inline reverse_iterator<_Itr>
    reverse_iterator<_Itr>::
        operator-(difference_type   __step) ustl_cpp_noexcept
    {
        _Self   __tmp(*this);
        __tmp -= __step;
        return  __tmp;
    }    


    template <typename _Itr>
    inline reverse_iterator<_Itr>
    reverse_iterator<_Itr>::
        operator+(difference_type   __step) ustl_cpp_noexcept
    {
        _Self   __tmp(*this);
        __tmp += __step;
        return  __tmp;
    }



    template <typename _Iterator>
    static inline ustl::diff_t
    operator-(reverse_iterator<_Iterator> &__last,
              reverse_iterator<_Iterator> &__first)
    {
        ustl::diff_t __dis_ret = 0;
        while (__first != __last)
            ++__dis_ret, (void)++__first;
        return __dis_ret;
    }



    template <typename _Iterator>
    static inline bool
    operator==(reverse_iterator<_Iterator> const &__l,
               reverse_iterator<_Iterator> const &__r)
    { return __l.base_iterator() == __r.base_iterator(); }



    template <typename _Iterator>
    static inline bool
    operator!=(reverse_iterator<_Iterator> const &__l,
               reverse_iterator<_Iterator> const &__r)
    { return __l.base_iterator() != __r.base_iterator(); }


}

#endif