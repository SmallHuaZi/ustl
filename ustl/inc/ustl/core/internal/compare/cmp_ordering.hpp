#ifndef __USTL_CORE_INTERNAL_COMPARE_ORDERING_HPP__
#define __USTL_CORE_INTERNAL_COMPARE_ORDERING_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace compare
{

    struct OrderingBasic
    {
        enum class State {
            Less    =  0x01, 
            Equal   =  0x02,
            Greater =  0x04,
            UnKown  =  0x08,
        };

        static USTL_CONSTEXPR State const less    =  State::Less;
        static USTL_CONSTEXPR State const equal   =  State::Equal;
        static USTL_CONSTEXPR State const greater =  State::Greater;
        static USTL_CONSTEXPR State const unkown  =  State::UnKown;

    };

    USTL_ALWAYS_INLINE USTL_CONSTEXPR 
    static int 
    operator&(OrderingBasic::State x, OrderingBasic::State y) 
    USTL_NOEXCEPT {
        return int(x) & int(y);
    }

    USTL_ALWAYS_INLINE USTL_CONSTEXPR 
    static bool 
    operator==(OrderingBasic::State x, OrderingBasic::State y) 
    USTL_NOEXCEPT {
        return int(x) == int(y);
    }

    USTL_ALWAYS_INLINE USTL_CONSTEXPR 
    static bool 
    operator!=(OrderingBasic::State x, OrderingBasic::State y) 
    USTL_NOEXCEPT {
        return int(x) != int(y);
    }


    struct Ordering 
        : public OrderingBasic
    {
        typedef Ordering        Self;
        typedef OrderingBasic   Base;

    public:
        USTL_CONSTEXPR
        Ordering() USTL_NOEXCEPT
            : _M_state(unkown)
        {}

        USTL_CONSTEXPR
        Ordering(State ord) USTL_NOEXCEPT
            : _M_state(ord)
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        bool
        is_eq() USTL_NOEXCEPT
        { return _M_state & equal; }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        bool
        is_ne() USTL_NOEXCEPT
        { return !is_eq(); }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        bool
        is_lt() USTL_NOEXCEPT
        { return _M_state & less; }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        bool
        is_gt() USTL_NOEXCEPT
        { return _M_state & greater; }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        bool
        is_le() USTL_NOEXCEPT
        { return is_lt() || is_eq(); }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        bool
        is_ge() USTL_NOEXCEPT
        { return is_gt() || is_eq(); }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        bool
        is_vaild() USTL_NOEXCEPT
        { return !(_M_state & unkown); }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        update(State state) USTL_NOEXCEPT
        { _M_state = state; }

    private:
        State   _M_state;
    };

    
} // namespace ustl::core::internal::compare
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl




#endif