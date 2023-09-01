#ifndef __UNIT_TEST__
#include <ustl/core/allocator> 
#endif


using   __USTL size_t;


struct buf_block 
{
    size_t      _M_mem_size; 
    union {
        char    _M_user_data[1];
    };
};


struct block_list 
{
    struct block_list   *_M_last;
    struct block_list   *_M_next;

    struct buf_block     _M_block;
};


class allocator
{
public:
    void *
    allocate_raw(size_t __ns);

    void *
    allocate_init(size_t __ns);

    void
    deallocate(void *__ptr);
private:
};


static inline constexpr size_t
align_upper(size_t __v, size_t __a)
{ return  (__v + __a) & ~(__a); }


static inline constexpr size_t
align_lower(size_t __v, size_t __a)
{ return  __v & ~(--__a); }


__EXTERNAL void *
__CORE __ustl_init_mem_allocate(size_t __s)
{
    return 0;
}


__EXTERNAL void *
__CORE __ustl_raw_mem_allocate(size_t __s)
{
    return 0;
}


__EXTERNAL void
__CORE __ustl_mem_deallocate(void *__data, size_t __s)
{
}