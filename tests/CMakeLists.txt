cmake_minimum_required(VERSION 3.20)
project(ustl_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OUT)
set(CMAKE_BUILD_TYPE "Debug")

# add_subdirectory(../ustl)
add_subdirectory(third-party/googletest)

enable_testing()
include(GoogleTest)

# Acquisition all cpp files
file(GLOB USTL_UNIT_TESTS src/*.cpp)

# Create all tests
foreach(In ${USTL_UNIT_TESTS})
    get_filename_component(FileName ${In} NAME_WE) 
    set(ExecutableName UnitTest-${FileName})

    add_executable(${ExecutableName} ${In})
    target_link_libraries(${ExecutableName}
        PRIVATE gtest gtest_main
    )

    target_include_directories(${ExecutableName}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
        PRIVATE ../ustl/inc
    )

    set_target_properties(${ExecutableName}
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/tests
    )

    # Add tests to CTest
    gtest_discover_tests(${ExecutableName}
        TEST_PREFIX ${ExecutableName}_
        PROPERTIES TIMEOUT 1
    )
endforeach()