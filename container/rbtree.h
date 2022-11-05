#ifndef __rbtree_h
#define __rbtree_h

#ifndef __debug_ustl
#include "ustl.h"
#include "iterator.h"
#include "memory.h"
#include "pair.h"
#include "rbtree_fwd.h"
#endif

#define __rbt_template_parameters                               \
    template <typename _Key, typename _Val, typename _KeyOfVal, \
              typename _Compare, typename _Alloc>

#define __rbt_action_scope \
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>

namespace ustl
{
    namespace internal_ustl
    {

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

            _Rbtree_Node() = default;

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

            static void
            _S_swap(_Node_ptr __l,
                    _Node_ptr __r) noexcept
            {
                value_type __tmp = __l->_M_value;
                __l->_M_value = __r->_M_value;
                __r->_M_value = __tmp;
            }

            static void
            _S_swap(_Rbt_node_base *__l,
                    _Rbt_node_base *__r) noexcept
            {
                _S_swap(static_cast<_Node_ptr>(__l),
                        static_cast<_Node_ptr>(__r));
            }
        };

        template <typename _Val, typename _Comp>
        struct rb_tree_Impl
        {
            _Comp _M_compare;
            _Rbt_header _M_header;

            void
            _M_move(rb_tree_Impl &__other)
            {
                _M_header._M_color = __other._M_header._M_color;
                _M_header._M_left = __other._M_header._M_left;
                _M_header._M_right = __other._M_header._M_right;
                _M_header._M_parent = __other._M_header._M_parent;
                _M_header._M_count = __other._M_header._M_count;
                _M_compare = __other._M_compare;
            }

            void
            _M_swap(rb_tree_Impl &__other)
            {
                rb_tree_Impl __tmp = *this;
                _M_move(__other);
                __other._M_move(__tmp);
            }
        };

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
                        construct_node(static_cast<_Node_ptr>(__tmp), forward(__v)...);
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

                template <typename... _Args>
                _Node_ptr
                construct_node(_Node_ptr __p, _Args &&...__a)
                {
                    return _Nallocator_type().construct(__p, forward(__a)...);
                }

                void
                destory_node(_Node_base_ptr __n) const noexcept
                {
                    _Node_base_ptr __p = __n->_M_parent;
                    if (__n == __p->_M_parent)
                        __p->_M_parent = __p->_M_left = __p->_M_right = 0;
                    else if (__n == __p->_M_right)
                        __p->_M_right = 0;
                    else if (__n == __p->_M_left)
                        __p->_M_left = 0;
                }

            private:
                size_t _M_count;
                _Node_base_ptr _M_head;
            };

            /**
             * @if reassginment, take all of tree node
             * don`t recyle root node
             */
            struct _rbt_recycle_reuse
            {
                _rbt_recycle_reuse(rb_tree &__t)
                    : _M_tree(__t),
                      _M_left_most(__t._M_left_most())
                {
                    if (_M_tree._M_data_plus->_M_header._M_parent)
                        _M_tree._M_data_plus->_M_header._M_reset();
                    else
                        _M_left_most = 0;
                }

                template <typename... _Args>
                _Node_ptr
                operator()(_Args &&...__a)
                {
                    _Node_ptr __ret = static_cast<_Node_ptr>(_M_extract());
                    if (0 == __ret)
                        __ret = (*_M_tree._M_node_pool)();
                    _M_tree._M_node_pool->construct_node(__ret, forward(__a)...);
                    return __ret;
                }

            private:
                _Node_base_ptr
                _M_extract()
                {
                    if (0 == _M_left_most)
                        return 0;

                    _Node_base_ptr __ret = _M_left_most;
                    _M_left_most = _M_left_most->_M_parent;
                    if (0 != _M_left_most)
                    {
                        if (_is_lchild(__ret))
                            _M_left_most->_M_left = 0;
                        else
                        {
                            _M_left_most->_M_right = 0;
                            while (_M_left_most->_M_right)
                                _M_left_most = _S_right(_M_left_most);
                            while (_M_left_most->_M_left)
                                _M_left_most = _S_left(_M_left_most);
                            if (_M_left_most->_M_right) // for leafs
                                _M_left_most = _S_right(_M_left_most);
                        }
                    }
                    else
                        _M_left_most = 0; /*ROOT*/
                    return __ret;
                }

                _Node_base_ptr _M_left_most;
                rb_tree &_M_tree;
            };

        protected:
            _Node_ptr
            _M_root() const noexcept
            {
                return static_cast<_Node_ptr>(_M_data_plus->_M_header._M_parent);
            }

            _Node_base_ptr
            _M_left_most() const noexcept
            {
                return _M_data_plus->_M_header._M_left;
            }

            _Node_base_ptr
            _M_right_most() const noexcept
            {
                return _M_data_plus->_M_header._M_right;
            }

            _Node_ptr
            _M_begin() const noexcept
            {
                return _M_root();
            }

            _Node_base_ptr
            _M_end() const noexcept
            {
                return &_M_data_plus->_M_header;
            }

            bool
            _M_compare_key(key_type const &__l,
                           key_type const &__r) const noexcept
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
#ifdef __debug_ustl
                _Node_ptr __tmp = static_cast<_Node_ptr>(__p);
                return _S_key(__tmp);
#endif
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
#else

#endif
            }

            rb_tree(const rb_tree &__other)
                : _M_data_plus(0)
            {
                clear();
                assign_equal(__other.begin(), __other.end());
            }

            rb_tree(rb_tree &&__other)
            {
                clear();
                _M_data_plus->_M_move(__other._M_data_plus);
            }

            ~rb_tree()
            {
                clear();
#ifdef __debug_ustl
                delete _M_data_plus;
                delete _M_node_pool;
#else

#endif
            }

            /**
             * @brief
             *      for public interface
             * @interface
             * @private
             */
        private:
            iterator
            _M_insert(_Node_base_ptr, value_type const &,
                      _rbt_recycle_reuse *);
            inline iterator
            _M_insert_equal(iterator, _rbt_recycle_reuse *);
            iterator
            _M_insert_equal(value_type const &, _rbt_recycle_reuse *);
            inline pair<iterator, bool>
            _M_insert_unique(iterator, _rbt_recycle_reuse *);
            pair<iterator, bool>
            _M_insert_unique(value_type const &, _rbt_recycle_reuse *);

            void
                _M_erase(iterator);

            iterator
            _M_get_insert_pos_unique(key_type const &) noexcept;
            iterator
            _M_get_insert_pos_equal(key_type const &) noexcept;

            iterator
            _M_lower_bound(_Node_base_ptr, _Node_base_ptr, key_type const &) const noexcept;

            iterator
            _M_upper_bound(_Node_base_ptr, _Node_base_ptr, key_type const &) const noexcept;

            /**
             * @brief
             *      provide to client
             * @interface
             * @public
             */
        public:
            template <typename _Itr>
            void
                assign_equal(_Itr, _Itr);
            template <typename _Itr>
            void
                assign_unique(_Itr, _Itr);

            inline pair<iterator, bool>
                insert_unique(iterator);

            inline iterator
                insert_equal(iterator);

            inline pair<iterator, bool>
            insert_unique(value_type const &);

            inline iterator
            insert_equal(value_type const &);

            iterator
                erase(iterator);
            iterator
                erase(iterator, iterator);
            size_t
            erase(key_type const &);

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

            inline void
            swap(rb_tree &) noexcept;

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

        __rbt_template_parameters typename __rbt_action_scope::iterator
        __rbt_action_scope::
            _M_insert(_Node_base_ptr __ist,
                      value_type const &__val,
                      _rbt_recycle_reuse *__node_reuse)
        {
            key_type const &__k = _KeyOfVal()(__val);
            // root insertion happen __is_left = false
            bool __is_left = (__ist == _M_end() || _M_compare_key(__k, _S_key(__ist)));
            _Node_ptr __new = __node_reuse
                                  ? (*__node_reuse)(__val)
                                  : (*_M_node_pool)(__val);
            _rbt_insert(__is_left, __new, __ist, &_M_data_plus->_M_header);
            ++_M_data_plus->_M_header._M_count;
            return iterator(__new);
        }

        __rbt_template_parameters void
        __rbt_action_scope::
            _M_erase(iterator __del)
        {
            _Node_base_ptr __val = _rbt_erase(__del._M_node, &_M_data_plus->_M_header);
            _Node_type::_S_swap(__val, __del._M_node);
            /// @bug if recycle, the itr of client taked is unknown
            /// if no recycle, the memory of heap unable to release
            (*_M_node_pool)(__val);
            --_M_data_plus->_M_header._M_count;
        }

        __rbt_template_parameters typename __rbt_action_scope::iterator
        __rbt_action_scope::
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
            /// @if result of comparsion is true, return __e
            /// @else return end()
            if (_M_compare_key(_S_key(__pre), __k))
                return iterator(__e);
            return end();
        }

        __rbt_template_parameters typename __rbt_action_scope::iterator
        __rbt_action_scope::
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

        __rbt_template_parameters typename __rbt_action_scope::iterator
        __rbt_action_scope::
            _M_lower_bound(_Node_base_ptr __s,
                           _Node_base_ptr __e,
                           key_type const &__k) const noexcept
        {
            while (__s)
            {
                // __k > __s, stroge the node that lower __k
                if (_M_compare_key(_S_key(__s), __k))
                    __s = _S_right(__s);
                // __k <= __s
                else
                    __e = __s, __s = _S_left(__s);
            }
            // return succursor or the node
            return iterator(__e);
        }

        __rbt_template_parameters typename __rbt_action_scope::iterator
        __rbt_action_scope::
            _M_upper_bound(_Node_base_ptr __s,
                           _Node_base_ptr __e,
                           key_type const &__k) const noexcept
        {
            while (__s)
            {
                // __k < __s
                if (_M_compare_key(__k, _S_key(__s)))
                    __e = __s, __s = _S_left(__s);
                // __k >= __s
                else
                    __s = _S_right(__s);
            }
            return iterator(__e);
        }

        __rbt_template_parameters typename __rbt_action_scope::iterator
        __rbt_action_scope::
            _M_insert_equal(value_type const &__val,
                            _rbt_recycle_reuse *__rcru)
        {
            key_type const &__key = _KeyOfVal()(__val);
            iterator __pos = _M_get_insert_pos_equal(__key);
            return iterator(_M_insert(__pos._M_node, __val, __rcru));
        }

        __rbt_template_parameters typename __rbt_action_scope::iterator
        __rbt_action_scope::
            _M_insert_equal(iterator __itr,
                            _rbt_recycle_reuse *__rcru)
        {
            value_type __val = *static_cast<_Node_ptr>(__itr._M_node)->_M_valptr();
            return iterator(_M_insert_equal(__val, __rcru));
        }

        __rbt_template_parameters pair<typename __rbt_action_scope::iterator, bool>
        __rbt_action_scope::
            _M_insert_unique(value_type const &__val,
                             _rbt_recycle_reuse *__rcru)
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
            return ret_type(_M_insert(__pos._M_node, __val, __rcru), true);
        }

        __rbt_template_parameters pair<typename __rbt_action_scope::iterator, bool>
        __rbt_action_scope::
            _M_insert_unique(iterator __itr,
                             _rbt_recycle_reuse *__rcru)
        {
            value_type __val = *static_cast<_Node_ptr>(__itr._M_node)->_M_valptr();
            return _M_insert_unique(__val, __rcru);
        }

        __rbt_template_parameters inline typename __rbt_action_scope::iterator
        __rbt_action_scope::
            insert_equal(value_type const &__val)
        {
            return _M_insert_equal(__val, 0);
        }

        __rbt_template_parameters inline pair<
            typename __rbt_action_scope::iterator, bool>
        __rbt_action_scope::
            insert_unique(value_type const &__itr)
        {
            return _M_insert_unique(__itr, 0);
        }

        __rbt_template_parameters inline typename __rbt_action_scope::iterator
        __rbt_action_scope::
            insert_equal(iterator __itr)
        {
            return _M_insert_equal(__itr, 0);
        }

        __rbt_template_parameters inline pair<
            typename __rbt_action_scope::iterator, bool>
        __rbt_action_scope::
            insert_unique(iterator __itr)
        {
            return _M_insert_unique(__itr, 0);
        }

        __rbt_template_parameters template <typename _Itr>
        void __rbt_action_scope::
            assign_equal(_Itr __b, _Itr __e)
        {
            _rbt_recycle_reuse __rcru(*this);
            while (__b != __e)
                _M_insert_equal(__b++, &__rcru);
        }

        __rbt_template_parameters template <typename _Itr>
        void
        __rbt_action_scope::
            assign_unique(_Itr __b, _Itr __e)
        {
            _rbt_recycle_reuse __rcru(*this);
            while (__b != __e)
                _M_insert_unique(__b++, &__rcru);
        }

        __rbt_template_parameters typename __rbt_action_scope ::iterator
        __rbt_action_scope::
            erase(iterator __begin, iterator __end)
        {
            if (begin() == __begin && end() == __end)
            {
                clear();
                return end();
            }
            else
            {
                while (__begin != __end)
                    _M_erase(__begin++);
                iterator __ret = __end;
                ++__ret;
                return __ret;
            }
        }

        /// @return return presurcor of node
        __rbt_template_parameters typename __rbt_action_scope::iterator
        __rbt_action_scope::
            erase(iterator __itr)
        {
            if (end() == __itr)
                return end();
            iterator __suc = __itr;
            ++__suc;
            _M_erase(__itr);
            return __suc;
        }

        __rbt_template_parameters size_t
        __rbt_action_scope::
            erase(key_type const &__key)
        {
            size_t __count = count();
            pair<iterator, iterator>
                __range = equal_range(__key);
            erase(__range._M_fisrt_val, __range._M_second_val);
            return __count - count();
        }

        __rbt_template_parameters typename __rbt_action_scope::iterator
        __rbt_action_scope::
            find(key_type const &__k) const noexcept
        {
            iterator __ret = lower_bound(__k);
            // check __k = key(__ret) or __k > key(__ret)
            if (end() != __ret || !_M_compare_key(__k, _S_key(__ret)))
                return __ret;
            return end();
        }

        __rbt_template_parameters typename __rbt_action_scope::iterator
        __rbt_action_scope::
            lower_bound(key_type const &__k) const noexcept
        {
            return _M_lower_bound(_M_root(), _M_end(), __k);
        }

        __rbt_template_parameters typename __rbt_action_scope::iterator
        __rbt_action_scope ::
            upper_bound(key_type const &__k) const noexcept
        {
            return _M_upper_bound(_M_root(), _M_end(), __k);
        }

        __rbt_template_parameters
            pair<typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator,
                 typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator>
            rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
                equal_range(key_type const &__k) const noexcept
        {
            typedef pair<iterator, iterator> ret_type;
            _Node_ptr __aim = _M_root();
            _Node_base_ptr __suc = _M_end();
            while (__aim)
            {
                // __k < key(__tmp), storage it`s succursor
                //  for which foreach using operator!=()
                if (_M_compare_key(__k, _S_key(__aim)))
                    __suc = __aim, __aim = _S_left(__aim);
                // __k > key(__tmp)
                else if (_M_compare_key(_S_key(__aim), __k))
                    __aim = _S_right(__aim);
                //  __k = key(__tmp)
                else
                {
                    // __begin storage lower key(__tmp)
                    return ret_type(_M_lower_bound(_S_left(__aim), __aim, __k),
                                    _M_upper_bound(_S_right(__aim), __suc, __k));
                }
            }
            /** if haven`t the node, return it`s logical succursor */
            return ret_type(iterator(__suc), iterator(__suc));
        }

        __rbt_template_parameters inline void
        __rbt_action_scope::
            swap(rb_tree &__other) noexcept
        {
            if (0 == _M_root())
            {
                if (0 != __other._M_root())
                    _M_data_plus->_M_move(__other._M_data_plus);
            }
            else if (0 == __other._M_root())
                __other._M_data_plus->_M_move(_M_data_plus);
            else
                _M_data_plus->_M_swap(__other._M_data_plus);
        }

        __rbt_template_parameters inline void
        __rbt_action_scope::
            clear()
        {
            _Node_base_ptr __parent;
            _Node_base_ptr __root = _M_left_most();
            while (__root && _M_end() != __root)
            {
                if (__root->_M_left)
                    __root = _S_left(__root);
                while (__root->_M_right)
                    __root = _S_right(__root);
                if (__root->_M_left)
                    __root = _S_left(__root);
                __parent = __root->_M_parent;
                _M_node_pool->destory_node(__root);
                (*_M_node_pool)(__root);
                __root = __parent;
            }
            _M_data_plus->_M_header._M_count = 0;
        }

        __rbt_template_parameters inline size_t
        __rbt_action_scope::
            count() const noexcept
        {
            return _M_data_plus->_M_header._M_count;
        }

        __rbt_template_parameters inline bool
        __rbt_action_scope::
            empty() const noexcept
        {
            return (0 == _M_data_plus->_M_header._M_count);
        }

        __rbt_template_parameters inline typename __rbt_action_scope::iterator
        __rbt_action_scope::
            begin() noexcept
        {
            return iterator(_M_left_most());
        }

        __rbt_template_parameters inline typename __rbt_action_scope::iterator
        __rbt_action_scope::
            end() noexcept
        {
            return iterator(&_M_data_plus->_M_header);
        }

        __rbt_template_parameters inline typename __rbt_action_scope::const_iterator
        __rbt_action_scope::
            cbegin() const noexcept
        {
            return const_iterator(_M_left_most());
        }

        __rbt_template_parameters inline typename __rbt_action_scope::const_iterator
        __rbt_action_scope::
            cend() const noexcept
        {
            return const_iterator(&_M_data_plus->_M_header);
        }
    }
}
#endif