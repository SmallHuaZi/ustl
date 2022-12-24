#ifndef __ustl_shared_pointer_counter_h
#define __ustl_shared_pointer_counter_h

#include "conc/atomic_t.h"
#include "allocator/memory.h"
#include "type/allocate_traits.h"

namespace ustl
{
    /// shared_ptr and weak_ptr using @class sp_counted ponter
    /// to operator derived class
    class sp_counted
    {
        template <typename _Tp>
        friend class shared_ptr;


    public:
        void
        _M_add_ref_counter() ustl_cpp_noexcept
        { ++_M_shared_counter; }

        void
        _M_add_weak_counter() ustl_cpp_noexcept
        { ++_M_weak_counter; }

        size_t
        _M_using_counter() ustl_cpp_noexcept
        { return    _M_shared_counter; }

        void
        _M_shared_release();

        void
        _M_weak_release();


    protected:
        virtual void
        _M_dispose() __pure_vritual; // destory data pointer

        virtual void
        _M_destory() __pure_vritual; // destory this pointer

    
    public:
        sp_counted()
            : _M_shared_counter(1), _M_weak_counter(1)
        {}

        virtual 
        ~sp_counted()
        { }


    private:
        asize_t         _M_shared_counter;      // shared_ptr promise data exist
        asize_t         _M_weak_counter;        // weak ptr promise had 
    }; 


    void
    sp_counted::
        _M_shared_release()
    {
        if(0 == --_M_shared_counter)
        {
            _M_dispose();
        /// 必须等 RPTR 释放了才能销毁自己
        __USTL_MEMORY_BARRIER_ALL
            if(0 == --_M_weak_counter)
                _M_destory();
        }
    }


    void
    sp_counted::
        _M_weak_release()
    {
        __USTL_MEMORY_BARRIER_ALL
        if(0 == --_M_weak_counter)
            _M_destory();
    }


} // namespace ustl


#endif