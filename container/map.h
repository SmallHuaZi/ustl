#ifndef __USTL_MAP_H
#define __USTL_MAP_H

#include "allocator/memory.h"
#include "algorithm/math.h"
#include "container/rbtree.h"

namespace ustl
{

    template<typename _Key, typename _Val, typename _Comp = ustl::less_t<_Key>, 
             typename _Alloc = ustl::allocator<ustl::pair<_Key, _Val>>>
    class map
    {        
        struct compare_t
        {
            bool
            operator()(_Val __l, _Val __r) const 
    #ifdef ustl_cpp_noexcept
            noexcept(noexcept(__cmp(__l, __r)))
    #endif
            { return  __cmp(__l, __r); }


        public:
            compare_t(_Comp __comp)
                : __cmp(__comp) {}

        private:
            _Comp   __cmp;
        };

        struct extract_key
        {
            _Val &
            operator()(ustl::pair<_Key, _Val> __node) ustl_cpp_noexcept
            { return __node._M_fisrt_val; }
        };  

        typedef     ustl::pair<_Key, _Val>      storage_type;
        typedef     ustl::rb_tree<_Key, _Val, compare_t, extract_key, _Alloc>  impl_type;
      

    public:
        typedef     _Key                key_type;
        typedef     _Val                value_type;
        typedef     _Val *              pointer;
        typedef     _Val &              reference;
        typedef     _Val const *        const_pointer;
        typedef     _Val const &        const_reference;
        typedef     _Comp               compare_type;
        typedef     _Alloc              allocator_type;
    
        typedef     typename impl_type::size_type                       size_type;
        typedef     typename impl_type::difference_type                 difference_type;
        typedef     typename impl_type::iterator                        iterator;
        typedef     typename impl_type::const_iterator                  const_iterator;
        typedef     typename impl_type::reverse_iterator                reverse_iterator;
        typedef     typename impl_type::const_reverse_iterator          const_reverse_iterator;

    
    public:
        iterator
        begin()             ustl_cpp_noexcept
        { return    _M_data_plus.begin(); }

        iterator
        end()               ustl_cpp_noexcept
        { return    _M_data_plus.end(); }

        const_iterator
        begin()     const   ustl_cpp_noexcept
        { return    _M_data_plus.begin(); }

        const_iterator
        end()       const   ustl_cpp_noexcept
        { return    _M_data_plus.end(); }

        const_iterator
        cbegin()            ustl_cpp_noexcept
        { return    _M_data_plus.cbegin(); }

        const_iterator
        cend()              ustl_cpp_noexcept
        { return    _M_data_plus.cend(); }

        const_iterator
        cbegin()     const  ustl_cpp_noexcept
        { return    _M_data_plus.cbegin(); }

        const_iterator
        cend()       const  ustl_cpp_noexcept
        { return    _M_data_plus.cend(); }

        reverse_iterator
        rbegin()            ustl_cpp_noexcept
        { return    _M_data_plus.rbegin(); }

        reverse_iterator
        rend()              ustl_cpp_noexcept
        { return    _M_data_plus.rend(); }

        const_reverse_iterator
        rbegin()    const   ustl_cpp_noexcept
        { return    _M_data_plus.rbegin(); }

        const_reverse_iterator
        rend()      const   ustl_cpp_noexcept
        { return    _M_data_plus.rend(); }

        const_reverse_iterator
        crbegin()    const  ustl_cpp_noexcept
        { return    _M_data_plus.crbegin(); }

        const_reverse_iterator
        crend()      const  ustl_cpp_noexcept
        { return    _M_data_plus.crend(); }

        size_type
        size()       const  ustl_cpp_noexcept
        { return    _M_data_plus.count(); }

        void
        swap(map &__other)  ustl_cpp_noexcept
        { _M_data_plus.swap(__other._M_data_plus); }

        void
        swap(map &&__rother)ustl_cpp_noexcept
        { _M_data_plus.swap(ustl::move(__rother._M_data_plus)); }

        iterator
        insert(value_type const &__lval)
        { return    _M_data_plus.insert_unique(__lval); }

        iterator
        insert(value_type &&__rval)
        { return    _M_data_plus.insert_unique(ustl::move(__rval)); }

        iterator
        erase(key_type const &__key)
        { return    _M_data_plus.erase(__key); }

        iterator
        find(key_type const &__key)                 ustl_cpp_noexcept
        { return    _M_data_plus.find(__key); }

        const_iterator
        find(key_type const &__key)         const   ustl_cpp_noexcept
        { return    _M_data_plus.find(__key); }

        iterator
        lower_bound(key_type const &__key)  const   ustl_cpp_noexcept
        { return    _M_data_plus.lower_bound(__key); }

        iterator
        upper_bound(key_type const &__key)  const   ustl_cpp_noexcept
        { return    _M_data_plus.upper_bound(__key); }

        ustl::pair<iterator, iterator>
        equal_range(key_type const &__key)  const   ustl_cpp_noexcept
        { return    _M_data_plus.equal_range(__key); }

        bool
        contains(key_type const &__key)     const   ustl_cpp_noexcept
        { return    _M_data_plus.find(__key) != _M_data_plus.end(); }

        void
        clear()
        { _M_data_plus.clear(); }


    public:
        template <typename _InputIterator>
        insert(_InputIterator __first, _InputIterator __last);

        iterator
        insert(const_iterator __pos, value_type const &__val);

        template <typename ..._Args>
        iterator
        emplace(const_iterator __pos, _Args &&...__init_args);

        template <typename ..._Args>
        iterator
        emplace(key_type const &__key, _Args &&...__init_args);

        size_type
        erase();

        reference 
        operator[](key_type const &);

        const_reference
        operator[](key_type const &) const;


    private:
        impl_type       _M_data_plus;
    };

} // namespace ustl


#endif