#ifndef __type_h
#define __type_h

namespace ustl
{
/**
 * @brief
 *      ustl::type tmp use either 'redefien type' or 'inherit',user can take @def 'RDEFTYPE'
 *      and @def 'INHERIT' to control which method is used
 *
 */
#define RDEFTYPE 0
#define INHERIT 1

    /* type infer */

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
    {
    };

    typedef boolean<true> true_type;
    typedef boolean<false> false_type;

    template <bool v>
    using __bool_constant = ustl::boolean<v>;

    /** double type is equals
     *  @if T == U
     *      is_same<T,U>()() = true
     *  @elseif
     *      is_same<T,U>()() = false
     *
     */
    template <typename T, typename U>
    struct is_same
        : false_type
    {
    };

    template <typename T>
    struct is_same<T, T>
        : true_type
    {
    };

    /** if - else
     *
     *
     */
    template <bool _Condition, typename _Then, typename _Else>
    struct if_else;

    template <typename _Then, typename _Else>
    struct if_else<true, _Then, _Else>
    {
        using type = _Then;
    };

    template <typename _Then, typename _Else>
    struct if_else<false, _Then, _Else>
    {
        using type = _Else;
    };

    /** while
     * @brief
     *      if you wanna get only result, you can
     *      @todo' typedef ' or @todo' inherit '
     * @
     *
     * @tparam _Action
     *   user should guarantee the _Action had members:
     *      __condition
     *      __next
     *      type
     *
     * @example
     *      template <int number, int step, int max>
     *      struct while_body
     *      {
     *          static constexpr bool __condtion = (number < max);
     *          typedef body<number, step, max> type;
     *          typedef body<number + step, step, max> __next;
     *
     *          constexpr int
     *          operator()() { return n;}
     *      };
     *      int __num = while_until<body<0, 1, 100>::__condtion, body<0, 1, 100>::__next>::type()();
     *      output __num -----> 100
     */
    template <bool _Condtion, typename _Action>
    struct while_until;

    template <typename _Action>
    struct while_until<true, _Action>
#if defined(INHERIT) && INHERIT
        : while_until<_Action::__next::__condtion,
                      typename _Action::__next>
    {
#elif defined(RDEFTYPE) && RDEFTYPE
    {
        typedef typename while_until<_Action::__next::__condtion,
                                     typename _Action::__next>::type
            type;
#endif
    };

    template <typename _Action>
    struct while_until<false, _Action>
    {
        typedef typename _Action::type type;
    };

/** type is what */
#define IS_WHAT(what, type) \
    template <>             \
    struct is_##what<type>  \
        : true_type         \
    {                       \
    };

/** partial specialization  */
#define IS_WHAT_PS(tpra, what, type) \
    template <typename tpra>         \
    struct is_##what<type>           \
        : true_type                  \
    {                                \
    };

    template <typename _Tp>
    struct is_integer
        : false_type
    {
    };
    IS_WHAT(integer, char)
    IS_WHAT(integer, short)
    IS_WHAT(integer, int)
    IS_WHAT(integer, long)
    IS_WHAT(integer, long long)

    template <typename _Tp>
    struct is_floating
        : false_type
    {
    };
    IS_WHAT(floating, float)
    IS_WHAT(floating, double)

    template <typename _Tp>
    struct is_pointer
        : false_type
    {
    };
    IS_WHAT_PS(_Tp, pointer, _Tp *)

    template <typename _Tp>
    struct is_reference
        : false_type
    {
    };
    IS_WHAT_PS(_Tp, reference, _Tp &)
    IS_WHAT_PS(_Tp, reference, _Tp &&)

    /** get type */
#define TYPEOF(stroge)           \
    template <typename _Tp>      \
    struct type_of<stroge _Tp>   \
    {                            \
        using type = stroge _Tp; \
    };

    template <typename _Tp>
    struct type_of
    {
        using type = _Tp;
    };
    TYPEOF(const)
    TYPEOF(volatile)

#define TYPE_RP(rp, symbol)      \
    template <typename _Tp>      \
    struct type_##rp             \
    {                            \
        using type = _Tp symbol; \
    };
    TYPE_RP(lvref, &)
    TYPE_RP(rvref, &&)
    TYPE_RP(ptr, *);

    /** control type display, void if default value  */
    template <bool, typename _Tp = void>
    struct enable_if
    {
    };

    template <typename _Tp>
    struct enable_if<true, _Tp>
    {
        using type = _Tp;
    };

    template <bool _Cond, typename _Tp>
    using enable_if_type = typename enable_if<_Cond, _Tp>::type;

    /** type */
    template <typename _Tp>
    struct type_idextity
    {
        using type = _Tp;
    };

    template <typename _Tp>
    struct remove_reference
    {
        using type = _Tp;
    };

    template <typename _Tp>
    struct remove_reference<_Tp &>
    {
        using type = _Tp;
    };

    template <typename _Tp>
    struct remove_reference<_Tp &&>
    {
        using type = _Tp;
    };

    template <typename _Tp>
    struct remove_cv
    {
        using type = _Tp;
    };

    template <typename _Tp>
    struct remove_cv<_Tp const>
    {
        using type = _Tp;
    };

    template <typename _Tp>
    struct remove_cv<_Tp const *>
    {
        using type = _Tp *;
    };

    template <typename _Tp>
    struct remove_cv<_Tp volatile>
    {
        using type = _Tp;
    };

    template <typename _Tp>
    struct remove_cv<_Tp volatile *>
    {
        using type = _Tp *;
    };

    template <typename _Tp>
    struct make_void
    {
        using type = void;
    };

    template <typename _Tp>
    using __uvoid_t = typename ustl::make_void<_Tp>::type;

    template <typename _Tp>
    _Tp
    __decl_value();

    template <typename _Tp, typename _Up, typename = void>
    struct __is_assign
        : ustl::false_type
    {
    };

    template <typename _Tp, typename _Up>
    struct __is_assign<_Tp, _Up,
                       ustl::__uvoid_t<decltype(__decl_value<_Tp>() = __decl_value<_Up>())>>
        : ustl::true_type
#ifdef __debug_ustl
        ,
          type_idextity<typename remove_reference<_Up>::type>
#endif
    {
    };

    template <typename _Tp, typename _Up, typename = void>
    struct __is_copy_assign
        : ustl::false_type
    {
    };

    template <typename _Tp, typename _Up>
    struct __is_copy_assign<_Tp, _Up,
                            ustl::__uvoid_t<decltype(__decl_value<_Tp &>() = __decl_value<_Up const &>())>>
        : ustl::true_type
#ifdef __debug_ustl
        ,
          type_idextity<decltype(__decl_value<_Up const &>())>
#endif
    {
    };

    template <typename _Tp, typename _Up, typename = void>
    struct __is_move_assign
        : ustl::false_type
    {
    };

    template <typename _Tp, typename _Up>
    struct __is_move_assign<_Tp, _Up,
                            ustl::__uvoid_t<decltype(__decl_value<_Tp &>() = __decl_value<_Up &&>())>>
        : ustl::true_type
#ifdef __debug_ustl
        ,
          type_idextity<decltype(__decl_value<_Up &&>())>
#endif
    {
    };
}
#endif