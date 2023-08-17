#ifndef __USTL_CORE_WRAPPER_RESULT_HPP__
#define __USTL_CORE_WRAPPER_RESULT_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif


namespace ustl
{
namespace core
{

    template <typename _Tp, typename _Err>
    struct result
    {
        typedef _Tp     elem_type;
        typedef _Err    error_type;

    public:
        explicit
        result(elem_type const &__item);

        explicit
        result(error_type const &__item);

        bool
        is_ok() const;

        bool
        is_err() const;

        elem_type &
        unwrap();
    };

} // namespace ustl::core
} // namespace ustl



#endif