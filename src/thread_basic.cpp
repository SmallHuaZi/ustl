#include "conc/thread_basic.h"

namespace ustl
{
    
    namespace conceal
    {

        tid_t
        thread_basic::
            _M_create_thread()
        {
            constexpr   int __clone_flag = CLONE_PIDFD | CLONE_VM | CLONE_FS |
                                              CLONE_FILES | CLONE_THREAD;
            void_ptr    __stack = mmap(0, __DEFAULT_STACK_SIZE, __STACK_PROP, __STACK_MAP_TYPE, -1, 0);
            if((void_ptr)-1 == __stack)
               ; // throw create threading failure
            phandle     __pid   = clone(0, __stack, __clone_flag , 0);
            if(-1 == __pid)
                ; // throw create threading failure
            tid_t       __ret   = _M_get_free_tid();
        }


        tid_t
        thread_basic::
            _M_get_free_tid()
        {
            size_t  __bit = 1;
            for(; __bit ; __bit << 1)
            {
                if(0 == (__bit & _M_tid_map))
                {
                    _M_tid_map |= __bit;
                    break;
                }
            }
            return  __bit;
        }
        
    } // namespace conceal
    

} // namespace ustl
