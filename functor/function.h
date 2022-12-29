#ifndef __USTL_FUNCTION_H
#define __USTL_FUNCTION_H 

namespace ustl
{

    template <typename _Result, typename... _Args>
    struct function;

    template <typename _Result, typename... _Args>
    struct function<_Result(_Args...)>
    {
        _Result
        operator()(_Args &&...__args)
        {
            return _M_callable(ustl::forward<_Args &&>(__args)...);
        }

        function(_Result(&__callable)(_Args...))
            : _M_callable(__callable) {}

    protected:
        _Result (&_M_callable) (_Args...)  ;
    };

} // namespace ustl

#endif