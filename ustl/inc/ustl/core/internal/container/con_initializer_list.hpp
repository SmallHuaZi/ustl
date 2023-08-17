#ifndef __USTL_CORE_INTERNAL_CONTAINER_INITIALIZER_LIST_HPP__
#define __USTL_CORE_INTERNAL_CONTAINER_INITIALIZER_LIST_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace container
{

    template <typename _Tp>
    struct InitializerList
    {
        USTL_GENERAL_ASSOCIATION_TYPE(InitializerList);
        USTL_GENERAL_INTERFACE_ASSOCIATION_TYPE(_Tp);

        typedef pointer        iter_mut;
        typedef const_pointer  iter_const;

    public:
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        InitializerList(ConstRef other) USTL_NOEXCEPT
            : _M_scope(other._M_scope),
              _M_length(other._M_length)
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        iter_const
        begin() const USTL_NOEXCEPT
        { return  _M_scope; }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        iter_const
        end() const USTL_NOEXCEPT
        { return  _M_scope + _M_length; }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        size_type
        size() const USTL_NOEXCEPT
        { return  _M_length; }

    private:
        iter_const  _M_scope;
        size_type   _M_length;
    };
    
} // namespace ustl::core::internal::container
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif