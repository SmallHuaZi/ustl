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

    for(int __i = 0; __i < 258; ++__i)
        __ustl_deque.push_front(__i);

    // for(auto __x : __ustl_deque)
    //     std::cout << __x << std::endl;   

    int __i;
    try{

        for(__i = 258; __i < 512; ++__i) {
            if(385 == __i) 
                int a = 10;
            __ustl_deque.push_back(__i);

        }
    }catch(...) {
        std::cout << "exception index:" 
                  << __i 
                  << std::endl;
    }

    auto __first = __ustl_deque.cbegin();
    auto __end = __ustl_deque.cend();

    // for(auto __x : __ustl_deque)
    //     std::cout << __x << std::endl;   
    
    for(__i = 0; __i < 10; ++__first, (void)++__i);

    // std::cout << "__end value = " <<*__end << std::endl;
    __ustl_deque.erase(__end);

    int __ary[] = {0, 1, 2, 3, 4};

    __ustl_deque.insert(__first, __ary, __ary + sizeof(__ary)/sizeof(int));
    __ustl_deque.pop_front();
    __ustl_deque.pop_back();

    for(auto __x : __ustl_deque)
        std::cout << __x << std::endl;   
    
    ustl::size_t __size = __ustl_deque.size();
    std::cout << "__ustl_deque size = "
              << __size
              << std::endl;
    auto __first1 = __ustl_deque.begin();

    std::cout << "index 256 = "
              << (__ustl_deque[256] = 100)
              << std::endl
              << "index 256 = "
              << __first1[256]
              << std::endl;

    return 0;
}