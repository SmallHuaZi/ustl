#include "./container/rbtree.h"
// #include "./container/tuple.h"
// #include <string>
#include <bits/stl_tree.h>
struct debug
{
  struct __1
  {
    int _M_a;
  };

  struct __2
  {
    __1 *_M_p;
  };

  __1 *
  operator->()
  {
    return _M_p->_M_p;
  }
  __2 *_M_p;
};

struct b
{
  int operator()(int a)
  {
    return a;
  }
};

int main(int argc, char **argv)
{

  std::_Rb_tree<int, int, b, std::less<int>> __a;
  __a._M_insert_equal(10);
  decltype(__a)::iterator __itr = __a.end();
  return 0;
}