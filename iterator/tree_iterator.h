#ifndef __tree_iterator_h
#define __tree_iterator_h

#include "include/config.h"
#include "container/tree_basic.h"

namespace ustl
{
    struct tree_node_basic;

    struct tree_iterator_basic
    {
        typedef     tree_iterator_basic       _Self;
        typedef     ustl::diff_t              difference_type;


        _Self &
        operator++() ustl_cpp_noexcept;

        _Self &
        operator--() ustl_cpp_noexcept;

        _Self 
        operator++(int) ustl_cpp_noexcept;

        _Self
        operator--(int) ustl_cpp_noexcept;

        _Self
        operator+(difference_type   __step) ustl_cpp_noexcept;

        _Self
        operator-(difference_type   __step) ustl_cpp_noexcept;


        tree_iterator_basic() = default;

        tree_iterator_basic(tree_node_basic *__p)
            : _M_data(__p)
        {}

        tree_iterator_basic(tree_iterator_basic const &__other)
            : _M_data(__other._M_data)
        {}

        tree_iterator_basic(tree_iterator_basic &&__rval)
            : _M_data(__rval._M_data)
        { __rval._M_data = 0; }



        tree_node_basic     *_M_data;
    }; 


    inline tree_iterator_basic &
    tree_iterator_basic::
        operator++() ustl_cpp_noexcept
    {
        _M_data = _tree_increment(_M_data);
        return  *this;
    }


    inline tree_iterator_basic &
    tree_iterator_basic::
        operator--() ustl_cpp_noexcept
    {
        _M_data = _tree_decrement(_M_data);
        return  *this;
    }


    inline tree_iterator_basic
    tree_iterator_basic::
        operator++(int) ustl_cpp_noexcept
    {
        _Self   __tmp(*this);
        _M_data = _tree_increment(_M_data);
        return  __tmp;
    }


    inline tree_iterator_basic
    tree_iterator_basic::
        operator--(int) ustl_cpp_noexcept
    {
        _Self   __tmp(*this);
        _M_data = _tree_decrement(_M_data);
        return  __tmp;
    }


    inline tree_iterator_basic
    tree_iterator_basic::
        operator-(difference_type   __step) ustl_cpp_noexcept
    {
        _Self   __tmp(*this);
        for(; __step && 0 < __step; --__step)
            __tmp._M_data = _tree_increment(__tmp._M_data);
        if(0 > __step)
            __tmp + (-__step);
        return  __tmp;
    }


    inline tree_iterator_basic
    tree_iterator_basic::
        operator+(difference_type   __step) ustl_cpp_noexcept
    {
        _Self   __tmp(*this);
        for(; __step && 0 < __step; --__step)
            __tmp._M_data = _tree_decrement(__tmp._M_data);
        if(0 > __step)
            __tmp - (-__step);
        return  __tmp;
    }


    static inline bool
    operator==(tree_iterator_basic const &__l, tree_iterator_basic const &__r) ustl_cpp_noexcept
    { return    __l._M_data == __r._M_data; }
    

    static inline bool
    operator!=(tree_iterator_basic const &__l, tree_iterator_basic const &__r) ustl_cpp_noexcept
    { return    __l._M_data != __r._M_data; }


    static inline ustl::diff_t
    operator-(tree_iterator_basic __last, tree_iterator_basic __first) ustl_cpp_noexcept
    {
        ustl::diff_t    __ret = 0;
        for(; __first != __last; ++__last)
            ++__ret;
        return  __ret;
    }



} // namespace ustl



#endif