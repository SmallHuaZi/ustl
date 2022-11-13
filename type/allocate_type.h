#ifndef __allocate_type_h
#define __allocate_type_h

namespace ustl
{
    template <typename _Alloc>
    struct allocate_traits
    {
        using allocator_type = _Alloc;

        using value_type = typename _Alloc::value_type;
        using difference_type = typename _Alloc::difference_type;
        using reference = value_type &;
        using const_reference = value_type const &;
        using pointer = value_type *;
        using const_pointer = value_type const *;

        static pointer
        allocate(allocator_type &__a,
                 size_t __s)
        {
            return __a.allocate(__s);
        }

        template <typename _Tp, typename... _Args>
        static _Tp *
        construct(allocator_type &__a,
                  _Tp *__p, _Args &&...__args)
        {
            return __a.construct(__p, forward(__args)...);
        }

        template <typename _OTp>
        static void
        destory(allocator_type &__a,
                _OTp __p)
        {
            __a.destory(__p);
        }

        static void
        deallocate(allocator_type &__a,
                   void_ptr __p, size_t __s)
        {
            __a.deallocate(__p, __s);
        }

        static size_t
        max_size(allocator_type &__a)
        {
            return __a.max_size();
        }

        template <typename _Tp>
        struct rebind
        {
            using other = typename allocator_type::template rebind<_Tp>::other;
        };
    };
}

#endif