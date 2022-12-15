#ifndef __math_h
#define __math_h

namespace ustl
{
    template <typename _Tp>
    struct less
    {
        bool
        operator()(_Tp __x, _Tp __y) const
        {
            return __x < __y;
        }
    };

    template <typename _Tp>
    struct equal_t
    {
        bool
        operator()(_Tp __x, _Tp __y) const
        {
            return __x == __y;
        }
    };

    template <typename _Tp, typename _Comp = ustl::less<_Tp>>
    _Tp
    min(_Tp __x, _Tp __y, _Comp __cmp = _Comp())
    {
        return __cmp(__x, __y) ? __x : __y;
    }

    template <typename _Tp, typename _Comp = ustl::less<_Tp>>
    _Tp
    max(_Tp __x, _Tp __y, _Comp __cmp = _Comp())
    {
        return __cmp(__x, __y) ? __y : __x;
    }

    template <typename _Tp, typename _Comp = ustl::equal_t<_Tp>>
    bool
    equal(_Tp __x, _Tp __y, _Comp __cmp = _Comp())
    {
        return  __cmp(__x, __y);
    }

    static inline double
    abs(double __val)
    {
        return  __val < 0 ? -__val : __val;
    }

} // namespace ustl

#endif