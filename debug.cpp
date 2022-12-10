#include <iostream>
// #include <string>
// #include <functional>
// #include <utility>
// #include <bits/stl_map.h>
// #include <map>
// #include <hash_map>

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

#include "include/config.h"

#include "include/ustl_tmp.h"
#include "include/ustl_exception.h"
#include "include/ustl_functor.h"
#include "include/ustl_memory.h"
#include "include/ustl_type_traits.h"
#include "include/ustl_algorithm.h"
#include "include/ustl_iterator.h"
#include "include/ustl_container.h"


#define __IS_STD 0

int 
main(int argc, char **argv)
{
    // ustl::hashtable<int, int> __ustl_hash;
    // __ustl_hash._M_insert_aux(1, 1);
    ustl::rb_tree<int, int, get_key, compare> __rbt;
    auto __root = decltype(__rbt)::root(__rbt);
    for(int __i = 0; __i < 20; ++__i)
    {
        __rbt.insert_equal(__i);
        __root = decltype(__rbt)::root(__rbt);
    }
    for(auto &__x : __rbt)
        std::cout << __x << std::endl;
    ustl::size_t size = ustl::_tree_node_height(__root);
    std::cout << size << std::endl;

    return 0;
}
