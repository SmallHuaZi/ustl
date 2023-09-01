#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_ARCHITECTURE_HPP__
#define __USTL_ARCHITECTURE_HPP__

#ifdef __GNUC__
# if defined(__x86_64__) || defined(_M_X64) || defined(__ia64__)
#   define ARCH_X86_64
# elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86) 
#   define ARCH_X86_32
# elif defined(__riscv)
#   if __riscv_xlen == 32
#     define ARCH_RISCV32
#   elif __riscv_xlen == 64
#     define ARCH_RISCV64
#   endif
# endif
#endif

#ifdef _MSC_VER
#endif

namespace ustl
{

    USTL_CONSTEXPR static int const BYTE_SIZE =  sizeof(u8);
    USTL_CONSTEXPR static int const BYTE_BITS =  BYTE_SIZE << 3;
    USTL_CONSTEXPR static int const WORD_SIZE =  sizeof(usize);
    USTL_CONSTEXPR static int const WORD_BITS =  WORD_SIZE * BYTE_BITS;

#if defined(ARCH_X86_64) 
    USTL_CONSTEXPR static bool const ARCH_IS_X64 = true;
#else
    USTL_CONSTEXPR static bool const ARCH_IS_X64 = false;
#endif

#if defined(ARCH_X86_32)
    USTL_CONSTEXPR static bool const ARCH_IS_X86 = true;
#else
    USTL_CONSTEXPR static bool const ARCH_IS_X86 = false;
#endif

#if defined(ARCH_RISCV32) 
    USTL_CONSTEXPR static bool const ARCH_IS_RISCV32 = true;
#else
    USTL_CONSTEXPR static bool const ARCH_IS_RISCV32 = false;
#endif

#if defined(ARCH_RISCV64)
    USTL_CONSTEXPR static bool const ARCH_IS_RISCV64 = true;
#else
    USTL_CONSTEXPR static bool const ARCH_IS_RISCV64 = false;
#endif
    
} // namespace ustl


#endif