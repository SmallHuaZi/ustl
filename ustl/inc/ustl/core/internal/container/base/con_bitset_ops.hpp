#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_CONTAINER_BASE_BITSET_OPS_HPP__
#define __USTL_CORE_INTERNAL_CONTAINER_BASE_BITSET_OPS_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

#ifndef __USTL_CORE_INTERNAL_INTEGER_HPP__
#include <ustl/core/internal/integer.hpp>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace container
{
namespace base
{
    struct USTL_API BitSetOpsBasic
    {
        typedef usize   word_type;
        typedef usize   size_type;

        USTL_ALWAYS_INLINE
        static size_type 
        _S_which_bit(size_type const pos) USTL_NOEXCEPT
        { return pos & (WORD_BITS - 1); }

        USTL_ALWAYS_INLINE
        static size_type 
        _S_which_byte(size_type const pos) USTL_NOEXCEPT
        { return pos / BYTE_BITS; }

        USTL_ALWAYS_INLINE
        static size_type 
        _S_which_word(size_type const pos) USTL_NOEXCEPT
        { return pos / WORD_BITS; }

        USTL_ALWAYS_INLINE
        static word_type 
        _S_make_bits(size_type const pos) USTL_NOEXCEPT
        { return word_type(1) << Self::_S_which_bit(pos); }

        USTL_ALWAYS_INLINE
        static word_type 
        _S_mask_bits(size_type const pos) USTL_NOEXCEPT
        { return ~Self::_S_make_bits(pos); }

        USTL_ALWAYS_INLINE
        static word_type 
        _S_mask_high_bits(size_type const n) USTL_NOEXCEPT
        { return WORD_MAX >> n << n; }

        USTL_ALWAYS_INLINE
        static word_type 
        _S_mask_low_bits(size_type const n) USTL_NOEXCEPT
        { return Self::_S_make_bits(n) - 1; }

        USTL_ALWAYS_INLINE
        static bool 
        _S_do_test(word_type const *map, size_type pos) USTL_NOEXCEPT
        {
            size_type p = Self::_S_which_word(pos);
            return map[p] & Self::_S_make_bits(pos);
        }

        USTL_ALWAYS_INLINE
        static void
        _S_do_flip(word_type *map, size_type pos) USTL_NOEXCEPT
        {
            size_type p = Self::_S_which_word(pos);
            map[p] = Self::_S_mask_bits(pos) ^ ~map[p];
        }

        USTL_ALWAYS_INLINE
        static void
        _S_do_clr(word_type *map, size_type pos) USTL_NOEXCEPT
        {
            size_type p = Self::_S_which_word(pos);
            map[p] &= Self::_S_mask_bits(pos);
        }

        USTL_ALWAYS_INLINE
        static void
        _S_do_set(word_type *map, size_type pos) USTL_NOEXCEPT
        {
            size_type bp = Self::_S_which_bit(pos);
            size_type wp = Self::_S_which_word(pos);
            map[wp] |= Self::_S_make_bits(bp);
        }

        USTL_ALWAYS_INLINE
        static void
        _S_do_or(word_type *first, word_type *last, word_type *other) USTL_NOEXCEPT
        {
            while (first != last) {
                *first++ |= *other++;
            }
        }

        USTL_ALWAYS_INLINE
        static void
        _S_do_xor(word_type *first, word_type *last, word_type *other) USTL_NOEXCEPT
        {
            while (first != last) {
                *first++ |= *other++;
            }
        }

        USTL_ALWAYS_INLINE
        static void
        _S_do_and(word_type *first, word_type *last, word_type *other) USTL_NOEXCEPT
        {
            while (first != last) {
                *first++ &= *other++;
            }
        }

        USTL_ALWAYS_INLINE
        static void
        _S_do_neg(word_type *first, word_type *last) USTL_NOEXCEPT
        {
            for (; first != last; ++first) {
                *first = ~*first;
            }
        }

        USTL_ALWAYS_INLINE
        static bool
        _S_do_all(word_type const *map, size_type const limit) USTL_NOEXCEPT
        {
            size_type i = 0;
            while (i < limit && map[i] == WORD_MAX);

            return i == limit;  
        }

        USTL_ALWAYS_INLINE
        static bool
        _S_do_any(word_type const *map, size_type const limit) USTL_NOEXCEPT
        {
            size_type i = 0;
            while (i < limit && !map[i++]);

            return i != limit;
        }

        static size_type 
        _S_do_set_first_unset(word_type *map, size_type const limit) USTL_NOEXCEPT;

        static size_type 
        _S_do_clr_first_set(word_type *map, size_type const limit) USTL_NOEXCEPT;

        static size_type 
        _S_do_find_first(word_type const *map, size_type const limit) USTL_NOEXCEPT;

        static size_type 
        _S_do_find_last(word_type const *map, size_type const limit) USTL_NOEXCEPT;

        static size_type
        _S_do_find_next(word_type const *map, size_type const prev, size_type const limit) USTL_NOEXCEPT;

        static void
        _S_do_left_shift(word_type *map, size_type const n, size_type const limit) USTL_NOEXCEPT;

        static void
        _S_do_right_shift(word_type *map, size_type const n, size_type const limit) USTL_NOEXCEPT;
    
    private:
        USTL_GENERAL_ASSOCIATION_TYPE(BitSetOpsBasic);
    };


    struct BitSetOps
        : public BitSetOpsBasic
    {
        USTL_ALWAYS_INLINE
        static size_type 
        set_first(word_type *map, size_type limit)
        { return Base::_S_do_set_first_unset(map, limit); }

        USTL_ALWAYS_INLINE
        static void
        set(word_type *map, size_type pos) USTL_NOEXCEPT
        { Base::_S_do_set(map, pos); }

        USTL_ALWAYS_INLINE
        static void
        set_range(word_type *map, size_type first, size_type last) USTL_NOEXCEPT
        {
            while (first != last) {
                Self::set(map, first++);
            }
        }

        USTL_ALWAYS_INLINE
        static size_type 
        clr_first(word_type *map, size_type pos) USTL_NOEXCEPT
        { return Base::_S_do_clr_first_set(map, pos); }

        USTL_ALWAYS_INLINE
        static void
        clr(word_type *map, size_type pos) USTL_NOEXCEPT
        { Base::_S_do_clr(map, pos); }

        USTL_ALWAYS_INLINE
        static void
        clr_range(word_type *map, size_type first, size_type last) USTL_NOEXCEPT
        {
            while (first != last) {
                Self::clr(map, first++);
            }
        }

        USTL_ALWAYS_INLINE
        static void
        flip(word_type *map, size_type pos) USTL_NOEXCEPT
        { Base::_S_do_flip(map, pos); }

        USTL_ALWAYS_INLINE
        static void
        flip_range(word_type *map, size_type first, size_type last) USTL_NOEXCEPT
        {
            while (first != last) {
                Self::flip(map, first++);
            }
        }

        USTL_ALWAYS_INLINE
        static bool 
        test(word_type const *map, size_type pos) USTL_NOEXCEPT
        { return Base::_S_do_test(map, pos); }

        USTL_ALWAYS_INLINE
        static bool 
        test_range(word_type const *map, size_type first, size_type last) USTL_NOEXCEPT
        {
            while (first != last && Self::test(map, first++));
            return first == last;
        }

        USTL_ALWAYS_INLINE
        static bool
        any(word_type const *map, size_type const limit) USTL_NOEXCEPT
        { return _S_do_any(map, limit); }

        USTL_ALWAYS_INLINE
        static bool
        all(word_type const *map, size_type const limit) USTL_NOEXCEPT
        { return _S_do_all(map, limit); }

        USTL_ALWAYS_INLINE
        static bool
        none(word_type const *map, size_type const limit) USTL_NOEXCEPT
        { return !any(map, limit); }

        USTL_ALWAYS_INLINE
        static size_type 
        find_first(word_type const *map, size_type const limit) USTL_NOEXCEPT
        { return Self::_S_do_find_first(map, limit); }

        USTL_ALWAYS_INLINE
        static size_type 
        find_last(word_type const *map, size_type const limit) USTL_NOEXCEPT
        { return Self::_S_do_find_last(map, limit); }

        USTL_ALWAYS_INLINE
        static size_type
        find_next(word_type const *map, size_type const prev, size_type const limit) USTL_NOEXCEPT
        { return Self::_S_do_find_next(map, prev, limit); }

        USTL_ALWAYS_INLINE
        static void 
        bit_or(word_type *first, word_type *last, word_type *other) USTL_NOEXCEPT
        { Self::_S_do_or(first, last, other); }

        USTL_ALWAYS_INLINE
        static void 
        bit_xor(word_type *first, word_type *last, word_type *other) USTL_NOEXCEPT
        { Self::_S_do_xor(first, last, other); }

        USTL_ALWAYS_INLINE
        static void 
        bit_and(word_type *first, word_type *last, word_type *other) USTL_NOEXCEPT
        { Self::_S_do_and(first, last, other); }

        USTL_ALWAYS_INLINE
        static void 
        bit_neg(word_type *first, word_type *last) USTL_NOEXCEPT
        { Self::_S_do_neg(first, last); }

        USTL_ALWAYS_INLINE
        static void 
        left_shift(word_type *map, size_type const n, size_type const limit) USTL_NOEXCEPT
        { Self::_S_do_left_shift(map, n, limit); }

        USTL_ALWAYS_INLINE
        static void 
        right_shift(word_type *map, size_type const n, size_type const limit) USTL_NOEXCEPT
        { Self::_S_do_right_shift(map, n, limit); }

    private:
        USTL_GENERAL_ASSOCIATION_TYPE_HAD_BASE(BitSetOps, BitSetOpsBasic);
    };


} // namespace ustl::core::internal::container::base
} // namespace ustl::core::internal::container
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl


#endif