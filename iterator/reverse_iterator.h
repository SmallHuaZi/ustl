#ifndef __reverse_iterator_h
#define __reverse_iterator_h

namespace ustl
{
    template <typename _Itr>
    struct reverse_iterator
    {
        typedef typename _Itr::value_type value_type;
        typedef typename _Itr::pointer pointer;
        typedef typename _Itr::reference reference;
        typedef typename _Itr::const_pointer const_pointer;
        typedef typename _Itr::const_reference const_reference;
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

    private:
        _Itr _M_current;
    };
}

#endif