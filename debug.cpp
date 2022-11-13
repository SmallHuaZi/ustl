#include <iostream>
// #include <map>
// #include <vector>

#include "rbtree.h"
#include "list.h"
#include "vector.h"
#include <vector>
#include <bits/stl_vector.h>
#include <bits/stl_list.h>
#include <list>
#include <exception>
// #include <unistd.h>
// using namespace ustl::internal_ustl;

struct get_key
{
    int const &
    operator()(int const &a)
    {
        return a;
    }
};

struct compare
{
    bool
    operator()(int const &a, int const &b) const
    {
        return a < b;
    }
};
bool equal_16(int __val)
{
    return 16 == __val;
}

#include "allocate_type.h"

int main(int argc, char **argv)
{
    ustl::vector<int> __vec;
    int const a = 10;
    __vec.insert(__vec.cbegin(), a);

    // std::vector<int> __vec;

    // int __ary[] = {1, 2, 3, 4, 5, 6, 7};
    // for (auto &__tmp : __ary)
    //     __vec.push_back(__tmp);
    // __vec.reserve(12);

    // __vec.insert(__vec.begin() + 5, 3, 10);
    // for (auto &__tmp : __vec)
    //     std::cout << __tmp << std::endl;
    return 0;
}