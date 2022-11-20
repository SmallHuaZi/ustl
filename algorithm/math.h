#ifndef __math_h
#define __math_h

namespace ustl
{
    template <typename _Tp>
    struct less
    {
        bool
        operator()(_Tp __x, _Tp __y)
        {
            return __x < __y;
        }
    };

    template <typename _Tp, typename _Comp = ustl::less<_Tp>>
    bool
    min(_Tp __x, _Tp __y, _Comp __cmp = _Comp())
    {
        return __cmp(__x, __y) ? __x : __y;
    }

} // namespace ustl

#endif