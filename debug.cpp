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

#include <bits/stl_tree.h>


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
};

struct debug_derived
{
    int
    reference()
    { return    1, 2; }
    debug   _M_data;
};

template <typename A>
void
function(A &&__a)
{ debug a(ustl::forward<A &&>(a)); }


int 
main(int argc, char **argv)
{
    function(debug());
    auto a = debug();
    function(a);
    std::cout <<debug_derived().reference()<< std::endl;;

    return 0;
}