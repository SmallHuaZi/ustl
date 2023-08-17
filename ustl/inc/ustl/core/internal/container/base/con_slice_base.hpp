#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_CONTAINER_BASE_SLICE_HPP__
#define __USTL_CORE_INTERNAL_CONTAINER_BASE_SLICE_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl
{
namespace core
{
namespace internal
{

    template <typename T>
    struct Slice 
    {
        typedef T   value_type;
        typedef T * pointer;
        typedef T & reference;


    public:
        usize   _M_length;
        pointer _M_scope;
    };
    
} // namespace internal
} // namespace core
} // namespace ustl


#endif