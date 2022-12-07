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

        typedef     _Key            key_type;
        typedef     _Val            value_type;
        typedef     _Val &          reference;
        typedef     _Val *          pointer;
        typedef     _Val const &    const_reference;
        typedef     _Val const *    const_pointer;
        typedef     _Hash           hash_type;
        typedef     _Alloc          allcoator_type;

        enum    { __DEFAULT_HASH_FACTOR = 75 };
        enum    { __DEFAULT_TABLE_LENGTH = 16 };
        enum    { __DEFAULT_LIST_LIMIT = 16 };        
        enum    { __MAX_TABLE_SIZE = 2048 };


        static constexpr float
        _S_require_factor()
        { return    float(__DEFAULT_HASH_FACTOR) / float(100);}

        bool
        _M_should_dilatation()
        { return     _M_data_plus._M_table_size * _S_require_factor() < _M_data_plus._M_key_count; }



        struct extract_value
        {

        };

        typedef     ustl::list<ustl::pair<_Key, _Val>>       list_node;
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

        static hash_node_ptr
        _S_next(hash_node_ptr __start, hash_node_ptr  __finish)
        {
            while(__start != __finish && 0 == __start)
                ++__start;
            return  __start == __finish ? 0 :__start;
        }

        static hash_node_ptr
        _S_last(hash_node_ptr   __rstart, hash_node_ptr __rfinish)
        {
            while(__rfinish != __rstart && 0 == __rstart)
                --__rstart;
            return  __rstart == __rfinish ? 0 : __rstart;
        }

        struct hashtable_impl
            : _Alloc,
             ustl::allocate_traits<_Alloc>::template rebind<hash_node>::other
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

            hash_node_ptr        _M_table;
            hash_node_ptr        _M_stroge_start;
            hash_node_ptr        _M_stroge_finish;

            size_t               _M_table_size;
            size_t               _M_key_count;
            size_t               _M_all_node;

            hash_type            _M_hash;
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
            { return non_cv_iterator(_M_data_nodes, _M_table); }

            _Self &
            operator++()
            { return  _M_inc(); }

            _Self &
            operator--()
            { return  _M_dec(); }

            _Self
            operator--(int)
            {
                _Self __tmp(*this);
                _M_dec();
                return  __tmp;
            }

            _Self
            operator++(int)
            {
                _Self  __tmp(*this);
                _M_inc();
                return  __tmp;
            }

            _Self
            operator-(difference_type __step)
            {
                _Self   __tmp(*this);
                if(__step > 0)
                {
                    for(; __step; --__step)
                        __tmp._M_dec();
                }
                else   
                    __tmp + (-__step);
                return  __tmp;
            }

            _Self
            operator+(difference_type __step)
            {
                _Self   __tmp(*this);
                if(__step > 0)
                {
                    for(; __step; --__step)
                        __tmp._M_dec();
                }
                else   
                    __tmp - (-__step);
                return  __tmp;
            }

            typename ustl::if_else<_Const, const_reference, reference>::type
            operator*()
            {
                if(size_t(__DEFAULT_LIST_LIMIT) <  _M_data_nodes->_M_size)
                    return  (*_M_tree_data)._M_second_val;
                else
                    return  (*_M_list_data)._M_second_val;
            }

            typename ustl::if_else<_Const, const_pointer, pointer>::type
            operator->()
            {
                if(size_t(__DEFAULT_LIST_LIMIT) <  _M_data_nodes->_M_size)
                    return  (*_M_tree_data).second_valptr();
                else
                    return  (*_M_list_data).second_valptr();
            }

            _Self & 
            _M_inc()
            {
                if(size_t(__DEFAULT_LIST_LIMIT) <  _M_data_nodes->_M_size)
                {                    
                    if(_M_tree_data == _M_data_nodes->_M_rbt_table->end())
                    {
                        _M_data_nodes = _S_next(_M_data_nodes, _M_table._M_stroge_end);
                        _M_relocate(true);
                    }
                    else
                        ++_M_tree_data;
                }
                else
                {
                    if(_M_list_data == _M_data_nodes->_M_list_table->end())
                    {
                        _M_data_nodes = _S_next(_M_data_nodes, _M_table._M_stroge_end);
                        _M_relocate(true);
                    }
                    else
                        ++_M_list_data;

                }
                return *this;
            }

            _Self & 
            _M_dec()
            {
                if(size_t(__DEFAULT_LIST_LIMIT) < _M_data_nodes->_M_size)
                {
                    if(_M_tree_data == _M_data_nodes->_M_rbt_table->begin())
                    {
                        _M_data_nodes = _S_last(_M_data_nodes, _M_table._M_table - 1);
                        _M_relocate(false);
                    }
                    else
                        --_M_tree_data;
                }
                else
                {
                    if(_M_list_data == _M_data_nodes->_M_list_table->begin())
                    {
                        _M_data_nodes = _S_last(_M_data_nodes, _M_table._M_table - 1);
                        _M_relocate(false);
                    }
                    else
                        --_M_list_data;
                }
                return *this;
            }

            void
            _M_relocate(bool    __inc)
            {
                if(_M_data_nodes)
                {
                    if(size_t(__DEFAULT_LIST_LIMIT) < _M_data_nodes->_M_size)               
                    {
                        if(__inc)
                            _M_tree_data = _M_data_nodes->_M_rbt_table->begin();
                        else
                        {
                            _M_tree_data = _M_data_nodes->_M_rbt_table->end();
                            --_M_tree_data;
                        }
                    }
                    else
                    {
                        if(__inc)
                            _M_list_data = _M_data_nodes->_M_list_table->begin();                
                        else
                        {
                            _M_list_data = _M_data_nodes->_M_list_table->end();
                            --_M_list_data;
                        }

                    }
                }
            }

            hashtable_iterator(impl_type &__table)
                : _M_data_nodes(0), _M_table(__table) {}

            hashtable_iterator(hash_node_ptr __data, impl_type &__table)
                : _M_data_nodes(__data), _M_table(__table) 
            { _M_relocate(); }


            union {
                list_iterator    _M_list_data;
                tree_iterator    _M_tree_data;
            };
            hash_node_ptr    _M_data_nodes;
            impl_type       &_M_table;
        };          


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
        size_t  __offset_start  = _M_data_plus._M_table - _M_data_plus._M_stroge_start;
        size_t  __offset_finish = _M_data_plus._M_stroge_finish - _M_data_plus._M_table;

        _M_data_plus._M_table = __new_table;
        _M_data_plus._M_stroge_start  = __new_table + __offset_start;
        _M_data_plus._M_stroge_finish = __new_table + __offset_finish;
        _M_data_plus._M_table_size = __new_size;
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
        _M_data_plus._M_all_node  = 0;
        _M_data_plus._M_stroge_start  = 0;
        _M_data_plus._M_stroge_finish = 0;
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

        size_type
        _M_hash(key_type const &) ustl_cpp_noexcept;

        iterator
        _M_insert_aux(key_type const &, value_type const &);

    public:
        iterator
        begin()
        { return    iterator(_M_data_plus._M_stroge_start, _M_data_plus); }

        iterator
        end()
        { return    iterator(0, _M_data_plus); }

        const_iterator
        begin() const
        { return    const_iterator(_M_data_plus._M_stroge_start, _M_data_plus); }

        const_iterator
        end() const
        { return    const_iterator(0, _M_data_plus); }

        const_iterator
        cbegin()
        { return    const_iterator(_M_data_plus._M_stroge_start, _M_data_plus); }

        const_iterator
        cend()
        { return    const_iterator(0, _M_data_plus); }

        const_iterator
        cbegin() const
        { return    const_iterator(_M_data_plus._M_stroge_start, _M_data_plus); }

        const_iterator
        cend() const
        { return    const_iterator(0, _M_data_plus); }

        size_type
        size()
        { return    _M_data_plus._M_all_node; }

        size_type
        size() const
        { return    _M_data_plus._M_all_node; }

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

    __hashtable_template_paramter
    size_t
    hashtable<_Key, _Val, _Hash, _Alloc>::
        _M_hash(key_type const  &__key) ustl_cpp_noexcept
    {
        return  _M_data_plus._M_hash(__key) % size_type(__MAX_TABLE_SIZE);
    }

    __hashtable_template_paramter
    auto
    hashtable<_Key, _Val, _Hash, _Alloc>::
        _M_insert_aux(key_type const &__key, value_type const &__val) -> iterator
    {
        size_t  __hash_value = _M_hash(__key);
        if(__hash_value > _M_data_plus._M_table_size)
            _M_rehash(__hash_value);
        hash_node_ptr   __pos = _M_data_plus._M_table + __hash_value;

    }

    

} // namespace ustl

#endif