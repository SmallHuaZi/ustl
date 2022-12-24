#ifndef __ustl_shared_element_ptr_h
#define __ustl_shared_element_ptr_h

#include "include/config.h"
#include "type/allocate_traits.h"
#include "allocator/sp_counted.h"

/**
 * 时间问题，设计过于粗糙
*/

namespace ustl
{
    template <typename _Tp>
    struct shared_count
        : sp_counted
    {
    public:
        virtual void
        _M_destory() override
        { delete    this; }

        virtual void
        _M_dispose() override
        { delete    _M_data_pointer; } 

        _Tp *
        _M_get() ustl_cpp_noexcept
        { return    _M_data_pointer; }


    public:
        shared_count()
            : _M_data_pointer(0)
        {}

        shared_count(_Tp *__p)
            : _M_data_pointer(__p)
        {}

        virtual
        ~shared_count()
        { _M_shared_release(); }

    
    private:
        _Tp             *_M_data_pointer;
    };



    template <typename _Tp, typename _Deleter, typename _Alloc>
    struct shared_count_deleter
        : sp_counted
    {
        typedef     __alloc_rebind_t<_Alloc, shared_count_deleter>          _Self_allocator_type;
        typedef     allocate_traits<_Self_allocator_type>                         _Allocate_traits;

        struct _Sp_helper
            : _Deleter, 
              _Self_allocator_type
        {
            _Deleter &
            _M_get_del()
            { return    *this; }

            _Self_allocator_type &
            _M_get_alloc()
            { return    *this; }

            _Sp_helper(_Deleter __del)
                : _Deleter(__del)
            {}

            _Tp             *_M_data_pointer;
        };


    public:
        virtual void
        _M_dispose() override
        { _M_Impl._M_get_del()(_M_Impl._M_data_pointer); }

        virtual void
        _M_destory() override
        { _Allocate_traits::deallocate(_M_Impl._M_get_alloc(), this, sizeof(*this));  }

        _Tp *
        _M_get() ustl_cpp_noexcept
        { return    _M_Impl._M_data_pointer; }

    
    public:
        shared_count_deleter(_Tp *__p)
        { _M_Impl._M_data_pointer = __p; }

        shared_count_deleter(_Tp *__p, _Deleter __del, _Alloc &__alloc)
            : _M_Impl(__del)
        { }

        virtual
        ~shared_count_deleter() ustl_cpp_noexcept
        { _M_shared_release(); }

    private:
        _Sp_helper          _M_Impl;
    };



    template <typename _Tp>
    class shared_ptr
    {
        typedef     _Tp                 element_type;
        typedef     _Tp *               element_ptr;
        typedef     _Tp &               element_ref;
        typedef     ustl::size_t        size_type;
        typedef     ustl::diff_t        difference_type;


    protected:
        typedef     ustl::allocator<_Tp>                            _Tp_allocator_type;
        typedef     ustl::allocate_traits<_Tp_allocator_type>       _Tp_allocate_traits;


    public:
        element_ref
        operator[](difference_type  __idx) ustl_cpp_noexcept
        { return    _M_actual_data[__idx]; }


        element_ptr
        operator->() ustl_cpp_noexcept
        { return    _M_actual_data; }


        element_ref
        operator*() ustl_cpp_noexcept
        { return    *_M_actual_data; }


        element_ptr
        operator+(difference_type __step) ustl_cpp_noexcept
        { return    _M_actual_data + __step; }


        element_ptr
        operator-(difference_type __step) ustl_cpp_noexcept
        { return    _M_actual_data - __step; }


        bool
        unique() const ustl_cpp_noexcept
        { return    1 == _M_reference->_M_shared_counter; }


        size_type
        use_count() const ustl_cpp_noexcept
        { return    _M_reference->_M_shared_counter; }


        element_ptr
        get() ustl_cpp_noexcept
        { return    _M_actual_data; }

        element_type const * 
        get() const ustl_cpp_noexcept
        { return    _M_actual_data; }


        explicit operator bool() const ustl_cpp_noexcept
        { return    0 == _M_actual_data; }

    
    public:
        shared_ptr &
        operator=(shared_ptr const &__lother) &;

        shared_ptr &
        operator=(shared_ptr &&__rother) &;

        // shared_ptr &
        // operator=(weak_ptr const &__wother) &;


    public:
        shared_ptr() = default;

        shared_ptr(element_ptr __p)
            : _M_actual_data(__p)
        { _M_reference = new shared_count(__p); }

        template <typename _Deleter, typename _Alloc>
        shared_ptr(element_ptr __p, _Deleter __del, _Alloc &__alloc)
            : _M_actual_data(__p)
        {
            typedef     shared_count_deleter<_Tp, _Deleter, _Alloc>         _Sp_type;
            typedef     typename allocate_traits<_Alloc>::template rebind_t<_Sp_type>                            
                        _Sp_allocator_type;
            typedef     allocate_traits<_Sp_allocator_type>             _Sp_allocate_traits;

            _Sp_allocator_type      __tmp;
            _Sp_type *__sp = _Sp_allocate_traits::allocate(__tmp, 1);
            _Sp_allocate_traits::construct(__tmp, __sp, __p, __del, __alloc);
            _M_reference = __sp;
        }

        ~shared_ptr()
        { _M_reference->~sp_counted(); }

    private:
        element_ptr          _M_actual_data;
        sp_counted          *_M_reference; 
    };


    template <typename _Tp>
    inline auto
    shared_ptr<_Tp>::
        operator=(shared_ptr const &__lother) & -> shared_ptr &
    {
        if(0 != __lother._M_reference)
            __lother._M_reference->_M_add_ref_counter();
        if(0 != _M_reference)
            _M_reference->_M_shared_release();
        _M_reference = __lother._M_reference;
        return  *this;
    }


    template <typename _Tp>
    inline auto
    shared_ptr<_Tp>::
        operator=(shared_ptr &&__lother) & -> shared_ptr &
    {
        if(0 != _M_reference)
            _M_reference->_M_shared_release();
        _M_reference = __lother._M_reference;
        return  *this;
    }

} // namespace ustl


#endif