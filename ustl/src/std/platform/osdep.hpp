#ifndef __USTL_STD_PLATFORM_OSDEP_HPP__
#define __USTL_STD_PLATFORM_OSDEP_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif


namespace ustl
{
namespace std
{
namespace internal
{
namespace platform
{

    struct os 
    {
        static usize
        open();

        static void 
        close();
    };
    
} // namespace platform
} // namespace internal
} // namespace std
} // namespace ustl



#endif