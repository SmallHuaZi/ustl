#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_ALLOCATOR_TRAIT_HPP__
#define __USTL_CORE_INTERNAL_TYPETRAITS_ALLOCATOR_TRAIT_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace type_traits 
{
    
    template <typename Allocator>
    struct AllocatorTrait
    {
        USTL_GENERAL_ASSOCIATION_TYPE(AllocatorTrait);

        typedef Allocator allocator_type;
        typedef typename allocator_type::value_type       value_type;
        typedef typename allocator_type::pointer          pointer;
        typedef typename allocator_type::reference        reference;
        typedef typename allocator_type::const_pointer    const_pointer;
        typedef typename allocator_type::const_reference  const_reference;

        template <typename T>
        using rebind_t = typename allocator_type::rebind<T>::type;

    public:
        static pointer
        allocate(allocator_type &alloc, size_t count)
        { return alloc.allocate(count); }

        static void
        deallocate(allocator_type &alloc, pointer scope)
        { return alloc.deallocate(scope); }

        template <typename T, typename... Args>
        static T *
        construct(T *obj, Args&& ...args)
        { return new (obj) T(forward<Args>(args)...); }

        template <typename _Tp>
        static void
        destory(_Tp *obj) USTL_NOEXCEPT
        { obj->~_Tp(); }

    private:
        AllocatorTrait() = delete;
        AllocatorTrait(Self &&) = delete;
        AllocatorTrait(ConstRef) = delete;
        ~AllocatorTrait() = delete;
    };

} // namespace ustl::core::internal::type_traits
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif