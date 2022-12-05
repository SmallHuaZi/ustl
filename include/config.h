#include "ustl.h"

#ifndef __config_h
#define __config_h

namespace ustl
{

#if __ustl_lib == 20221018UL
    typedef unsigned long size_t;
    typedef long diff_t;
    typedef char byte;
    typedef void *void_ptr;
#endif

#define __pure_vritual = 0

#define platform 64UL

#define alignment_criteria 8

#define ustl_cpp_noexcept noexcept

}
#endif