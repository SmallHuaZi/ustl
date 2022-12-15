#ifndef __allocate_type_h
#define __allocate_type_h

#include "include/config.h"

namespace ustl
{
    template <typename _Alloc>
    struct allocate_traits
    {
        typedef     _Alloc               allocator_type;
        typedef     ustl::diff_t         difference_type;

        typedef     typename _Alloc::value_type         value_type;
        typedef     typename _Alloc::pointer            pointer;
        typedef     typename _Alloc::reference          reference;
        typedef     typename _Alloc::const_reference    const_reference;
        typedef     typename _Alloc::const_pointer      const_pointer;


    public:
        template <typename _Tp>
        struct rebind
        { using other = typename allocator_type::template rebind<_Tp>::other; };


        template<typename _Tp>
        using   rebind_t = typename allocator_type::template rebind<_Tp>::other;


    public:
        static pointer
        allocate(allocator_type &__a, size_t __s)
        { return    __a.allocate(__s); }



        template <typename _Tp, typename... _Args>
        static _Tp *
        construct(allocator_type &__a, _Tp *__p, _Args &&...__args)
        { return    __a.construct(__p, ustl::forward(__args)...); }



        template <typename _OTp>
        static void
        destory(allocator_type &__a, _OTp __p)
        { __a.destory(__p); }



        static void
        deallocate(allocator_type &__a, void_ptr __p, size_t __s)
        { __a.deallocate(__p, __s); }



        static size_t
        max_size(allocator_type &__a)
        { return    __a.max_size(); }



    };
}

#endif