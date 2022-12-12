#ifndef __memory_h
#define __memory_h

#include <malloc.h>
#include <atomic>
#include <mutex>

#include "include/config.h"
#include "tmp/move.h"
#include "allocator/memopt.h"


namespace ustl
{

    class allocator_basic
    {
    protected:

        enum    { __ALIGNMENT = 0x10UL };
        enum    { __MAX_BYTES = 0x100UL };
        enum    { __TABLE_SIZE = __MAX_BYTES / __ALIGNMENT };
        enum    { __DEFAULT_OBJECT_NUMBER = 0x14 };

        // embedded pointer
        union obj {
            obj     *_M_next;
            byte     _M_client_data[0];
        };

        typedef     obj *           obj_ptr;
        typedef     ustl::diff_t    difference_type;

    private:
        static inline byte         *_S_free_start;
        static inline byte         *_S_free_end;
        static inline size_t        _S_heap_size;
        static inline std::mutex    _S_mutex;
        static inline obj_ptr       _S_free_list[__TABLE_SIZE];

    public:
        static obj_ptr *
        _M_get_free_list(size_t __bs)
        { return _S_free_list + (__bs / (size_t(__ALIGNMENT - 1))); }        


        static byte *
        _M_refill(size_t);

        static byte *
        _M_alloc_chuck(size_t, size_t *);

        static void *
        _M_allocate(size_t __number, size_t const __size);

        static void
        _M_deallocate(void *__p, size_t __number, size_t const __size);
    };


    template <typename _Tp>
    class allocator
        : public allocator_basic
    {
#if defined(platform) && platform == 64UL 
        enum    { __MEMORY_MAPPING_SIZE = 0x7fffffffffffffffUL };
#else
        enum    { __MEMORY_MAPPING_SIZE = 0x7fffffffUL };
#endif

        typedef     allocator_basic     _Base_type;
    public:
        typedef     _Tp                 value_type;
        typedef     _Tp *               pointer;
        typedef     _Tp &               reference;
        typedef     _Tp const *         const_pointer;
        typedef     _Tp const &         const_reference;
        typedef     ustl::size_t        size_type;
        typedef     allocator           allocator_type;
        using       _Base_type::difference_type;


        template <typename _OTp>
        struct rebind
        { using other = allocator<_OTp>; };

    public:

        pointer 
        allocate(size_type __n)
        { return  static_cast<pointer>(_M_allocate(__n, sizeof(_Tp))); }


        void 
        deallocate(void_ptr __p, size_type __n) ustl_cpp_noexcept
        { _M_deallocate(__p, __n, sizeof(_Tp)); }


        template <typename _OTp, typename... _Args>
        _OTp *
        construct(_OTp *__p, _Args &&...__a)
        { return new (__p) _OTp(ustl::forward<_Args &&>(__a)...); }


        template <typename _OTp>
        void
        destory(_OTp *__p)
        { __p->~_OTp(); }


        constexpr size_type
        max_size()
        { return size_type(__MEMORY_MAPPING_SIZE) / sizeof(_Tp); }

    };

} // namespace ustl

#endif