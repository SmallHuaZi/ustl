#ifndef __hashtable_h
#define __hashtable_h

namespace ustl
{

    template <typename _Key, typename _Val, typename _Alloc>
    struct hashtable_impl
        : _Alloc
    {
    };

    template <typename _Val>
    struct hashtable_iterator
    {
    };

    template <typename _Val>
    struct hashtable_const_iterator
    {
        /* data */
    };

    template <typename _Key, typename _Comp>
    struct hashtable_compare
    {
        bool
        operator()(_Key __l, _Key __r)
        {
            return _M_compare(__l, __r);
        }

    protected:
        _Comp _M_compare;
    };

    template <typename _Key, typename _Val, typename _Comp,
              typename _KeyOfVal, typename _Alloc>
    class hashtable
    {

    protected:
        typedef hashtable_impl<_Key, _Val, _Alloc> impl_type;
        typedef hashtable_compare<_Key, _Comp> compare_type;

        impl_type *_M_data_plus;
        compare_type _M_compare;
    };

} // namespace ustl

#endif