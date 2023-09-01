#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_CONTAINER_BITSET_HPP__
#define __USTL_CORE_INTERNAL_CONTAINER_BITSET_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

#ifndef __USTL_CORE_INTERNAL_CONTAINER_BASE_BITSET_OPS_HPP__
#include <ustl/core/internal/container/base/con_bitset_ops.hpp>
#endif

#ifndef __USTL_CORE_INTERNAL_UTILITY_ALIGN_HPP__
#include <ustl/core/internal/utility/align.hpp>
#endif

#ifndef __USTL_CORE_INTERNAL_ALGORITHM_COPY_HPP__
#include <ustl/core/internal/algorithm/algo_copy.hpp>
#endif

namespace ustl::core::internal::container
{
    template <usize NBits>
    class BitSet;

    template <usize N>
    static bool
    operator==(BitSet<N> const &x, BitSet<N> const &y) USTL_NOEXCEPT;

    template <usize N>
    static bool
    operator==(BitSet<N> const &x, BitSet<N> const &y) USTL_NOEXCEPT;

    template <usize N>
    static bool
    operator<(BitSet<N> const &x, BitSet<N> const &y) USTL_NOEXCEPT;

    template <usize N>
    static bool
    operator>=(BitSet<N> const &x, BitSet<N> const &y) USTL_NOEXCEPT;

    template <usize NWords>
    class BitSetBasic
        : protected base::BitSetOps
    {
    protected:
        typedef usize   size_type;
        typedef usize   word_type;

    protected:
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        size_type
        _M_bits_size() const USTL_NOEXCEPT
        { return sizeof(_M_map) * BYTE_BITS; }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        size_type
        _M_byte_size() const USTL_NOEXCEPT
        { return sizeof(_M_map); }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        size_type
        _M_word_size() const USTL_NOEXCEPT
        { return sizeof(_M_map) / sizeof(_M_map[0]); }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        _M_do_set_all(word_type val) USTL_NOEXCEPT
        {
            size_type const limit = _M_word_size();
            for (size_type i = 0; i < limit; i++) {
                this->_M_map[i] = val;
            }
        }

    protected:
        word_type   _M_map[NWords];
    };


    /// @class 'BitSet'
    /// @brief
    /// @tparam NBits
    template <usize NBits>
    class BitSet
        : protected BitSetBasic<internal::utility::align_upper(NBits, WORD_BITS) / WORD_BITS>
    {
        USTL_GENERAL_ASSOCIATION_TYPE_HAD_BASE(BitSet, 
            BitSetBasic<internal::utility::align_upper(NBits, WORD_BITS) / WORD_BITS>);

    public:
        typedef typename Base::size_type     size_type;
        typedef typename Base::word_type     word_type;

    private:
        using  Base::_M_map;
        using  Base::_M_bits_size;
        using  Base::_M_byte_size;
        using  Base::_M_word_size;
        using  Base::_M_do_set_all;

    public:
        BitSet() = default;

        /// @brief 
        /// @param pos
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        set(size_type const pos) USTL_NOEXCEPT
        { 
            Base::set(_M_map, pos); 
        }

        /// @brief 
        /// @param first 
        /// @param last
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        set_range(size_type const first, size_type const last) USTL_NOEXCEPT
        { 
            Base::set_range(_M_map, first, last); 
        }

        /// @brief
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        set_all() USTL_NOEXCEPT
        { 
            _M_do_set_all(WORD_MAX); 
        }

        /// @brief 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        size_type
        set_first() USTL_NOEXCEPT
        { 
            return Base::set_first(_M_map, _M_word_size()); 
        }

        /// @brief 
        /// @param pos
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        clr(size_type const pos) USTL_NOEXCEPT
        { 
            Base::clr(_M_map, pos); 
        }

        /// @brief 
        /// @param first 
        /// @param last
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        clr_range(size_type const first, size_type const last) USTL_NOEXCEPT
        { 
            Base::clr_range(this->_M_map, first, last); 
        }

        /// @brief
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        clr_all() USTL_NOEXCEPT
        { 
            _M_do_set_all(0); 
        }

        /// @brief 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        size_type
        clr_first() USTL_NOEXCEPT
        { 
            return Base::clr_first(_M_map, _M_word_size()); 
        }

        /// @brief 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void 
        flip_all() USTL_NOEXCEPT
        { 
            Base::bit_neg(_M_map, _M_map + _M_word_size()); 
        }

        /// @brief 
        /// @param pos 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        flip(size_type const pos) USTL_NOEXCEPT
        { 
            Base::flip(_M_map, pos); 
        }

        /// @brief 
        /// @param first 
        /// @param last 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        flip_range(size_type const first, size_type const last) USTL_NOEXCEPT
        { 
            Base::flip_range(_M_map, first, last); 
        }

        /// @brief 
        /// @param pos
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        bool
        test(size_type const pos) const USTL_NOEXCEPT
        { 
            return Base::test(_M_map, pos); 
        }

        /// @brief 
        /// @param first
        /// @param last 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        bool
        test_range(size_type const first, size_type const last) const USTL_NOEXCEPT
        { 
            return Base::test_range(_M_map, first, last); 
        }

        /// @brief 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        bool
        any() const USTL_NOEXCEPT
        { 
            return Base::any(_M_map, _M_word_size()); 
        }

        /// @brief 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        bool
        all() const USTL_NOEXCEPT
        { 
            return Base::all(_M_map, _M_word_size()); 
        }

        /// @brief 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        bool
        none() const USTL_NOEXCEPT
        { 
            return Base::none(_M_map, _M_word_size()); 
        }

        /// @brief 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        size_type
        find_first() const USTL_NOEXCEPT
        { 
            return Base::find_first(_M_map, _M_word_size()); 
        }

        /// @brief 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        size_type
        find_next(size_type const prev) const USTL_NOEXCEPT
        { 
            return Base::find_next(_M_map, prev, _M_word_size()); 
        }

        /// @brief 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        size_type
        find_last() const USTL_NOEXCEPT
        { 
            return Base::find_last(_M_map, _M_word_size()); 
        }

        /// @brief 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        size_type
        size() const USTL_NOEXCEPT
        { 
            return _M_bits_size(); 
        }

        /// @brief 
        /// @param other 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Ref
        operator=(Self const &other) & USTL_NOEXCEPT
        {
            using internal::algorithm::copy;
            copy(_M_map, _M_map + _M_word_size(), other._M_map);

            return *this;
        }

        /// @brief 
        /// @param other 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Ref
        operator&=(ConstRef other) & USTL_NOEXCEPT
        {
            Base::bit_and(_M_map, _M_map + _M_word_size(), other._M_map);
            return *this;
        }

        /// @brief 
        /// @param other 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Ref
        operator|=(ConstRef other) & USTL_NOEXCEPT
        {
            Base::bit_or(_M_map, _M_map + _M_word_size(), other._M_map);
            return *this;
        }

        /// @brief 
        /// @param other 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Ref
        operator^=(ConstRef other) & USTL_NOEXCEPT
        {
            Base::bit_xor(_M_map, _M_map + _M_word_size(), other._M_map);
            return *this;
        }

        /// @brief 
        /// @param n 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Ref 
        operator>>=(size_type const n) & USTL_NOEXCEPT
        {
            Base::right_shift(_M_map, n, _M_word_size());
            return *this;
        }

        /// @brief 
        /// @param n 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Ref
        operator<<=(size_type const n) & USTL_NOEXCEPT
        {
            Base::left_shift(_M_map, n, _M_word_size());
            return *this;
        }

        /// @brief 
        /// @param other 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Self
        operator&(ConstRef other) const USTL_NOEXCEPT
        {
            Self res {*this};
            res &= other;
            return res;
        }

        /// @brief 
        /// @param other 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Self
        operator|(ConstRef other) const USTL_NOEXCEPT
        {
            Self res {*this};
            res |= other;
            return res;
        }

        /// @brief
        /// @param other 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Self
        operator^(ConstRef other) const USTL_NOEXCEPT
        {
            Self res {*this};
            res ^= other;
            return res;
        }

        /// @brief
        /// @param n
        /// @return
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Self
        operator>>(size_type const n) const USTL_NOEXCEPT
        {
            Self res {*this};
            res >>= n;
            return res;
        }

        /// @brief 
        /// @param n 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Self
        operator<<(size_type const n) const USTL_NOEXCEPT
        {
            Self res {*this};
            res <<= n;
            return res;
        }

        /// @brief 
        /// @return 
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Self
        operator!() const USTL_NOEXCEPT
        {
            Self res {*this};
            Base::bit_neg(res._M_map, res._M_map + res._M_word_size());
            return res;
        }

        friend bool
        operator== <>(ConstRef x, ConstRef y);

        friend bool
        operator!= <>(ConstRef x, ConstRef y);

        friend bool
        operator< <>(ConstRef x, ConstRef y);

        friend bool
        operator>= <>(ConstRef x, ConstRef y);
    };

    template <usize NBits>
    USTL_ALWAYS_INLINE
    static bool
    operator==(BitSet<NBits> const &x, BitSet<NBits> const &y) USTL_NOEXCEPT
    {
        int i = 0, j = x._M_word_size();
        for (; i < j && x._M_map[i] == y._M_map[i]; ++i);
        
        return i == j; 
    }

    template <usize NBits>
    USTL_ALWAYS_INLINE
    static bool
    operator!=(BitSet<NBits> const &x, BitSet<NBits> const &y) USTL_NOEXCEPT
    {
        return !(x == y); 
    }
        
    template <usize NBits>
    USTL_ALWAYS_INLINE
    static bool
    operator<(BitSet<NBits> const &x, BitSet<NBits> const &y) USTL_NOEXCEPT
    {
        int i = 0, j = x._M_word_size();
        for (; i < j && x._M_map[i] <= y._M_map[i]; ++i);

        return i == j;
    }

    template <usize NBits>
    USTL_ALWAYS_INLINE
    static bool
    operator>=(BitSet<NBits> const &x, BitSet<NBits> const &y) USTL_NOEXCEPT
    {
        return !(x < y);
    }

} // namespace ustl::core::internal::container

#endif