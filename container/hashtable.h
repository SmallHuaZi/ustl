#ifndef __USTL_HASHTABLE_H
#define __USTL_HASHTABLE_H

#include "container/pair.h"
#include "container/avltree.h"
#include "container/slist.h"

#include "allocator/memory.h"
#include "include/ufunctor.h"
#include "include/uexception.h"



namespace ustl
{
    template <bool _Const>
    struct hashtable_iterator
    {

    };



    template <typename _Key, typename _Val, typename _Hash, typename _Alloc>
    struct hashtable_basic
    {

        enum    { __DEFAULT_HASH_FACTOR = 75 };
        enum    { __DEFAULT_TABLE_LENGTH = 16 };
        enum    { __DEFAULT_LIST_LIMIT = 16 };        
        enum    { __MAX_TABLE_SIZE = 2048 };

    protected:
        typedef     _Key            key_type;
        typedef     _Val            value_type;
        typedef     _Val &          reference;
        typedef     _Val *          pointer;
        typedef     _Val const &    const_reference;
        typedef     _Val const *    const_pointer;
        typedef     _Hash           hash_type;
        typedef     _Alloc          allcoator_type;


    protected:
        static constexpr float
        _S_require_factor()
        { return    float(__DEFAULT_HASH_FACTOR) / float(100);}

        bool
        _M_should_dilatation()
        { return     _M_data_plus._M_table_size * _S_require_factor() < _M_data_plus._M_key_count; }


    protected:
        struct extract_key
        {

        };

        typedef     ustl::list<ustl::pair<_Key, _Val>>       list_node;
        typedef     ustl::avl_tree<_Key, ustl::pair<_Key, _Val>, ustl::less_t<size_t>, extract_key, _Alloc>     tree_node;

        struct hashtable_bucket
        {
            hashtable_bucket()
                : _M_list_table(0), _M_size(0) {}

            union {
                list_node    *_M_list_table;
                tree_node    *_M_rbt_table;
            };
            size_t      _M_size;
        };

        typedef     ustl::pair<_Key, _Val>      node_type;
        typedef     ustl::pair<_Key, _Val> *    node_pointer;
        typedef     hashtable_bucket            bucket_type;
        typedef     hashtable_bucket *          bucket_pointer;

        static bucket_pointer
        _S_next(bucket_pointer __start, bucket_pointer  __finish)
        {
            while(__start != __finish && 0 == __start)
                ++__start;
            return  __start == __finish ? 0 :__start;
        }

        static bucket_pointer
        _S_last(bucket_pointer   __rstart, bucket_pointer __rfinish)
        {
            while(__rfinish != __rstart && 0 == __rstart)
                --__rstart;
            return  __rstart == __rfinish ? 0 : __rstart;
        }

        struct hashtable_impl
            : _Alloc,
             ustl::allocate_traits<_Alloc>::template rebind<bucket_type>::other,
             ustl::allocate_traits<_Alloc>::template rebind<list_node>::other,
             ustl::allocate_traits<_Alloc>::template rebind<tree_node>::other
        {

            void
            _M_swap(hashtable_impl &__other)
            {
                hashtable_impl  __tmp(*this);
                _M_move(__other);
                __other._M_move(__tmp);
            }

            void
            _M_move(hashtable_impl &__other)
            {
                _M_table    =   __other._M_table;
                _M_stroge_start = __other._M_stroge_start;
                _M_stroge_finish = __other._M_stroge_finish;

                _M_table_size = __other._M_table_size;
                _M_key_count = __other._M_key_count;
                _M_all_node = __other._M_all_node;

                __other._M_reset();
            }

            void
            _M_reset()
            {
                _M_table      = 0;
                _M_all_node   = 0;
                _M_key_count  = 0;
                _M_table_size = 0;
                _M_stroge_start  = 0;
                _M_stroge_finish = 0;
            }

            bucket_pointer        _M_table;
            bucket_pointer        _M_stroge_start;
            bucket_pointer        _M_stroge_finish;

            size_t               _M_table_size;
            size_t               _M_key_count;
            size_t               _M_all_node;

            hash_type            _M_hash;
        };  

        typedef     hashtable_impl              impl_type;


        typedef     typename allocate_traits<_Alloc>::template rebind<hashtable_bucket>::other  
                    _HashNode_allocator_type;
        typedef     typename allocate_traits<_Alloc>::template rebind<list_node>::other
                    list_node_allocator_type;
        typedef     typename allocate_traits<_Alloc>::template rebind<tree_node>::other
                    tree_node_allocator_type; 

        typedef     allocate_traits<_Alloc>     _KVPair_allocate_traits;
        typedef     allocate_traits<_HashNode_allocator_type> _HashNode_allocate_traits;
        typedef     allocate_traits<list_node_allocator_type>   _List_Node_allocate_traits;
        typedef     allocate_traits<tree_node_allocator_type>   _Tree_Node_allocate_traits;

        typedef     hashtable_iterator<false>   iterator;
        typedef     hashtable_iterator<true>    const_iterator;    


    public:
        allcoator_type &
        _M_get_kvp_allocator()
        { return    _M_data_plus; }

        _HashNode_allocator_type &
        _M_get_hn_allocator()
        { return    _M_data_plus; }

        list_node_allocator_type &
        _M_get_list_node_allocator_type()
        { return    _M_data_plus; }

        tree_node_allocator_type &
        _M_get_tree_node_allocator_type()
        { return    _M_data_plus; }

        node_pointer 
        _M_allocate_kvp()
        {
            return  _KVPair_allocate_traits::allocate(_M_data_plus, 1);
        }

        bucket_pointer 
        _M_allocate_bucket(size_t    __len)
        {
            return _HashNode_allocate_traits::allocate(_M_data_plus, __len);
        }

        list_node *
        _M_allocate_list_node(size_t    __len)
        {
            return _List_Node_allocate_traits::allocate(_M_data_plus, __len);
        }

        tree_node *
        _M_allocate_tree_node(size_t    __len)
        {
            return _Tree_Node_allocate_traits::allocate(_M_data_plus, __len);
        }

        void
        _M_deallocate_kvp(node_pointer  __p)
        {
            _KVPair_allocate_traits::deallocate(_M_get_kvp_allocator(), __p, 1);
        }

        void
        _M_deallocate_bucket(bucket_pointer   __table, size_t __len)
        {
            _HashNode_allocate_traits::deallocate(_M_get_hn_allocator(), __table, __len);
        }

        template<typename ..._Args>
        void
        _M_construct_kvp(node_pointer   __p, _Args &&...__init_args)
        {
            _KVPair_allocate_traits::construct(_M_data_plus, __p->second_valptr(), ustl::forward<_Args &&>(__init_args)...);
        }

        void
        _M_destory_kvp(node_pointer     __p)
        {
            _KVPair_allocate_traits::destory(_M_data_plus, __p->first_valptr());
            _KVPair_allocate_traits::destory(_M_data_plus, __p->second_valptr());
        }

        size_t
        _M_node_max_size()
        { 
            return    _HashNode_allocate_traits::max_size(_M_get_hn_allocator()); 
        }

        void
        _M_rehash(size_t = size_t(__DEFAULT_TABLE_LENGTH));

        void
        _M_default_initialize();

    public:
        size_t
        max_size()
        { return _KVPair_allocate_traits::max_size(_M_get_kvp_allocator()); }
    
    protected:
        hashtable_basic()
            : _M_data_plus()
        { _M_default_initialize(); }

    protected:

        impl_type   _M_data_plus;
    };


    template<typename _Key, typename _Val, typename _Hash, typename _Alloc>
    void
    hashtable_basic<_Key, _Val, _Hash, _Alloc>::
        _M_rehash(size_t __len)
    {
        size_t  __new_size  = (_M_data_plus._M_table_size << 1) + 1;
        if(__len > __new_size)
            __new_size = __len;

        if(__new_size > _M_node_max_size())
            __ustl_throw_array_length("hashtable::_M_rehash(): allocate length overflap");

        bucket_pointer __new_table = _M_allocate_bucket(__new_size);
        ustl::relocate_forward(_M_data_plus._M_table, 
                               _M_data_plus._M_table + _M_data_plus._M_table_size,
                               __new_table, _M_get_kvp_allocator());
        _M_deallocate_bucket(_M_data_plus._M_table, _M_data_plus._M_table_size);
        size_t  __offset_start  = _M_data_plus._M_table - _M_data_plus._M_stroge_start;
        size_t  __offset_finish = _M_data_plus._M_stroge_finish - _M_data_plus._M_table;

        _M_data_plus._M_table = __new_table;
        _M_data_plus._M_stroge_start  = __new_table + __offset_start;
        _M_data_plus._M_stroge_finish = __new_table + __offset_finish;
        _M_data_plus._M_table_size = __new_size;
    }



    template<typename _Key, typename _Val, typename _Hash, typename _Alloc>
    void
    hashtable_basic<_Key, _Val, _Hash, _Alloc>::
        _M_default_initialize()
    {
        bucket_pointer   __new_table = _M_allocate_bucket(size_t(__DEFAULT_TABLE_LENGTH));
        _M_data_plus._M_table = __new_table;
        _M_data_plus._M_table_size = size_t(__DEFAULT_TABLE_LENGTH);
        _M_data_plus._M_key_count = 0;
        _M_data_plus._M_all_node  = 0;
        _M_data_plus._M_stroge_start  = 0;
        _M_data_plus._M_stroge_finish = 0;
    }



    template <typename _Key, typename _Val, 
              typename _Hash  = ustl::hash<_Key>,
              typename _Comp  = ustl::less_t<decltype(ustl::hash<_Key>()())>,
              typename _Alloc = ustl::allocator<ustl::pair<_Key, _Val>>>
    class hashtable
        : hashtable_basic<_Key, _Val, _Hash, _Alloc>
    {

        typedef    hashtable_basic<_Key, _Val, _Hash, _Alloc>   _Base_type;

        typedef     typename _Base_type::impl_type           impl_type;
        typedef     typename _Base_type::node_type           node_type;
        typedef     typename _Base_type::node_pointer        node_pointer;
        typedef     typename _Base_type::bucket_type           hash_node;
        typedef     typename _Base_type::bucket_pointer       bucket_pointer;

    public:

        typedef     typename _Base_type::key_type             key_type;
        typedef     typename _Base_type::value_type           value_type;
        typedef     typename _Base_type::reference            reference;
        typedef     typename _Base_type::pointer              pointer;
        typedef     typename _Base_type::const_reference      const_reference;
        typedef     typename _Base_type::const_pointer        const_pointer;
        typedef     typename _Base_type::hash_type            hash_type;
        typedef     typename _Base_type::allcoator_type       allcoator_type;

        typedef     ustl::size_t        size_type;
        typedef     ustl::diff_t        difference_type;
        typedef     typename _Base_type::iterator             iterator;
        typedef     typename _Base_type::const_iterator       const_iterator;

        using   _Base_type::__MAX_TABLE_SIZE;
        using   _Base_type::__DEFAULT_HASH_FACTOR;
        using   _Base_type::__DEFAULT_TABLE_LENGTH;
        using   _Base_type::__DEFAULT_LIST_LIMIT;       


    private:
        using   _Base_type::_M_get_kvp_allocator;
        using   _Base_type::_M_get_hn_allocator;
        using   _Base_type::_M_allocate_kvp;
        using   _Base_type::_M_allocate_bucket;
        using   _Base_type::_M_deallocate_kvp;
        using   _Base_type::_M_deallocate_bucket;
        using   _Base_type::_M_construct_kvp;
        using   _Base_type::_M_destory_kvp;
        using   _Base_type::_M_node_max_size;
        using   _Base_type::_M_rehash;
        using   _Base_type::_M_default_initialize;
        using   _Base_type::_M_allocate_list_node;
        using   _Base_type::_M_allocate_tree_node;

        size_type
        _M_hash(key_type const &) ustl_cpp_noexcept;

        bucket_pointer
        _M_calculate_postion(key_type const &);

        iterator
        _M_insert_aux(key_type const &, value_type const &);

        template<typename _InputIterator>
        iterator
        _M_range_insert(_InputIterator, _InputIterator);


    public:
        iterator
        begin()
        { return    iterator(); }

        iterator
        end()
        { return    iterator(); }

        const_iterator
        begin() const
        { return    const_iterator(); }

        const_iterator
        end() const
        { return    const_iterator(); }

        const_iterator
        cbegin()
        { return    const_iterator(); }

        const_iterator
        cend()
        { return    const_iterator(); }

        const_iterator
        cbegin() const
        { return    const_iterator(); }

        const_iterator
        cend() const
        { return    const_iterator(); }

        size_type
        size()
        { return    _M_data_plus._M_all_node; }

        size_type
        size() const
        { return    _M_data_plus._M_all_node; }

    public:
        using   _Base_type::max_size;

        iterator
        insert_equal(key_type, value_type);

        iterator
        insert_unique(key_type, value_type);

        iterator
        erase(key_type);
    
        iterator
        erase(key_type, value_type);

        void 
        swap(hashtable &);

        void
        swap(hashtable &&);

        void
        resize(size_type);

        iterator
        find_first(key_type);

        iterator
        find_last(key_type);

        pair<iterator, iterator>
        find_all(key_type);

        reference
        operator[](key_type) ustl_cpp_noexcept;

        const_reference
        operator[](key_type) const ustl_cpp_noexcept;

        hashtable &
        operator=(hashtable const &);

        hashtable &
        operator=(hashtable &&);


    protected:
        using       _Base_type::_M_data_plus;

    };

    

} // namespace ustl

#endif