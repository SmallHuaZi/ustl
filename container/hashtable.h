#ifndef __hashtable_h
#define __hashtable_h

#include "container/pair.h"
#include "container/rbtree.h"
#include "container/slist.h"
#include "include/ustl_exception.h"
#include "include/ustl_functor.h"

#define __hashtable_template_paramter \
    template <typename _Key, typename _Val, typename _Hash, typename _Alloc>


namespace ustl
{

    template<typename _Key, typename _Val, typename _Hash, typename _Alloc>
    struct hashtable_basic
    {
        enum    { __DEFAULT_HASH_FACTOR = 75 };
        enum    { __DEFAULT_TABLE_LENGTH = 16 };
        enum    { __DEFAULT_LIST_LIMIT = 16 };        

        static constexpr float
        _S_require_factor()
        { return    float(__DEFAULT_HASH_FACTOR) / float(100);}

        bool
        _M_should_dilatation()
        { return     _M_data_plus._M_table_size * _S_require_factor() < _M_data_plus._M_key_count; }



        struct extract_value
        {

        };

        typedef     ustl::slist<ustl::pair<_Key, _Val>>       list_node;
        typedef     ustl::rb_tree<_Key, ustl::pair<_Key, _Val>, extract_value, ustl::less<size_t>, _Alloc>     tree_node;

        struct hashtable_node 
        {
            hashtable_node()
                : _M_list_table(0), _M_size(0) {}

            union {
                list_node    *_M_list_table;
                tree_node    *_M_rbt_table;
            };
            size_t      _M_size;
        };

        typedef     ustl::pair<_Key, _Val>      node_type;
        typedef     ustl::pair<_Key, _Val> *    node_pointer;
        typedef     hashtable_node              hash_node;
        typedef     hashtable_node *            hash_node_ptr;

        struct hashtable_impl
            : _Alloc,
             ustl::allocate_traits<_Alloc>::template rebind<hash_node>::other
        {

            void
            _M_swap(hashtable_impl &__other)
            {}

            void
            _M_move(hashtable_impl &__other)
            {}

            void
            _M_reset()
            {
                _M_table      = 0;
                _M_key_count  = 0;
                _M_table_size = 0;
            }

            hash_node_ptr        _M_table;
            size_t               _M_table_size;
            size_t               _M_key_count;
        };  

        typedef     hashtable_impl              impl_type;
  
        template<bool _Const>
        struct hashtable_iterator
        {

            typedef     hashtable_iterator  _Self;
            typedef     ustl::diff_t        difference_type;
            typedef     _Val                value_type;
            typedef     _Val *              pointer;
            typedef     _Val &              reference;
            typedef     _Val const *        const_pointer;
            typedef     _Val const &        const_reference;
            typedef     hashtable_iterator<false>       non_cv_iterator;

            typedef     typename list_node::iterator    list_iterator;
            typedef     typename tree_node::iterator    tree_iterator;

            non_cv_iterator
            _M_const_cast()
            { return non_cv_iterator(_M_data, _M_table); }

            _Self &
            operator++()
            {}

            _Self &
            operator--()
            {}

            _Self
            operator--(int)
            {}

            _Self
            operator++(int)
            {}

            _Self
            operator-(difference_type __step)
            {}

            _Self
            operator+(difference_type __step)
            {}

            typename ustl::if_else<_Const, const_reference, reference>::type
            operator*()
            {}

            typename ustl::if_else<_Const, const_pointer, pointer>::type
            operator->()
            {}

            hashtable_iterator(impl_type &__table)
                : _M_data_nodes(0), _M_table(__table) {}

            hashtable_iterator(hash_node_ptr __data, impl_type &__table)
                : _M_data_nodes(__data), _M_table(__table) {}


            union {
                list_iterator    _M_list_data;
                tree_iterator    _M_tree_data;
            };
            hash_node_ptr    _M_data_nodes;
            impl_type       &_M_table;
        };          

        typedef     _Key            key_type;
        typedef     _Val            value_type;
        typedef     _Val &          reference;
        typedef     _Val *          pointer;
        typedef     _Val const &    const_reference;
        typedef     _Val const *    const_pointer;
        typedef     _Hash           hash_type;
        typedef     _Alloc          allcoator_type;

        typedef     allocate_traits<_Alloc>     _KVPair_allocate_traits;
        typedef     typename allocate_traits<_Alloc>::template rebind<hashtable_node>::other  
                    _HashNode_allocator_type;
        typedef     allocate_traits<_HashNode_allocator_type> _HashNode_allocate_traits;

        typedef     hashtable_iterator<false>   iterator;
        typedef     hashtable_iterator<true>    const_iterator;    


public:

        allcoator_type &
        _M_get_kvp_allocator()
        { return    _M_data_plus; }

        _HashNode_allocator_type &
        _M_get_hn_allocator()
        { return    _M_data_plus; }

        node_pointer 
        _M_allocate_kvp()
        {
            return  _KVPair_allocate_traits::allocate(_M_data_plus, 1);
        }

        hashtable_node * 
        _M_allocate_hash_node(size_t    &__len)
        {
            return _HashNode_allocate_traits::allocate(_M_data_plus, __len);
        }

        void
        _M_deallocate_kvp(node_pointer  __p)
        {
            _KVPair_allocate_traits::deallocate(_M_get_kvp_allocator(), __p, 1);
        }

        void
        _M_deallocate_table(hash_node_ptr   __table, size_t __len)
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

        impl_type   _M_data_plus;
    };

    __hashtable_template_paramter
    void
    hashtable_basic<_Key, _Val, _Hash, _Alloc>::
        _M_rehash(size_t __len)
    {
        size_t  __new_size  = (_M_data_plus._M_table_size << 1) + 1;
        if(__len > __new_size)
            __new_size = __len;

        if(__new_size > _M_node_max_size())
            __ustl_throw_array_length("hashtable::_M_rehash(): allocate length overflap");

        hash_node_ptr __new_table = _M_allocate_hash_node(__new_size);
        ustl::relocate_forward(_M_data_plus._M_table, 
                               _M_data_plus._M_table + _M_data_plus._M_table_size,
                               __new_table, _M_get_kvp_allocator());
        _M_deallocate_table(_M_data_plus._M_table);
        _M_data_plus._M_table = __new_table;
    }

    __hashtable_template_paramter
    void
    hashtable_basic<_Key, _Val, _Hash, _Alloc>::
        _M_default_initialize()
    {
        hash_node_ptr   __new_table = _M_allocate_hash_node(size_t(__DEFAULT_TABLE_LENGTH));
        _M_data_plus._M_table = __new_table;
        _M_data_plus._M_table_size = size_t(__DEFAULT_TABLE_LENGTH);
        _M_data_plus._M_key_count = 0;
    }

    template <typename _Key, typename _Val, 
              typename _Hash = ustl::hash<ustl::pair<_Key, _Val>>,
              typename _Alloc = ustl::allocator<ustl::pair<_Key, _Val>>>
    class hashtable
        : hashtable_basic<_Key, _Val, _Hash, _Alloc>
    {

        typedef    hashtable_basic<_Key, _Val, _Hash, _Alloc>   _Base_type;

        typedef     typename _Base_type::impl_type           impl_type;
        typedef     typename _Base_type::node_type           node_type;
        typedef     typename _Base_type::node_pointer        node_pointer;

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
        
    private:

    public:
        using   _Base_type::max_size;

        iterator
        insert(key_type, value_type);

        iterator
        erase(key_type);
    
        iterator
        erase(key_type, value_type);

        void
        reserve(size_type);

        void 
        swap(hashtable &);

        void
        swap(hashtable &&);

        reference
        operator[](key_type) ustl_cpp_noexcept;

        const_reference
        operator[](key_type) const ustl_cpp_noexcept;

        hashtable &
        operator=(hashtable const &);

        hashtable &
        operator=(hashtable &&);



protected:
        using   _Base_type::_M_data_plus;

    };

    

} // namespace ustl

#endif