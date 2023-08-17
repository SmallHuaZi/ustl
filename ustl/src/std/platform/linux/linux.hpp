#ifndef __USTL_STD_PLATFORM_LINUX_LINUX_HPP__
#define __USTL_STD_PLATFORM_LINUX_LINUX_HPP__

#if defined(__GNUC__) && defined(__linux__)
#include <asm/unistd.h>
#else
#error "ustl [std/platform/linux/linux.hpp] must used be on linux"
#endif
#endif