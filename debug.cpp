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
    { return a; }
};

struct compare
{
    bool
    operator()(int const &a, int const &b) const
    { return a < b; }
};

#include "include/ustl_tmp.h"
#include "include/ustl_exception.h"
#include "include/ustl_functor.h"
#include "include/ustl_memory.h"
#include "include/ustl_type_traits.h"
#include "include/ustl_algorithm.h"
#include "include/ustl_iterator.h"
#include "include/ustl_container.h"

// #include <mutex>
// #include <memory>
#include <cstring>
#include <string>

// template <typename _Tp = int>
// using list = std::list<_Tp>;

int 
main(int argc, char **argv)
{
    // ustl::list<int> __list(10, 2);
    // __list.resize(20, 10);
    // for(auto __x : __list)
    //     std::cout << __x << std::endl;
    char const *__x = "abc";
    char const *__y = "abce";

    std::string __sx(__x);
    std::string __sy(__y);

    std::cout << __sx.compare(__sy) << std::ends;


    return 0;
}