#ifndef __function_h
#define __function_h

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
            return _M_function(ustl::forward<_Args &&>(__args)...);
        }

        function(_Result(_Args...) & __callable)
            : _M_callable(__callable) {}

    protected:
        _Result(_Args...) & _M_callable;
    };

} // namespace ustl

#endif