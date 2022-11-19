#ifndef __reverse_iterator_h
#define __reverse_iterator_h

#include "ustl_type_traits.h"

namespace ustl
{
    template <typename _Itr>
    struct reverse_iterator
    {
        typedef ustl::itr_traits<_Itr> _iterator_traits;
        typedef _Itr iterator_type;

        typedef typename _iterator_traits::iterator_tag iterator_tag;
        typedef typename _iterator_traits::value_type value_type;
        typedef typename _iterator_traits::pointer pointer;
        typedef typename _iterator_traits::reference reference;
        typedef typename _iterator_traits::const_pointer const_pointer;
        typedef typename _iterator_traits::const_reference const_reference;
        typedef reverse_iterator _Self;

        _Self &
        operator++()
        {
            --_M_current;
            return *this;
        }

        _Self
        operator--()
        {
            ++_M_current;
            return *this;
        }

        _Self
        operator++(int)
        {
            _Itr __tmp = _M_current;
            --_M_current;
            return _Self(__tmp);
        }

        _Self
        operator--(int)
        {
            _Itr __tmp = _M_current;
            ++_M_current;
            return _Self(__tmp);
        }

        reference
        operator*()
        {
            return *_M_current;
        }

        pointer
        operator->()
        {
            return _M_current.operator->();
        }

        friend bool
        operator==(_Self const &__l,
                   _Self const &__r)
        {
            return __l._M_current == __r._M_current;
        }

        friend bool
        operator!=(_Self const &__l,
                   _Self const &__r)
        {
            return __l._M_current != __r._M_current;
        }

        reverse_iterator() = default;

        reverse_iterator(iterator_type __itr)
            : _M_current(__itr) {}

    private:
        iterator_type _M_current;
    };
}

#endif