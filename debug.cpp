#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <deque>

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
#include "include/ustl_memory.h"
#include "include/ustl_type_traits.h"
#include "include/ustl_algorithm.h"
#include "include/ustl_iterator.h"
#include "include/ustl_container.h"


#define __IS_STD 0

int 
main(int argc, char **argv)
{
#if defined(__IS_STD) && __IS_STD == 1
    std
#else
    ustl
#endif
    ::deque<int> __ustl_deque;

    for(int __i = 0; __i < 258; ++__i) {
        __ustl_deque.push_front(__i);
    }

    for(int __i = 258; __i < 512; ++__i) {
        __ustl_deque.push_back(__i);
    }

    auto __end = __ustl_deque.end();

    for(auto __x : __ustl_deque)
        std::cout << __x << std::endl;
    return 0;
}