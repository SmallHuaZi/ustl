#include <iostream>
// #include <map>
// #include <vector>

#include "rbtree.h"
#include "list.h"
#include "vector.h"
#include <vector>
#include <bits/stl_list.h>
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
    std::vector<int> __std_vec;
    int __ary[] = {1, 2, 3, 4, 5, 6, 7};
    for (auto __tmp : __ary)
        __std_vec.push_back(__tmp);
    std::cout << __std_vec.capacity() << std::endl;

    try
    {
        __vec[0];
    }
    __ustl_catch(ustl::exception)
    {
        std::cout << __e.message() << std::endl;
    }
    return 0;
}