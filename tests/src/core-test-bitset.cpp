#include "config.hpp"
#include <ustl/core/integer>
#include <ustl/core/bitset>
#include <core/container/con_bitset_ops.cpp>
#include <bitset>

using namespace ustl;
using namespace core;
using namespace internal::container;
using namespace base;

static constexpr int const LENGTH = 100;

static usize y[LENGTH];
static usize d[LENGTH];
static constexpr int const BYTES_LENGTH = sizeof(y);
static constexpr int const BITS_LENGTH = sizeof(y) * 8;

static ::std::bitset<BITS_LENGTH> *x = (decltype(x))y;
static ::std::bitset<BITS_LENGTH> *z = (decltype(z))d;

static inline usize 
myrand() noexcept
{
    ::std::random_device rd;
    ::std::mt19937_64 engine{rd()};
    ::std::uniform_int_distribution<usize> gen;

    return gen(engine);
}


TEST(InterfaceTesting, set)
{
    GTEST_SKIP();
    ::std::bitset<BITS_LENGTH> z;
    memset(y, 0, BYTES_LENGTH);

    for (size_t i = 0; i < BITS_LENGTH; i++) {
        z.set(i);
        BitSetOps::set(y, i);
        ASSERT_TRUE(0 == memcmp(y, &z, BYTES_LENGTH)) 
            << i 
            << " " << z.to_ulong() << " " << y[i];
    }
}

TEST(InterfaceTesting, clr)
{
    GTEST_SKIP();
    ::std::bitset<BITS_LENGTH> z;
    z.flip();
    
    memset(y, 0xff, BYTES_LENGTH);

    for (size_t i = 0; i < BITS_LENGTH; i++) {
        z.set(i, false);
        BitSetOps::clr(y, i);
        ASSERT_TRUE(0 == memcmp(y, &z, BYTES_LENGTH)) 
            << i 
            << " " << z.to_ulong() 
            << " " << y[i];
    }    
}

TEST(InterfaceTesting, filp)
{
    GTEST_SKIP();
    ::std::bitset<BITS_LENGTH> z;
    z.flip();
    
    memset(y, 0xff, BYTES_LENGTH);

    for (size_t i = 0; i < BITS_LENGTH; i++) {
        z.flip(i);
        BitSetOps::flip(y, i);
        ASSERT_TRUE(0 == memcmp(y, &z, BYTES_LENGTH)) 
            << i 
            << " " << z.to_ulong() 
            << " " << y[i];
    }    
}


TEST(InterfaceTesting, test)
{
    GTEST_SKIP();
    for (size_t i = 0; i < LENGTH; i++) {
        y[i] = myrand();
    }

    for (size_t i = 0; i < BITS_LENGTH; i++) {
        bool res0 = x->test(i);
        bool res1 = BitSetOps::test(y, i);
        ASSERT_EQ(res0, res1);
    }
}

TEST(InterfaceTesting, find_first)
{
    GTEST_SKIP();
    memset(y, 0, BYTES_LENGTH);

    for (size_t i = 0; i < 10000; i++) {
        usize r0 = myrand() % LENGTH;

        y[r0] = myrand();
        int j = x->_Find_first();
        int k = BitSetOps::find_first(y, LENGTH);
        y[r0] = 0;
        ASSERT_EQ(k, j) << "Loop to " << i;
    }
    
}


static int j = 0;
TEST(InterfaceTesting, find_next)
{
    GTEST_SKIP();
    memset(y, 0, BYTES_LENGTH);
    for (size_t i = 0; i < 100000; i++) {
        usize r0 = myrand() % LENGTH;

        y[r0] = myrand();
        int j = x->_Find_first();
        int j1 = x->_Find_next(j);
        int k1 = BitSetOps::find_next(y, j, LENGTH);
        ASSERT_EQ(k1, j1) << "Loop to " << i;
    }

    memset(y, 0, BYTES_LENGTH);
    for (size_t i = 0; i < 100000; i++) {
        usize r0 = myrand() % LENGTH;

        y[r0] = myrand();
        int max = myrand() % LENGTH;

        //int 
        j = x->_Find_first();
        for (size_t i = 0; i < max && x->_Find_next(j) != x->size(); i++) {
            j = x->_Find_next(j);
        }

        int j1 = x->_Find_next(j);
        int k1 = BitSetOps::find_next(y, j, LENGTH);

        ASSERT_EQ(k1, j1) 
            << "Loop to " << i << "; "
            << "R0 " << r0 << "; "
            << "J " << j <<"; ";
    }
}

TEST(InterfaceTesting, find_last)
{
    GTEST_SKIP();
    memset(y, 0, BYTES_LENGTH);

    for (size_t i = 0; i < 100000; i++) {
        usize r0 = myrand() % LENGTH;

        y[r0] = myrand();
        int j = x->_Find_first();
        while (x->_Find_next(j) != x->size()) {
            j = x->_Find_next(j);
        }

        int k = BitSetOps::find_last(y, LENGTH);
        ASSERT_EQ(k, j) << "Loop to " << i;
    }    
}

TEST(InterfaceTesting, left_shift)
{
    GTEST_SKIP();
    memset(y, 0, BYTES_LENGTH);

    for (size_t j = 0; j < 100000; ++j) {
        for (size_t i = 0; i < LENGTH; i++) {
            y[i] = myrand();
            d[i] = y[i];
        }

        ASSERT_TRUE(0 == memcmp(d, y, BYTES_LENGTH));

        usize t = myrand() % (BITS_LENGTH / 2);
        BitSetOps::left_shift(y, t, LENGTH);
        *z <<= t;
        
        ASSERT_TRUE(0 == memcmp(d, y, BYTES_LENGTH));
    }
}

TEST(InterfaceTesting, right_shift)
{
    GTEST_SKIP();

    memset(y, 0, BYTES_LENGTH);

    for (size_t j = 0; j < 100000; ++j) {
        for (size_t i = 0; i < LENGTH; i++) {
            y[i] = myrand();
            d[i] = y[i];
        }

        ASSERT_TRUE(0 == memcmp(d, y, BYTES_LENGTH));

        usize t = myrand() % (BITS_LENGTH / 2);
        BitSetOps::right_shift(y, t, LENGTH);
        *z >>= t;
        
        ASSERT_TRUE(0 == memcmp(d, y, BYTES_LENGTH)) << j;
    }
}


struct BitSetSample
    : ::testing::Test
{
    virtual void
    SetUp() override
    {
        memset(&my_bs, 0, BYTES_LENGTH);
        memset(&cc_bs, 0, BYTES_LENGTH);
        memset(&my_bs_1, 0, BYTES_LENGTH);

        usize *ary0 = (usize*)&my_bs;
        usize *ary1 = (usize*)&cc_bs;
        usize *ary2 = (usize*)&my_bs_1;
        for (int i = 0; i < LENGTH; ++i) {
            usize idx = myrand() % LENGTH;
            ary0[idx] = ary0[idx] ^ myrand() >> 3 ^ ~(myrand());
            ary1[idx] = ary0[idx];
            ary2[idx] = ary0[idx];
        }

    }

    ustl::core::bitset<BITS_LENGTH> my_bs;    
    ustl::core::bitset<BITS_LENGTH> my_bs_1;    
    ::std::bitset<BITS_LENGTH> cc_bs;
};

TEST_F(BitSetSample, interface_set)
{
    GTEST_SKIP();
    for (int i = 0; i < 1000; ++i) {
        usize pos = myrand() % BITS_LENGTH;
        my_bs.set(pos);
        cc_bs.set(pos);

        ASSERT_EQ(my_bs.test(pos), cc_bs.test(pos));
    }
}

TEST_F(BitSetSample, interface_clr)
{
    GTEST_SKIP();
    for (int i = 0; i < 1000; ++i) {
        usize pos = myrand() % BITS_LENGTH;
        my_bs.clr(pos);
        cc_bs.set(pos, false);

        ASSERT_EQ(my_bs.test(pos), cc_bs.test(pos));
    }
}

TEST_F(BitSetSample, interface_clr_range)
{
    GTEST_SKIP();
    for (int i = 0; i < 10000; ++i) {
        usize pos = myrand() % LENGTH;
        if (pos > LENGTH - 4) {
            pos = LENGTH - 4;
        }

        usize n = myrand() % 234;
        usize beg = pos * WORD_BITS;
        usize end = beg + n;

        my_bs.clr_range(beg, end);
        
        for (int i = beg; i < end; i++) {
            cc_bs.set(i, false);
            ASSERT_TRUE(my_bs.test(i) == cc_bs.test(i));
        }
    }
}

TEST_F(BitSetSample, interface_operator_ls)
{
    GTEST_SKIP();
    for (int i = 0; i < 10000; i++) {
        this->SetUp();
        usize shift = myrand() % (BITS_LENGTH >> (myrand() % 10));

        my_bs <<= shift; 
        cc_bs <<= shift; 

        ASSERT_EQ(0, memcmp(&my_bs, &cc_bs, BYTES_LENGTH)) << "Index " << i;
    }
}

TEST_F(BitSetSample, interface_operator_rs)
{
    GTEST_SKIP();
    for (int i = 0; i < 10000; i++) {
        this->SetUp();
        usize shift = myrand() % (BITS_LENGTH >> (myrand() % 10));

        my_bs >>= shift; 
        cc_bs >>= shift; 

        ASSERT_EQ(0, memcmp(&my_bs, &cc_bs, BYTES_LENGTH)) << "Index " << i;
    }
}

TEST_F(BitSetSample, interface_none)
{
    GTEST_SKIP();
    for (int i = 0; i < 10000; i++) {
        this->SetUp();
        ASSERT_FALSE(my_bs.none());
        ASSERT_FALSE(cc_bs.none());
    }

    memset(&my_bs, 0, BYTES_LENGTH);
    memset(&cc_bs, 0, BYTES_LENGTH);
    ASSERT_TRUE(my_bs.none());
    ASSERT_TRUE(cc_bs.none());
}

TEST_F(BitSetSample, interface_any)
{
    GTEST_SKIP();
    for (int i = 0; i < 10000; i++) {
        this->SetUp();
        ASSERT_TRUE(my_bs.any());
        ASSERT_TRUE(cc_bs.any());
    }

    memset(&my_bs, 0, BYTES_LENGTH);
    memset(&cc_bs, 0, BYTES_LENGTH);
    ASSERT_FALSE(my_bs.any());
    ASSERT_FALSE(cc_bs.any());
    
}

TEST_F(BitSetSample, interface_flip)
{
    GTEST_SKIP();
    for (int i = 0; i < 10000; i++) {
        this->SetUp();
        ASSERT_EQ(0, memcmp(&my_bs, &cc_bs, BYTES_LENGTH)) << "Index " << i;
        usize pos = myrand() % BITS_LENGTH;

        my_bs.flip(pos);
        cc_bs.flip(pos);
        ASSERT_EQ(my_bs.test(pos), cc_bs.test(pos));
    }
}

TEST_F(BitSetSample, interface_clr_first)
{
    GTEST_SKIP();
    for (int i = 0; i < 10000; i++) {
        this->SetUp();
        ASSERT_EQ(0, memcmp(&my_bs, &cc_bs, BYTES_LENGTH)) << "Index " << i;

        auto p0 = cc_bs._Find_first();
        auto p1 = my_bs.clr_first();
        ASSERT_EQ(p1, p0);
    }
}

TEST_F(BitSetSample, interface_set_first)
{
    char *buf = (char *)&my_bs;
    memset(buf, 0, BYTES_LENGTH);
    memset(buf, 0xff, 13);
    auto p0 = my_bs.set_first();
    ASSERT_EQ(p0, 13 * BYTE_BITS);

    memset(buf + 13, 0xdf, 1);
    p0 = my_bs.set_first();
    ASSERT_EQ(p0, 13 * BYTE_BITS + 5);
}

TEST_F(BitSetSample, interface_operator_eq)
{
    this->SetUp();    
    ASSERT_TRUE(my_bs == my_bs_1);

    usize *y = (decltype(y))&my_bs;
    usize *x = (decltype(x))&my_bs_1;
    --x[LENGTH - 1];
    ASSERT_TRUE(my_bs_1 < my_bs) << x[LENGTH - 1] << " " << y[LENGTH - 1];
}