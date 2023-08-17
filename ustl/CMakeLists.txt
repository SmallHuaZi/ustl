cmake_minimum_required(VERSION 3.10)
project(
    ustl 
    VERSION 1.0.0 
    DESCRIPTION "ustl is an stl-like library"
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(PROJECT_NAMESPACE ustl::)

# submodule
add_subdirectory(src/core)
add_subdirectory(src/std)


# version header
configure_file(
    ${CMAKE_SOURCE_DIR}/etc/headers/ustl.hpp.txt
    ${CMAKE_SOURCE_DIR}/inc/ustl/ustl
)


include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/etc/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}-${PROJECT_VERSION}"
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)


# install standard headers
install(
    DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/
    DESTINATION inc
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)


# install configure files
install(
    FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION "lib/cmake/${PROJECT_NAME}-${PROJECT_VERSION}"
)