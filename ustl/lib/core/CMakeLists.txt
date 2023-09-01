set(COMPONENT_NAME core)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE SrcFiles 
    ${PROJECT_SOURCE_DIR}/inc/${COMPONENT_NAME}/*.hpp
    ${PROJECT_SOURCE_DIR}/inc/${COMPONENT_NAME}/*.h
    ${PROJECT_SOURCE_DIR}/inc/*.hpp
    *.cpp
    *.c
)


add_library(${COMPONENT_NAME} STATIC ${SrcFiles})
add_library(${PROJECT_NAMESPACE}${COMPONENT_NAME} ALIAS ${COMPONENT_NAME})


if(CMAKE_BUILD_TYPE MATCHES Debug)
target_compile_definitions(${COMPONENT_NAME} 
    PUBLIC -D__USTL_CORE_DEV
)
endif()


target_include_directories(
    ${COMPONENT_NAME} 
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:inc>
)


# Create configure files
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/etc/cmake/${COMPONENT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${COMPONENT_NAME}Config.cmake
    INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}-${PROJECT_VERSION}"
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${COMPONENT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion 
)


install(
    TARGETS ${COMPONENT_NAME} 
    EXPORT ${COMPONENT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)


# install configure files
install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${COMPONENT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${COMPONENT_NAME}ConfigVersion.cmake
    DESTINATION lib/cmake/${COMPONENT_NAME}
)


# install imported configure files
install(
    EXPORT ${COMPONENT_NAME}Targets
    FILE ${COMPONENT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAMESPACE}
    DESTINATION "lib/cmake/${PROJECT_NAME}-${PROJECT_VERSION}"
    COMPONENT ${COMPONENT_NAME}
)