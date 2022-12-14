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

// #include "include/config.h"

#include "include/ustl_tmp.h"
// #include "include/ustl_exception.h"
// #include "include/ustl_functor.h"
// #include "include/ustl_memory.h"
// #include "include/ustl_type_traits.h"
// #include "include/ustl_algorithm.h"
// #include "include/ustl_iterator.h"
// #include "include/ustl_container.h"

// #include <bits/stl_tree.h>


#define __IS_STD 0

struct debug
{
    debug() = default;

    debug(debug const &__lval)
    { std::cout << "lval constructor" << std::endl; }

    debug(debug &&__lval)
    { std::cout << "rval constructor" << std::endl; }

    debug &
    reference()
    { return    *this; }


    int 
    operator()()
    { return 1; }
};

struct debug_derived
{
    int
    reference()
    { return    1, 2; }

    int 
    operator()(int a)
    { return a; }
};

template <typename A>
void
function(A &&__a)
{ debug a(ustl::forward<A &&>(a)); }


#include <list>

int 
main(int argc, char **argv)
{
    std::list<int> __list(10, 2);
    __list.insert(__list.begin(), __list.begin(), __list.end());
    for(auto __x : __list)
        std::cout << __x << std::endl;
    return 0;
}