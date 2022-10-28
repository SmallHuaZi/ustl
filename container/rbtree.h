#ifndef __debug_ustl
#include "../ustl.h"
#include "../iterator/iterator.h"
#include "../allocator/memory.h"
#include "pair.h"

#endif

namespace ustl
{
    /**
     *                 left         right
     *            min<——————header ——————> max
     *                        |
     *                        |parent
     *                        |
     *                        V
     *                       root
     *
     *
     *
     */
    namespace internal_ustl
    {
        enum _color : unsigned long
        {
            _Block,
            _Red
        };

        enum _value : unsigned long
        {
            _lvalue,
            _rvalue
        };

        struct _Rbt_node_base
        {
            using _Node_color = _color;
            using _Node_ptr = _Rbt_node_base *;
            using _CNode_ptr = const _Rbt_node_base *;
            /**
             * take typedef or using to cover function overload
             */

            _Node_color _M_color;
            _Node_ptr _M_parent;
            _Node_ptr _M_left;
            _Node_ptr _M_right;

            _Rbt_node_base()
                : _M_color(_Red) {}

            _Rbt_node_base(_Node_ptr __p)
                : _M_parent(__p) {}

            _Rbt_node_base(_Node_ptr __l,
                           _Node_ptr __r, _Node_ptr __p)
                : _M_color(_Red), _M_left(__l),
                  _M_right(__r), _M_parent(__p) {}

            static _color
            _S_color(_Rbt_node_base *__p) noexcept
            {
                return __p ? __p->_M_color : _Block;
            }

            void
            _M_setcolor(_color __c) noexcept
            {
                if (this)
                    this->_M_color = __c;
            }

            static _Node_ptr
            maxnode(_Node_ptr __r) noexcept
            {
                while (__r->_M_right)
                    __r = __r->_M_right;
                return __r;
            }

            static _CNode_ptr
            maxnode(_CNode_ptr __r) noexcept
            {
                while (__r->_M_right)
                    __r = __r->_M_right;
                return __r;
            }

            static _Node_ptr
            minnode(_Node_ptr __r) noexcept
            {
                while (__r->_M_left)
                    __r = __r->_M_left;
                return __r;
            }

            static _CNode_ptr
            minnode(_CNode_ptr __r) noexcept
            {
                while (__r->_M_left)
                    __r = __r->_M_left;
                return __r;
            }
        };

        struct _Rbt_header
            : _Rbt_node_base
        {
            size_t _M_count;

            _Rbt_header()
                : _M_count(0),
                  _Rbt_node_base(this, this, this) {}

            _Rbt_header(_Node_ptr __l,
                        _Node_ptr __r, _Node_ptr __p, size_t __n)
                : _M_count(__n), _Rbt_node_base(__l, __r, __p) {}

            void _M_reset() noexcept
            {
                _M_count = 0;
                _M_parent = _M_left = _M_right = this;
            }

            _Node_ptr
            _S_Min_node() const noexcept
            {
                return this->_M_left;
            }

            _Node_ptr
            _S_Max_node() const noexcept
            {
                return this->_M_right;
            }
        };

        template <typename _Val>
        struct _Rbtree_Node
            : _Rbt_node_base
        {
            typedef _Val value_type;
            typedef _Rbtree_Node<_Val> *_Node_ptr;
            typedef const _Rbtree_Node<_Val> *_CNode_ptr;

            value_type _M_value;

            value_type *
            _M_valptr()
            {
                return &this->_M_value;
            }

            const value_type *
            _M_valptr() const
            {
                return &this->_M_value;
            }

            _Rbtree_Node()
                : _Rbtree_Node() {}

            _Rbtree_Node(value_type __v)
                : _M_value(__v), _Rbt_node_base() {}

            _Rbtree_Node(value_type __v, _Node_ptr __p)
                : _M_value(__v), _Rbt_node_base(__p) {}

            _Rbtree_Node(value_type __v, _Node_ptr __l,
                         _Node_ptr __r, _Node_ptr __p)
                : _M_value(__v), _Rbt_node_base(__l, __r, __p) {}
        };

        template <typename _Val, typename _Comp>
        struct _Rbtree_Impl
        {
            _Comp _M_compare;
            _Rbt_header _M_header;
        };

        /// @brief find first node that greater __p
        /// @param __p
        _Rbt_node_base::_Node_ptr
        _Rbt_increment(_Rbt_node_base::_Node_ptr __p) noexcept
        {
            _Rbt_node_base::_Node_ptr __tmp;
            if (__p->_M_right)
            {
                __tmp = __p->_M_right;
                while (__tmp->_M_left)
                    __tmp = __tmp->_M_left;
                return __tmp;
            }
            else
            {
                __tmp = __p->_M_parent;
                while (__p == __tmp->_M_right)
                {
                    __p = __tmp;
                    __tmp = __tmp->_M_parent;
                }
            }
            return 0;
        }

        /// @brief find first node that lesser __p
        /// @param __p
        _Rbt_node_base::_Node_ptr
        _Rbt_decrement(_Rbt_node_base::_Node_ptr __p) noexcept
        {

            _Rbt_node_base::_Node_ptr __tmp;
            if (__p->_M_left)
            {
                __tmp = __p->_M_left;
                while (__tmp->_M_right)
                    __tmp = __tmp->_M_right;
                return __tmp;
            }
            else
            {
                __tmp = __p->_M_parent;
                while (__p == __tmp->_M_left)
                {
                    __p = __tmp;
                    __tmp = __tmp->_M_parent;
                }
            }
            return 0;
        }

        template <typename _Tp>
        struct _rbtree_itertor
        {
            using value_type = _Tp;
            using pointer = _Tp *;
            using reference = _Tp &;

            using difference_type = ustl::diff_t;
            using itr_tag = _bothway_itertor;

            using _Self = _rbtree_itertor<_Tp>;
            using base_ptr = _Rbt_node_base::_Node_ptr;
            using _link_type = _Rbtree_Node<_Tp> *;

            _rbtree_itertor() = default;

            explicit _rbtree_itertor(base_ptr __p)
                : _M_node(__p) {}

            _rbtree_itertor(const _rbtree_itertor &__itr)
                : _M_node(__itr._M_node) {}

            _Self &
            operator--()
            {
                _M_node = _Rbt_increment(_M_node);
                return *this;
            }

            _Self &
            operator++()
            {
                _M_node = _Rbt_decrement(_M_node);
                return *this;
            }

            _Self
            operator--(int)
            {
                _Self __tmp = *this;
                _M_node = _Rbt_increment(_M_node);
                return __tmp;
            }

            _Self
            operator++(int)
            {
                _Self __tmp = *this;
                _M_node = _Rbt_decrement(_M_node);
                return __tmp;
            }

            reference
            operator*() const
            {
                return *static_cast<_link_type>(_M_node)->_M_valptr();
            }

            pointer
            operator->() const
            {
                return static_cast<_link_type>(_M_node)->_M_valptr();
            }

            friend bool
            operator==(const _Self &__l, const _Self &__r)
            {
                return __l._M_node == __r._M_node;
            }

            friend bool
            operator!=(const _Self &__l, const _Self &__r)
            {
                return __l._M_node != __r._M_node;
            }

            base_ptr _M_node;
        };

        template <typename _Tp>
        struct _const_rbtree_itertor
        {
            using value_type = _Tp const;
            using pointer = _Tp const *;
            using reference = _Tp const &;

            using difference_type = ustl::diff_t;
            using itr_tag = _bothway_itertor;

            using _Self = _const_rbtree_itertor<_Tp>;
            using base_ptr = _Rbt_node_base::_Node_ptr;
            using _link_type = _Rbtree_Node<_Tp> *;

            _const_rbtree_itertor() = default;

            explicit _const_rbtree_itertor(base_ptr __p)
                : _M_node(__p) {}

            _const_rbtree_itertor(_rbtree_itertor<_Tp> &__itr)
                : _M_node(__itr._M_node) {}

            _Self &
            operator--()
            {
                _M_node = _Rbt_increment(_M_node);
                return *this;
            }

            _Self &
            operator++()
            {
                _M_node = _Rbt_decrement(_M_node);
                return *this;
            }

            _Self
            operator--(int)
            {
                _Self __tmp = *this;
                _M_node = _Rbt_increment(_M_node);
                return __tmp;
            }

            _Self
            operator++(int)
            {
                _Self __tmp = *this;
                _M_node = _Rbt_decrement(_M_node);
                return __tmp;
            }

            reference
            operator*()
            {
                return *static_cast<_link_type>(_M_node)->_M_valptr();
            }

            pointer
            operator->()
            {
                return static_cast<_link_type>(_M_node)->_M_valptr();
            }

            friend bool
            operator==(const _Self &__l, const _Self &__r)
            {
                return __l._M_node == __r._M_node;
            }

            friend bool
            operator!=(const _Self &__l, const _Self &__r)
            {
                return __l._M_node != __r._M_node;
            }

            base_ptr _M_node;
        };

        /**
         *  @tparam _Key : key type
         *  @tparam _Val : stroge key and data
         *  @tparam _KeyOfVal : get key from KVpairs
         *  @tparam _Compare : compare key
         *  @tparam _Alloc : memory alloctor
         */
        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc = ustl::allocator<_Val>>
        class rb_tree
        {
        public:
            using key_type = _Key;
            using value_type = _Val;
            using compare_type = _Compare;
            using allocator_type = _Alloc;

            using _Node_type = _Rbtree_Node<_Val>;
            using _Node_ptr = _Rbtree_Node<_Val> *;
            using _Node_base_ptr = _Rbt_node_base *;
            using _Nallocator_type = typename _Alloc::rebind<_Rbtree_Node<_Val>>::other;

            using iterator = _rbtree_itertor<_Val>;
            using const_iterator = _const_rbtree_itertor<_Val>;

        private:
            /**
             * @brief preserve a pool of erasing node and it`s max capacity is 20,
             *      when pool is empty, using alloator alloction a new node to user
             */
            struct _Node_Manager
            {
                enum
                {
                    _MAX_COUNT = 20
                };

                template <typename... _Arg>
                _Node_ptr
                operator()(_Arg &&...__v)
                {
                    /** maybe new exception or constructor exception,
                     *  but it was decide by client, we just use try__catch to provied machine
                     */
                    _Node_ptr __tmp;
                    try
                    {

                        if (_M_count)
                        {
                            __tmp = _M_head;
                            _M_head = _M_head->_M_right;
                            allocator_type().destory(__tmp);
                            --_M_count;
                        }
                        else
                            __tmp = allocator_type().allocate();
                        allocator_type().construct(__tmp, forward(__v)...);
                    }
                    catch (...)
                    {
                        allocator_type().deallocate(__tmp, sizeof(_Node_type));
                        throw;
                    }
                    return __tmp;
                }

                void
                operator()(_Node_base_ptr __n) noexcept
                {
                    if (++_M_count <= 20)
                    {
                        __n->_M_right = _M_head;
                        _M_head = __n;
                    }
                    else
                        allocator_type().deallocate(__n, sizeof(_Node_type));
                }

            private:
                size_t _M_count;
                _Node_base_ptr _M_head;
            };

        private:
            _Node_base_ptr
            _M_root() noexcept
            {
                return _M_data_plus->_M_header._M_parent;
            }

            _Node_base_ptr
            _M_left_most() noexcept
            {
                return _M_data_plus->_M_header._M_left;
            }

            _Node_base_ptr
            _M_right_most() noexcept
            {
                return _M_data_plus->_M_header._M_right;
            }

            _Node_base_ptr
            _M_begin() noexcept
            {
                return _M_root();
            }

            _Node_base_ptr
            _M_end() noexcept
            {
                return _M_data_plus->_M_header;
            }

            bool _M_compare_key(key_type const &__l,
                                key_type const &__r) noexcept
            {
                return _M_data_plus->_M_compare(__l, __r);
            }

            _Node_ptr
            _M_extract(iterator &__itr) noexcept
            {
                return __itr._M_node;
            }

            static _Node_ptr &
            _S_left(_Node_base_ptr __p) noexcept
            {
                return static_cast<_Node_ptr>(__p->_M_left);
            }

            static _Node_ptr &
            _S_right(_Node_base_ptr __p) noexcept
            {
                return static_cast<_Node_ptr>(__p->_M_right);
            }

            static key_type &
            _S_key(_Node_ptr __p)
            {
                return _KeyOfVal()(*(__p->_M_valptr()));
            }

            static key_type const &
            _S_key(iterator &__itr)
            {
                return _KeyOfVal()(*_M_extract(__itr));
            }

            static key_type const &
            _S_key(const_iterator &__itr)
            {
                return _KeyOfVal()(*_M_extract(__itr));
            }

        private:
            iterator _M_insert_equal(bool, iterator &, _Node_ptr const);
            iterator _M_insert_unique(bool, iterator &, _Node_ptr const);

            iterator _M_erase_equal(key_type const &);
            iterator _M_erase_unique(key_type const &);

            iterator _M_lower_bound(key_type const &);
            iterator _M_upper_bound(key_type const &);

            iterator _M_get_insert_pos(key_type const &);

        public:
            iterator find(key_type const &) const noexcept;

        public:
            iterator
            insert_unique(key_type const &__k,
                          value_type const &__v)
            {
                _Node_ptr __new = (*_M_node_pool)(__v);
                iterator __pos = _M_get_insert_pos(__k);
                bool __is_right = _M_compare_key(_S_key(__new), __k);
                return _M_insert_unique(__is_right, __pos, __new);
            }

            iterator
            insert_equal(key_type const &__k,
                         value_type const &__v)
            {
                /**
                 * @bug there is a question of equal
                 */
                _Node_ptr __new = (*_M_node_pool)(__v);
                iterator __pos = _M_get_insert_pos(__k);
                bool __is_right = _M_compare_key(_S_key(__new), __k);
                return _M_insert_unique(__is_right, __pos, __new);
            }

            iterator
            erase_unique(key_type const &__k)
            {
                _M_erase_unique(__k);
            }

            iterator
            erase_equal(key_type const &__k)
            {
                _M_erase_equal(__k);
            }

            iterator
            begin() noexcept
            {
                return _rbtree_itertor(_M_left_most());
            }

            iterator
            end() noexcept
            {
                return _rbtree_itertor(_M_end());
            }

            const_iterator
            cbegin() const noexcept
            {
                return _const_rbtree_itertor(_M_left_most());
            }

            const_iterator
            cend() const noexcept
            {
                return _const_rbtree_itertor(_M_end());
            }

            size_t
            count() const noexcept
            {
                return _M_data_plus->_M_header._M_count;
            }

            iterator
            lower_bound(key_type const &__k) noexcept
            {
                return _M_lower_bound(__k);
            }

            iterator
            upper_bound(key_type const &__k) noexcept
            {
                return _M_upper_bound(__k);
            }

            pair<iterator, iterator>
            equal_range(key_type const &__k) noexcept
            {
                iterator __s = _M_lower_bound(__k);
                iterator __e = _M_upper_bound(__k);
                return pair(++__s, __e);
            }

        public:
            rb_tree()
                : _M_data_plus(0) {}

            rb_tree(const rb_tree &__other)
                : _M_data_plus(0) {}

            rb_tree(rb_tree &&__other)
                : _M_data_plus(0) {}

        private:
            /** use implement pointer, isolation implement and interface */
            _Rbtree_Impl<value_type, compare_type> *_M_data_plus;
            _Node_Manager *_M_node_pool;
        };

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            _M_lower_bound(key_type const &__k)
        {
            _Node_ptr __p = _M_end();
            _Node_ptr __s = _M_begin();
            while (__s)
            {
                if (_M_compare_key(__k, _S_key(__s)) ||
                    (!_M_compare_key(_S_key(__p), __k) &&
                     !_M_compare_key(__k, _S_key(__p))))
                {
                    __p = __s;
                    __s = _S_left(__s);
                }
                else
                    __s = _S_right(__s);
            }
            return iterator(__p);
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            _M_upper_bound(key_type const &__k)
        {
            _Node_ptr __s = _M_end();
            _Node_ptr __p = _M_begin();
            while (__p)
            {
                if (_M_compare_key(_S_key(__p), __k) ||
                    (!_M_compare_key(_S_key(__p), __k) &&
                     !_M_compare_key(__k, _S_key(__p))))
                    __p = _S_right(__p);
                else
                {
                    __s = __p;
                    __p = _S_left(__p);
                }
            }
            return iterator(__s);
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            find(_Key const &__k) const noexcept
        {
            iterator __ret = _M_lower_bound(__k);
            if (end() == __ret || _M_compare_key(_S_key(++__ret), __k) ||
                _M_compare_key(__k, _S_key(__ret)))
                return end();
            return __ret;
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            _M_insert_unique(bool __is_right,
                             typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator &__pos,
                             _Rbtree_Node<_Val> *const __node)
        {
            _Node_ptr __p = _M_extract(__pos);
            if (__is_right)
            {
                _S_right(__node) = _S_right(__p);
                _S_right(__p) = __node;
            }
            else
            {
                _S_left(__node) = _S_left(__p);
                _S_left(__p) = __node;
            }
            _rbt_reblance_insert(__node, _M_root());
            return iterator(__node);
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            _M_insert_equal(bool __is_right,
                            typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator &__pos,
                            _Rbtree_Node<_Val> *const __node)
        {
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            _M_erase_unique(_Key const &__k)
        {
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            _M_erase_equal(_Key const &__k)
        {
        }

        /**
         * @brief
         *  use non-template function to eliminate duplication caussed by templates
         */
        /// @brief 左旋操作
        /// @param __n 将要旋转的结点
        /// @param __h 红黑树header
        void
        _rbt_rotate_left(_Rbt_node_base *__n,
                         _Rbt_node_base *__h) noexcept
        {
            typedef _Rbt_node_base *_Node_ptr;
            _Node_ptr __parent = __n->_M_parent,
                      __new = __n->_M_right;
            __n->_M_parent = __new;
            __new->_M_parent = __parent;

            if (__new->_M_left)
                __new->_M_left->_M_parent = __n;

            if (__parent == __h)
                __h->_M_parent = __n;
            else if (__n == __parent->_M_left)
                __parent->_M_left = __new;
            else
                __parent->_M_right = __new;

            __n->_M_right = __new->_M_left;
            __new->_M_left = __n;
        }

        /// @brief 右旋操作
        /// @param __n 将要旋转的结点
        /// @param __h 根节点
        void
        _rbt_rotate_right(_Rbt_node_base *__n,
                          _Rbt_node_base *__h) noexcept
        {
            typedef _Rbt_node_base *_Node_ptr;
            _Node_ptr __parent = __n->_M_parent,
                      __new = __n->_M_left;
            __n->_M_parent = __new;
            __new->_M_parent = __parent;

            if (__new->_M_right)
                __new->_M_right->_M_parent = __n;

            if (__parent == __h)
                __h->_M_parent = __n;
            else if (__n == __parent->_M_left)
                __parent->_M_left = __new;
            else
                __parent->_M_right = __new;

            __n->_M_left = __new->_M_right;
            __new->_M_right = __n;
        }

        /// @bug 先不处理根节点
        inline _Rbt_node_base *
        _rbt_bro_ptr(_Rbt_node_base *__p) noexcept
        {
            _Rbt_node_base *__parent = __p->_M_parent;
            if (__p == __parent->_M_left)
                return __parent->_M_right;
            else
                return __parent->_M_left;
        }

        /// @brief
        /// @return return a pointer which point node that was recolor with red
        inline _Rbt_node_base *
        _rbt_recolor(_Rbt_node_base *__n,
                     _Rbt_node_base *__h) noexcept
        {
            _Rbt_node_base *__parent = __n->_M_parent;
            _Rbt_node_base *__grand_parent = __parent->_M_parent;
            _Rbt_node_base *__uncle = _rbt_bro_ptr(__parent);
            __uncle->_M_setcolor(_Block);
            __parent->_M_setcolor(_Block);
            __grand_parent->_M_setcolor(_Red);
            return __grand_parent;
        }

        void
        _rbt_reblance_insert(_Rbt_node_base *__n,
                             _Rbt_node_base *__h) noexcept
        {
            typedef _Rbt_node_base _Node;
            _Rbt_node_base *__p = __n->_M_parent;
            if (_Block == _Node::_S_color(__p))
                return;
            _Node *__uncle = _rbt_bro_ptr(__p);
            if (_Red == _Node::_S_color(__uncle))
            {
                __p = _rbt_recolor(__n, __h);
                _rbt_reblance_insert(__p, __h);
            }
            else
            {
            }
        }

        void
        _rbt_reblance_erase(_Rbt_node_base *__n,
                            _Rbt_node_base *__h) noexcept
        {
        }

    }
}
