
// #include "./container/tuple.h"
// #include <string>
#include <bits/stl_tree.h>
#include <iostream>
// #include <map>

#include "rbtree.h"
using namespace ustl::internal_ustl;

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

int main(int argc, char **argv)
{

    rb_tree<int, int, get_key, compare> __rbt;
    decltype(__rbt)::_node_ptr __root;
    int __ary[] = {16, 3, 7, 11, 9, 26, 18, 14, 15, 19, 30, 40, 32, 45};
    // int __ary[] = {6, 2, 15, 10, 18, 9, 12, 20, 8};
    for (auto __tmp : __ary)
    {
        __rbt.insert_unique(__tmp);
        // __rbt.insert_equal(__tmp);
        __root = __rbt.debug_root();
    }

    decltype(__rbt)::iterator __itr = __rbt.upper_bound(9);

    for (auto __tmp : __ary)
    {
        __rbt.erase(__tmp);
        __root = __rbt.debug_root();
    }

    for (auto __tmp : __rbt)
        std::cout << __tmp << std::endl;

    return 0;
}