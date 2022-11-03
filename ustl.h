#include "config.h"
#include "type.h"
#include "iterator.h"
#include "move.h"

#ifndef __ustl_h
#define __ustl_h

namespace ustl
{
#define __debug_ustl
/**
 *
 *
 */
#define __ustl_lib 20221018UL
#define __ustl_internal_type 1
#define __type_traits 1

#if defined(__ustl_internal_type) && __ustl_internal_type

#if __ustl_lib == 20221018UL
    typedef unsigned long size_t;
    typedef long diff_t;
    typedef char byte;
    typedef void *void_ptr;
#endif

#endif

#if defined(__type_traits) && __type_traits

#endif

}
#endif