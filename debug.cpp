
// #include "./container/tuple.h"
// #include <string>
// #include <bits/stl_tree.h>
#include <iostream>

#include "./container/rbtree.h"
using namespace ustl::internal_ustl;

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
template <typename _T>
struct ndoe
{
    typedef _T value_type;
    value_type _M_val;

    struct iterator
    {
        value_type _M_val;
        iterator(value_type __v)
            : _M_val(__v) {}

        bool
        operator!=(iterator &__other)
        {
            return _M_val != __other._M_val;
        }

        bool
        operator==(iterator &__other)
        {
            return _M_val == __other._M_val;
        }

        value_type
        operator++()
        {
            return (++_M_val);
        }

        value_type
        operator*()
        {
            return _M_val;
        }
    };

    iterator
    begin()
    {
        return 0;
    }

    iterator
    end()
    {
        return 10;
    }
};
int main(int argc, char **argv)
{
    rb_tree<int, int, get_key, compare> __rbt;
    decltype(__rbt)::_node_ptr __root;
    int __ary[] = {16, 3, 7, 11, 9, 26, 18, 14, 15, 15};
    // int __ary[] = {6, 2, 15, 10, 18, 9, 12, 20, 8};
    for (auto __tmp : __ary)
    {
        __rbt.insert_unique(__tmp);
        // __rbt.insert_equal(__tmp);
        __root = __rbt.debug_root();
    }
    ndoe<int> __n;
    for (auto __tmp : __n)
        std::cout << __tmp << std::endl;

    decltype(__rbt)::iterator __begin = __rbt.begin();
    for (; __begin != __rbt.end(); ++__begin)
        std::cout << *__begin << std::endl;
    return 0;
}