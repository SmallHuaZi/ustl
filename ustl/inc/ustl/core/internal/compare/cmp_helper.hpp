#ifndef __USTL_CORE_INTERNAL_COMPARE_HELPER_HPP__
#define __USTL_CORE_INTERNAL_COMPARE_HELPER_HPP__

#ifndef __USTL_CORE_INTERNAL_COMPARE_ORDERING_HPP__
#include <ustl/core/internal/compare/cmp_ordering.hpp>
#endif

#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_OPERATOR_HPP__
#include <ustl/core/internal/type_traits/tt_operator.hpp>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace compare 
{

    template <typename T>
    USTL_ALWAYS_INLINE
    Ordering
    compare(T input, T expected) USTL_NOEXCEPT
    {
        static_assert(!internal::type_traits::IsOverrideRel<T>::value
                      "The template parameter T should prepare the relational operator.");

        if (input > expected) {
            return Ordering(Ordering::greater);
        }
        if (input < expected) {
            return Ordering(Ordering::less);
        }

        return Ordering(Ordering::equal);
    }

    template <>
    Ordering
    compare<float>(float input, float expected) USTL_NOEXCEPT;

    template <>
    Ordering
    compare<double>(double input, double expected) USTL_NOEXCEPT;
    
    template <>
    Ordering
    compare<long double>(long double input, long double expected) USTL_NOEXCEPT;

} // namespace compare 
} // namespace internal
} // namespace core
} // namespace ustl




#endif