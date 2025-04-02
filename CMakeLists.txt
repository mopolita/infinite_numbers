cmake_minimum_required(VERSION 3.10)

# create the project
project(InfiniteInt)

# make the compiler use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set the output directory for the executable to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# search for all .cpp files in the src directory and add them to the executable
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(exe ${SOURCES})

# add the include directory to the compiler's search path
target_include_directories(exe PRIVATE include)
