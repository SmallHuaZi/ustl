#include <config.hpp>

struct tag_1 {};
struct tag_2 {};

template <typename Struct>
struct Trait
{
    typedef Struct::tag     tag;
};

struct Struct_0
{
    typedef tag_1   tag;
};

struct Struct_1
{
    typedef tag_2   tag;
};


template <typename Struct, typename Tag = Trait<Struct>::tag>
std::enable_if_t<std::is_same_v<Tag, tag_1>, std::string>
function(Struct x)
{
    return "Struct_0";
}

template <typename Struct, typename Tag = Trait<Struct>::tag>
std::enable_if_t<std::is_same_v<Tag, tag_2>, std::string>
function(Struct x)
{
    return "Struct_1";
}

TEST(SimulationPartializedFunction, function)
{
    Struct_0 _0{};
    ASSERT_EQ(function(_0), "Struct_0");

    Struct_1 _1{};
    ASSERT_EQ(function(_1), "Struct_1");
}