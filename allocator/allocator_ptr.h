#ifndef __ustl_allocator_pointer_h
#define __ustl_allocator_pointer_h

#include "type/allocate_traits.h"

namespace ustl
{
    // RAII
    template <typename _Alloc>
    struct allocator_ptr
    {
        typedef     typename ustl::allocate_traits<_Alloc>::pointer             pointer;
        typedef     typename ustl::allocate_traits<_Alloc>::value_type          value_type;


    public:
        allocator_ptr(_Alloc & __alloc, pointer __p)
            : _M_allocator(__alloc), _M_data_pointer(__p)
        {}

        ~allocator_ptr()
        { allocate_traits<_Alloc>::deallocate(_M_allocator, _M_data_pointer, sizeof(value_type)); }

    
    protected:
        pointer         _M_data_pointer;
        _Alloc          _M_allocator;
    };


    
} // namespace ustl



#endif