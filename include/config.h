#ifndef __USTL_CONFIG 
#define __USTL_CONFIG 

#include "include/ustl.h"

namespace ustl
{

#if __ustl_lib == 20221018UL
    typedef     char                byte;
    typedef     long                diff_t;
    typedef     unsigned long       size_t;
    typedef     double              float_t;
    typedef     void *              void_ptr;


#ifdef  __UNICODE
    typedef     wchar_t     _Wchar_t;
#define __WCSTR(__str)   L##__str
#else
    typedef     char        _Wchar_t;
#define __WCSTR(__str)  __str
    
#endif // __UNICODE

#define __pure_vritual = 0

#define platform 64UL

#define alignment_criteria 8

#define __ustl_try try

#define __ustl_catch_all catch (...)

#define __ustl_catch(except) catch (except & __e)

#define __ustl_throw_again throw;

#define ustl_cpp_noexcept noexcept

}
#endif
#endif