cmake_minimum_required(VERSION 3.10)
project(InfiniteInt LANGUAGES CXX)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Option : Build test executable ?
option(BUILD_TEST "Build test executable" OFF)

# Sources files (exclude test.cpp)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create a static library
add_library(infint STATIC ${SOURCES})
target_include_directories(infint PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# apply compiler optimizations on release build
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# specifics optimizations for infint
target_compile_options(infint PRIVATE $<$<CONFIG:Release>:-O3>)

# If BUILD_TEST is enabled, add the test executable
if(BUILD_TEST)
    message(STATUS "Test build enabled.")

    add_executable(test_runner test/test.cpp)
    target_link_libraries(test_runner PRIVATE infint)
    target_include_directories(test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()
