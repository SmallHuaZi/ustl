#include "config.hpp"
// #include <ustl/std/rbtree>
// #include <initializer_list>

// using namespace ustl::std;


// struct STDRBTreeTestSample
//     : ::testing::Test
// {

//     virtual void 
//     SetUp() override
//     {

//     }

//     virtual void 
//     TearDown() override
//     {

//     }

// public:
//     rbtree<int, pair<int, int>, elem_extractor<0, pair<int, int>>> tree_0;
// };


// static std::vector<int> 
// get_random_test_dat(long len)
// {
//     std::vector<int> items;
//     std::random_device  rd;
//     std::mt19937    gen(rd());
//     std::uniform_int_distribution<> dis(1, 2000);

//     for (int i = 0; i < len; ++i) {
//         int r = dis(gen);
//         items.push_back(r);
//     }
//     return items;
// }


// TEST_F(STDRBTreeTestSample, assign_unique)
// {
//     std::vector<int> items = get_random_test_dat(1000);
//     auto first1 = items.begin();
//     auto last1 = items.begin();

//     tree_0.assign_unique(first1, last1);
//     std::sort(items.begin(), items.end());

//     auto first2 = tree_0.begin();
//     auto last2 = tree_0.end();

//     ASSERT_TRUE(std::lexicographical_compare(first1, last1, first2, last2));
// }