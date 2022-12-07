#ifndef __ustl_map_h
#define __ustl_map_h

namespace ustl
{

    template<typename _Key, typename _Val, typename _Comp, 
             typename _Alloc = ustl::allocator<ustl::pair<_Key, _Val>>>
    class map
    {        
        struct compare_t
        {
            bool
            operator()(_Val __l, _Val __r)
            {
                return  __cmp(__l, __r);
            }

            compare_t() = default;

            compare_t(_Comp __comp)
                : __cmp(__comp) {}

        private:
            _Comp   __cmp;
        };

        struct extract_value
        {
            _Val &
            operator()(ustl::pair<_Key, _Val> __node)
            {
                return __node._M_second_val;
            }
        };  

        typedef     ustl::pair<_Key, _Val>      storage_type;
        typedef     ustl::rb_tree<_Key, _Val, compare_t, extract_value, _Alloc>  impl_type;

      

    public:
        typedef     _Key            key_type;
        typedef     _Val            value_type;
        typedef     _Val *          pointer;
        typedef     _Val &          reference;
        typedef     _Val const *    const_pointer;
        typedef     _Val const &    const_reference;
        typedef     _Comp           compare_type;
        typedef     _Alloc          allocator_type;
    
        typedef     typename impl_type::iterator        iterator;
        typedef     typename impl_type::const_iterator  const_iterator;

    public:
        iterator
        insert(key_type, value_type);

        iterator
        emplace(key_type, value_type);

        iterator
        erase(key_type);

        reference 
        operator[](key_type const &);

        const_reference
        operator[](key_type const &) const;

    private:
        impl_type       _M_data_plus;

    };

} // namespace ustl


#endif