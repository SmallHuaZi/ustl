#include "allocator/memory.h"
#include "include/ustl_exception.h"

namespace ustl
{
    byte *
    allocator_basic::
    _M_refill(size_t __s)
    {
        size_t __count = size_t(__DEFAULT_OBJECT_NUMBER);
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

    byte *
    allocator_basic::
        _M_alloc_chuck(size_t __s, size_t *__count)
    {
        byte *__ret;
        size_t __alloc_size = __s * size_t(__DEFAULT_OBJECT_NUMBER);
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
                ((obj_ptr)_S_free_start)->_M_next = *__plist;
                *__plist = (obj_ptr)_S_free_start;
            }

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
                for (__i = __s; __i <= size_t(__MAX_BYTES); __i += size_t(__ALIGNMENT))
                {
                    __list = _S_free_list + __s / size_t(__ALIGNMENT);
                    __had_list = *__list;
                    if (__had_list)
                    {
                        _S_free_start = (byte *)__had_list;
                        _S_free_end = _S_free_start + __i;
                        return _M_alloc_chuck(__s, __count);
                    }
                }
                /** memory alloc failure, throws a exception !  */
                __ustl_throw_bad_alloc();
            }
            _S_heap_size += __alloc_size;
            _S_free_end = _S_free_start + __alloc_size;
            return _M_alloc_chuck(__s, __count);
        }
        return __ret;
    }

    void *
    allocator_basic::
        _M_allocate(size_t __number, size_t const __size)
    {
        void * __ret = 0;
        if(__number > 0)
        {
            size_t const __alloc_size = __number * __size;
            if(__alloc_size > size_t(__MAX_BYTES))
                return  malloc(__alloc_size);
            
            obj_ptr *__list = _M_get_free_list(__alloc_size);
            obj_ptr  __obj = *__list;

            std::unique_lock    __tmp_mutex(_S_mutex);

            if(0 == __obj)
                __ret = _M_refill(align_extend(__alloc_size, alignment_criteria));
            else
            {
                *__list = __obj->_M_next;
                __ret = __obj;
            }

            if(0 == __ret)
                __ustl_throw_bad_alloc("allocator_basic::_M_allocate: allocate memory excepton\n");
        }
        return  __ret;
    }

    void
    allocator_basic::
        _M_deallocate(void *__p, size_t __number, size_t const __size)
    {
        size_t const __recycle_size = __size * __number;
        if(0 != __p && 0 != __number)
        {
            if(size_t(__MAX_BYTES) < __recycle_size)
                free(__p);
            else
            {
                size_t  __i = 0;
                obj_ptr *__list = _M_get_free_list(__recycle_size);
                obj_ptr __new_head = static_cast<obj_ptr>(__p);

                std::unique_lock __tmp_mutex(_S_mutex);
                __new_head->_M_next = *__list;
                *__list = __new_head;
            }
        }
    }


} // namespace ustl