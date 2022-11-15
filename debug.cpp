#include <iostream>
// #include <map>
// #include <vector>

#include "rbtree.h"
#include "list.h"
#include "vector.h"
#include <vector>
#include <bits/stl_vector.h>
// #include <bits/stl_list.h>
// #include <list>
// #include <exception>
// #include <iterator>
// #include <unistd.h>
// using namespace ustl::internal_ustl;

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
bool equal_16(int __val)
{
    return 16 == __val;
}

#include "allocate_type.h"

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
int object::_S_count = 0;
int object::_S_copy_count = 0;

int main(int argc, char **argv)
{
    ustl::vector<object> __vec;
    ustl::vector<object> __vec1;

    int __ary[] = {1, 1, 2, 3, 4, 5, 6, 7, 1, 1};
    for (auto &__tmp : __ary)
        __vec.emplace_back(__tmp);

    __vec1.assign(__vec.begin(), __vec.end());
    auto __first = __vec1.cbegin();
    __vec1.insert(++__first, __vec.begin(), __vec.end());
    // for (auto &__tmp : __vec)
    //     std::cout << __tmp._M_data << std::endl;
    for (auto &__tmp : __vec1)
        std::cout << __tmp._M_data << std::endl;
    // std::cout << __vec[10]._M_data << std::endl;
    // __std_vec.reserve(19);
    // std::cout << __std_vec.capacity() << std::endl;
    return 0;
}