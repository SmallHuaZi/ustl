#ifndef __object_traits_h
#define __object_traits_h

namespace ustl
{

#define __ustl_is_exist(class_name, func_name) \
    ustl::_is_exist_##func_name()(class_name())

#define _is_exist(func_name)                          \
    struct _is_exist_##func_name                      \
    {                                                 \
        template <typename _U, auto = &_U::func_name> \
        struct _is_exist_helper;                      \
                                                      \
        template <typename _U>                        \
        constexpr bool                                \
        operator()(_is_exist_helper<_U> &)            \
        {                                             \
            return true;                              \
        }                                             \
                                                      \
        constexpr bool                                \
        operator()(...)                               \
        {                                             \
            return false;                             \
        }                                             \
    };

    _is_exist(push_back);
    _is_exist(push_front);
    _is_exist(emplace_back);
    _is_exist(emplace_front);
    _is_exist(emplace);
    _is_exist(insert);

} // namespace ustl

#endif