#include <iostream>
// #include <string>
// #include <functional>
// #include <utility>
// #include <bits/stl_map.h>
// #include <map>
// #include <forward_list>
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
#include <bits/shared_ptr_base.h>
// #include <cstring>
// #include <string>
// #include <queue>

// template <typename _Tp = int>
// using list = std::list<_Tp>;


struct recycle
{
    void
    operator()(void *)
    {}
};


int 
main(int argc, char **argv)
{
    ustl::vector<int>       __vec(10, 10);

    // for(auto __x : __vec)
    //     std::cout << __x << std::endl;

    for(ustl::size_t __i = 0; __i < 20; ++__i)
        __vec.push_back(__i);
    
    std::cout << *__vec.insert(++++++__vec.cbegin(), 200);
    std::cout << std::endl;

    __vec.reverse();
    __vec.remove(10);

    for(auto __x : __vec)
        std::cout << __x << std::endl;
    
    return 0;
}