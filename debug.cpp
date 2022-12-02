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

#include "config.h"
#include "ustl_tmp.h"

#include "ustl_exception.h"
#include "ustl_memory.h"
#include "ustl_type_traits.h"
#include "ustl_algorithm.h"
#include "ustl_iterator.h"
#include "ustl_container.h"

struct a
{
    /* data */
};

struct b
{
    b &operator=(a &&__a)
    {
    }
};


int main(int argc, char **argv)
{
    std::deque<int> __deque;
    __deque.push_back(0);
    __deque.push_back(1);
    __deque.push_back(2);
    std::cout<< sizeof(__deque)<< std::endl;
    return 0;
}