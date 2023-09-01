#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_INTEGER_HPP__
#define __USTL_CORE_INTERNAL_INTEGER_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

namespace ustl
{
namespace core
{
namespace internal
{

    USTL_CONSTEXPR static i8 const I8_MIN = 0x80;
    USTL_CONSTEXPR static i8 const I8_MAX = 0x7f;
    USTL_CONSTEXPR static u8 const U8_MIN = 0;
    USTL_CONSTEXPR static u8 const U8_MAX = 0xff;

    USTL_CONSTEXPR static i16 const I16_MIN = 0x8000;
    USTL_CONSTEXPR static i16 const I16_MAX = 0x7fff;
    USTL_CONSTEXPR static u16 const U16_MIN = 0;
    USTL_CONSTEXPR static u16 const U16_MAX = 0xffff;

    USTL_CONSTEXPR static i32 const I32_MIN = 0x80000000;
    USTL_CONSTEXPR static i32 const I32_MAX = 0x7fffffff;
    USTL_CONSTEXPR static u32 const U32_MIN = 0;
    USTL_CONSTEXPR static u32 const U32_MAX = 0xffffffff;

    /// @bug
    USTL_CONSTEXPR static i64 const I64_MIN = 0x8000000000000000;
    USTL_CONSTEXPR static i64 const I64_MAX = 0x7fffffffffffffff;
    USTL_CONSTEXPR static u64 const U64_MIN = 0;
    USTL_CONSTEXPR static u64 const U64_MAX = 0xffffffffffffffff;

#if defined(ARCH_X86_64) || defined(ARCH_RISCV64)
    USTL_CONSTEXPR static isize const ISIZE_MIN = I64_MIN;
    USTL_CONSTEXPR static isize const ISIZE_MAX = I64_MAX;
    USTL_CONSTEXPR static usize const USIZE_MIN = U64_MIN;
    USTL_CONSTEXPR static usize const USIZE_MAX = U64_MAX;
#elif defined(ARCH_X86_32) || defined(ARCH_RISCV32)
    USTL_CONSTEXPR static isize const ISIZE_MIN = I32_MIN;
    USTL_CONSTEXPR static isize const ISIZE_MAX = I32_MAX;
    USTL_CONSTEXPR static usize const USIZE_MIN = U32_MIN;
    USTL_CONSTEXPR static usize const USIZE_MAX = U32_MAX;
#else
#error "ustl only supports 64-bit or 32-bit platforms."
#endif

    USTL_CONSTEXPR static usize const BYTE_MAX = U8_MAX;
    USTL_CONSTEXPR static usize const WORD_MAX = USIZE_MAX;
    
} // namespace internal
} // namespace core
} // namespace ustl



#endif