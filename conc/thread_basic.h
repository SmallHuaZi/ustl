#ifndef __thread_basic_h
#define __thread_basic_h

#include "include/config.h"
#include "conc/mthread.h"
#include <sys/mman.h>
#include <unistd.h>
#include <sched.h>

namespace ustl
{
    
    namespace conceal
    {
#ifdef  __linux__
       typedef    pid_t         phandle; 
       typedef    size_t        tid_t;


       class thread_basic
       {
            enum    { __THREADING_MAXNUMBER = sizeof(size_t) << 3 };
            enum    { __DEFAULT_STACK_SIZE = 1024 * 1024 * 4 };
            enum    { __STACK_PROP = PROT_EXEC | PROT_READ };
            enum    { __STACK_MAP_TYPE = MAP_PRIVATE | MAP_ANONYMOUS | MAP_GROWSDOWN | MAP_STACK};

        public:
            tid_t
            _M_create_thread();


            tid_t
            _M_get_free_tid();



        private:
            size_t          _M_tid_map;
            phandle         _M_pid[__THREADING_MAXNUMBER];
       }; 
#endif
    } // namespace conceal

} // namespace ustl

#endif