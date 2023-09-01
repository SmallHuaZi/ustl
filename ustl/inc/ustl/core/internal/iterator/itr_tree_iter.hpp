#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_ITERATOR_TREE_ITER_HPP__
#define __USTL_CORE_INTERNAL_ITERATOR_TREE_ITER_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_BASE_HPP__ 
#include <ustl/core/internal/type_traits/tt_base.hpp>
#endif

#ifndef __USTL_CORE_INTERNAL_ITERATOR_CATEGORY_HPP__ 
#include <ustl/core/internal/iterator/itr_category.hpp>
#endif

#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_TREENODE_TRAIT_HPP__ 
#include <ustl/core/internal/type_traits/tt_treenode_trait.hpp>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace iterator
{

    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    struct TreeIter;

    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    static bool
    operator==(TreeIter<IsMut, Node, Compare, KeyOfVal> const &x, 
               TreeIter<IsMut, Node, Compare, KeyOfVal> const &y) USTL_NOEXCEPT;

    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    static bool
    operator!=(TreeIter<IsMut, Node, Compare, KeyOfVal> const &x, 
               TreeIter<IsMut, Node, Compare, KeyOfVal> const &y) USTL_NOEXCEPT;

    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    static bool
    operator>=(TreeIter<IsMut, Node, Compare, KeyOfVal> const &x, 
               TreeIter<IsMut, Node, Compare, KeyOfVal> const &y) USTL_NOEXCEPT;

    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    static bool
    operator<(TreeIter<IsMut, Node, Compare, KeyOfVal> const &x, 
              TreeIter<IsMut, Node, Compare, KeyOfVal> const &y) USTL_NOEXCEPT;


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    class TreeIter
    {
        typedef internal::type_traits::TreeNodeTrait<Node>  NodeTrait;

    public:
        typedef typename NodeTrait::value_type       value_type;
        typedef typename NodeTrait::reference        reference;
        typedef typename NodeTrait::pointer          pointer;
        typedef typename NodeTrait::const_reference  const_reference;
        typedef typename NodeTrait::const_pointer    const_pointer;

        typedef isize       difference_type;
        typedef bothway_iter_category   iter_category;

    private:
        typedef typename NodeTrait::NodePtr       NodePtr;
        typedef typename NodeTrait::NodeRef       NodeRef;
        typedef typename NodeTrait::ConstNodePtr  ConstNodePtr;
        typedef typename NodeTrait::ConstNodeRef  ConstNodeRef;

        typedef TreeIter<IsMut, Node, Compare, KeyOfVal>  Self;
        typedef TreeIter<false, Node, Compare, KeyOfVal>  Const;
        typedef TreeIter<true, Node, Compare, KeyOfVal>   Mut;

        typedef typename internal::type_traits::Conditional<IsMut, reference, const_reference>::type
            ChosenRef;

        typedef typename internal::type_traits::Conditional<IsMut, pointer, const_pointer>::type
            ChosenPtr;

        typedef typename internal::type_traits::Conditional<IsMut, NodePtr, ConstNodePtr>::type
            ChosenNodePtr;

        typedef typename internal::type_traits::Conditional<IsMut, NodeRef, ConstNodeRef>::type
            ChosenNodeRef;

    public:
        TreeIter(ChosenNodePtr);

        TreeIter(ChosenNodeRef);

        /**
         * 
        */
        Self &
        operator++() USTL_NOEXCEPT;

        /**
         * 
        */
        Self &
        operator--() USTL_NOEXCEPT;

        /**
         * 
        */
        Self
        operator++(int) USTL_NOEXCEPT;

        /**
         * 
        */
        Self
        operator--(int) USTL_NOEXCEPT;

        /**
         * 
        */
        ChosenRef
        operator*() USTL_NOEXCEPT;

        /**
         * 
        */
        ChosenPtr
        operator->() USTL_NOEXCEPT;

        /**
         * 
        */
        Mut
        _M_const_cast() USTL_NOEXCEPT;

        /**
         * 
        */
        friend bool
        operator!= <>(Self const &x, Self const &y) USTL_NOEXCEPT;

        /**
         * 
        */
        friend bool
        operator!= <>(Self const &x, Self const &y) USTL_NOEXCEPT;

        /**
         * 
        */
        friend bool
        operator>= <>(Self const &x, Self const &y) USTL_NOEXCEPT;

        /**
         * 
        */
        friend bool
        operator< <>(Self const &x, Self const &y) USTL_NOEXCEPT;

    private:
        NodePtr     _M_node;
    };


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    TreeIter<IsMut, Node, Compare, KeyOfVal>::
        TreeIter(ChosenNodePtr node)
        : _M_node(const_cast<NodePtr>(node))
    {}


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    TreeIter<IsMut, Node, Compare, KeyOfVal>::
        TreeIter(ChosenNodeRef node)
        : _M_node(const_cast<NodePtr>(&node))
    {}


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    auto TreeIter<IsMut, Node, Compare, KeyOfVal>::
        operator++() USTL_NOEXCEPT -> Self &
    {
        _M_node = NodeTrait::increment(_M_node);
        return *this;
    }


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    auto TreeIter<IsMut, Node, Compare, KeyOfVal>::
        operator++(int) USTL_NOEXCEPT -> Self {
        Self res{*this};
        _M_node = NodeTrait::increment(_M_node);
        return res;
    }


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    auto TreeIter<IsMut, Node, Compare, KeyOfVal>::
        operator--() USTL_NOEXCEPT -> Self &
    {
        _M_node = NodeTrait::decrement(_M_node);
        return *this;
    }


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    auto TreeIter<IsMut, Node, Compare, KeyOfVal>::
        operator--(int) USTL_NOEXCEPT -> Self
    {
        Self res{*this};
        _M_node = NodeTrait::decrement(_M_node);
        return res;
    }


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    auto TreeIter<IsMut, Node, Compare, KeyOfVal>::
        _M_const_cast() USTL_NOEXCEPT -> Mut 
    { return Mut(_M_node); }


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    auto TreeIter<IsMut, Node, Compare, KeyOfVal>::
        operator*() USTL_NOEXCEPT -> ChosenRef 
    { return NodeTrait::get_value(_M_node); }


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    auto TreeIter<IsMut, Node, Compare, KeyOfVal>::
        operator->() USTL_NOEXCEPT -> ChosenPtr
    { return NodeTrait::get_value_ptr(_M_node); }


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    static bool
    operator!=(TreeIter<IsMut, Node, Compare, KeyOfVal> const &x, 
               TreeIter<IsMut, Node, Compare, KeyOfVal> const &y) USTL_NOEXCEPT
    { return x._M_node != y._M_node; }


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    static bool
    operator==(TreeIter<IsMut, Node, Compare, KeyOfVal> const &x, 
               TreeIter<IsMut, Node, Compare, KeyOfVal> const &y) USTL_NOEXCEPT
    { return x._M_node == y._M_node; }


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    static bool
    operator>=(TreeIter<IsMut, Node, Compare, KeyOfVal> const &x, 
               TreeIter<IsMut, Node, Compare, KeyOfVal> const &y) USTL_NOEXCEPT
    { return !x < y; }


    template <bool IsMut, typename Node, typename Compare, typename KeyOfVal>
    USTL_ALWAYS_INLINE
    static bool
    operator<(TreeIter<IsMut, Node, Compare, KeyOfVal> const &x, 
              TreeIter<IsMut, Node, Compare, KeyOfVal> const &y) USTL_NOEXCEPT
    {
        typedef typename TreeIter<IsMut, Node, Compare, KeyOfVal>::NodeTrait    NodeTrait;

        auto extract = KeyOfVal{};
        auto &xv = extract(NodeTrait::get_value(x._M_node));
        auto &yv = extract(NodeTrait::get_value(y._M_node));
        return Compare{}(xv, yv);
    }

    
} // namespace ustl::core::internal::iterator
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl


#endif