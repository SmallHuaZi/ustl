#include <ustl/core/bitmap>

#if defined(__x86_64__) || defined(__aarch64__) || defined(_M_X64) || defined(_M_ARM64)
static size_t constexpr const MASK = 0x3f;
static size_t constexpr const SHIFT = 0x06;
static size_t constexpr const FULL = 0xffffffffffffffff;
#else
static size_t constexpr const MASK = 0x1f;
static size_t constexpr const SHIFT = 0x03;
static size_t constexpr const FULL = 0xffffffff;
#endif




void
__CORE bitmap::
    set(csize_t __pos) __NOEXCEPT
{
    csize_t idx = __pos >> SHIFT;
    csize_t bit = __pos & MASK;

    _M_maps[idx] |= 1 << bit;
}


void
__CORE bitmap::
    set(size_t __pos, size_t __len) __NOEXCEPT
{

}


void
__CORE bitmap::
    clr(size_t __pos) __NOEXCEPT
{
    csize_t idx = __pos >> SHIFT;
    csize_t bit = __pos & MASK;

    _M_maps[idx] &= ~(1 << bit);
}


void
__CORE bitmap::
    clr(size_t __pos, size_t __len) __NOEXCEPT
{

}


void
__CORE bitmap::
    neg() __NOEXCEPT
{
    size_t i = 0;
    csize_t half = _M_size >> 1;

    while (i < half) {
        _M_maps[i] = ~_M_maps[i];
        _M_maps[i + 1] = ~_M_maps[i + 1];
        i += 2;
    }

    if (half % 2) {
        _M_maps[_M_size - 1] = ~_M_maps[_M_size - 1];
    }
}


size_t
__CORE bitmap::
    find_first() const __NOEXCEPT
{
    size_t i = 0;
    size_t k = 0;

    while (i < _M_size && _M_maps[i] != FULL) {
        ++i;
    }

    if (i > _M_size) {
        return size_t(-1);
    }

    while (k < sizeof(size_t) && ((1 << k) & _M_maps[i])) {
        ++k;
    }

    return  i * sizeof(size_t) + k;
}


size_t
__CORE bitmap::
    set_first() __NOEXCEPT
{
    size_t i = 0;
    size_t k = 0;

    while (i < _M_size && _M_maps[i] != FULL) {
        ++i;
    }

    if (i > _M_size) {
        return size_t(-1);
    }

    while (k < sizeof(size_t) && ((1 << k) & _M_maps[i])) {
        ++k;
    }

    _M_maps[i] |= 1 << k;

    return  i * sizeof(size_t) + k;
}


bool
__CORE bitmap::
    exist(size_t __pos) const __NOEXCEPT
{

}


auto
__CORE bitmap::
    operator=(_Self_type const &__other) & -> _Self_type &
{

}


auto
__CORE bitmap::
    operator=(_Self_type &&__other) & -> _Self_type &
{

}