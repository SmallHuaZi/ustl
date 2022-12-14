#ifndef __type_base_h
#define __type_base_h

namespace ustl
{
   
    template <typename T, T v>
    struct type_base
    {
        typedef T value_type;
        typedef type_base<T, v> type;

        constexpr T
        operator()() { return v; }

        static constexpr T value = v;
    };

    template <bool v>
    struct boolean
        : public type_base<bool, v>
    {};

    typedef boolean<true> true_type;
    typedef boolean<false> false_type;

    template <bool v>
    using __bool_constant = ustl::boolean<v>; 


    template <typename _Tp>
    struct make_void
    {
        using type = void;
    };

    template <typename _Tp>
    using __uvoid_t = typename ustl::make_void<_Tp>::type;

} // namespace ustl


#endif