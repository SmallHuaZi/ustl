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

#include "include/ustl_tmp.h"
#include "include/ustl_exception.h"
#include "include/ustl_functor.h"
#include "include/ustl_memory.h"
#include "include/ustl_type_traits.h"
#include "include/ustl_algorithm.h"
#include "include/ustl_iterator.h"
#include "include/ustl_container.h"

// #include <bits/stl_tree.h>


// #define __IS_STD 0

// struct debug
// {
//     debug() = default;

//     debug(debug const &__lval)
//     { std::cout << "lval constructor" << std::endl; }

//     debug(debug &&__lval)
//     { std::cout << "rval constructor" << std::endl; }

//     debug &
//     reference()
//     { return    *this; }


//     int 
//     operator()()
//     { return 1; }
// };

struct debug_derived
{
    int
    reference() noexcept(noexcept(operator()(1)))
    { return    1, 2; }

    int 
    operator()(int a) noexcept(false)
    { 
        throw "";
        return a; 
    }
};

// template <typename A>
// void
// function(A &&__a)
// { debug a(ustl::forward<A &&>(a)); }


#include <list>

template <typename _Tp = int>
using list = std::list<_Tp>;

int 
main(int argc, char **argv)
{
    // debug_derived de;
    // de.reference();
    // bool __excep = noexcept(debug_derived()(1));
    ustl::list<int> __list;
    for(ustl::size_t __n = 0; __n <20; ++__n)
        __list.push_back(__n);
    
    __list.reverse();
    // __list.sort();

    auto    __first = __list.rbegin();
    auto    __last  = __list.rend();

    while(__first != __last)
        std::cout << *++__first << " ";
    std::cout << std::endl;

    __list.sort();

    for(auto __z : __list)
        std::cout << __z << std::endl;
    // list<char>  __clist;
    // __clist.push_back('10');
    // std::cout << *__clist.begin() << std::endl;
    return 0;
}