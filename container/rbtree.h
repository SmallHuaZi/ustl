#ifndef __rbtree_h
#define __rbtree_h

#include "container/rbtree_fwd.h"

#define __rbt_template_parameters                               \
    template <typename _Key, typename _Val, typename _KeyOfVal, \
              typename _Compare, typename _Alloc>

#define _rbt_type \
    rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>

namespace ustl
{
    template <typename _Val>
    struct _Rbtree_Node
        : _Rbt_node_base
    {
        typedef     _Val    value_type;
        typedef         _Rbtree_Node<_Val> *    _Node_ptr;
        typedef const   _Rbtree_Node<_Val> *    _CNode_ptr;

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
                _Node_ptr __r) ustl_cpp_noexcept
        {
            value_type __tmp = __l->_M_value;
            __l->_M_value = __r->_M_value;
            __r->_M_value = __tmp;
        }

        static void
        _S_swap(_Rbt_node_base *__l,
                _Rbt_node_base *__r) ustl_cpp_noexcept
        {
            _S_swap(static_cast<_Node_ptr>(__l),
                    static_cast<_Node_ptr>(__r));
        }
    };

    template <typename _Tp>
    struct _rbtree_itertor
    {
        using   value_type  =   _Tp;
        using   pointer     =   _Tp *;
        using   reference   =   _Tp &;

        using   itr_tag     = _bothway_iterator;
        using   difference_type =   ustl::diff_t;

        using   _Self       =   _rbtree_itertor<_Tp>;
        using   base_ptr    =   _Rbt_node_base::_Node_ptr;
        using   _link_type  =   _Rbtree_Node<_Tp> *;

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
        using itr_tag = _bothway_iterator;

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
     * @if reassginment, take all of tree node
     * don`t recyle root node
     */
    template <typename _Tp, typename _Alloc>
    struct _Rbt_node_pool
        : _Alloc::template rebind<_Rbtree_Node<_Tp>>::other
    {
        enum
        {
            __MAX_CAPACITY = 10
        };

        using base_ptr = _Rbt_node_base *;
        using value_type = _Rbtree_Node<_Tp>;
        using pointer = _Rbtree_Node<_Tp> *;
        using reference = _Rbtree_Node<_Tp> &;

        using _Base_type = typename _Alloc::
            template rebind<_Rbtree_Node<_Tp>>::other;

        using _Base_type::allocate;
        using _Base_type::construct;
        using _Base_type::deallocate;
        using _Base_type ::destory;

        template <typename... _Args>
        pointer
        operator()(_Args &&...__args)
        {
            /** maybe new exception or constructor exception,
             *  but it was decide by client, we just use try__catch to provied machine
             */
            base_ptr __tmp;
            try
            {

                if (_M_node_count)
                {
                    __tmp = _M_list_header;
                    _M_list_header = _M_list_header->_M_right;
                    destory(static_cast<pointer>(__tmp));
                    --_M_node_count;
                }
                else
                    __tmp = allocate(1);
                construct_node(static_cast<pointer>(__tmp),
                               forward<_Args>(__args)...);
            }
            catch (...)
            {
                deallocate(__tmp, 1);
                throw;
            }
            return static_cast<pointer>(__tmp);
        }

        void
        recycle_node(base_ptr __p)
        {
            if (++_M_node_count <= __MAX_CAPACITY)
            {
                __p->_M_right = _M_list_header;
                _M_list_header = __p;
                if (!_M_list_last)
                    _M_list_last = __p;
            }
            else
                deallocate(__p, 1);
        }

        template <typename... _Args>
        void
        construct_node(base_ptr __p, _Args &&...__a)
        {
            construct(static_cast<pointer>(__p)->_M_valptr(),
                      forward<_Args>(__a)...);
        }

        void
        destory_node(base_ptr __n)
        {
            base_ptr __p = __n->_M_parent;
            if (__n == __p->_M_parent)
                __p->_M_parent = __p->_M_left = __p->_M_right = 0;
            else if (__n == __p->_M_right)
                __p->_M_right = 0;
            else if (__n == __p->_M_left)
                __p->_M_left = 0;
        }

        void
        _M_move(_Rbt_node_pool &__other)
        {
            size_t __i = 0;
            base_ptr __tmp;
            for (; __i < __other._M_node_count; ++__i)
            {
                __tmp = __other._M_list_header;
                __other._M_list_header = __tmp->_M_right;
                recycle_node(__tmp);
            }
        }

        ~_Rbt_node_pool()
        {
            base_ptr __tmp;
            while (_M_list_header)
            {
                __tmp = _M_list_header;
                _M_list_header = _M_list_header->_M_right;
                deallocate(__tmp, 1);
            }
        }

        size_t _M_node_count;
        base_ptr _M_list_header;
        base_ptr _M_list_last;
    };

    template <typename _Val, typename _Alloc, typename _Comp>
    struct _rbt_impl
    {
        void
        _M_move(_rbt_impl &__other)
        {
            _M_compare = __other._M_compare;
            _M_header._M_color = __other._M_header._M_color;
            _M_header._M_left = __other._M_header._M_left;
            _M_header._M_right = __other._M_header._M_right;
            _M_header._M_parent = __other._M_header._M_parent;
            _M_header._M_count = __other._M_header._M_count;
        }

        void
        _M_swap(_rbt_impl &__other)
        {
            _rbt_impl __tmp = *this;
            _M_move(__other);
            __other._M_move(__tmp);
        }

        _Comp _M_compare;
        _Rbt_header _M_header;
        _Rbt_node_pool<_Val, _Alloc> _M_node_pool;
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
        using   key_type            =   _Key;
        using   value_type          =   _Val;
        using   pointer             =   _Val *;
        using   reference           =   _Val &;
        using   compare_type        =  _Compare;
        using   allocator_type      =   _Alloc;
        using   difference_type     =   diff_t;

        using   iterator            =   _rbtree_itertor<_Val>;
        using   const_iterator      =   _const_rbtree_itertor<_Val>;

    protected:
        using   _Node_type          =   _Rbtree_Node<_Val>;
        using   _Node_ptr           =   _Rbtree_Node<_Val> *;
        using   _Node_base_ptr      =   _Rbt_node_base *;

    private:
        /**
         * @brief preserve a pool of erasing node and it`s max capacity is 20,
         *      when pool is empty, using alloator alloction a new node to user
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

            ~_rbt_recycle_reuse()
            {
            }

            template <typename... _Args>
            _Node_ptr
            operator()(_Args &&...__a)
            {
                _Node_ptr __ret = static_cast<_Node_ptr>(_M_extract());
                if (0 == __ret)
                    __ret = _M_tree._M_create_node(forward<_Args>(__a)...);
                _M_tree._M_construct_node(__ret, forward<_Args>(__a)...);
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
        _M_root() const ustl_cpp_noexcept
        {
            return static_cast<_Node_ptr>(_M_data_plus->_M_header._M_parent);
        }

        _Node_base_ptr
        _M_left_most() const ustl_cpp_noexcept
        {
            return _M_data_plus->_M_header._M_left;
        }

        _Node_base_ptr
        _M_right_most() const ustl_cpp_noexcept
        {
            return _M_data_plus->_M_header._M_right;
        }

        _Node_ptr
        _M_begin() const ustl_cpp_noexcept
        {
            return _M_root();
        }

        _Node_base_ptr
        _M_end() const ustl_cpp_noexcept
        {
            return &_M_data_plus->_M_header;
        }

        bool
        _M_compare_key(key_type const &__l,
                       key_type const &__r) const ustl_cpp_noexcept
        {
            return _M_data_plus->_M_compare(__l, __r);
        }

        _Node_ptr
        _M_extract(iterator &__itr) ustl_cpp_noexcept
        {
            return static_cast<_Node_ptr>(__itr._M_node);
        }

        _Node_ptr const
        _M_extract(const_iterator &__citr) ustl_cpp_noexcept
        {
            return static_cast<_Node_ptr const>(__citr._M_node);
        }

        static _Node_ptr
        _S_left(_Node_base_ptr __p) ustl_cpp_noexcept
        {
            return static_cast<_Node_ptr>(__p->_M_left);
        }

        static _Node_ptr
        _S_right(_Node_base_ptr __p) ustl_cpp_noexcept
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

        template <typename... _Args>
        _Node_ptr
        _M_create_node(_Args &&...__a)
        {
            return (_M_data_plus->_M_node_pool)(forward<_Args &&>(__a)...);
        }

        template <typename... _Args>
        _Node_ptr
        _M_construct_node(_Node_base_ptr __p,
                          _Args &&...__a)
        {
            (_M_data_plus->_M_node_pool).construct_node(__p, forward<_Args>(__a)...);
            return static_cast<_Node_ptr>(__p);
        }

        void
        _M_destory_node(_Node_base_ptr __p)
        {
            (_M_data_plus->_M_node_pool).destory_node(__p);
        }

        void
        _M_deallocate_node(_Node_base_ptr __p)
        {
            (_M_data_plus->_M_node_pool).recycle_node(__p);
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
            _M_data_plus = new _rbt_impl<value_type, allocator_type, compare_type>;
#else

#endif
        }

        rb_tree(const rb_tree &__other)
            : _M_data_plus(0)
        {
            if (&__other == this)
                return;
            clear();
            assign_equal(__other.begin(), __other.end());
        }

        rb_tree(rb_tree &&__other)
        {
            if (&__other == this)
                return;
            clear();
            _M_data_plus->_M_move(__other._M_data_plus);
        }

        template <typename _Itr>
        rb_tree(_Itr __first, _Itr __last)
        {
            for (; __first != __last; ++__first)
                ;
        }

        ~rb_tree()
        {
            clear();
#ifdef __debug_ustl
            delete _M_data_plus;
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
        _M_insert(_Node_base_ptr, value_type const &, _rbt_recycle_reuse *);
        inline iterator
        _M_insert_equal(iterator, _rbt_recycle_reuse *);
        iterator
        _M_insert_equal(value_type const &, _rbt_recycle_reuse *);
        inline pair<iterator, bool>
        _M_insert_unique(iterator, _rbt_recycle_reuse *);
        pair<iterator, bool>
        _M_insert_unique(value_type const &, _rbt_recycle_reuse *);

        void _M_erase(iterator);

        iterator
        _M_get_insert_pos_unique(key_type const &) ustl_cpp_noexcept;
        iterator
        _M_get_insert_pos_equal(key_type const &) ustl_cpp_noexcept;

        iterator
        _M_lower_bound(_Node_base_ptr, _Node_base_ptr, key_type const &) const ustl_cpp_noexcept;

        iterator
        _M_upper_bound(_Node_base_ptr, _Node_base_ptr, key_type const &) const ustl_cpp_noexcept;

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

        template <typename... _Args>
        inline iterator 
        emplace_equal(_Args &&...);
        inline iterator 
        insert_equal(iterator);
        inline iterator 
        insert_equal(value_type const &);

        template <typename... _Args>
        inline iterator 
        emplace_unique(_Args &&...);
        inline pair<iterator, bool> 
        insert_unique(iterator);
        inline pair<iterator, bool> 
        insert_unique(value_type const &);

        iterator 
        erase(iterator);
        iterator 
        erase(iterator, iterator);
        size_t 
        erase(key_type const &);

        iterator 
        find(key_type const &) const ustl_cpp_noexcept;
        iterator 
        lower_bound(key_type const &) const ustl_cpp_noexcept;
        iterator 
        upper_bound(key_type const &) const ustl_cpp_noexcept;
        pair<iterator, iterator> 
        equal_range(key_type const &) const ustl_cpp_noexcept;

        void 
        clear();

        inline void 
        swap(rb_tree &) ustl_cpp_noexcept;

        inline size_t 
        count() const ustl_cpp_noexcept;

        inline bool 
        empty() const ustl_cpp_noexcept;

        inline iterator 
        begin() ustl_cpp_noexcept;
        inline iterator 
        end() ustl_cpp_noexcept;
        inline const_iterator 
        begin() const ustl_cpp_noexcept;
        inline const_iterator 
        end() const ustl_cpp_noexcept;

        inline const_iterator 
        cbegin() ustl_cpp_noexcept;
        inline const_iterator 
        cend() ustl_cpp_noexcept;
        inline const_iterator 
        cbegin() const ustl_cpp_noexcept;
        inline const_iterator cend() const ustl_cpp_noexcept;

        rb_tree &
        operator=(rb_tree const &);

        static inline _Node_ptr 
        root(rb_tree const &) ustl_cpp_noexcept;

    private:
        /** use implement pointer, isolation implement and interface */
        _rbt_impl<value_type, allocator_type, compare_type> *_M_data_plus;
    };

    __rbt_template_parameters 
    typename _rbt_type::iterator
    _rbt_type::
        _M_insert(_Node_base_ptr __ist,
                  value_type const &__val,
                  _rbt_recycle_reuse *__node_reuse)
    {
        key_type const &__k = _KeyOfVal()(__val);
        // root insertion happen __is_left = false
        bool __is_left = (__ist == _M_end() || _M_compare_key(__k, _S_key(__ist)));
        _Node_ptr __new = __node_reuse
                              ? (*__node_reuse)(__val)
                              : _M_create_node(__val);
        _rbt_insert(__is_left, __new, __ist, &_M_data_plus->_M_header);
        ++_M_data_plus->_M_header._M_count;
        return iterator(__new);
    }

    __rbt_template_parameters 
    void
    _rbt_type::
        _M_erase(iterator __del)
    {
        _Node_base_ptr __val = _rbt_erase(__del._M_node, &_M_data_plus->_M_header);
        _Node_type::_S_swap(__val, __del._M_node);
        /// @bug if recycle, the itr of client taked is unknown
        /// if no recycle, the memory of heap unable to release
        _M_deallocate_node(__val);
        --_M_data_plus->_M_header._M_count;
    }

    __rbt_template_parameters 
    typename _rbt_type::iterator
    _rbt_type::
        _M_get_insert_pos_unique(_Key const &__k) ustl_cpp_noexcept
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

    __rbt_template_parameters 
    typename _rbt_type::iterator
    _rbt_type::
        _M_get_insert_pos_equal(_Key const &__k) ustl_cpp_noexcept
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

    __rbt_template_parameters 
    typename _rbt_type::iterator
    _rbt_type::
        _M_lower_bound(_Node_base_ptr __s,
                       _Node_base_ptr __e,
                       key_type const &__k) const ustl_cpp_noexcept
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

    __rbt_template_parameters 
    typename _rbt_type::iterator
    _rbt_type::
        _M_upper_bound(_Node_base_ptr __s,
                       _Node_base_ptr __e,
                       key_type const &__k) const ustl_cpp_noexcept
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

    __rbt_template_parameters 
    typename _rbt_type::iterator
    _rbt_type::
        _M_insert_equal(value_type const &__val,
                        _rbt_recycle_reuse *__rcru)
    {
        key_type const &__key = _KeyOfVal()(__val);
        iterator __pos = _M_get_insert_pos_equal(__key);
        return iterator(_M_insert(__pos._M_node, __val, __rcru));
    }

    __rbt_template_parameters 
    typename _rbt_type::iterator
    _rbt_type::
        _M_insert_equal(iterator __itr,
                        _rbt_recycle_reuse *__rcru)
    {
        value_type __val = *static_cast<_Node_ptr>(__itr._M_node)->_M_valptr();
        return iterator(_M_insert_equal(__val, __rcru));
    }

    __rbt_template_parameters 
    pair<typename _rbt_type::iterator, bool>
    _rbt_type::
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

    __rbt_template_parameters 
    pair<typename _rbt_type::iterator, bool>
    _rbt_type::
        _M_insert_unique(iterator __itr,
                         _rbt_recycle_reuse *__rcru)
    {
        value_type __val = *static_cast<_Node_ptr>(__itr._M_node)->_M_valptr();
        return _M_insert_unique(__val, __rcru);
    }

    __rbt_template_parameters 
    template <typename... _Args>
    inline typename _rbt_type::iterator
    _rbt_type::
        emplace_equal(_Args &&...__a)
    {
        _Node_ptr __new = _M_create_node();
        _M_construct_node(__new, forward(__a)...);
        key_type __k = _S_key(__new);
        iterator __pos = _M_get_insert_pos_equal(__k);
        bool __is_left = (__pos == _M_end() || _M_compare_key(__k, _S_key(__pos)));
        _rbt_insert(__is_left, __new, __pos._M_node, &_M_data_plus->_M_header);
        return iterator(__new);
    }

    __rbt_template_parameters 
    inline typename _rbt_type::iterator
    _rbt_type::
        insert_equal(value_type const &__val)
    {
        return _M_insert_equal(__val, 0);
    }

    __rbt_template_parameters 
    inline pair<typename _rbt_type::iterator, bool>
    _rbt_type::
        insert_unique(value_type const &__itr)
    {
        return _M_insert_unique(__itr, 0);
    }

    __rbt_template_parameters 
    inline typename _rbt_type::iterator
    _rbt_type::
        insert_equal(iterator __itr)
    {
        return _M_insert_equal(__itr, 0);
    }

    __rbt_template_parameters inline pair<
    typename _rbt_type::iterator, bool>
    _rbt_type::
        insert_unique(iterator __itr)
    {
        return _M_insert_unique(__itr, 0);
    }

    __rbt_template_parameters 
    template <typename _Itr>
    void _rbt_type::
        assign_equal(_Itr __b, _Itr __e)
    {
        _rbt_recycle_reuse __rcru(*this);
        while (__b != __e)
            _M_insert_equal(__b++, &__rcru);
    }

    __rbt_template_parameters 
    template <typename _Itr>
    void
    _rbt_type::
        assign_unique(_Itr __b, _Itr __e)
    {
        _rbt_recycle_reuse __rcru(*this);
        while (__b != __e)
            _M_insert_unique(__b++, &__rcru);
    }

    __rbt_template_parameters 
    typename _rbt_type ::iterator
    _rbt_type::
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
    __rbt_template_parameters 
    typename _rbt_type::iterator
    _rbt_type::
        erase(iterator __itr)
    {
        if (end() == __itr)
            return end();
        iterator __suc = __itr;
        ++__suc;
        _M_erase(__itr);
        return __suc;
    }

    __rbt_template_parameters 
    size_t
    _rbt_type::
        erase(key_type const &__key)
    {
        size_t __count = count();
        pair<iterator, iterator>
            __range = equal_range(__key);
        erase(__range._M_fisrt_val, __range._M_second_val);
        return __count - count();
    }

    __rbt_template_parameters 
    typename _rbt_type::iterator
    _rbt_type::
        find(key_type const &__k) const ustl_cpp_noexcept
    {
        iterator __ret = lower_bound(__k);
        // check __k = key(__ret) or __k > key(__ret)
        if (end() != __ret || !_M_compare_key(__k, _S_key(__ret)))
            return __ret;
        return end();
    }

    __rbt_template_parameters 
    typename _rbt_type::iterator
    _rbt_type::
        lower_bound(key_type const &__k) const ustl_cpp_noexcept
    {
        return _M_lower_bound(_M_root(), _M_end(), __k);
    }

    __rbt_template_parameters 
    typename _rbt_type::iterator
    _rbt_type ::
        upper_bound(key_type const &__k) const ustl_cpp_noexcept
    {
        return _M_upper_bound(_M_root(), _M_end(), __k);
    }

    __rbt_template_parameters
        pair<typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator,
             typename rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::iterator>
        rb_tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc>::
            equal_range(key_type const &__k) const ustl_cpp_noexcept
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

    __rbt_template_parameters 
    inline void
    _rbt_type::
        swap(rb_tree &__other) ustl_cpp_noexcept
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

    __rbt_template_parameters 
    inline void
    _rbt_type::
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
            _M_destory_node(__root);
            _M_deallocate_node(__root);
            __root = __parent;
        }
        _M_data_plus->_M_header._M_count = 0;
    }

    __rbt_template_parameters 
    inline size_t
    _rbt_type::
        count() const ustl_cpp_noexcept
    {
        return _M_data_plus->_M_header._M_count;
    }

    __rbt_template_parameters 
    inline bool
    _rbt_type::
        empty() const ustl_cpp_noexcept
    {
        return (0 == _M_data_plus->_M_header._M_count);
    }

    __rbt_template_parameters 
    inline typename _rbt_type::iterator
    _rbt_type::
        begin() ustl_cpp_noexcept
    {
        return iterator(_M_left_most());
    }

    __rbt_template_parameters 
    inline typename _rbt_type::iterator
    _rbt_type::
        end() ustl_cpp_noexcept
    {
        return iterator(&_M_data_plus->_M_header);
    }

    __rbt_template_parameters 
    inline typename _rbt_type::const_iterator
    _rbt_type::
        begin() const ustl_cpp_noexcept
    {
        return const_iterator(_M_left_most());
    }

    __rbt_template_parameters 
    inline typename _rbt_type::const_iterator
    _rbt_type::
        end() const ustl_cpp_noexcept
    {
        return const_iterator(&_M_data_plus->_M_header);
    }
    __rbt_template_parameters 
    inline typename _rbt_type::const_iterator
    _rbt_type::
        cbegin() ustl_cpp_noexcept
    {
        return const_iterator(_M_left_most());
    }

    __rbt_template_parameters 
    inline typename _rbt_type::const_iterator
    _rbt_type::
        cend() ustl_cpp_noexcept
    {
        return const_iterator(&_M_data_plus->_M_header);
    }

    __rbt_template_parameters 
    inline typename _rbt_type::const_iterator
    _rbt_type::
        cbegin() const ustl_cpp_noexcept
    {
        return const_iterator(_M_left_most());
    }

    __rbt_template_parameters 
    inline typename _rbt_type::const_iterator
    _rbt_type::
        cend() const ustl_cpp_noexcept
    {
        return const_iterator(&_M_data_plus->_M_header);
    }

    __rbt_template_parameters 
    _rbt_type &
    _rbt_type::
    operator=(rb_tree const &__other)
    {
        if (&__other != this)
            assign_equal(__other);
        return *this;
    }

    __rbt_template_parameters 
    typename _rbt_type::_Node_ptr
    _rbt_type::
        root(rb_tree const &__other) ustl_cpp_noexcept
    {
        return static_cast<_Node_ptr>(__other._M_data_plus->_M_header._M_parent);
    }

    __rbt_template_parameters 
    bool
    operator==(_rbt_type const &__l,
               _rbt_type const &__r)
    {
        typedef typename _rbt_type::const_iterator iterator;

        iterator __frist = __l.begin();
        iterator __last = __l.end();
        iterator __frist1 = __r.begin();
        iterator __last1 = __r.end();

        while (__frist1 != __last1 && __frist != __last &&
               *__frist1 == *__frist)
            ++__frist1, ++__frist;
        return __frist1 == __last1 && __frist == __last;

#ifdef __tree_struct_equal
        typedef _Rbt_node_base *base_ptr;
        typedef _Rbtree_Node<_Val> *node_ptr;
        base_ptr __Lroot = _rbt_type::root(__l);
        base_ptr __Rroot = _rbt_type::root(__r);
        bool __is_go_back = false;
        bool __from_lchild = false;

        while (*static_cast<node_ptr>(__Lroot)->_M_valptr() ==
                   *static_cast<node_ptr>(__Rroot)->_M_valptr() &&
               0 != __Lroot && 0 != __Rroot)
        {
            base_ptr __parent = __Lroot->_M_parent;
            base_ptr __rparent = __Rroot->_M_parent;

            if (__Lroot == __parent->_M_left && __from_lchild)
                return true;

            if (__is_go_back)
            {
                if (__from_lchild)
                {
                    __Rroot = __Rroot->_M_right;
                    __Lroot = __Lroot->_M_right;
                    __is_go_back = false;
                }
                else
                {
                    if (__Lroot == __parent->_M_left)
                        __from_lchild = true;
                    __Lroot = __parent;
                    __Rroot = __rparent;
                }
            }
            else
            {
                if (__Lroot->_M_left)
                {
                    __Lroot = __Lroot->_M_left;
                    __Rroot = __Rroot->_M_left;
                }
                else if (__Lroot->_M_right)
                {
                    __Lroot = __Lroot->_M_right;
                    __Rroot = __Rroot->_M_right;
                }
                else
                {
                    if (__parent->_M_parent == __Lroot && !__from_lchild)
                        break;
                    __from_lchild = (__Lroot == __parent->_M_left ? true : false);
                    __is_go_back = true;
                    __Lroot = __parent;
                    __Rroot = __rparent;
                }
            }
        }
        return false;
#endif
    }
}
#endif