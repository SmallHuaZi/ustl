#include <ustl/core/internal/compare/cmp_helper.hpp>


namespace ustl::core::internal::compare
{

    USTL_CONSTEXPR static double const FERROR = 1e-6;
    USTL_CONSTEXPR static double const DERROR = 1e-15;
    USTL_CONSTEXPR static double const LDERROR = 1e-15;

    template <>
    Ordering 
    compare<float>(float input, float expected) USTL_NOEXCEPT
    {
        if (input < expected) {
            return Ordering(Ordering::less);
        }
        if (((input - expected) < 0 ? (-(input - expected)) : (input - expected)) < FERROR) {
            return Ordering(Ordering::equal);
        }

        return Ordering(Ordering::greater);
    };

    template <>
    Ordering 
    compare<double>(double input, double expected) USTL_NOEXCEPT
    {
        if (input < expected) {
            return Ordering(Ordering::less);
        }
        if (((input - expected) < 0 ? (-(input - expected)) : (input - expected)) < DERROR) {
            return Ordering(Ordering::equal);
        }

        return Ordering(Ordering::greater);
    };

    template <>
    Ordering compare<long double>(long double input, long double expected) USTL_NOEXCEPT
    {
        if (input < expected) {
            return Ordering(Ordering::less);
        }
        if (((input - expected) < 0 ? (-(input - expected)) : (input - expected)) < LDERROR) {
            return Ordering(Ordering::equal);
        }

        return Ordering(Ordering::greater);
    };
}