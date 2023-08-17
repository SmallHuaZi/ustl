#ifndef __USTL_CORE_INTERNAL_MATH_POW_HPP__
#define __USTL_CORE_INTERNAL_MATH_POW_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif
#include <ustl/core/internal/type_traits/tt_floating.hpp>

namespace ustl
{
namespace core
{
namespace internal
{
namespace math
{

    template <typename Number>
    Number
    pow(Number base, Number exp) USTL_NOEXCEPT
    {
        static_assert(!internal::type_traits::IsFloating<Number>::value,
                      "Template parameter 'Number' is not allowed to be a float. "
                      "Please use 'powf' to calculate powers of floating point numbers");

        Number result = 1;
        while (exp) {
            if (exp & 1) {
                result *= base;
            }

            exp >>= 1;
            base *= base;
        }

        return result;
    }

    long double
    powf(long double base, long double exp) USTL_NOEXCEPT;
    
} // namespace ustl::core::internal::math
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl


#endif