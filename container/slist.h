#ifndef __ustl_single_list_h
#define __ustl_single_list_h

namespace ustl
{
    struct slist_node_basic
    {
        typedef slist_node_basic _base_type;
        typedef slist_node_basic *_base_ptr;

        void
        _M_hook(_base_ptr __last)
        {
            _M_next = __last->_M_next;
            __last->_M_next = this;
        }

        void
        _M_unhook(_base_ptr __last)
        {
            __last->_M_next = _M_next;
            _M_next = 0;
        }

        _base_ptr _M_next;
    };

    struct slist_header
        : slist_node_basic
    {
        typedef slist_header _Self;
        typedef slist_node_basic *_base_ptr;

        size_t
        _M_length()
        {
            return _M_count;
        }

        _base_ptr
        _M_front()
        {
            return _M_next;
        }

        _base_ptr
        _M_back()
        {
            return _M_last;
        }

        size_t _M_count;
        _base_ptr _M_last;
    };

    template <typename _Tp>
    struct slist_node
        : slist_node_basic
    {
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;

        pointer
        _M_valptr()
        {
            return &_M_value_field;
        }

        reference
        _M_value()
        {
            return _M_value_field;
        }

        static _base_ptr
        _M_next()
        {
            return _M_next;
        }

        value_type _M_value_field;
    };

    template <typename _Tp, typename _Alloc>
    struct slist_impl
        : _Alloc
    {
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;

        slist_header _M_header;
    };

    template <typename _Tp, typename _Alloc = ustl::allocator<_Tp>>
    class slist
    {
    public:
        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef _Tp const *const_pointer;
        typedef _Tp const &const_reference;
        typedef allocate_traits<_Alloc> alloc_traits;
        typedef typename alloc_traits::allocator_type allocator_type;

        typedef ustl::size_t size_type;
        typedef ustl::diff_t difference_type;
        typedef ustl::itr_traits<pointer> iterator_traits;
        typedef ustl::fwd_iterator<pointer> iterator;
        typedef ustl::fwd_iterator<const_pointer> const_iterator;

    private:
        typedef slist_node_basic *base_ptr;
        typedef slist_node<_Tp> node_type;
        typedef slist_node<_Tp> *node_ptr;
        typedef slist_impl<_Tp, _Alloc> impl_type;

    public:
        allocator_type &
        _M_get_allocator()
        {
            return _M_data_plus;
        }

        template <typename... _Args>
        base_ptr
        _M_create_node(_Args &&...__args)
        {
            base_ptr __new = alloc_traits::allocate(_M_get_allocator(), 1);
            return alloc_traits::construct(_M_get_allocator(),
                                           static_cast<node_ptr>(__new)->_M_valptr(),
                                           ustl::forward<_Args &&>(__args)...);
        }

        void
        _M_destory_node(base_ptr __p)
        {
            alloc_traits::destory(_M_get_allocator(),
                                  static_cast<node_ptr>(__p)->_M_valptr());
        }

        void
        _M_deallocate_node(base_ptr __p, size_type __n = 1)
        {
            alloc_traits::deallocate(_M_get_allocator(), __p, __n);
        }

        base_ptr
        _M_front() { return _M_data_plus._M_header._M_front(); }

        base_ptr
        _M_back() { return _M_data_plus._M_header._M_back(); }

        base_ptr
        _M_header() { return &_M_data_plus._M_header; }

        static base_ptr
        _S_next(base_ptr __p) { return __p->_M_next; }

    public:
        size_type
        size() { return _M_data_plus._M_header._M_length(); }

        reference
        front() { return *_M_front(); }

        reference
        back() { return *_M_back(); }

        iterator
        begin() { return iterator(_M_front();) }

        iterator
        end() { return iterator(_M_header()); }

        const_iterator
        begin() const { return const_iterator(_M_front()); }

        const_iterator
        end() const { return const_iterator(_M_header()); }

        const_iterator
        cbegin() { return const_iterator(_M_front()); }

        const_iterator
        cend() { return const_iterator(_M_back()); }

        const_iterator
        cbegin() const { return const_iterator(_M_front()); }

        const_iterator
        cend() const { return const_iterator(_M_back()); }

        bool
        empty() { return 0 == size(); }

    private:
        static void
        _M_transer_after(base_ptr __pos, base_ptr __ist)
        {
            __ist->_M_hook(__pos);
        }

        static void
        _M_transer_before(base_ptr __pos, base_ptr __ist)
        {
            __pos->_M_hook(__ist);
        }

        template <typename... _Args>
        void
        _M_transer_after_dis(const_iterator __pos, _Args &&...__a)
        {
            pointer __pos_ptr = const_cast<pointer>(__pos.base_iterator());
            pointer __ist = _M_create_node(ustl::forward<_Args &&>(__a)...);
            _M_transer_after(__pos_ptr, __ist);
        }

        template <typename... _Args>
        void
        _M_transer_before_dis(const_iterator __pos, _Args &&...__a)
        {
            pointer __pos_ptr = const_cast<pointer>(__pos.base_iterator());
            pointer __ist = _M_create_node(ustl::forward<_Args &&>(__a)...);
            _M_transer_before(__ist, __pos_ptr);
        }

    public:
        template <typename... _Args>
        void emplace(const_iterator, _Args &&...)
        {
            _M_transer_before_dis(__pos, ustl::forward<_Args &&>(__a)...);
        }

        template <typename... _Args>
        void emplace_back(_Args &&...)
        {
            _M_transer_before_dis(cend(), ustl::forward<_Args &&>(__a)...);
        }

        template <typename... _Args>
        void emplace_front(_Args &&...)
        {
            _M_transer_before(cbegin(), ustl::forward<_Args &&>(__a)...);
        }

    public:
        void assign(value_type const &, size_type);
        template <typename _ForwardIterator>
        void assign(_ForwardIterator, _ForwardIterator);

        void push_back(value_type const &);
        void push_front(value_type const &);

        iterator insert_after(const_iterator, value_type const &, size_type = 1);
        iterator insert_before(const_iterator, value_type const &, size_type = 1);
        template <typename _ForwardIterator>
        iterator insert(const_iterator, _ForwardIterator, _ForwardIterator);

        size_type replace(const_iterator, const_iterator, value_type const &);
        template <typename _ForwardIterator>
        size_type replace(const_iterator, const_iterator, _ForwardIterator, _ForwardIterator);

        void pop_back();
        void pop_front();

        void erase(const_iterator);
        void erase(const_iterator, const_iterator);

        void remove(const_iterator);
        template <typename _Predicate>
        void remove_if(_Predicate const &);

        void swap(slist &);
        void swap(slist &&);

        void reverse();

        void reserve();
        void resize(size_type);
        void resize(size_type, value_type const &);

        void merge(slist &);
        void merge(slist &&);

        void sort();
        template <typename _Predicate>
        void sort(_Predicate const &);

        void clear();

    protected:
        impl_type _M_data_plus;
    };

} // namespace ustl::slist

#endif