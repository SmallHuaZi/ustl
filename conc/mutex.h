#ifndef __USTL_MUTEX_H
#define __USTL_MUTEX_H

#include "include/config.h"
#include "conc/atomic.h"

namespace ustl
{
   class mutex
   {
   private:
    void
    _M_lock() ustl_cpp_noexcept
    {  }

    void
    _M_unlock() ustl_cpp_noexcept
    {  }


   public:
    mutex(atomic_t *__mutex)
        : _M_mux(__mutex)
    { *_M_mux = 0; }

    ~mutex()
    {}

    void 
    acquire();

    void
    release();

    protected:
        atomic_t    *_M_mux;
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