namespace ustl 
{
namespace std 
{
namespace internal
{
namespace container
{

    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    struct RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::RBTreeImpl
        : public KeyOfVal,
          public compare_type, 
          public allocator_type,
          public NodeAllocatorType
    {
        Header  _M_data;
    };


    template <typename Key, typename Val, typename Comp, typename Compare, typename Allocator>
    struct RBTreeBasic<Key, Val, Comp, Compare, Allocator>::RBTreeNode
        : public NodeBase 
    {
        USTL_GENERAL_ASSOCIATION_TYPE_HAD_BASE(RBTreeNode, NodeBase);
        USTL_GENERAL_INTERFACE_ASSOCIATION_TYPE_HAD_ALLOCATOR(Val, Allocator);

    public:
        reference
        get_value() USTL_NOEXCEPT
        { return _M_data; }

        const_reference
        get_value() const USTL_NOEXCEPT
        { return _M_data; }

        pointer
        get_value_ptr() USTL_NOEXCEPT
        { return &_M_data; }

        const_pointer
        get_value_ptr() const USTL_NOEXCEPT
        { return &_M_data; }

    private:
        value_type        _M_data;
    };


/**---------------------------------------- [RBTreeBasic] BEGIN --------------------------------------------*/
    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_allocate_node(size_type count) -> NodePtr
    { return NodeAllocatorTrait::allocate(_M_get_node_allocator(), count); }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    void RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_deallocate_node(pointer scope, size_type count)
    { return NodeAllocatorTrait::deallocate(_M_get_node_allocator(), scope, count); }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    template <typename... InitArgs>
    USTL_ALWAYS_INLINE
    void RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_construct_elem(pointer ptr, InitArgs &&...args)
    { ValueAllocatorTrait::construct(ptr, internal::utility::forward<InitArgs>(args)...); }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    void RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_destory_elem(pointer ptr) USTL_NOEXCEPT
    { ValueAllocatorTrait::destory(ptr); }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_get_node_allocator() USTL_NOEXCEPT -> NodeAllocatorType &
    { return *_M_impl; }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_get_value_allocator() USTL_NOEXCEPT -> allocator_type &
    { return *_M_impl; }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    bool RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_compare_key(key_type const &x, key_type const &y) USTL_NOEXCEPT(USTL_NOEXCEPT(_M_impl(x, y)))
    { return    _M_impl(x, y); }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    auto RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_extract_key(value_type const &val)  USTL_NOEXCEPT(USTL_NOEXCEPT(_M_impl(val))) -> key_type const &
    { return    _M_impl(val); }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    auto RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_insert_node(NodePtr pos, NodePtr freshly) USTL_NOEXCEPT -> iter_mut
    {
        key_type const &key_of_new = _M_extract_key(freshly);
        key_type const &key_of_pos = _M_extract_key(pos);

        if (pos == _M_end()) {
            NodeTrait::set_parent(freshly, pos);
            NodeTrait::set_parent(pos, freshly);
        }
        else if (_M_compare_key(key_of_new, key_of_pos)) {
            NodeTrait::set_left(pos, freshly);
        }
        else {
            NodeTrait::set_right(pos, freshly);
        }

        base::ustl_rbt_rebalance_after_insertion(freshly, _M_end());
        ++_M_impl->_M_data._M_count;

        return iter_mut(freshly);
    }


    template<typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    template<typename ...InitArgs>
    USTL_ALWAYS_INLINE
    auto  RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_emplace_unique(InitArgs &&...args) -> iter_mut
    {
        NodePtr freshly;

        // Catch potential memory allocation exceptions and construction exceptions. 
        USTL_TRY {
             freshly = _M_allocate_node(1);
            _M_construct_elem(freshly->get_value_ptr(), internal::utility::forward<InitArgs>(args)...);
        }
        USTL_CATCH_ALL {
            _M_destory_elem(freshly);
            _M_deallocate_node(freshly);
            USTL_THROW_AGAIN;
        }

        iter_const pos = _M_get_insert_pos_unique(freshly->get_value());
        if (0 != _M_begin() && _M_end() == pos._M_node) {
            return pos;
        }

        return _M_insert_node(pos._M_node, freshly);
    }


    template<typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    template<typename ...InitArgs>
    inline auto RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_emplace_multi(InitArgs &&...args) -> iter_mut
    {
        NodePtr freshly;

        // Catch potential memory allocation exceptions and construction exceptions. 
        USTL_TRY {
             freshly = _M_allocate_node(1);
            _M_construct_elem(freshly->get_value_ptr(), internal::utility::forward<InitArgs>(args)...);
        }
        USTL_CATCH_ALL {
            _M_destory_elem(freshly);
            _M_deallocate_node(freshly);
            USTL_THROW_AGAIN;
        }
        iter_const pos = _M_get_insert_pos_multi(freshly->get_value());

        return _M_insert_node(pos._M_node, freshly);
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    auto RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_get_insert_pos_unique(key_type const &key) USTL_NOEXCEPT -> iter_const 
    {
        bool cmp = true;
        NodePtr cur = _M_begin();
        NodePtr pre = _M_end();

        while (cur) {
            pre = cur;
            cmp = _M_compare_key(key, _M_extract_key(cur));
            cur = cmp ? cur->left() : cur->right();
        }

        if (cmp) {
            if (_M_left_most() == pre) {
                return iter_const(pre);
            }
            pre = Node::template _S_decrement<Node>(pre);
        }

        if (_M_compare_key(_M_extract_key(pre), key)) {
            return iter_const(pre);
        }

        return iter_const(_M_end());  
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    auto RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_get_insert_pos_multi(key_type const &key) USTL_NOEXCEPT -> iter_const 
    {
        bool cmp = true;
        NodePtr beg = _M_begin();
        NodePtr pre = _M_end();

        while (beg) {
            pre = beg;
            cmp = _M_compare_key(key, _M_extract_key(beg));
            beg = cmp ? beg->left() : beg->right();
        }

        return iter_const(pre);
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    void RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_erase_aux(iter_const pos) USTL_NOEXCEPT
    {
        if (pos._M_node == _M_end()) {
            return;
        }

        NodePtr old = base::ustl_rbt_erase_and_rebalance(pos._M_node, _M_end());
        _M_destory_elem(old->_M_data);
        _M_deallocate_node(old);
        --_M_impl->_M_data._M_count;
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    auto RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_erase_range(iter_const first, iter_const last) USTL_NOEXCEPT -> size_type
    {
        if (first == last) {
            return 0;
        }

        size_type count = 0;
        for (; first != last; (void)++first, ++count) {
            NodePtr old = base::ustl_rbt_erase_and_rebalance(first._M_node, _M_end());
            _M_destory_elem(old->_M_data);
            _M_deallocate_node(old);
        }

        _M_impl->_M_data._M_count -= count;
        return count;
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    auto RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_lower_bound(NodePtr beg, NodePtr end, key_type const &key) USTL_NOEXCEPT -> iter_const
    {
        while (beg) {
            if (_M_compare_key(_M_extract_key(beg), key)) {
                beg = beg->right();
            }
            else {
                end = beg;
                beg = beg->left();
            }
        }

        return iter_const(end);
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    auto RBTreeBasic<Key, Val, KeyOfVal, Compare, Allocator>::
        _M_upper_bound(NodePtr beg, NodePtr end, key_type const &key) USTL_NOEXCEPT -> iter_const
    {
        while (beg) {
            if (_M_compare_key(key, _M_extract_key(beg))) {
                end = beg;
                beg = beg->left();
            }
            else {
                beg = beg->right();
            }
        }

        return iter_const(end);
    }

/**---------------------------------------- [RBTreeBasic] END --------------------------------------------*/


/**---------------------------------------- [RBTree] BEGIN --------------------------------------------*/
    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        insert_unique(const_reference val) -> pair<iter_mut, bool>
    {
        iter_mut pos = _M_emplace_unique(internal::utility::forward<value_type>(val));
        return pair<iter_mut, bool> {pos, pos != end()};
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        insert_unique(value_type &&val) -> pair<iter_mut, bool>
    {
        iter_mut pos = _M_emplace_unique(internal::utility::forward<value_type>(val));
        return pair<iter_mut, bool> {pos, pos != end()};
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        insert_multi(const_reference val) -> iter_mut
    { return _M_emplace_multi(internal::utility::forward<value_type>(val)); }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        insert_multi(value_type &&val) -> iter_mut
    { return _M_emplace_multi(internal::utility::forward<value_type>(val)); }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    void RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        erase_unique(iter_const pos) USTL_NOEXCEPT
    { _M_erase_aux(pos); }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        erase_multi(key_type const &key) USTL_NOEXCEPT -> size_type
    {
        pair<iter_const, iter_const> range = _M_equal_range(key);
        return _M_erase_range(range.first(), range.second());
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        erase_range(iter_const first, iter_const last) USTL_NOEXCEPT -> size_type
    { return _M_erase_range(first, last); }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        find(key_type const &__key) const USTL_NOEXCEPT -> iter_const
    {
        iter_const __beg = begin();
        iter_const __end = end();

        for (; __end != __beg; ++__beg) {
            key_type const &__itr_key = _S_get_key(__beg);

            if (_SCompare_key(__itr_key, __key)) {
                break;
            }
        }

        return __beg;
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        find(key_type const &__key) USTL_NOEXCEPT -> iter_mut 
    {
        iter_const cres = static_cast<ConstPtr>(this)->find(__key);
        return  cres._M_const_cast();
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        lower_bound(key_type const &__key) USTL_NOEXCEPT -> iter_mut
    {
        iter_const res = static_cast<ConstPtr>(this)->lower_bound(__key);
        return  res._M_const_cast();
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        upper_bound(key_type const &__key) USTL_NOEXCEPT -> iter_mut
    {
        iter_const res = static_cast<ConstPtr>(this)->upper_bound(__key);
        return  res._M_const_cast();
    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        lower_bound(key_type const &__key) const USTL_NOEXCEPT -> iter_const
    {

    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        upper_bound(key_type const &__key) const USTL_NOEXCEPT -> iter_const
    {

    }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        begin() USTL_NOEXCEPT -> iter_mut
    { return iter_mut(_M_left_most()); }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    USTL_ALWAYS_INLINE
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        end() USTL_NOEXCEPT -> iter_mut
    { return iter_mut(_M_end()); }


    template <typename Key, typename Val, typename KeyOfVal, typename Compare, typename Allocator>
    auto RBTree<Key, Val, KeyOfVal, Compare, Allocator>::
        operator=(Self const &) & -> Self &
    {
        return *this;
    }

/**---------------------------------------- [RBTree] END --------------------------------------------*/

} // namespace ustl::core::internal::container
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl