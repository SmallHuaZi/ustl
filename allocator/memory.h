#include <malloc.h>
#include <atomic>
#include <mutex>
#include "ustl.h"
#include "exception.h"
#include "move.h"
#include "config.h"

#ifndef __memory_h
#define __memory_h

#if defined(platform) && platform == 64UL
#define MEM_MAP_MAXSIZE 0x7fffffffffffffffUL
#else
#define MEM_MAP_MAXSIZE 0x7fffffffUL
#endif

#define __default_obj_count 20

namespace ustl
{
    /**
     * @brief using embedded pointer
     *      Use base classes to store static data and avoid
     *      spinning out class templates to instantiate multiple copies of static data
     */

    constexpr size_t
    align_extend(size_t __s, size_t __a);

    constexpr size_t
    align_compress(size_t __s, size_t __a);

    class allocator_basic
    {
    protected:
        enum
        {
            __ALIGNMENT = 0x10UL,
            __MAX_BYTES = 0x100UL,
            __TABLE_SIZE = __MAX_BYTES / __ALIGNMENT
        };

        /**
         * @brief enbedded pointer
         * @memberof _M_next : point next free memory area of sizeof(type)
         * @memberof _M_client_data : point data of client, example : container element
         * @if client data is exist :
         *      then _M_next is invaild
         * @else
         *      then _M_client_data is a pointer and it point type data
         */
        union obj
        {
            obj *_M_next;
            byte _M_client_data[0];
        };

        typedef obj *obj_ptr;
        typedef diff_t difference_type;

    private:
        static inline obj_ptr _S_free_list[__TABLE_SIZE];
        static inline byte *_S_free_start;
        static inline byte *_S_free_end;
        static inline size_t _S_heap_size;

    public:
        /**
         * @param __bs
         *      user must provide it align by @enum __ALIGNMENT
         */
        obj_ptr *
        _M_get_free_list(size_t __bs)
        {
            return _S_free_list + __bs / __ALIGNMENT - 1;
        }

        byte *_M_refill(size_t);

        byte *_M_alloc_chuck(size_t, size_t *);
    };

    /// @brief fill memory of alignment, initialization the new free list
    /// @param __s reqeust byte size
    byte *
    allocator_basic::_M_refill(size_t __s)
    {
        size_t __count = __default_obj_count;
        byte *__chuck = _M_alloc_chuck(__s, &__count);
        obj_ptr *__list = _M_get_free_list(__s);
        obj_ptr __cur = (obj_ptr)((byte *)__chuck + __s), __next;
        *__list = __cur;
        size_t __i{0};
        for (; __i < __count - 2; ++__i)
        {
            /** cast to byteptr and add size of block */
            __next = (obj_ptr)((byte *)__cur + __s);
            __cur->_M_next = __next;
            __cur = __next;
        }
        __cur[__i]._M_next = 0;
        return __chuck;
    }

    /// @brief alloc memory for ouser
    /// @param __s
    /// @param __count
    /// @return return a pointer and it point that allocament memory
    byte *
    allocator_basic::_M_alloc_chuck(size_t __s,
                                    size_t *__count)
    {
        byte *__ret;
        size_t __alloc_size = __s * __default_obj_count;
        difference_type __pool_size = _S_free_end - _S_free_start;
        // free size > request size
        if (__pool_size >= __alloc_size)
        {
            __ret = _S_free_start;
            _S_free_start += __alloc_size;
            return __ret;
        }
        /// @if default_block_count * sizeof(type) >= size of residue memory &&
        ///     sizeof(type) <= size of residue memory
        /// @return all of residue memory
        else if (__s <= __pool_size)
        {
            *__count = __alloc_size / __s;
            __alloc_size = (*__count) * __s;
            __ret = _S_free_start;
            _S_free_start += __alloc_size;
            return __ret;
        }
        else
        {
            __alloc_size = __alloc_size << 1 + align_extend(_S_heap_size >> 4, 16);
            if (__pool_size > 0)
            {
                /** recycle last free memory */
                obj_ptr *__plist = _M_get_free_list(__pool_size);
                ((obj_ptr)_S_free_start)->_M_next = (*__plist)->_M_next;
                (*__plist)->_M_next = (obj_ptr)_S_free_start;

                _S_free_start = (byte *)malloc(__alloc_size);
                if (!_S_free_start)
                {
                    /**
                     * @brief
                     * @if alloc failure
                     *      just find big chuck that size of element > __s
                     * @if find failure
                     *      throws bad_alloc
                     */
                    size_t __i;
                    obj_ptr *__list, __had_list;
                    for (__i = __s; __i <= __MAX_BYTES; __i += __ALIGNMENT)
                    {
                        __list = _S_free_list + __s / __ALIGNMENT;
                        __had_list = *__list;
                        if (__had_list)
                        {
                            _S_free_start = (byte *)__had_list;
                            _S_free_end = _S_free_start + __i;
                            return _M_alloc_chuck(__s, __count);
                        }
                    }
                    /** memory alloc failure, throws a exception !  */
                    __throw_bad_alloc();
                }
                _S_heap_size += __alloc_size;
                _S_free_end = _S_free_start + __alloc_size;
                return _M_alloc_chuck(__s, __count);
            }
        }
        return __ret;
    }

    template <typename _Tp>
    class allocator
        : public allocator_basic
    {
    public:
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef const _Tp *const_pointer;
        typedef _Tp &reference;
        typedef const _Tp &const_reference;

    private:
        static inline std::mutex _S_mutex;

    public:
        pointer allocate(size_t);

        void deallocate(void_ptr, size_t);

        template <typename _OTp>
        struct rebind
        {
            using other = allocator<_OTp>;
        };

        template <typename... _Args>
        pointer
        construct(void_ptr __p, _Args &&...__a)
        {
            return new (__p) _Tp(forward<_Args>(__a)...);
        }

        void
        destory(value_type *__p)
        {
            __p->~_Tp();
        }

        constexpr size_t
        max_size()
        {
            return MEM_MAP_MAXSIZE / sizeof(_Tp);
        }
    };

    /// @brief
    /// @tparam _Tp type
    /// @param __n request obj count
    /// @return
    template <typename _Tp>
    typename allocator<_Tp>::pointer
    allocator<_Tp>::allocate(size_t __n)
    {
        pointer __ret = 0;
        if (__n > 0)
        {
            const size_t __alloc_size = __n * sizeof(_Tp);
            if (__alloc_size > __MAX_BYTES)
                return static_cast<pointer>(malloc(__alloc_size));
            obj_ptr *__list = _M_get_free_list(__alloc_size);
            obj_ptr __pobj = *__list;
            /** lock, adapt multithread envirment */
            std::unique_lock __tmp_mutex(_S_mutex);
            if (!__pobj)
                __pobj = (obj_ptr)_M_refill(align_compress(__alloc_size, alignment_criteria));
            else
                *__list = __pobj->_M_next;
            if (!__pobj)
                __throw_bad_alloc();
        }
        return static_cast<pointer>(__ret);
    }

    template <typename _Tp>
    void
    allocator<_Tp>::deallocate(void_ptr __p, size_t __n)
    {
        const size_t __recycle_size = __n * sizeof(_Tp);
        if (__p && __n)
        {
            if (__recycle_size > __MAX_BYTES)
            {
                free(__p);
                return;
            }
            size_t __i{0};
            obj_ptr *__list = _M_get_free_list(__recycle_size);
            obj_ptr __new_head = static_cast<obj_ptr>(__p);
            std::unique_lock __tmp_mutex(_S_mutex);
            __new_head->_M_next = *__list;
            *__list = __new_head;
        }
    }

    constexpr size_t
    align_extend(size_t __s, size_t __a)
    {
        return (__s + --__a) & ~(__a);
    }

    constexpr size_t
    align_compress(size_t __s, size_t __a)
    {
        return __s & ~(--__a);
    }
}

#endif