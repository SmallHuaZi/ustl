#ifndef __fwd_iterator_h
#define __fwd_iterator_h

namespace ustl
{

    template <typename _ForwardIterator>
    class fwd_iterator
    {
    public:
        typedef fwd_iterator _Self;
        typedef _ForwardIterator iterator_type;
        typedef ustl::itr_traits<_ForwardIterator> _iterator_traits;

        typedef typename _iterator_traits::iterator_tag iterator_tag;
        typedef typename _iterator_traits::value_type value_type;
        typedef typename _iterator_traits::pointer pointer;
        typedef typename _iterator_traits::reference reference;
        typedef typename _iterator_traits::const_pointer const_pointer;
        typedef typename _iterator_traits::const_reference const_reference;

        static_assert(ustl::is_same<iterator_tag, _forword_itertor>()() ||
                          ustl::is_same<iterator_tag, _bothway_itertor>()() ||
                          ustl::is_same<iterator_tag, _random_itertor>()(),
                      "template paramater::type _ForwardIterator is not forward iterator");

    public:
        _Self
        operator+(size_t __n) ustl_cpp_noexcept
        {
            iterator_type __tmp = _M_current;
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

        iterator_type
        base_iterator() ustl_cpp_noexcept
        {
            return _M_current;
        }

    public:
        fwd_iterator() = default;

        fwd_iterator(iterator_type __itr)
            : _M_current(__itr) {}

    protected:
        iterator_type _M_current;
    };

    template <typename _FwdIterator>
    bool
    operator==(fwd_iterator<_FwdIterator> const &__l,
               fwd_iterator<_FwdIterator> const &__r)
    {
        return __l.base_iterator() == __r.base_iterator();
    }

    template <typename _FwdIterator>
    bool
    operator!=(fwd_iterator<_FwdIterator> const &__l,
               fwd_iterator<_FwdIterator> const &__r)
    {
        return __l.base_iterator() != __r.base_iterator();
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

} // namespace ustl

#endif