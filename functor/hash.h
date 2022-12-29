#ifndef __USTL_HASH_H
#define __USTL_HASH_H

#include "include/config.h"

namespace ustl
{
   template<typename _Tp>
   struct hash
   {
        size_t
        operator()(_Tp const &__val, size_t __prime = 0)
        {
            char    *__data = (char *)&__val;
            size_t  __hash_value = 0;

            for(size_t __tmp = 0; __tmp < sizeof(_Tp); ++__tmp)
            {
                __hash_value += (__data[__tmp] << 4) ^ ((size_t)&__data[__tmp] >> 16);
            }

            return  __prime ?__hash_value  % __prime : __hash_value;
        }

   }; 

} // namespace ustl


#endif