#include "config.hpp"
#include <ustl/core/tuple>

using namespace ustl;

struct TupleSample
    : testing::Test
{

    struct PolymericType {
        int _0;
        struct PolymericType *_next;
        struct PolymericType *_prev;

        PolymericType()
            : _next(0),
              _prev(0)
        {}

        PolymericType(PolymericType const &other)
        {
            *this = other;
        }

        PolymericType(PolymericType &&other)
        {
            *this = ::std::move(other);
        }

        PolymericType &
        operator=(PolymericType &&other)
        {
            this->_0 = other._0;
            this->_next = other._next;
            this->_prev = other._prev;
            return *this;
        }

        PolymericType &
        operator=(PolymericType const &other)
        {
            this->_next = 0;
            this->_prev = 0;
            return *this;
        }

        ~PolymericType()
        {}
    };

public: 
    core::tuple<int, char, long>  _0;
    core::tuple<int, char, long>  _1;
    core::tuple<int, PolymericType, long>  _2;
};

typedef TupleSample::PolymericType PolymericType;
static inline bool
operator==(PolymericType const &x, PolymericType const &y)
{
    return x._0 == y._0 && x._next == y._next && x._prev == y._prev;
}


TEST_F(TupleSample, get)
{
    ASSERT_TRUE(sizeof(_0) == 16);

    auto &f0 = core::get<0>(_0);
    auto &f1 = core::get<1>(_0);
    auto &f2 = core::get<2>(_0);
    ASSERT_EQ(&core::get<0>(_0), &f0);
    ASSERT_EQ(&core::get<1>(_0), &f1);
    ASSERT_EQ(&core::get<2>(_0), &f2);

    f0 = 100;
    f1 = 'a';
    f2 = 100000;
    ASSERT_EQ(get<0>(_0), f0);
    ASSERT_EQ(get<1>(_0), f1);
    ASSERT_EQ(get<2>(_0), f2);
}


TEST_F(TupleSample, swap)
{
    _0 = {100, 'd', 999};
    _1 = {200, 'c', 888};
    _0.swap(_1);

    ASSERT_EQ(200, get<0>(_0));
    ASSERT_EQ('c', get<1>(_0));
    ASSERT_EQ(888, get<2>(_0));

    ASSERT_EQ(100, get<0>(_1));
    ASSERT_EQ('d', get<1>(_1));
    ASSERT_EQ(999, get<2>(_1));
}


TEST_F(TupleSample, operator_eq_and_ne)
{
    _0 = {100, 'd', 999};
    _1 = {200, 'c', 888};

    ASSERT_FALSE(_0 == _1);
    ASSERT_TRUE(_0 != _1);

    _1 = {100, 'd', 999};
    ASSERT_TRUE(_0 == _1);
    ASSERT_FALSE(_0 != _1);
}


TEST_F(TupleSample, operator_assign_on_polymeric_type)
{
    auto sample = PolymericType{};
    sample._prev = reinterpret_cast<PolymericType *>(1000);
    sample._next = reinterpret_cast<PolymericType *>(1000);

    _2 = {0, ::std::move(sample), 100};
    // Set _next or _prev to zero if call copy assignment
    ASSERT_NE(reinterpret_cast<PolymericType *>(0), get<1>(_2)._next);
    ASSERT_NE(reinterpret_cast<PolymericType *>(0), get<1>(_2)._prev);
}