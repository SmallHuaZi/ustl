
#ifndef __vector_h
#define __vector_h

#include "algorithm.h"
#include "memory.h"

namespace ustl
{
    template <typename _Tp, typename _Alloc>
    struct _vec_impl
        : allocate_traits<_Alloc>::allocator_type
    {
        typedef _Tp *pointer;
        typedef _Tp &reference;

        size_t
        _M_element_count()
        {
            return _M_stroge - _M_begin;
        }

        void
        _M_copy_data(_vec_impl &__other)
        {
            _M_begin = __other._M_begin;
            _M_end = __other._M_end;
            _M_stroge = __other._M_stroge;
        }

        void
        _M_swap(_vec_impl &__other)
        {
            _vec_impl __tmp{*this};
            _M_copy_data(__other);
            __other._M_copy_data(__tmp);
        }

        void
        _M_amend(pointer __begin,
                 size_t __size,
                 size_t __capacity)
        {
            _M_begin = __begin;
            _M_end = __begin + __capacity;
            _M_stroge = __begin + __size;
        }

        _vec_impl() = default;

        pointer _M_begin;
        pointer _M_end;
        pointer _M_stroge;
    };

    template <typename _Tp>
    struct _vector_iterator
    {
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _vector_iterator _Self;

        pointer
        operator->()
        {
            return _M_data_ptr;
        }

        reference
        operator*()
        {
            return *_M_data_ptr;
        }

        _Self
        operator++()
        {
            ++_M_data_ptr;
            return *this;
        }

        _Self
        operator--()
        {
            --_M_data_ptr;
            return *this;
        }

        _Self
        operator++(int)
        {
            pointer __ret = _M_data_ptr++;
            return _Self(__ret);
        }

        _Self
        operator--(int)
        {
            pointer __ret = _M_data_ptr--;
            return _Self(__ret);
        }

        friend bool
        operator!=(_Self __l, _Self __r)
        {
            return __l._M_data_ptr != __r._M_data_ptr;
        }

        friend bool
        operator==(_Self __l, _Self __r)
        {
            return __l._M_data_ptr == __r._M_data_ptr;
        }

        _vector_iterator() = default;

        _vector_iterator(pointer __p)
            : _M_data_ptr(__p) {}

        pointer _M_data_ptr;
    };

    template <typename _Tp>
    struct _vector_const_iterator
    {
        typedef _Tp const *pointer;
        typedef _Tp const &reference;
        typedef _vector_const_iterator _Self;

        pointer
        operator->()
        {
            return _M_data_ptr;
        }

        reference
        operator*()
        {
            return *_M_data_ptr;
        }

        _Self
        operator++()
        {
            ++_M_data_ptr;
            return *this;
        }

        _Self
        operator--()
        {
            --_M_data_ptr;
            return *this;
        }

        _Self
        operator++(int)
        {
            pointer __ret = _M_data_ptr++;
            return _Self(__ret);
        }

        _Self
        operator--(int)
        {
            pointer __ret = _M_data_ptr--;
            return _Self(__ret);
        }

        friend bool
        operator!=(_Self __l, _Self __r)
        {
            return __l._M_data_ptr != __r._M_data_ptr;
        }

        friend bool
        operator==(_Self __l, _Self __r)
        {
            return __l._M_data_ptr == __r._M_data_ptr;
        }

        _vector_const_iterator() = default;

        _vector_const_iterator(_vector_iterator __itr)
            : _M_data_ptr(__itr._M_data_ptr) {}

        _vector_const_iterator(pointer __p)
            : _M_data_ptr(__p) {}

        pointer _M_data_ptr;
    };

    template <typename _Tp, typename _Alloc = ustl::allocator<_Tp>>
    class vector
    {
    public:
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;
        typedef diff_t difference_type;
        typedef size_t size_type;

        typedef _Alloc allocator_type;
        typedef _vector_iterator<_Tp> iterator;
        typedef _vector_const_iterator<_Tp> const_iterator;

        typedef allocate_traits<_Alloc> _Tp_alloc_traits;

    private:
        bool
        _M_check_overflow(size_t __idx)
        {
            return __idx < size();
        }

        allocator_type &
        _M_get_allocator()
        {
            return _M_data_plus;
        }

        pointer
        _M_allocate(size_t __n)
        {
            return _Tp_alloc_traits::allocate(_M_get_allocator(), __n);
        }

        void
        _M_deallocate()
        {
            _Tp_alloc_traits::deallocate(_M_get_allocator(),
                                         _M_data_plus->_M_begin,
                                         _M_data_plus->_M_end - _M_data_plus->_M_begin);
        }

        void _M_default_append(size_type); // append element on default state

        void _M_fll_assgin(size_type, value_type const &);
        void _M_fill_insert(const_iterator, size_type, value_type const &);

        void _M_insert_rval(iterator, value_type const &);                        // insert rvalue
        template <typename... _Args>                                              //
        void _M_insert_aux(iterator, _Args &&...);                                // normal insert
        template <typename _ForwardIterator>                                      //
        void _M_range_insert(const_iterator, _ForwardIterator, _ForwardIterator); // range [__first, __last) insert
        template <typename... _Args>                                              //
        void _M_realloc_insert(const_iterator, _Args &&...);                      // realloc memory and insert

        void _M_erase(iterator);
        void _M_erase(iterator, iterator);

    public:
        vector()
        {
            _M_data_plus._M_amend(_M_alloc_block(1), 0, 1);
        }

    public:
        template <typename... _Args>
        iterator insert(iterator, _Args &&...);
        iterator insert(iterator, value_type const &);

        void push_back(value_type const &);
        void push_front(value_type const &);
        void push_back(iterator);
        void push_front(iterator);

        template <typename... _Args>
        void emplace(_Args &&...);
        template <typename... _Args>
        void emplace_back(_Args &&...);
        template <typename... _Args>
        void emplace_front(_Args &&...);

        iterator erase(iterator);
        iterator erase(value_type const &);

        void remove(iterator);
        template <typename _Predicate>
        void remove_if(_Predicate);

        template <typename _Itr>
        void assign(_Itr, _Itr);

        void clear();

        bool empty() ustl_cpp_noexcept;
        bool empty() const ustl_cpp_noexcept;

        size_t size() ustl_cpp_noexcept;
        size_t size() const ustl_cpp_noexcept;

        size_t capacity() ustl_cpp_noexcept;
        size_t capacity() const ustl_cpp_noexcept;

        iterator begin() ustl_cpp_noexcept;
        iterator end() ustl_cpp_noexcept;
        const_iterator cbegin() ustl_cpp_noexcept;
        const_iterator cend() ustl_cpp_noexcept;

        const_iterator begin() const ustl_cpp_noexcept;
        const_iterator end() const ustl_cpp_noexcept;
        const_iterator cbegin() const ustl_cpp_noexcept;
        const_iterator cend() const ustl_cpp_noexcept;

        reference operator[](size_t);
        void operator=(vector const &);

    private:
        _vec_impl<_Tp, _Alloc> _M_data_plus;
    };

    template <typename _Tp, typename _Alloc>
    bool
    vector<_Tp, _Alloc>::
        empty() ustl_cpp_noexcept
    {
        return _M_data_plus._M_begin == _M_data_plus._M_stroge;
    }

    template <typename _Tp, typename _Alloc>
    bool
    vector<_Tp, _Alloc>::
        empty() const ustl_cpp_noexcept
    {
        return _M_data_plus._M_begin == _M_data_plus._M_stroge;
    }

    template <typename _Tp, typename _Alloc>
    size_t
    vector<_Tp, _Alloc>::
        size() ustl_cpp_noexcept
    {
        return _M_data_plus._M_element_count();
    }

    template <typename _Tp, typename _Alloc>
    size_t
    vector<_Tp, _Alloc>::
        size() const ustl_cpp_noexcept
    {
        return _M_data_plus._M_element_count();
    }

    template <typename _Tp, typename _Alloc>
    size_t
    vector<_Tp, _Alloc>::
        capacity() ustl_cpp_noexcept
    {
        return _M_data_plus._M_end - _M_data_plus._M_begin;
    }

    template <typename _Tp, typename _Alloc>
    size_t
    vector<_Tp, _Alloc>::
        capacity() const ustl_cpp_noexcept
    {
        return _M_data_plus._M_end - _M_data_plus._M_begin;
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
        begin() ustl_cpp_noexcept
    {
        return iterator(_M_data_plus._M_begin);
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_iterator
    vector<_Tp, _Alloc>::
        begin() const ustl_cpp_noexcept
    {
        return const_iterator(_M_data_plus._M_begin);
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
        end() ustl_cpp_noexcept
    {
        return iterator(_M_data_plus._M_end);
    }

    template <typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_iterator
    vector<_Tp, _Alloc>::
        end() const ustl_cpp_noexcept
    {
        return const_iterator(_M_data_plus._M_end);
    }

    template <typename _Tp, typename _Alloc>
    _Tp &
    vector<_Tp, _Alloc>::
    operator[](size_t __idx)
    {
        if (_M_check_overflow(__idx))
            return *(_M_data_plus._M_begin + __idx);
        __throw_index_outof();
    }
}

/**
 * vector interanl member fucntion implement
 */

namespace ustl
{
    template <typename _Tp, typename _Alloc>
    template <typename... _Args>
    void
    vector<_Tp, _Alloc>::
        _M_insert_aux(iterator __pos,
                      _Args &&...__val)
    {
        iterator __last = end();
        ++_M_data_plus._M_stroge;
        ustl::relocate_back(__pos, __last,
                            _M_data_plus->_M_stroge,
                            _M_get_allocator());
        _Tp_alloc_traits::construct(
            _M_get_allocator(),
            &*__pos, ustl::forward<_Args &&>(__val)...);
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        _M_insert_rval(iterator __pos,
                       value_type const &__rval)
    {
        iterator __last = end();
        ++_M_data_plus._M_stroge;
        ustl::relocate_back(__pos, __last,
                            _M_data_plus->_M_stroge,
                            _M_get_allocator());
        _Tp_alloc_traits::construct(
            _M_get_allocator(),
            &*__pos, ustl::move(__rval));
    }

    template <typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
        _M_fill_insert(const_iterator __pos,
                       size_type __n,
                       value_type const &__val)
    {
        if (_M_data_plus->_M_end - _M_data_plus->_M_stroge >= __n)
        {
        }
        else
        {
        }
    }
}

#endif