#ifndef __debug_ustl
#include "../ustl.h"
#include "../iterator/iterator.h"
#include "../allocator/memory.h"
#include "pair.h"

#endif

namespace ustl
{
    namespace internal_ustl
    {

#include "rbtree_fwd.h"

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

#ifdef __debug_ustl
            int _M_value;
#endif

            _Rbt_node_base()
                : _M_color(_Red)
            {
            }

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
                  _Rbt_node_base(this, this, 0) {}

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

#ifndef __debug_ustl
            value_type _M_value;
#endif
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
                :
#ifndef __debug_ustl
                  _M_value(__v),
#endif
                  _Rbt_node_base()
            {
#ifdef __debug_ustl
                this->_M_value = __v;
#endif
            }

            _Rbtree_Node(value_type __v, _Node_ptr __p)
                :
#ifndef __debug_ustl
                  _M_value(__v),
#endif
                  _Rbt_node_base(__p)
            {
#ifdef __debug_ustl
                this->_M_value = __v;
#endif
            }

            _Rbtree_Node(value_type __v, _Node_ptr __l,
                         _Node_ptr __r, _Node_ptr __p)
                :
#ifndef __debug_ustl
                  _M_value(__v),
#endif
                  _Rbt_node_base(__l, __r, __p)
            {
#ifdef __debug_ustl
                this->_M_value = __v;
#endif
            }
        };

        template <typename _Val, typename _Comp>
        struct rb_tree_Impl
        {
            _Comp _M_compare;
            _Rbt_header _M_header;
        };

        /// @brief find succursor of __p
        /// @param __p
        _Rbt_node_base *
        _rbt_increment(_Rbt_node_base *__p) noexcept
        {
            _Rbt_node_base::_Node_ptr __tmp;
            if (__p->_M_right)
            {
                __tmp = __p->_M_right;
                while (__tmp->_M_left)
                    __tmp = __tmp->_M_left;
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
            return __tmp;
        }

        /// @brief find presuccor of __p
        /// @param __p
        _Rbt_node_base *
        _rbt_decrement(_Rbt_node_base *__p) noexcept
        {
            _Rbt_node_base::_Node_ptr __tmp;
            if (__p->_M_left)
            {
                __tmp = __p->_M_left;
                while (__tmp->_M_right)
                    __tmp = __tmp->_M_right;
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
            return __tmp;
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
                _M_node = _rbt_decrement(_M_node);
                return *this;
            }

            _Self &
            operator++()
            {
                _M_node = _rbt_increment(_M_node);
                return *this;
            }

            _Self
            operator--(int)
            {
                _Self __tmp = *this;
                _M_node = _rbt_decrement(_M_node);
                return __tmp;
            }

            _Self
            operator++(int)
            {
                _Self __tmp = *this;
                _M_node = _rbt_increment(_M_node);
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
                _M_node = _rbt_increment(_M_node);
                return *this;
            }

            _Self &
            operator++()
            {
                _M_node = _rbt_decrement(_M_node);
                return *this;
            }

            _Self
            operator--(int)
            {
                _Self __tmp = *this;
                _M_node = _rbt_increment(_M_node);
                return __tmp;
            }

            _Self
            operator++(int)
            {
                _Self __tmp = *this;
                _M_node = _rbt_decrement(_M_node);
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
            using pointer = _Val *;
            using reference = _Val &;
            using compare_type = _Compare;
            using allocator_type = _Alloc;
            using difference_type = diff_t;

            using iterator = _rbtree_itertor<_Val>;
            using const_iterator = _const_rbtree_itertor<_Val>;
            using _Nallocator_type = typename _Alloc::template rebind<_Rbtree_Node<_Val>>::other;

        protected:
            using _Node_type = _Rbtree_Node<_Val>;
            using _Node_ptr = _Rbtree_Node<_Val> *;
            using _Node_base_ptr = _Rbt_node_base *;

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
                    _Node_base_ptr __tmp;
                    try
                    {

                        if (_M_count)
                        {
                            __tmp = _M_head;
                            _M_head = _M_head->_M_right;
                            _Nallocator_type().destory(static_cast<_Node_ptr>(__tmp));
                            --_M_count;
                        }
                        else
                            __tmp = _Nallocator_type().allocate(sizeof(_Node_type));
                        _Nallocator_type().construct(__tmp, forward(__v)...);
                    }
                    catch (...)
                    {
                        _Nallocator_type().deallocate(__tmp, sizeof(_Node_type));
                        throw;
                    }
                    return static_cast<_Node_ptr>(__tmp);
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
                        _Nallocator_type().deallocate(__n, sizeof(_Node_type));
                }

            private:
                size_t _M_count;
                _Node_base_ptr _M_head;
            };

        protected:
            _Node_ptr
            _M_root() noexcept
            {
                return static_cast<_Node_ptr>(_M_data_plus->_M_header._M_parent);
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

            _Node_ptr
            _M_begin() noexcept
            {
                return _M_root();
            }

            _Node_base_ptr
            _M_end() noexcept
            {
                return &_M_data_plus->_M_header;
            }

            bool _M_compare_key(key_type const &__l,
                                key_type const &__r) noexcept
            {
                return _M_data_plus->_M_compare(__l, __r);
            }

            _Node_ptr
            _M_extract(iterator &__itr) noexcept
            {
                return static_cast<_Node_ptr>(__itr._M_node);
            }

            _Node_ptr const
            _M_extract(const_iterator &__citr) noexcept
            {
                return static_cast<_Node_ptr const>(__citr._M_node);
            }

            static _Node_ptr
            _S_left(_Node_base_ptr __p) noexcept
            {
                return static_cast<_Node_ptr>(__p->_M_left);
            }

            static _Node_ptr
            _S_right(_Node_base_ptr __p) noexcept
            {
                return static_cast<_Node_ptr>(__p->_M_right);
            }

            static key_type const &
            _S_key(_Node_ptr __p)
            {
                return _KeyOfVal()(*(__p->_M_valptr()));
            }

            static key_type const &
            _S_key(_Node_base_ptr __p)
            {
                return _S_key(static_cast<_Node_ptr>(__p));
            }

            static key_type const &
            _S_key(iterator &__itr)
            {
                return _S_key(__itr._M_node);
            }

            static key_type const &
            _S_key(const_iterator &__itr)
            {
                return _S_key(__itr._M_node);
            }

#ifdef __debug_ustl
        public:
            using _node_ptr = _Node_ptr;
            _Node_ptr
            debug_root()
            {
                return static_cast<_Node_ptr>(_M_data_plus->_M_header._M_parent);
            }

#endif
        public:
            rb_tree()
                : _M_data_plus(0)
            {
#ifdef __debug_ustl
                _M_data_plus = new rb_tree_Impl<value_type, compare_type>;
                _M_node_pool = new _Node_Manager;
#endif
            }

            rb_tree(const rb_tree &__other)
                : _M_data_plus(0) {}

            rb_tree(rb_tree &&__other)
                : _M_data_plus(0) {}

        private:
            iterator
            _M_insert(_Node_base_ptr, value_type const &);

            iterator
            _M_erase(bool, _Node_base_ptr, key_type const &);

            iterator
            _M_get_insert_pos_unique(key_type const &) noexcept;
            iterator
            _M_get_insert_pos_equal(key_type const &) noexcept;

            iterator
            _M_lower_bound(_Node_ptr, _Node_ptr, key_type const &) const noexcept;

            iterator
            _M_upper_bound(_Node_ptr, _Node_ptr, key_type const &) const noexcept;

        public:
            iterator
            insert_equal(value_type const &);
            pair<iterator, bool>
            insert_unique(value_type const &);

            pair<iterator, iterator>
            erase_equal(key_type const &);
            iterator
            erase_unique(key_type const &);

            iterator
            find(key_type const &) const noexcept;
            iterator
            lower_bound(key_type const &) const noexcept;
            iterator
            upper_bound(key_type const &) const noexcept;
            pair<iterator, iterator>
            equal_range(key_type const &) const noexcept;

            void
            clear();

            inline size_t
            count() const noexcept;

            inline bool
            empty() const noexcept;

            inline iterator
            begin() noexcept;

            inline iterator
            end() noexcept;

            inline const_iterator
            cbegin() const noexcept;

            inline const_iterator
            cend() const noexcept;

        private:
            /** use implement pointer, isolation implement and interface */
            rb_tree_Impl<value_type, compare_type> *_M_data_plus;
            _Node_Manager *_M_node_pool;
        };

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            _M_insert(_Node_base_ptr __ist,
                      value_type const &__val)
        {
            key_type const &__k = _KeyOfVal()(__val);
            bool __is_left = (__ist == _M_end() || _M_compare_key(__k, _S_key(__ist)));
            _Node_ptr __new = (*_M_node_pool)(__val);
            _rbt_insert(__is_left, __new, __ist, &_M_data_plus->_M_header);
            ++_M_data_plus->_M_header._M_count;
            return iterator(__new);
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            _M_erase(bool __is_right,
                     _Node_base_ptr __del,
                     key_type const &)
        {
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            _M_get_insert_pos_unique(_Key const &__k) noexcept
        {
            _Node_ptr __s{_M_begin()};
            _Node_base_ptr __e{_M_end()};
            bool __comp{true};
            while (__s)
            {
                __e = __s;
                __comp = _M_compare_key(__k, _S_key(__s));
                __s = __comp ? _S_left(__s) : _S_right(__s);
            }

            _Node_ptr __pre = static_cast<_Node_ptr>(__e);
            // if go left one last time, the precursor of __e
            // must >= __k, so we should compare precursor of __e
            // and __k are equals, but wo must check __e is minimum
            // node before it, because the node of minimum don`t have
            // node of precursor
            if (__comp)
            {
                if (static_cast<_Node_ptr>(_M_left_most()) == __pre)
                    return iterator(__pre);
                __pre = static_cast<_Node_ptr>(_rbt_decrement(__pre));
            }
            // estimate the key(node of precursor) whether is equal to the __k
            /// @if result of comparsion == true
            /// @return __e
            /// @else
            /// @return end()
            if (_M_compare_key(_S_key(__pre), __k))
                return iterator(__e);
            return end();
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            _M_get_insert_pos_equal(_Key const &__k) noexcept
        {
            _Node_ptr __s{_M_begin()};
            _Node_base_ptr __e{_M_end()};
            bool __comp;
            while (__s)
            {
                __e = __s;
                __comp = _M_compare_key(__k, _S_key(__s));
                __s = __comp ? _S_left(__s) : _S_right(__s);
            }
            /// don`t estimate double key is equal, event if it happens,
            /// the result of found are correct
            return iterator(__e);
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            _M_lower_bound(_Node_ptr __s,
                           _Node_ptr __e,
                           key_type const &__k) const noexcept
        {
            while (__s)
            {
                // __s < __k
                if (_M_compare_key(_S_key(__s), __k))
                    __s = _S_right(__s);
                // __s >= __k
                else
                {
                    __e = __s;
                    __s = _S_left(__s);
                }
            }
            return iterator(__e);
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            _M_upper_bound(_Node_ptr __s,
                           _Node_ptr __e,
                           key_type const &__k) const noexcept
        {
            while (__e)
            {
                // __k < __p
                if (_M_compare_key(__k, _S_key(__e)))
                {
                    // find pre of __k
                    __s = __e;
                    __e = _S_left(__e);
                }
                // __k >= __p
                else
                    __e = _S_right(__e);
            }
            return iterator(__s);
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            insert_equal(value_type const &__val)
        {
            key_type const &__key = _KeyOfVal()(__val);
            iterator __pos = _M_get_insert_pos_equal(__key);
            return iterator(_M_insert(__pos._M_node, __val));
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        pair<typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator, bool>
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            insert_unique(value_type const &__val)
        {
            /// @if null != root && end() = pos
            ///     then : double key is equals
            /// @elseif null = root && end() = pos
            ///     then : root is null
            using ret_type = pair<iterator, bool>;
            key_type const &__key = _KeyOfVal()(__val);
            iterator __pos = _M_get_insert_pos_unique(__key);

            if (0 != _M_root() && end() == __pos)
                return ret_type(__pos, false);
            return ret_type(_M_insert(__pos._M_node, __val), true);
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        pair<typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator,
             typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator>
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            erase_equal(key_type const &__key)
        {
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            erase_unique(key_type const &__key)
        {
            // if (__del->_M_left)
            //     __del = _rbt_decrement(__del);
            // if (_Block == _Rbt_node_base::_S_color(__del))
            //     _rbt_rebalance_erase(__del, _rbt_bro_ptr(__del), __header);
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            find(_Key const &__k) const noexcept
        {
            iterator __ret = lower_bound(__k);
            // check __k = key(__ret) or __k > key(__ret)
            if (end() != __ret || !_M_compare_key(__k, _S_key(__ret)))
                return __ret;
            return end();
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            lower_bound(key_type const &) const noexcept
        {
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            upper_bound(key_type const &) const noexcept
        {
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        pair<typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator,
             typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator>
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            equal_range(key_type const &__k) const noexcept
        {
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        void
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            clear()
        {
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        inline size_t
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            count() const noexcept
        {
            return _M_data_plus->_M_header._M_count;
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        inline bool
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            empty() const noexcept
        {
            return (0 == _M_data_plus->_M_header._M_count);
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        inline typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            begin() noexcept
        {
            return iterator(_M_left_most());
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        inline typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            end() noexcept
        {
            return iterator(&_M_data_plus->_M_header);
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        inline typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::const_iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            cbegin() const noexcept
        {
            return const_iterator(_M_left_most());
        }

        template <typename _Key, typename _Val, typename _KeyOfVal,
                  typename _Compare, typename _Alloc>
        inline typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::const_iterator
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            cend() const noexcept
        {
            return const_iterator(&_M_data_plus->_M_header);
        }

        /**
         * @brief
         *  use non-template function to eliminate duplication caussed by templates
         */

        void
        _rbt_insert(bool __is_l, _Rbt_node_base *__new,
                    _Rbt_node_base *__ist,
                    _Rbt_header *__header) noexcept
        {
            if (__is_l)
            {
                if (__header->_M_parent)
                {
                    if (__ist == __header->_M_left)
                        __header->_M_left = __new;
                    __ist->_M_left = __new;
                }
                else
                {
                    __ist->_M_parent = __new;
                    __ist->_M_right = __ist->_M_left = __new;
                }
            }
            else
            {
                if (__ist == __header->_M_right)
                    __header->_M_right = __new;
                __ist->_M_right = __new;
            }
            __new->_M_parent = __ist;
            _rbt_recolor(__new, __header);
        }

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
                __h->_M_parent = __new;
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
                __h->_M_parent = __new;
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

        void
        _rbt_reblance_insert(_Rbt_node_base *__n,
                             _Rbt_node_base *__h) noexcept
        {
            typedef _Rbt_node_base *_Node_ptr;
            _Node_ptr __parent = __n->_M_parent;
            _Node_ptr __gparnet = __parent->_M_parent;
            __parent->_M_setcolor(_Block);
            __gparnet->_M_setcolor(_Red);
            if (__parent == __gparnet->_M_right)
            {
                if (__n != __parent->_M_right) // rl
                {
                    __n->_M_setcolor(_Block);
                    _rbt_rotate_right(__parent, __h);
                }
                _rbt_rotate_left(__gparnet, __h);
            }
            else
            {
                if (__n == __parent->_M_right) // lr
                {
                    __n->_M_setcolor(_Block);
                    _rbt_rotate_left(__parent, __h);
                }
                _rbt_rotate_right(__gparnet, __h);
            }
        }

        void
        _rbt_reblance_erase(_Rbt_node_base *__n,
                            _Rbt_node_base *__h) noexcept
        {
        }

        void
        _rbt_recolor(_Rbt_node_base *__n,
                     _Rbt_node_base *__h) noexcept
        {
            typedef _Rbt_node_base _Node;
            typedef _Rbt_node_base *_Node_ptr;

            if (__n == __h->_M_parent)
            {
                __n->_M_setcolor(_Block);
                return;
            }

            __n->_M_setcolor(_Red);
            _Node_ptr __p = __n->_M_parent;
            if (_Block == _Node::_S_color(__p))
                return;

            _Node_ptr __uncle = _rbt_bro_ptr(__p);
            if (_Red == _Node::_S_color(__uncle))
            {
                __uncle->_M_setcolor(_Block);
                __p->_M_setcolor(_Block);
                _rbt_recolor(__p->_M_parent, __h);
            }
            else
                _rbt_reblance_insert(__n, __h);
        }
    }
}
