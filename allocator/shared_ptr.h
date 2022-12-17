#ifndef __shared_pointer_h
#define __shared_pointer_h

#include "include/config.h"

namespace ustl
{
    
    template <typename _Tp>
    class shared_ptr
    {
        typedef     _Tp             value_type;
        typedef     _Tp *           pointer;
        typedef     _Tp &           reference;
        typedef     ustl::size_t    size_type;
        typedef     ustl::diff_t    difference_type;


        reference
        operator[](difference_type  __idx) ustl_cpp_noexcept
        { return    _M_data_plus[__idx]; }

        pointer
        operator->() ustl_cpp_noexcept
        { return    _M_data_plus; }

        pointer             _M_data_plus; 
        size_type           _M_reference_counter;
    };
} // namespace ustl


#endif