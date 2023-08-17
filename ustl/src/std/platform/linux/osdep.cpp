#include <std/platform/osdep.hpp>
#include <std/platform/linux/linux.hpp>

#define TO_STR(...)  #__VA_ARGS__
#define SC_NUM(num)  TO_STR(mov num, %rax\n\t)
#define SC_ONE(arg)  TO_STR()

using namespace ustl;
using namespace ustl::std;
using namespace internal;
using namespace platform;


usize
os::open()
{

}

void
os::close()
{

}