#ifndef __UT_CONFIG_HPP__
#define __UT_CONFIG_HPP__


#include <cassert>

#include <thread>
#include <random>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>


#include "gtest/gtest.h"


#ifndef __TEST_ENTRY__
int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif

#endif