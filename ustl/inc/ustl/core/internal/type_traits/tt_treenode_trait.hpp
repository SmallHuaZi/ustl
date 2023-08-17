#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_TREENODE_TRAIT_HPP__
#define __USTL_CORE_INTERNAL_TYPETRAITS_TREENODE_TRAIT_HPP__

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

    template <typename TreeNode>
    struct TreeNodeTrait
    {
        typedef TreeNode    Node;
        typedef TreeNode *  NodePtr;
        typedef TreeNode &  NodeRef;
        typedef TreeNode const *  ConstNodePtr;
        typedef TreeNode const &  ConstNodeRef;

        typedef typename Node::value_type       value_type;
        typedef typename Node::pointer          pointer;
        typedef typename Node::reference        reference;
        typedef typename Node::const_pointer    const_pointer;
        typedef typename Node::const_reference  const_reference;

    public:
        USTL_ALWAYS_INLINE 
        static NodePtr
        increment(NodePtr node) USTL_NOEXCEPT
        { return Node::template _S_increment<Node>(node); }

        USTL_ALWAYS_INLINE 
        static NodePtr
        decrement(NodePtr node) USTL_NOEXCEPT
        { return Node::template _S_decrement<Node>(node); }

        USTL_ALWAYS_INLINE 
        static void 
        rotl(NodePtr node) USTL_NOEXCEPT
        { node->_M_rotate_left(); }

        USTL_ALWAYS_INLINE 
        static void 
        rotr(NodePtr node) USTL_NOEXCEPT
        { node->_M_rotate_right(); }

        USTL_ALWAYS_INLINE 
        static usize 
        height(NodePtr node) USTL_NOEXCEPT
        { return node->_M_height(); }

        USTL_ALWAYS_INLINE
        static NodePtr
        get_left(NodePtr node) USTL_NOEXCEPT
        { return static_cast<NodePtr>(node->_M_left); }

        USTL_ALWAYS_INLINE
        static NodePtr
        get_right(NodePtr node) USTL_NOEXCEPT
        { return static_cast<NodePtr>(node->_M_right); }

        USTL_ALWAYS_INLINE
        static NodePtr
        get_parent(NodePtr node) USTL_NOEXCEPT
        { return static_cast<NodePtr>(node->_M_parent); }

        USTL_ALWAYS_INLINE
        static void 
        set_left(NodePtr node, NodePtr flush) USTL_NOEXCEPT
        { node->_M_left = flush; }

        USTL_ALWAYS_INLINE
        static NodePtr
        set_right(NodePtr node, NodePtr flush) USTL_NOEXCEPT
        { node->_M_right = flush; }

        USTL_ALWAYS_INLINE
        static NodePtr
        set_parent(NodePtr node, NodePtr flush) USTL_NOEXCEPT
        { node->_M_parent = flush; }

        USTL_ALWAYS_INLINE
        static reference 
        get_value(NodePtr node) USTL_NOEXCEPT
        { return node->get_value(); }

        USTL_ALWAYS_INLINE
        static pointer 
        get_value_ptr(NodePtr node) USTL_NOEXCEPT
        { return node->get_value_ptr(); }
    };

} // namespace ustl::core::internal::type_traits
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl
    
#endif