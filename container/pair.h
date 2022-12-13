#ifndef __pair_h
#define __pair_h

namespace ustl
{
    template <typename _Tp1, typename _Tp2>
    class pair
    {
    public:
        typedef _Tp1 first_type;
        typedef _Tp2 second_type;

    private:
        void
        _M_copy(const pair &__other)
        {
            _M_fisrt_val = __other._M_fisrt_val;
            _M_second_val = __other._M_second_val;
        }

    public:
        constexpr pair() = default;

        constexpr pair(first_type const &__f, 
                       second_type const &__s)
            : _M_fisrt_val(__f),
              _M_second_val(__s) {}

        constexpr pair(pair const &__lval)
        { *this = __lval; }

        constexpr pair(pair &&__rval)
        { *this = ustl::move(__rval); }


        pair &
        operator=(pair const &__lval)
        { 
            _M_copy(__lval);
            return  *this;
        }


        pair &
        operator=(pair &&__rval)
        {
            _M_fisrt_val = ustl::move(__rval._M_fisrt_val);
            _M_second_val = ustl::move(__rval._M_second_val);
            return  *this;
        }


        void
        swap(pair &__other)
        {
            pair __tmp(__other);
            __other._M_copy(*this);
            _M_copy(__tmp);
        }


        second_type * 
        second_valptr(pair &__node)
        { return    &__node._M_second_val; }


        first_type * 
        first_valptr(pair&__node)
        { return    &__node._M_fisrt_val;  }



        first_type _M_fisrt_val;
        second_type _M_second_val;
    };

}

#endif