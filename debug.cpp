#include <iostream>
#include <string>
#include <functional>
#include <forward_list>

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

    static inline int _S_count = 0;
    static inline int _S_copy_count = 0;
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
    ustl::slist<int> __si;
    ustl::slist<int> __sint;
    int __ary[] = {2, 6, 1, 3, -1, -5, 9, 4};
    // int __ary2[] = {2, 4, 6, 8, 10};

    __sint.assign(__ary, __ary + sizeof(__ary) / sizeof(int));
    __sint.sort();

    auto __first = __sint.begin();
    ++ ++ ++__first;
    auto __end = __first;
    ++ ++ ++__end;

    __sint.splice_after(__first, __ary, __ary + 4);
    for (auto __tmp : __sint)
        std::cout << __tmp << std::endl;

    __sint.erase_after(__first, __end);
    for (auto __tmp : __sint)
        std::cout << __tmp << std::endl;

    return 0;
}

struct basic
{
    int _M_value_field;
    basic *_M_next;
};

struct derived
    : basic
{
    // derived(int a)
    //     : _M_value_field(a) {}
};
