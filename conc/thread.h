#ifndef __ustl_thread_h
#define __ustl_thread_h

#define __ustl_multi_processtor

#ifdef __linux__
#include <unistd.h>
#elif  _WIN32
#include <windows.h>
#endif

namespace ustl
{
    class thread
    {
        struct handle 
        {
#ifdef  __linux__
            typedef pid_t   thandle;
#elif   _WIN32
            typedef HANDLE  thandle;
#endif

            thandle     _M_handle;
        };

    
    public:
        void
        join();

        void
        detach();

        void
        sleep(size_t);


    public: 
        thread() = default;

        template <typename _Invoke, typename ..._Args>
        thread(_Invoke);

    private:
        handle          _M_thandle;
    };

} // namespace ustl



#endif