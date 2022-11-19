#include <iostream>
#include <string>

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

// #include "allocate_type.h"

struct object
{
    object() = default;
    object(int a)
        : _M_data(a)
    {
        std::cout << "init"
                  << ++_S_count
                  << std::endl;
        // if (_S_count > 2)
        //     throw "太多了";
    }

    object(object const &other)
        : _M_data2(other._M_data2),
          _M_data(other._M_data)
    {
        std::cout << "copy"
                  << ++_S_copy_count
                  << std::endl;
    }

    friend bool
    operator==(object const &__l,
               object const &__r)
    {
        return __l._M_data2 == __r._M_data2 &&
               __l._M_data == __r._M_data;
    }

    friend bool
    operator!=(object const &__l,
               object const &__r)
    {
        return __l._M_data2 != __r._M_data2 ||
               __l._M_data != __r._M_data;
    }

    static int _S_count;
    static int _S_copy_count;
    int _M_data;
    long _M_data2;
};

#include "config.h"
#include "ustl_tmp.h"

#include "ustl_exception.h"
#include "ustl_memory.h"
#include "ustl_type_traits.h"
#include "ustl_algorithm.h"
#include "ustl_iterator.h"
#include "ustl_container.h"

int main(int argc, char **argv)
{

    ustl::string __str;
    __str.append("hello world");
    __str.append(__str);
    auto __idx = __str.rfind("hello");
    std::cout << __str[__idx] << std::endl;

    return 0;
}