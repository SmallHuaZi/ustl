#ifndef __move_h
#define __move_h

#include "type/type.h"

namespace ustl
{
    /**
     * @brief _Tp& + _Tp&& --> _Tp& lvalue
     *        _Tp&& + _Tp&& --> _Tp rvalue
     */

    /**
     * @brief using remove_reference, let type of return convert to rr
     */
    template <typename _Tp>
    typename remove_reference<_Tp>::type &&
    move(_Tp &&__lr)
    {
        return static_cast<typename remove_reference<_Tp>::type &&>(__lr);
    }

    template <typename _Tp>
    _Tp &&
    forward(_Tp &__lr)
    {
        return static_cast<_Tp &&>(__lr);
    }

    template <typename _Tp>
    _Tp &&
    forward(_Tp &&__rr)
    {
        return static_cast<_Tp &&>(__rr);
    }

} // namespace ustl
#endif