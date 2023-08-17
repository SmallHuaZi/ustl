#ifndef __USTL_STD_INTERNAL_MEMORY_ALLOCATOR_HPP__
#define __USTL_STD_INTERNAL_MEMORY_ALLOCATOR_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl
{
namespace std
{
namespace internal
{
namespace scope
{

    template <typename Tp, typename... Options>
    class Allocator
    {
        USTL_GENERAL_ASSOCIATION_TYPE(Allocator);

    public:
        typedef Tp              value_type;
        typedef Tp *            pointer;
        typedef Tp &            reference;
        typedef Tp const *      const_pointer;
        typedef Tp const &      const_reference;

        template <typename Up, typename... OtherOptions>
        struct rebind
        { typedef Allocator<Up, OtherOptions...>     type; };
    };
    
    
} // namespace ustl::std::internal::scope
} // namespace ustl::std::internal
} // namespace ustl::std
} // namespace ustl



#endif