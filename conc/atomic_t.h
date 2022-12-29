#ifndef __USTL_ATOMIC_T_H
#define __USTL_ATOMIC_T_H

#include "include/config.h"
#include "conc/atomic.h"

namespace ustl
{
    namespace conceal
    {
        template<typename _Tp>
        class atomic_type
        {
        public:
            _Tp
            operator+(_Tp const __n) ustl_cpp_noexcept
            { return    _M_value_field + _Tp(__n); }


            _Tp
            operator-(_Tp const __n) ustl_cpp_noexcept
            { return    _M_value_field - _Tp(__n); }


            _Tp
            operator*(_Tp const __n) ustl_cpp_noexcept
            { return    _M_value_field * _Tp(__n); }


            _Tp
            operator/(_Tp const __n) ustl_cpp_noexcept
            { return    _M_value_field / __n; }


            _Tp
            operator%(_Tp const __n) ustl_cpp_noexcept
            { return    _M_value_field % __n; }


            atomic_type &
            operator+=(_Tp const __n) ustl_cpp_noexcept
            { return    atomic_add(&_M_value_field, __n), *this; }


            atomic_type &
            operator-=(_Tp const __n) ustl_cpp_noexcept
            { return    atomic_sub(&_M_value_field, __n), *this;}


            atomic_type &
            operator*=(_Tp const __n) ustl_cpp_noexcept
            { return    atomic_mul(&_M_value_field, __n), *this; }


            atomic_type &
            operator/=(_Tp const __n) ustl_cpp_noexcept
            { return    atomic_div(&_M_value_field, __n), *this; }


            atomic_type &
            operator=(_Tp const __n) ustl_cpp_noexcept
            { return    atomic_assign(&_M_value_field, __n), *this; }


            atomic_type &
            operator++() ustl_cpp_noexcept
            { return    atomic_add(&_M_value_field, _Tp(1)), *this; }

            
            atomic_type &
            operator--() ustl_cpp_noexcept
            { return    atomic_add(&_M_value_field, _Tp(-1)), *this; }


            operator _Tp() ustl_cpp_noexcept
            { return    atomic_load(&_M_value_field); }


        public:
            atomic_type() = default;

            atomic_type(_Tp const __val)
                : _M_value_field(__val)
            {}

            atomic_type(atomic_type const &__other)
                : _M_value_field(__other._M_vale_field)
            {}


        private:
            _Tp          _M_value_field;
        };



        template<>
        class atomic_type<bool>
        {
            atomic_type &
            operator=(bool const __val) ustl_cpp_noexcept
            { return    atomic_assign(&_M_value_field, __val), *this; }


            operator bool()
            { return    _M_value_field; }


        public:
            atomic_type() = default;

            atomic_type(bool const __val)
                : _M_value_field(__val)
            {}

            atomic_type(atomic_type const &__val)
                : _M_value_field(__val._M_value_field)
            {}

        private:    
            bool        _M_value_field;
        };       

    } // namespace ustl::conceal


    typedef     conceal::atomic_type<size_t>         asize_t;
    typedef     conceal::atomic_type<diff_t>         adiff_t;
    typedef     conceal::atomic_type<bool>           abool_t;

} // namespace ustl


#endif