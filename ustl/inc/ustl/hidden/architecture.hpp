#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_ARCHITECTURE_HPP__
#define __USTL_ARCHITECTURE_HPP__

#ifdef __GNUC__
# if defined(__x86_64__) || defined(_M_X64) || defined(__ia64__)
#   define ARCH_x86_64
# elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86) 
#   define ARCH_x86_32
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

#endif