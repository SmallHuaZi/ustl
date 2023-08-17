#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CONFIG_HPP__
#define __USTL_CONFIG_HPP__


/// Keyword
#define USTL_TRY           try
#define USTL_THROW         throw
#define USTL_CATCH_ALL     catch (...)
#define USTL_CATCH(except) catch (except const &__e)
#define USTL_THROW_AGAIN   throw;
#define USTL_INTERFACE     = 0
#if defined(__cplusplus) && __cplusplus < 201103ul
#   define USTL_NOEXCEPT   throw()
#   define USTL_CONSTEXPR
#   define USTL_HAD_EXCEPT(...)
#else
#   define USTL_NOEXCEPT           noexcept
#   define USTL_CONSTEXPR          constexpr
#   define USTL_HAD_EXCEPT(expr) noexcept(expr)
#endif

/// Property [noreturn]
#if defined(__cplusplus) && __cplusplus >= 201103ul
#   define USTL_NORETURN            [[noreturn]]
#elif defined(__GNUC__)
#   define USTL_NORETURN            __attribute__((noreturn))
#elif defined(_MSC_VER)
#   define USTL_NORETURN            __declspec(noreturn)
#elif 1
#   define USTL_NORETURN
#endif

/// Property [always_inline], [packed], [naked]
#if defined(__cplusplus) && __cplusplus >= 201103ul
#   if defined(__GNUC__)
#       define USTL_ALWAYS_INLINE       [[gnu::always_inline]] inline 
#       define USTL_PACKED              [[gnu::packed]]
#       define USTL_NAKED               [[gnu::naked]]
#   elif defined(_MSC_VER)
#       define USTL_ALWAYS_INLINE       [[msvc::forceinline]]
#       define USTL_PACKED
#       define USTL_NAKED               __declspec(naked)
#   endif
#elif defined(__GNUC__)
#   define USTL_ALWAYS_INLINE   inline __attribute__((always_inline))    
#   define USTL_PACKED          __attribute__((packed))
#   define USTL_NAKED           __attribute__((naked)) 
#elif defined(_MSC_VER)
#   define USTL_ALWAYS_INLINE   __forceinline
#   define USTL_PACKED              
#   define USTL_NAKED           __declspec(naked) 
#elif 1
#   define USTL_ALWAYS_INLINE
#   define USTL_PACKED
#   define USTL_NAKED
#endif

/// Property [nodiscard]
#if __cplusplus >= 201703ul
#   define  USTL_NODISCARD          [[nodiscard]]
#elif defined(__GNUC__)
#   define  USTL_NODISCARD          __attribute__((nodiscard))
#elif defined(_MSC_VER)
#   define  USTL_NODISCARD
#endif

/// Property [likely], [unlikely]
#if defined(__cplusplus) && __cplusplus >= 202002ul
#   define  USTL_LIKELY             [[likely]]
#   define  USTL_UNLIKELY           [[unlikely]]
#elif defined(__GNUC__)
#   define  USTL_LIKELY             __attribute__((likely))
#   define  USTL_UNLIKELY           __attribute__((unlikely))
#else 
#   define  USTL_LIKELY
#   define  USTL_UNLIKELY
#endif


#if defined(_MSC_VER)
#   if defined(USTL_DEV)
#       define     USTL_API    __declspec(dllexport)
#   else
#       define     USTL_API    __declspec(dllimport)
#   endif
#else
#   define     USTL_API
#endif


#endif