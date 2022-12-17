#ifndef __mutex_h
#define __mutex_h

#include "include/config.h"

namespace ustl
{
   class mutex
   {
    typedef     ustl::size_t        atomic_mutex_t;


   private:
    void
    _M_lock() ustl_cpp_noexcept
    { asm volatile("mov $1, %0  \n\t" :"=m"(_M_mux) :"memory"); }

    void
    _M_unlock() ustl_cpp_noexcept
    { asm volatile("mov $0, %0  \n\t" :"=m"(_M_mux) :"memory"); }


   public:
    mutex(atomic_mutex_t    *__mutex)
        : _M_mux(__mutex)
    { *_M_mux = 0; }

    ~mutex()
    {}

    void 
    acquire();

    void
    release();

    protected:
        atomic_mutex_t      *_M_mux;
   };

    inline void
    mutex::
        acquire()
    {
        while(*_M_mux);
        _M_lock();
    }


    inline void
    mutex::
        release()
    {
        _M_unlock();
    }
    
    
} // namespace ustl





#endif