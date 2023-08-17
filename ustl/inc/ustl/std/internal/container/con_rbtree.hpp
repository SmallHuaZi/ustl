#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_STD_INTERNAL_CONTAINER_RBTREE_HPP__
#define __USTL_STD_INTERNAL_CONTAINER_RBTREE_HPP__


namespace ustl
{
namespace std 
{
namespace internal
{
namespace container
{

    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    class RBTree;

    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    static inline bool
    operator!=(RBTree<Key, Val, KeyOfVal, Compare, Allocator> const &,
               RBTree<Key, Val, KeyOfVal, Compare, Allocator> const &);

    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    static inline bool
    operator==(RBTree<Key, Val, KeyOfVal, Compare, Allocator> const &,
               RBTree<Key, Val, KeyOfVal, Compare, Allocator> const &);

    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    static inline bool
    operator<(RBTree<Key, Val, KeyOfVal, Compare, Allocator> const &,
              RBTree<Key, Val, KeyOfVal, Compare, Allocator> const &);

    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    static inline bool
    operator>=(RBTree<Key, Val, KeyOfVal, Compare, Allocator> const &,
               RBTree<Key, Val, KeyOfVal, Compare, Allocator> const &);


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    struct RBTreeBasic
    {
        struct RBTreeImpl;
        struct RBTreeNode;

        using NodeTrait = internal::type_traits::TreeNodeTrait<RBTreeNode>;
        using ValueAllocatorTrait = internal::type_traits::AllocatorTrait<Allocator>;
        using NodeAllocatorType = typename ValueAllocatorTrait::template rebind_t<RBTreeNode>;
        using NodeAllocatorTrait = internal::type_traits::AllocatorTrait<NodeAllocatorType>;

        template <bool IsMut>
        using RBTreeIter = internal::iterator::TreeIter<IsMut, RBTreeNode, KeyOfVal, Compare>;

    protected:
        USTL_GENERAL_INTERFACE_ASSOCIATION_TYPE_HAD_ALLOCATOR(Val, Allocator);

        typedef RBTreeImpl       Impl;
        typedef RBTreeNode       Node;
        typedef RBTreeNode *     NodePtr;
        typedef base::TreeHeader        Header;
        typedef base::RBTreeNodeBasic   NodeBase;

        typedef Key     key_type;
        typedef Compare compare_type;
        typedef RBTreeIter<true>   iter_mut;
        typedef RBTreeIter<false>  iter_const;

    protected:
        using base::RBTreeNodeColor::Red;
        using base::RBTreeNodeColor::Black;

    protected:
        template <typename OtherAllocator, typename>
        RBTreeBasic(OtherAllocator &&alloc = OtherAllocator{});

        NodePtr
        _M_allocate_node(size_type);

        void
        _M_deallocate_node(pointer, size_type);

        template <typename... InitArgs>
        void
        _M_construct_elem(pointer, InitArgs&& ...);

        void
        _M_destory_elem(pointer) USTL_NOEXCEPT;

        NodeAllocatorType &
        _M_get_node_allocator() USTL_NOEXCEPT;

        allocator_type & 
        _M_get_value_allocator() USTL_NOEXCEPT;

        bool
        _M_compare_key(key_type const &x, key_type const &y) 
            USTL_NOEXCEPT(USTL_NOEXCEPT(_M_impl(x, y)));

        key_type const &
        _M_extract_key(value_type const &val)
            USTL_NOEXCEPT(USTL_NOEXCEPT(_M_impl(val)));

        iter_mut
        _M_insert_node(NodePtr, NodePtr) USTL_NOEXCEPT;

        template <typename... InitArgs>
        iter_mut
        _M_emplace_unique(InitArgs&& ...args);

        template <typename... InitArgs>
        iter_mut
        _M_emplace_multi(InitArgs&& ...args);

        iter_const
        _M_get_insert_pos_multi(key_type const &) USTL_NOEXCEPT;

        iter_const
        _M_get_insert_pos_unique(key_type const &) USTL_NOEXCEPT;

        void
        _M_erase_aux(iter_const) USTL_NOEXCEPT;

        size_type 
        _M_erase_range(iter_const first, iter_const last) USTL_NOEXCEPT;

        iter_const
        _M_upper_bound(NodePtr, NodePtr, key_type const &) USTL_NOEXCEPT;

        iter_const
        _M_lower_bound(NodePtr, NodePtr, key_type const &) USTL_NOEXCEPT;

        iter_const
        _M_equal_range(NodePtr, NodePtr, key_type const &) USTL_NOEXCEPT;

        NodePtr
        _M_begin() USTL_NOEXCEPT;

        NodePtr
        _M_end() USTL_NOEXCEPT;

        NodePtr
        _M_left_most() USTL_NOEXCEPT;

        NodePtr
        _M_right_most() USTL_NOEXCEPT;

    private:
        Impl    *_M_impl;
    };


    /// @brief 
    /// @tparam Key 
    /// @tparam Val 
    /// @tparam KeyOfVal 
    /// @tparam Compare 
    /// @tparam Allocator 
    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    class RBTree
        : private RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>
    {
    protected:
        USTL_GENERAL_ASSOCIATION_TYPE(RBTree);

        typedef RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator> Base;
        typedef typename Base::NodePtr  NodePtr;

    public: 
        typedef typename Base::key_type            key_type;
        typedef typename Base::value_type          value_type;
        typedef typename Base::pointer             pointer;
        typedef typename Base::reference           reference;
        typedef typename Base::const_pointer       const_pointer;
        typedef typename Base::const_reference     const_reference;
        typedef typename Base::iter_mut            iter_mut;
        typedef typename Base::iter_const          iter_const;
        typedef typename Base::compare_type        compare_type;
        typedef typename Base::allocator_type      allocator_type;
        typedef typename Base::size_type           size_type;
        typedef typename Base::diff_type           diff_type;

    public:
        explicit RBTree() USTL_NOEXCEPT;

        /// @brief 
        /// @tparam OtherAllocator 
        /// @tparam  
        /// @param otehr 
        /// @param alloc 
        template <typename OtherAllocator, typename>
        explicit RBTree(Self const &otehr, OtherAllocator &alloc);

        /// @brief 
        /// @param other 
        explicit RBTree(Self &&other);

        /// @brief 
        /// @param elems 
        explicit RBTree(initializer_list<value_type> const &elems);

        /// @brief 
        /// @param elems 
        explicit RBTree(initializer_list<value_type> &&elems);

        /// @brief 
        /// @tparam FwdIter
        /// @param first 
        /// @param last 
        template <typename FwdIter, typename>
        explicit RBTree(FwdIter first, FwdIter last); 

        ~RBTree() USTL_NOEXCEPT;

    public:
        /// @brief 
        /// @param val 
        /// @return 
        pair<iter_mut, bool>
        insert_unique(const_reference val);

        /// @brief 
        /// @param flush 
        /// @return 
        pair<iter_mut, bool>
        insert_unique(value_type &&val);

        /// @brief 
        /// @param flush 
        /// @return 
        iter_mut 
        insert_multi(const_reference val);

        /// @brief 
        /// @param flush 
        /// @return 
        iter_mut 
        insert_multi(value_type &&flush);

        /// @brief 
        /// @tparam ...InitArgs 
        /// @param ...args 
        /// @return 
        template <typename... InitArgs>
        iter_mut
        emplace_unique(InitArgs&& ...args);

        /// @brief 
        /// @tparam ...InitArgs 
        /// @param ...args 
        /// @return 
        template <typename... InitArgs>
        iter_mut
        emplace_multi(InitArgs&& ...args);

        /// @brief 
        /// @param  pos 
        /// @return 
        void 
        erase_unique(iter_const pos) USTL_NOEXCEPT;

        /// @brief 
        /// @param  key 
        /// @return 
        void 
        erase_unique(key_type const &key) USTL_NOEXCEPT;

        /// @brief 
        /// @param  pos 
        /// @return 
        size_type
        erase_multi(iter_const pos) USTL_NOEXCEPT;

        /// @brief 
        /// @param  key
        /// @return 
        size_type
        erase_multi(key_type const &key) USTL_NOEXCEPT;

        /// @brief 
        /// @param  key
        /// @return 
        size_type
        erase_range(iter_const first, iter_const last) USTL_NOEXCEPT;

        /// @brief 
        /// @param  key
        /// @return 
        iter_mut 
        find(key_type const &key) USTL_NOEXCEPT;

        /// @brief 
        /// @param  key
        /// @return 
        iter_const
        find(key_type const &key) const USTL_NOEXCEPT;

        /// @brief 
        /// @param  key
        /// @return 
        iter_const
        lower_bound(key_type const &key) const USTL_NOEXCEPT;

        /// @brief 
        /// @param  key
        /// @return 
        iter_mut
        lower_bound(key_type const &key) USTL_NOEXCEPT;

        /// @brief 
        /// @param  key
        /// @return 
        iter_mut
        upper_bound(key_type const &key) USTL_NOEXCEPT;

        /// @brief 
        /// @param  key
        /// @return 
        iter_const
        upper_bound(key_type const &key) const USTL_NOEXCEPT;

        /// @brief 
        /// @param  key
        /// @return 
        pair<iter_mut, iter_mut>
        equal_range(key_type const &key) USTL_NOEXCEPT;

        /// @brief 
        /// @param  key
        /// @return 
        pair<iter_const, iter_const>
        equal_range(key_type const &key) const USTL_NOEXCEPT;

        /// @brief 
        /// @param  key
        /// @return 
        bool
        contains(key_type const &key) const USTL_NOEXCEPT;

        /// @brief 
        /// @return 
        size_type
        count() const USTL_NOEXCEPT;

        /// @brief 
        /// @return 
        reference
        first() USTL_NOEXCEPT;

        /// @brief 
        /// @return 
        const_reference
        first() const USTL_NOEXCEPT;

        /// @brief 
        /// @return 
        reference
        last() USTL_NOEXCEPT;

        /// @brief 
        /// @return 
        const_reference
        last() const USTL_NOEXCEPT;

        /// @brief 
        /// @return
        iter_mut 
        begin() USTL_NOEXCEPT;

        /// @brief 
        /// @return
        iter_mut 
        end() USTL_NOEXCEPT;

        /// @brief 
        /// @return
        iter_const 
        cbegin() const USTL_NOEXCEPT;

        /// @brief 
        /// @return
        iter_const 
        cend() const USTL_NOEXCEPT;

        /// @brief 
        /// @return
        iter_mut
        rbegin() USTL_NOEXCEPT;

        /// @brief 
        /// @return
        iter_mut
        rend() USTL_NOEXCEPT;

        /// @brief 
        /// @return
        iter_const
        crbegin() const USTL_NOEXCEPT;

        /// @brief 
        /// @return
        iter_const
        crend() const USTL_NOEXCEPT;

        /// @brief 
        /// @param elems
        /// @return
        void
        assign_unique(initializer_list<value_type> const &elems);

        /// @brief 
        /// @param elems
        /// @return
        void
        assign_multi(initializer_list<value_type> const &elems);

        /// @brief 
        /// @tparam  FwdIter
        /// @param  first 
        /// @param  last 
        /// @return
        template <typename FwdIter>
        void
        assign_unique(FwdIter first, FwdIter last);

        /// @brief 
        /// @tparam  FwdIter
        /// @param  first 
        /// @param  last 
        /// @return
        template <typename FwdIter>
        void
        assign_multi(FwdIter first, FwdIter last);

        /// @brief 
        /// @param  oter 
        void
        swap(Ref other) USTL_NOEXCEPT;

        /// @brief 
        /// @param  oter 
        void
        swap(Self &&otehr) USTL_NOEXCEPT;

        /// @brief 
        /// @param  oter 
        void
        merge(Ref otehr) USTL_NOEXCEPT;

        /// @brief 
        /// @param  oter 
        void
        merge(Self &&otehr) USTL_NOEXCEPT;

        /// @brief 
        void
        clear() USTL_NOEXCEPT;

        /// @brief 
        /// @return
        allocator_type const &
        allocator() const USTL_NOEXCEPT;

        /// @brief 
        /// @param  other
        /// @return
        Self &
        operator=(initializer_list<value_type> const &other) &;

        /// @brief 
        /// @param  other
        /// @return
        Self &
        operator=(initializer_list<value_type> &&other) &;

        /// @brief 
        /// @param  other
        /// @return
        Self &
        operator=(ConstRef other) &;

        /// @brief 
        /// @param  other
        /// @return
        Self &
        operator=(Self &&other) &;

        /// @brief 
        /// @param  x
        /// @param  y
        /// @return
        friend bool
        operator== <>(ConstRef x, ConstRef y) USTL_NOEXCEPT;

        /// @brief 
        /// @param  x
        /// @param  y
        /// @return
        friend bool
        operator!= <>(ConstRef x, ConstRef y) USTL_NOEXCEPT;

        /// @brief 
        /// @param  x
        /// @param  y
        /// @return
        friend bool
        operator< <>(ConstRef x, ConstRef y) USTL_NOEXCEPT;

        /// @brief 
        /// @param  x
        /// @param  y
        /// @return
        friend bool
        operator>= <>(ConstRef x, ConstRef y) USTL_NOEXCEPT;

    protected:
        using  Base::_M_destory_elem;
        using  Base::_M_compare_key;
        using  Base::_M_extract_key;
        using  Base::_M_emplace_unique;
        using  Base::_M_emplace_multi;
        using  Base::_M_get_insert_pos_unique;
        using  Base::_M_get_insert_pos_multi;
        using  Base::_M_erase_aux;
        using  Base::_M_erase_range;
        using  Base::_M_lower_bound;
        using  Base::_M_upper_bound;
        using  Base::_M_equal_range;
        using  Base::_M_left_most;
        using  Base::_M_right_most;
        using  Base::_M_end;
        using  Base::_M_get_value_allocator;
    };

    
} // namespace ustl::std::internal::container
} // namespace ustl::std::internal
} // namespace ustl::std
} // namespace ustl

#endif