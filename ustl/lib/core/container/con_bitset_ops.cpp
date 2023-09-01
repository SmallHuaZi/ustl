#include <ustl/core/internal/container/base/con_bitset_ops.hpp>

typedef ustl::core::internal::container::base::BitSetOpsBasic BitSetOpsBasic;


auto BitSetOpsBasic::
_S_do_find_first(word_type const *map, size_type const limit) 
    USTL_NOEXCEPT -> size_type
{
    for (size_type i = 0; i < limit; ++i) {
        if (map[i]) {
            word_type t0 = map[i], t1 = map[i];
            size_type j = 0;

            while ((t0 << j) == t1) {
                t0 >>= 1;
                ++j;
            }

            return i * WORD_BITS + j - 1;
        }
    }

    return limit * WORD_BITS;
}


auto BitSetOpsBasic::
_S_do_find_next(word_type const *map, size_type const prev, size_type const limit) 
    USTL_NOEXCEPT -> size_type
{
    size_type bit_pos = Self::_S_which_bit(prev + 1);
    size_type word_pos = Self::_S_which_word(prev + 1);

    for (; word_pos < limit; ++word_pos, bit_pos = 0) {
        if (!map[word_pos]) {
            continue;
        }

        word_type t0 = map[word_pos] >> bit_pos;
        word_type t1 = t0 << bit_pos;

        while (bit_pos < WORD_BITS && (t0 << bit_pos) == t1) {
            t0 >>= 1;
            ++bit_pos;
        }

        if (t1 && WORD_BITS >= bit_pos) {
            return word_pos * WORD_BITS + bit_pos - 1; 
        }
    }

    return limit * WORD_BITS;
}


auto BitSetOpsBasic::
_S_do_find_last(word_type const *map, size_type const limit) 
    USTL_NOEXCEPT -> size_type
{
    size_type i = limit;

    while (i-- && !map[i]); 
    if (i != size_type(-1)) {
        word_type t0 = map[i], t1 = map[i];
        size_type j = 0;

        while ((t0 >> j) == t1) {
            t0 <<= 1;
            ++j;
        }

        return (i + 1) * WORD_BITS - j;
    }

    return limit * WORD_BITS;
}


auto BitSetOpsBasic::
_S_do_set_first_unset(word_type *map, size_type const limit) 
    USTL_NOEXCEPT -> size_type
{
    for (size_type i = 0; i < limit; i++) {
        if (map[i] == WORD_MAX) {
            continue;
        }
        word_type t = map[i];
        size_type j = 0;
        
        while (t & 1) {
            t >>= 1;
            ++j;
        }

        map[i] |= Self::_S_make_bits(j);

        return i * WORD_BITS + j;
    }

    return limit * WORD_BITS;
}


auto BitSetOpsBasic::
_S_do_clr_first_set(word_type *map, size_type const limit) 
    USTL_NOEXCEPT -> size_type
{
    for (size_type i = 0; i < limit; i++) {
        if (!map[i]) {
            continue;
        }
        word_type t = map[i];
        size_type j = 0;

        while ((t & 1) == 0) {
            t >>= 1;
            ++j;
        }

        map[i] &= Self::_S_mask_bits(j);

        return i * WORD_BITS + j;
    }
    
    return limit * WORD_BITS;
}


void BitSetOpsBasic::
_S_do_left_shift(word_type *map, size_type const n, size_type const limit) 
    USTL_NOEXCEPT
{
    if (!n) {
        return;
    }

    size_type const bits_ofs = _S_which_bit(n);
    size_type const word_ofs = _S_which_word(n);

    if (bits_ofs) {
        size_type rev_bits_ofs = WORD_BITS - bits_ofs;
        for (size_type i = limit - 1; i > word_ofs; --i) {
            word_type low = map[i - word_ofs - 1] >> rev_bits_ofs; 
            map[i] = (map[i - word_ofs] << bits_ofs) | low;
        }
        map[word_ofs] = map[0] << bits_ofs;
    }
    else {
        for (size_type i = limit - 1; i >= word_ofs; --i) {
            map[i] = map[i - word_ofs];
        }
    }

    for (size_type i = 0; i < word_ofs; ++i) {
        map[i] = 0;
    }
}


void BitSetOpsBasic::
_S_do_right_shift(word_type *map, size_type const n, size_type const limit) 
    USTL_NOEXCEPT
{
    if (!n) {
        return;
    }

    size_type const bits_ofs = _S_which_bit(n);
    size_type const word_ofs = _S_which_word(n);
    size_type const end = limit - word_ofs - 1;

    if (bits_ofs) {
        size_type const rev_bitis_ofs = WORD_BITS - bits_ofs;
        for (size_type i = 0; i < end; i++) {
            word_type high = map[i + word_ofs + 1] << rev_bitis_ofs;
            map[i] = (map[i + word_ofs] >> bits_ofs) | high;
        }
        map[end] = map[limit - 1] >> bits_ofs;
    }
    else {
        for (size_type i = 0; i <= end; i++) {
            map[i] = map[i + word_ofs];
        }
    }

    for (size_type i = limit - 1; i > end; --i) {
        map[i] = 0;
    }
}