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

    template <typename _Tp, typename _Tag, typename _Diff>
    struct iterator
    {
        using value_type = _Tp;
        using pointer = _Tp *;
        using reference = _Tp &;
        using diffence_type = _Diff;
        using itr_tag = _Tag;
    };

    template <typename _ForwardIterator>
    class fwd_iterator
    {
    public:
        typedef fwd_iterator _Self;
        typedef _ForwardIterator _itr_type;
        typedef typename _ForwardIterator::itr_tag itr_tag;
        typedef typename _ForwardIterator::difference_type difference_type;
        typedef typename _ForwardIterator::pointer pointer;
        typedef typename _ForwardIterator::reference reference;

        static_assert(ustl::is_same<itr_tag, _forword_itertor>()() ||
                          ustl::is_same<itr_tag, _bothway_itertor>()() ||
                          ustl::is_same<itr_tag, _random_itertor>()(),
                      "template paramater::type _ForwardIterator is not forward iterator");

    public:
        _Self
        operator+(size_t __n) ustl_cpp_noexcept
        {
            _itr_type __tmp = _M_current;
            while (__n--)
                --__tmp;
            return __tmp;
        }

        _Self &
        operator+=(size_t __n) ustl_cpp_noexcept
        {
            while (__n--)
                ++_M_current;
            return *this;
        }

        _Self &
        operator++() ustl_cpp_noexcept
        {
            ++_M_current;
            return *this;
        }

        _Self
        operator++(int) ustl_cpp_noexcept
        {
            _itr_type __tmp = _M_current++;
            return _Self(__tmp);
        }

        pointer
        operator->() ustl_cpp_noexcept
        {
            return _M_current.operator->();
        }

        reference
        operator*() ustl_cpp_noexcept
        {
            return *_M_current;
        }

        _itr_type
        base_iterator() ustl_cpp_noexcept
        {
            return _M_current;
        }

    public:
        fwd_iterator() = default;

        fwd_iterator(_itr_type __itr)
            : _M_current(__itr) {}

    protected:
        _itr_type _M_current;
    };

    template <typename _Iterator>
    class normal_iterator
    {
    public:
        typedef normal_iterator _Self;
        typedef _Iterator _itr_type;
        typedef typename _Iterator::itr_tag itr_tag;
        typedef typename _Iterator::difference_type difference_type;
        typedef typename _Iterator::reference reference;
        typedef typename _Iterator::pointer pointer;

        static_assert(ustl::is_same<itr_tag, _bothway_itertor>()() ||
                          ustl::is_same<itr_tag, _random_itertor>()(),
                      "template paramater::type _Iterator is not bothway iterator");

    public:
        _Self
        operator+(size_t __n) ustl_cpp_noexcept
        {
            _itr_type __tmp = _M_current;
            while (__n--)
                ++__tmp;
            return normal_iterator(__tmp);
        }

        _Self
        operator-(size_t __n) ustl_cpp_noexcept
        {
            _itr_type __tmp = _M_current;
            while (__n--)
                --__tmp;
            return normal_iterator(__tmp);
        }

        _Self &
        operator+=(size_t __n) ustl_cpp_noexcept
        {
            while (__n--)
                ++_M_current;
            return *this;
        }

        _Self &
        operator-=(size_t __n) ustl_cpp_noexcept
        {
            while (__n--)
                --_M_current;
            return *this;
        }

        _Self &
        operator++() ustl_cpp_noexcept
        {
            ++_M_current;
            return *this;
        }

        _Self &
        operator--() ustl_cpp_noexcept
        {
            --_M_current;
            return *this;
        }

        _Self
        operator--(int) ustl_cpp_noexcept
        {
            _itr_type __tmp = _M_current--;
            return _Self(__tmp);
        }

        _Self
        operator++(int) ustl_cpp_noexcept
        {
            _itr_type __tmp = _M_current++;
            return _Self(__tmp);
        }

        pointer
        operator->() ustl_cpp_noexcept
        {
            return _M_current.operator->();
        }

        reference
        operator*() ustl_cpp_noexcept
        {
            return *_M_current;
        }

        _itr_type
        base_iterator() ustl_cpp_noexcept
        {
            return _M_current;
        }

        template <typename _Itr>
        friend bool
        operator==(normal_iterator<_Itr> const &__l,
                   normal_iterator<_Itr> const &__r);

        template <typename _Itr>
        friend bool
        operator!=(normal_iterator<_Itr> const &__l,
                   normal_iterator<_Itr> const &__r);

        template <typename _Itr>
        friend ustl::diff_t
        operator-(normal_iterator<_Iterator> &__l,
                  normal_iterator<_Iterator> &__r);

        template <typename _Itr>
        friend ustl::diff_t
        operator+(normal_iterator<_Iterator> &__l,
                  normal_iterator<_Iterator> &__r);

    public:
        normal_iterator() = default;

        normal_iterator(_itr_type __itr)
            : _M_current(__itr) {}

    protected:
        _itr_type _M_current;
    };

    template <typename _FwdIterator>
    bool
    operator==(fwd_iterator<_FwdIterator> const &__l,
               fwd_iterator<_FwdIterator> const &__r)
    {
        return __l._M_current == __r._M_current;
    }

    template <typename _FwdIterator>
    bool
    operator!=(fwd_iterator<_FwdIterator> const &__l,
               fwd_iterator<_FwdIterator> const &__r)
    {
        return __l._M_current != __r._M_current;
    }

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

    template <typename _Iterator>
    ustl::diff_t
    operator-(normal_iterator<_Iterator> &__l,
              normal_iterator<_Iterator> &__r)
    {
        ustl::diff_t __dis = 0;
        for (; __l != __r; ++__dis, (void)++__l)
            ;
        return __dis;
    }

    template <typename _Iterator>
    bool
    operator==(normal_iterator<_Iterator> const &__l,
               normal_iterator<_Iterator> const &__r)
    {
        return __l._M_current == __r._M_current;
    }

    template <typename _Iterator>
    bool
    operator!=(normal_iterator<_Iterator> const &__l,
               normal_iterator<_Iterator> const &__r)
    {
        return __l._M_current != __r._M_current;
    }

} // namespace ustl
#endif