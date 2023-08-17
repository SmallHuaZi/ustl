#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_CONTAINER_BASE_RBTREENODE_HPP__ 
#define __USTL_CORE_INTERNAL_CONTAINER_BASE_RBTREENODE_HPP__

#ifndef __USTL_CORE_INTERNAL_CONTAINER_BASE_TREENODE_HPP__ 
#include <ustl/core/internal/container/base/con_treenode.hpp>
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

    enum class RBTreeNodeColor 
        : usize 
    {
        Black,
        Red
    };


    struct RBTreeNodeBasic
        : public TreeNodeBasic 
    {
        USTL_GENERAL_ASSOCIATION_TYPE_HAD_BASE(RBTreeNodeBasic, TreeNodeBasic);
        typedef RBTreeNodeColor          Color;

    public:
        RBTreeNodeBasic() USTL_NOEXCEPT;

        RBTreeNodeBasic(
            Ptr __n
        ) USTL_NOEXCEPT;

        RBTreeNodeBasic(
            Ptr __l, 
            Ptr __r, 
            Ptr __p
        ) USTL_NOEXCEPT;

    public:
        USTL_ALWAYS_INLINE
        Ptr
        right() USTL_NOEXCEPT
        { return    static_cast<Ptr>(_M_right); }

        USTL_ALWAYS_INLINE
        Ptr
        left() USTL_NOEXCEPT
        { return    static_cast<Ptr>(_M_left); }

        USTL_ALWAYS_INLINE
        Ptr
        parent() USTL_NOEXCEPT
        { return    static_cast<Ptr>(_M_parent); }

        USTL_ALWAYS_INLINE
        ConstPtr
        right() const USTL_NOEXCEPT
        { return    static_cast<ConstPtr>(_M_right); }

        USTL_ALWAYS_INLINE
        ConstPtr
        left() const USTL_NOEXCEPT
        { return    static_cast<ConstPtr>(_M_left); }

        USTL_ALWAYS_INLINE
        ConstPtr
        parent() const USTL_NOEXCEPT
        { return    static_cast<ConstPtr>(_M_parent); }
    
    public:
        Color _M_color;
    };


    /**
     *  @function: void ustl_rbt_insert(RBTreeNodeBasic *, RBTreeHeader *) noexcept
     *  @arg  n  The new node that has been inserted into the tree 
     *  @arg  h  The head node of the tree
     *  @brief Balance the nodes that have been inserted into the tree 
    */
    USTL_API 
    extern void 
    ustl_rbt_rebalance_after_insertion(RBTreeNodeBasic *n, TreeHeader * const h) USTL_NOEXCEPT;


    /**
     *  @function: RBTreeNodeBasic * ustl_rbt_erase(RBTreeNodeBasic *, RBTreeHeader *) noexcept
     *  @arg  n  The Node to be deleted but not yet deleted
     *  @arg  h  The head node of the tree
     *  @brief Virtually delete the specified node and balance the tree
     *  @return The node to delete
    */
    USTL_API 
    extern RBTreeNodeBasic * 
    ustl_rbt_erase_and_rebalance(RBTreeNodeBasic *n, TreeHeader * const h) USTL_NOEXCEPT;

} // namespace ustl::core::internal::container::base
} // namespace ustl::core::internal::container
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl




#endif