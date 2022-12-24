#ifndef __ustl_new_h
#define __ustl_new_h

#include "include/config.h"

namespace ustl
{
    class ustl_new
    {
public:
        static void *
        operator new(size_t __s)
        {

        }

        static void
        operator delete(void *__del, size_t __s)
        {

        }
    };

} // namespace ustl



#endif