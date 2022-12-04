#ifndef __normal_iterator_h
#define __normal_iterator_h

namespace ustl
{

    template <typename _Iterator>
    class normal_iterator
    {
    public:
        typedef normal_iterator _Self;
        typedef typename ustl::remove_cv<_Iterator>::type iterator_type;
        typedef ustl::itr_traits<_Iterator> _iterator_traits;

        typedef typename _iterator_traits::iterator_tag iterator_tag;
        typedef typename _iterator_traits::value_type value_type;
        typedef typename _iterator_traits::pointer pointer;
        typedef typename _iterator_traits::reference reference;
        typedef typename _iterator_traits::const_pointer const_pointer;
        typedef typename _iterator_traits::const_reference const_reference;
        typedef typename _iterator_traits::difference_type difference_type;

        static_assert(ustl::is_same<iterator_tag, _bothway_iterator>()() ||
                          ustl::is_same<iterator_tag, _random_iterator>()(),
                      "template paramater::type _Iterator is not bothway iterator");

    public:
        _Self
        operator+(size_t __n) ustl_cpp_noexcept
        {
            iterator_type __tmp = _M_current;
            while (__n--)
                ++__tmp;
            return normal_iterator(__tmp);
        }

        _Self
        operator-(size_t __n) ustl_cpp_noexcept
        {
            iterator_type __tmp = _M_current;
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
            iterator_type __tmp = _M_current--;
            return _Self(__tmp);
        }

        _Self
        operator++(int) ustl_cpp_noexcept
        {
            iterator_type __tmp = _M_current++;
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

        iterator_type const &
        base_iterator() const ustl_cpp_noexcept
        {
            return _M_current;
        }

    public:
        normal_iterator() = default;

        normal_iterator(iterator_type __itr)
            : _M_current(__itr) {}

        normal_iterator(normal_iterator<iterator_type> const &__non_cv)
            : _M_current(__non_cv.base_iterator()) {}

    protected:
        iterator_type _M_current;
    };

    template <typename _Iterator>
    ustl::diff_t
    operator-(normal_iterator<_Iterator> const &__l,
              normal_iterator<_Iterator> const &__r)
    {
        ustl::diff_t __dis = 0;
        normal_iterator<_Iterator> __tmp = __r;
        for (; __tmp != __l; ++__dis, (void)++__tmp)
            ;
        return __dis;
    }

    template <typename _Iterator>
    bool
    operator==(normal_iterator<_Iterator> const &__l,
               normal_iterator<_Iterator> const &__r)
    {
        return __l.base_iterator() == __r.base_iterator();
    }

    template <typename _Iterator>
    bool
    operator!=(normal_iterator<_Iterator> const &__l,
               normal_iterator<_Iterator> const &__r)
    {
        return __l.base_iterator() != __r.base_iterator();
    }

}
// namespace ustl

#endif