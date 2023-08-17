#ifndef __USTL_CORE_INTERNAL_MATH_TRIGONOMETRIC_HPP__
#define __USTL_CORE_INTERNAL_MATH_TRIGONOMETRIC_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace math
{

    template <typename Number>
    USTL_ALWAYS_INLINE
    static Number
    sin(Number radian) USTL_NOEXCEPT
    { return sin<double>(radian); }

    template<>
    double
    sin<double>(double radian) USTL_NOEXCEPT;


    template <typename Number>
    USTL_ALWAYS_INLINE
    static Number
    cos(Number radian) USTL_NOEXCEPT
    { return cos<double>(radian); }
    
    template<>
    double
    cos<double>(double radian) USTL_NOEXCEPT;


    template <typename Number>
    USTL_ALWAYS_INLINE
    Number
    tan(Number radian) USTL_NOEXCEPT
    { return tan<double>(radian); }
    
    template<>
    double
    tan<double>(double radian) USTL_NOEXCEPT;
    

    template <typename Number>
    USTL_ALWAYS_INLINE
    Number
    sec(Number radian) USTL_NOEXCEPT
    { return sec<double>(radian); }
    
    template<>
    double
    sec<double>(double radian) USTL_NOEXCEPT;

} // namespace math
} // namespace internal
} // namespace core
} // namespace ustl



#endif