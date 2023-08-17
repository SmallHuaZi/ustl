#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_CONTAINER_BASE_TREENODE_HPP__ 
#define __USTL_CORE_INTERNAL_CONTAINER_BASE_TREENODE_HPP__

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
namespace base
{

    struct TreeNodeBasic
    {
        USTL_GENERAL_ASSOCIATION_TYPE(TreeNodeBasic);

    public:
        TreeNodeBasic() USTL_NOEXCEPT;

        TreeNodeBasic(
            Ptr p
        ) USTL_NOEXCEPT;

        TreeNodeBasic(
            Ptr l, 
            Ptr r, 
            Ptr p
        ) USTL_NOEXCEPT;

    public:
        void
        _M_reset() USTL_NOEXCEPT;

        void
        _M_rotate_left() USTL_NOEXCEPT;

        void
        _M_rotate_right() USTL_NOEXCEPT;

        usize
        _M_height() const USTL_NOEXCEPT;

    public:
        template <typename T>
        USTL_ALWAYS_INLINE
        T *
        _M_sibling() USTL_NOEXCEPT
        { return   const_cast<T *>(ConstPtr(this)->_M_sibling<T>()); }

        template <typename T>
        USTL_ALWAYS_INLINE
        T const *
        _M_sibling() const USTL_NOEXCEPT
        { return   static_cast<T const *>(_M_sibling<Self>()); }

        template <typename T>
        USTL_ALWAYS_INLINE
        static T *
        _S_decrement(Ptr root) USTL_NOEXCEPT
        { return   const_cast<T *>(_S_decrement<T>(ConstPtr(root))); }

        template <typename T>
        USTL_ALWAYS_INLINE
        static T *
        _S_increment(Ptr root) USTL_NOEXCEPT
        { return   const_cast<T *>(_S_increment<T>(ConstPtr(root))); }
        
        template <typename T>
        USTL_ALWAYS_INLINE
        static T const *
        _S_decrement(ConstPtr root) USTL_NOEXCEPT
        { return   static_cast<T const *>(_S_decrement<Self>(root)); }

        template <typename T>
        USTL_ALWAYS_INLINE
        static T const *
        _S_increment(ConstPtr root) USTL_NOEXCEPT
        { return   static_cast<T const *>(_S_increment<Self>(root)); }

        template <typename T>
        USTL_ALWAYS_INLINE
        static T * 
        _S_maxnode(Ptr root) USTL_NOEXCEPT
        { return   const_cast<T *>(_S_maxnode<T>(ConstPtr(root))); }

        template <typename T>
        USTL_ALWAYS_INLINE
        static T * 
        _S_minnode(Ptr root) USTL_NOEXCEPT
        { return   const_cast<T *>(_S_minnode<T>(ConstPtr(root))); }

        template <typename T>
        USTL_ALWAYS_INLINE
        static T const *
        _S_minnode(ConstPtr root) USTL_NOEXCEPT
        { return   static_cast<T const *>(_S_minnode<Self>(root)); }

        template <typename T>
        USTL_ALWAYS_INLINE
        static  T const * 
        _S_maxnode(ConstPtr root) USTL_NOEXCEPT
        { return   static_cast<T const *>(_S_maxnode<Self>(root)); }

    public:
        Ptr  _M_left;
        Ptr  _M_right;
        Ptr  _M_parent;
    };



    struct TreeHeader 
        : public TreeNodeBasic
    {
        USTL_GENERAL_ASSOCIATION_TYPE_HAD_BASE(TreeHeader, TreeNodeBasic);

    public:
        void
        _M_reset() USTL_NOEXCEPT;

        void
        _M_swap(Ref other) USTL_NOEXCEPT;

    public:
        template <typename T>
        USTL_ALWAYS_INLINE
        T *
        _M_get_root() USTL_NOEXCEPT
        { return   static_cast<T *>(_M_parent); }

        template <typename T>
        USTL_ALWAYS_INLINE
        T const *
        _M_get_root() const USTL_NOEXCEPT
        { return   static_cast<T const *>(_M_parent); }

        template <typename T>
        USTL_ALWAYS_INLINE
        T *
        _M_left_most() USTL_NOEXCEPT
        { return   static_cast<T *>(_M_left); }

        template <typename T>
        USTL_ALWAYS_INLINE
        T const *
        _M_left_most() const USTL_NOEXCEPT
        { return   static_cast<T const *>(_M_left); }

        template <typename T>
        USTL_ALWAYS_INLINE
        T *
        _M_right_most() USTL_NOEXCEPT
        { return   static_cast<T *>(_M_right); }

        template <typename T>
        USTL_ALWAYS_INLINE
        T const *
        _M_right_most() const USTL_NOEXCEPT
        { return   static_cast<T const *>(_M_right); }

    public:
        usize   _M_count;
    };


    USTL_ALWAYS_INLINE
    TreeNodeBasic::TreeNodeBasic() USTL_NOEXCEPT
        : _M_parent(this),
          _M_right(this),
          _M_left(this)
    {}


    USTL_ALWAYS_INLINE
    TreeNodeBasic::TreeNodeBasic(Ptr parent) USTL_NOEXCEPT
        : Self()
    { _M_parent = parent; }


    USTL_ALWAYS_INLINE
    TreeNodeBasic::TreeNodeBasic(Ptr left, Ptr right, Ptr parent) USTL_NOEXCEPT
        : _M_parent(parent),
          _M_right(right),
          _M_left(left)
    {}


    template <>
    USTL_ALWAYS_INLINE
    TreeNodeBasic const *
    TreeNodeBasic::_M_sibling<TreeNodeBasic>() const USTL_NOEXCEPT
    { return  this == _M_parent->_M_left ? _M_parent->_M_right : this; }


    USTL_ALWAYS_INLINE
    void
    TreeNodeBasic::_M_reset() USTL_NOEXCEPT
    {
        _M_left   = this;
        _M_right  = this;
        _M_parent = this;
    }


    USTL_ALWAYS_INLINE
    void
    TreeHeader::_M_reset() USTL_NOEXCEPT
    {
        Base::_M_reset();
        _M_count = 0;
    }


    USTL_ALWAYS_INLINE
    void
    TreeHeader::_M_swap(Self &other) USTL_NOEXCEPT
    {
        Self tmp {*this};
        *this = other;
        other = tmp;
    }
    

} // namespace ustl::core::internal::container::base
} // namespace ustl::core::internal::container
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl


#endif