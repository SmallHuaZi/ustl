// #include <iostream>
// #include <string>
// #include <functional>
// #include <utility>
// #include <bits/stl_map.h>

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
    ustl::hashtable<int, int> __ustl_hash;
    float __f = 0.75;
    return 0;
}